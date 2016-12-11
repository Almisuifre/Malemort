/* --- INCLUDE --- */
//#include <LCD4x16.h>
#include <LiquidCrystal.h>
#include <FlexiTimer2.h>
#include "conf.h"
#include "masques_sequences.h"

/* --- COMMANDE INITIALISATION LCD --- */
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

void capture() {
  //Etat des cantons
  tZoneArret[0] = digitalRead(ZA0R);
  tZoneArret[1] = digitalRead(ZA1R);
  tZoneArret[2] = digitalRead(ZA2R);
  tZoneArret[3] = digitalRead(ZA3R);
  tZoneArret[4] = digitalRead(ZA4R);
  tZoneArret[5] = digitalRead(ZA5R);
  tZoneArret[6] = digitalRead(ZA6R);
  
  etatAiguilleMalemort = digitalRead(ETAT_AIG_Malemort);
  ckeckAiguilleMalemort(etatAiguilleMalemort);

  //Séquences erreurs
  //if(memcmp(tZoneArret, tMaskDefalutEmpty, NB_ZA) == 0) { checkSequence(111); }

//Séquences de marche pour 1 train
  if(nbTrainReel == 1) {
    if(memcmp(tZoneArret, tMaskTrain1Seq0, NB_ZA) == 0) { checkSequence(0); }        //ZA0 -> ZA1
    else if(memcmp(tZoneArret, tMaskTrain1Seq1, NB_ZA) == 0) { checkSequence(1); } //ZA1 -> ZA2 / ZA3
    else if(memcmp(tZoneArret, tMaskTrain1Seq2, NB_ZA) == 0) { checkSequence(2); } //ZA2 -> ZA4
    else if(memcmp(tZoneArret, tMaskTrain1Seq3, NB_ZA) == 0) { checkSequence(3); } //ZA3 -> ZA4
    else if(memcmp(tZoneArret, tMaskTrain1Seq4, NB_ZA) == 0) { checkSequence(4); } //ZA4 -> ZA5 / ZA6
    else if(memcmp(tZoneArret, tMaskTrain1Seq5, NB_ZA) == 0) { checkSequence(5); } //ZA5 -> ZA0
    else if(memcmp(tZoneArret, tMaskTrain1Seq6, NB_ZA) == 0) { checkSequence(6); } //ZA6 -> ZA0
  }
  if(nbTrainReel == 2) {
    if(memcmp(tZoneArret, tMaskTrain2Seq0, NB_ZA) == 0) { checkSequence(0);  }        //ZA0 -> ZA1
    else if(memcmp(tZoneArret, tMaskTrain2Seq1, NB_ZA) == 0) { checkSequence(1);  } //ZA1 -> ZA2 / ZA3
    else if(memcmp(tZoneArret, tMaskTrain2Seq2, NB_ZA) == 0) { checkSequence(4);  } //ZA4 -> ZA5 / ZA6
    else if(memcmp(tZoneArret, tMaskTrain2Seq3, NB_ZA) == 0) { checkSequence(4);  } //ZA4 -> ZA5 / ZA6
    else if(memcmp(tZoneArret, tMaskTrain2Seq4, NB_ZA) == 0) { checkSequence(5);  } //ZA5 -> ZA0
    else if(memcmp(tZoneArret, tMaskTrain2Seq5, NB_ZA) == 0) { checkSequence(6);  } //ZA6 -> ZA0
    else if(memcmp(tZoneArret, tMaskTrain2Seq6, NB_ZA) == 0) { checkSequence(5);  } //ZA5 -> ZA0
    else if(memcmp(tZoneArret, tMaskTrain2Seq7, NB_ZA) == 0) { checkSequence(6);  } //ZA6 -> ZA0
    else if(memcmp(tZoneArret, tMaskTrain2Seq8, NB_ZA) == 0) { checkSequence(2);  } //ZA2 -> ZA4
    else if(memcmp(tZoneArret, tMaskTrain2Seq9, NB_ZA) == 0) { checkSequence(3);  } //ZA3 -> ZA4
  }
  if(nbTrainReel == 3) {
    if(memcmp(tZoneArret, tMaskTrain3Seq0, NB_ZA) == 0) { checkSequence(0);  }        //ZA0 -> ZA1
    else if(memcmp(tZoneArret, tMaskTrain3Seq1, NB_ZA) == 0) { checkSequence(0);  } //ZA0 -> ZA1
    else if(memcmp(tZoneArret, tMaskTrain3Seq2, NB_ZA) == 0) { checkSequence(1);  } //ZA1 -> ZA2 / ZA3
    else if(memcmp(tZoneArret, tMaskTrain3Seq3, NB_ZA) == 0) { checkSequence(1);  } //ZA1 -> ZA2 / ZA3
    else if(memcmp(tZoneArret, tMaskTrain3Seq4, NB_ZA) == 0) { checkSequence(5);  } //ZA5 -> ZA0
    else if(memcmp(tZoneArret, tMaskTrain3Seq5, NB_ZA) == 0) { checkSequence(6);  } //ZA6 -> ZA0
    else if(memcmp(tZoneArret, tMaskTrain3Seq6, NB_ZA) == 0) { checkSequence(5);  } //ZA5 -> ZA0
    else if(memcmp(tZoneArret, tMaskTrain3Seq7, NB_ZA) == 0) { checkSequence(6);  } //ZA6 -> ZA0
    else if(memcmp(tZoneArret, tMaskTrain3Seq8, NB_ZA) == 0) { checkSequence(4);  } //ZA4 -> ZA5 / ZA6
    else if(memcmp(tZoneArret, tMaskTrain3Seq9, NB_ZA) == 0) { checkSequence(4);  } //ZA4 -> ZA5 / ZA6
    else if(memcmp(tZoneArret, tMaskTrain3Seq10, NB_ZA) == 0) { checkSequence(2);  } //ZA2 -> ZA4
    else if(memcmp(tZoneArret, tMaskTrain3Seq11, NB_ZA) == 0) { checkSequence(3);  } //ZA3 -> ZA4
    else if(memcmp(tZoneArret, tMaskTrain3Seq12, NB_ZA) == 0) { checkSequence(2);  } //ZA2 -> ZA4
    else if(memcmp(tZoneArret, tMaskTrain3Seq13, NB_ZA) == 0) { checkSequence(3);  } //ZA3 -> ZA4
  }
  
  if(nbTrainReel == 4) {
    
     if(memcmp(tZoneArret, tMaskTrain4Seq0, NB_ZA) == 0) { checkSequence(0);  }        //ZA0 -> ZA1
    else if(memcmp(tZoneArret, tMaskTrain4Seq1, NB_ZA) == 0) { checkSequence(0);  }  //ZA0 -> ZA1
    else if(memcmp(tZoneArret, tMaskTrain4Seq2, NB_ZA) == 0) { checkSequence(0);  }  //ZA0 -> ZA1
    else if(memcmp(tZoneArret, tMaskTrain4Seq3, NB_ZA) == 0) { checkSequence(0);  }  //ZA0 -> ZA1
    else if(memcmp(tZoneArret, tMaskTrain4Seq4, NB_ZA) == 0) { checkSequence(5);  }  //ZA5 -> ZA0
    else if(memcmp(tZoneArret, tMaskTrain4Seq5, NB_ZA) == 0) { checkSequence(5);  }  //ZA5 -> ZA0
    else if(memcmp(tZoneArret, tMaskTrain4Seq6, NB_ZA) == 0) { checkSequence(6);  }  //ZA6 -> ZA0
    else if(memcmp(tZoneArret, tMaskTrain4Seq7, NB_ZA) == 0) { checkSequence(6);  }  //ZA6 -> ZA0
    else if(memcmp(tZoneArret, tMaskTrain4Seq8, NB_ZA) == 0) { checkSequence(4);  }  //ZA4 -> ZA5 / ZA6
    else if(memcmp(tZoneArret, tMaskTrain4Seq9, NB_ZA) == 0) { checkSequence(4);  }  //ZA4 -> ZA5 / ZA6
    else if(memcmp(tZoneArret, tMaskTrain4Seq10, NB_ZA) == 0) { checkSequence(2);  }  //ZA2 -> ZA4
    else if(memcmp(tZoneArret, tMaskTrain4Seq11, NB_ZA) == 0) { checkSequence(2);  }  //ZA2 -> ZA4
    else if(memcmp(tZoneArret, tMaskTrain4Seq12, NB_ZA) == 0) { checkSequence(3);  }  //ZA3 -> ZA4
    else if(memcmp(tZoneArret, tMaskTrain4Seq13, NB_ZA) == 0) { checkSequence(3);  }  //ZA3 -> ZA4
    else if(memcmp(tZoneArret, tMaskTrain4Seq14, NB_ZA) == 0) { checkSequence(1);  }  //ZA1 -> ZA2 / ZA3
    else if(memcmp(tZoneArret, tMaskTrain4Seq15, NB_ZA) == 0) { checkSequence(1);  }  //ZA1 -> ZA2 / ZA3
  }
  
  if(nbTrainReel == 5) {
    
    if(memcmp(tZoneArret, tMaskTrain5Seq0, NB_ZA) == 0) { checkSequence(0);  }         //ZA0 -> ZA1
    else if(memcmp(tZoneArret, tMaskTrain5Seq1, NB_ZA) == 0) { checkSequence(0);  }  //ZA0 -> ZA1
    
    else if(memcmp(tZoneArret, tMaskTrain5Seq2, NB_ZA) == 0) { checkSequence(5);  }  //ZA5 -> ZA0
    else if(memcmp(tZoneArret, tMaskTrain5Seq3, NB_ZA) == 0) { checkSequence(6);  }  //ZA6 -> ZA0
    
    else if(memcmp(tZoneArret, tMaskTrain5Seq4, NB_ZA) == 0) { checkSequence(10);  }  //ZA4 (aiguille) -> ZA5 / ZA6
    else if(memcmp(tZoneArret, tMaskTrain5Seq5, NB_ZA) == 0) { checkSequence(10);  }  //ZA4 (aiguille) -> ZA5 / ZA6
    else if(memcmp(tZoneArret, tMaskTrain5Seq6, NB_ZA) == 0) { checkSequence(10);  }  //ZA4 (aiguille) -> ZA5 / ZA6
    
    else if(memcmp(tZoneArret, tMaskTrain5Seq7, NB_ZA) == 0) { checkSequence(8);  }  //ZA2 / ZA3 -> ZA4
    else if(memcmp(tZoneArret, tMaskTrain5Seq8, NB_ZA) == 0) { checkSequence(8);  }  //ZA2 / ZA3 -> ZA4
    
    else if(memcmp(tZoneArret, tMaskTrain5Seq9, NB_ZA) == 0) { checkSequence(9);  }  //ZA1 (direct) -> ZA2 / ZA3
    else if(memcmp(tZoneArret, tMaskTrain5Seq10, NB_ZA) == 0) { checkSequence(9);  }  //ZA1 (direct) -> ZA2 / ZA3
    else if(memcmp(tZoneArret, tMaskTrain5Seq11, NB_ZA) == 0) { checkSequence(9);  }  //ZA1 (direct) -> ZA2 / ZA3
    else if(memcmp(tZoneArret, tMaskTrain5Seq12, NB_ZA) == 0) { checkSequence(9);  }  //ZA1 (direct) -> ZA2 / ZA3
  }
}

