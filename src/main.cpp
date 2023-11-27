#include "game.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <memory>

int main() {
  std::unique_ptr<Game> game = std::make_unique<Game>();
  game->init();
  game->run();
  
  return 0;
}
