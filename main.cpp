#include <Graphics.hpp>
#include "Common/Random.h"
#include "Hero/Hero.h"
#include "Enemy/Enemies.h"
#include "Common/GameConsts.h"
#include "Weapon/Sword.h"
#include "Bow.h"
#include "Environments/Background.h"
#include "Experience.h"

void createWindow(sf::RenderWindow& window)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;
    window.create(
            sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
            "Kaban Survivors", sf::Style::Fullscreen, settings);
    window.setFramerateLimit(MAX_FPS);
    window.setMouseCursorVisible(false);
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

void update(sf::Clock& clock, Background& background, Experience& experience, Hero& hero, Enemies& enemies)
{
    const float elapsedTime = clock.restart().asSeconds();
    hero.move();
    hero.update();

    std::shared_ptr<Enemies> enemiesPtr = std::make_shared<Enemies>(enemies);
    hero.attack(elapsedTime, enemiesPtr, experience);
    hero.enemiesCollision(enemiesPtr);
    enemies.setEnemies(enemiesPtr->getEnemies());

    hero.experienceCollision(experience);

    background.move(elapsedTime, std::make_shared<Hero>(hero));
    background.update();

    experience.move(elapsedTime, std::make_shared<Hero>(hero));

    enemies.enemiesCollision(elapsedTime);
    enemies.move(elapsedTime, std::make_shared<Hero>(hero));
    enemies.update();
}

void render(sf::RenderWindow& window, Background& background, Experience& experience, const Hero& hero, Enemies& enemies)
{
    window.clear(sf::Color(0xFF, 0xF2, 0xCC));
    window.draw(background);
    window.draw(experience);
    window.draw(hero);
    for (Enemy& enemy : enemies.getEnemies())
    {
        window.draw(enemy);
    }
    for (const std::shared_ptr<Weapon>& weapon : hero.getWeapons())
    {
        window.draw(*weapon);
    }
    window.display();
}

int main()
{
    sf::RenderWindow window;
    createWindow(window);

    Background background(BACKGROUND_PATH);
    Experience experience(EXPERIENCE_PATH);

    Sword sword(SWORD_PATH, SWORD_AMMO_PATH);
    Bow bow(BOW_PATH, BOW_AMMO_PATH);

    Hero knight(KNIGHT_PATH, { (float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT / 2 }, std::make_shared<Sword>(sword));

    Enemies enemies;
    enemies.add(BOAR_PATH, 30);

    sf::Clock clock;
    while (window.isOpen())
    {
        handleEvents(window, knight);
        if (!knight.isDeath())
        {
            update(clock, background, experience, knight, enemies);
        }
        render(window, background, experience, knight, enemies);
    }
}