/* --- INITIALISATION --- */
void setup() {
  //Affichage
  lcd.begin(16,4);

  //FlexiTimer2
  FlexiTimer2::set(1, capture);
  FlexiTimer2::start();

  //Configuration des Entrées
  pinMode(ZA0R, INPUT);
  pinMode(ZA1R, INPUT);
  pinMode(ZA2R, INPUT);
  pinMode(ZA3R, INPUT);
  pinMode(ZA4R, INPUT);
  pinMode(ZA5R, INPUT);
  pinMode(ZA6R, INPUT);

  //Etat commande aiguille Malemort
  pinMode(ETAT_AIG_Malemort, INPUT);

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
  etatAiguilleTulle = 2;
  etatAiguilleTulleChanged = true;

  //Moniteur série
  Serial.begin(9600);

  EcranPge1("");
}

/* --- LOOP --- */
void loop() {

  //Tableau des états des cantons (Débuggage)
  Serial.println(tZoneArret[0]);
  Serial.println(tZoneArret[1]);
  Serial.println(tZoneArret[2]);
  Serial.println(tZoneArret[3]);
  Serial.println(tZoneArret[4]);
  Serial.println(tZoneArret[5]);
  Serial.println(tZoneArret[6]);
  Serial.println(" ------------------------------------ ");

  //Si la séquence à changer
  if(currentSeqChanged) {
    currentSeqChanged = false;  //Réinitialiser le flag séquence
    
    //En fonction de la séquence courante lancer des commandees
    switch(seqCurrent) {
      case 0:
      cmdZA0_to_ZA1();
      break;
      case 1:
      cmdZA1_to_ZA2ZA3();
      break;
      case 2:
      cmdZA2_to_ZA4();
      break;
      case 3:
      cmdZA3_to_ZA4();
      break;
      case 4:
      cmdZA4_to_ZA5ZA6();
      break;
      case 5:
      cmdZA5_to_ZA0();
      break;
      case 6:
      cmdZA6_to_ZA0();
      break;
      case 7:
      cmdZA5ZA6_to_ZA0();
      break;
      case 8:
      cmdZA2ZA3_to_ZA4();
      break;
      case 9:
      cmdZA1_direct_to_ZA2ZA3();
      break;
      case 10:
      cmdZA4_aiguille_to_ZA5ZA6();
      break;
    }
  }
}

