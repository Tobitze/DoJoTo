#include <math.h>
class Spieler 
{
public:

	double player_start_x = 300;
	double player_start_y = 456;

	double player_x;// Bewegung x-Achse
	double player_y;// Bewegung y-achse
	
	double speedPlayer = 0; // Gescchwindigkeit x-Richtung
	double heightPlayer = 0;// Höhe y-Richtung

	int jumpTime; // zählt die zeit des sprungs
	int playerTimeXA; // zeit, die in x beschleunigt wird
	int playerTimeXD;
	
	//Konstruktor
	Spieler(){
		this->player_x = player_start_x;
		this->player_y = player_start_y;
	}
		
	// Beschleunigung in x-Richtung 
	double PlayerBeschleunigung(double bx,double tx) {
		double ax;
			ax = bx * (tx/5);
		return ax;
		//std::cout << ax << std::endl;
	};
	
	// Sprung in y richtung
	double PlayerSprung(int t, const double MAX_H, double v,bool p) {
		const double g = 9.81;
		double yt = t * v;
		double gt = -g * 0.1 * t;
		
		if ((yt < MAX_H)&&(p = true)) {
			return yt;
		}
		else if ((yt >= MAX_H)&&(p = true)) {
			return gt;
		}
		else if ((yt < MAX_H)&&(p = false)) {
			return gt;
		}
		else if ((yt >= MAX_H) && (p = false)) {
			return gt;
		}
			
	};
};