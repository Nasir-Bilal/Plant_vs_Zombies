# Plants vs Zombies Clone

**This project was developed as a group project.**

A C++14-based clone of the classic "Plants vs Zombies" game, built using [SFML](https://www.sfml-dev.org/) for graphics and input. The project is modular, with each file handling a specific aspect of the game, such as plants, zombies, levels, and the user interface.

---

## Project Structure

### Main Game Logic
- **main.cpp**  
  Entry point. Handles the main game loop, menus, and state transitions.
- **game.h**  
  Manages the overall game state, transitions, and main window.

### User Interface
- **mainMenu.h**  
  Implements the main menu UI and navigation.
- **LevelSelection.h**  
  Handles the level selection screen.

### Levels
- **Levels/levels.h**  
  Base class and logic for game levels.
- **Levels/level1.h**  
  Implementation for Level 1.
- **Levels/level2.h**  
  Implementation for Level 2.

### Plants
- **Plants/Plant.h**  
  Base class for all plant types.
- **Plants/Sunflower.h**  
  Sunflower plant logic (generates suns).
- **Plants/PeaShooter.h**  
  PeaShooter plant logic (shoots peas).
- **Plants/SnowPea.h**  
  SnowPea plant logic (shoots slowing peas).
- **Plants/Repeater.h**  
  Repeater plant logic (shoots double peas).
- **Plants/PlantFactory.h**  
  Factory for creating plant objects.

### Zombies
- **Zombies/zombies.h**  
  Base class for all zombie types.
- **Zombies/simpleZ.h**  
  Simple zombie logic.
- **Zombies/bucketZ.h**  
  Bucket zombie logic (more health).
- **Zombies/zombieFactory.h**  
  Factory for creating zombie objects.

### Elements (Projectiles, Suns, Shop)
- **Elements/Pea.h**  
  Logic for pea projectiles.
- **Elements/Suns.h**  
  Handles sun objects (collectible currency).
- **Elements/SunFactory.h**  
  Factory for generating suns.
- **Elements/Shop.h**  
  Shop logic for buying plants.
- **Elements/ShopPanel.h**  
  UI for the shop panel.

### Utilities
- **coordinates.h**  
  Utility struct/class for grid and screen coordinates.

### Source
- **Source.cpp**  
  (If present) May contain additional logic or be a placeholder for Visual Studio.

---

## Requirements

- C++14 compatible compiler (e.g., MSVC, g++, clang++)
- [SFML 2.x](https://www.sfml-dev.org/)
- Resource files (images, fonts) as referenced in the code (e.g., `Arial.ttf`, `gaming.jpg`, plant/zombie sprites)

---

## Building

1. Install SFML and set up your Visual Studio 2022 project to link against SFML.
2. Place all required resource files in the executable directory.
3. Open the solution in Visual Studio 2022.
4. Build and run the project.

---

## How to Play

- **Start the Game:** Launch the executable. Use the main menu to select a level.
- **Place Plants:** Use the shop to select and place plants on the grid.
- **Defend:** Prevent zombies from reaching the left side by strategically placing plants.
- **Progress:** Survive waves of zombies to complete levels.

---

## Notes

- Ensure all required images and fonts are present, or the game may not start.
- The project is for educational and demonstration purposes.

---

## License

This project is provided for educational use. See [SFML's license](https://www.sfml-dev.org/license.php) for details on the graphics library.

