/****************************************************************************
 * Hamster Game Content
 * SinglePlayer Game Currently
 * Version 0.6.0
 * With GameUI and Mistake count
 */
 
const int WAMlevel12 = 10;
const int WAMlevel23 = 20;
 
int GameHamster(){
    unsigned long timeStart,randomNum,preRandomNum = 0;
    int count = 0,fail = 0,buttonPressed = 0,unitLength = 2000,turn = 1;
    
    while(fail<5){
        if(count >= WAMlevel12 && count < WAMlevel23){
            unitLength = 1000;
        }else if(count >=WAMlevel23){
            unitLength = 500;
        }
            
        randomNum = random(1,5);
        OrbitOledSetCursor(0,2);
        OrbitOledPutString("| |=| |=| |=| |");
        OrbitOledSetCursor(randomNum+3*(randomNum-1),2);
        OrbitOledPutChar('*');
        LEDHelpStart(randomNum);
        
        timeStart = millis();
        buttonPressed = gameButtonPressed(timeStart,unitLength);
        
        if(buttonPressed == randomNum){
            count++;
            buttonPressed = 0;
          }else{
              fail++;
              buttonPressed = 0;
            }
            turn++;
            preRandomNum = randomNum;
            OrbitOledSetCursor(6,3);
            OrbitOledPutChar(fail+'0');
            OrbitOledSetCursor(0,2);
            OrbitOledPutString("| |=| |=| |=| |");
            Serial.println(fail); //Temp Test * Delete Me *
            delay(200);
            LEDHelpStop(randomNum);
      }
      return count;
  }


/********************************************************************
*                         Button Press Function                     *
*      For Game WacAMole                    Version 0.5.0           *
*********************************************************************/
int gameButtonPressed(unsigned long timeStart,int unitLength){
    unsigned long timeLoc = millis();
     while(timeLoc<=timeStart+unitLength){
       buttonDownState = digitalRead(PBD1);
       buttonUpState = digitalRead(PBU1);
       buttonConfirmState = digitalRead(PBC1);
       buttonCancelState = digitalRead(PBC2);
       if(buttonDownState == 1){
          while(timeLoc<=timeStart+unitLength){
              buttonDownState = digitalRead(PBD1);
              if(buttonDownState == 0){
                return 4;
              }
              delay(15);
              timeLoc = millis();
            }
         }
         delay(15); 
       if(buttonUpState == 1){
          while(timeLoc<=timeStart+unitLength){
              buttonUpState = digitalRead(PBU1);
              if(buttonUpState == 0){
                return 3;
              }
              delay(15);
              timeLoc = millis();
            }
         }
         delay(15); 
       if(buttonCancelState == 0){
          while(timeLoc<=timeStart+unitLength){
              buttonCancelState = digitalRead(PBC2);
              if(buttonCancelState == 1){
                return 1;
              }
              delay(15);
              timeLoc = millis();
            }
         }
         delay(15); 
       if(buttonConfirmState == 0){
          while(timeLoc<=timeStart+unitLength){
              buttonConfirmState = digitalRead(PBC1);
              if(buttonConfirmState == 1){
                return 2;
              }
              delay(15);
              timeLoc = millis();
            }
        }
       timeLoc = millis();
     }
     return 0;
 }

/*****************************************************************
*                    LED Aid System Function                     *
*    Input: random number in the game                            *
******************************************************************/
 void LEDHelpStart(int randomnum){
    if(randomnum == 1){digitalWrite(LED4, HIGH);}
    else if(randomnum == 2){digitalWrite(LED3, HIGH);}
    else if(randomnum == 3){digitalWrite(LED2, HIGH);}
    else if(randomnum == 4){digitalWrite(LED1, HIGH);}
  }

  void LEDHelpStop(int randomnum){
    if(randomnum == 1){digitalWrite(LED4, LOW);}
    else if(randomnum == 2){digitalWrite(LED3, LOW);}
    else if(randomnum == 3){digitalWrite(LED2, LOW);}
    else if(randomnum == 4){digitalWrite(LED1, LOW);}
  }
