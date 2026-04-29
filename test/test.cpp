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

TEST(MinesweeperTest, MinesArePlacedCorrectly) {
    Minesweeper game(3, 3, 3);
    game.placeMines();

    int mineCount = 0;
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            if (game.isMine(x, y)) {
                mineCount++;
            }
        }
    }
    EXPECT_EQ(mineCount, 3);
}

TEST(MinesweeperTest, MinesArePlacedRandomly) {
    Minesweeper game1(5, 5, 5);
    Minesweeper game2(5, 5, 5);

    game1.placeMines();
    game2.placeMines();

    bool allSame = true;
    for (int y = 0; y < 5; ++y) {
        for (int x = 0; x < 5; ++x) {
            if (game1.isMine(x, y) != game2.isMine(x, y)) {
                allSame = false;
                break;
            }
        }
    }

    EXPECT_FALSE(allSame);
}

TEST(MinesweeperTest, CountNeighbourMinesTest) {
    Minesweeper game(3, 3, 1);
    game.setMineForTest(1, 1);

    EXPECT_EQ(game.countNeighbourMines(0, 0), 1);
    EXPECT_EQ(game.countNeighbourMines(1, 0), 1);
    EXPECT_EQ(game.countNeighbourMines(2, 0), 1);
    EXPECT_EQ(game.countNeighbourMines(0, 1), 1);
    EXPECT_EQ(game.countNeighbourMines(1, 1), -1);
    EXPECT_EQ(game.countNeighbourMines(2, 1), 1);
    EXPECT_EQ(game.countNeighbourMines(0, 2), 1);
    EXPECT_EQ(game.countNeighbourMines(1, 2), 1);
    EXPECT_EQ(game.countNeighbourMines(2, 2), 1);
}

TEST(MinesweeperTest, CellIsRevealedAfterCall) {
    Minesweeper game(3, 3, 0);
    game.reveal(1, 1);
    EXPECT_TRUE(game.isRevealed(1, 1));
}

TEST(MinesweeperTest, RevealMine) {
    Minesweeper game(3, 3, 1);
    game.setMineForTest(1, 1);
    bool result = game.reveal(1, 1);
    EXPECT_FALSE(result);
}