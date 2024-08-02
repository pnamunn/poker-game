#include <gtest/gtest.h>
#include "PlayerList.h"
#include "Player.h"
#include <iostream>
using namespace std;

class AddPlayerTest : public testing::Test {
    protected:
        PlayerList list;
        Player player1,  *p1 = &player1;
        Player player2,  *p2 = &player2;
        Player player3,  *p3 = &player3;

        // /* Constructor */
        // AddPlayerTest() {
        //     // list.addPlayer(*p1);
        //     // list.addPlayer(*p2);
        //     // list.addPlayer(*p3);
        // }
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
    list.addPlayer(*p1);
    list.addPlayer(*p2);
    list.addPlayer(*p3);

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

