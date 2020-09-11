void loop()
{
  udpIn();

  //debug();

  if(event){
    if(happyhour){
      Serial.println("Event: happyhour");
      allRandom(happyhour, 65000, 3);
      gyrophare(12, 3);
    }
    else if(buzzers){
      Serial.println("Event: buzzers");
      allRandom(buzzers, 40, 7);
    }
    else if(konami){
      Serial.println("Event: konami");
      konamiEffect();
    }
    else{
      event = false;
      reset = true;
    }
  }
  else if(reset){
    LED_1.clear();
    LED_2.clear();
    GYRO.clear();
    
    reset = false;
  }
  else{
    //-----Routine-----
    global();
    cadran(255, 220, 220);
    
    //-----Interactions-----    
    clignotte(255, 0, 0);
    
    //temoin bouton sur le tableau
    temoin(BC1_3,  4, 90,  0,  0, 0);
    temoin(BC1_4,  5,  0, 90,  0, 0);
    temoin(BC2_3, 10, 90,  0,  0, 0);
    temoin(BC2_4, 11,  0, 90,  0, 0);
    temoin(BC3_3, 16, 90,  0,  0, 0);
    temoin(BC3_4, 17,  0, 90,  0, 0);

    keyStop(6, 150);
    keyPlay();
    keyUp();
    
    buzzerCode(500);
    buzzerPress(2000);
  } 
  
  LED_1.show();
  LED_2.show();
  GYRO.show();
  
  delay(10);
}
