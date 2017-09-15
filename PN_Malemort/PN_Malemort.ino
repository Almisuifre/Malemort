/*
   Reseau MALEMORT
   GESTION DES PN

*/

/* ** CONFIGURATIONS ** */
#define detect_1   2    //D2 (INPUT) detection 1
#define detect_2   3    //D3 (INPUT) detection 2
#define detect_3   4    //D4 (INPUT) detection 3
#define btnConfig  A0   //A0 (INPUT) CONFIG
#define btnMove    A1   //A1 (INPUT) Transport
#define feuPN_1    9    //D9 (OUTPUT) Feu PN 1
#define feuPN_2    10   //D10 (OUTPUT) Feu PN 2
#define sensPN_1   11   //D11 (OUTPUT) SENS PN 1
#define sensPN_2   12   //D12 (OUTPUT) SENS PN 2

/* ** VARIABLES ** */
int btnConf = 0;
int btnMoveTo = 0;
boolean detection_1 = false;
boolean detection_2 = false;
boolean detection_3 = false;

boolean waitEndSeq = false;

unsigned long passages_A = 0;
unsigned long passages_B = 0;

boolean initPN = false;
int currentSeq = 0;

long previousMillis_A = 0;
unsigned long currentMillis_A =0;
boolean led_PN1_state = false;
boolean start_Led_PN1 = false;

long previousMillis_B = 0;
unsigned long currentMillis_B =0;
boolean led_PN2_state = false;
boolean start_Led_PN2 = false;


void setup() {
  //INPUT
  pinMode(detect_1, INPUT);   //Detection 1
  pinMode(detect_2, INPUT);   //Detection 2
  pinMode(detect_3, INPUT);   //Detection 3
  pinMode(btnConfig, INPUT);  //Configuration
  pinMode(btnMove, INPUT);    //Mode transport

  //OUTPUT
  pinMode(feuPN_1, OUTPUT);   //Feu PN 1
  pinMode(feuPN_2, OUTPUT);   //Feu PN 2
  pinMode(sensPN_1, OUTPUT);  //Sens PN 1
  pinMode(sensPN_2, OUTPUT);  //Sens PN 2

  //SERIAL
  Serial.begin(9600);
}

void loop() {
  capture();
  
  //Bouton transport
  if((btnMoveTo > 500) && (btnMoveTo < 520)) {
    //Mode fonctionnel : Automate active
    
    //Bouton mode normal / mode ralonge
    if((btnConf > 500) && (btnConf < 520)) {
      //Mode normal
      seqNormale();
      actionPN();
    }
    else if ((btnConf > 700) && (btnConf < 710)) {
      //Mode ralonge
      seqRalonge();
      actionPN();
    }
    waitEndSequence(500); //Attendre 500 passages
    clignotementFeuPN1(start_Led_PN1);
    clignotementFeuPN2(start_Led_PN2);
  }
  else if ((btnMoveTo > 700) && (btnMoveTo < 710)) {
    //Mode transport : Automate désactive
    modeTransport();
    currentSeq = 0;
  }
}

void capture() {
  //Recupere l'etat des boutons
  btnConf = analogRead(btnConfig);
  btnMoveTo = analogRead(btnMove);
  detection_1 = digitalRead(detect_1);
  detection_2 = digitalRead(detect_2);
  detection_3 = digitalRead(detect_3);
}

//Sequence normale
void seqNormale() {
  initBarrieres(); //Initialisation des barrieres
  dirBriveToTulle("NORMALE");  //Direction Brive vers Tulle
  dirTulleToBrive("NORMALE"); //Direction Tulle vers Brive
  Serial.print(currentSeq);
  Serial.print(" - ");
  Serial.print(passages_A);
  Serial.print(" - ");
  Serial.print(passages_B);
  Serial.print("\n");
}

//Sequence ralonge
void seqRalonge() {
  initBarrieres(); //Initialisation des barrieres
  dirBriveToTulle("RALONGE"); //Direction Brive vers Tulle
  dirTulleToBrive("RALONGE"); //Direction Tulle vers Brive
  Serial.print(currentSeq);
  Serial.print(" - ");
  Serial.print(passages_A);
  Serial.print(" - ");
  Serial.print(passages_B);
  Serial.print("\n");
}

