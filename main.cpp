#include <Graphics.hpp>
#include <random>
#include <cassert>
#include "Hero.h"
#include "Enemy.h"

constexpr unsigned ANTIALIASING_LEVEL = 8;
constexpr unsigned WINDOW_WIDTH = 1600;
constexpr unsigned WINDOW_HEIGHT = 900;
constexpr unsigned MAX_FPS = 60;
const unsigned SIDES_COUNT = 4;
const unsigned RIGHT_SIDE = 0;
const unsigned TOP_SIDE = 1;
const unsigned LEFT_SIDE = 2;
const unsigned BOTTOM_SIDE = 3;
const int RENDER_DISTANCE = 100;
const int RENDER_SPREAD_MULTIPLY = 5;
const std::string KNIGHT_PATH = "../images/heroes/Knight.png";
const std::string BOAR_PATH = "../images/enemies/Baton.png";

void createWindow(sf::RenderWindow& window);
void handleEvents(sf::RenderWindow& window);
void update(sf::Clock& clock, sf::CircleShape& shape);
void render(sf::RenderWindow& window, sf::CircleShape& shape);

struct PRNG
{
    std::mt19937 engine;
};

void initGenerator(PRNG& generator)
{
    std::random_device device;
    generator.engine.seed(device());
}

template<typename type>
type random(PRNG& generator, type minValue, type maxValue)
{
    assert(minValue <= maxValue);

    std::uniform_real_distribution<float> distribution(minValue, maxValue);

    return (type)distribution(generator.engine);
}

void generateEnemies(std::vector<Enemy>& enemies, int enemiesCount)
{
    PRNG generator;
    initGenerator(generator);
    for (int i = 0; i < enemiesCount; i++)
    {
        int side = (int)(i % SIDES_COUNT);
        if (side == RIGHT_SIDE)
        {
            enemies.push_back(Enemy(BOAR_PATH,{
                random<float>(generator, (float)(-RENDER_DISTANCE * RENDER_SPREAD_MULTIPLY), (float)(-RENDER_DISTANCE)),
                random<float>(generator, (float)(-RENDER_DISTANCE), (float)(WINDOW_HEIGHT + RENDER_DISTANCE)) }));
        }
        if (side == TOP_SIDE)
        {
            enemies.push_back(Enemy(BOAR_PATH,{
                random<float>(generator, (float)(-RENDER_DISTANCE), (float)(WINDOW_WIDTH + RENDER_DISTANCE)),
                random<float>(generator, (float)(-RENDER_DISTANCE * RENDER_SPREAD_MULTIPLY), (float)(-RENDER_DISTANCE)) }));
        }
        if (side == LEFT_SIDE)
        {
            enemies.push_back(Enemy(BOAR_PATH,{
                random<float>(generator, (float)(WINDOW_WIDTH + RENDER_DISTANCE), (float)(WINDOW_WIDTH + RENDER_DISTANCE * RENDER_SPREAD_MULTIPLY)),
                random<float>(generator, (float)(-RENDER_DISTANCE), (float)(WINDOW_HEIGHT + RENDER_DISTANCE)) }));
        }
        if (side == BOTTOM_SIDE)
        {
            enemies.push_back(Enemy(BOAR_PATH,{
                random<float>(generator, (float)(-RENDER_DISTANCE), (float)(WINDOW_WIDTH + RENDER_DISTANCE)),
                random<float>(generator, (float)(WINDOW_HEIGHT + RENDER_DISTANCE), (float)(WINDOW_HEIGHT + RENDER_DISTANCE * RENDER_SPREAD_MULTIPLY)) }));
        }
    }
}