//Commande pour ZA0 -> ZA1
void cmdZA0_to_ZA1() {
  EcranPge1("Sens : Tulle");
  cmd_sensMarche(Tulle, Marche);  //Lancer le sens de marche vers Tulle
  delay(tempoArretGare_ZA0);
  EcranPge1("ZA0 -> ZA1");
  cmd_ZA_auto(ZA0, tempoFeuOff_ZA0);  //Lancer le départ du train
}

//Commande pour ZA1 -> ZA2 / ZA3
void cmdZA1_to_ZA2ZA3() {
  EcranPge1("Sens : Stop");
  delay(5000); //Impératif pour charger les capacités
  cmd_sensMarche(SensStop, Arret);  //Annuler le sens de marche

  if(tZoneArret[2] == 1) {
    cmd_aiguille(AigTo_ZA3); //Place l'aiguille Tulle sur ZA3
    etatAiguilleTulle = 3;
    etatAiguilleTulleChanged = true;
    flagTunnel = true;
  }
  else if(tZoneArret[3] == 1) {
    cmd_aiguille(AigTo_ZA2); //Place l'aiguille Tulle sur ZA2
    etatAiguilleTulle = 2;
    etatAiguilleTulleChanged = true;
    flagTunnel = true;
  }
  else if(tZoneArret[2] == 0 && tZoneArret[3] == 0) {
    flagTunnel = false;
  }

  if(flagTunnel) {
    delay(tempoArretGare_ZA1);
    if(etatAiguilleTulle == 3) {
      EcranPge1("ZA1 -> ZA3");
    }
    else if(etatAiguilleTulle == 2) {
      EcranPge1("ZA1 -> ZA2");
    }
  }
  cmd_ZA_auto(ZA1, tempoFeuOff_ZA1);  //Lancer le départ du train
}