//Direction Brive vers Tulle + mode NORMALE / RALONGE
void dirBriveToTulle(char mode[10]) {
  if(strcmp(mode, "NORMALE") == 0) {
    //Si detection 1 et sequence courente 0
    if(detection_1 && (currentSeq == 0)) {
      passages_B = 0;
      currentSeq = 11; //Sequence 11 : Brive vers Tulle, baisser barriere PN 1, pause, baisser barriere PN 2
    }
    else if(detection_2 && (currentSeq == 11)) {
      passages_B = 0;
      currentSeq = 12; //Sequence 12 : Brive vers Tulle, lever barriere PN 1, pause, lever barriere PN 2
      waitEndSeq = true; //Mettre en pause
    }
    else if((currentSeq == 12) && !waitEndSeq) {
      currentSeq = 0;
    }
  }
  else if(strcmp(mode, "RALONGE") == 0) {
    //Si detection 1 et sequence courante 0
    if(detection_1 && (currentSeq == 0)) {
      passages_B = 0;
      currentSeq = 21; //Sequence 21 : Brive vers Tulle, baisser barriere PN 1, pause, baisser barriere PN 2
    }
    else if(detection_3 && (currentSeq == 21)) {
      passages_B = 0;
      currentSeq = 22; //Sequence 22 : Brive vers Tulle, lever barriere PN 1, pause, lever barriere PN 2
      waitEndSeq = true; //Mettre en pause
    }
    else if((currentSeq == 22) && !waitEndSeq) {
      currentSeq = 0;
    }
  }
}

//Direction Tulle vers Brive + mode NORMALE / RALONGE
void dirTulleToBrive(char mode[10]) {
  if(strcmp(mode, "NORMALE") == 0) {
    //Si detection 2 et sequence courante 0
    if(detection_2 && (currentSeq == 0)) {
      passages_B = 0;
      currentSeq = 13; //Sequence 13 : Tulle vers Brive, baisser barriere PN 2, pause, baisser barriere PN 1
    }
    else if(detection_1 && (currentSeq == 13)) {
      passages_B = 0;
      currentSeq = 14; //Sequence 14 : Tulle vers Brive, lever barriere PN 2, pause, lever barriere PN 1
      waitEndSeq = true; //Mettre en pause
    }
    else if((currentSeq == 14) && !waitEndSeq) {
      currentSeq = 0;
    }
  }
  else if(strcmp(mode, "RALONGE") == 0) {
    //Si detection 3 et sequence courente 0
    if(detection_3 && (currentSeq == 0)) {
      passages_B = 0;
      currentSeq = 23; //Sequence 23 : Tulle vers Brive, baisser barriere PN 2, pause, baisser barriere PN 1
    }
    else if(detection_1 && (currentSeq == 23)) {
      passages_B = 0;
      currentSeq = 24; //Sequence 24 : Tulle vers Brive, lever barriere PN 2, pause, lever barriere PN 1
      waitEndSeq = true; //Mettre en pause
    }
    else if((currentSeq == 24) && !waitEndSeq) {
      currentSeq = 0;
    }
  }
}

void actionPN() {
  
  //Sequence 11 : Brive vers Tulle, baisser barriere PN 1, pause, baisser barriere PN 2, NORMAL
  if(currentSeq == 11) {
    if(passages_B < 200) {
      PN(1, "DOWN");
      FEUX(1, "ON");
      passages_B++;
    }
    else if(passages_B == 200) {
      PN(2, "DOWN");
      FEUX(2, "ON");
      passages_B = 0;
    }
  }
  
  //Sequence 12 : Brive vers Tulle, lever barriere PN 1, pause, lever barriere PN 2, NORMAL
  if(currentSeq == 12) {
    if(passages_B < 200) {
      PN(1, "UP");
      FEUX(1, "OFF");
      passages_B++;
    }
    else if(passages_B == 200) {
      PN(2, "UP");
      FEUX(2, "OFF");
    }
  }
  
  //Sequence 21 : Brive vers Tulle, baisser barriere PN 1, pause, baisser barriere PN 2, RALONGE
  if(currentSeq == 21) {
    if(passages_B < 200) {
      PN(1, "DOWN");
      FEUX(1, "ON");
      passages_B++;
    }
    else if(passages_B == 200) {
      PN(2, "DOWN");
      FEUX(2, "ON");
    }
  }
  
  //Sequence 22 : Brive vers Tulle, lever barriere PN 1, pause, lever barriere PN 2, RALONGE
  if(currentSeq == 22) {
    if(passages_B < 200) {
      PN(1, "UP");
      FEUX(1, "OFF");
      passages_B++;
    }
    else if(passages_B == 200) {
      PN(2, "UP");
      FEUX(2, "OFF");
    }
  }
  
  //Sequence 13 : Tulle vers Brive, baisser barriere PN 2, pause, baisser barriere PN 1, NORMAL
  if(currentSeq == 13) {
    if(passages_B < 200) {
      PN(2, "DOWN");
      FEUX(2, "ON");
      passages_B++;
    }
    else if(passages_B == 200) {
      PN(1, "DOWN");
      FEUX(1, "ON");
    }
  }
  
  //Sequence 14 : Tulle vers Brive, lever barriere PN 2, pause, lever barriere PN 1, NORMAL
  if(currentSeq == 14) {
    if(passages_B < 200) {
      PN(2, "UP");
      FEUX(2, "OFF");
      passages_B++;
    }
    else if(passages_B == 200) {
      PN(1, "UP");
      FEUX(1, "OFF");
    }
  }
  
  //Sequence 23 : Tulle vers Brive, baisser barriere PN 2, pause, baisser barriere PN 1, RALONGE
  if(currentSeq == 23) {
    if(passages_B < 200) {
      PN(2, "DOWN");
      FEUX(2, "ON");
      passages_B++;
    }
    else if(passages_B == 200) {
      PN(1, "DOWN");
      FEUX(1, "ON");
    }
  }
  
  //Sequence 24 : Tulle vers Brive, lever barriere PN 2, pause, lever barriere PN 1, RALONGE
  if(currentSeq == 24) {
    if(passages_B < 200) {
      PN(2, "UP");
      FEUX(2, "OFF");
      passages_B++;
    }
    else if(passages_B == 200) {
      PN(1, "UP");
      FEUX(1, "OFF");
    }
  }
}

