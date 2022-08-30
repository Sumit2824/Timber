#include <SFML/Graphics.hpp>
/*
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1920, 1080), "SFML works!", Style::Fullscreen);
    CircleShape shape(100.f);
    shape.setFillColor(Color::Green);

    // Create texture to hold a graphic in GPU//

    Texture textureBackGround;

    textureBackGround.loadFromFile("D:/VS Project/Timber/graphics/background.png");

    // Create a sprite//

    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackGround);

    // Set the sprite background to cover the screen//

    spriteBackground.setPosition(0,0);

    while (window.isOpen())
    {
        
        {
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }
                
        }

        window.clear();
        window.draw(spriteBackground);
        window.draw(shape);
        window.display();
    }

    return 0;
}
*/