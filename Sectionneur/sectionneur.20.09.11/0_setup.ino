void setup() {  
  Serial.begin(9600);
  
  pinMode(SEC_PIN, INPUT_PULLUP);
  pinMode(RLS_PIN, OUTPUT);  

  //-----UDP-----
  Ethernet.begin(mac, section);  
  Udp.begin(localPort);
  

  //-----Leds-----
  LED.begin();
  
  
  //-----Boutons----- 
  pinMode(BTN_0, INPUT_PULLUP);
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  pinMode(BTN_3, INPUT_PULLUP);

  Serial.println("Arduino pret.");
}
