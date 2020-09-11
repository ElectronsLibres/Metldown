void setup()
{
  Serial.begin(9600);
  

  //-----UDP-----
  Ethernet.begin(mac, machine2);
  Udp.begin(localPort);
  
  Serial.println("Machine 2 prête.");


  //-----Leds-----
  LED.begin();
  BOX.begin();

  
  //-----Boutons-----
  multi.begin();

  multi.pinMode(1, INPUT); // Cuve: Switch bascule 
  multi.pinMode(2, INPUT); // Cuve: Bouton instant
  multi.pinMode(3, INPUT); // Boitier: Bouton instant gauche (noir)
  multi.pinMode(4, INPUT); // Boitier: Bouton instant droite (bleu)
  multi.pinMode(5, INPUT); // Boitier: Switch bascule (gris)
  multi.pinMode(6, INPUT); // Boitier: Switch instant haut (jaune)
  multi.pinMode(7, INPUT); // Boitier: Switch instant bas (brun)
  
  multi.pullUp(1, HIGH);  
  multi.pullUp(2, HIGH);  
  multi.pullUp(3, HIGH);  
  multi.pullUp(4, HIGH);  
  multi.pullUp(5, HIGH);  
  multi.pullUp(6, HIGH);  
  multi.pullUp(7, HIGH);
}
