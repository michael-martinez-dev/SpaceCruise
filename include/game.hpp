#ifndef GAME_HPP
#define GAME_HPP

#include "rocketship.hpp"
#include "star.hpp"
#include "spaceobject.hpp"
#include "eventlistener.hpp"
#include "event.hpp"

#include <vector>
#include <chrono>
#include <random>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>


class Game : public EventListener {
  private:
    sf::RenderWindow window;
    sf::Font font;
    std::unique_ptr<Rocketship> rocket;
    std::vector<sf::Text> preGameMsgs;
    std::vector<Star> stars;
    std::mt19937 rng;
    std::uniform_real_distribution<float> distX;
    std::uniform_real_distribution<float> distSpeed;
    std::vector<std::unique_ptr<SpaceObject>> spaceObjects;
    float timeSinceLastSpaceObject;
    float timeSinceLastFuelDecrease;
    bool rocketHit;
    bool play = true;
    bool quit = false;

    void initializePreGame(std::vector<std::string> preGameMsgs);
    void initializeStars();
    void update(float deltaTime);
    void renderPreGame();
    void render(std::chrono::steady_clock::time_point *lastFrameTime);
    void renderStars();
    void renderSpaceObjects();
    void renderStats();
    void renderPostGame();
    void handleEvents();
    void addRandomSpaceObject();
    bool shouldAddNewSpaceObject();

  public:
    Game();
    void init();
    void run();
    void onEvent(const Event& event) override;
};

#endif