//Commande pour ZA1 (direct) -> ZA2 / ZA3
void cmdZA1_direct_to_ZA2ZA3() {
  EcranPge1("Sens : Stop");
  cmd_sensMarche(SensStop, Arret);  //Annuler le sens de marche

  if(tZoneArret[2] == 1) {
    cmd_aiguille(AigTo_ZA3); //Place l'aiguille Tulle sur ZA3
    etatAiguilleTulle = 3;
    flagTunnel = true;
  }
  else if(tZoneArret[3] == 1) {
    cmd_aiguille(AigTo_ZA2); //Place l'aiguille Tulle sur ZA2
    etatAiguilleTulle = 2;
    flagTunnel = true;
  }
  else if(tZoneArret[2] == 0 && tZoneArret[3] == 0) {
    flagTunnel = false;
  }

  delay(tempoArretGare_ZA1);
  if(flagTunnel) {
    EcranPge1("ZA1 -> ZA2 ZA3");
    cmd_ZA_auto(ZA1, tempoFeuOff_ZA1);  //Lancer le départ du train
  }
}

//Commande pour ZA2 -> ZA4
void cmdZA2_to_ZA4() {
  etatAiguilleTulleChanged = false;
  delay(tempoArretGare_ZA2);
  EcranPge1("ZA2 -> ZA4");
  cmd_ZA_auto(ZA2, tempoFeuOff_ZA2);  //Lancer le départ du train
}

