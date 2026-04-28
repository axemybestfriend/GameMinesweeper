#pragma once
#include <vector>

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
        int placed = 0;
        for (int y = 0; y < height && placed < minesCount; ++y) {
            for (int x = 0; x < width && placed < minesCount; ++x) {
                field[y][x] = true;
                placed++;
            }
        }
    }

private:
    int width = 0;
    int height = 0;
    int minesCount = 0;
    std::vector<std::vector<bool>> field;
};