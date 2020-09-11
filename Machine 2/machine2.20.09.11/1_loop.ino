void loop(){

  debug();

  udpIn();
  
  if(event){
    if(happyhour){
      Serial.println("Event: happyhour");
      allRandom(happyhour, 65000, 3);
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
    flash = true;
     
    LED.clear();
    
    aleatoire(4, 70);
    aleatoire(5, 70);
    aleatoire(6, 100);

    aleatoire(7, 70);
    aleatoire(8, 70);
    aleatoire(9, 70);
    
    aleatoire(11, 70);

    aleatoire(10, 0);
    aleatoire(12, 0);
    
    reset = false;
  }  
  else{
    //-----Routine-----
    decompte();
    flashEffect();
    
    //-----Interactions-----
    clavierCode();
    
    allumage();
    danger();
    
    vert();
    rouge();
    toggle();
    teinte();
    
    konamiCode();
  }

  LED.show();
  BOX.show();

  delay(10);
}
