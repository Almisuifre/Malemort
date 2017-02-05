
#include "conf.h"
#include <LiquidCrystal.h>
#include <FlexiTimer2.h>

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

//Séquence pour 5 trains et 7 cantons
boolean tMaskTrain5Seq0[NB_ZA] = {1,0,1,1,1,1,0};  //ZA0 -> ZA1
boolean tMaskTrain5Seq1[NB_ZA] = {1,0,1,1,1,0,1};  //ZA0 -> ZA1
boolean tMaskTrain5Seq2[NB_ZA] = {0,1,1,1,1,1,0};  //ZA5 -> ZA0
boolean tMaskTrain5Seq3[NB_ZA] = {0,1,1,1,1,0,1};  //ZA6 -> ZA0
boolean tMaskTrain5Seq4[NB_ZA] = {1,1,1,1,1,0,0};  //ZA4 -> ZA5 / ZA6
boolean tMaskTrain5Seq5[NB_ZA] = {1,1,1,1,1,1,0};  //ZA4 -> ZA5 / ZA6
boolean tMaskTrain5Seq6[NB_ZA] = {1,1,1,1,1,0,1};  //ZA4 -> ZA5 / ZA6
boolean tMaskTrain5Seq7[NB_ZA] = {1,1,1,1,0,1,0};  //ZA2 / ZA3 -> ZA4
boolean tMaskTrain5Seq8[NB_ZA] = {1,1,1,1,0,0,1};  //ZA2 / ZA3 -> ZA4
boolean tMaskTrain5Seq9[NB_ZA] = {1,1,0,1,1,0,1};  //ZA1 -> ZA2 / ZA3
boolean tMaskTrain5Seq10[NB_ZA] = {1,1,0,1,1,1,0};  //ZA1 -> ZA2 / ZA3
boolean tMaskTrain5Seq11[NB_ZA] = {1,1,1,0,1,0,1};  //ZA1 -> ZA2 / ZA3
boolean tMaskTrain5Seq12[NB_ZA] = {1,1,1,0,1,1,0};  //ZA1 -> ZA2 / ZA3


void capture() {
  //Etat des cantons
  tZoneArret[0] = digitalRead(ZA0R);
  tZoneArret[1] = digitalRead(ZA1R);
  tZoneArret[2] = digitalRead(ZA2R);
  tZoneArret[3] = digitalRead(ZA3R);
  tZoneArret[4] = digitalRead(ZA4R);
  tZoneArret[5] = digitalRead(ZA5R);
  tZoneArret[6] = digitalRead(ZA6R);

  commandeAigBrive = digitalRead(CMD_AIG_Brive);
  checkAigBrive(commandeAigBrive);
    
  if(memcmp(tZoneArret, tMaskTrain5Seq0, NB_ZA) == 0) { checkSequence(0);  }         //ZA0 -> ZA1
  else if(memcmp(tZoneArret, tMaskTrain5Seq1, NB_ZA) == 0) { checkSequence(0);  }  //ZA0 -> ZA1
    
  else if(memcmp(tZoneArret, tMaskTrain5Seq2, NB_ZA) == 0) { checkSequence(1);  }  //ZA5 -> ZA0
  else if(memcmp(tZoneArret, tMaskTrain5Seq3, NB_ZA) == 0) { checkSequence(2);  }  //ZA6 -> ZA0
    
  else if(memcmp(tZoneArret, tMaskTrain5Seq4, NB_ZA) == 0) { checkSequence(3);  }  //ZA4 (aiguille) -> ZA5 / ZA6
  else if(memcmp(tZoneArret, tMaskTrain5Seq5, NB_ZA) == 0) { checkSequence(3);  }  //ZA4 (aiguille) -> ZA5 / ZA6
  else if(memcmp(tZoneArret, tMaskTrain5Seq6, NB_ZA) == 0) { checkSequence(3);  }  //ZA4 (aiguille) -> ZA5 / ZA6
    
  else if(memcmp(tZoneArret, tMaskTrain5Seq7, NB_ZA) == 0) { checkSequence(4);  }  //ZA2 / ZA3 -> ZA4
  else if(memcmp(tZoneArret, tMaskTrain5Seq8, NB_ZA) == 0) { checkSequence(4);  }  //ZA2 / ZA3 -> ZA4
    
  else if(memcmp(tZoneArret, tMaskTrain5Seq9, NB_ZA) == 0) { checkSequence(5);  }  //ZA1 (direct) -> ZA2 / ZA3
  else if(memcmp(tZoneArret, tMaskTrain5Seq10, NB_ZA) == 0) { checkSequence(5);  }  //ZA1 (direct) -> ZA2 / ZA3
  else if(memcmp(tZoneArret, tMaskTrain5Seq11, NB_ZA) == 0) { checkSequence(5);  }  //ZA1 (direct) -> ZA2 / ZA3
  else if(memcmp(tZoneArret, tMaskTrain5Seq12, NB_ZA) == 0) { checkSequence(5);  }  //ZA1 (direct) -> ZA2 / ZA3
}

