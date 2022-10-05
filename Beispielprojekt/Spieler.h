#pragma once
class Spieler
{
public:

	double player_start_x = 300;
	double player_start_y = 456;

	double player_x;// Bewegung x-Achse
	double player_y;// Bewegung y-achse

	double speedPlayer = 0; // Gescchwindigkeit x-Richtung
	double heightPlayer = 0;// H�he y-Richtung

	int jumpTime; // z�hlt die zeit des sprungs
	int playerTimeXA; // zeit, die in x beschleunigt wird
	int playerTimeXD;

	//Konstruktor
	Spieler();

	// Beschleunigung in x-Richtung 
	double PlayerBeschleunigung(double bx, double tx);

	// Sprung in y richtung
	double PlayerSprung(int t, const double MAX_H, double v, bool p);

};
