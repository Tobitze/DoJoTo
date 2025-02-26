#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <iostream>
#include "Spieler.h"
#include <math.h>
#include "GameState.h"


GameState::GameState()
//Level Design
	: bodenR("boden1.jpg")
	, bodenL("boden1.jpg")
	, Wand("boden1.jpg")
	, Wand_r1("Wand rechts.png")
	, Wand_l1("Wand links.png")
	, Boden_HG("boden_hg.png")
	, hintergrund("hintergrund.jfif")
	, Kiste("Block.png")
	, Plattform1("Plattform1.png")
	, Plattform2("Plattform1.png")
	, spikesLng("spikes_lng.png")
	, spikessrt("spikes_srt.png")
	, Tuer("Tuere.png")
	, Tuer_offen("Tuere_offen.png")		//Hier Grafik f�r T�r offen implementieren!
	, Lava("Lava.png")
	, Lava_G("Lava1.png")
	, Key("Schluessel.png")
	, Altklausur0("Matherfucking_holy_Altklausur_0.png")
	, Altklausur1("Matherfucking_holy_Altklausur_1.png")
	//HUD
	, hud("HUD.png")
	, hudHP("hud_hp.png")
	, hudHP2("hud_hp-1.png")
	, hudHP1("hud_hp-2.png")
	, hudHP0("hud_hp-3.png")
	, Scroll("Scroll.png")
	, Scroll2("Scroll2.png")
	, Scroll3("Scroll3.png")
	, Scroll4("Mister Coco schild.png")
	, GameOver("GameOver.png")
	, Keys0("Schluessel_HUD0.png")
	, Keys1("Schluessel_HUD1.png")
	, Keys2("Schluessel_HUD2.png")
	, Endscreen("Mister Coco schild.png")
	//Player (temp)
	, rPlayertemp1("r-Dr.Salzig1.png")
	, rPlayertemp2("r-Dr.Salzig2.png")
	, rPlayertempA1("r-Dr.Salzig1-attack.png")
	, rPlayertempA2("r-Dr.Salzig2-attack.png")
	, lPlayertemp1("l-Dr.Salzig1.png")
	, lPlayertemp2("l-Dr.Salzig2.png")
	, lPlayertempA1("l-Dr.Salzig1-attack.png")
	, lPlayertempA2("l-Dr.Salzig2-attack.png")
	, Laserbild("Laser.png")
	// Gegener
	, MisterCoco("Mister Coco.png")
	, MisterCocodead("Mister Coco-tot.png")

	, Wand_destr_0("Wand_destr_l.png")
	, Wand_destr_1("Wand_destr_l_1.png")
	, Wand_destr_2("Wand_destr_l_2.png")
	, Wand_destr_3("Wand_destr_l_3.png")

	//Sounds
	//, HintergrundSound("HintergrundSound.wav")
	, SprungSound("Sprung.wav")
	//, GewonnenSound("Gewonnen.wav")
	, VerlorenSound("Verloren.wav")
	//, TuerSound("Tuer.wav")
	//, SchadenSound("Schaden.wav")
	//, WandSound("Wand.wav")
	, SchadenGegnerSound("Gegner_Schaden.wav")
	//, LaserSound("Laser.wav")
	, TestSound("Windows Critical Stop.wav")
{

	p1 = new Spieler();
	g1 = new Spieler();
	g1->player_x = 3000;		//Start-Koords Mr Coco
	g1->player_y = 0;
	g1->player_start_x = 3000;		//Start-Koords Mr Coco
	g1->player_start_y = 0;

	ilistenproblenloeser = erstelle_Objekt_fest_ptr(0, 0, 0, 0, 0, nullptr, nullptr, 1, 1);					 //Einfach nicht hinterfragen
	//Startraum\\
	//Boden
	ibodenR = erstelle_Objekt_fest_ptr(474, 58, 476, 550, 100, ilistenproblenloeser, std::make_shared<Gosu::Image>(bodenR), 1, 1);
	ibodenL = erstelle_Objekt_fest_ptr(474, 58, 0, 550, 100, ibodenR, std::make_shared<Gosu::Image>(bodenL), 1, 1);				 //Linked list �ber pointer
	
	

	//Objekte
	iKiste = erstelle_Objekt_fest_ptr(80, 80, 700, 469, 100, ibodenL, std::make_shared<Gosu::Image>(Kiste), 1, 1);
	//Plattformen
	iPlattform1 = erstelle_Objekt_fest_ptr(200, 43, 300, 200, 100, iKiste, std::make_shared<Gosu::Image>(Plattform1), 1, 1);
	iPlattform2 = erstelle_Objekt_fest_ptr(200, 43, 700, -140, 100, iPlattform1, std::make_shared<Gosu::Image>(Plattform2), 1, 1);
	//W�nde
	iWand_r1 = erstelle_Objekt_fest_ptr(58, 473, 890, 90, 100, iPlattform2, std::make_shared<Gosu::Image>(Wand_r1), 1, 1);
	iWand_r2 = erstelle_Objekt_fest_ptr(58, 473, 890, -383, 100, iWand_r1, std::make_shared<Gosu::Image>(Wand_r1), 1, 1);
	iWand_l1 = erstelle_Objekt_fest_ptr(58, 473, 0, 90, 100, iWand_r2, std::make_shared<Gosu::Image>(Wand_l1), 1, 1);
	iWand_l2 = erstelle_Objekt_fest_ptr(58, 473, 0, 0, 100, iWand_l1, std::make_shared<Gosu::Image>(Wand_l1), 1, 1);
	iWand_r3 = erstelle_Objekt_fest_ptr(58, 473, 890, 90, 100, iWand_l2, std::make_shared<Gosu::Image>(Wand_r1), 1, 1);
	iWand_r4 = erstelle_Objekt_fest_ptr(58, 473, 890, -383, 100, iWand_r3, std::make_shared<Gosu::Image>(Wand_r1), 1, 1);
	iWand_l3 = erstelle_Objekt_fest_ptr(58, 473, 0, 90, 100, iWand_r4, std::make_shared<Gosu::Image>(Wand_l1), 1, 1);
	iWand_l4 = erstelle_Objekt_fest_ptr(58, 473, 0, 0, 100, iWand_l3, std::make_shared<Gosu::Image>(Wand_l1), 1, 1);
	iWand_l5 = erstelle_Objekt_fest_ptr(58, 473, 0, -705, 100, iWand_l4, std::make_shared<Gosu::Image>(Wand_l1), 1, 1);

	iWand_destr_test = erstelle_Objekt_fest_ptr(57, 99, 0, -133, 100, iWand_l5, std::make_shared<Gosu::Image>(Wand_destr_0), 1, 1, false, true);
	iWand_destr_test2 = erstelle_Objekt_fest_ptr(57, 99, 0, -232, 100, iWand_destr_test, std::make_shared<Gosu::Image>(Wand_destr_0), 1, 1, false, true);

	//Lavaraum\\ Entspricht raum 2
	//B�den
	iBoden3 = erstelle_Objekt_fest_ptr(474, 58, -414, -45, 100, iWand_destr_test2, std::make_shared<Gosu::Image>(bodenR), 1, 1);
	iLava1 = erstelle_Objekt_fest_ptr(50, 20, -464, -10, 100, iBoden3, std::make_shared<Gosu::Image>(Lava), 1, 1);
	iLava2 = erstelle_Objekt_fest_ptr(50, 20, -514, -10, 100, iLava1, std::make_shared<Gosu::Image>(Lava), 1, 1);
	iLava3 = erstelle_Objekt_fest_ptr(50, 20, -564, -10, 100, iLava2, std::make_shared<Gosu::Image>(Lava), 1, 1);
	iLava4 = erstelle_Objekt_fest_ptr(50, 20, -614, -10, 100, iLava3, std::make_shared<Gosu::Image>(Lava), 1, 1);
	iLava5 = erstelle_Objekt_fest_ptr(50, 20, -664, -10, 100, iLava3, std::make_shared<Gosu::Image>(Lava), 1, 1);
	iBoden4 = erstelle_Objekt_fest_ptr(474, 58, -1138, -45, 100, iLava5, std::make_shared<Gosu::Image>(bodenR), 1, 1);
	WandR2L1 = erstelle_Objekt_fest_ptr(58, 437, -1138, -465, 100, iBoden4, std::make_shared<Gosu::Image>(Wand_l1),1,1);
	KeyR21 = erstelle_Objekt_fest_ptr(58, 437, -1000, -100, 100, WandR2L1, std::make_shared<Gosu::Image>(Key), 1, 1, true);
	DeckeR21 = erstelle_Objekt_fest_ptr(474, 58, -1138, -465, 100, KeyR21, std::make_shared<Gosu::Image>(bodenR), 1, 1); // Falsche Bilder sniff :C
	DeckeR22 = erstelle_Objekt_fest_ptr(474, 58, -690, -465, 100, DeckeR21, std::make_shared<Gosu::Image>(bodenR), 1, 1);
	DeckeR23 = erstelle_Objekt_fest_ptr(474, 58, -450, -465, 100, DeckeR22, std::make_shared<Gosu::Image>(bodenR), 1, 1);


	//Gang zu Raum 3
	BodenG11 = erstelle_Objekt_fest_ptr(474, 58, 890, -383, 100, DeckeR23, std::make_shared<Gosu::Image>(bodenR), 1, 1);
	BodenG12 = erstelle_Objekt_fest_ptr(474, 58, 1364, -383, 100, BodenG11, std::make_shared<Gosu::Image>(bodenR), 1, 1);
	BodenG13 = erstelle_Objekt_fest_ptr(474, 58, 1838, -383, 100, BodenG12, std::make_shared<Gosu::Image>(bodenR), 1, 1);
	WandG1RZ1 = erstelle_Objekt_fest_ptr(57, 99, 2255, -480, 100, BodenG13, std::make_shared<Gosu::Image>(Wand_destr_0), 1, 1, false, true);
	WandG1RZ2 = erstelle_Objekt_fest_ptr(57, 99, 2255, -579, 100, WandG1RZ1, std::make_shared<Gosu::Image>(Wand_destr_0), 1, 1, false, true);
	WandG1R1 = erstelle_Objekt_fest_ptr(58, 437, 2255, -1053, 100, WandG1RZ2, std::make_shared<Gosu::Image>(Wand_r1), 1, 1);
	DeckeG11 = erstelle_Objekt_fest_ptr(474, 58, 1781, -1053, 100, WandG1R1, std::make_shared<Gosu::Image>(bodenR), 1, 1);
	DeckeG12 = erstelle_Objekt_fest_ptr(474, 58, 833, -1053, 100, DeckeG11, std::make_shared<Gosu::Image>(bodenR), 1, 1);
	DeckeG13 = erstelle_Objekt_fest_ptr(474, 58, 359, -1053, 100, DeckeG12, std::make_shared<Gosu::Image>(bodenR), 1, 1);
	DeckeG14 = erstelle_Objekt_fest_ptr(474, 58, 0, -1053, 100, DeckeG13, std::make_shared<Gosu::Image>(bodenR), 1, 1);
	WandG1L1 = erstelle_Objekt_fest_ptr(58, 437, 0, -1053, 100, DeckeG14, std::make_shared<Gosu::Image>(Wand_l1), 1, 1);
	KisteG11 = erstelle_Objekt_fest_ptr(80, 80, 1300, -500, 100, WandG1L1, std::make_shared<Gosu::Image>(Kiste), 1, 1);
	KisteG12 = erstelle_Objekt_fest_ptr(80, 80, 1600, -800, 100, KisteG11, std::make_shared<Gosu::Image>(Kiste), 1, 1);
	
	//Anti Geheimgang
	WandA1R1 = erstelle_Objekt_fest_ptr(58, 437, 1781, -1490, 100, KisteG12, std::make_shared<Gosu::Image>(Wand_r1), 1, 1);
	DeckeA11 = erstelle_Objekt_fest_ptr(474, 58, 1307, -1490, 100, WandA1R1, std::make_shared<Gosu::Image>(bodenR), 1, 1);
	DeckeA12 = erstelle_Objekt_fest_ptr(474, 58, 833, -1490, 100, DeckeA11, std::make_shared<Gosu::Image>(bodenR), 1, 1);
	DeckeA13 = erstelle_Objekt_fest_ptr(474, 58, 359, -1490, 100, DeckeA12, std::make_shared<Gosu::Image>(bodenR), 1, 1);
	DeckeA14 = erstelle_Objekt_fest_ptr(474, 58, -115, -1490, 100, DeckeA13, std::make_shared<Gosu::Image>(bodenR), 1, 1);
	DeckeA15 = erstelle_Objekt_fest_ptr(474, 58, -589, -1490, 100, DeckeA14, std::make_shared<Gosu::Image>(bodenR), 1, 1);
	WandA1L1 = erstelle_Objekt_fest_ptr(58, 437, -589, -1490, 100, DeckeA15, std::make_shared<Gosu::Image>(Wand_l1), 1, 1);
	WandA1L2 = erstelle_Objekt_fest_ptr(58, 437, -589, -1053, 100, WandA1L1, std::make_shared<Gosu::Image>(Wand_r1), 1, 1);
	WandA1L3 = erstelle_Objekt_fest_ptr(58, 437, -589, -900, 100, WandA1L2, std::make_shared<Gosu::Image>(Wand_r1), 1, 1);
	//Raum 3
	DeckeR31 = erstelle_Objekt_fest_ptr(474, 58, 2255, -700, 100, WandA1L3, std::make_shared<Gosu::Image>(bodenR), 1, 1);
	WandR3L1 = erstelle_Objekt_fest_ptr(58, 437, 2255, -380, 100, DeckeR31, std::make_shared<Gosu::Image>(Wand_l1), 1, 1);
	WandR3LZ1 = erstelle_Objekt_fest_ptr(58, 99, 2255, 37, 100, WandR3L1, std::make_shared<Gosu::Image>(Wand_destr_0), 1, 1,false,true);
	WandR3LZ2 = erstelle_Objekt_fest_ptr(58, 99, 2255, 126, 100, WandR3LZ1, std::make_shared<Gosu::Image>(Wand_destr_0), 1, 1, false, true);
	BodenR31 = erstelle_Objekt_fest_ptr(474, 58, 2255, 215, 100, WandR3LZ2, std::make_shared<Gosu::Image>(bodenR), 1, 1);
	iTuer = erstelle_Objekt_fest_ptr(45, 138, 2684, 87, 100, BodenR31, std::make_shared<Gosu::Image>(Tuer), 1, 1);
	WandR3R1 = erstelle_Objekt_fest_ptr(58, 437 , 2671, -383, 100, iTuer, std::make_shared<Gosu::Image>(Wand_r1), 1, 1);
	WandR3R2 = erstelle_Objekt_fest_ptr(58, 437, 2671, -700, 100, WandR3R1, std::make_shared<Gosu::Image>(Wand_r1), 1, 1);
	PlattformR3L1 = erstelle_Objekt_fest_ptr(200, 43, 2500, -250, 100, WandR3R2, std::make_shared<Gosu::Image>(Plattform1), 1, 1);
	PlattformR3R1 = erstelle_Objekt_fest_ptr(200, 43, 2255, 40, 100, PlattformR3L1, std::make_shared<Gosu::Image>(Plattform2), 1, 1);


	//Raum 4
	DeckeR41 = erstelle_Objekt_fest_ptr(474, 58, 1781, -222, 100, PlattformR3R1, std::make_shared<Gosu::Image>(bodenR), 1, 1);
	WandR4L1 = erstelle_Objekt_fest_ptr(58, 437, 1781, -222, 100, DeckeR41, std::make_shared<Gosu::Image>(Wand_r1), 1, 1);
	BodenR41 = erstelle_Objekt_fest_ptr(474, 58, 1781, 215, 100, WandR4L1, std::make_shared<Gosu::Image>(bodenR), 1, 1);
	KeyR41 = erstelle_Objekt_fest_ptr(58, 437, 2000, 0, 100, BodenR41, std::make_shared<Gosu::Image>(Key), 1, 1, true);

	//Bossraum
	BodenB11 = erstelle_Objekt_fest_ptr(474, 58, 2729, 215, 100, KeyR41, std::make_shared<Gosu::Image>(bodenR), 1, 1);
	BodenB12 = erstelle_Objekt_fest_ptr(474, 58, 3203, 215, 100, BodenB11, std::make_shared<Gosu::Image>(bodenR), 1, 1);
	WandB1L1 = erstelle_Objekt_fest_ptr(58, 437, 3619, -222, 100, BodenB12, std::make_shared<Gosu::Image>(Wand_l1), 1, 1);
	DeckeB11 = erstelle_Objekt_fest_ptr(474, 58, 3203, -222, 100, WandB1L1, std::make_shared<Gosu::Image>(bodenR), 1, 1);
	DeckeB12 = erstelle_Objekt_fest_ptr(474, 58, 2729, -222, 100, DeckeB11, std::make_shared<Gosu::Image>(bodenR), 1, 1);
	Altklausur = erstelle_Objekt_fest_ptr(400, 400, 3450, 115, 100, DeckeB12, std::make_shared<Gosu::Image>(Altklausur0), 1,1, true);
	
	//liste Konstruktor
	elem_O_f = std::make_shared<Objekt_fest>();
	listenstart_O_f = Altklausur; //Hier immer letztes Element hinschreiben	<-----------------------		REMINDER F�R DORIAN		<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	//Liste f�r Player
	ilistenproblenloeserplayer = erstelle_Player_data_ptr(0, 0, nullptr, nullptr, false, 1, 1);
	iplayertempr1 = erstelle_Player_data_ptr(35, 94, ilistenproblenloeserplayer, std::make_shared<Gosu::Image>(rPlayertemp1), true, 1, 1);
	iplayertempr2 = erstelle_Player_data_ptr(35, 94, iplayertempr1, std::make_shared<Gosu::Image>(rPlayertemp2), false, 1, 1);
	iplayertempl1 = erstelle_Player_data_ptr(35, 94, iplayertempr2, std::make_shared<Gosu::Image>(lPlayertemp1), false, 1, 1);
	iplayertempl2 = erstelle_Player_data_ptr(35, 94, iplayertempl1, std::make_shared<Gosu::Image>(lPlayertemp2), false, 1, 1);
	iplayertempl1A = erstelle_Player_data_ptr(35, 94, iplayertempl2, std::make_shared<Gosu::Image>(lPlayertempA1), false, 1, 1);
	iplayertempl2A = erstelle_Player_data_ptr(35, 94, iplayertempl1A, std::make_shared<Gosu::Image>(lPlayertempA2), false, 1, 1);
	iplayertempr1A = erstelle_Player_data_ptr(35, 94, iplayertempl2A, std::make_shared<Gosu::Image>(rPlayertempA1), false, 1, 1);
	iplayertempr2A = erstelle_Player_data_ptr(35, 94, iplayertempr1A, std::make_shared<Gosu::Image>(rPlayertempA2), false, 1, 1);

	elem_P_d = std::make_shared<Player_data>();
	listenstart_P_d = iplayertempr2A; //Hier immer letztes Element hinschreiben
	elem_P_d = listenstart_P_d;

	//Liste f�r Objekt_damage

	ilistenproblemloeserobjektdamage = erstelle_Objekt_damage_ptr(0, 0, 0, 0, 0, nullptr, nullptr, 1, 1);	//Never touch a working system
	iGegner = erstelle_Objekt_damage_ptr(80, 80, 3000, 0, 100, ilistenproblemloeserobjektdamage, std::make_shared<Gosu::Image>(MisterCoco), 1, 1);		//Au�er den Breiten nix anfassen!
	//Hier neue einf�gen
	iLava_G1 = erstelle_Objekt_damage_ptr(145, 58, -545, -40, 300, iGegner, std::make_shared<Gosu::Image>(Lava_G), 1, 1);
	iLava_G2 = erstelle_Objekt_damage_ptr(145, 58, -690, -40, 300, iLava_G1, std::make_shared<Gosu::Image>(Lava_G), 1, 1);
	ispikes0 = erstelle_Objekt_damage_ptr(76, 19, 1970, 200, 300, iLava_G2, std::make_shared<Gosu::Image>(spikessrt), 1, 1);
	ispikes1 = erstelle_Objekt_damage_ptr(76, 19, -750, -60, 300, ispikes0, std::make_shared<Gosu::Image>(spikessrt), 1, 1);
	ispikes2 = erstelle_Objekt_damage_ptr(76, 19, 1500, -400, 300, ispikes1, std::make_shared<Gosu::Image>(spikessrt), 1, 1);
	ispikes3 = erstelle_Objekt_damage_ptr(76, 19, 3300, 200, 300, ispikes2, std::make_shared<Gosu::Image>(spikessrt), 1, 1);
	SpikesA11 = erstelle_Objekt_damage_ptr(76, 19, -76, -484, 300, ispikes2, std::make_shared<Gosu::Image>(spikessrt), 1, 1);
	SpikesA12 = erstelle_Objekt_damage_ptr(76, 19, -152, -484, 300, SpikesA11, std::make_shared<Gosu::Image>(spikessrt), 1, 1);
	SpikesA13 = erstelle_Objekt_damage_ptr(76, 19, -228, -484, 300, SpikesA12, std::make_shared<Gosu::Image>(spikessrt), 1, 1);
	SpikesA14 = erstelle_Objekt_damage_ptr(76, 19, -304, -484, 300, SpikesA13, std::make_shared<Gosu::Image>(spikessrt), 1, 1);
	SpikesA15 = erstelle_Objekt_damage_ptr(76, 19, -380, -484, 300, SpikesA14, std::make_shared<Gosu::Image>(spikessrt), 1, 1);
	SpikesA16 = erstelle_Objekt_damage_ptr(76, 19, -456, -484, 300, SpikesA15, std::make_shared<Gosu::Image>(spikessrt), 1, 1);
	SpikesA17 = erstelle_Objekt_damage_ptr(76, 19, -532, -484, 300, SpikesA16, std::make_shared<Gosu::Image>(spikessrt), 1, 1);
	elem_O_d = std::make_shared<Objekt_damage>();
	listenstart_O_d = SpikesA17; //Hier immer letztes Element hinschreiben



};