void setup() {
  // put your setup code here, to run once:

  lcd.begin(16,4); //LCD

  //Configuration des Entrées
  pinMode(ZA0R, INPUT);
  pinMode(ZA1R, INPUT);
  pinMode(ZA2R, INPUT);
  pinMode(ZA3R, INPUT);
  pinMode(ZA4R, INPUT);
  pinMode(ZA5R, INPUT);
  pinMode(ZA6R, INPUT);
  pinMode(CMD_AIG_Brive, INPUT);

  //Configuration des Sorties
  pinMode(ZA0W, OUTPUT);
  pinMode(ZA1W, OUTPUT);
  pinMode(ZA2W, OUTPUT);
  pinMode(ZA3W, OUTPUT);
  pinMode(ZA4W, OUTPUT);
  pinMode(ZA5W, OUTPUT);
  pinMode(ZA6W, OUTPUT);

  //Carte sens direction
  pinMode(Direction, OUTPUT);
  pinMode(Autorisation, OUTPUT);

  //Carte Aiguillage Tulle
  pinMode(AIG_Vers_za2, OUTPUT);
  pinMode(AIG_Vers_za3, OUTPUT);
  
  //Carte Aiguillage Malemort
  pinMode(AIG_Vers_za5, OUTPUT);
  pinMode(AIG_Vers_za6, OUTPUT);

  //Place l'aiguille Tulle sur ZA2
  cmd_aiguille(AigTo_ZA2);

  //FlexiTimer2
  FlexiTimer2::set(1, capture);
  FlexiTimer2::start();

  Serial.begin(9600); //Moniteur série

  lcdPrint("LTBC","MALEMORT","","");
}

void loop() {
  //Serial.println(returnZa(ZA0R)+" "+returnZa(ZA1R)+" "+returnZa(ZA2R)+" "+returnZa(ZA3R)+" "+returnZa(ZA4R)+" "+returnZa(ZA5R)+" "+returnZa(ZA6R));
  //testWriteCard();
  //delay(2000);

  //Si l'aiguille Brive est basculée
  if(currentAigBriveChanged) {
    currentAigBriveChanged = false; //Réinitialiser le flag aiguille Brive

    switch(aigBriveCurrent) {
      case 0:
        cmd_aiguille(AigTo_ZA6); //Place l'aiguille Tulle sur ZA6
        break;
      case 1:
        cmd_aiguille(AigTo_ZA5); //Place l'aiguille Tulle sur ZA5
        break;
    }
  }

  //Si la séquence à changer
  if(currentSeqChanged) {
    currentSeqChanged = false;  //Réinitialiser le flag séquence
    
    //En fonction de la séquence courante lancer des commandees
    switch(seqCurrent) {
      case 0:
        cmdZA0_to_ZA1();
        break;
      case 1:
        cmdZA5_to_ZA0();
        break;
      case 2:
        cmdZA6_to_ZA0();
        break;
      case 3:
        cmdZA4_to_ZA5ZA6();
        break;
      case 4:
        cmdZA2ZA3_to_ZA4();
        break;
      case 5:
        cmdZA1_to_ZA2ZA3();
        break;
    }
  }
}

//Gestion de la séquence en cours
void checkSequence(uint8_t sequence) {
  //Si la séquence actuelle est diférente de la séquence précédente
  if(seqCurrent != sequence) {
    
    seqCurrent = sequence;        //Mettre à jour la séquence
    currentSeqChanged = true;  //Placer le flag à l'état changé
  }
}

//Gestion de la commande aiguille Brive en cours
void checkAigBrive(boolean AigBrive) {
  //Si la séquence actuelle est diférente de la séquence précédente
  if(aigBriveCurrent != AigBrive) {
    
    aigBriveCurrent = AigBrive;        //Mettre à jour la séquence
    currentAigBriveChanged = true;  //Placer le flag à l'état changé
  }
}

//Commande pour ZA0 -> ZA1
void cmdZA0_to_ZA1() {
  lcdPrint("MALEMORT","Sens Tulle","Start","");
  cmd_sensMarche(Tulle, Marche);  //Lancer le sens de marche vers Tulle
  delay(tempoArretGare_ZA0);
  lcdPrint("MALEMORT","ZA0 -> ZA1","","");
  cmd_ZA_auto(ZA0, tempoFeuOff_ZA0);  //Lancer le départ du train
}

