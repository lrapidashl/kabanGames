#include <Graphics.hpp>
#include "Common/Random.h"
#include "Hero/Hero.h"
#include "Enemy/Enemies.h"
#include "Common/GameConsts.h"

void createWindow(sf::RenderWindow& window)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;
    window.create(
            sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
            "Kaban Survivors", sf::Style::Fullscreen, settings);
    window.setFramerateLimit(MAX_FPS);
}

void handleEvents(sf::RenderWindow& window, Hero& hero)
{
    sf::Event event{};
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::W)
            {
                hero.moveUp();
            }
            if (event.key.code == sf::Keyboard::S)
            {
                hero.moveDown();
            }
            if (event.key.code == sf::Keyboard::D)
            {
                hero.moveRight();
            }
            if (event.key.code == sf::Keyboard::A)
            {
                hero.moveLeft();
            }
        }
        if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            if (event.key.code == sf::Keyboard::W)
            {
                hero.stopUp();
            }
            if (event.key.code == sf::Keyboard::S)
            {
                hero.stopDown();
            }
            if (event.key.code == sf::Keyboard::D)
            {
                hero.stopRight();
            }
            if (event.key.code == sf::Keyboard::A)
            {
                hero.stopLeft();
            }
        }
    }
}

void update(sf::Clock& clock, Hero& hero, Enemies& enemies)
{
    const float elapsedTime = clock.restart().asSeconds();
    hero.move();
    hero.update();
    enemies.enemiesCollision(elapsedTime);
    enemies.move(elapsedTime, hero);
    enemies.update();
}

void render(sf::RenderWindow& window, const Hero& hero, Enemies& enemies)
{
    window.clear(sf::Color(0xFF, 0xF2, 0xCC));
    window.draw(hero);
    for (Enemy& enemy : enemies.getEnemies())
    {
        window.draw(enemy);
    }
    window.display();
}

int main()
{
    sf::RenderWindow window;
    createWindow(window);

    Hero knight(KNIGHT_PATH);
    knight.setPosition({ (float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT / 2 });
    Enemies enemies;
    enemies.add(BOAR_PATH, 100);

    sf::Clock clock;
    while (window.isOpen())
    {
        handleEvents(window, knight);
        update(clock, knight, enemies);
        render(window, knight, enemies);
    }
}