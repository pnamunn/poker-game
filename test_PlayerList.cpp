#include <gtest/gtest.h>
#include "PlayerList.h"
#include "Player.h"
#include <iostream>
using namespace std;

///////// CREATE FRAMEWORKS ////////

class BasePlayerList_F : public testing::Test {
    protected:
        PlayerList list = PlayerList(NULL);  // init to not use outOfGame list
        Player player1,  *p1 = &player1;
        Player player2,  *p2 = &player2;
        Player player3,  *p3 = &player3;
        Player player4,  *p4 = &player4;

        void add4Players() {
            list.addPlayer(*p1);
            list.addPlayer(*p2);
            list.addPlayer(*p3);
            list.addPlayer(*p4);
            name4Players();
        }

        void name4Players() {
            player1.name = "P1";
            player2.name = "P2";
            player3.name = "P3";
            player4.name = "P4";
        }
};

class AddPlayerTest : public BasePlayerList_F { };

class RemovePlayerTest : public BasePlayerList_F {
    void SetUp() override {
        add4Players();
    }
};

class ListPlayersTest : public BasePlayerList_F { };
// class ChangeHeadTest : public BasePlayerList_F { };
class GetLengthTest : public BasePlayerList_F { };

////////////////////////////////////


//// addPlayer

TEST_F(AddPlayerTest, MakeCDLLOfOne) { // CDDL = Circular Doubly Linked List
    list.addPlayer(*p1);
    EXPECT_EQ(list.head, p1);
    EXPECT_EQ(list.head->next, p1);
    EXPECT_EQ(list.head->last, p1);
}

TEST_F(AddPlayerTest, MakeCDLLOfTwoOrMore) {
    add4Players();

    // p1 is head.  Points to p2, circularly back to p3
    EXPECT_EQ(list.head, p1);
    EXPECT_EQ(list.head->next, p2);
    EXPECT_EQ(list.head->last, p4);

    // p2 points to p3 & back to p1
    EXPECT_EQ((list.head->next)->next, p3);
    EXPECT_EQ((list.head->next)->last, p1);

    // p3 points to p4 & back to p2
    EXPECT_EQ((list.head->next->next)->next, p4);
    EXPECT_EQ((list.head->next->next)->last, p2);

    // p4 points circularly next to p1 & back to p3
    EXPECT_EQ((list.head->next->next->next)->next, p1);
    EXPECT_EQ((list.head->next->next->next)->last, p3);
}


//// removePlayer

TEST_F(RemovePlayerTest, RemoveFirstLink) {
    list.removePlayer("P1");
    EXPECT_EQ(list.head, p2);
}

TEST_F(RemovePlayerTest, RemoveMiddleLink) {
    list.removePlayer("P3");
    // after p3 is removed, p2 and p4 get linked
    EXPECT_EQ((list.head->next)->next, p4);
    EXPECT_EQ((list.head->next->next)->last, p2);
}

TEST_F(RemovePlayerTest, RemoveFinalLink) {
    list.removePlayer("P4");
    // after p4 is removed, p1 and p3 get linked
    EXPECT_EQ(list.head->last, p3);
    EXPECT_EQ((list.head->next->next)->next, p1);
}

TEST_F(RemovePlayerTest, MakeCDLLEmpty) {
    list.removePlayer("P3");
    list.removePlayer("P4");
    list.removePlayer("P1");
    list.removePlayer("P2");
    EXPECT_EQ(list.head, nullptr);
}

TEST_F(RemovePlayerTest, AttemptToRemovePlayerWhoseNameDNE) {
    testing::internal::CaptureStdout();     // start capturing cout stream
    list.removePlayer("banana");
    EXPECT_EQ(testing::internal::GetCapturedStdout(),
              "Cannot remove.  Player name 'banana' not found.\n");
}

// typa unit test you delete
// TEST_F(RemovePlayerTest, NotUsingOutOfGameList) {
//     list.removePlayer("P4");
//     EXPECT_EQ(list.outOfGame, nullptr);
// }

TEST_F(RemovePlayerTest, UseOutOfGameList) {
    PlayerList outList(NULL);
    list.outOfGame = &outList;
    list.removePlayer("P4");
    list.removePlayer("P1");
    list.removePlayer("P2");
    list.removePlayer("P3");

    // check that outOfGame list receives the removed players
    EXPECT_EQ(list.outOfGame->head->next, p1);
    EXPECT_EQ(list.outOfGame->head->next->next, p2);
    EXPECT_EQ(list.outOfGame->head->next->next->next, p3);
    // verify the outOfGame list is CDLL
    EXPECT_EQ(list.outOfGame->head->last, p3);
}


//// listPlayers

TEST_F(ListPlayersTest, EmptyList) {
    testing::internal::CaptureStdout();
    list.listPlayers(false);
    EXPECT_EQ(testing::internal::GetCapturedStdout(),
              "Arrrg list be empty\n");
}

TEST_F(ListPlayersTest, OnlyInPlayers) {
    // list of 4 in players, 0 out players; with outOfGame not init'ed
    add4Players();

    testing::internal::CaptureStdout();
    list.listPlayers(false);
    EXPECT_EQ(testing::internal::GetCapturedStdout(),
              "Listing players in game...\nP1\nP2\nP3\nP4\n\n");
}

TEST_F(ListPlayersTest, InPlayersAndOutPlayers) {
    PlayerList outList(NULL);
    list.outOfGame = &outList;
    add4Players();
    list.removePlayer("P3");
    list.removePlayer("P1");
    // TODO change so does not rely on removePlayers()?

    testing::internal::CaptureStdout();
    list.listPlayers(true);
    EXPECT_EQ(testing::internal::GetCapturedStdout(),
              "Listing players in game...\nP2\nP4\n\nListing players out of game...\nP3\nP1\n\n");
}


//// changeHead

// // TODO parameterize to see if each player has an equal probability
// TEST_P(ChangeHeadTest, ) {

// }

// INSTANTIATE_TEST_SUITE_P(EqualProbability, ChangeHeadTest, Range(0, 4))


//// getLength

TEST_F(GetLengthTest, EmptyList) {
    EXPECT_EQ(list.getLength(), 0);
}

TEST_F(GetLengthTest, ListOf4) {
    add4Players();
    EXPECT_EQ(list.getLength(), 4);
}




int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}