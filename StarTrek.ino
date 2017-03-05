/****************************************************************************
 * StarTrek Game Content
 * SinglePlayer Game Currently
 * Version 0.7.0
 */

/****************************************************************
*                      Game Tick Event                          *
*                     Excuted per frame                         *
*****************************************************************/
const int intervalPerStone = 3;
const int numOfArrayEle = 5;
const int STlevel12 = 150*4;
const int STlevel23 = 450*4;

int frameTime = 100;

int gameStarTick(struct stone all[]){
  int fps = 0,index = 1,num = 1,playerCol = 3,lifes = 4,timeScoreST = 0;
  
  all[0] = generateStone();
  while(1){
      if(timeScoreST >= STlevel12 && timeScoreST < STlevel23){
        frameTime = 75;
        timeScoreST += 3;
      }else if(timeScoreST >= STlevel23){
        frameTime = 50;
        timeScoreST += 2;
      }else{
        timeScoreST += 4;
      }
      LEDLife(lifes);
      fps++;
      if(fps == intervalPerStone){  //3
          all[index] = generateStone();
          if(num<= numOfArrayEle){                                          //for the first turn when the num of stone on the screen is less than the maximum 4
             num++;
          }
          if(index >= numOfArrayEle){//4
            index = 0;
          }else{
            index++;
          }
          fps = 0;  
      }
  
      for(int i = 0;i < num;i++){                              //Draw all the stones in the array
          if(all[i].row>=16){
            continue;
          }
          printStone(all[i]);
          all[i].row++;
      }

      playerCol = printPlayer(playerCol);

      for(int i = 0;i < num;i++){                                                  //Check if the player is hurt
          if(all[i].row == 14){
              if(all[i].col == playerCol && (all[i].type > 3)){                    //small stone 'O' eliminate 2 units of health
                  if(lifes>=3){
                      lifes -= 2;
                  }else{
                      LEDLife(0);                                                  //Turn off all the lights
                      return timeScoreST/4;
                    }
                }else if(all[i].col == playerCol && (all[i].type == 3)){           //heavy stone '@' eliminate 3 units of health
                  if(lifes>=4){
                      lifes -= 3;
                  }else{
                      LEDLife(0);                                                  //Turn off all the lights
                      
                      return timeScoreST/4;
                  }  
                }else if(all[i].col == playerCol && (all[i].type == 1)){           //eat '+' can add 1 unit of health
                  if(lifes<4){                
                      lifes += 1;
                  }
                }
            }
      }
      delay(frameTime);
      clearScreen();
  } 
  return timeScoreST/4;
}

/****************************************************************
*                  Generate Stone and location                  *
*    Output: structure stone                                    *
*****************************************************************/
struct stone generateStone(){
    struct stone temp;
    temp.row = 0;
    temp.col = random(0,4);
    temp.type = random(1,10);
    return temp;
  }

/****************************************************************
*                  Print Single Stone or Empty                  *
*                   Current Logo 'O'/'@'/' '                    *
*****************************************************************/
void printStone(struct stone aStone){
    if(aStone.type == 1){
        OrbitOledSetCursor(aStone.row,aStone.col);
        OrbitOledPutString("+");     
      }else if(aStone.type == 2){
          OrbitOledSetCursor(aStone.row,aStone.col);
          OrbitOledPutString(" ");
        }else if(aStone.type == 3){
          OrbitOledSetCursor(aStone.row,aStone.col);
          OrbitOledPutString("@");
        }else if(aStone.type == 4){
          OrbitOledSetCursor(aStone.row,aStone.col);
          OrbitOledPutString("O");
        }else if(aStone.type == 5){
          OrbitOledSetCursor(aStone.row,aStone.col);
          OrbitOledPutString("O");
        }else if(aStone.type == 6){
          OrbitOledSetCursor(aStone.row,aStone.col);
          OrbitOledPutString("O");
        }else if(aStone.type == 7){
          OrbitOledSetCursor(aStone.row,aStone.col);
          OrbitOledPutString("O");
        }else if(aStone.type == 8){
          OrbitOledSetCursor(aStone.row,aStone.col);
          OrbitOledPutString("O");
        }else if(aStone.type == 9){
          OrbitOledSetCursor(aStone.row,aStone.col);
          OrbitOledPutString("O");
        }
    
  }

/****************************************************************
*                       Print Player Logo                       *
*                       Current Logo '<='                       *
*****************************************************************/
int printPlayer(int playerCol){
    int receive = 0;
    receive = gameSpaceButton();
    if(receive == 3){
        if(playerCol > 0 && playerCol <= 3){
            playerCol--;
        }
    }
    if(receive == 4){
        if(playerCol >= 0 && playerCol < 3){
            playerCol++;
        }
    }
    OrbitOledSetCursor(15,playerCol);
    OrbitOledPutChar('=');
    OrbitOledSetCursor(14,playerCol);
    OrbitOledPutChar('<');
    return playerCol;
}

/****************************************************************
*                      Button Press Function                    *
*                          For StarTrek                         *
*                     Response Once Per Frame                   *
*****************************************************************/
int gameSpaceButton(){
       buttonDownState = digitalRead(PBD1);
       buttonUpState = digitalRead(PBU1);
       if(buttonDownState == 1){
                return 4;
       }else if(buttonUpState == 1){
                return 3;
       }
       return 0;
 }

/****************************************************************
*                    Life LED System Function                   *
*   Input: number of lifes                                      *
*****************************************************************/
void LEDLife(int num){
    if(num == 0){
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      }
    else if(num == 1){
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, HIGH);
      }
    else if(num == 2){
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
      }
    else if(num == 3){
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
      }
    else if(num == 4){
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
      }
 }


