#include <SFML/Graphics.hpp>

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

#include <iostream>


int main()
{
    fs::path currentPath = fs::current_path();
    std::cerr << currentPath;
    auto window = sf::RenderWindow( {800U, 600U }, "Test Application");

    window.setFramerateLimit(70);
    auto clock = sf::Clock{};
    auto shape = sf::RectangleShape{ sf::Vector2f{ window.getSize() } };

    auto shader = sf::Shader{};
    if (!shader.loadFromFile("../../data/shader.frag", sf::Shader::Fragment))
    {
        std::cerr << "Couldn't load fragment shader\n";
        return -1;
    }

    auto mouse_position = sf::Vector2f{};


    sf::Texture texture;
    if (!texture.loadFromFile("../../data/bricks.png"))
    {
        // Обработка ошибки загрузки текстуры
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);



    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                mouse_position = window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
            }
        }

        shader.setUniform("u_resolution", sf::Glsl::Vec2{ window.getSize() });
        shader.setUniform("u_mouse", sf::Glsl::Vec2{ mouse_position });
        shader.setUniform("u_time", clock.getElapsedTime().asSeconds());
        // Привязка текстуры к шейдеру
        shader.setUniform("u_texture", texture);

        window.clear();
        window.draw(shape, &shader);
        window.display();
    }
}