//Commande pour ZA3 -> ZA4
void cmdZA3_to_ZA4() {
  etatAiguilleTulleChanged = false;
  delay(tempoArretGare_ZA3);
  EcranPge1("ZA3 -> ZA4");
  cmd_ZA_auto(ZA3, tempoFeuOff_ZA3);  //Lancer le départ du train
}

//Commande pour ZA4 -> ZA5 / ZA6
void cmdZA4_to_ZA5ZA6() {
  EcranPge1("Sens : Brive");
  cmd_sensMarche(Brive, Marche);  //Lancer le sens de marche vers Brive
  delay(tempoArretGare_ZA4);
  EcranPge1("ZA4 -> ZA5 ZA6");
  cmd_ZA_auto(ZA4, tempoFeuOff_ZA4);  //Lancer le départ du train
}

//Commande pour ZA5 -> ZA0
void cmdZA5_to_ZA0() {
  EcranPge1("Sens : Stop");
  cmd_sensMarche(SensStop, Arret);  //Annuler le sens de marche
  delay(tempoArretGare_ZA5);
  EcranPge1("ZA5 -> ZA0");
  cmd_ZA_auto(ZA5, tempoFeuOff_ZA5);  //Lancer le départ du train
}

//Commande pour ZA6 -> ZA0
void cmdZA6_to_ZA0() {
  EcranPge1("Sens : Stop");
  cmd_sensMarche(SensStop, Arret);  //Annuler le sens de marche
  delay(tempoArretGare_ZA6);
  EcranPge1("ZA6 -> ZA0");
  cmd_ZA_auto(ZA6, tempoFeuOff_ZA6);  //Lancer le départ du train
}

//Gestion de la séquence en cours
void checkSequence(uint8_t sequence) {
  //Si la séquence actuelle est diférente de la séquence précédente
  if(seqCurrent != sequence) {
    
    seqCurrent = sequence;        //Mettre à jour la séquence
    currentSeqChanged = true;  //Placer le flag à l'état changé
  }
}

//Pilotage aiguille Malemort
void ckeckAiguilleMalemort(uint8_t versZA5ZA6) {
  //Si la séquence actuelle est différente de la séquence précédente
  if(aigCurrent != versZA5ZA6) {
    aigCurrent = versZA5ZA6; //Mettre à jour la séquence
    currentAigChanged = true; //Placer le flag à l'état changé
  }

  //Si l'aiguille à changé
  if(currentAigChanged) {
    currentAigChanged = false; //Mettre le currectAigCganged à off

    //Si l'aiguille courante correspond à 0 -> vers ZA6 ; à 1 -> Za5
    switch(aigCurrent) {

      case 0:
      cmd_aiguille(AigTo_ZA6); //Place l'aiguille Tulle sur ZA6
      break;

      case 1:
      cmd_aiguille(AigTo_ZA5); //Place l'aiguille Tulle sur ZA5
      break;
    }
  }
}

//Commande pour ZA5ZA6 -> ZA0
void cmdZA5ZA6_to_ZA0() {
  EcranPge1("Sens : Stop");
  cmd_sensMarche(SensStop, Arret);  //Annuler le sens de marche
  delay(tempoArretGare_ZA5ZA6);
  
  if(aigCurrent) {
    EcranPge1("ZA5 -> ZA0");
    cmd_ZA_auto(ZA5, tempoFeuOff_ZA5);  //Lancer le départ du train
  } else {
    EcranPge1("ZA6 -> ZA0");
    cmd_ZA_auto(ZA6, tempoFeuOff_ZA6);  //Lancer le départ du train
  }
}

//Commande pour ZA2 / ZA3 -> ZA4
void cmdZA2ZA3_to_ZA4() {
  etatAiguilleTulleChanged = false;
  delay(tempoArretGare_ZA2ZA3);
  if(etatAiguilleTulle == 2) {
    EcranPge1("ZA2 -> ZA4");
    cmd_ZA_auto(ZA2, tempoFeuOff_ZA2);  //Lancer le départ du train
  } else {
    EcranPge1("ZA3 -> ZA4");
    cmd_ZA_auto(ZA3, tempoFeuOff_ZA3);  //Lancer le départ du train
  }
}