void GameState::Rolle(bool end, bool death) //entrollen der schriftrolle
{
	if (end && death || !end)
	{
		i = i - 1;
		if (i == s)
		{
			VerlorenSound.play(0.1);
		}
		if (i > (3 * s / 4)) {
			Scroll.draw_rot(400, 174, 450.0, 0.0, 0.5, 0.5);
		}
		else if (i <= (3 * s / 4) && i > (s / 2))
		{
			Scroll2.draw_rot(400, 243, 450.0, 0.0, 0.5, 0.5);
		}
		else if (i <= (s / 2) && i > (s / 4))
		{
			Scroll3.draw_rot(400, 291, 450.0, 0.0, 0.5, 0.5);
		}
		else if (i <= (s / 4))
		{
			if (!end)
			{
				GameOver.draw_rot(400, 300, 450.0, 0.0, 0.5, 0.5);
			}
			else if (end && death) {
				Endscreen.draw_rot(400, 300, 450.0, 0.0, 0.5, 0.5);
				gamefinished = true;
			}
		}
	}
}


void GameState::SpielerModelupdate()
{
	elem_P_d = listenstart_P_d;
	while (elem_P_d->next != nullptr)	//Alle Grafiken deaktivieren
	{
		elem_P_d->active = false;
		elem_P_d = elem_P_d->next;
	}
	t = (t == 0) ? IMAGE_CYCLE_TIME : t - 1;	//Danke Gabriel :D
	if (attack)
	{
		if (facing_l && t < (IMAGE_CYCLE_TIME / 2))
		{
			iplayertempl1A->active = true;
		}
		else if (facing_l && t >= (IMAGE_CYCLE_TIME / 2))
		{
			iplayertempl2A->active = true;
		}
		else if (facing_r && t < (IMAGE_CYCLE_TIME / 2))
		{
			iplayertempr1A->active = true;
		}
		else if (facing_r && t >= (IMAGE_CYCLE_TIME / 2))
		{
			iplayertempr2A->active = true;
		}
	}
	else {
		if (facing_l && t < (IMAGE_CYCLE_TIME / 2))
		{
			iplayertempl1->active = true;
		}
		else if (facing_l && t >= (IMAGE_CYCLE_TIME / 2))
		{
			iplayertempl2->active = true;
		}
		else if (facing_r && t < (IMAGE_CYCLE_TIME / 2))
		{
			iplayertempr1->active = true;
		}
		else if (facing_r && t >= (IMAGE_CYCLE_TIME / 2))
		{
			iplayertempr2->active = true;
		}
	}
	if (t < (IMAGE_CYCLE_TIME / 2)) 
	{
		this->Altklausur->image = std::make_shared<Gosu::Image>(Altklausur0);
	}
	if (t >= (IMAGE_CYCLE_TIME / 2))
	{
		this->Altklausur->image = std::make_shared<Gosu::Image>(Altklausur1);
	}
}

