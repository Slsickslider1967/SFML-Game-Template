#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;
using namespace std;

// Global variables for delta time
Clock _deltaClock;
Time _deltaTime;

//Game resources
Texture _texture;
Font _font;
SoundBuffer _soundBuffer;
optional<Sound> _sound;
optional<Sprite> _sprite;
optional<Text> _text;
Music _music;

void Initialize()
{
    /// <summary>
    /// Initializes game resources and states.
    /// Put your initialization code here.
    /// </summary>
    cout << "Game initialized!" << std::endl;
}

void LoadContent()
{
    /// <summary>
    /// Loads game assets such as textures, fonts, and sounds.
    /// Put your asset loading code here.
    /// </summary>

    if (!_texture.loadFromFile("assets/Laser_Cannon.png"))
        cerr << "Failed to load texture!" << std::endl;

    if (!_font.openFromFile("assets/arial.ttf"))
        cerr << "Failed to load font!" << std::endl;
    
    if (!_soundBuffer.loadFromFile("assets/laser_sound.wav"))
        cerr << "Failed to load sound!" << std::endl;
    
    if (!_music.openFromFile("assets/background_music.ogg"))
        cerr << "Failed to load music!" << std::endl;

    _sprite.emplace(_texture);
    _sprite->setPosition(Vector2f(100.f, 100.f));

    _text.emplace(_font);
    _text->setString("Hello, SFML!");
    _text->setCharacterSize(24);
    _text->setFillColor(Color::White);

    cout << "Game content loaded!" << std::endl;
}

void Update()
{
    /// <summary>
    /// Updates game logic and states.
    /// Put your game update code here.
    /// </summary>
    _deltaTime = _deltaClock.restart();
}

void Draw(RenderWindow& _window)
{
    /// <summary>
    /// Renders game objects to the window.
    /// Put your drawing code here.
    /// </summary>
    _window.clear(Color::Black);

    //Draw your game objects here
    if (_sprite)
        _window.draw(*_sprite);
    if (_text)
        _window.draw(*_text);

    _window.display();

}

void Input(const optional<Event>* event, RenderWindow& _window)
{
    /// <summary>
    /// Handles user input events.
    /// Put your input handling code here.
    /// </summary>
    if (const auto* keyPressed = (*event)->getIf<Event::KeyPressed>())
    {
        if (keyPressed->code == Keyboard::Key::Escape)
            _window.close();

        if (keyPressed->code == Keyboard::Key::Space)
            cout << "Space key pressed!" << std::endl;
    }
}

void UnloadContent()
{
    /// <summary>
    /// Unloads game assets and cleans up resources.
    /// Put your cleanup code here.
    /// </summary>
    cout << "Game content unloaded!" << std::endl;
}

int main()
{
    RenderWindow _window(VideoMode({1080, 720}), "SFML works!");
    _window.setFramerateLimit(60); 

    Initialize();
    LoadContent();

    while (_window.isOpen())
    {
        while (auto event = _window.pollEvent())
        {
            if (event->is<Event::Closed>())
                _window.close();
            
            Input(&event, _window);

        }

        Update();
        Draw(_window);
    }

    UnloadContent();
    return 0;
}

