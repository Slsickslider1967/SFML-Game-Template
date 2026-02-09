# SFML Game Template

A MonoGame-like game template built with SFML (Simple and Fast Multimedia Library) for C++. This template provides a structured framework for creating 2D games with a familiar game loop pattern.

## Features

- **MonoGame-inspired structure**: Familiar `Initialize()`, `LoadContent()`, `Update()`, `Draw()`, and `UnloadContent()` methods
- **Delta time support**: Frame-independent movement and timing
- **Organized input handling**: Dedicated `Input()` method for processing user input
- **Asset management**: Clear separation of resource loading and game logic
- **Audio support**: Built-in support for music and sound effects
- **Modern C++20**: Uses latest C++ features and best practices

## Project Structure

```
SFML Template/
├── Main.cpp          # Main game code with MonoGame-like structure
├── Makefile          # Build configuration
├── game              # Compiled executable
└── assets/           # (Create this) Place your game assets here
    ├── textures/     # Image files (.png, .jpg)
    ├── fonts/        # Font files (.ttf, .otf)
    ├── sounds/       # Sound effects (.wav, .ogg)
    └── music/        # Background music (.ogg, .mp3)
```

## Dependencies

### Required Libraries
- **SFML 3.x** (or compatible version)
  - sfml-graphics
  - sfml-window
  - sfml-system
  - sfml-audio

### Installation

**Arch Linux:**
```bash
sudo pacman -S sfml
```

**Ubuntu/Debian:**
```bash
sudo apt-get install libsfml-dev
```

**Fedora:**
```bash
sudo dnf install SFML-devel
```

**macOS (Homebrew):**
```bash
brew install sfml
```

## Building and Running

### Compile
```bash
make
```

### Run
```bash
make run
```

### Clean build files
```bash
make clean
```

## Game Structure

The template follows a MonoGame-like pattern with these core methods:

### `Initialize()`
Called once at startup. Initialize game state variables, set up game objects, and configure initial settings.

```cpp
void Initialize()
{
    // Set up game state
    // Initialize variables
    cout << "Game initialized!" << endl;
}
```

### `LoadContent()`
Load all game assets (textures, fonts, sounds, music). This is called after `Initialize()`.

```cpp
void LoadContent()
{
    // Load textures
    if (!_texture.loadFromFile("assets/player.png"))
        cerr << "Failed to load texture!" << endl;
    
    // Load fonts
    if (!_font.openFromFile("assets/font.ttf"))
        cerr << "Failed to load font!" << endl;
    
    // Create sprites and text using the loaded resources
    _sprite.emplace(_texture);
    _text.emplace(_font);
}
```

### `Update()`
Called every frame. Update game logic, handle physics, check collisions, and update entity states.

```cpp
void Update()
{
    _deltaTime = _deltaClock.restart();
    float dt = _deltaTime.asSeconds();
    
    // Update game objects
    // Handle physics
    // Check collisions
}
```

### `Input()`
Process user input events (keyboard, mouse, window events).

```cpp
void Input(const optional<Event>* event, RenderWindow& _window)
{
    if (const auto* keyPressed = (*event)->getIf<Event::KeyPressed>())
    {
        if (keyPressed->code == Keyboard::Key::Escape)
            _window.close();
    }
}
```

### `Draw()`
Render all game objects to the window.

```cpp
void Draw(RenderWindow& _window)
{
    _window.clear(Color::Black);
    
    // Draw sprites, text, shapes, etc.
    if (_sprite)
        _window.draw(*_sprite);
    
    _window.display();
}
```

### `UnloadContent()`
Clean up resources before the game exits.

```cpp
void UnloadContent()
{
    // Clean up dynamically allocated resources
    cout << "Game content unloaded!" << endl;
}
```

## Adding Game Content

### 1. Create Assets Directory
```bash
mkdir -p assets
```

### 2. Add Your Assets
Place your image files, fonts, sounds, and music in the `assets/` directory.

### 3. Declare Resources (Global Variables)
```cpp
// At the top of Main.cpp
Texture playerTexture;
optional<Sprite> playerSprite;
Font gameFont;
optional<Text> scoreText;
```

### 4. Load in LoadContent()
```cpp
void LoadContent()
{
    // Load texture
    if (!playerTexture.loadFromFile("assets/player.png"))
        cerr << "Failed to load player texture!" << endl;
    
    // Create sprite
    playerSprite.emplace(playerTexture);
    playerSprite->setPosition(Vector2f(100.f, 100.f));
    
    // Load font
    if (!gameFont.openFromFile("assets/font.ttf"))
        cerr << "Failed to load font!" << endl;
    
    // Create text
    scoreText.emplace(gameFont);
    scoreText->setString("Score: 0");
    scoreText->setCharacterSize(24);
}
```

### 5. Update in Update()
```cpp
void Update()
{
    _deltaTime = _deltaClock.restart();
    float dt = _deltaTime.asSeconds();
    
    // Move player with WASD
    Vector2f movement(0.f, 0.f);
    if (Keyboard::isKeyPressed(Keyboard::Key::W))
        movement.y -= 200.f * dt;
    if (Keyboard::isKeyPressed(Keyboard::Key::S))
        movement.y += 200.f * dt;
    if (Keyboard::isKeyPressed(Keyboard::Key::A))
        movement.x -= 200.f * dt;
    if (Keyboard::isKeyPressed(Keyboard::Key::D))
        movement.x += 200.f * dt;
    
    if (playerSprite)
        playerSprite->move(movement);
}
```

### 6. Draw in Draw()
```cpp
void Draw(RenderWindow& _window)
{
    _window.clear(Color::Black);
    
    if (playerSprite)
        _window.draw(*playerSprite);
    
    if (scoreText)
        _window.draw(*scoreText);
    
    _window.display();
}
```

## Configuration

### Window Settings
Modify these in `main()`:
```cpp
RenderWindow _window(VideoMode({1080, 720}), "Your Game Title");
_window.setFramerateLimit(60);
```

### Compiler Flags
Edit the Makefile to adjust:
- `CXXFLAGS`: Compiler flags (e.g., `-std=c++20 -Wall`)
- `LDFLAGS`: Linker flags for SFML libraries

## Tips

- **Use delta time** for frame-independent movement: `velocity * dt.asSeconds()`
- **Use `optional<>`** for objects that depend on resources (Sprite, Text, Sound)
- **Check asset loading**: Always verify that assets load successfully
- **Organize assets**: Keep assets organized in subdirectories
- **Separate concerns**: Keep game logic in `Update()`, rendering in `Draw()`

## Troubleshooting

### "undefined reference" errors
Make sure SFML libraries are properly linked in the Makefile.

### Assets not loading
- Check file paths are correct (relative to executable location)
- Verify assets exist in the `assets/` directory
- Check file permissions

### Compilation errors with Text/Sprite
SFML 3.x requires constructors with parameters. Use `optional<>` or pointers and initialize after loading resources.

## License

This template is provided as-is for educational and commercial use.

## Contributing

Feel free to fork this repository and customize it for your needs!

## Resources

- [SFML Documentation](https://www.sfml-dev.org/documentation/)
- [SFML Tutorials](https://www.sfml-dev.org/tutorials/)
- [MonoGame Documentation](https://docs.monogame.net/) (for comparison)