std::vector<GameState::Laser> GameState::getLaserVektor()
{
	return this->Laservektor;
}
void GameState::Lasershooter()
{
	if (attack)
	{
		tl = (tl == 0) ? LASER_SHOOTING_TIMER : tl - 1;	//Danke Gabriel :D
		if (tl == LASER_SHOOTING_TIMER - 1)
		{
			if (facing_r)
			{
				Laservektor.push_back(erstelle_Laser((35 + p1->player_start_x), p1->player_y + 19, facing_r));
			}
			else {
				Laservektor.push_back(erstelle_Laser((p1->player_start_x), p1->player_y + 19, facing_r));
			}
			TestSound.play();
		}
	}
	else {
		tl = LASER_SHOOTING_TIMER;
	}
	for (size_t i = 0; i < Laservektor.size(); i++)
	{
		Laservektor.at(i).posx = Laservektor.at(i).posx + (p1->player_x_alt - p1->player_x);
		Laservektor.at(i).posy = Laservektor.at(i).starty - (p1->player_y - p1->player_start_y);
		if (Laservektor.at(i).direction_right)
		{
			Laservektor.at(i).posx = Laservektor.at(i).posx + LASER_SPEED;
		}
		else {
			Laservektor.at(i).posx = Laservektor.at(i).posx - LASER_SPEED;
		}
		if (distance_from_player(i) > LASER_RENDERDISTANCE)
		{
			Laservektor.erase(Laservektor.begin() + i);
		}
	}
	std::shared_ptr<GameState::Objekt_fest> elem_O_f = listenstart_O_f;
	bool crash = false;
	for (size_t i = 0; i < Laservektor.size(); i++)	//Zweite schleife, sonst wird auf evtl. gel�schtes zugegriffen...
	{
		elem_O_f = listenstart_O_f;
		crash = false;

		while (elem_O_f->next != nullptr && crash == false)
		{
			if (elem_O_f->nohitbox == false)
			{
				if (Laservektor.at(i).posx < (elem_O_f->posx + elem_O_f->breite - 1) && (Laservektor.at(i).posx + 25) >(elem_O_f->posx))
				{
					if ((Laservektor.at(i).posy + 1) > elem_O_f->posy && (Laservektor.at(i).posy) < (elem_O_f->posy + elem_O_f->hoehe - 1))
					{
						//Theoretisch muss hier jede Laser - Objekt - Kollision behandelt werden
						Laservektor.erase(Laservektor.begin() + i);
						crash = true;	//Setzen des bools, um weitere ausf�hrung der Schleife zu verhindern (Sonst wird auf gel�schtes zugegriffen...)
						if (elem_O_f->destroyable)
						{
							switch (elem_O_f->destroy_state)
							{
							case 0:
								elem_O_f->destroy_state = 1;
								elem_O_f->image = std::make_shared<Gosu::Image>(Wand_destr_1);
								break;
							case 1:
								elem_O_f->destroy_state = 2;
								elem_O_f->image = std::make_shared<Gosu::Image>(Wand_destr_2);
								break;
							case 2:
								elem_O_f->destroy_state = 3;
								elem_O_f->image = std::make_shared<Gosu::Image>(Wand_destr_3);
								break;
							case 3:
								elem_O_f->destroy_state = 4;
								elem_O_f->startx = 100000;
								elem_O_f->starty = 100000;
								elem_O_f->posx = 100000;
								elem_O_f->posy = 100000;
								break;
							default:
								break;
							}
						}
					}
				}
			}
			elem_O_f = elem_O_f->next;
		}
		if (!crash)
		{
			if (Laservektor.at(i).posx < (iGegner->posx + iGegner->breite - 1) && (Laservektor.at(i).posx + 25) >(iGegner->posx))		//Und jz noch Kollision mir Mr. Coco pr�fen
			{
				if ((Laservektor.at(i).posy + 1) > iGegner->posy && (Laservektor.at(i).posy) < (iGegner->posy + iGegner->hoehe - 1))
				{
					Laservektor.erase(Laservektor.begin() + i);
					health_gegner = health_gegner - 1;
				}
			}
		}
	}
}


