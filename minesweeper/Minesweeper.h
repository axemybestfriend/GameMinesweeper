#pragma once
#include <vector>
#include <random>
#include <algorithm>

class Minesweeper {
public:
    Minesweeper() {}

    Minesweeper(int w, int h) : width(w), height(h) {
        field.assign(height, std::vector<bool>(width, false));
    }

    Minesweeper(int w, int h, int mines)
        : width(w), height(h), minesCount(std::min(mines, w* h - 1)) {
        field.assign(height, std::vector<bool>(width, false));
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

private:
    int width = 0;
    int height = 0;
    int minesCount = 0;
    std::vector<std::vector<bool>> field;
};