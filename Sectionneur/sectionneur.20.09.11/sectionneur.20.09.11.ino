// === Sectionneur ===

//-----Variables-----
static byte R = 50;
static byte G = 35;
static byte B = 0;

static byte mode = 0;
#define modeMax 3


//-----UDP-----
#include <SPI.h>        
#include <Ethernet.h>
#include <EthernetUdp.h>

IPAddress section(192, 168, 1, 40);
IPAddress machine1(192, 168, 1, 41);
IPAddress machine2(192, 168, 1, 42);
IPAddress medialon(255, 255, 255, 255);

byte mac[] = { 0x2C, 0xF7, 0xF1, 0x08, 0x24, 0x81 }; //section
//byte mac[] = { 0x2C, 0xF7, 0xF1, 0x08, 0x17, 0xE3 }; //machine1
//byte mac[] = { 0x2C, 0xF7, 0xF1, 0x08, 0x24, 0x71 }; //machine2

uint16_t localPort = 5001;
uint16_t mediaPort = 8888;

EthernetUDP Udp;

char message[UDP_TX_PACKET_MAX_SIZE];


//-----Leds-----
#include <Adafruit_NeoPixel.h>

#define PIN 13
#define NUM 3

Adafruit_NeoPixel LED = Adafruit_NeoPixel(NUM, PIN, NEO_GRB + NEO_KHZ800);

//-----Sectionneur-----
#define SEC_PIN 12
#define RLS_PIN 3


//-----Boutons-----
#define BTN_0 11
#define BTN_1 10
#define BTN_2 9
#define BTN_3 8
