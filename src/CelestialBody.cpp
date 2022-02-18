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

double height = 900;
double width = 900;

CelestialBody::CelestialBody()
{
	//default constructor
}
CelestialBody::CelestialBody(double _x_pos, double _y_pos, double _x_vel, double _y_vel, double _mass, string _filename, double _radius)
{
	x_pos = _x_pos;
	y_pos = _y_pos;
	x_vel = _x_vel;
	y_vel = _y_vel;
	mass = _mass;
	filename = _filename;

	radius = _radius;
	double scale_x_pos = ((x_pos/radius) * (width/2)) + (width/2); //Scaling universe to given radius from file
	double scale_y_pos = ((y_pos/radius) * (height/2)) + (height/2); 
	
	Image image;
        image.loadFromFile(filename);
        texture.loadFromImage(image);
        sprite = Sprite(texture);
        sprite.setPosition(scale_x_pos, scale_y_pos);
	
}
void CelestialBody::setRadius(double _radius)
{
	radius = _radius;
}
void CelestialBody::loadImages(void)
{
	Image image;
	image.loadFromFile(filename);
    	texture.loadFromImage(image);
    	sprite = Sprite(texture);
	double scale_x_pos = ((x_pos/radius) * (width/2)) + (width/2); //Scaling universe to given radius from file
	double scale_y_pos = ((y_pos/radius) * (height/2)) + (height/2); 
	sprite.setPosition(scale_x_pos, scale_y_pos);
}
void Universe::step(double delta_t)
{
	
	double ForceX;
	double ForceY;

	for (auto itr1 = bodies.begin(); itr1 != bodies.end(); itr1++) //iterate through array of CelestialBodys, calculate net force being exerted on each body by all other bodies in Universe
	{
		ForceX = 0.0;
		ForceY = 0.0;

		for (auto itr2 = bodies.begin(); itr2!= bodies.end(); itr2++)
		{
			
			if (itr1 != itr2)
			{
				ForceX += (*itr1)->getForceX(*itr2);
				ForceY += (*itr1)->getForceY(*itr2);
			}
		}
		(*itr1)->setForceX(ForceX);
		(*itr1)->setForceY(ForceY);
	}
	for (auto a = bodies.begin(); a != bodies.end(); a++) // Once net force is calculated, we can use this to calculate new acceleration, new velocity, and new position for each body
	{
		(*a)->calculateAccelleration();
		(*a)->calculateVelocity(delta_t);
		(*a)->calculatePosition(delta_t);
	}
}
double CelestialBody::getForceX(shared_ptr<CelestialBody> body) // Calculate Force in X direction
{
	double G = 6.67 / 1e11; // Universal Gravitational Constant
	double delta_x = body->x_pos - this->x_pos;
	double delta_y = body->y_pos - this->y_pos;
	
	double distance = sqrt( (delta_x * delta_x) + (delta_y * delta_y) );
	double Force = (G * mass * body->mass) / (distance * distance);
	double Fx = Force * (delta_x / distance);
//	double Fy = Force * (delta_y / distance);
	return Fx;
}
double CelestialBody::getForceY(shared_ptr<CelestialBody> body) // Calculate Force in Y direction
{
	double G = 6.67 / 1e11; // Universal Gravitational Constant
	double delta_x = body->x_pos - this->x_pos;
	double delta_y = body->y_pos - this->y_pos;

	double distance = sqrt( (delta_x * delta_x) + (delta_y * delta_y) );
	double Force = (G * mass * body->mass) / (distance * distance);
//	double Fx = Force * (delta_x / distance);
	double Fy = Force * (delta_y / distance);
	return Fy;
}
void CelestialBody::calculateAccelleration(void)
{
	ax = ForceX/mass;
	ay = ForceY/mass;
}
void CelestialBody::calculateVelocity(double delta_t)
{
	x_vel = x_vel + (delta_t * ax);
	y_vel = y_vel + (delta_t * ay);
}
void CelestialBody::calculatePosition(double delta_t)
{
	x_pos = x_pos + (delta_t * x_vel); 
	y_pos = y_pos + (delta_t * y_vel);
	
	double scale_x_pos = ((x_pos/radius) * (width/2)) + (width/2); //Scaling universe to given radius from file
	double scale_y_pos = ((y_pos/radius) * (height/2)) + (height/2); 
	sprite.setPosition(scale_x_pos,scale_y_pos);
}
void CelestialBody::setForceX(double Fx)
{
	this->ForceX = Fx;
}
void CelestialBody::setForceY(double Fy)
{
	this->ForceY = Fy;
}
Sprite CelestialBody::getSprite(void)
{
	return sprite;
}
istream& operator >> (istream& in, shared_ptr<CelestialBody> body) //overloaded insertion and extraction operators
{
	in >> body->x_pos >> body->y_pos >> body->x_vel >> body->y_vel >> body->mass >> body->filename;
	body->x_pos = body->x_pos * -1;
	return in;
}
ostream& operator << (ostream &out, shared_ptr<CelestialBody> body)
{
	out << body->x_pos << "   " << body->y_pos << "   " << body->x_vel << "   " << body->y_vel << "   " << body->mass << "   " << body->filename << endl;
	return out;
}
Universe::Universe(int size)
{
	for (int i = 0; i < size; i++)
	{
		bodies.push_back(shared_ptr<CelestialBody>(new CelestialBody)); // Init vector of pointers to CelestialBody objects
	}
}

