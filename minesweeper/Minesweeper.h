#pragma once

class Minesweeper {
public:
    Minesweeper() {}
    Minesweeper(int w, int h) : width(w), height(h) {}
    Minesweeper(int w, int h, int mines) : width(w), height(h), minesCount(std::min(mines, w * h - 1)) {}
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getMinesCount() const { return minesCount; }

    bool isMine(int x, int y) const {
        return false;
    }

private:
    int width = 0;
    int height = 0;
    int minesCount = 0;
};