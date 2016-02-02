
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"

int main(int, char const**)
{
    bool character_select_flag = false;
    bool fight_flag = false;
    sf::String character = "";
    
    sf::CircleShape shape(50);
    shape.setFillColor(sf::Color(100, 250, 50));
    shape.setPosition(80, 1030);
    
    sf::RectangleShape bach(sf::Vector2f(50, 50));
    bach.setFillColor(sf::Color(0, 250, 0));
    bach.setPosition(80, 1030);
    
    sf::RectangleShape opponent(sf::Vector2f(50,50));
    opponent.setFillColor(sf::Color(0, 0, 250));
    opponent.setPosition(1000, 1030);
    
    sf::Sprite ryu;
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1600, 1200), "SFML window");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "SFF_Start.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);
    
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("test", font, 50);
    text.setColor(sf::Color::Black);

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }

    // Play the music
    music.play();

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                // left mouse button is pressed: move to next screen
                
                character_select_flag = true;
                fight_flag = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                // space pressed: move to fight screen
                
                fight_flag = true;
                character_select_flag = false;
            }
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        // Clear screen
        window.clear();

        // Draw the bg
        if(fight_flag) texture.loadFromFile(resourcePath()+"cute_image.jpg");
        if(character_select_flag) texture.loadFromFile(resourcePath()+"character_select.jpg");
        window.draw(sprite);
        
        // Draw overlay
        
        if(character_select_flag){

            sf::Vector2f right(1350.0f,0.0f);
            
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                //shape.move(shape.getPosition() + right);
                shape.move(1350,0);
                if(shape.getPosition().x>=1600)     shape.setPosition(80, 1030);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
                character_select_flag = false;
                fight_flag = true;
                if(shape.getPosition().x == 80){
                    printf("bach");
                    character = "bach";
                }
                else if(shape.getPosition().x == 1430){
                    printf("chopin");
                    character = "chopin";
                }
            }
            
           window.draw(shape);
           window.draw(opponent);
        }
        
        if(fight_flag){
            sf::Vector2f right(10.0f,0.0f);
            if(character == "bach"){
                
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                    if(bach.getPosition().x+25==opponent.getPosition().x-25){
                        printf("collided");
                    }
                    else{
                        bach.move(10,0);
                    }
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                    bach.move(-10,0);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){

                }
                
                window.draw(bach);
                window.draw(opponent);
            }
            if(character == "chopin"){
                
                sf::CircleShape chopin(50);
                chopin.setFillColor(sf::Color(250, 0, 0));
                chopin.setPosition(80, 1030);
                window.draw(chopin);
                window.draw(opponent);
            }
        }

        // Draw the string
        window.draw(text);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
