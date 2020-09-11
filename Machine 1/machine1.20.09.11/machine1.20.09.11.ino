//-----Variables-----
static bool event = false;
static bool reset = true;

static byte happyhour = 0;
static byte buzzers = 0;
static byte konami = 0;

static byte R = 50;
static byte G = 35;
static byte B = 0;


//-----UDP-----
#include <SPI.h>        
#include <Ethernet.h>
#include <EthernetUdp.h>

EthernetUDP Udp;

IPAddress section(192, 168, 1, 40);
IPAddress machine1(192, 168, 1, 41);
IPAddress machine2(192, 168, 1, 42);
IPAddress medialon(255, 255, 255, 255);

//byte mac[] = { 0x2C, 0xF7, 0xF1, 0x08, 0x24, 0x81 }; //section
byte mac[] = { 0x2C, 0xF7, 0xF1, 0x08, 0x17, 0xE3 }; //machine1
//byte mac[] = { 0x2C, 0xF7, 0xF1, 0x08, 0x24, 0x71 }; //machine2

uint16_t localPort = 5001;
uint16_t mediaPort = 8889;

char message[UDP_TX_PACKET_MAX_SIZE];


//-----Leds-----
#include <Adafruit_NeoPixel.h>

//bas
#define PIN_1 2
#define NUM_1 20

//haut
#define PIN_2 3
#define NUM_2 15

//gyro
#define PIN_3 5
#define NUM_3 24

Adafruit_NeoPixel LED_1 = Adafruit_NeoPixel(NUM_1, PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel LED_2 = Adafruit_NeoPixel(NUM_2, PIN_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel GYRO  = Adafruit_NeoPixel(NUM_3, PIN_3, NEO_GRB + NEO_KHZ800);


//-----Boutons-----
//console 1
#define BTN_0 22  // Commande Haut
#define BTN_1 23  // Commande Stop
#define BTN_2 24  // Commande Droite

#define SWT_1 25  // Switch
#define BC1_1 26  // Bouton co-Push
#define BC1_2 27  // Bouton Push
#define BC1_3 28  // Bouton gauche
#define BC1_4 29  // Bouton droite

//console 2
#define BTN_3 32  // Commande Play
#define BTN_4 33  // Commande Stop

#define SWT_2 34  // Switch
#define BC2_1 35  // Bouton co-Push
#define BC2_2 36  // Bouton Push
#define BC2_3 37  // Bouton gauche
#define BC2_4 38  // Bouton droite

//console 3
#define BTN_5 42  // Commande Play
#define BTN_6 43  // Commande Stop

#define SWT_3 44  // Switch
#define BC3_1 45  // Bouton co-Push
#define BC3_2 46  // Bouton Push
#define BC3_3 47  // Bouton gauche
#define BC3_4 48  // Bouton droite

//colonne
#define CLN_1 A14  // Commande Haut
#define CLN_2 A15  // Commande Stop
#define CLN_3 A13  // Commande Bas
