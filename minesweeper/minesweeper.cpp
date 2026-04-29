#include <SFML/Graphics.hpp>
#include "Minesweeper.h"
#include <string>
#include <iostream>
#include <optional>

int main() {
    const int CELL_SIZE = 40;
    const int WIDTH = 9;
    const int HEIGHT = 9;
    const int MINES = 10;

    Minesweeper game(WIDTH, HEIGHT, MINES);
    game.placeMines();

    sf::RenderWindow window(
        sf::VideoMode({ WIDTH * CELL_SIZE, HEIGHT * CELL_SIZE + 50 }),
        "Minesweeper"
    );

    sf::Font font;

    std::vector<std::vector<bool>> flags(HEIGHT, std::vector<bool>(WIDTH, false));

    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* mousePressed =
                event->getIf<sf::Event::MouseButtonPressed>()) {

                int x = mousePressed->position.x / CELL_SIZE;
                int y = mousePressed->position.y / CELL_SIZE;

                if (x >= 0 && x < WIDTH &&
                    y >= 0 && y < HEIGHT &&
                    !game.isGameOver() &&
                    !game.isWin()) {

                    if (mousePressed->button == sf::Mouse::Button::Left) {
                        if (!flags[y][x])
                            game.reveal(x, y);
                    }
                    else if (mousePressed->button == sf::Mouse::Button::Right) {
                        if (!game.isRevealed(x, y))
                            flags[y][x] = !flags[y][x];
                    }
                }
            }

            if (const auto* keyPressed =
                event->getIf<sf::Event::KeyPressed>()) {

                if (keyPressed->code == sf::Keyboard::Key::R) {
                    game = Minesweeper(WIDTH, HEIGHT, MINES);
                    game.placeMines();
                    flags.assign(HEIGHT, std::vector<bool>(WIDTH, false));
                }
            }
        }

        window.clear(sf::Color::White);

        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {

                sf::RectangleShape cell(
                    sf::Vector2f(CELL_SIZE - 2.f, CELL_SIZE - 2.f));
                cell.setPosition(
                    sf::Vector2f(x * CELL_SIZE + 1.f,
                        y * CELL_SIZE + 1.f));

                if (game.isRevealed(x, y)) {
                    if (game.isMine(x, y))
                        cell.setFillColor(sf::Color::Red);
                    else
                        cell.setFillColor(sf::Color(200, 200, 200));
                }
                else {
                    cell.setFillColor(sf::Color(120, 120, 120));
                }

                window.draw(cell);

                if (!game.isRevealed(x, y) && flags[y][x]) {
                    sf::RectangleShape flag(
                        sf::Vector2f(CELL_SIZE - 10.f,
                            CELL_SIZE - 10.f));
                    flag.setPosition(
                        sf::Vector2f(x * CELL_SIZE + 5.f,
                            y * CELL_SIZE + 5.f));
                    flag.setFillColor(sf::Color::Green);
                    window.draw(flag);
                }

                if (game.isRevealed(x, y) && !game.isMine(x, y)) {
                    int cnt = game.countNeighbourMines(x, y);

                    if (cnt > 0) {
                        sf::Text text(font);
                        text.setString(std::to_string(cnt));
                        text.setCharacterSize(CELL_SIZE / 2);
                        text.setFillColor(sf::Color::Black);

                        float textX = x * CELL_SIZE + CELL_SIZE / 3.f;
                        float textY = y * CELL_SIZE + CELL_SIZE / 4.f;

                        text.setPosition({ textX, textY });
                        window.draw(text);
                    }
                }
            }
        }

        if (game.isWin()) {
            sf::Text winText(font);
            winText.setString("YOU WIN! Press R to restart");
            winText.setCharacterSize(20);
            winText.setFillColor(sf::Color::Blue);
            winText.setPosition({ 20.f, HEIGHT * CELL_SIZE + 10.f });
            window.draw(winText);
        }
        else if (game.isGameOver()) {
            sf::Text loseText(font);
            loseText.setString("GAME OVER! Press R to restart");
            loseText.setCharacterSize(20);
            loseText.setFillColor(sf::Color::Red);
            loseText.setPosition({ 20.f, HEIGHT * CELL_SIZE + 10.f });
            window.draw(loseText);
        }

        window.display();
    }

    return 0;
}