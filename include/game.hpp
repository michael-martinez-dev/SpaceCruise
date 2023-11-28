#ifndef GAME_HPP
#define GAME_HPP
#include "rocketship.hpp"
#include "star.hpp"
#include "spaceobject.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vector>
#include <chrono>
#include <random>

class Game {
  private:
    sf::RenderWindow window;
    sf::Font font;
    std::unique_ptr<Rocketship> rocket;
    std::vector<sf::Text> initMsgs;
    std::vector<Star> stars;
    std::mt19937 rng;
    std::uniform_real_distribution<float> distX;
    std::uniform_real_distribution<float> distSpeed;
    std::vector<std::unique_ptr<SpaceObject>> spaceObjects;

    void initializeStars();
    void update(float deltaTime);
    void render(std::chrono::steady_clock::time_point *lastFrameTime);
    void handleEvents();
    void addRandomSpaceObject();
    bool shouldAddNewSpaceObject();

  public:
    Game();
    void init();
    void run();
};

#endif