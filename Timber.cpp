// Include important libraries
#include <sstream>
#include <SFML/Graphics.hpp>

// Make code easier to type using namespace
using namespace sf;

//Function declaration
// void -> signature, updateBranches -> function prototype, int -> argument 

void updateBranches(int seed);  
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

//Where is the player/Branch - Left or Right

enum class side
{
    LEFT, RIGHT, NONE
};

side branchPositions[NUM_BRANCHES];

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

    spriteBackground.setPosition(0, 0);

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
    spriteCloud2.setPosition(0, 250);
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

    //Time bar

    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);
    Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    //Track wheather the game is running

    bool paused = true;

    //Draw some text
    int score = 0;
    Text messageText;
    Text scoreText;

    //We need to choose a font

    Font font;
    font.loadFromFile("fonts/KOMIKAGL.ttf");

    //Set the font to our message

    messageText.setFont(font);
    scoreText.setFont(font);

    //assign the actual message

    messageText.setString("Press Enter to start");
    scoreText.setString("Score = 0");

    //change text size

    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);

    //choose a color

    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);

    //Position the text

    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
    scoreText.setPosition(20, 20);

    //Prepare 6 branches
    Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");

    //set the texture for each branch sprite

    for (int i = 0; i < NUM_BRANCHES; i++)
    {
        branches[i].setTexture(textureBranch);
        branches[i].setPosition(-2000, -2000);

        //set the sprite origin to be dead center
        //we can then spin it around without changing its position

        branches[i].setOrigin(220, 20);
    }

    //preapare the player
    Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(580, 720);
    side playerSide = side::LEFT;   //player start from left

    //prepare the gravestone

    Texture textureRIP;
    textureRIP.loadFromFile("graphics/rip.png");
    Sprite spriteRIP;
    spriteRIP.setTexture(textureRIP);
    spriteRIP.setPosition(600, 860);

    //prepare the axe

    Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition(700, 830);

    //line the axe up with the tree

    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;

    //prepare the flying log

    Texture textureLog;
    textureLog.loadFromFile("graphics/log.png");
    Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition(810, 720);

    //some other log related variable

    bool logActibve = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;

    //control player input
    bool acceptInput = false;


    while (window.isOpen())

    {

        /*

        ****************************************

        Handle the players input

        ****************************************

        */
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased && !paused)
            {
                // listen the key press again
                acceptInput = true;

                //hide the axe
                spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))

        {

            window.close();
        }
        //Start the game
        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            paused = false;

            // Reset the time and score

            score = 0;
            timeRemaining = 6;

            // make all branches disappear
            //starting in the second position

            for (int i = 0; i < NUM_BRANCHES; i++)
            {
                branchPositions[i] = side::NONE;
            }
            //make sure grave stone is hidden

            spriteRIP.setPosition(675, 2000);

            //move player into position

            spritePlayer.setPosition(580, 720);
            acceptInput = true;
        }
        //warp player control to make sure we are accepting inputs

        if (acceptInput)
        {
            //first handle the right cursor key
            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                //make sure player is on the right 

                playerSide = side::RIGHT;
                score++;

                //add the amount of time remaining

                timeRemaining += (2 / score) + .15;
                spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
                spritePlayer.setPosition(1200, 720);

                //upsate the branches
                updateBranches(score);

                //set log flying to the left

                spriteLog.setPosition(810, 720);
                logSpeedX = -5000;
                logActibve = true;
                acceptInput = false;
            }

            //handle left cursor key
            if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                //make sure player is on the right 

                playerSide = side::LEFT;
                score++;

                //add the amount of time remaining

                timeRemaining += (2 / score) + .15;
                spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
                spritePlayer.setPosition(580, 720);

                //upsate the branches
                updateBranches(score);

                //set log flying to the left

                spriteLog.setPosition(810, 720);
                logSpeedX = 5000;
                logActibve = true;
                acceptInput = false;
            }
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

                //subtract from the amount of time remainng 

                timeRemaining -= dt.asSeconds();

                //size up the time bar

                timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

                if (timeRemaining <= 0.0f)
                {
                    //Pause the game

                    paused = true;

                    //change message shown to the player

                    messageText.setString("Out of time!!");

                    //reposition the text based on its new size

                    FloatRect textRect = messageText.getLocalBounds();
                    messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
                }

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
                    // bee speed * time(sec) = distance(pixels)

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

                //Update the score text

                std::stringstream ss;
                ss << "Score = " << score;
                scoreText.setString(ss.str());

                //update branch sprites

                for (int i = 0; i < NUM_BRANCHES; i++)
                {
                    float height = i * 150;
                    if (branchPositions[i] == side::LEFT)
                    {
                        //move the sprite to the left side
                        branches[i].setPosition(610, height);

                        //flip the sprite round the other way
                        branches[i].setRotation(180);
                    }
                    else if (branchPositions[i] == side::RIGHT)
                    {
                        //move the sprite to the right side
                        branches[i].setPosition(1330, height);

                        //set sprite rotation to normal
                        branches[i].setRotation(0);
                    }
                    else
                    {
                        //hide the branch
                        branches[i].setPosition(3000, height);
                    }
                }
            }//end if paused

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
            for (int i = 0; i < NUM_BRANCHES; i++)
            {
                window.draw(branches[i]);
            }
            window.draw(spriteTree);
            window.draw(spritePlayer);
            window.draw(spriteAxe);
            window.draw(spriteLog);
            window.draw(spriteRIP);
            window.draw(spriteBee);
            window.draw(scoreText);
            window.draw(timeBar);

            if (paused)
            {
                window.draw(messageText);
            }


            // Show everything we just drew

            window.display();

        }

        return 0;

    }

    // Function definatiom

    void updateBranches(int seed)
    {
        // move all the branches down one place
        for (int j = NUM_BRANCHES - 1; j > 0; j--)
        {
            branchPositions[j] = branchPositions[j - 1];
        }
        //spawn a new branch at position 0
        // left, right, or none
        srand((int)time(0) + seed);
        int r = (rand() % 5);
        switch (r)
        {
        case 0:
            branchPositions[0] = side::LEFT;
            break;
        case 1:
            branchPositions[0] = side::RIGHT;
            break;
        default:
            branchPositions[0] = side::NONE;
            break;
        }
    }
