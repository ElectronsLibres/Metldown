//-----UDP-----

/*
 * Reception de message, lecture et accusé de réception
 */
void udpIn(){
  int packetSize = Udp.parsePacket();
  
  if(packetSize){    
    Udp.read(message, UDP_TX_PACKET_MAX_SIZE);
    
    Serial.print("Message recu: ");
    Serial.println(message);

    if(strcmp(message, "happyHour0") == 0) { event = true; happyhour = 0; }
    if(strcmp(message, "happyHour1") == 0) { event = true; happyhour = 1; }
    if(strcmp(message, "happyHour2") == 0) { event = true; happyhour = 2; }
    if(strcmp(message, "happyHour3") == 0) { event = true; happyhour = 3; }
    if(strcmp(message, "konami") == 0) { event = true; konami = true;}

  }
  else{memset(message, 0, UDP_TX_PACKET_MAX_SIZE);}
}



//-----Events-----

/*
 * Définit pour chaque led une couleur aléatoire
 * 
 * trigger = état du déclancheur
 * timer = durée de l'effet
 * 
 */
void allRandom(byte &trigger, uint16_t timer, byte num){
  static uint16_t t = 0;
  
  for(byte i = 0; i < NUM_1; i++){rainbowRandom(1, i, num);}
  for(byte j = 0; j < NUM_2; j++){rainbowRandom(2, j, num);}

  if(t == timer){    
    t = 0;
    trigger = 0;
    Serial.println("allRandom: Fin");
  }
  else{t++;}

  delay(100);
}


//allrandom (suite)
void rainbowRandom(byte strip, byte led, byte num){
  byte m = random(num);
  byte r;
  byte g;
  byte b;  

  if(m == 0){r = 0; g = 0; b = 0;}
  else if(m == 1){r = 80; g =  0; b =  0;}
  else if(m == 2){r =  0; g = 80; b =  0;}
  else if(m == 3){r =  0; g =  0; b = 80;}
  else if(m == 4){r = 80; g = 80; b =  0;}
  else if(m == 5){r = 80; g =  0; b = 80;}
  else if(m == 6){r =  0; g = 80; b = 80;}

  if(strip == 1){LED_1.setPixelColor( led, r, g, b);}
  if(strip == 2){LED_2.setPixelColor( led, r, g, b);}
}


/*
 * Gyrophare plat
 * 
 * ecart = distance entre les leds qui se chasent (codé pour 3 sur 36)
 * trace = quantité de leds restant allumées derrière le chase
 * 
 */
void gyrophare(byte ecart, byte trace){
  
  static byte p1 = 0;
  byte p2 = 0;
  byte p3 = 0;  
  
  p2 = p1 + ecart;
  p3 = p2 + ecart; 

  byte b1, b2, b3;

  if(p1 < trace){
    b1 = p1 + (ecart - trace);
    b2 = p2 + (ecart - trace);
    b3 = p3 + (ecart - trace); 
  }
  else{
    b1 = p1 - trace;
    b2 = p2 - trace;
    b3 = p3 - trace; 
  } 

  GYRO.setPixelColor(p1, 255, 0, 0);
  GYRO.setPixelColor(p2, 255, 0, 0);
  GYRO.setPixelColor(p3, 255, 0, 0);
  
  GYRO.setPixelColor(b1, 0, 0, 0);
  GYRO.setPixelColor(b2, 0, 0, 0);
  GYRO.setPixelColor(b3, 0, 0, 0);

  if(p1 == (ecart-1) ){p1 = 0;}
  else{p1++;}

  delay(20);
}




//konamiCode (suite)
void konamiEffect (){
  static uint16_t t = 1000;
  
  if(t > 0){
    byte r = (t / 4);
    byte g = 35 - (t / 30);    
    
    uint32_t c = LED_1.Color(r, g, 0);
    
    t--;
    LED_1.fill(c);
    LED_2.fill(c);
  }
  else{
    t = 1000;
    konami = 0;
    Serial.println("konamiEffect: Fin");}  
}



//-----Reset-----



