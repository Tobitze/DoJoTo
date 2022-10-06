#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <iostream>
#include <math.h>
//#include "Menu.cpp"
#include "GameState.h"


bool game_start = true;
bool y_down = false; // sprung?
bool x_down = false; // ist waagerecht gedrückt ?
bool collision_rechts = false;
bool collision_links = false;
bool collision_oben = false;
bool collision_unten = true;


const double MAX_SPEED = 5;			//Maximale Geschwindikkeit Spieler x-Richtung
const double MAX_HEIGHT = 100;		// Maximale Sprunghöhe Spieler y-Richtung
const double MAX_JUMP_TIME = 10;	//Maximale Zeit, die w gedrückt werden kann, um Sprungdauer zu beeinflussen.
const double PLAYER_ACC_UP = 2;		//Sprungkraft
const double SCHWERKRAFT_G = 0.1;	//Schwerkraft
//#define debugSpielerX
//#define debugSpielerY

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
					if (game.distance_from_player(game.elem_O_f) < 5000)  //Objekte werden nur gerendert wenn Sie näher als 5k Pixel sind
					{
						game.elem_O_f->image->draw(game.elem_O_f->posx, game.elem_O_f->posy, game.elem_O_f->posz);
					}
					game.elem_O_f = game.elem_O_f->next;
				}
				game.hintergrund.draw_rot(400, 320, 10.0,
					0.0,
					0.5, 0.5);
				//HUD
				if (game.health == 3)
				{
					game.hudHP.draw_rot(120, 40, 100.0,
						0.0,
						0.5, 0.5);
				}
				else if (game.health == 2)
				{
					game.hudHP2.draw_rot(120, 40, 100.0,
						0.0,
						0.5, 0.5);
				}
				else if (game.health == 1)
				{
					game.hudHP1.draw_rot(120, 40, 100.0,
						0.0,
						0.5, 0.5);
				}
				else if (game.health <= 0)
				{
					game.hudHP0.draw_rot(120, 40, 100.0,
						0.0,
						0.5, 0.5);
					game.GameOver.draw_rot(400, 300, 100.0,
						0.0,
						0.5, 0.5);


				}
				//game.rPlayertemp1.draw(p1.player_start_x,game.get_Spieler()->player_start_y, 100, 1, 1);
				//game.rPlayertemp2.draw(p1.player_start_x,game.get_Spieler()->player_start_y, 100, 1, 1);    //Veraltet
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
			//}
		}

		void update() override
		{
			//while (game_start == true) {
			collision_rechts = game.kollision_rechts(game.listenstart_O_f, game.elem_P_d);// , game.get_Spieler());
			collision_links = game.kollision_links(game.listenstart_O_f, game.elem_P_d);// , game.get_Spieler());
			collision_oben = game.kollision_oben(game.listenstart_O_f, game.elem_P_d);// , game.get_Spieler());
			collision_unten = game.kollision_unten(game.listenstart_O_f, game.elem_P_d);// , game.get_Spieler());
			game.SpielerAni();

				//HUD
				if (input().down(Gosu::KB_K) && !game.pressed)
				{
					game.pressed = true;
					game.health = game.health - 1;

				}
				else if (!input().down(Gosu::KB_K)) { game.pressed = false; }

				if (input().down(Gosu::KB_F) && game.health <= 0) //Respawn
				{
					game = GameState(); //Neues Spiel erzeugen
				}


				//Reine Test-Features, können bei working Player weg
				if (input().down(Gosu::KB_LEFT))
				{
					if (collision_links == false)
					{

						game.get_Spieler()->player_x = game.get_Spieler()->player_x - 5;
					}
				}
				if (input().down(Gosu::KB_RIGHT))
				{
					if (collision_rechts == false)
					{
						game.get_Spieler()->player_x = game.get_Spieler()->player_x + 5;
					}

				}
				if (input().down(Gosu::KB_UP))
				{
					if (collision_oben == false)
					{
						game.get_Spieler()->player_y =game.get_Spieler()->player_y - 5;
					}
				}
				if (input().down(Gosu::KB_DOWN))
				{
					if (collision_unten == false)
					{
						game.get_Spieler()->player_y =game.get_Spieler()->player_y + 5;
					}
				}


				//Haupt-Map-Move-Funktionen
				game.elem_O_f = game.listenstart_O_f;
				while (game.elem_O_f->next != nullptr)
				{
					if (game.distance_from_player(game.elem_O_f) < 10000)	//Renderdistanz
					{
						game.elem_O_f->posx = game.elem_O_f->startx - (game.get_Spieler()->player_x - game.get_Spieler()->player_start_x);
						game.elem_O_f->posy = game.elem_O_f->starty - (game.get_Spieler()->player_y - game.get_Spieler()->player_start_y);
						game.elem_O_f = game.elem_O_f->next;
					}
				}

				if (game.get_Spieler()->player_y > 1000) //Player Killen und anhalten wenn er zu tief fällt
				{
					restart();
					collision_unten = true;
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
				if (collision_unten == true && !(game.get_Spieler()->speedPlayerY < 0))
				{
					game.get_Spieler()->speedPlayerY = 0;
					game.get_Spieler()->fallTime = 0;
				}

				game.get_Spieler()->player_y = game.get_Spieler()->player_y + game.get_Spieler()->speedPlayerY;		//Player um seinen Y_Speed entsprechend moven

				if (input().down(Gosu::KB_W)) {

					game.w_pressed = true;

					//game.get_Spieler()->jumpTime = (game.get_Spieler()->jumpTime < MAX_JUMP_TIME ? game.get_Spieler()->jumpTime : MAX_JUMP_TIME); // wie größ ist die Übergebene Sprungzeit?
					//game.get_Spieler()->heightPlayer = (game.get_Spieler()->PlayerSprung(game.get_Spieler()->jumpTime, MAX_HEIGHT,game.get_Spieler()->PlayerBeschleunigung(1,game.get_Spieler()->jumpTime), game.w_pressed));
					//game.get_Spieler()->player_y =game.get_Spieler()->player_y -game.get_Spieler()->heightPlayer; // y ist invertiert im Vergleich zu koordinatensystemen
					game.get_Spieler()->jumpTime = game.get_Spieler()->jumpTime + 1;
					if (game.get_Spieler()->jumpTime < MAX_JUMP_TIME && collision_oben == false)
					{
						game.get_Spieler()->speedPlayerY = game.get_Spieler()->speedPlayerY - PLAYER_ACC_UP;
					}


#ifdef debugSpielerY 
					std::cout << "beschleunigung: " <<game.get_Spieler()->PlayerSprung(game.get_Spieler()->jumpTime, MAX_HEIGHT,game.get_Spieler()->PlayerBeschleunigung(1,game.get_Spieler()->jumpTime), game.w_pressed) << std::endl;
					std::cout << "Player´s y: " <<game.get_Spieler()->player_y << std::endl;
					std::cout << "zeit taste w: " <<game.get_Spieler()->jumpTime << std::endl;
#endif
				}
				else {
					game.w_pressed = false;
					game.get_Spieler()->jumpTime = 0;
				}
				//Beschleunigte Bewegung in x -------------------------------------------------------------------------

					// Taste A
				if (input().down(Gosu::KB_A) && collision_links == false) {
					game.a_pressed = true;
					game.get_Spieler()->speedPlayer = (game.get_Spieler()->PlayerBeschleunigung(1,game.get_Spieler()->playerTimeXA) < MAX_SPEED) ?game.get_Spieler()->PlayerBeschleunigung(1,game.get_Spieler()->playerTimeXA) : MAX_SPEED;
					game.get_Spieler()->player_x =game.get_Spieler()->player_x -game.get_Spieler()->speedPlayer;
					game.get_Spieler()->playerTimeXA =game.get_Spieler()->playerTimeXA + 1;


#ifdef debugSpielerX
					std::cout << "beschleunigung:" <<game.get_Spieler()->PlayerBeschleunigung(1,game.get_Spieler()->playerTimeXA) << std::endl;
					std::cout << "Player´s x:" <<game.get_Spieler()->player_x << std::endl;
					std::cout << "Zeit taste a" <<game.get_Spieler()->playerTimeXA << std::endl;
#endif
				}
				else {
					game.a_pressed = false;
					game.get_Spieler()->playerTimeXA = 0;
				}
				// Taste D
				if (input().down(Gosu::KB_D) && collision_rechts == false) {
					game.d_pressed = true;
					game.get_Spieler()->speedPlayer = (game.get_Spieler()->PlayerBeschleunigung(1,game.get_Spieler()->playerTimeXD) < MAX_SPEED) ?game.get_Spieler()->PlayerBeschleunigung(1,game.get_Spieler()->playerTimeXD) : MAX_SPEED;
					// Zeile Drüber wenn beschl. kleiner als MAX_SPEED, dann beschleunigung, sonst MAX_SPEED (schnellschreibweise 'x?x:x' (ternärer operator) danke Gabriel :D
					game.get_Spieler()->player_x =game.get_Spieler()->player_x +game.get_Spieler()->speedPlayer;
					game.get_Spieler()->playerTimeXD =game.get_Spieler()->playerTimeXD + 1;

#ifdef debugSpielerX 	
					std::cout << "beschleunigung:" <<game.get_Spieler()->PlayerBeschleunigung(1,game.get_Spieler()->playerTimeXD) << std::endl;
					std::cout << "Player´s x:" <<game.get_Spieler()->player_x << std::endl;
					std::cout << "zeit taste d" <<game.get_Spieler()->playerTimeXD << std::endl;
#endif
				}
				else {
					game.d_pressed = false;
					game.get_Spieler()->playerTimeXD = 0;
				}
				//------------------------------------------------------------------------------------------------------
			//}
	}
};

// C++ Hauptprogramm
int main()
{	
	GameWindow window;
	window.show();
	
}
