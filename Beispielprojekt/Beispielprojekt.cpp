#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <iostream>
#include <math.h>

//#include "Menu.cpp" //Also wenn, dann eh Menu.h ....		:P
#include "GameState.h"

bool game_start = true;
bool y_down = false; // sprung?
bool x_down = false; // ist waagerecht gedrückt ?
bool collision_rechts = false;
bool collision_links = false;
bool collision_oben = false;
bool collision_unten = true;
bool newjumpallowed = true;
bool collision_damage = false;
int damage_timer = 0;
bool gegner_dead = false;


const double DAMAGE_TIME_CYCLE = 20;	//Zeitintervall, nachdem DAMAGE_COUNT Herzen abgezogen werden
const double DAMAGE_COUNT = 1;			//Anzahl der Herzen welche man abgezogen bekommt
const double PLAYER_VOIDKILL_DISTANCE = 2000;
const int RENDER_DISTANCE = 5000;
const double MAX_SPEED = 5;				//Maximale Geschwindikkeit Spieler x-Richtung
const double MAX_HEIGHT = 100;			// Maximale Sprunghöhe Spieler y-Richtung
const double MAX_JUMP_TIME = 14;		//Maximale Zeit, die w gedrückt werden kann, um Sprungdauer zu beeinflussen.
const double PLAYER_ACC_UP = 0.5;		//Sprungkraft
const double SCHWERKRAFT_G = 0.01;		//Schwerkraft
const double GEGNER_SPEED = 2;
//#define debugSpielerX
//#define debugSpielerY
#define debugmodus

class GameWindow : public Gosu::Window
{
public:
	/*GameState game;
	GameWindow()
		: Window(800, 600)
		, game()*/
		/*if (game_start == false) {
			GameMenu menu;
			GameWindow()
				: Window(800, 600)
				, menu()
			{
				set_caption("Dr. Salzig und Mister Coco");
			};
			else if (game_start == true) {*/
	GameState game;
	GameWindow()
		: Window(800, 600)
		, game()
	{
		set_caption("Dr. Salzig und Mister Coco");
	};
	//}

	void restart()
	{
		game.get_Spieler()->reset();
		game = GameState();
	}

	void draw() override
	{
		//while (game_start == true) {
			//Level Design
		game.elem_O_f = game.listenstart_O_f; //Hier immer letztes Element hinschreiben!  (Weil wegen sonst wird der Player gerendert wo er net soll, weil der is ja starr)
		while (game.elem_O_f->next != nullptr)
		{
			if (game.distance_from_player(game.elem_O_f) < RENDER_DISTANCE)  //Objekte werden nur gerendert wenn Sie näher als 5k Pixel sind
			{
				game.elem_O_f->image->draw(game.elem_O_f->posx, game.elem_O_f->posy, game.elem_O_f->posz);
			}
			game.elem_O_f = game.elem_O_f->next;
		}
		game.elem_O_d = game.listenstart_O_d;
		while (game.elem_O_d->next != nullptr)
		{
			if (game.distance_from_player(game.elem_O_d) < RENDER_DISTANCE)  //Objekte werden nur gerendert wenn Sie näher als 5k Pixel sind
			{
				game.elem_O_d->image->draw(game.elem_O_d->posx, game.elem_O_d->posy, game.elem_O_d->posz);
			}
			game.elem_O_d = game.elem_O_d->next;
		}

		game.hintergrund.draw_rot(400, 320, 10.0,
			0.0,
			0.5, 0.5);

		//HUD
		game.hud.draw(0, 0, 300.0, 1, 0.75);
		switch (game.keys) {
		case 2:
			game.Keys2.draw(668, 10, 400); break;
		case 1:
			game.Keys1.draw(668, 10, 400); break;
		case 0:
			game.Keys0.draw(668, 10, 400); break;
		}
		switch (game.health) {
		case 3:
			game.hudHP.draw_rot(120, 40, 400.0, 0.0, 0.5, 0.5); break;
		case 2:
			game.hudHP2.draw_rot(120, 40, 400.0, 0.0, 0.5, 0.5); break;
		case 1:
			game.hudHP1.draw_rot(120, 40, 400.0, 0.0, 0.5, 0.5); break;
		default:
			game.hudHP0.draw_rot(120, 40, 400.0, 0.0, 0.5, 0.5);
			game.Rolle();

			/*game.Scroll.draw_rot(400, 174, 150.0, 0.0, 0.5, 0.5);

				game.GameOver.draw_rot(400, 300, 150.0, 0.0, 0.5, 0.5);*/


		}

		//Player rendering
		game.elem_P_d = game.listenstart_P_d;
		while (game.elem_P_d->next != nullptr)
		{
			if (game.elem_P_d->active == true)  //Nur Playerbild rendern, welches aktiv ist
			{
				game.elem_P_d->image->draw(game.get_Spieler()->player_start_x, game.get_Spieler()->player_start_y, 100, 1, 1);
				break;
			}
			game.elem_P_d = game.elem_P_d->next;
		}

		//Laser Rendering
		for (size_t i = 0; i < game.Laservektor.size(); i++)
		{
			game.Laserbild.draw_rot(game.Laservektor.at(i).posx, game.Laservektor.at(i).posy, 100.0, 0.0, 0.5, 0.5);
		}


		//}
	}

