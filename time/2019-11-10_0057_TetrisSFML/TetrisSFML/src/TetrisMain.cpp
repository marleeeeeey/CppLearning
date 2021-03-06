#define NOMINMAX
#include "Windows.h"
#include "Game.h"

int main()
{
    if constexpr (true) // set true to hide console
    {
        auto hwnd = GetConsoleWindow();
        ShowWindow(hwnd, SW_HIDE);
    }

    srand(time(NULL));
    sf::Vector2u size{14, 25};
    unsigned w = (size.x + 7) * Cell::getSize();
    unsigned h = (size.y + 1) * Cell::getSize();
    sf::RenderWindow window(sf::VideoMode(w, h), "Tetris");
    Game game(size);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed
                || isKeyPressed(event, sf::Keyboard::Escape))
            {
                window.close();
            }

            game.dispatchKey(event);
        }
        window.clear();
        game.draw(window);
        window.display();
    }

    return 0;
}
