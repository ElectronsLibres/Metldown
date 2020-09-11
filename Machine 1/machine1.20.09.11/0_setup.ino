void setup()
{
  Serial.begin(9600);


  //-----UDP-----
  Ethernet.begin(mac, machine1);
  Udp.begin(localPort);
  
  Serial.println("Machine 1 prête.");


  //-----Leds-----
  LED_1.begin();
  LED_2.begin();
  GYRO.begin();


  //-----Boutons-----
  pinMode(BTN_0, INPUT_PULLUP);
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  pinMode(BTN_3, INPUT_PULLUP);
  pinMode(BTN_4, INPUT_PULLUP);
  pinMode(BTN_5, INPUT_PULLUP);
  pinMode(BTN_6, INPUT_PULLUP);

  pinMode(SWT_1, INPUT_PULLUP);
  pinMode(BC1_1, INPUT_PULLUP);
  pinMode(BC1_2, INPUT_PULLUP);
  pinMode(BC1_3, INPUT_PULLUP);
  pinMode(BC1_4, INPUT_PULLUP);

  pinMode(SWT_2, INPUT_PULLUP);
  pinMode(BC2_1, INPUT_PULLUP);
  pinMode(BC2_2, INPUT_PULLUP);
  pinMode(BC2_3, INPUT_PULLUP);
  pinMode(BC2_4, INPUT_PULLUP);

  pinMode(SWT_3, INPUT_PULLUP);
  pinMode(BC3_1, INPUT_PULLUP);
  pinMode(BC3_2, INPUT_PULLUP);
  pinMode(BC3_3, INPUT_PULLUP);
  pinMode(BC3_4, INPUT_PULLUP);
  
  pinMode(CLN_1, INPUT_PULLUP);
  pinMode(CLN_2, INPUT_PULLUP);
  pinMode(CLN_3, INPUT_PULLUP);
}
