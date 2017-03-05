/***********************************************************************
*                    *** Game Manager Function ***                     *
* Inputs: GameMode: (1-3 currently)                                    *
*         Number of Players: (Only for GameMode 2 currently)           * 
************************************************************************/
void playGame(int GameMode,int NumPlayer){
  int winner,score,CSLevel;
  int scoreTime = 0;
    switch(GameMode){
        case 1:                                                       //*** Hamster(WacAMole) Runtime ***
          gameStartCountDown(5);
          OrbitOledSetCursor(0,0);                                    //Pre-print the game UI
          OrbitOledPutString(" WhacAMole GAME ");
          OrbitOledSetCursor(0,1);
          OrbitOledPutString(" 1   2   3   4 ");
          OrbitOledSetCursor(0,2);
          OrbitOledPutString("| |=| |=| |=| |");
          OrbitOledSetCursor(0,3);
          OrbitOledPutString("Lives:0/5 ");
          
          score = GameHamster();
          delay(700);                                                 //Avoid mistake button input which may skip the score print
          
          gameScorePrint(score,0);
          clearScreen();
          delay(700);
          break;
        case 2:                                                       //*** CS Game Runtime ***
          NumPlayer = printNumPlayerMenu(9,1);
          if(NumPlayer==-10){break;}                                  //Simple Cancel Function
          CSLevel = printNumLevelMenu(4,1);
          if(CSLevel==-10){break;}                                    //Simple Cancel Function
          
          randomSeed(millis());
          GameCsGame(NumPlayer,CSLevel);
          clearScreen();
          break;
        case 3:                                                        //*** Star Trek Runtime ***
          printGameRuleStar();
          gameStartCountDown(5);
          scoreTime = GameSpaceShip();
          delay(1000);
          clearScreen();
          
          gameScorePrint(scoreTime,0);
          delay(700);
          clearScreen();
          break;
      }
  }

/****************************************************************************
 * CS Game Call                                                             *
 * For Easy Modification                                                    *
 ****************************************************************************/
void GameCsGame(int NumPlayer,int CSLevel){
    int allPlayerScore[9];
    int i=1;
    
    clearScreen(); 
    OrbitOledSetCursor(0,1);                                         //print first player number
    OrbitOledPutString("   Player:    ");
    OrbitOledSetCursor(11,1);
    OrbitOledPutChar(i+'0');
    OrbitOledSetCursor(0,3);
    OrbitOledPutString("Press Any Button"); 
    buttonDownPressed();                                             //Waiting for player input
    clearScreen();
    
    allPlayerScore[1] = CSGameRuntime(CSLevel);                      //Run the game first time

    if(NumPlayer==1){                                                //Achieve Multiplay
      gameScorePrint(allPlayerScore[1],0);
    }else{
      i++;
      while(i<=NumPlayer){
        clearScreen();
        OrbitOledSetCursor(0,1);
        OrbitOledPutString("   Player:     ");
        OrbitOledSetCursor(11,1);
        OrbitOledPutChar(i+'0');
        OrbitOledSetCursor(0,3);
        OrbitOledPutString("Press Any Button"); 
        buttonDownPressed();                                          //Waiting for player input
        clearScreen();
        allPlayerScore[i] = CSGameRuntime(CSLevel);
        i++;
      }
      
      int maxScore = 0,winner = 0;
      for(int j=1;j<=NumPlayer;j++){
        if(allPlayerScore[j]>maxScore){
          maxScore=allPlayerScore[j];
          winner = j;
        }
      }
      if(maxScore==0){
        gameScorePrint(0,1);
      }else{
        gameScorePrint(winner,1);
      }
    }
  }

/****************************************************************************
 * Space Ship(Star Trek) Game Call                                          *
 * For Easy Modification                                                    *
 ****************************************************************************/
int GameSpaceShip(){
    struct stone allStone[8];//***
    int tempTime10 = gameStarTick(allStone);
    return tempTime10/10;
  }


/***********************************************************************
*                      Print Prepare For Game Screen                   *
* Inputs: countdown time length (1-9)                                  *
************************************************************************/
void gameStartCountDown(int countTime){
    clearScreen();
    OrbitOledSetCursor(0,0);
    OrbitOledPutString("    READY ?    ");
    for(int i = countTime;i>0;i--){
        OrbitOledSetCursor(8,2);
        OrbitOledPutChar(i+'0');
        delay(1000);
      }
    OrbitOledSetCursor(0,2);
    OrbitOledPutString("      GO !!    ");
    delay(1000);
    clearScreen();
  }

/***********************************************************************
*                          Print Score of Game                         *
* Inputs: score int                                                    *
*         type  int mode->1 for singleplayer                           *
*                   mode->2 for multiplayer                            *
************************************************************************/
void gameScorePrint(int score,int type){
    int startSlot = 0;
    if(score >= 10&&score < 100){
      startSlot = 1;
    }else if(score >= 100&&score < 1000){
      startSlot = 2;
    }else if(score >= 1000&&score < 10000){
      startSlot = 3;
    }else{
      startSlot = 0;
    }
    clearScreen();

    char charBuf[16];
    String str = String(score,DEC);
    str.toCharArray(charBuf, 16);

    if(type == 0){
      OrbitOledSetCursor(0,0);
      OrbitOledPutString("   YOUR SCORE: ");
      OrbitOledSetCursor(8-startSlot,1);
      OrbitOledPutString(charBuf);
    }else{
      OrbitOledSetCursor(0,0);
      OrbitOledPutString(" THE WINNER IS:");
      OrbitOledSetCursor(0,2);
      OrbitOledPutString("   Player:     ");
      OrbitOledSetCursor(11,2);
      OrbitOledPutChar(score+'0');
    }
    
    OrbitOledSetCursor(0,3);
    OrbitOledPutString("Press Any Button"); 
    int butsptemp = buttonDownPressed();
}

/***********************************************************************
*                         MilliSecond to Second                        *
* Inputs: time millis                                                  *
************************************************************************/
int msToSecSecond(unsigned long timeDelta){
    int secondDigit = (int)(timeDelta/1000);
    return secondDigit;
  }
  
int msToSecMilli(unsigned long timeDelta){
    int millisecondDigit = timeDelta%1000;
    return millisecondDigit;
  }

/*****************************************************************
 *            Print Game Rules For StarTrek Game                 *
 *                         Page 1                                *
 * Rules                                                         *
 * Mind Inertia!                                                 *
 * LEDs -> HP Bar                                                *
 *                         Page 2                                *
 * 'O'-> -2 health                                               *
 * '@'-> -3 health                                               *
 * '+'-> +1 health                                               *
*****************************************************************/
void printGameRuleStar(){
    OrbitOledSetCursor(0,0);
    OrbitOledPutString("     RULES:    ");
    OrbitOledSetCursor(0,1);
    OrbitOledPutString("  Mind Inertia!");
    OrbitOledSetCursor(0,2);
    OrbitOledPutString("LEDs -> HP Bar");
    OrbitOledSetCursor(0,3);
    OrbitOledPutString("Press Any Button"); 
    int butsptemp = buttonDownPressed();
    clearScreen();
    OrbitOledSetCursor(0,0);
    OrbitOledPutString("'+'-> +1 health");
    OrbitOledSetCursor(0,1);
    OrbitOledPutString("'O'-> -2 health");
    OrbitOledSetCursor(0,2);
    OrbitOledPutString("'@'-> -3 health");
    OrbitOledSetCursor(0,3);
    OrbitOledPutString("Press Any Button"); 
    butsptemp = buttonDownPressed();
    clearScreen();
  }