//Commande pour ZA5 -> ZA0
void cmdZA5_to_ZA0() {
  lcdPrint("MALEMORT","Sens","Stop","");
  cmd_sensMarche(SensStop, Arret);  //Stop le sens de marche
  delay(tempoArretGare_ZA5);
  lcdPrint("MALEMORT","ZA5 -> ZA0","","");
  cmd_ZA_auto(ZA5, tempoFeuOff_ZA5);  //Lancer le départ du train
}

//Commande pour ZA6 -> ZA0
void cmdZA6_to_ZA0() {
  lcdPrint("MALEMORT","Sens","Stop","");
  cmd_sensMarche(SensStop, Arret);  //Stop le sens de marche
  delay(tempoArretGare_ZA6);
  lcdPrint("MALEMORT","ZA6 -> ZA0","","");
  cmd_ZA_auto(ZA6, tempoFeuOff_ZA6);  //Lancer le départ du train
}

//Commande pour ZA4 -> ZA5ZA6
void cmdZA4_to_ZA5ZA6() {
  lcdPrint("MALEMORT","Sens Brive","Start","");
  cmd_sensMarche(Brive, Marche);  //Lancer le sens de marche vers Brive
  delay(tempoArretGare_ZA4);
  lcdPrint("MALEMORT","ZA4 -> ZA5 ZA6","","");
  cmd_ZA_auto(ZA4, tempoFeuOff_ZA4);  //Lancer le départ du train
}

//Commande pour ZA2ZA3 -> ZA4
void cmdZA2ZA3_to_ZA4() {
  lcdPrint("MALEMORT","Sens","Stop","");
  cmd_sensMarche(SensStop, Arret);  //Stop le sens de marche
  
  if(etatAiguilleTulle == 2) {
    delay(tempoArretGare_ZA3);
    lcdPrint("MALEMORT","ZA3 -> ZA4","","");
    cmd_ZA_auto(ZA3, tempoFeuOff_ZA3);  //Lancer le départ du train
    
  }
  else if (etatAiguilleTulle == 3) {
    delay(tempoArretGare_ZA2);
    lcdPrint("MALEMORT","ZA2 -> ZA4","","");
    cmd_ZA_auto(ZA2, tempoFeuOff_ZA2);  //Lancer le départ du train
    
  }
}

//Commande pour ZA1 (direct) -> ZA2 / ZA3
void cmdZA1_to_ZA2ZA3() {

  if(tZoneArret[2] == 1) {
    cmd_aiguille(AigTo_ZA3); //Place l'aiguille Tulle sur ZA3
    lcdPrint("MALEMORT","Aiguille","ZA3","");
    flagTunnel = true;
  }
  else if(tZoneArret[3] == 1) {
    cmd_aiguille(AigTo_ZA2); //Place l'aiguille Tulle sur ZA2
    lcdPrint("MALEMORT","Aiguille","ZA2","");
    flagTunnel = true;
  }
  else if(tZoneArret[2] == 0 && tZoneArret[3] == 0) {
    lcdPrint("MALEMORT","Aiguille","Impossible","");
    flagTunnel = false;
  }

  delay(tempoArretGare_ZA1);
  if(flagTunnel) {
    lcdPrint("MALEMORT","ZA1 -> ZA2 ZA3","","");
    cmd_ZA_auto(ZA1, tempoFeuOff_ZA1);  //Lancer le départ du train
  }
}

//Pilotage du sens de marche
void cmd_sensMarche(int sens, int marche) {
  digitalWrite(Direction, sens);
  digitalWrite(Autorisation, marche);
}

//Pilotage zone d'arret auto
void cmd_ZA_auto(int ZA, int tempo) {
  if(ZA == 0) {
    digitalWrite(ZA0W, HIGH);
    delay(tempo);
    digitalWrite(ZA0W, LOW);
  }
  else if(ZA == 1) {
    digitalWrite(ZA1W, HIGH);
    delay(tempo);
    digitalWrite(ZA1W, LOW);
  }
  else if(ZA == 2) {
    digitalWrite(ZA2W, HIGH);
    delay(tempo);
    digitalWrite(ZA2W, LOW);
  }
  else if(ZA == 3) {
    digitalWrite(ZA3W, HIGH);
    delay(tempo);
    digitalWrite(ZA3W, LOW);
  }
  else if(ZA == 4) {
    digitalWrite(ZA4W, HIGH);
    delay(tempo);
    digitalWrite(ZA4W, LOW);
  }
  else if(ZA == 5) {
    digitalWrite(ZA5W, HIGH);
    delay(tempo);
    digitalWrite(ZA5W, LOW);
  }
  else if(ZA == 6) {
    digitalWrite(ZA6W, HIGH);
    delay(tempo);
    digitalWrite(ZA6W, LOW);
  }
}

