#pragma once
#include "Spieler.h"

const int IMAGE_CYCLE_TIME = 20;
const int LASER_SHOOTING_TIMER = 20;
const double LASER_SPEED = 10;		//Sollte nicht größer sein als Laser breit, sonst tunnelt er durch Objekte
const double LASER_RENDERDISTANCE = 1000;

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
		bool nohitbox, destroyable;
		int destroy_state;
		std::shared_ptr<Objekt_fest> next;
		std::shared_ptr<Gosu::Image> image;
		//Objekt_fest* next;
		//Gosu::Image* image;
	};
	std::shared_ptr<Objekt_fest> erstelle_Objekt_fest_ptr(double breite, double hoehe, double posx, double posy, double posz, std::shared_ptr<Objekt_fest> next, std::shared_ptr<Gosu::Image> image, double scale_x = 1, double scale_y = 1, bool hit = false, bool destr = false, int destroy_state = 0);
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
	int keys = 0;
	int i = 12; //entrollen der schriftrolle counter
	int s = i;
	bool facing_r = true;
	bool facing_l = false;
	bool pressed = false;
	bool w_pressed = false;// player sprung
	bool a_pressed = false;// player links
	bool d_pressed = false;// player rechts
	int health_gegner = 5;
	void Rolle();

	Gosu::Image bodenR;
	Gosu::Image bodenL;
	Gosu::Image Wand;
	Gosu::Image Wand_r1;
	Gosu::Image Wand_l1;
	Gosu::Image hintergrund;
	Gosu::Image Kiste;
	Gosu::Image Plattform1;
	Gosu::Image Plattform2;
	Gosu::Image spikesLng;
	Gosu::Image Lava;
	Gosu::Image Lava_G;
	//HUD
	Gosu::Image hud;
	Gosu::Image hudHP;
	Gosu::Image hudHP2;
	Gosu::Image hudHP1;
	Gosu::Image hudHP0;
	Gosu::Image Scroll;
	Gosu::Image Scroll2;
	Gosu::Image Scroll3;
	Gosu::Image GameOver;
	Gosu::Image Keys0;
	Gosu::Image Keys1;
	Gosu::Image Keys2;

	//Player	//Aus dem Provisorium ist ein dauerhafter Zustand geworden xD
	Gosu::Image rPlayertemp1;
	Gosu::Image rPlayertemp2;
	Gosu::Image rPlayertempA1;
	Gosu::Image rPlayertempA2;
	Gosu::Image lPlayertemp1;
	Gosu::Image lPlayertemp2;
	Gosu::Image lPlayertempA1;
	Gosu::Image lPlayertempA2;
	Gosu::Image MisterCoco;
	Gosu::Image Laserbild;
	Gosu::Image Wand_destr_0;
	Gosu::Image Wand_destr_1;
	Gosu::Image Wand_destr_2;
	Gosu::Image Wand_destr_3;
	Gosu::Image Tuer;

	//Sounds

	 
		
	//Gosu::Song HintergrundSound;
	//Gosu::Sample SprungSound;



	//Gosu::Sample HintergrundSound;
	Gosu::Sample SprungSound;

	//Gosu::Sample GewonnenSound;
	Gosu::Sample VerlorenSound;
	//Gosu::Sample TuerSound;
	//Gosu::Sample SchadenSound;
	//Gosu::Sample WandSound;
	Gosu::Sample SchadenGegnerSound;
	//Gosu::Sample LaserSound;
	Gosu::Sample TestSound;

	//Game Window

	std::shared_ptr<Objekt_fest> ilistenproblenloeser;					 //Einfach nicht hinterfragen
	//Linked list über pointer

//Objekte

	std::shared_ptr<Objekt_fest> iKiste;

	//Plattformen
	std::shared_ptr<Objekt_fest> iPlattform1;
	std::shared_ptr<Objekt_fest> iPlattform2;

	//Böden
	std::shared_ptr<Objekt_fest> ibodenR;
	std::shared_ptr<Objekt_fest> ibodenL;
	std::shared_ptr<Objekt_fest> iBoden3;
	std::shared_ptr<Objekt_fest> iBoden4;
	std::shared_ptr<Objekt_fest> iBoden5;


	std::shared_ptr<Objekt_fest> iBoden6;
	std::shared_ptr<Objekt_fest> iBoden7;
	std::shared_ptr<Objekt_fest> iBoden8;

	std::shared_ptr<Objekt_damage> ispikesLong;



	//Wände links
	std::shared_ptr<Objekt_fest> iWand_l1;
	std::shared_ptr<Objekt_fest> iWand_l2;

	std::shared_ptr<Objekt_fest> iWand_l3;
	std::shared_ptr<Objekt_fest> iWand_l4;
	std::shared_ptr<Objekt_fest> iWand_l5;

	//Wände rechts
	std::shared_ptr<Objekt_fest> iWand_r1;
	std::shared_ptr<Objekt_fest> iWand_r2;
	std::shared_ptr<Objekt_fest> iWand_r3;
	std::shared_ptr<Objekt_fest> iWand_r4;

	std::shared_ptr<Objekt_fest> iWand_destr_test;
	std::shared_ptr<Objekt_fest> iWand_destr_test2;
	std::shared_ptr<Objekt_fest> iTuer;
	std::shared_ptr<Objekt_fest> iLava1;
	std::shared_ptr<Objekt_fest> iLava2;

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
	std::shared_ptr<Objekt_damage> iGegner;	//Reines Test-Objekt, kann auch wieder weg...
	//Hier neue einfügen
	std::shared_ptr<Objekt_damage> iLava_G1;
	std::shared_ptr<Objekt_damage> iLava_G2;
	std::shared_ptr<Objekt_damage> elem_O_d;
	std::shared_ptr<Objekt_damage> listenstart_O_d; //Hier immer letztes Element hinschreiben





	GameState();





#pragma region 1 //Kollsionskäse
	double distance_from_player(std::shared_ptr<GameState::Objekt_fest> o2);// , Spieler* p1);
	double distance_from_player(std::shared_ptr<GameState::Objekt_damage> o2);
	double distance_from_player(int Vektorlisteni);
	bool kollision_rechts(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Player_data> iplayertemp);//, std::shared_ptr<Spieler> p1);
	bool kollision_links(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Player_data> iplayertemp);//, Spieler* p1);
	bool kollision_oben(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Player_data> iplayertemp);//, Spieler* p1);
	bool kollision_unten(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Player_data> iplayertemp);//, Spieler* p1);
	bool kollsion_damage(std::shared_ptr<GameState::Objekt_damage> listenstart, std::shared_ptr<GameState::Player_data> iplayertemp);
	void SpielerModelupdate();
	bool kollision_rechts_gegner(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Objekt_damage> iplayertemp);//, std::shared_ptr<Spieler> p1);
	bool kollision_links_gegner(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Objekt_damage> iplayertemp);//, Spieler* p1);
	bool kollision_oben_gegner(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Objekt_damage> iplayertemp);//, Spieler* p1);
	bool kollision_unten_gegner(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Objekt_damage> iplayertemp);//, Spieler* p1);
#pragma endregion	
};