//-----Routine-----
void global(){
    static uint16_t t = 6000;
    
    int leds_1[] = {0,1,2,4,5,6,7,8,10,11,12,13,14,15,16,17,19}; //17    
    int leds_2[] = {2,3,4,7,8,9,10,11,12,13,14}; // 11

    static int val_1[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    static int val_2[] = {0,0,0,0,0,0,0,0,0,0,0};

  if (t == 0){   
    for (byte i = 0; i < 17; i++){val_1[i] = random(2);}   
    for (byte i = 0; i < 11; i++){val_2[i] = random(2);}
    t = random(4000, 6000);
  }
  else{t--;}

  //Applique les couleurs aux leds
  for (byte i = 0; i < 17; i++){
    if(val_1[i] == 1){LED_1.setPixelColor(leds_1[i], R, G, B);}
    else{LED_1.setPixelColor(leds_1[i], 0, 0, 0);}
  }
  for (byte i = 0; i < 17; i++){
    if(val_2[i] == 1){LED_2.setPixelColor(leds_2[i], R, G, B);}
    else{LED_2.setPixelColor(leds_2[i], 0, 0, 0);}
  }
}


//Retro éclairage des cadrans
void cadran(byte r, byte g, byte b){  
  bool btn1 = digitalRead(SWT_1);
  bool btn2 = digitalRead(SWT_2);
  bool btn3 = digitalRead(SWT_3);

  if(btn1 == 0){LED_1.setPixelColor(3, 0);}
  else{LED_1.setPixelColor(3, r, g, b);}
  
  if(btn2 == 1){LED_1.setPixelColor(9, 0);}
  else{LED_1.setPixelColor(9, r, g, b);}
  
  if(btn3 == 1){LED_1.setPixelColor(15, 0);}
  else{LED_1.setPixelColor(15, r, g, b);}
}



//-----Interactions-----

// bouton pressé
void temoin (byte pin, byte pixel, byte cr, byte cg, byte cb, bool nc){
  bool btn = digitalRead(pin);
  
  if(btn == nc){LED_1.setPixelColor(pixel, cr, cg, cb);}
  else{LED_1.setPixelColor(pixel, R, G, B);}    
}



/*
 * Quand les boutons Stop sont enfoncé, fait tout clignoter en rouge
 * 
 * timer = durée du blink
 * delai = cooldown entre les blinks
 * 
 */
void keyStop(byte timer, byte delai){
  static byte t = 0;
  static bool trigger = false;

  
  if(trigger){allBlink(trigger, timer, 90, 0, 0);}

  if(t > 0){t--;}  
  else{
    bool btn1 = digitalRead(BTN_1);
    bool btn2 = digitalRead(BTN_4);
    bool btn3 = digitalRead(BTN_6);
    bool btn4 = digitalRead(CLN_2);
      
    if(btn1 || !btn2 || !btn3 || btn4){trigger = true; t = delai;}
  }
}



//
void keyUp(){
  static bool trigger = false;
  
  bool btn1 = digitalRead(BTN_0);
  bool btn2 = digitalRead(CLN_1);

  if(!btn1 || !btn2){trigger = true;}

  if(trigger){chaseTop(trigger, 80);}
}


//
void keyPlay(){
  static bool trigger = false;
  
  bool btn1 = digitalRead(BTN_2);
  bool btn2 = digitalRead(BTN_3);
  bool btn3 = digitalRead(BTN_5);
  bool btn4 = digitalRead(CLN_3);

  if(!btn1 || btn2 || btn3 || !btn4){trigger = true;}

  if(trigger){chaseBot(trigger, 100);}
}



/*
 * Appuyer sur les 3 Push en un temps donné pour activer une variable
 * 
 * push  = true si les 3 push sont enfoncé avant la fin du timer
 * timer = temps nécéssaire pour activer les 3 punshs avant reset
 * 
 */
void buzzerCode(uint16_t timer){

  bool btn1 = digitalRead(BC1_2);
  bool btn2 = digitalRead(BC2_2);
  bool btn3 = digitalRead(BC3_2);
  
  static bool lock1 = false;
  static bool lock2 = false;
  static bool lock3 = false;

  static uint16_t t = 0;
  
  //Compte à rebours + Reset
  if(t > 0){t--;}
  else{
    lock1 = false;
    lock2 = false;
    lock3 = false;
  }

  //Validation
  if(lock1 && lock2 && lock3){
    t = 0;
    lock1 = false;
    lock2 = false;
    lock3 = false;
    event = true;
    buzzers = 1;
    Udp.beginPacket(machine2, localPort);
    Udp.write("buzzers");
    Udp.endPacket();
  }


  //Lance le chrono
  if(btn1 == 0 || btn2 == 0 || btn3 == 0){
    if(t == 0){t = timer;}
  }


  //Enregistre les Pushs
  if(btn1 == 0){lock1 = true;}    
  if(btn2 == 0){lock2 = true;}    
  if(btn3 == 0){lock3 = true;}


  //Applique les couleurs
  if(lock1){
    LED_1.setPixelColor( 2, 0, 50, 0);
    LED_1.setPixelColor( 8, 0, 50, 0);
    LED_1.setPixelColor(14, 0, 50, 0);
  }    
  if(lock2){
    LED_1.setPixelColor( 1, 0, 0, 50);
    LED_1.setPixelColor( 7, 0, 0, 50);
    LED_1.setPixelColor(13, 0, 0, 50);
  }    
  if(lock3){
    LED_1.setPixelColor( 0, 50, 10, 0);
    LED_1.setPixelColor( 6, 50, 10, 0);
    LED_1.setPixelColor(12, 50, 10, 0);
  }
}



/*
 * Ajoute un effet quand un buzzer est enfoncé
 */
void buzzerPress(uint16_t cooldown){  
  bool btn1 = digitalRead(BC1_2);
  bool btn2 = digitalRead(BC2_2);
  bool btn3 = digitalRead(BC3_2);
  
  static bool push1 = false;
  static bool push2 = false;
  static bool push3 = false;

  static byte p1 = 0;
  static byte p2 = 0;
  static byte p3 = 0;

  if(p1 > 0){p1--;}
  else if(btn1 == 0){p1 = cooldown; push1 = true;}
  
  if(p2 > 0){p2--;}
  else if(btn2 == 0){p2 = cooldown; push2 = true;}
  
  if(p3 > 0){p3--;}
  else if(btn3 == 0){p3 = cooldown; push3 = true;}

  if(push1){allBlink(push1, 2,  0, 90,  0);}
  if(push2){allBlink(push2, 2,  0,  0, 90);}
  if(push3){allBlink(push3, 2, 90, 20,  0);}
}




//-----Effets-----

void chaseTop(bool &trigger, uint16_t timer){
  static uint16_t t = 0;

  byte p = map(t, 0, timer, 0, NUM_2);

  LED_2.setPixelColor(p, 0, 90, 0);

  if(p > 0){
    byte b = p-1;
    LED_2.setPixelColor( b, 0);
  }  

  if(t < timer){t++;}
  else{t = 0; trigger = false;}
}


void chaseBot(bool &trigger, uint16_t timer){
  static uint16_t t = 0;

  byte p = map(t, 0, timer, 0, NUM_1);

  LED_1.setPixelColor(p, 0, 90, 0);

  if(p > 0){
    byte b = p-1;
    LED_1.setPixelColor( b, 0);    
  }

  if(t < timer){t++;}
  else{t = 0; trigger = false;}
}


/*
 * 
 */
void allBlink(bool &trigger, uint16_t timer, byte r, byte g, byte b){

  static byte t = 0;
  static bool m = 1;

  uint32_t c = LED_1.Color(r, g, b);

  if(m){
    LED_1.fill(c);
    LED_2.fill(c);
  }
  else{
    LED_1.clear();
    LED_2.clear();
  }
  
  if(t == timer){
    t = 0;
    trigger = false;
    LED_1.clear();
    LED_2.clear();
    }
  else{t++;}

  if((t % 2) == 0){m = 1;}
  else{m = 0;}  

  delay(100);  
}


//Effet sur les girophares
void clignotte(byte r, byte g, byte b){
  static byte t = 0;
  static byte u = 0;  
  
  bool btn1 = digitalRead(BC1_1);
  bool btn2 = digitalRead(BC2_1);
  bool btn3 = digitalRead(BC3_1);

  if(btn1 == 0 || btn2 == 0 || btn3 == 0){

    t++;
    if(t == 10){
      t = 0;
      u++;      
    }
    if ((u % 2) == 0){
      LED_1.setPixelColor(19, r, g, b);
      LED_2.setPixelColor( 6, r, g, b);
      LED_2.setPixelColor(14, r, g, b);
    }
    else{
      LED_1.setPixelColor(19, 0);
      LED_2.setPixelColor( 6, 0);
      LED_2.setPixelColor(14, 0);
    }
  }
  else{    
    t=0;
    u=0;
    
    LED_1.setPixelColor(19, 0);
    LED_2.setPixelColor( 6, 0);
    LED_2.setPixelColor(14, 0);
    
  }
}


void debug(){
  bool btn1 = digitalRead(BTN_2);
  bool btn2 = digitalRead(BTN_3);
  bool btn3 = digitalRead(BTN_5);
  bool btn4 = digitalRead(CLN_3);
  
  bool btn5 = digitalRead(BTN_1);
  bool btn6 = digitalRead(BTN_4);
  bool btn7 = digitalRead(BTN_6);
  bool btn8 = digitalRead(CLN_2);

  Serial.println(btn1);
  Serial.println(btn2);
  Serial.println(btn3);
  Serial.println(btn4);
  Serial.println("");
  
  Serial.println(btn5);
  Serial.println(btn6);
  Serial.println(btn7);
  Serial.println(btn8);
  Serial.println("");
  Serial.println("-----");
  Serial.println("");
}
