#pragma once
#include "Spieler.h"

const int IMAGE_CYCLE_TIME = 20;
const int LASER_SHOOTING_TIMER = 20;

class GameState {
	Spieler* p1;
	Spieler* g1;
public:

	bool attack = false;
	int t = 0;	//Just don't touch it
	int tl = 0;
	//static Spieler p1;
	Spieler* get_Spieler();
	Spieler* get_Gegner();

	struct Objekt_fest
	{
		double posx, posy, startx, starty, posz;
		double breite, hoehe, scale_x, scale_y;
		bool nohitbox;
		std::shared_ptr<Objekt_fest> next;
		std::shared_ptr<Gosu::Image> image;
		//Objekt_fest* next;
		//Gosu::Image* image;
	};
	std::shared_ptr<Objekt_fest> erstelle_Objekt_fest_ptr(double breite, double hoehe, double posx, double posy, double posz, std::shared_ptr<Objekt_fest> next, std::shared_ptr<Gosu::Image> image, double scale_x = 1, double scale_y = 1, bool hit = false);
	struct Player_data
	{
		bool active;
		double breite, hoehe, scale_x, scale_y;
		std::shared_ptr<Player_data> next;
		std::shared_ptr<Gosu::Image> image;
	};
	std::shared_ptr<Player_data> erstelle_Player_data_ptr(double breite, double hoehe, std::shared_ptr<Player_data> next, std::shared_ptr<Gosu::Image> image, bool active, double scale_x = 1, double scale_y = 1);
	struct Objekt_damage
	{
		double posx, posy, startx, starty, posz;
		double breite, hoehe, scale_x, scale_y;
		std::shared_ptr<Objekt_damage> next;
		std::shared_ptr<Gosu::Image> image;
	};
	std::shared_ptr<Objekt_damage> erstelle_Objekt_damage_ptr(double breite, double hoehe, double posx, double posy, double posz, std::shared_ptr<Objekt_damage> next, std::shared_ptr<Gosu::Image> image, double scale_x = 1, double scale_y = 1);
	struct Laser
	{
		double startx, starty;
		double posx, posy;
		bool direction_right;
	};
	Laser erstelle_Laser(double x, double y, bool d_r);
	std::vector<Laser> getLaserVektor();

	std::vector<Laser> Laservektor;
	void Lasershooter();

	int health = 3;
	int i = 8; //entrollen der schriftrolle counter

	bool facing_r = true;
	bool facing_l = false;
	bool pressed = false;
	bool w_pressed = false;// player sprung
	bool a_pressed = false;// player links
	bool d_pressed = false;// player rechts
	void Rolle();

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
	Gosu::Image Scroll;
	Gosu::Image Scroll2;
	Gosu::Image GameOver;
	//Player	//Aus dem Provisorium ist ein dauerhafter Zustand geworden xD
	Gosu::Image rPlayertemp1;
	Gosu::Image rPlayertemp2;
	Gosu::Image rPlayertempA1;
	Gosu::Image rPlayertempA2;
	Gosu::Image lPlayertemp1;
	Gosu::Image lPlayertemp2;
	Gosu::Image lPlayertempA1;
	Gosu::Image lPlayertempA2;

	Gosu::Image Laserbild;

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
	std::shared_ptr<Player_data> iplayertempr1;
	std::shared_ptr<Player_data> iplayertempr2;
	std::shared_ptr<Player_data> iplayertempl1;
	std::shared_ptr<Player_data> iplayertempl2;
	std::shared_ptr<Player_data> iplayertempl1A;
	std::shared_ptr<Player_data> iplayertempl2A;
	std::shared_ptr<Player_data> iplayertempr1A;
	std::shared_ptr<Player_data> iplayertempr2A;

	std::shared_ptr<Player_data> elem_P_d;
	std::shared_ptr<Player_data> listenstart_P_d; //Hier immer letztes Element hinschreiben
	
	//Liste für Objekt_damage

	std::shared_ptr<Objekt_damage> ilistenproblemloeserobjektdamage;
	std::shared_ptr<Objekt_damage> ikisteschaden;	//Reines Test-Objekt, kann auch wieder weg...
	//Hier neue einfügen

	std::shared_ptr<Objekt_damage> elem_O_d;
	std::shared_ptr<Objekt_damage> listenstart_O_d; //Hier immer letztes Element hinschreiben





	GameState();


	


#pragma region 1 //Kollsionskäse
	double distance_from_player(std::shared_ptr<GameState::Objekt_fest> o2);// , Spieler* p1);
	double distance_from_player(std::shared_ptr<GameState::Objekt_damage> o2);
	bool kollision_rechts(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Player_data> iplayertemp);//, std::shared_ptr<Spieler> p1);
	bool kollision_links(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Player_data> iplayertemp);//, Spieler* p1);
	bool kollision_oben(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Player_data> iplayertemp);//, Spieler* p1);
	bool kollision_unten(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Player_data> iplayertemp);//, Spieler* p1);
	bool kollsion_damage(std::shared_ptr<GameState::Objekt_damage> listenstart, std::shared_ptr<GameState::Player_data> iplayertemp);
	void SpielerModelupdate();
#pragma endregion	
};