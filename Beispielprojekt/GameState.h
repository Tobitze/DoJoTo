#pragma once
#include "Spieler.h"

const int IMAGE_CYCLE_TIME = 20;
const int LASER_SHOOTING_TIMER = 20;
const double LASER_SPEED = 10;		//Sollte nicht gr��er sein als Laser breit, sonst tunnelt er durch Objekte
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
		bool nohitbox;
		std::shared_ptr<Objekt_damage> next;
		std::shared_ptr<Gosu::Image> image;
	};
	std::shared_ptr<Objekt_damage> erstelle_Objekt_damage_ptr(double breite, double hoehe, double posx, double posy, double posz, std::shared_ptr<Objekt_damage> next, std::shared_ptr<Gosu::Image> image, double scale_x = 1, double scale_y = 1, bool hit = false);
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
	int i = 24; //entrollen der schriftrolle counter
	int s = i;
	int j = 12;
	int u = j;
	bool facing_r = true;
	bool facing_l = false;
	bool pressed = false;
	bool w_pressed = false;// player sprung
	bool a_pressed = false;// player links
	bool d_pressed = false;// player rechts
	int health_gegner = 5;
	bool gamefinished = false;
	void Rolle(bool end, bool death);


	Gosu::Image bodenR;
	Gosu::Image bodenL;
	Gosu::Image Boden_HG;
	Gosu::Image Wand;
	Gosu::Image Wand_r1;
	Gosu::Image Wand_l1;
	Gosu::Image hintergrund;
	Gosu::Image Kiste;
	Gosu::Image Plattform1;
	Gosu::Image Plattform2;
	Gosu::Image spikesLng;
	Gosu::Image spikessrt;
	Gosu::Image Lava;
	Gosu::Image Lava_G;
	Gosu::Image Key;
	Gosu::Image Altklausur0;
	Gosu::Image Altklausur1;
	//HUD
	Gosu::Image hud;
	Gosu::Image hudHP;
	Gosu::Image hudHP2;
	Gosu::Image hudHP1;
	Gosu::Image hudHP0;
	Gosu::Image Scroll;
	Gosu::Image Scroll2;
	Gosu::Image Scroll3;
	Gosu::Image Scroll4;
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
	Gosu::Image MisterCocodead;
	Gosu::Image Laserbild;
	Gosu::Image Wand_destr_0;
	Gosu::Image Wand_destr_1;
	Gosu::Image Wand_destr_2;
	Gosu::Image Wand_destr_3;
	Gosu::Image Tuer;
	Gosu::Image Tuer_offen;
	Gosu::Image Endscreen;

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
	//Linked list �ber pointer

//Objekte
	
