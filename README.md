# Space Cruise

Space Cruise is an immersive, space-themed 2D game where players navigate a spacecraft through an endlessly evolving universe. Set against a backdrop of procedurally generated star systems and cosmic challenges, the game combines elements of exploration, strategy, and skillful navigation.

## Key Features

- **Endless Space Exploration:** Discover new star systems and navigate through unique obstacles in a procedurally generated universe.
- **Resource Management:** Collect fuel and materials from planets critical for survival.
- **Dynamic Challenges:** Face unexpected space phenomena like asteroids, black holes, and more.

## Installation

### Prerequisites

- SFML (Simple and Fast Multimedia Library)
- A C++17 compatible compiler
- CMake (optional, for build automation)

### Building the Game

1. **Clone the Repository:**
```
git clone https://github.com/michael-martinez-dev/SpaceCruiser.git
cd SpaceCruiser
```


2. **Compile the Source Code:**
- **With CMake:**
  ```
  cmake .
  make
  ```
- **Manual Compilation:**
  ```
  g++ -o SpaceCruiser src/*.cpp -lsfml-graphics -lsfml-window -lsfml-system -Iinclude
  ```

3. **Run the Game:**
```
./location/of/project/bin/<version>/SpaceCruiser
```

## Controls

- **Left Arrow Key:** Rotate the spacecraft counter-clockwise.
- **Right Arrow Key:** Rotate the spacecraft clockwise.
- **Up Arrow Key:** Speed up
- **Down Arrow Key:** Slow Down

## Contributing

Contributions to Space Cruiser are warmly welcomed. Feel free to report bugs, discuss new features, or submit pull requests. Every contribution is valued and helps improve the game.

## License

Space Cruiser is open source and licensed under the [MIT License](LICENSE).

## Acknowledgments

- Thanks to the SFML team for providing an excellent graphics library.
- icons by [Icons8](icons.com)