Spieler* GameState::get_Spieler()
{
	return this->p1;
}

Spieler* GameState::get_Gegner()
{
	return this->g1;
}

std::shared_ptr<GameState::Objekt_fest> GameState::erstelle_Objekt_fest_ptr(double breite, double hoehe, double posx, double posy, double posz, std::shared_ptr<GameState::Objekt_fest> next, std::shared_ptr<Gosu::Image> image, double scale_x, double scale_y, bool hit, bool destr, int destroy_state)
{
	GameState::Objekt_fest temp;
	//double breitetemp2 = (double)image->width();
	temp.breite = breite * scale_x;
	//temp.breite = breitetemp2;
	temp.hoehe = hoehe * scale_y;
	//temp.hoehe = (double)image->height();
	temp.posx = posx;
	temp.posy = posy;
	temp.startx = posx;
	temp.starty = posy;
	temp.posz = posz;
	temp.nohitbox = hit;

	temp.next = next;
	temp.image = image;
	temp.scale_x = scale_x;
	temp.scale_y = scale_y;
	temp.destroyable = destr;
	temp.destroy_state = destroy_state;
	return std::make_shared<GameState::Objekt_fest>(temp);
}

std::shared_ptr<GameState::Player_data> GameState::erstelle_Player_data_ptr(double breite, double hoehe, std::shared_ptr<GameState::Player_data> next, std::shared_ptr<Gosu::Image> image, bool active, double scale_x, double scale_y)
{
	GameState::Player_data temp;
	//double breitetemp2 = (double)image->width();
	temp.breite = breite * scale_x;
	//temp.breite = breitetemp2;
	temp.hoehe = hoehe * scale_y;
	//temp.hoehe = (double)image->height();
	temp.next = next;
	temp.image = image;
	temp.scale_x = scale_x;
	temp.scale_y = scale_y;
	temp.active = active;
	return std::make_shared<GameState::Player_data>(temp);
}

