#include <Adafruit_NeoPixel.h>

// Boutons
#define BTN_0 A0
#define BTN_1 A1
#define BTN_2 A2


// RetroLed
#define LED 6


// Strips
#define PIN_1 2
#define NUM_1 58

#define PIN_2 3
#define NUM_2 19

#define PIN_3 4
#define NUM_3 45


// Neopixel
Adafruit_NeoPixel LED_1 = Adafruit_NeoPixel(NUM_1, PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel LED_2 = Adafruit_NeoPixel(NUM_2, PIN_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel LED_3 = Adafruit_NeoPixel(NUM_3, PIN_3, NEO_GRB + NEO_KHZ800);


// Couleurs
uint32_t cVert = LED_1.Color(  0, 255,   0);
uint32_t cJaun = LED_1.Color(255, 255,   0);
uint32_t cRoug = LED_1.Color(255,   0,   0);
uint32_t cMauv = LED_1.Color(255,   0, 255);
uint32_t cBleu = LED_1.Color(  0,   0, 255);
uint32_t cCyan = LED_1.Color(255, 255,   0);
uint32_t cBlan = LED_1.Color(255, 255, 255);


// Setup
void setup()
{
  pinMode(BTN_0, INPUT_PULLUP);
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  
  pinMode(LED, OUTPUT);

  LED_1.begin();
  LED_2.begin();
  LED_3.begin();
}


// Loop
void loop()
{
  boolean btnAlim = digitalRead(BTN_0);
  boolean btnMenu = digitalRead(BTN_1);
  boolean btnMode = digitalRead(BTN_2);

  static uint8_t menu = 0;
  static uint8_t aplat = 0;
  static uint8_t versus = 0;
  static uint8_t rainbow = 0;
  
  static uint16_t teinte = 0;
  static uint8_t  saturation = 255;
  static uint8_t  luminosite = 20;

  static uint32_t couleur;


// Quand le bouton Alim est enfoncé
if(btnAlim == HIGH)
{
  digitalWrite(LED, HIGH);

  // Quand on appuie sur le bouton Menu
  if(btnMenu == 0)
  {
    menu ++;
    if(menu > 3){menu = 0;}
  }


  // Action !!!
  switch(menu)
  {
    // Mode: Aplat
    case 0:
    if(btnMode == 0)
    {
      aplat++;
      if(aplat > 7){aplat = 0;}
    }
    
    teinte = constrain(((8192 * aplat) -1), 0, 65535);
    couleur = LED_1.ColorHSV(teinte, saturation, luminosite);

    LED_1.fill(couleur);
    LED_2.fill(couleur);
    LED_3.fill(couleur);
    break;

    
    // Mode: Versus    
    case 1:
    if(btnMode == 0)
    {
      versus++;
      if(versus > 1){versus = 0;}
    }

    switch(versus)
    {
      case 0:
      LED_1.fill(cRoug,  0, 28);
      LED_1.fill(cBleu, 29, 58);

      LED_2.fill(cRoug,  0,  5);
      
      LED_3.fill(cRoug,  0, 21);
      LED_3.fill(cBleu, 22, 45);
      break;

      case 1:
      LED_1.fill(cBleu,  0, 28);
      LED_1.fill(cRoug, 29, 58);

      LED_2.fill(cBleu,  0,  5);
      
      LED_3.fill(cBleu,  0, 21);
      LED_3.fill(cRoug, 22, 45);
      break;

    }
    break;

    
    // Mode: Rainbow
    case 2:
    if(btnMode == 0)
    {
      rainbow += 5;
      if(rainbow > 255){rainbow = 0;}
    }
    
    teinte  = map(rainbow, 0, 255, 0, 65535);
    couleur = LED_1.ColorHSV(teinte, saturation, luminosite);
    
    LED_1.fill(couleur);
    LED_2.fill(couleur);
    LED_3.fill(couleur);
    break;


    // Mode: Luminosite
    case 3:
    if(btnMode == 0)
    {
      luminosite -= 5;
      if(luminosite < 10){luminosite = 255;}
    }
    
    couleur = LED_1.ColorHSV(teinte, 0, luminosite);

    LED_1.fill(couleur);
    LED_2.fill(couleur);
    LED_3.fill(couleur);
    break;
  }
}


  else
  {
    digitalWrite(LED, LOW);
    
    LED_1.clear();
    LED_2.clear();
    LED_3.clear();
  }
  
  LED_1.show();
  LED_2.show();
  LED_3.show();
  
  delay(200);
}
