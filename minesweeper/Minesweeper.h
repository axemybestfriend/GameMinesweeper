#pragma once

class Minesweeper {
public:
    Minesweeper() {}
    Minesweeper(int w, int h) : width(w), height(h) {}
    int getWidth() const { return width; }
    int getHeight() const { return height; }
private:
    int width = 0;
    int height = 0;
};