std::shared_ptr<GameState::Objekt_damage> GameState::erstelle_Objekt_damage_ptr(double breite, double hoehe, double posx, double posy, double posz, std::shared_ptr<GameState::Objekt_damage> next, std::shared_ptr<Gosu::Image> image, double scale_x, double scale_y, bool hit)
{
	GameState::Objekt_damage temp;
	//double breitetemp2 = (double)image->width();
	temp.breite = breite * scale_x;
	//temp.breite = breitetemp2;
	temp.hoehe = hoehe * scale_y;
	//temp.hoehe = (double)image->height();
	temp.posx = posx;
	temp.posy = posy;
	temp.startx = posx;
	temp.starty = posy;
	temp.posz = posz;
	temp.nohitbox = hit;
	temp.next = next;
	temp.image = image;
	temp.scale_x = scale_x;
	temp.scale_y = scale_y;
	return std::make_shared<GameState::Objekt_damage>(temp);
}

GameState::Laser GameState::erstelle_Laser(double x, double y, bool d_r)
{
	GameState::Laser temp;
	temp.posx = x;
	temp.posy = y;
	temp.startx = x;
	temp.starty = y;
	temp.direction_right = d_r;
	return temp;
}


double GameState::distance_from_player(std::shared_ptr<GameState::Objekt_fest> o2)
{
	return sqrt(pow((this->p1->player_x - o2->startx), 2) + pow((this->p1->player_y - o2->starty), 2));
}
double GameState::distance_from_player(std::shared_ptr<GameState::Objekt_damage> o2)
{
	return sqrt(pow((this->p1->player_x - o2->startx), 2) + pow((this->p1->player_y - o2->starty), 2));
}
double GameState::distance_from_player(int vektorlisteni)
{
	return sqrt(pow((this->p1->player_start_x - Laservektor.at(vektorlisteni).posx), 2) + pow((this->p1->player_start_y - (Laservektor.at(vektorlisteni).posy)), 2));
}
bool GameState::kollision_rechts(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Player_data> iplayertemp)//, std::shared_ptr<Spieler> p1)//std::shared_ptr<GameState::Objekt_fest> listenstart_O_f, Spieler p1, std::shared_ptr<GameState::Player_data> iplayertemp)
{
	std::shared_ptr<GameState::Objekt_fest> elem_O_f = this->listenstart_O_f;
	//std::shared_ptr<GameState::Objekt_fest> elem_O_f = listenstart;
	bool tmp = false;
	//auto elem_O_f = GameState::get_listenstart_O_f();   //listenstart_O_f; //Hier immer letztes Element hinschreiben!
	while (elem_O_f->next != nullptr)
	{
		if (distance_from_player(elem_O_f) < 5000 && elem_O_f->nohitbox == false)
		{
			if ((this->p1->player_x + iplayertemp->breite + 3 + this->p1->speedPlayer) > elem_O_f->startx && (this->p1->player_x) < (elem_O_f->startx + elem_O_f->breite) - 5)
			{
				if ((this->p1->player_y + iplayertemp->hoehe) > elem_O_f->starty && (this->p1->player_y) < (elem_O_f->starty + elem_O_f->hoehe))
				{
					tmp = true;
				}
			}
		}
		elem_O_f = elem_O_f->next;
	}
	return tmp;
}
bool GameState::kollision_links(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Player_data> iplayertemp)//, Spieler* p1)
{
	std::shared_ptr<GameState::Objekt_fest> elem_O_f = listenstart;
	bool tmp = false;
	//elem_O_f = listenstart_O_f; //Hier immer letztes Element hinschreiben!
	while (elem_O_f->next != nullptr)
	{
		if (distance_from_player(elem_O_f) < 5000 && elem_O_f->nohitbox == false)
		{
			if ((this->p1->player_x - (3 + this->p1->speedPlayer)) < (elem_O_f->startx + elem_O_f->breite) && (this->p1->player_x + iplayertemp->breite) > (elem_O_f->startx + 5))
			{
				if ((this->p1->player_y + iplayertemp->hoehe) > elem_O_f->starty && (this->p1->player_y) < (elem_O_f->starty + elem_O_f->hoehe))
				{
					tmp = true;
				}
			}
		}
		elem_O_f = elem_O_f->next;
	}
	return tmp;
}
bool GameState::kollision_oben(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Player_data> iplayertemp)//, Spieler* p1)
{
	std::shared_ptr<GameState::Objekt_fest> elem_O_f = listenstart;
	bool tmp = false;
	//elem_O_f = listenstart_O_f; //Hier immer letztes Element hinschreiben!
	while (elem_O_f->next != nullptr)
	{
		if (distance_from_player(elem_O_f) < 5000 && elem_O_f->nohitbox == false)
		{
			if (this->p1->player_x < (elem_O_f->startx + elem_O_f->breite) && (this->p1->player_x + iplayertemp->breite) >(elem_O_f->startx))
			{
				if ((this->p1->player_y + iplayertemp->hoehe) > elem_O_f->starty && (this->p1->player_y - (5 + abs(this->p1->speedPlayerY))) < (elem_O_f->starty + elem_O_f->hoehe))
				{
					tmp = true;
				}
			}
		}
		elem_O_f = elem_O_f->next;
	}
	return tmp;
}
bool GameState::kollision_unten(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Player_data> iplayertemp)//, Spieler* p1)
{
	std::shared_ptr<GameState::Objekt_fest> elem_O_f = listenstart;
	bool tmp = false;
	//elem_O_f = listenstart_O_f; //Hier immer letztes Element hinschreiben!
	while (elem_O_f->next != nullptr)
	{
		if (distance_from_player(elem_O_f) < 5000 && elem_O_f->nohitbox == false)
		{
			if (this->p1->player_x < (elem_O_f->startx + elem_O_f->breite) && (this->p1->player_x + iplayertemp->breite) >(elem_O_f->startx))
			{
				if ((this->p1->player_y + iplayertemp->hoehe + 5 + abs(this->p1->speedPlayerY)) > elem_O_f->starty && (this->p1->player_y) < (elem_O_f->starty + elem_O_f->hoehe))
				{
					tmp = true;
				}
			}
		}
		elem_O_f = elem_O_f->next;
	}
	return tmp;
}
bool GameState::kollsion_damage(std::shared_ptr<GameState::Objekt_damage> listenstart, std::shared_ptr<GameState::Player_data> iplayertemp)
{
	std::shared_ptr<GameState::Objekt_damage> elem_O_d = listenstart;
	bool tmp = false;
	while (elem_O_d->next != nullptr)
	{
		if (distance_from_player(elem_O_d) < 5000 && elem_O_d->nohitbox == false)
		{
			if (this->p1->player_x < (elem_O_d->startx + elem_O_d->breite - 1) && (this->p1->player_x + iplayertemp->breite - 1) >(elem_O_d->startx))
			{
				if ((this->p1->player_y + iplayertemp->hoehe - 1) > elem_O_d->starty && (this->p1->player_y) < (elem_O_d->starty + elem_O_d->hoehe - 1))
				{
					tmp = true;
				}
			}
		}
		elem_O_d = elem_O_d->next;
	}
	return tmp;
}