//nach R�umen sortiert
	//Raum 1 - Spawn 
	
	//Raum 2 - Lava und Schl�ssel
	std::shared_ptr<Objekt_fest> DeckeR21;
	std::shared_ptr<Objekt_fest> DeckeR22;
	std::shared_ptr<Objekt_fest> DeckeR23;

	std::shared_ptr<Objekt_fest> WandR2L1;

	std::shared_ptr<Objekt_fest> KeyR21;
	//Gang zu Raum 3 - �ber Raum 1 (mit Fake ausgang)
	std::shared_ptr<Objekt_fest>BodenG11;
	std::shared_ptr<Objekt_fest>BodenG12;
	std::shared_ptr<Objekt_fest>BodenG13;

	std::shared_ptr<Objekt_fest>DeckeG11;
	std::shared_ptr<Objekt_fest>DeckeG12;
	std::shared_ptr<Objekt_fest>DeckeG13;
	std::shared_ptr<Objekt_fest>DeckeG14;
	
	std::shared_ptr<Objekt_fest>WandG1R1;
	std::shared_ptr<Objekt_fest>WandG1RZ1;
	std::shared_ptr<Objekt_fest>WandG1RZ2;
	std::shared_ptr<Objekt_fest>WandG1L1;

	std::shared_ptr<Objekt_fest> KisteG11;
	std::shared_ptr<Objekt_fest> KisteG12;
	//Anti Geheimgang
	std::shared_ptr<Objekt_fest> DeckeA11;
	std::shared_ptr<Objekt_fest> DeckeA12;
	std::shared_ptr<Objekt_fest> DeckeA13;
	std::shared_ptr<Objekt_fest> DeckeA14;
	std::shared_ptr<Objekt_fest> DeckeA15;
	
	std::shared_ptr<Objekt_fest> WandA1R1;
	std::shared_ptr<Objekt_fest> WandA1L1;
	std::shared_ptr<Objekt_fest> WandA1L2;
	std::shared_ptr<Objekt_fest> WandA1L3;
	std::shared_ptr<Objekt_damage> SpikesA11;
	std::shared_ptr<Objekt_damage> SpikesA12;
	std::shared_ptr<Objekt_damage> SpikesA13;
	std::shared_ptr<Objekt_damage> SpikesA14;
	std::shared_ptr<Objekt_damage> SpikesA15;
	std::shared_ptr<Objekt_damage> SpikesA16;
	std::shared_ptr<Objekt_damage> SpikesA17;
	//Raum 3 - von Gang zu Bossraum 
	std::shared_ptr<Objekt_fest>DeckeR31;
	
	std::shared_ptr<Objekt_fest>BodenR31;
	
	std::shared_ptr<Objekt_fest>WandR3R1;
	std::shared_ptr<Objekt_fest>WandR3R2;
	std::shared_ptr<Objekt_fest>WandR3L1;
	std::shared_ptr<Objekt_fest>WandR3L2;
	std::shared_ptr<Objekt_fest>WandR3LZ1;
	std::shared_ptr<Objekt_fest>WandR3LZ2;
	std::shared_ptr<Objekt_fest> iTuer;

	std::shared_ptr<Objekt_fest> PlattformR3L1;
	std::shared_ptr<Objekt_fest> PlattformR3R1;
	//Raum 4 - Schl�ssel 2
	std::shared_ptr<Objekt_fest>DeckeR41;
	
	std::shared_ptr<Objekt_fest>BodenR41;
	
	std::shared_ptr<Objekt_fest>WandR4L1;
	std::shared_ptr<Objekt_fest> KeyR41;
	//Bossraum - hinter der T�r (Unten Rechts)
	std::shared_ptr<Objekt_fest>BodenB11;
	std::shared_ptr<Objekt_fest>BodenB12;

	std::shared_ptr<Objekt_fest>DeckeB11;
	std::shared_ptr<Objekt_fest>DeckeB12;

	std::shared_ptr<Objekt_fest>WandB1L1;

	std::shared_ptr<Objekt_fest>Altklausur;
	//Alles andere
	std::shared_ptr<Objekt_fest> iKiste;

	//Plattformen
	std::shared_ptr<Objekt_fest> iPlattform1;
	std::shared_ptr<Objekt_fest> iPlattform2;

	//B�den
	std::shared_ptr<Objekt_fest> ibodenR;
	std::shared_ptr<Objekt_fest> ibodenL;
	std::shared_ptr<Objekt_fest> iBoden3;
	std::shared_ptr<Objekt_fest> iBoden4;
	std::shared_ptr<Objekt_fest> iBoden5;


	std::shared_ptr<Objekt_fest> iBoden6;
	std::shared_ptr<Objekt_fest> iBoden7;
	std::shared_ptr<Objekt_fest> iBoden8;





	//W�nde links
	std::shared_ptr<Objekt_fest> iWand_l1;
	std::shared_ptr<Objekt_fest> iWand_l2;

	std::shared_ptr<Objekt_fest> iWand_l3;
	std::shared_ptr<Objekt_fest> iWand_l4;
	std::shared_ptr<Objekt_fest> iWand_l5;


	//W�nde rechts
	std::shared_ptr<Objekt_fest> iWand_r1;
	std::shared_ptr<Objekt_fest> iWand_r2;
	std::shared_ptr<Objekt_fest> iWand_r3;
	std::shared_ptr<Objekt_fest> iWand_r4;

	std::shared_ptr<Objekt_fest> iWand_destr_test;
	std::shared_ptr<Objekt_fest> iWand_destr_test2;

	std::shared_ptr<Objekt_fest> iLava1;
	std::shared_ptr<Objekt_fest> iLava2;
	std::shared_ptr<Objekt_fest> iLava3;
	std::shared_ptr<Objekt_fest> iLava4;
	std::shared_ptr<Objekt_fest> iLava5;
	std::shared_ptr<Objekt_fest> elem_O_f;
	std::shared_ptr<Objekt_fest> listenstart_O_f; //Hier immer letztes Element hinschreiben

	//Liste f�r Player
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

	//Liste f�r Objekt_damage

	std::shared_ptr<Objekt_damage> ilistenproblemloeserobjektdamage;
	std::shared_ptr<Objekt_damage> iGegner;	//Reines Test-Objekt, kann auch wieder weg...
	//Hier neue einf�gen
	std::shared_ptr<Objekt_damage> iLava_G1;
	std::shared_ptr<Objekt_damage> iLava_G2;
	std::shared_ptr<Objekt_damage> elem_O_d;
	std::shared_ptr<Objekt_damage> ispikes0;
	std::shared_ptr<Objekt_damage> ispikes1;
	std::shared_ptr<Objekt_damage> ispikes2;
	std::shared_ptr<Objekt_damage> ispikes3;

	std::shared_ptr<Objekt_damage> listenstart_O_d; //Hier immer letztes Element hinschreiben





	GameState();





#pragma region 1 //Kollsionsk�se
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