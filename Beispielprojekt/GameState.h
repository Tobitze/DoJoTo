#pragma once
#include "Spieler.h"

class GameState {
	Spieler* p1;
public:
	//static Spieler p1;
	Spieler* get_Spieler();

	struct Objekt_fest
	{
		double posx, posy, startx, starty, posz;
		double breite, hoehe, scale_x, scale_y;
		Objekt_fest* next;
		Gosu::Image* image;
	};
	Objekt_fest erstelle_Objekt_fest(double breite, double hoehe, double posx, double posy, double posz, Objekt_fest* next, Gosu::Image* image, double scale_x = 1, double scale_y = 1);
	struct Player_data
	{
		bool active;
		double breite, hoehe, scale_x, scale_y;
		Player_data* next;
		Gosu::Image* image;
	};
	Player_data erstelle_Player_data(double breite, double hoehe, Player_data* next, Gosu::Image* image, bool active, double scale_x = 1, double scale_y = 1);

	int health = 3;

	bool pressed = false;
	bool w_pressed = false;// player sprung
	bool a_pressed = false;// player links
	bool d_pressed = false;// player rechts

	Gosu::Image bodenR;
	Gosu::Image bodenL;
	Gosu::Image Wand;
	Gosu::Image hintergrund;
	Gosu::Image Kiste;
	Gosu::Image Plattform1;
	//HUD
	Gosu::Image hudHP;
	Gosu::Image hudHP2;
	Gosu::Image hudHP1;
	Gosu::Image hudHP0;
	Gosu::Image GameOver;
	//Player, temp
	Gosu::Image rPlayertemp1;
	Gosu::Image rPlayertemp2;
	Gosu::Image rPlayertempA1;
	Gosu::Image rPlayertempA2;
	Gosu::Image lPlayertemp1;
	Gosu::Image lPlayertemp2;
	Gosu::Image lPlayertempA1;
	Gosu::Image lPlayertempA2;

	//Game Window

	Objekt_fest ilistenproblenloeser;					 //Einfach nicht hinterfragen
	Objekt_fest ibodenR;
	Objekt_fest ibodenL;				 //Linked list über pointer
	Objekt_fest iKiste;
	Objekt_fest iPlattform1;
	Objekt_fest iWand;

	Objekt_fest* elem_O_f;
	Objekt_fest* listenstart_O_f; //Hier immer letztes Element hinschreiben

	//Liste für Player
	Player_data ilistenproblenloeserplayer;
	Player_data iplayertemp;

	Player_data* elem_P_d;
	Player_data* listenstart_P_d; //Hier immer letztes Element hinschreiben
	
	
	GameState();

	


#pragma region 1 //Kollsionskäse
	double distance_from_player(Objekt_fest* o2);
	bool kollision_rechts();
	bool kollision_links();
	bool kollision_oben();
	bool kollision_unten();
#pragma endregion	
};