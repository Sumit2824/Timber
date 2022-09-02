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

    //Make a tree sprite

    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);

    //Prepare the bee

    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);
    
    //Is the bee currently moving

    bool beeActive = false;
    
    //How fast can the bee fly

    float beeSpeed = 0.0f;

    //make three sprites from 1 texture

    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");
    Sprite spriteCloud1;
    Sprite spriteCloud2;
    Sprite spriteCloud3;
    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);
    spriteCloud1.setPosition(0, 0);
    spriteCloud2.setPosition(0,250);
    spriteCloud3.setPosition(0, 500);

    //Are clouds currently on screen?

    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;

    //How fast is each cloud?

    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;

    //Variable to control time itself

    Clock clock;

    //Track wheather the game is running

    bool paused = true;


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
        //Start the game
        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            paused = false;
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
        if (!paused)
        {

            //Measure time

            Time dt = clock.restart();

            //Setup bee

            if (!beeActive)
            {
                //How fast is the bee
                /*
                srand gives random values based on input int so input int
                need to be differant each time, so having time funtion means
                differant values each frame converted to int and generate
                random from sequence of differant number.
                */
                srand((int)time(0));
                beeSpeed = (rand() % 200) + 200;//speed = 200 - 399)

                //How high is the bee;

                srand((int)time(0) * 10);
                float height = (rand() % 500) + 500;
                spriteBee.setPosition(2000, height);
                beeActive = true;
            }
            else
                //Move bee
            {
                /*
                higher framerate ~ lower value of dt.asSeconds lower number subtracted
                lower framerate ~ higher value of dt.asSeconds higher number subtracted
                therefore net speed will appear the same
                */
                spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);

                //Has the bee reached the left-hand edge of the screen?
                if (spriteBee.getPosition().x < -100)
                {
                    //set it up ready to be a whole new bee

                    beeActive = false;
                }
            }

            //Manage clouds

            if (!cloud1Active)
            {
                //How fast is the cloud

                srand((int)time(0) * 10);
                cloud1Speed = (rand() % 200);

                //how high is the cloud 

                srand((int)time(0) * 10);
                float height = (rand() % 150);
                spriteCloud1.setPosition(-200, height);
                cloud1Active = true;
            }
            else
            {
                spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()), spriteCloud1.getPosition().y);
                if (spriteCloud1.getPosition().x > 1920)
                {
                    cloud1Active = false;
                }
            }
            if (!cloud2Active)
            {
                //How fast is the cloud

                srand((int)time(0) * 20);
                cloud2Speed = (rand() % 200);

                //how high is the cloud 

                srand((int)time(0) * 20);
                float height = (rand() % 300) - 150;
                spriteCloud2.setPosition(-200, height);
                cloud2Active = true;
            }
            else
            {
                spriteCloud2.setPosition(spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()), spriteCloud2.getPosition().y);
                if (spriteCloud2.getPosition().x > 1920)
                {
                    cloud2Active = false;
                }
            }
            if (!cloud3Active)
            {
                //How fast is the cloud

                srand((int)time(0) * 30);
                cloud3Speed = (rand() % 200);

                //how high is the cloud 

                srand((int)time(0) * 30);
                float height = (rand() % 450) - 150;
                spriteCloud3.setPosition(-200, height);
                cloud3Active = true;
            }
            else
            {
                spriteCloud3.setPosition(spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()), spriteCloud3.getPosition().y);
                if (spriteCloud3.getPosition().x > 1920)
                {
                    cloud3Active = false;
                }
            }
        }

        /*

        ****************************************

        Draw the scene

        ****************************************

        
        */
         

        // Clear everything from the last frame

        window.clear();

        // Draw our game scene here

        window.draw(spriteBackground);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        window.draw(spriteTree);
        window.draw(spriteBee);


        // Show everything we just drew

        window.display();

    }

    return 0;

}
