#ifndef Solar_System
#define Solar_System

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <memory>
#include <vector>

using namespace std;
using namespace sf;


class CelestialBody // Sun, Earth, Mars, Mercury, Venus are all celestial bodies
{
	public:
		CelestialBody();
		CelestialBody(double _x_pos, double _y_pos, double _x_vel, double _y_vel, double _mass, string _filename, double radius);
		void setRadius(double _radius);
		void loadImages(void);
		Sprite getSprite(void);
		double getForceX(shared_ptr<CelestialBody> body);
		double getForceY(shared_ptr<CelestialBody> body);
		void setForceX(double Fx);
		void setForceY(double Fy);
		void calculateAccelleration(void);
		void calculateVelocity(double delta_t);
		void calculatePosition(double delta_t);
		friend istream& operator >> (istream &in, shared_ptr<CelestialBody> body); // overloaded insertion and extraction operator
		friend ostream& operator << (ostream &out, shared_ptr<CelestialBody> body);
	private:
		double x_pos; // (x,y) coordinates of position
		double y_pos;
		double x_vel; // (x,y) coordinates of velocity
		double y_vel;
		double mass;  // Mass of Celestial Body
		double radius; // radius of Universe
		double ForceX; //Force in the x direction
		double ForceY; //Force in the Y direction
		double ax; // (x,y) coordinates of acceleration
		double ay; 
		string filename;
		Texture texture;
		Sprite sprite; 
};

class Universe
{
	public:
		Universe(int size);
		void step(double delta_t);
		void update(void);
		vector<shared_ptr<CelestialBody>> bodies; // array of pointers to CelestialBody objects
};


#endif