//Pilotage des aiguilles
void cmd_aiguille(int versZA) {
  
  if(versZA == 2) {
    digitalWrite(AIG_Vers_za2, HIGH);
    delay(100);
    digitalWrite(AIG_Vers_za2, LOW);
    etatAiguilleTulle = 2;
    etatAiguilleTulleChanged = true;
  }
  else if(versZA == 3) {
    digitalWrite(AIG_Vers_za3, HIGH);
    delay(100);
    digitalWrite(AIG_Vers_za3, LOW);
    etatAiguilleTulle = 3;
    etatAiguilleTulleChanged = true;
  }
  if(versZA == 5) {
    digitalWrite(AIG_Vers_za5, HIGH);
    delay(100);
    digitalWrite(AIG_Vers_za5, LOW);
  }
  if(versZA == 6) {
    digitalWrite(AIG_Vers_za6, HIGH);
    delay(100);
    digitalWrite(AIG_Vers_za6, LOW);
  }
}

// Fonction de retour de l'état des voies
String returnZa(int ZA) {

  String Valeur;
   
  switch(ZA) {
    case 22:
      Valeur = "ZA0 ";
      Valeur += digitalRead(ZA);
      break;

      case 24:
      Valeur = "ZA1 ";
      Valeur += digitalRead(ZA);
      break;

      case 26:
      Valeur = "ZA2 ";
      Valeur += digitalRead(ZA);
      break;

      case 28:
      Valeur = "ZA3 ";
      Valeur += digitalRead(ZA);
      break;

      case 30:
      Valeur = "ZA4 ";
      Valeur += digitalRead(ZA);
      break;

      case 32:
      Valeur = "ZA5 ";
      Valeur += digitalRead(ZA);
      break;

      case 34:
      Valeur = "ZA6 ";
      Valeur += digitalRead(ZA);
      break;
  }
  
  return Valeur;
}

// Fonction de commande des cartes
void testWriteCard() {
  for (int i = 0; i <= 9; i++) {
    switch(i) {
    case 0:
      digitalWrite(ZA0W, HIGH);
      digitalWrite(ZA6W, LOW);
      break;
      
    case 1:
      digitalWrite(ZA1W, HIGH);
      digitalWrite(ZA0W, LOW);
      break;

    case 2:
      digitalWrite(ZA2W, HIGH);
      digitalWrite(ZA1W, LOW);
      break;

    case 3:
      digitalWrite(ZA3W, HIGH);
      digitalWrite(ZA2W, LOW);
      break;
      
    case 4:
      digitalWrite(ZA4W, HIGH);
      digitalWrite(ZA3W, LOW);
      break;

    case 5:
      digitalWrite(ZA5W, HIGH);
      digitalWrite(ZA4W, LOW);
      break;

    case 6:
      digitalWrite(ZA6W, HIGH);
      digitalWrite(ZA5W, LOW);
      break;

    case 7:
      digitalWrite(Direction, HIGH);
      delay(100);
      digitalWrite(Direction, LOW);
      delay(100);
      digitalWrite(Direction, HIGH);
      digitalWrite(Autorisation, HIGH);
      delay(100);
      digitalWrite(Direction, LOW);
      digitalWrite(Autorisation, LOW);
      break;

    case 8:
      digitalWrite(AIG_Vers_za2, HIGH);
      delay(20);
      digitalWrite(AIG_Vers_za2, LOW);
      delay(100);
      digitalWrite(AIG_Vers_za3, HIGH);
      delay(20);
      digitalWrite(AIG_Vers_za3, LOW);
      break;

    case 9:
      digitalWrite(AIG_Vers_za5, HIGH);
      delay(20);
      digitalWrite(AIG_Vers_za5, LOW);
      delay(100);
      digitalWrite(AIG_Vers_za6, HIGH);
      delay(20);
      digitalWrite(AIG_Vers_za6, LOW);
      break;
    }
    
    delay(500);
  }
}

void lcdPrint(String txtL0, String txtL1, String txtL2, String txtL3) {
  lcd.clear();
  lcd.setCursor(0,0); //Colonne, ligne
  lcd.print(txtL0);
  lcd.setCursor(0,1); //Colonne, ligne
  lcd.print(txtL1);
  lcd.setCursor(0,2); //Colonne, ligne
  lcd.print(txtL2);
  lcd.setCursor(0,3); //Colonne, ligne
  lcd.print(txtL3);
}

