#pragma once
class Objekt_fest
{
	double breite, hoehe, posx, posy;
	//Gosu::Image bild;

public:
	Objekt_fest(double breite, double hoehe, double posx, double posy/*, Gosu::Image bild*/);

	void move_x(double deltax);
	void move_y(double deltay);
};