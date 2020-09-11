// === Machine 2 ===

//-----Variables-----
static bool event = false;
static bool reset = true;
static bool flash = true;

static byte happyhour = 0;
static byte buzzers = 0;
static byte clavier = 0;
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
//byte mac[] = { 0x2C, 0xF7, 0xF1, 0x08, 0x17, 0xE3 }; //machine1
byte mac[] = { 0x2C, 0xF7, 0xF1, 0x08, 0x24, 0x71 }; //machine2
//byte mac[] = { 0x2C, 0xF7, 0xF1, 0x08, 0x24, 0x8B }; //test

uint16_t localPort = 5001;
uint16_t mediaPort = 8888;

char message[UDP_TX_PACKET_MAX_SIZE];


//-----Leds-----
#include <Adafruit_NeoPixel.h>

#define PIN 2
#define NUM 15

#define PIN_BOX 3
#define NUM_BOX 6

Adafruit_NeoPixel LED = Adafruit_NeoPixel(NUM, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel BOX = Adafruit_NeoPixel(NUM_BOX, PIN_BOX, NEO_GRB + NEO_KHZ800);


//-----Clavier-----
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {6, 7, 8, 9};
byte colPins[COLS] = {A0, A1, A2, A3}; 

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


//-----Boutons-----
#include <Wire.h>
#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 multi;
