// Include important libraries
#include <SFML/Graphics.hpp>

// Make code easier to type using namespace
using namespace sf;

// This is where our game starts from

int main()

{
    //Create a video mode object
    VideoMode vm(1920, 1080);
    
    //Create and open a window for thr game
    RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

    // Create texture to hold a graphic in GPU//

    Texture textureBackGround;

    textureBackGround.loadFromFile("graphics/background.png");

    // Create a sprite//

    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackGround);

    // Set the sprite background to cover the screen//
    
    spriteBackground.setPosition(0,0);

    while (window.isOpen())

    {

        /*

        ****************************************

        Handle the players input

        ****************************************

        */

        if (Keyboard::isKeyPressed(Keyboard::Escape))

        {

            window.close();
        }

        /*

        ****************************************

        Update the scene

        ****************************************

        */

        /*

        ****************************************

        Draw the scene

        ****************************************

        */

        // Clear everything from the last }

        /*

        ****************************************

        Update the scene

        ****************************************

        */

        /*

        ****************************************

        Draw the scene

        ****************************************

        
        */
         

        // Clear everything from the last frame

        window.clear();

        // Draw our game scene here

        window.draw(spriteBackground);

        // Show everything we just drew

        window.display();

    }

    return 0;

}