void enemiesCollision(std::vector<Enemy> &enemies, float elapsedTime)
{
    for (int i = 0; i < enemies.size(); i++)
    {
        for (int j = 0; j < enemies.size(); j++)
        {
            if (i != j)
            {
                float topDelta = std::abs(enemies[i].getPosition().y - enemies[j].getPosition().y - enemies[j].getSize().y);
                float bottomDelta = std::abs(enemies[i].getPosition().y - enemies[j].getPosition().y + enemies[i].getSize().y);
                float leftDelta = std::abs(enemies[i].getPosition().x - enemies[j].getPosition().x - enemies[j].getSize().x);
                float rightDelta = std::abs(enemies[i].getPosition().x - enemies[j].getPosition().x + enemies[i].getSize().x);
                bool horizontalCollision = (enemies[j].getPosition().x <= enemies[i].getPosition().x && enemies[i].getPosition().x <= enemies[j].getPosition().x + enemies[j].getSize().x) || (enemies[j].getPosition().x <= enemies[i].getPosition().x && enemies[i].getPosition().x + enemies[i].getSize().x <= enemies[j].getPosition().x + enemies[j].getSize().x);
                bool verticalCollision = (enemies[j].getPosition().y <= enemies[i].getPosition().y && enemies[i].getPosition().y <= enemies[j].getPosition().y + enemies[j].getSize().y) || (enemies[j].getPosition().y <= enemies[i].getPosition().y && enemies[i].getPosition().y + enemies[i].getSize().y <= enemies[j].getPosition().y + enemies[j].getSize().y);
                bool topCollision = enemies[i].getPosition().y >= enemies[j].getPosition().y && enemies[i].getPosition().y <= enemies[j].getPosition().y + enemies[j].getSize().y + 2;
                bool bottomCollision = enemies[i].getPosition().y + enemies[i].getSize().y >= enemies[j].getPosition().y - 2 && enemies[i].getPosition().y + enemies[i].getSize().y <= enemies[j].getPosition().y + enemies[j].getSize().y;
                bool leftCollision = enemies[i].getPosition().x >= enemies[j].getPosition().x  && enemies[i].getPosition().x <= enemies[j].getPosition().x + enemies[j].getSize().x + 2;
                bool rightCollision = enemies[i].getPosition().x + enemies[i].getSize().x >= enemies[j].getPosition().x - 2 && enemies[i].getPosition().x + enemies[i].getSize().x <= enemies[j].getPosition().x + enemies[j].getSize().x;
                if (i != j)
                {
                    if (horizontalCollision && topCollision)
                    {
                        enemies[i].setPosition({ enemies[i].getPosition().x, enemies[i].getPosition().y + enemies[i].getSpeed() * elapsedTime });
                        enemies[j].setPosition({ enemies[j].getPosition().x, enemies[j].getPosition().y - enemies[j].getSpeed() * elapsedTime });

                    }
                    if (horizontalCollision && bottomCollision)
                    {
                        enemies[i].setPosition({ enemies[i].getPosition().x, enemies[i].getPosition().y - enemies[i].getSpeed() * elapsedTime });
                        enemies[j].setPosition({ enemies[j].getPosition().x, enemies[j].getPosition().y + enemies[j].getSpeed() * elapsedTime });
                    }
                    if (verticalCollision && leftCollision)
                    {
                        enemies[i].setPosition({ enemies[i].getPosition().x + enemies[i].getSpeed() * elapsedTime, enemies[i].getPosition().y });
                        enemies[j].setPosition({ enemies[j].getPosition().x - enemies[j].getSpeed() * elapsedTime, enemies[j].getPosition().y });
                    }
                    if (verticalCollision && rightCollision)
                    {
                        enemies[i].setPosition({ enemies[i].getPosition().x - enemies[i].getSpeed() * elapsedTime, enemies[i].getPosition().y });
                        enemies[j].setPosition({ enemies[j].getPosition().x + enemies[j].getSpeed() * elapsedTime, enemies[j].getPosition().y });
                    }
                }
            }
        }
    }
}

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

void update(sf::Clock& clock, Hero& hero, std::vector<Enemy>& enemies)
{
    const float elapsedTime = clock.restart().asSeconds();
    hero.update(elapsedTime);
    enemiesCollision(enemies, elapsedTime);
    for (Enemy& enemy : enemies)
    {
        enemy.move(elapsedTime, hero);
        enemy.update();
    }
}

void render(sf::RenderWindow& window, const Hero& hero, const std::vector<Enemy>& enemies)
{
    window.clear(sf::Color(0xFF, 0xF2, 0xCC));
    window.draw(hero);
    for (const Enemy& enemy : enemies)
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
    std::vector<Enemy> enemies;
    generateEnemies(enemies, 500);

    sf::Clock clock;
    while (window.isOpen())
    {
        handleEvents(window, knight);
        update(clock, knight, enemies);
        render(window, knight, enemies);
    }
}