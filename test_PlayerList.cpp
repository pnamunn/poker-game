#include <gtest/gtest.h>
#include "PlayerList.h"
#include "Player.h"
#include <iostream>
using namespace std;


class AddPlayerTest : public testing::Test {
    protected:
        PlayerList list = PlayerList(true);
        Player player1,  *p1 = &player1;
        Player player2,  *p2 = &player2;
        Player player3,  *p3 = &player3;
        Player player4,  *p4 = &player4;


        void add3Players() {
            list.addPlayer(*p1);
            list.addPlayer(*p2);
            list.addPlayer(*p3);
        }
};

class RemovePlayerTest : public AddPlayerTest {
    public:
        void add4Players() {
            add3Players();
            list.addPlayer(*p4);
        }
        void name4Players() {
            player1.name = "P1";
            player2.name = "P2";
            player3.name = "P3";
            player4.name = "P4";
        }
};

TEST_F(AddPlayerTest, listOfOne) {
    list.addPlayer(*p1);

    // p1 is the list's head
    // & the next and last ptrs point to itself
    EXPECT_EQ(list.head, p1);
    EXPECT_EQ(list.head->next, p1);
    EXPECT_EQ(list.head->last, p1);
}

TEST_F(AddPlayerTest, listOfTwoOrMore) {
    // list.addPlayer(*p1);
    // list.addPlayer(*p2);
    // list.addPlayer(*p3);
    add3Players();

    // p1 is still head, points to p2, & circularly to p3
    EXPECT_EQ(list.head, p1);
    EXPECT_EQ(list.head->next, p2);
    EXPECT_EQ(list.head->last, p3);

    // p2 points to p3 & back to p1
    EXPECT_EQ((list.head->next)->next, p3);
    EXPECT_EQ((list.head->next)->last, p1);

    // p3 points circularly to p1 & back to p2
    EXPECT_EQ((list.head->next->next)->next, p1);
    EXPECT_EQ((list.head->next->next)->last, p2);
}

TEST_F(RemovePlayerTest, removeAny) {
    add4Players();
    name4Players();
    list.outList->head = NULL;  // for whatever reason, address is being deallocated before test,
                                // resetting it back to 0xCCCC...

    // try to remove player that does not exist
    testing::internal::CaptureStdout();     // start capturing cout stream
    list.removePlayer("banana");
    EXPECT_EQ(testing::internal::GetCapturedStdout(),
                "That player name not found\n");

    // remove first in list
    list.removePlayer("P1");
    EXPECT_EQ(list.head, p2);
    EXPECT_EQ(list.head->next, p3);
    EXPECT_EQ(list.head->last, p4);

    // remove player in middle
    list.removePlayer("P3");
    EXPECT_EQ(list.head->next, p4);
    EXPECT_EQ((list.head->next)->last, p2);

    // remove last in list
    list.removePlayer("P4");
    EXPECT_EQ(list.head->next, list.head);
    EXPECT_EQ(list.head->last, list.head);

    // make list completely empty
    list.removePlayer("P2");
    EXPECT_EQ(list.head, nullptr);

    // checks outList is receiving the removed players
    EXPECT_EQ(list.outList->head, p1);
    EXPECT_EQ(list.outList->head->next, p3);
    EXPECT_EQ(list.outList->head->next->next, p4);
    EXPECT_EQ(list.outList->head->next->next->next, p2);
    EXPECT_EQ(list.outList->head->last, p2);
}