bool GameState::kollision_rechts_gegner(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Objekt_damage> iplayertemp)//, std::shared_ptr<Spieler> p1)//std::shared_ptr<GameState::Objekt_fest> listenstart_O_f, Spieler p1, std::shared_ptr<GameState::Player_data> iplayertemp)
{
	std::shared_ptr<GameState::Objekt_fest> elem_O_f = this->listenstart_O_f;
	//std::shared_ptr<GameState::Objekt_fest> elem_O_f = listenstart;
	bool tmp = false;
	//auto elem_O_f = GameState::get_listenstart_O_f();   //listenstart_O_f; //Hier immer letztes Element hinschreiben!
	while (elem_O_f->next != nullptr)
	{
		//if (distance_from_player(elem_O_f) < 5000 && elem_O_f->nohitbox == false)
		//{
			if ((this->g1->player_x + iplayertemp->breite - 25) > elem_O_f->startx && (this->g1->player_x) < (elem_O_f->startx + elem_O_f->breite) - 5)
			{
				if ((this->g1->player_y + iplayertemp->hoehe) > elem_O_f->starty && (this->g1->player_y) < (elem_O_f->starty + elem_O_f->hoehe))
				{
					tmp = true;
				}
			}
		//}
		elem_O_f = elem_O_f->next;
	}
	return tmp;
}
bool GameState::kollision_links_gegner(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Objekt_damage> iplayertemp)//, Spieler* p1)
{
	std::shared_ptr<GameState::Objekt_fest> elem_O_f = listenstart;
	bool tmp = false;
	//elem_O_f = listenstart_O_f; //Hier immer letztes Element hinschreiben!
	while (elem_O_f->next != nullptr)
	{
		//if (distance_from_player(elem_O_f) < 5000 && elem_O_f->nohitbox == false)
		//{
			if ((this->g1->player_x - (3 + this->g1->speedPlayer)) < (elem_O_f->startx + elem_O_f->breite) && (this->g1->player_x + iplayertemp->breite) > (elem_O_f->startx + 5))
			{
				if ((this->g1->player_y + iplayertemp->hoehe) > elem_O_f->starty && (this->g1->player_y) < (elem_O_f->starty + elem_O_f->hoehe))
				{
					tmp = true;
				}
			}
		//}
		elem_O_f = elem_O_f->next;
	}
	return tmp;
}
bool GameState::kollision_oben_gegner(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Objekt_damage> iplayertemp)//, Spieler* p1)
{
	std::shared_ptr<GameState::Objekt_fest> elem_O_f = listenstart;
	bool tmp = false;
	//elem_O_f = listenstart_O_f; //Hier immer letztes Element hinschreiben!
	while (elem_O_f->next != nullptr)
	{
		//if (distance_from_player(elem_O_f) < 5000 && elem_O_f->nohitbox == false)
		//{
			if (this->g1->player_x < (elem_O_f->startx + elem_O_f->breite) && (this->g1->player_x + iplayertemp->breite) >(elem_O_f->startx))
			{
				if ((this->g1->player_y + iplayertemp->hoehe) > elem_O_f->starty && (this->p1->player_y - 5) < (elem_O_f->starty + elem_O_f->hoehe))
				{
					tmp = true;
				}
			}
		//}
		elem_O_f = elem_O_f->next;
	}
	return tmp;
}
bool GameState::kollision_unten_gegner(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Objekt_damage> iplayertemp)//, Spieler* p1)
{
	std::shared_ptr<GameState::Objekt_fest> elem_O_f = listenstart;
	bool tmp = false;
	//elem_O_f = listenstart_O_f; //Hier immer letztes Element hinschreiben!
	while (elem_O_f->next != nullptr)
	{
		//if (distance_from_player(elem_O_f) < 5000 && elem_O_f->nohitbox == false)
		//{
			if (this->g1->player_x < (elem_O_f->startx + elem_O_f->breite) && (this->g1->player_x + iplayertemp->breite) >(elem_O_f->startx))
			{
				if ((this->g1->player_y + iplayertemp->hoehe + 25) > elem_O_f->starty && (this->g1->player_y) < (elem_O_f->starty + elem_O_f->hoehe))
				{
					tmp = true;
				}
			}
		//}
		elem_O_f = elem_O_f->next;
	}
	return tmp;
}