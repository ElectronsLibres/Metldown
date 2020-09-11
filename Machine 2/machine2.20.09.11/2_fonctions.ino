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
    if(strcmp(message, "buzzers") == 0) { event = true; buzzers = 1; }
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
  
  for(byte i = 0; i < NUM; i++){rainbowRandom(i, num);}

  if(t == timer){    
    t = 0;
    trigger = 0;
    Serial.println("allRandom: Fin");
  }
  else{t++;}

  delay(100);
}


//allrandom (suite)
void rainbowRandom(byte led, byte num){
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

  LED.setPixelColor(led, r, g, b);
}



//konamiCode (suite)
void konamiEffect (){
  static uint16_t t = 1000;
  
  if(t > 0){
    byte r = (t / 4);
    byte g = 35 - (t / 30);    
    
    uint32_t c = LED.Color(r, g, 0);
    
    t--;
    LED.fill(c);
  }
  else{t = 1000; konami = 0; Serial.println("konamiEffect: Fin");}  
}



//-----Reset-----

/*
 * Allume ou non une led
 * 
 * pixel = Led traitée
 * taux  = Pourcentage de chance que la led soit allumée 
 */
void aleatoire (byte pixel, byte taux){
  byte valeur = random(0, 100);
  
  if(valeur <= taux)
       {LED.setPixelColor(pixel, R, G, B);}
  else {LED.setPixelColor(pixel, 0);}
}



//-----Routine-----
void decompte(){
  static uint16_t t = 5000;

  if(t == 3500){flash = true;}
  if(t == 1500){flash = true;}
  if(t == 0){reset = true; t = random(4000, 6000);}
  
  t--;
}


/*
 * Fait clignoter la box vitrée
 */
void flashEffect(){  
  uint32_t couleur = 15790335;
  static byte t = 0;

  if(flash == true){
    if(t == 11) { BOX.fill(couleur); }
    if(t == 10) { BOX.clear(); }
    if(t ==  6) { BOX.fill(couleur); }
    if(t ==  5) { BOX.clear(); }
    if(t ==  1) { BOX.fill(couleur); }

    if(t == 0){
      BOX.clear();
      t = random(2, 15);
      flash = false;
    }
    t--;
  }
}



//-----Interactions-----

/*
 * Lit et réagit au clavier code
 */
void clavierCode(){
  static byte jeu = 0;
  static byte pos = 0;
  
  char key = keypad.getKey();

  if (key != NO_KEY){
    if(key == 'A'){jeu = 1; pos = 0;}
    if(key == 'B'){jeu = 2; pos = 0;}
    if(key == 'C'){jeu = 3; pos = 0;}
    if(key == 'D'){jeu = 4; pos = 0;}
    
    //Serial.println(key);
    
    decodage(jeu, pos, key);
  }
}


//clavier (suite)
void decodage(byte jeu, byte &pos, char key){
  if(jeu == 1){
    int code[] = {'1', '6', '0', '2'};
    if(key == code[pos]){pos++;}
    else{pos = 0;}
    if(pos == 4){
      pos = 0;
      
      Udp.beginPacket(medialon, mediaPort);
      Udp.write("code1");
      Udp.endPacket();
      
      Serial.println("Anno 1602");}
  }
  
  if(jeu == 2){
    int code[] = {'1', '9', '4', '2'};
    if(key == code[pos]){pos++;}
    else{pos = 0;}
    if(pos == 4){
      pos = 0;
      
      Udp.beginPacket(medialon, mediaPort);
      Udp.write("code2");
      Udp.endPacket();
      
      Serial.println("Battlefield 1942");}
  }
  
  if(jeu == 3){
    int code[] = {'2', '0', '7', '7'};
    if(key == code[pos]){pos++;}
    else{pos = 0;}
    if(pos == 4){
      pos = 0;
      
      Udp.beginPacket(medialon, mediaPort);
      Udp.write("code3");
      Udp.endPacket();
      
      Serial.println("Cyberpunk 2077");}
  }
  
  if(jeu == 4){
    int code[] = {'2', '0', '0', '0'};
    if(key == code[pos]){pos++;}
    else{pos = 0;}
    if(pos == 4){
      pos = 0;
      
      Udp.beginPacket(medialon, mediaPort);
      Udp.write("code4");
      Udp.endPacket();
      
      Serial.println("Dune 2000");}
  }
}




void allumage (){
  bool btn = multi.digitalRead(1);
  
  static byte t = 0;
  static bool reset = 0; 


  if(btn == 1 && reset == 1){
    t = 0;
    reset = 0;
    
    LED.setPixelColor(0, 0);
    LED.setPixelColor(1, 0);
    LED.setPixelColor(2, 0);
    
    LED.setPixelColor(6, 0); 
  }
  else if(btn == 1){
    t = 0;
  }
  else if (t < 4){
    t++;
    reset = 1;
    
    LED.setPixelColor(0, R, G, B);
    LED.setPixelColor(6, 0);
  }
  else if(t < 8){
    t++;    
    LED.setPixelColor(1, R, G, B);
    LED.setPixelColor(6, 0);
  }
  else if(t < 12){
    t++;    
    LED.setPixelColor(2, R, G, B);
    LED.setPixelColor(6, 0);
  }
  else if(t < 18){
    t++;
  }
  else{
    LED.setPixelColor(0, R, G, B);
    LED.setPixelColor(1, R, G, B);
    LED.setPixelColor(2, R, G, B);
    
    LED.setPixelColor(6, R, G, B);  
  }
}


