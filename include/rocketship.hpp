#ifndef ROCKETSHIP_H
#define ROCKETSHIP_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Rocketship {
    private:
      sf::RenderWindow *window;
      sf::Vector2f originalPosition;
      sf::Texture texture;
      sf::Sprite sprite;
      ushort shakeOn = 0;
      int shakeIntensity = 4;
    public:
        Rocketship(sf::RenderWindow *window);
        sf::Sprite getSprite();
        void turnLeft();
        void turnRight();
        void enableShake();
        void disableShake();
        void update();
        void noShake();
        void decreaseShake();
        void increaseShake();
        int getSpeed();
};

#endif
