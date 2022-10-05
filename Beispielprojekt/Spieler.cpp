#include <math.h>
class Spieler 
{
public:

	double player_start_x = 300;
	double player_start_y = 456;

	double player_x;// Bewegung x-Achse
	double player_y;// Bewegung y-achse
	
	double speedPlayer = 0; // Gescchwindigkeit x-Richtung
	double speedPlayerY = 0; // Geschwindigkeit in y-Richtung
	double heightPlayer = 0;// Höhe y-Richtung

	int fallTime; //zählt die Fallzeit 
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
		double vx;
			vx = bx * (tx/5);
		return vx;
		//std::cout << ax << std::endl;
	};
	
	// Sprung in y richtung
	double PlayerSprung(int t, const double MAX_H, double v,bool p) {
		const double g = 9.81;
		double yt = (v * v)/ (2 * g) ;
		double gt = -((g*g)/(2*g));
		double tmax = v / g;
		
		if(t <= tmax) {
			return yt;
		}
		else {
			return gt;
		}
	};
};