	void update() override
	{
		if (game.distance_from_player(game.KeyR21) < 50)
		{
			game.keys = game.keys + 1;	//Wegen Linked list kann ich sie net removen. Aus dem Auge, aus dem Sinn...
			game.KeyR21->startx = 10000;
			game.KeyR21->starty = 10000;
			//Playsound plop?
		}
		if (game.distance_from_player(game.KeyR41) < 50)
		{
			game.keys = game.keys + 1;
			game.KeyR41->startx = 10000;
			game.KeyR41->starty = 10000;
		}
		if (game.distance_from_player(game.iTuer) < 50 && game.keys >= 2)
		{
			game.iTuer->nohitbox = true;
			game.iTuer->image = std::make_shared<Gosu::Image>(game.Tuer_offen);
		}

		//while (game_start == true) {
		 //game.Hintergrundsound;
		collision_rechts = game.kollision_rechts(game.listenstart_O_f, game.elem_P_d);// , game.get_Spieler());
		collision_links = game.kollision_links(game.listenstart_O_f, game.elem_P_d);// , game.get_Spieler());
		collision_oben = game.kollision_oben(game.listenstart_O_f, game.elem_P_d);// , game.get_Spieler());
		collision_unten = game.kollision_unten(game.listenstart_O_f, game.elem_P_d);// , game.get_Spieler());
		collision_damage = game.kollsion_damage(game.listenstart_O_d, game.elem_P_d);
		game.SpielerModelupdate();

		//HUD
		if (input().down(Gosu::KB_K) && !game.pressed)
		{
			game.pressed = true;
			game.health = game.health - 1;
		}
		else if (!input().down(Gosu::KB_K)) { game.pressed = false; }

		if (input().down(Gosu::KB_F) && game.health <= 0) //Respawn
		{
			restart(); //Neues Spiel erzeugen
		}

		game.attack = (input().down(Gosu::KB_SPACE)) ? true : false;		//Danke Gabriel :D
		game.Lasershooter();

		//Haupt-Map-Move-Funktionen
		game.elem_O_f = game.listenstart_O_f;
		while (game.elem_O_f->next != nullptr)
		{
			game.elem_O_f->posx = game.elem_O_f->startx - (game.get_Spieler()->player_x - game.get_Spieler()->player_start_x);
			game.elem_O_f->posy = game.elem_O_f->starty - (game.get_Spieler()->player_y - game.get_Spieler()->player_start_y);
			game.elem_O_f = game.elem_O_f->next;
		}
		game.elem_O_d = game.listenstart_O_d;
		while (game.elem_O_d->next != nullptr)
		{
			game.elem_O_d->posx = game.elem_O_d->startx - (game.get_Spieler()->player_x - game.get_Spieler()->player_start_x);
			game.elem_O_d->posy = game.elem_O_d->starty - (game.get_Spieler()->player_y - game.get_Spieler()->player_start_y);
			game.elem_O_d = game.elem_O_d->next;
		}


		if (game.get_Spieler()->player_y > PLAYER_VOIDKILL_DISTANCE) //Player Killen und anhalten wenn er zu tief fällt
		{
			restart();
			collision_unten = true;
		}

		if (collision_damage)
		{
			if (game.health >= 0 && damage_timer == 0)
			{
				game.health = game.health - DAMAGE_COUNT;
				damage_timer = DAMAGE_TIME_CYCLE;
			}
			damage_timer--;
		}
		else {
			damage_timer = DAMAGE_TIME_CYCLE;
		}
		//----------------------------------------------MR COCO----------------------------------------------
		if (game.distance_from_player(game.iGegner) < 1000 && !gegner_dead)
		{
			game.get_Gegner()->KI();	//Setzen der playeraction des Gegners
			//std::cout << game.get_Gegner()->playeraction << "\t" << game.kollision_oben_gegner(game.listenstart_O_f, game.iGegner) << "\n";
			switch (game.get_Gegner()->playeraction)
			{
			case 0:		//Nix
				break;
			case 1:		//Links
				if (!game.kollision_links_gegner(game.listenstart_O_f, game.iGegner))
				{
					game.iGegner->startx = game.iGegner->startx - GEGNER_SPEED;
				}
				break;
			case 2:		//rechts
				if (!game.kollision_rechts_gegner(game.listenstart_O_f, game.iGegner))
				{
					game.iGegner->startx = game.iGegner->startx + GEGNER_SPEED;
				}
				break;
			case 3:		//hoch
				if (!game.kollision_oben_gegner(game.listenstart_O_f, game.iGegner))
				{
					game.iGegner->starty = game.iGegner->starty - (GEGNER_SPEED * 2);
				}
				break;
			default:
				break;
			}
			//game.get_Gegner()->player_start_x = game.get_Gegner()->player_start_x;
			
			//game.iGegner->posx = game.get_Gegner()->player_x;
			//game.iGegner->posy = game.get_Gegner()->player_y;
			//game.iGegner->startx = game.get_Gegner()->player_x + game.get_Gegner()->player_start_x;
			//game.iGegner->starty = game.get_Gegner()->player_y;
			//Schwerkraft Gegner

			if (!game.kollision_unten_gegner(game.listenstart_O_f, game.iGegner))
			{
				game.iGegner->starty = game.iGegner->starty + GEGNER_SPEED;
			}
			//game.get_Gegner()->player_start_y = game.get_Gegner()->player_start_y;

			
			
		}
		//game.get_Gegner()->player_x = game.get_Gegner()->player_start_x - (game.get_Spieler()->player_x - game.get_Spieler()->player_start_x);
		//game.get_Gegner()->player_y = game.get_Gegner()->player_start_y - (game.get_Spieler()->player_y - game.get_Spieler()->player_start_y);
		//game.iGegner->posx = game.get_Gegner()->player_x;
		//game.iGegner->posy = game.get_Gegner()->player_y;
		//game.iGegner->startx = game.get_Gegner()->player_start_x;
		//game.iGegner->starty = game.get_Gegner()->player_start_y;
		game.get_Gegner()->player_x = game.iGegner->startx;
		game.get_Gegner()->player_y = game.iGegner->starty;

		if (game.health_gegner <= 0)
		{
			gegner_dead = true;
			game.iGegner->startx = 10000;
			game.iGegner->starty = 10000;
			game.iGegner->posx = 10000;
			game.iGegner->posy = 10000;
			//Playsound
		}


		/*------------------------------------------------------------------------------------------------------------
															Player
		------------------------------------------------------------------------------------------------------------*/

		//Sprung ---------------------------------------------------------------------------------------------

			// Taste W

		if (collision_oben == true && game.get_Spieler()->speedPlayerY < 0)
		{

			game.get_Spieler()->speedPlayerY = 0;
			game.get_Spieler()->jumpTime = MAX_JUMP_TIME;
		}

		if (collision_unten == false) {
			game.get_Spieler()->speedPlayerY = game.get_Spieler()->speedPlayerY + game.get_Spieler()->PlayerBeschleunigung(SCHWERKRAFT_G, game.get_Spieler()->fallTime);
			game.get_Spieler()->fallTime = game.get_Spieler()->fallTime + 1;
		}
		else {
			newjumpallowed = true;
		}
		if (collision_unten == true && !(game.get_Spieler()->speedPlayerY < 0))
		{
			game.get_Spieler()->speedPlayerY = 0;
			game.get_Spieler()->fallTime = 0;
		}

		game.get_Spieler()->player_y = game.get_Spieler()->player_y + game.get_Spieler()->speedPlayerY;		//Player um seinen Y_Speed entsprechend moven

		if (input().down(Gosu::KB_W) && game.health > 0) {

			game.w_pressed = true;
			
			//game.get_Spieler()->jumpTime = (game.get_Spieler()->jumpTime < MAX_JUMP_TIME ? game.get_Spieler()->jumpTime : MAX_JUMP_TIME); // wie größ ist die Übergebene Sprungzeit?
			//game.get_Spieler()->heightPlayer = (game.get_Spieler()->PlayerSprung(game.get_Spieler()->jumpTime, MAX_HEIGHT,game.get_Spieler()->PlayerBeschleunigung(1,game.get_Spieler()->jumpTime), game.w_pressed));
			//game.get_Spieler()->player_y =game.get_Spieler()->player_y -game.get_Spieler()->heightPlayer; // y ist invertiert im Vergleich zu koordinatensystemen
			if (newjumpallowed)
			{
				game.get_Spieler()->jumpTime = game.get_Spieler()->jumpTime + 1;
				if (game.get_Spieler()->jumpTime < MAX_JUMP_TIME && collision_oben == false)
				{
					game.get_Spieler()->speedPlayerY = game.get_Spieler()->speedPlayerY - PLAYER_ACC_UP;
				}
			}


#ifdef debugSpielerY 
			std::cout << "beschleunigung: " << game.get_Spieler()->PlayerSprung(game.get_Spieler()->jumpTime, MAX_HEIGHT, game.get_Spieler()->PlayerBeschleunigung(1, game.get_Spieler()->jumpTime), game.w_pressed) << std::endl;
			std::cout << "Player´s y: " << game.get_Spieler()->player_y << std::endl;
			std::cout << "zeit taste w: " << game.get_Spieler()->jumpTime << std::endl;
#endif
		}
		else {
			game.w_pressed = false;
			game.get_Spieler()->jumpTime = 0;
			newjumpallowed = false;
		}
		//Beschleunigte Bewegung in x -------------------------------------------------------------------------

			// Taste A
		game.get_Spieler()->player_x_alt = game.get_Spieler()->player_x;	//Don't touch, sonst gehen die Laser nimmer
		if (input().down(Gosu::KB_A) && collision_links == false && game.health > 0) {
			game.a_pressed = true;
			game.facing_l = true;
			game.facing_r = false;
			game.get_Spieler()->speedPlayer = (game.get_Spieler()->PlayerBeschleunigung(1, game.get_Spieler()->playerTimeXA) < MAX_SPEED) ? game.get_Spieler()->PlayerBeschleunigung(1, game.get_Spieler()->playerTimeXA) : MAX_SPEED;
			game.get_Spieler()->player_x = game.get_Spieler()->player_x - game.get_Spieler()->speedPlayer;
			game.get_Spieler()->playerTimeXA = game.get_Spieler()->playerTimeXA + 1;


#ifdef debugSpielerX
			std::cout << "beschleunigung:" << game.get_Spieler()->PlayerBeschleunigung(1, game.get_Spieler()->playerTimeXA) << std::endl;
			std::cout << "Player´s x:" << game.get_Spieler()->player_x << std::endl;
			std::cout << "Zeit taste a" << game.get_Spieler()->playerTimeXA << std::endl;
#endif
		}
		else {
			game.a_pressed = false;
			game.get_Spieler()->playerTimeXA = 0;
		}
		// Taste D
		if (input().down(Gosu::KB_D) && collision_rechts == false && game.health > 0) {
			game.d_pressed = true;
			game.facing_l = false;
			game.facing_r = true;
			game.get_Spieler()->speedPlayer = (game.get_Spieler()->PlayerBeschleunigung(1, game.get_Spieler()->playerTimeXD) < MAX_SPEED) ? game.get_Spieler()->PlayerBeschleunigung(1, game.get_Spieler()->playerTimeXD) : MAX_SPEED;
			// Zeile Drüber wenn beschl. kleiner als MAX_SPEED, dann beschleunigung, sonst MAX_SPEED (schnellschreibweise 'x?x:x' (ternärer operator) danke Gabriel :D
			game.get_Spieler()->player_x = game.get_Spieler()->player_x + game.get_Spieler()->speedPlayer;
			game.get_Spieler()->playerTimeXD = game.get_Spieler()->playerTimeXD + 1;

#ifdef debugSpielerX 	
			std::cout << "beschleunigung:" << game.get_Spieler()->PlayerBeschleunigung(1, game.get_Spieler()->playerTimeXD) << std::endl;
			std::cout << "Player´s x:" << game.get_Spieler()->player_x << std::endl;
			std::cout << "zeit taste d" << game.get_Spieler()->playerTimeXD << std::endl;
#endif
		}
		else {
			game.d_pressed = false;
			game.get_Spieler()->playerTimeXD = 0;
		}
		if (!input().down(Gosu::KB_D) && !input().down(Gosu::KB_A))
		{
			game.get_Spieler()->speedPlayer = 0;
		}
		//------------------------------------------------------------------------------------------------------
	//}


#ifdef debugmodus
		if (input().down(Gosu::KB_UP))
		{
			game.get_Spieler()->player_y = game.get_Spieler()->player_y - 10;
		}
		if (input().down(Gosu::KB_DOWN))
		{
			game.get_Spieler()->player_y = game.get_Spieler()->player_y + 10;
		}
		if (input().down(Gosu::KB_RIGHT))
		{
			game.get_Spieler()->player_x = game.get_Spieler()->player_x + 10;
		}
		if (input().down(Gosu::KB_LEFT))
		{
			game.get_Spieler()->player_x = game.get_Spieler()->player_x - 10;
		}
#endif
	}
};

// C++ Hauptprogramm
int main()
{
	GameWindow window;
	window.show();

}
