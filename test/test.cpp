#include "pch.h"
#include "../minesweeper/Minesweeper.h"

TEST(MinesweeperTest, ClassCreationTest) {
    Minesweeper game;
    EXPECT_TRUE(true);
}

TEST(MinesweeperTest, FieldHasSize) {
    Minesweeper game(10, 20);
    EXPECT_EQ(game.getWidth(), 10);
    EXPECT_EQ(game.getHeight(), 20);
}

TEST(MinesweeperTest, MinesCountTest) {
    Minesweeper game(10, 10, 15);
    EXPECT_EQ(game.getMinesCount(), 15);
}