//Commande pour ZA4 (aiguille) -> ZA5 / ZA6
void cmdZA4_aiguille_to_ZA5ZA6() {
  EcranPge1("Sens : Brive");
  cmd_sensMarche(Brive, Marche);  //Lancer le sens de marche vers Brive
  
  if(!etatAiguilleTulleChanged) {
    //Si on à l'aiguille sur 2
    if(etatAiguilleTulle == 2) {  
      cmd_aiguille(AigTo_ZA3); //Place l'aiguille Tulle sur ZA3
      etatAiguilleTulle = 3;
      etatAiguilleTulleChanged = true;
    } else {
      cmd_aiguille(AigTo_ZA2); //Place l'aiguille Tulle sur ZA2
      etatAiguilleTulle = 2;
      etatAiguilleTulleChanged = true;
    }
  }
   
   delay(tempoArretGare_ZA4);
   EcranPge1("ZA4 -> ZA5 ZA6");
   cmd_ZA_auto(ZA4, tempoFeuOff_ZA4);  //Lancer le départ du train
}

//Pilotage zone d'arret manuelle
void cmd_ZA_manuel(int ZA, int etatCmd) {
  
  if(ZA == 0) {
    if(etatCmd) {digitalWrite(ZA0W, HIGH); } else { digitalWrite(ZA0W, LOW); }
  }
  else if(ZA == 1) {
    if(etatCmd) {digitalWrite(ZA1W, HIGH); } else { digitalWrite(ZA1W, LOW); }
  }
  else if(ZA == 2) {
    if(etatCmd) {digitalWrite(ZA2W, HIGH); } else { digitalWrite(ZA2W, LOW); }
  }
  else if(ZA == 3) {
    if(etatCmd) {digitalWrite(ZA3W, HIGH); } else { digitalWrite(ZA3W, LOW); }
  }
  else if(ZA == 4) {
    if(etatCmd) {digitalWrite(ZA4W, HIGH); } else { digitalWrite(ZA4W, LOW); }
  }
  else if(ZA == 5) {
    if(etatCmd) {digitalWrite(ZA5W, HIGH); } else { digitalWrite(ZA5W, LOW); }
  }
  else if(ZA == 6) {
    if(etatCmd) {digitalWrite(ZA6W, HIGH); } else { digitalWrite(ZA6W, LOW); }
  }
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

//Pilotage du sens de marche
void cmd_sensMarche(int sens, int marche) {
  digitalWrite(Direction, sens);
  digitalWrite(Autorisation, marche);
}

//Pilotage des aiguilles
void cmd_aiguille(int versZA) {
  
  if(versZA == 2) {
    digitalWrite(AIG_Vers_za2, HIGH);
    EcranPge1("Aig vers ZA2");
    delay(1000);
    digitalWrite(AIG_Vers_za2, LOW);
  }
  else if(versZA == 3) {
    digitalWrite(AIG_Vers_za3, HIGH);
    EcranPge1("Aig vers ZA3");
    delay(1000);
    digitalWrite(AIG_Vers_za3, LOW);
  }
  if(versZA == 5) {
    digitalWrite(AIG_Vers_za5, HIGH);
    EcranPge1("Aig vers ZA5");
    delay(1000);
    digitalWrite(AIG_Vers_za5, LOW);
  }
  if(versZA == 6) {
    digitalWrite(AIG_Vers_za6, HIGH);
    EcranPge1("Aig vers ZA6");
    delay(1000);
    digitalWrite(AIG_Vers_za6, LOW);
  }
}

//Ecran page 1
void EcranPge1(String infos_L2) {
  lcd.clear();
  lcd.setCursor(0,0); //Colonne, ligne
  lcd.print("LTBC - MALEMORT");
  delay(1);

  lcd.setCursor(0,1); //Colonne, ligne
  lcd.print("Mode : ");
  delay(1);
  lcd.setCursor(6,1); //Colonne, ligne
  lcd.print(nbTrainReel);
  delay(1);
  lcd.setCursor(8,1); //Colonne, ligne
  lcd.print("trains");
  delay(1);

  if(infos_L2) {
    lcd.setCursor(0,2); //Colonne, ligne
    lcd.print("                ");
    delay(1);
    lcd.setCursor(0,2); //Colonne, ligne
    lcd.print(infos_L2);
    delay(1);
  }

  lcd.setCursor(0,3); //Colonne, ligne
  lcd.print("MENU");
  delay(1);
}


