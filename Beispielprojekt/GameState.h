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
		std::shared_ptr<Objekt_fest> next;
		std::shared_ptr<Gosu::Image> image;
		//Objekt_fest* next;
		//Gosu::Image* image;
	};
	std::shared_ptr<Objekt_fest> erstelle_Objekt_fest_ptr(double breite, double hoehe, double posx, double posy, double posz, std::shared_ptr<Objekt_fest> next, std::shared_ptr<Gosu::Image> image, double scale_x = 1, double scale_y = 1);
	struct Player_data
	{
		bool active;
		double breite, hoehe, scale_x, scale_y;
		std::shared_ptr<Player_data> next;
		std::shared_ptr<Gosu::Image> image;
	};
	std::shared_ptr<Player_data> erstelle_Player_data_ptr(double breite, double hoehe, std::shared_ptr<Player_data> next, std::shared_ptr<Gosu::Image> image, bool active, double scale_x = 1, double scale_y = 1);


	int z = 50; //zähler für spieleranimation
	int health = 3;

	bool facing_r = false; //standardwert true, hier aber zu testzwecken false :D später soll der bool je nach tastendruck gesetzt werden

	bool pressed = false;
	bool w_pressed = false;// player sprung
	bool a_pressed = false;// player links
	bool d_pressed = false;// player rechts

	Gosu::Image bodenR;
	Gosu::Image bodenL;
	Gosu::Image Wand;
	Gosu::Image Wand_r1; 
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

	std::shared_ptr<Objekt_fest> ilistenproblenloeser;					 //Einfach nicht hinterfragen
	std::shared_ptr<Objekt_fest> ibodenR;
	std::shared_ptr<Objekt_fest> ibodenL;				 //Linked list über pointer
	std::shared_ptr<Objekt_fest> iKiste;
	std::shared_ptr<Objekt_fest> iPlattform1;
	std::shared_ptr<Objekt_fest> iWand_r1;
	std::shared_ptr<Objekt_fest> iWand;

	std::shared_ptr<Objekt_fest> elem_O_f;
	std::shared_ptr<Objekt_fest> listenstart_O_f; //Hier immer letztes Element hinschreiben

	//Liste für Player
	std::shared_ptr<Player_data> ilistenproblenloeserplayer;
	std::shared_ptr<Player_data> iplayertemp;
	std::shared_ptr<Player_data>	iplayertemp2;
	std::shared_ptr<Player_data>	iplayertempl1;
	std::shared_ptr<Player_data> iplayertempl2;

	std::shared_ptr<Player_data> elem_P_d;
	std::shared_ptr<Player_data> listenstart_P_d; //Hier immer letztes Element hinschreiben
	
	std::shared_ptr<GameState::Objekt_fest> get_listenstart_O_f();
	std::shared_ptr<GameState::Player_data> get_listenstart_P_d();


	GameState();


	


#pragma region 1 //Kollsionskäse
	double distance_from_player(std::shared_ptr<GameState::Objekt_fest> o2);// , Spieler* p1);
	bool kollision_rechts(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Player_data> iplayertemp);//, std::shared_ptr<Spieler> p1);
	bool kollision_links(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Player_data> iplayertemp);//, Spieler* p1);
	bool kollision_oben(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Player_data> iplayertemp);//, Spieler* p1);
	bool kollision_unten(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Player_data> iplayertemp);//, Spieler* p1);
	void SpielerAni();
#pragma endregion	
};