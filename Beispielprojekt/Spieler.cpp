#include <math.h>
class Spieler // Doris ding Anfang :D
{
public:

	double player_start_x = 300;
	double player_start_y = 456;

	double player_x;// Bewegung x-Achse
	double player_y;// Bewegung y-achse
	
	//double player_a_x;// Geschwindigkeit x-richtung
	double speedPlayer = 0;
	
	double player_a_y;// Geschwindigkeit y-richtung
	
	
	const double player_g = 9.81;// gravitationskonstante


	int sprung_t; // zählt die zeit des sprungs
	int player_t_x_a; // zeit, die in x beschleunigt wird
	int player_t_x_d;
	
	//Konstruktor
	Spieler(){
		this->player_x = player_start_x;
		this->player_y = player_start_y;
	}
		//player Bewegung
		// bewegung in x richtung 
	
	
	double player_beschleunigung(double bx,double tx) {
		double ax;
			ax = bx * (tx/5);
		return ax;
		//std::cout << ax << std::endl;
	};

	// sprung timer - zählt, wie lange der player springt.
	int sprung_dauer(bool y) {
		while (y = true) {
			switch (y) {
			case true:
				return this->sprung_t = this->sprung_t + 1;;
				break;
			case false:
				return this->sprung_t = 0;
				break;
			default:
				break;
			};

		}
	};
	// bewegug in y richtung
	double player_sprung_y(double v,double y,double t) {
		double yt;
		yt = (-0.5 * 9, 81 * t * t) + (v * t) + y;
			return yt;
	};
}; // Doris ding ende :D