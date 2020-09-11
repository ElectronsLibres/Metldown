void loop() {
    
  byte sec = digitalRead(SEC_PIN);

  byte btn0 = digitalRead(BTN_0);
  byte btn1 = digitalRead(BTN_1);
  byte btn2 = digitalRead(BTN_2);
  byte btn3 = digitalRead(BTN_3);

  LED.setPixelColor(0, R, G, B);
  LED.setPixelColor(1, R, G, B);
  LED.setPixelColor(2, R, G, B);

  Serial.println(sec);
  
  Serial.println(btn0);
  Serial.println(btn1);
  Serial.println(btn2);
  Serial.println(btn3);

  static bool ackhappyhour0 = false;
  static bool ackhappyhour1 = false;
  static bool ackhappyhour2 = false;
  static bool ackhappyhour3 = false;
  
  // ------------ Ecoute :  
  int packetSize = Udp.parsePacket();
  
  if(packetSize) {    
    Udp.read(message, UDP_TX_PACKET_MAX_SIZE);
    
    Serial.print("Message recu : ");
    Serial.println(message);

    if(strcmp(message, "ackhappyhour0") == 0) { ackhappyhour0 = true; }
    if(strcmp(message, "ackhappyhour1") == 0) { ackhappyhour1 = true; }
    if(strcmp(message, "ackhappyhour2") == 0) { ackhappyhour2 = true; }
    if(strcmp(message, "ackhappyhour3") == 0) { ackhappyhour3 = true; }
    
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write("acknowledge");
    Udp.endPacket();    

    memset(message, 0, UDP_TX_PACKET_MAX_SIZE);
  }


  // ------------ Envoie :
  if(sec == 0 && ackhappyhour0 == false) {      
    Udp.beginPacket(medialon, mediaPort);
    Udp.write("happyHour0");
    Udp.endPacket();
         
    Udp.beginPacket(machine1, localPort);
    Udp.write("happyHour0");
    Udp.endPacket();
         
    Udp.beginPacket(machine2, localPort);
    Udp.write("happyHour0");
    Udp.endPacket();
    
    Serial.println("Happy Hour terminée.");
    
    ackhappyhour1 = false;
    ackhappyhour2 = false;
    ackhappyhour3 = false;

    digitalWrite(RLS_PIN, LOW);
        
    delay(100);
  }
      Serial.println("test2");
  if(sec == 1 && ackhappyhour1 == false) {      
    Udp.beginPacket(medialon, mediaPort);
    Udp.write("happyHour1");
    Udp.endPacket(); 
         
    Udp.beginPacket(machine1, localPort);
    Udp.write("happyHour1");
    Udp.endPacket(); 
         
    Udp.beginPacket(machine2, localPort);
    Udp.write("happyHour1");
    Udp.endPacket();
    
    Serial.println("Happy Hour 1 commence.");

    ackhappyhour0 = false;
    
    digitalWrite(RLS_PIN, HIGH);
    
    delay(100);
  }

  //---Fonctions---
  selection();
  boutons();
  

  LED.show();
  delay(10);
}