void danger (){   
  bool btn = multi.digitalRead(2);
  
  static uint16_t t = 0;

  if(btn == 1){
    t = 0;
    LED.setPixelColor(6, R, G, B);
  }
  else if(t < 200){
    t++;
    LED.setPixelColor(6, 50, 0, 0);
  }
  
  byte r = R + (t / 10);
  byte g = G - ((G * t)/ 200);
  
  LED.setPixelColor(3, r, g, B);
}


void vert (){
  static bool reset = 0; 
  static uint32_t couleur;
  
  bool btn = multi.digitalRead(3); 

  if(btn == 1 && reset == 0){
    couleur = LED.getPixelColor(13);
  }
  else if(btn == 1 && reset == 1){
    reset = 0;        
    LED.setPixelColor(14, couleur);
  }
  else{
    reset = 1;
    LED.setPixelColor(14, 0,  50, 0);
    LED.setPixelColor(10, 0, 255, 0);
  }
}


void rouge (){
  static bool reset = 0; 
  static uint32_t couleur;
  
  bool btn = multi.digitalRead(4); 

  if(btn == 1 && reset == 0){
    couleur = LED.getPixelColor(14);
  }
  else if(btn == 1 && reset == 1){
    reset = 0;        
    LED.setPixelColor(13, couleur);
  }
  else{
    reset = 1;
    LED.setPixelColor(13,  50, 0, 0);    
    LED.setPixelColor(12, 255, 0, 0);
  }
}


void toggle(){  
  bool btn = multi.digitalRead(5);

  if(btn == 1){
    LED.setPixelColor(13, 0);
    LED.setPixelColor(14, 0);
  }
  else{
    LED.setPixelColor(13, R, G, B);
    LED.setPixelColor(14, R, G, B);
  }  
}


void teinte(){
  bool top = multi.digitalRead(6);
  bool bot = multi.digitalRead(7);

  static bool s = false;
  static byte t = 5;

  if (top == 0 && t < 9){t++; s = true; reset = true;}
  if (bot == 0 && t > 0){t--; s = true; reset = true;}

  if(s){
    if(t == 0){R = 30; G = 65; B = 0;}
    if(t == 1){R = 35; G = 50; B = 0;}
    if(t == 3){R = 40; G = 45; B = 0;}
    if(t == 4){R = 45; G = 40; B = 0;}
    if(t == 5){R = 50; G = 35; B = 0;}
    if(t == 6){R = 53; G = 30; B = 0;}
    if(t == 7){R = 56; G = 25; B = 0;}
    if(t == 8){R = 59; G = 20; B = 0;}
    if(t == 9){R = 62; G = 15; B = 0;}
    s = false;
  }
}


/*
 * Vérifie la séquence de bouton correspondant au Konami Code
 */
void konamiCode (){
  static byte code = 0;

  byte rebond = 200;

  bool ab     = multi.digitalRead(5);
  bool bas    = multi.digitalRead(7);
  bool haut   = multi.digitalRead(6);
  bool gauche = multi.digitalRead(3);
  bool droite = multi.digitalRead(4);

  if(haut == 0 && code != 1 && code !=2)   { code = 0;}
  if(bas == 0  && code != 3 && code !=4)   { code = 0;}
  if(gauche == 0 && code != 5 && code !=7) { code = 0;}
  if(droite == 0 && code != 6 && code !=8) { code = 0;}
  
  if(code == 10 && ab == 0) {
    event = true;
    konami = 1;
    code = 0;
    Udp.beginPacket(machine1, localPort);
    Udp.write("konami");
    Udp.endPacket();
  }
  else if(code == 9 && ab == 1)     { code++; delay(rebond); }
  else if(code == 8 && droite == 0) { code++; delay(rebond); }
  else if(code == 7 && gauche == 0) { code++; delay(rebond); }
  else if(code == 6 && droite == 0) { code++; delay(rebond); }
  else if(code == 5 && gauche == 0) { code++; delay(rebond); }
  else if(code == 4 && bas == 0)    { code++; delay(rebond); }
  else if(code == 3 && bas == 0)    { code++; delay(rebond); }
  else if(code == 2 && haut == 0)   { code++; delay(rebond); }
  else if(code == 1 && haut == 0)   { code++; delay(rebond); }
  else if(code == 0 && ab == 0)     { code++; delay(rebond); }
}



void debug(){
  
  bool btn1 = multi.digitalRead(1);
  bool btn2 = multi.digitalRead(2);
  bool btn3 = multi.digitalRead(3);
  bool btn4 = multi.digitalRead(4);
  bool btn5 = multi.digitalRead(5);
  bool btn6 = multi.digitalRead(6);
  bool btn7 = multi.digitalRead(7);

  if(btn1){Serial.println("1");}
  if(!btn2){Serial.println("2");}
  if(!btn3){Serial.println("3");}
  if(!btn4){Serial.println("4");}
  if(btn5){Serial.println("5");}
  if(!btn6){Serial.println("6");}
  if(!btn7){Serial.println("7");}
}
