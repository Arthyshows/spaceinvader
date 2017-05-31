#include "graphics.h"

	typedef int MONSTRE;
	
	typedef struct {
		POINT coin;
		MONSTRE T[10][5];
	}	ESQUADE;
	
	typedef struct {
		POINT position_tir;
		int verification;
	}	TIR;
	
	typedef struct {
		TIR T1;
		TIR T2;
		ESQUADE M;
		POINT joueur;
	}	JEU;

	#define MORT 0
	#define NIVEAU1 1
	#define NIVEAU2 2
	#define TAILLE_FENETRE 300
	
	
// Définition 
JEU init_jeu(JEU J, int difficulte){
	int i, j;
	for(i=0; i<10; i++){
		for(j=0; j<5;j++){
			J.M.T[i][j] = difficulte;
			}
		}
	J.T1.position_tir.x = -TAILLE_FENETRE;
	J.T1.position_tir.y = 0;
	J.T1.verification = 0;
	J.M.coin.y = TAILLE_FENETRE - TAILLE_FENETRE/30;
	J.M.coin.x = TAILLE_FENETRE/9;
	J.joueur.x = TAILLE_FENETRE/2;
	return J;
	}

void affiche_joueur(JEU J){
	POINT pos_J;
	pos_J.x = J.joueur.x - TAILLE_FENETRE/17.5 ;
	pos_J.y = TAILLE_FENETRE/10;
	aff_pol("^", TAILLE_FENETRE/7.5, pos_J, blue);	
	}

void affiche_menu(){
		fill_screen(noir);
		
		POINT p1 = {73,250};
		POINT rec1 = {30,250};
		POINT rec2 = {270,200};
		draw_fill_rectangle(rec1,rec2,gris);
		aff_pol("Difficulte",35,p1,white);
		
		POINT p2_1= {35,132};
		POINT rec2_11 = {30,130};
		POINT rec2_12 = {150,100};
		draw_fill_rectangle(rec2_11,rec2_12,blue);
		aff_pol("Niveau 1",25,p2_1,white);
		
		POINT p2_2= {155,132};
		POINT rec2_21 = {150,130};
		POINT rec2_22 = {270,100};
		draw_fill_rectangle(rec2_21,rec2_22,red);
		aff_pol("Niveau 2",25,p2_2,white);		
				
	}

void affiche_tir(JEU J){
	J.T1.position_tir.x = J.T1.position_tir.x - TAILLE_FENETRE/60;
	aff_pol("|", TAILLE_FENETRE/15, J.T1.position_tir, gold);
	}
	
void affiche_monstres(int i, int j, POINT P){
	POINT position_monstre, test;
	position_monstre.x = P.x + i*TAILLE_FENETRE/12 - TAILLE_FENETRE/30;
	position_monstre.y = P.y + j*TAILLE_FENETRE/12 + TAILLE_FENETRE/30;
	test.x = P.x + i*TAILLE_FENETRE/12;
	test.y = P.y + j*TAILLE_FENETRE/12;
	affiche_image("images/MonstreNiv1.bmp", position_monstre, 100, 100);
	draw_circle(test, TAILLE_FENETRE/30 , red);
	}
	
void affiche_esquade(JEU J){
	int i, j;
	for (i = 0; i < 10; i++){
		for (j = 0; j < 5; j++){
			if (J.M.T[i][j] != MORT){
				affiche_monstres(i, j, J.M.coin);
				}
			}
		}
	}
	
BOOL choisir_difficulte(){		
		while(1){
			POINT click = wait_clic();
			
			if (click.x > 150 && click.x < 270 && click.y > 100 && click.y < 130){
				return NIVEAU2;
			}else{
				if (click.x > 30 && click.x < 150 && click.y > 100 && click.y < 130){
					return NIVEAU1;
				}
			}
		}
	}

JEU tir_joueur(JEU J){
	int espace;
	espace = touche_espace();
	if (J.T1.verification == 0){
		if (espace > 0){
			J.T1.position_tir.x = J.joueur.x;
			J.T1.position_tir.y = TAILLE_FENETRE/6;
			J.T1.verification = 1;
			}
		}
	return J;
	}

int deplacement_joueur(JEU J){
	int distance_deplacement;
	POINT fleche;
	distance_deplacement = 0;
	fleche = get_arrow();
	if (fleche.x < 0){
		if (J.joueur.x > 0){
			distance_deplacement = -TAILLE_FENETRE/60;
			}
		}
	if (fleche.x > 0){
		if (J.joueur.x < TAILLE_FENETRE){
			distance_deplacement = TAILLE_FENETRE/60;
			}
		}
	return distance_deplacement;
	}

