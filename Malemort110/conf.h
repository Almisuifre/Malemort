//Paramètres généraux
#define NB_ZA 7  //Nombre de zone d'arrets

//Temporisaion d'arrêt des feux (Carré d'arrêt)
#define tempoFeuOff_ZA0 5000 //ZA0
#define tempoFeuOff_ZA1 4000 //ZA1
#define tempoFeuOff_ZA2 7000 //ZA2
#define tempoFeuOff_ZA3 7000 //ZA3
#define tempoFeuOff_ZA4 5000 //ZA4
#define tempoFeuOff_ZA5 2000 //ZA5
#define tempoFeuOff_ZA6 2000 //ZA6

//Temporisation de mise en départ du train
#define tempoArretGare_ZA0 1000 //ZA0
#define tempoArretGare_ZA1 1500 //ZA1
#define tempoArretGare_ZA2 1000 //ZA2
#define tempoArretGare_ZA3 1000 //ZA3
#define tempoArretGare_ZA2ZA3 1000 //ZA2 et ZA3
#define tempoArretGare_ZA4 1500 //ZA4
#define tempoArretGare_ZA5 1500 //ZA5
#define tempoArretGare_ZA6 1500 //ZA6
#define tempoArretGare_ZA5ZA6 1500 //ZA5 et ZA6

//Zone d'arret 0
#define ZA0R 22 //<- Lecture (Read)
#define ZA0W 23 //-> Écriture (Write)

//Zone d'arret 1
#define ZA1R 24 //<- Lecture (Read)
#define ZA1W 25 //-> Écriture (Write)

//Zone d'arret 2
#define ZA2R 26 //<- Lecture (Read)
#define ZA2W 27 //-> Écriture (Write)

//Zone d'arret 3
#define ZA3R 28 //<- Lecture (Read)
#define ZA3W 29 //-> Écriture (Write)

//Zone d'arret 4
#define ZA4R 30 //<- Lecture (Read)
#define ZA4W 31 //-> Écriture (Write)

//Zone d'arret 5
#define ZA5R 32 //<- Lecture (Read)
#define ZA5W 33 //-> Écriture (Write)

//Zone d'arret 6
#define ZA6R 34 //<- Lecture (Read)
#define ZA6W 35 //-> Écriture (Write)

//CarteAiguillageTulle
#define AIG_Vers_za2 48
#define AIG_Vers_za3 49

//CarteAiguillageMalemort
#define AIG_Vers_za5 50
#define AIG_Vers_za6 51

//Carte Sens et marche
#define Direction 52  //-> Sens
#define Autorisation 53 //-> Marche

//LCD
#define RS    2
#define E     3
#define D4    11
#define D5    10
#define D6    9
#define D7    8

//Actions
#define Tulle HIGH  //Sens vers Tulle
#define Brive LOW  //Sens vers Brive
#define SensStop LOW //Sens stop

#define Marche HIGH //Mise en marche
#define Arret LOW  //Mise en arret

#define ZA0 0  //ZA0
#define ZA1 1  //ZA1
#define ZA2 2  //ZA2
#define ZA3 3  //ZA3
#define ZA4 4  //ZA4
#define ZA5 5  //ZA5
#define ZA6 6  //ZA6

#define AigTo_ZA2 2  //Aiguille vers ZA2
#define AigTo_ZA3 3  //Aiguille vers ZA3
#define AigTo_ZA5 5  //Aiguille vers ZA5
#define AigTo_ZA6 6  //Aiguille vers ZA5

/* --- ZONE D'ARRET DES TRAINS / CANTONS -- */
boolean tZoneArret[NB_ZA];  //Tableau des état des zones d'arrets

uint8_t seqCurrent = 111;           //Séquence courrente
boolean currentSeqChanged = false;  //Flag séquence changé

int etatAiguilleTulle = 0;  //Etat de l'aiguille Tulle Inconnu
boolean etatAiguilleTulleChanged = false; //Flag aiguille tulle
boolean flagTunnel = true; //Flag de sécurité tunnel
