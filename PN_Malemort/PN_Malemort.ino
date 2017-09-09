/*
 * Réseau MALEMORT
 * GESTION DES PN
 * 
 */

/* ** CONFIGURATIONS ** */
/*
 * D2 (INPUT) détection 1
 * D3 (INPUT) détection 2
 * D4 (INPUT) détection 3
 * 
 * A0 (INPUT) CONFIG
 * A1 (INPUT) Transport
 * 
 * D7 (OUTPUT) Feu PN 1
 * D8 (OUTPUT) Feu PN 2
 * 
 * D11 (OUTPUT) SENS PN 1
 * D12 (OUTPUT) SENS PN 2
 */

 #define detect_1 2 //PD2
 #define detect_2 3 //PD3
 #define detect_3 4// PD4
 #define btnConfig A0 //PC0
 #define btnMove A1 //PC1
 #define feuPN_1 7 //PD7
 #define feuPN_2 8 //PB0
 #define sensPN_1 11 //PB3
 #define sensPN_2 12 //PB4


 int btnConf = 0;
 int btnMoveTo = 0;
 boolean detection_1 = false;
 boolean detection_2 = false;
 boolean detection_3 = false;

 long previousMillis = 0;

 boolean init_barriere = false;
 boolean sens_brive_to_tulle = false;
 boolean sens_tulle_to_brive = false;
 boolean wait_detect = false;

 boolean start_led_PN1 = false;
 boolean start_led_PN2 = false;

 boolean led_PN1_state = false;
 boolean led_PN2_state = false;
 
void setup() {
  //INPUT
  pinMode(detect_1, INPUT); //D2 (INPUT) détection 1
  pinMode(detect_2, INPUT); //D3 (INPUT) détection 2
  pinMode(detect_3, INPUT); //D4 (INPUT) détection 3

  pinMode(btnConfig, INPUT); //A0 (INPUT) CONFIG
  pinMode(btnMove, INPUT); //A1 (INPUT) Transport

  //OUTPUT
  pinMode(feuPN_1, OUTPUT); //D7 (OUTPUT) Feu PN 1
  pinMode(feuPN_2, OUTPUT); //D8 (OUTPUT) Feu PN 2

  pinMode(sensPN_1, OUTPUT); //D11 (OUTPUT) SENS PN 1
  pinMode(sensPN_2, OUTPUT); //D12 (OUTPUT) SENS PN 2

  Serial.begin(9600);
  Serial.println("Malemort start");
  Serial.println("--------------");
  Serial.println("");
}

void loop() {
  //Scruter les états
  btnConf = analogRead(btnConfig);  //Bouton configuration
  btnMoveTo = analogRead(btnMove);  //Bouton transport (baisser les barrières)
  detection_1 = digitalRead(detect_1);  //Détection 1
  detection_2 = digitalRead(detect_2);  //Détection 2
  detection_3 = digitalRead(detect_3);  //Détection 3

  if((btnMoveTo > 500) && (btnMoveTo < 520)) {
    //On est en mode normal, l'automatisme fonctionne
    //Les barrières sont levés
    Serial.println("Mode Normal : L'automatisme est activé");
    if(!init_barriere) {
      //Lancer initialisation
      PN_1_UP();
      PN_2_UP();
      init_barriere = true;
    }

    if((btnConf > 500) && (btnConf < 520)) {
      //Mode court (Detection 1 + Détection 2)
      Serial.println("Mode court");
      
      if(detection_1 && !wait_detect) {
        //Si le train est détecté sur Detect_1
        delay(100);
        PN_1_DO();
        delay(500);
        PN_2_DO();
        sens_brive_to_tulle = true;
      }

      if(detection_2 && sens_brive_to_tulle) {
        //Si le train est détecté sur Detect_2
        delay(100);
        PN_1_UP();
        delay(500);
        PN_2_UP();
        sens_brive_to_tulle = false;
        wait_detect = true;
      }

       if(detection_2 && !wait_detect) {
        //Si le train est détecté sur Detect_2
        delay(100);
        PN_2_DO();
        delay(500);
        PN_1_DO();
        sens_tulle_to_brive = true;
      }

      if(detection_1 && sens_tulle_to_brive) {
        //Si le train est détecté sur Detect_1
        delay(100);
        PN_2_UP();
        delay(500);
        PN_1_UP();
        sens_tulle_to_brive = false;
        wait_detect = true;
      }
    }
    if((btnConf > 700) && (btnConf < 710)) {
      //Mode long (Détection 1 + Détection 3)
      Serial.println("Mode long");

       if(detection_1 && !wait_detect) {
        //Si le train est détecté sur Detect_1
        delay(100);
        PN_1_DO();
        
        delay(500);
        PN_2_DO();
        
        sens_brive_to_tulle = true;
      }

      if(detection_3 && sens_brive_to_tulle) {
        //Si le train est détecté sur Detect_3
        delay(100);
        PN_1_UP();
        delay(500);
        PN_2_UP();
        sens_brive_to_tulle = false;
        wait_detect = true;
      }

       if(detection_3 && !wait_detect) {
        //Si le train est détecté sur Detect_3
        delay(100);
        PN_2_DO();
        
        delay(500);
        PN_1_DO();
        
        sens_tulle_to_brive = true;
      }

      if(detection_1 && sens_tulle_to_brive) {
        //Si le train est détecté sur Detect_1
        delay(100);
        PN_2_UP();
        delay(500);
        PN_1_UP();
        sens_tulle_to_brive = false;
        wait_detect = true;
      }
    }

    PN_Clignote(start_led_PN1, start_led_PN2);
    
    if(wait_detect) {
      int i = 0;
      while(i <= 5000) {
        i++;
        delay(1);
      }
      wait_detect = false;
    }
  }
  if((btnMoveTo > 700) && (btnMoveTo < 710)) {
    //On est en mode transport, l'automatisme ne fonctionne pas
    //Baisser les barrières
    Serial.println("Mode Transport : L'automatisme est désactivé. Les barrières sont baissés");
    if(init_barriere) {
      //On refera une initialisation
      PN_1_DO();
      PN_2_DO();
      FEUX_STOP();
      init_barriere = false;
    }
  }
  delay(1);
}

void PN_1_UP(){
  digitalWrite(sensPN_1, HIGH);
  start_led_PN1 = false;
  digitalWrite(feuPN_1, LOW);
}

void PN_2_UP(){
  digitalWrite(sensPN_2, HIGH);
  start_led_PN2 = false;
  digitalWrite(feuPN_2, LOW);
}

void PN_1_DO(){
  digitalWrite(sensPN_1, LOW);
  start_led_PN1 = true;
}

void PN_2_DO(){
  digitalWrite(sensPN_2, LOW);
  start_led_PN2 = true;
}

void FEUX_STOP(){
  digitalWrite(feuPN_1, LOW);
  digitalWrite(feuPN_2, LOW);
}


void PN_Clignote(boolean led_PN1, boolean led_PN2) {
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > 600) {
    previousMillis = currentMillis;
    if(led_PN1) {
      if(led_PN1_state){
        digitalWrite(feuPN_1, LOW);
        led_PN1_state = false;
      } else {
        digitalWrite(feuPN_1, HIGH);
        led_PN1_state = true;
      }
    }
    if(led_PN2) {
       if(led_PN2_state){
        digitalWrite(feuPN_2, LOW);
        led_PN2_state = false;
      } else {
        digitalWrite(feuPN_2, HIGH);
        led_PN2_state = true;
      }
    }
  }   
}

