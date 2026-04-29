#pragma once
#include <vector>
#include <random>
#include <algorithm>

class Minesweeper {
public:
    Minesweeper() {}

    Minesweeper(int w, int h) : width(w), height(h) {
        field.assign(height, std::vector<bool>(width, false));
        revealed.assign(height, std::vector<bool>(width, false));
    }

    Minesweeper(int w, int h, int mines)
        : width(w), height(h), minesCount(std::min(mines, w* h - 1)), gameOver(false) {
        field.assign(height, std::vector<bool>(width, false));
        revealed.assign(height, std::vector<bool>(width, false));
        totalSafeCells = width * height - minesCount;
        safeRevealedCount = 0;
    }

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getMinesCount() const { return minesCount; }

    bool isMine(int x, int y) const {
        return field[y][x];
    }

    void placeMines() {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                field[y][x] = false;
            }
        }

        int totalCells = width * height;
        std::vector<int> indices(totalCells);
        for (int i = 0; i < totalCells; ++i) {
            indices[i] = i;
        }

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(indices.begin(), indices.end(), g);

        for (int i = 0; i < minesCount; ++i) {
            int pos = indices[i];
            int x = pos % width;
            int y = pos / width;
            field[y][x] = true;
        }
    }

    void setMineForTest(int x, int y) {
        field[y][x] = true;
    }

    int countNeighbourMines(int x, int y) const {
        if (isMine(x, y)) {
            return -1;  
        }

        int count = 0;
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                if (dx == 0 && dy == 0) continue;

                int nx = x + dx;
                int ny = y + dy;

                if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                    if (field[ny][nx]) {
                        count++;
                    }
                }
            }
        }
        return count;
    }

    bool reveal(int x, int y) {
        if (gameOver) {
            return false;
        }

        if (x < 0 || x >= width || y < 0 || y >= height) {
            return true;
        }

        if (revealed[y][x]) {
            return true; 
        }

        if (field[y][x]) {
            gameOver = true;
            return false; 
        }

        revealed[y][x] = true;
        safeRevealedCount++;

        if (countNeighbourMines(x, y) == 0) {
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    if (dx == 0 && dy == 0) continue;
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        reveal(nx, ny);
                    }
                }
            }
        }

        return true;
    }

    bool isRevealed(int x, int y) const {
        return revealed[y][x];
    }

    bool isWin() const {
        return safeRevealedCount == totalSafeCells;
    }

    bool isGameOver() const { return gameOver; }

private:
    int width = 0;
    int height = 0;
    int minesCount = 0;
    int safeRevealedCount = 0;
    int totalSafeCells = 0;
    bool gameOver = false;
    std::vector<std::vector<bool>> field;
    std::vector<std::vector<bool>> revealed;
};