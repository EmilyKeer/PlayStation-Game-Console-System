/****************************************************************************
 * CS Game Content
 * SinglePlayer Game Currently
 * Version 0.7.1
 */
const int desireLevelTime = 60000;
 
int bin[8]={0},input[8]={0};

int CSGameRuntime(int CSLevel){
    int timerWithButton[1] = {0};
    int previousNum = 0, level = 1, result = 0,scoreCSTemp = 0;
    clearScreen();
    
    while(1){
      while(result == previousNum){                             //Generate different number
        result = gererateQuestion(level);
      }
      
      previousNum = result;
      decimalToBinary(result,bin,input);
      printQuestion(result);
      readInput(input,timerWithButton);
      int isCorrect = matchOrNot(input,bin);
      if(isCorrect == 1&&level<CSLevel){                        //Calculate Score
        scoreCSTemp += timerWithButton[0];
        level++;  
      }else if(isCorrect == 1&&level==CSLevel){
        scoreCSTemp += timerWithButton[0];
        if(((level*desireLevelTime-scoreCSTemp)/1000)<=0){
          return 0;
        }else{
          return (level*desireLevelTime-scoreCSTemp)/1000;
        } 
      }else{
        level--;
        if(((level*desireLevelTime-scoreCSTemp)/1000)<=0){
          return 0;
        }else{
          return (level*desireLevelTime-scoreCSTemp)/1000;
        } 
      }
    }
}

/*****************************************************************
*                   Generate Question Function                   *
*                             Step 1:                            *
******************************************************************/
int gererateQuestion(int level){
  int result = 0;
    switch(level){
      case 1:
        result = random(16,32);
        break;
      case 2:
        result = random(32,64);
        break;
      case 3:
        result = random(64,128);
        break;
      case 4:
        result = random(128,256);
        break; 
      default: ; 
    }
    return result;
  }

/*****************************************************************
*                   Generate Question Function                   *
*                     Step 2: Turn to Binary                     *
******************************************************************/
void decimalToBinary(int result,int bin[],int input[]){
    int temp = result;
    for(int i=0;i<8;i++){
      bin[i]=0;
      input[i]=0;
    }
    for(int i=7;i>=0;i--){
      bin[i] = temp%2;
      temp = temp/2;    
    }
  }

/*****************************************************************
*               Measure Whether The Input is Correct             *
*                          For Game CS                           *
******************************************************************/
int matchOrNot(int input[],int bin[]){
    for(int i = 0;i<8;i++){
      if(input[i] != bin[i]){
        return 0;
      }
    }
    return 1;
  }

/*****************************************************************
*                   Read Player Button Input                     *
*                          For CS Game                           *
*                    And Cancel Input Number                     *
******************************************************************/
int readInput(int input[],int timerWithButton[]){
    int feadback = 0;
    int cancel = 0;
    for(int i = 0;i<8;i++){
      feadback = gameButtonPressedMode2(timerWithButton);
      if(feadback == 3){
        input[i]=0;
        OrbitOledSetCursor(i,3);
        OrbitOledPutChar('0');
      }else if(feadback == 4){
        input[i]=1;
        OrbitOledSetCursor(i,3);
        OrbitOledPutChar('1');
      }else if(feadback == 1){
        i -= 2;
        OrbitOledSetCursor(i+1,3);
        OrbitOledPutChar('?');
      }else{
        i--;  
      }
    }
  }

/*****************************************************************
*                   Print The Question Function                  *
*                          For Game CS                           *
******************************************************************/
void printQuestion(int result){
    OrbitOledSetCursor(0,0);
    OrbitOledPutString("Your Question:");
    char charBufCS[5];
    String str = String(result,DEC);
    str.toCharArray(charBufCS, 5);
    OrbitOledSetCursor(0,1);
    OrbitOledPutString(charBufCS);
    OrbitOledSetCursor(7,1);
    OrbitOledPutString("DEC->BIN");
    OrbitOledSetCursor(0,2);
    OrbitOledPutString("Answer:");
    OrbitOledSetCursor(0,3);
    OrbitOledPutString("????????");
  }

/*****************************************************************
*                      Button Press Function                     *
*      For Game CS                          Version 0.5.0        *
******************************************************************/
int gameButtonPressedMode2(int timerWithButton[]){
     while(1){
       buttonDownState = digitalRead(PBD1);
       buttonUpState = digitalRead(PBU1);
       buttonConfirmState = digitalRead(PBC1);
       buttonCancelState = digitalRead(PBC2);
       if(buttonDownState == 1){
          while(1){
              buttonDownState = digitalRead(PBD1);
              if(buttonDownState == 0){
                return 4;
              }
              delay(15);
              timerWithButton[0] += 15;
            }
         }
       if(buttonUpState == 1){
          while(1){
              buttonUpState = digitalRead(PBU1);
              if(buttonUpState == 0){
                return 3;
              }
              delay(15);
              timerWithButton[0] += 15;
            }
         }
       if(buttonCancelState == 0){
          while(1){
              buttonCancelState = digitalRead(PBC2);
              if(buttonCancelState == 1){
                return 1;
              }
              delay(15);
              timerWithButton[0] += 15;
            }
         } 
       if(buttonConfirmState == 0){
          while(1){
              buttonConfirmState = digitalRead(PBC1);
              if(buttonConfirmState == 1){
                return 2;
              }
              delay(15);
              timerWithButton[0] += 15;
            }
        }
        delay(15);
        timerWithButton[0] += 15;
     }
     return 0;
 }
