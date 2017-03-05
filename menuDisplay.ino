void gameOLEDInit(){ 
    OrbitOledInit(); 
    OrbitOledClear(); 
    OrbitOledClearBuffer();
    OrbitOledSetCursor(0,0);
} 

/*************************************************************
*                    Safe Clear The Screen                   *
**************************************************************/
void clearScreen(){
    OrbitOledClear(); 
    OrbitOledClearBuffer();
    OrbitOledSetCursor(0,0);
    OrbitOledUpdate();
  }

void printWelcome(){
    OrbitOledPutString("TAT PlayStation");
    OrbitOledSetCursor(0,2);
    OrbitOledPutString("Version: 0.7.1");
    OrbitOledSetCursor(0,3);
    OrbitOledPutString("Author: Team3");
    delay(5000);
    clearScreen();
}

void printLoading(){
    OrbitOledPutString("Loading");
    for(int i=0;i<6;i++){
       OrbitOledSetCursor(i+7,0);
       OrbitOledPutString(".");
       OrbitOledSetCursor(13,0);
       OrbitOledPutChar('-');
       delay(100);
       OrbitOledSetCursor(13,0);
       OrbitOledPutChar('\\');
       delay(100);
       OrbitOledSetCursor(13,0);
       OrbitOledPutChar('|');
       delay(100);
       OrbitOledSetCursor(13,0);
       OrbitOledPutChar('/');
       delay(100);
    }
    delay(450);
    clearScreen();    
  }
  
/**************************************************************
*                  Print Game Selection Menu                  *
*  Output: The number of gamemode (1-3 currently)             *
***************************************************************/
int printSelectionMenu(){
  int selectorState = 0;
  while(1){
      if(selectorState==0){
          OrbitOledSetCursor(0,0);
          OrbitOledPutString("Select Game Mode");
          OrbitOledSetCursor(0,1);
          OrbitOledPutString("1. Whac-A-Mole");
          OrbitOledSetCursor(0,2);
          OrbitOledPutString("   Singleplayer.");
          drawTriangleAt(92,26,1);
          int atemp = buttonDownPressed();
          if(atemp==2){
            return 1;
            }else if(atemp==1){
                selectorState=1;
              }else if(atemp==3){
                  selectorState=2;
                }
          clearScreen();
        }
        if(selectorState==1){
          OrbitOledSetCursor(0,0);
          OrbitOledPutString("Select Game Mode");
          OrbitOledSetCursor(0,1);
          OrbitOledPutString("2. CS Game");
          OrbitOledSetCursor(0,2);
          OrbitOledPutString("   Multiplayer.");
          drawTriangleAt(92,26,1);
          drawTriangleAt(28,26,-1);
          int atemp = buttonDownPressed();
          if(atemp==2){
            return 2;
            }else if(atemp==1){
                selectorState=2;
              }else if(atemp==3){
                  selectorState=0;
                }
          clearScreen();
        }
        if(selectorState==2){
          OrbitOledSetCursor(0,0);
          OrbitOledPutString("Select Game Mode");
          OrbitOledSetCursor(0,1);
          OrbitOledPutString("3. Star Trek");
          OrbitOledSetCursor(0,2);
          OrbitOledPutString("   Singleplayer.");
          drawTriangleAt(28,26,-1);
          int atemp = buttonDownPressed();
          if(atemp==2){
           return 3;
            }else if(atemp==1){
                selectorState=0;
              }else if(atemp==3){
                  selectorState=1;
                }
          clearScreen();
        }
    }
    clearScreen();
  }

/*************************************************************
*             Print Player Number Selection Menu             *
*  Inpute: The minimum number of players (1-9)               *
*          The maximum number of players (1-9)               *
*  Output: The number of players                             *
**************************************************************/
  int printNumPlayerMenu(int maxNumPlayer,int minNumPlayer){
      clearScreen();
      int NumPlayerState = minNumPlayer;
      OrbitOledSetCursor(0,0);
      OrbitOledPutString("Select Number  ");
      OrbitOledSetCursor(0,1);
      OrbitOledPutString("of Players:    ");
      while(1){
                  OrbitOledSetCursor(0,2);
                  OrbitOledPutChar(NumPlayerState+'0');
                  int btemp = buttonDownPressed();
                  if(btemp==2){
                    return NumPlayerState;
                    }else if(btemp==3){
                        if(NumPlayerState<maxNumPlayer){
                            NumPlayerState++;
                          }
                    }else if(btemp==1){
                        if(NumPlayerState>minNumPlayer){
                            NumPlayerState--;
                          }
                    }else if(btemp==4){
                        return -10;
                    }
            }
    }

/*************************************************************
*                Print Levels Selection Menu                 *
*  Inpute: The minimum number of levels (1-9)                *
*          The maximum number of levels (1-9)                *
*  Output: The number of levels                              *
**************************************************************/
  int printNumLevelMenu(int maxNumlevel,int minNumlevel){
      clearScreen();
      int NumlevelState = minNumlevel;
      OrbitOledSetCursor(0,0);
      OrbitOledPutString("Select Number  ");
      OrbitOledSetCursor(0,1);
      OrbitOledPutString("of Levels:    ");
      while(1){
                  OrbitOledSetCursor(0,2);
                  OrbitOledPutChar(NumlevelState+'0');
                  int btemp = buttonDownPressed();
                  if(btemp==2){
                    return NumlevelState;
                    }else if(btemp==3){
                        if(NumlevelState<maxNumlevel){
                            NumlevelState++;
                          }
                    }else if(btemp==1){
                        if(NumlevelState>minNumlevel){
                            NumlevelState--;
                          }
                    }else if(btemp==4){
                        return -10;
                    }
            }
    }

/****************************************************************
*                      Button Press Function                    *
*                           For Menu                            *
*                   Seperateed for modification                 *
*****************************************************************/
int buttonDownPressed(){
     while(1){
       buttonDownState = digitalRead(PBD1);
       buttonUpState = digitalRead(PBU1);
       buttonConfirmState = digitalRead(PBC1);
       buttonCancelState = digitalRead(PBC2);
       if(buttonDownState == 1){
          while(1){
              buttonDownState = digitalRead(PBD1);
              if(buttonDownState == 0){
                return 1;
              }
              delay(15);
            }
         }
         delay(15); 
       if(buttonUpState == 1){
          while(1){
              buttonUpState = digitalRead(PBU1);
              if(buttonUpState == 0){
                return 3;
              }
              delay(15);
            }
         }
         delay(15); 
       if(buttonConfirmState == 0){
          while(1){
              buttonConfirmState = digitalRead(PBC1);
              if(buttonConfirmState == 1){
                return 2;
              }
              delay(15);
            }
       } 
       if(buttonCancelState == 0){
          while(1){
              buttonCancelState = digitalRead(PBC2);
              if(buttonCancelState == 1){
                return 4;
              }
              delay(15);
            }
       } 
    }
 }

/*************************************************************
*                Draw Triangular At Location                 *
*  Inpute: col; row                                          *
*          mod: 1 is downward; 2 is upward                   *
**************************************************************/
void drawTriangleAt(int row,int col,int mod){
  if(mod == 1){
    for(int j = 0;j<=4;j++){
      for(int i = j;i<=8-j;i++){
        OrbitOledMoveTo(row+i,col+j);
        OrbitOledDrawPixel();
      }
    }
  }else if(mod == -1){
    col += 4;
    for(int j = 0;j>=-4;j--){
      for(int i = -j;i<=8+j;i++){
        OrbitOledMoveTo(row+i,col+j);
        OrbitOledDrawPixel();
      }
    }
  }
  OrbitOledUpdate();
}
