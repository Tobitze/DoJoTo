class Spieler // Doris ding Anfang :D
{
public:
	double player_x;// Bewegung x-Achse
	double player_y;// Bewegung y-achse
	
	double player_a_x;// Geschwindigkeit x-richtung
	const double player_v_xmax = 3; // max geschwindigket x
	
	double player_a_y;// Geschwindigkeit y-richtung
	const double player_v_ymax = 3; // max geschwindigkeit y
	
	const double player_g = 9.81;// gravitationskonstante


	int sprung_t; // zählt die zeit des sprungs
	int player_t_x_a; // zeit, die in x beschleunigt wird
	int player_t_x_d;
	
	//Konstruktor
	Spieler(){
		this->player_x = 300;
		this->player_y = 500;
	}
		//player Bewegung
		// bewegung in x richtung 
	
	
	double player_beschleunigung(double bx,double tx, const double txm) {
		double ax;
		if (tx < txm) {
			ax = bx * (tx / 5);
		}
		else {
			ax = bx * (txm / 5);
		}
		return ax;
		//std::cout << ax << std::endl;
	};

	// sprung timer - zählt, wie lange der player springt.
	int sprung_dauer(bool y) {
		while (y = true) {
			switch (y) {
			case true:
				return this->sprung_t = this->sprung_t + 1;;
				break;
			case false:
				return this->sprung_t = 0;
				break;
			default:
				break;
			};

		}
	};
	// bewegug in y richtung
	double player_sprung(double x, double y, double v, double t, bool xx) {
		double zeit_sprung = t;

		for (double u; u < zeit_sprung; u++) { // berechnen von x-Koordinaten derPunkte der Wurfparabel 
			switch (xx) {
			case true:
				return this->player_a_x == 0;//this->beschleunigung()  ;// berechnen der x-Geschwinigkeit -> koordinate = vx(t) / t
				break;
			case false:
				return this->player_a_x == 0;
				break;
			default:
				break;
			};
		};
	};
}; // Doris ding ende :D