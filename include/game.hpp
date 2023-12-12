#ifndef GAME_HPP
#define GAME_HPP

#include "rocketship.hpp"
#include "star.hpp"
#include "spaceobject.hpp"
#include "eventlistener.hpp"
#include "event.hpp"

#include <SFML/Graphics/Color.hpp>
#include <memory>
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
    sf::Text *popupText = NULL;
    sf::Sprite *popupImage = NULL;
    float timeSinceLastSpaceObject;
    float timeSinceLastFuelDecrease;
    float timeSincePopupStart;
    int score;
    bool rocketHit;
    bool play = true;
    bool quit = false;
    bool displayPopupText = false;
    bool isPaused = false;

    void initializePreGame(std::vector<std::string> preGameMsgs);
    void initializeStars();
    void update(std::chrono::steady_clock::time_point *lastFrameTime);
    void renderPreGame();
    void render();
    void renderStars();
    void renderSpaceObjects();
    void renderStats();
    void renderPostGame();
    void handleEvents();
    void addRandomSpaceObject();
    bool shouldAddNewSpaceObject();
    void popup(std::string msg, sf::Color color, sf::Vector2f position);
    void popup(sf::Sprite sprite, sf::Color color, sf::Vector2f position);
    void togglePause() {this->isPaused = !this->isPaused;};

  public:
    Game();
    void init();
    void run();
    void onEvent(const Event& event) override;
    ~Game() {
      free(this->popupText);
      free(this->popupImage);
    };
};

#endif