//Rends volontairement bloquant toute sequence
//Sensibilisation aux declenchement intempestifs
//Attendre en fin de sequence
void waitEndSequence(int timeWait){
  //Pause active ?
  if(waitEndSeq) {
    if(passages_A < timeWait) {
      passages_A++;
    }
    else if(passages_A = timeWait) {
      passages_A = 0; //Reinitialise passages a  0
      waitEndSeq = false; //Reinitialise la pause
    }
  }
}

//Initialisation de la barriere
void initBarrieres() {
  if(!initPN) {
    //Lever les barrieres
    PN(1, "UP");
    FEUX(1, "OFF");
    PN(2, "UP");
    FEUX(2, "OFF");
    
    initPN = true; //Initialisation fini
  }
}

//Mode transport
void modeTransport() {
  PN(1, "DOWN");
  FEUX(1, "OFF");
  PN(2, "DOWN");
  FEUX(2, "OFF");
  initPN = false; //Initialisation a  faire
}

//Gestion des barrieres des passages a  niveaux
void PN(int nro, char action[10]) {
  if(nro == 1) {
    if(strcmp(action, "DOWN") == 0) {
      digitalWrite(sensPN_1, LOW);
    }
    else if(strcmp(action, "UP") == 0) {
      digitalWrite(sensPN_1, HIGH);
    }
  }
  else if(nro == 2) {
    if(strcmp(action, "DOWN") == 0) {
      digitalWrite(sensPN_2, LOW);
    }
    else if(strcmp(action, "UP") == 0) {
      digitalWrite(sensPN_2, HIGH);
    }
  }
}

//Gestion des feux clignotants des passages a  niveaux
void FEUX(int nro, char action[5]) {
  if(nro == 1) {
    if(strcmp(action, "OFF") == 0) {
      start_Led_PN1 = false;
      digitalWrite(feuPN_1, LOW);
    }
    else if(strcmp(action, "ON") == 0) {
      //digitalWrite(feuPN_1, HIGH);
      start_Led_PN1 = true;
    }
  }
  else if(nro == 2) {
    if(strcmp(action, "OFF") == 0) {
      start_Led_PN2 = false;
      digitalWrite(feuPN_2, LOW);
    }
    else if(strcmp(action, "ON") == 0) {
      //digitalWrite(feuPN_2, HIGH);
      start_Led_PN2 = true;
    }
  }
}

void clignotementFeuPN1(boolean athorizedLed1) {
  currentMillis_A = millis();
  if(currentMillis_A - previousMillis_A > 700) {
    previousMillis_A = currentMillis_A;
    if(athorizedLed1) {
      if(led_PN1_state) {
        digitalWrite(feuPN_1, LOW);
        led_PN1_state = false;
      }
      else {
        digitalWrite(feuPN_1, HIGH);
        led_PN1_state = true;
      }
    }
  }
}

void clignotementFeuPN2(boolean athorizedLed2) {
  currentMillis_B = millis();
  if(currentMillis_B - previousMillis_B > 700) {
    previousMillis_B = currentMillis_B;
    if(athorizedLed2) {
      if(led_PN2_state) {
        digitalWrite(feuPN_2, LOW);
        led_PN2_state = false;
      }
      else {
        digitalWrite(feuPN_2, HIGH);
        led_PN2_state = true;
      }
    }
  }
}

