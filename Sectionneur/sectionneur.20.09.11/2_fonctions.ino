void selection(){
  byte btn0 = digitalRead(BTN_0);
  byte btn1 = digitalRead(BTN_1);

  byte sec = digitalRead(SEC_PIN);

  //---
  if(btn0 == 1 && sec == 1){
    if(mode > 0){mode--;}
    else{mode = modeMax;}
    Serial.println(btn0);
  }
  
  if(btn1 == 1 && sec == 1){
    if(mode < modeMax){mode++;}
    else{mode = 0;}
    Serial.println(btn1);
  }

  if(mode == 0){R = 33; G = 33; B = 33;}
  else if(mode == 1){R = 50; G = 0; B = 0;}
  else if(mode == 2){R = 0; G = 50; B = 0;}
  else if(mode == 3){R = 0; G = 0; B = 50;}

  LED.setPixelColor(0,  R, G, B);
}

void boutons(){
    
  byte btn2 = digitalRead(BTN_2);
  byte btn3 = digitalRead(BTN_3);
  
  byte sec = digitalRead(SEC_PIN);

  if(btn2 == 1 && sec == 1){
    LED.setPixelColor(1,  R, G, B);
    
    Serial.println(btn2);

    //Udp.beginPacket(medialon, mediaPort);
    //if(mode == 0){Udp.write("audio0");}
    //if(mode == 1){Udp.write("audio2");}
    //if(mode == 2){Udp.write("audio4");}
    //if(mode == 3){Udp.write("audio6");}
    //Udp.endPacket();   
  }
  else{
    LED.setPixelColor(1, 0);
  }

  if(btn3 == 1 && sec == 1){
    LED.setPixelColor(2, R, G, B);
    
    Serial.println(btn3);

    //Udp.beginPacket(medialon, mediaPort);
    //if(mode == 0){Udp.write("audio1");}
    //if(mode == 1){Udp.write("audio3");}
    //if(mode == 2){Udp.write("audio5");}
    //if(mode == 3){Udp.write("audio7");}
    //Udp.endPacket();   
  }
  else{
    LED.setPixelColor(2, 0);
  }
}
