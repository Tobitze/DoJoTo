#pragma once
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
	Spieler();

	// Beschleunigung in x-Richtung 
	double PlayerBeschleunigung(const double bx, double tx);

	// Sprung in y richtung
	double PlayerSprung(int t, const double MAX_H, double v, bool p);

	void reset();

};