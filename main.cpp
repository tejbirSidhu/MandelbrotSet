#include <ComplexPlane.h>
#include <SFML/Graphics/VertexArray.hpp>
#include <complex>
#include <iostream>
using namespace std;
using namespace sf;

int main()
{
    int height, width;
    width = VideoMode::getDesktopMode().width;
    height = VideoMode::getDesktopMode().height;

    Videomode vm = (width, height);
    RenderWindow window(vm, "Mandelbrot Set");
    ComplexPlane plane(width, height);
    Font font;

    if(!font.loadFromFile("batman.ttf"))
    {
        cout << "Error, couldn't open font file" << endl;
    }

    Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(Color::White);

    while (window.isOpen())
    {
        Event event;
        while(winodw.pollEvent(event))
        {
            if(event.type == Event::Closed)
            {
                window.close();
            }
            
            if(event.type == Event::MouseButtonPressed)
            {
                if(event.MouseButton.button == Mouse::Left)
                {
                    plane.zoomIn();
                    plane.setCenter(Vector2f(event.mouseButton.x, event.mouseButton.y));
                }
                else if(event.mouseButton.button == Mouse::Right)
                {
                    plane.zoomOut();
                    plane.setCenter(Vector2f(event.mouseButton.x,event.mouseButton.y));
                }
            }

            if(event.type == Event:: MouseMoved)
            {
                plane.setMouseLocation(Vector2f(event.mouseButton.x,event.mouseButton.y));
            }
            
            if(Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }
        }

        
    }

    return 0;

}