JEU deplacement_tir(JEU J, int compteur){
	int modulo;
	modulo = compteur % 3;
	if (J.T1.verification == 1){
		if (modulo == 0){
			J.T1.position_tir.y = J.T1.position_tir.y + TAILLE_FENETRE/15;
			}
		}else{
			J.T1.position_tir.x = -TAILLE_FENETRE;
			}
	if (J.T1.position_tir.y > TAILLE_FENETRE + TAILLE_FENETRE/15){
		J.T1.verification = 0;
		}
	return J;
	}

JEU deplacement_esquade(JEU J, int compteur){
	int modulo;
	modulo = compteur % 120;
	if (modulo == 20 || modulo == 80){
		J.M.coin.y = J.M.coin.y - TAILLE_FENETRE/30;
		}
	if (modulo == 0 || modulo == 100){
		J.M.coin.x = J.M.coin.x - TAILLE_FENETRE/30;
		}
	if (modulo == 40 || modulo == 60){
		J.M.coin.x = J.M.coin.x + TAILLE_FENETRE/30;
		}
	return J;
	}

JEU tue_monstre(JEU J, int difficulte){
	int i, j; for (i = 0; i<10; i++){ for (j = 0; j<5; j++){
			if (J.T1.position_tir.x > J.M.coin.x - TAILLE_FENETRE/25 + i*TAILLE_FENETRE/12 && J.T1.position_tir.x < J.M.coin.x + TAILLE_FENETRE/25 + i*TAILLE_FENETRE/12){
				if (J.T1.position_tir.y > J.M.coin.y - TAILLE_FENETRE/25 + j*TAILLE_FENETRE/12 && J.T1.position_tir.y < J.M.coin.y + TAILLE_FENETRE/25 + j*TAILLE_FENETRE/12){
					if (difficulte == NIVEAU1){
						if (J.M.T[i][j] == 1){
							J.M.T[i][j] = 0;
							J.T1.verification = 0;
						}
					} else {
						if (J.M.T[i][j] == 2){
							 J.M.T[i][j] = 1;
							 J.T1.verification = 0;
						} else {
						if (J.M.T[i][j] == 1){
							J.M.T[i][j] = 0;
							J.T1.verification = 0;
								}
							}
						}				
					}
				}
			}
		}
		return J;
	}

BOOL jeu_fini(JEU J, int difficulte){
	int i,j,nombre_monstres;
	nombre_monstres = 0;
	for (i = 0; i < 10; i++){
		for (j = 0; j < 5; j++){
			if (J.M.T[i][j] == difficulte){
				nombre_monstres = nombre_monstres + 1;
				if (J.M.coin.y + i*TAILLE_FENETRE/12 - TAILLE_FENETRE/30 < 10)
					return true;
				}
			}
		}
	if (nombre_monstres == 0){
		return true;
		}
	return false;
	}
	
void fin_jeu(){
	fill_screen(black);
	POINT P; 
	P.x = TAILLE_FENETRE/2 - largeur_texte("GAME OVER", TAILLE_FENETRE/10)/2;
	P.y = TAILLE_FENETRE/2 + hauteur_texte("GAME OVER", TAILLE_FENETRE/10)/2;
	aff_pol("GAME OVER", TAILLE_FENETRE/10, P, red);
	}


int main(){
	init_graphics(TAILLE_FENETRE,TAILLE_FENETRE);
	
	affiche_menu();
	int difficulte = choisir_difficulte();	
	
	int compteur;
	JEU J;
	J = init_jeu(J, difficulte);
	compteur = 0;
	affiche_auto_off();
	clavier_souris_auto_off();
	while (!jeu_fini(J, difficulte)){									//vérifie si tous les monstres sont morts et si le joueur est mort
		fill_screen(black);
		
		update_clavier_souris();
		
		J.joueur.x = J.joueur.x + deplacement_joueur(J);	//change la position du joueur sur l'axe x
		J = deplacement_tir(J, compteur);					//vérifie si il y a un tir et change la position du tir ou permet au joueur de tirer
		J = deplacement_esquade(J, compteur);				//change la position de tous les monstres
		J = tir_joueur(J);									//crée un tir si le joueur appuie sur la fleche du haut
		
		J = tue_monstre(J, difficulte);									//vérifie si le tir a touché un des monstres et change le tableau si oui
		
		affiche_joueur(J);									//affiche le joueur à sa position
		affiche_tir(J);										//affiche le tir à sa position
		affiche_esquade(J);									//affiche les monstres
		affiche_all();
		
		attendre(30);
		compteur ++;
		}
	fin_jeu();
	wait_escape();
	exit(0);
}
