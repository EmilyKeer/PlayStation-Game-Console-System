/******************************************************
*                   TAT Play Station                  *
*      Author: Team 3       Bohan Shi  20598919       *
*                           Keer Liu   20668904       *
*                           Zhaowei Wu 20653255       *
*                    Version: 0.7.1                   *
*          *** Read The Manual Before Play ***        *
*******************************************************/
#include <delay.h>
#include <FillPat.h>
#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h>
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>
#include <string.h> 


//All LED pins
#define LED1 35
#define LED2 34
#define LED3 33
#define LED4 2

//All button pins
const int PBD1 = 25;
const int PBU1 = 18; 
const int PBC1 = PUSH2;
const int PBC2 = PUSH1;

//Initial button state
int buttonDownState = 0;
int buttonUpState = 0;
int buttonConfirmState = 1;
int buttonCancelState = 1;

int GameMode = 0;
int NumPlayer = 0;

struct stone{
    int row;
    int col;
    int type;
};

void setup() {
  Serial.begin(9600);
  pinModInit();
  gameOLEDInit();
  printWelcome();
  printLoading();
  randomSeed(analogRead(0));
}

void loop() {
  buttonInit();
  GameMode = printSelectionMenu();
  clearScreen();
  
  playGame(GameMode,NumPlayer);
}


