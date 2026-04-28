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

TEST(MinesweeperTest, MinesNotExceedTotalCells) {
    Minesweeper game(5, 5, 30);
    EXPECT_LE(game.getMinesCount(), 24);
}

TEST(MinesweeperTest, FieldCellsExist) {
    Minesweeper game(3, 3, 0);
    EXPECT_FALSE(game.isMine(0, 0));
    EXPECT_FALSE(game.isMine(1, 1));
    EXPECT_FALSE(game.isMine(2, 2));
}