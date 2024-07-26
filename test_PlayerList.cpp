#include <gtest/gtest.h>
#include "PlayerList.h"
#include "Player.h"


TEST(test_addPlayer, firstInList) {
    PlayerList list;
    Player *p1 = new Player();
    list.addPlayer(*p1);


    // p1 is the list's head
    // & the next and last ptrs point to itself
    EXPECT_EQ(list.head, p1);

    // Player *p1Next = list.head->next;

    // EXPECT_EQ(p1Next, p1);
    // EXPECT_EQ(list.head.last, p1);
}

