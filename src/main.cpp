#include <string>
#include <iostream>
#include <iostream>
#include <string> 
#include <memory>
#include <vector>
#include <math.h>
#include "CelestialBody.hpp"

using namespace std;
using namespace sf; 

int main(int argc, char** argv)
{

	double total_t = stod(argv[1]); //total time
	double delta_t = stod(argv[2]); // delta t is the rate at which time changes during each step of the simulation
	double time_elapsed = 0.0;
	
	int size; //number of celestial bodies in Universe
	double radius; // radius of universe

	cin >> size >> radius;
	cout << size << endl << radius << endl << total_t << endl << delta_t << endl;

	Universe universe(size);
	
	for (int i = 0; i < size; i++)
	{
		cin >> universe.bodies[i];
		universe.bodies[i]->setRadius(radius);
		universe.bodies[i]->loadImages();
	}

	RenderWindow window(VideoMode(900,900), "Solar System");
	
	Texture BackgroundTexture; // scaling background to fit window
        Sprite Background;
        Vector2u TextureSize;
        Vector2u WindowSize;

	if (!BackgroundTexture.loadFromFile("data/sf.jpeg"))
			return -1;

	TextureSize = BackgroundTexture.getSize();
	WindowSize = window.getSize();

	float ScaleX = static_cast<float>(WindowSize.x) / TextureSize.x;
	float ScaleY = static_cast<float>(WindowSize.y) / TextureSize.y;

	Background.setTexture(BackgroundTexture);
	Background.setScale(ScaleX, ScaleY);
	
	while (window.isOpen())
	{
		for (time_elapsed = 0; time_elapsed <= total_t; time_elapsed += delta_t)
		{
			Event event;
                	while (window.pollEvent(event))
                	{
                    		if (event.type == Event::Closed)
                        	{
					window.close();
                        		return 1;
				}
			}

                	window.clear(Color::Black);
                	window.draw(Background);
                	for (int i = 0; i < size; i++)
                	{
                        	window.draw(universe.bodies[i]->getSprite());
				cout << universe.bodies[i] << endl;
                	}
                	window.display();
			universe.step(delta_t);
		}
	}

	return 0;
}
