#ifndef GAME_HPP
#define GAME_HPP
#include "rocketship.hpp"
#include "star.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vector>
#include <chrono>

class Game {
  private:
    sf::RenderWindow window;
    sf::Font font;
    std::unique_ptr<Rocketship> rocket;
    std::vector<sf::Text> initMsgs;
    std::vector<Star> stars;
    void initializeStars();
    void update(float deltaTime);
    void render(std::chrono::steady_clock::time_point *lastFrameTime);
  public:
    Game();
    void init();
    void run();
};

#endif