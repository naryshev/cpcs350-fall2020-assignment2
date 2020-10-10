#include "GameOfLife.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;


//Default constructor
GameOfLife::GameOfLife(){
    mapWidth = 0;
    mapHeight = 0;
    mapPopDensity = 0;
    aliveCounter = 0;

}
//Overloaded Constructor
GameOfLife::GameOfLife(int height, int width, double popDensity){
    mapWidth = width;
    mapHeight = height;
    mapPopDensity = popDensity;
    aliveCounter = 0;
    mapNeighbors = 0;
    worldEnd = false;

}
GameOfLife::~GameOfLife(){

}
//Take in file path as argument and then initialize board with demensions as specified on mapFile
//Populate board based on mapfile
void GameOfLife::populateBoardMapFromFile(string fileName){
    string fileHeight = "", fileWidth = "", line = "";
    char fileChar;
    fstream fileRead(fileName);
    //Store dimensions of board from map file
    getline(fileRead, fileHeight);
    getline(fileRead, fileWidth);

    //Convert dimensions from string to integer
    mapWidth = stoi(fileWidth);
    mapHeight = stoi(fileHeight);

    //Initialize board with given dimensions
      mapBoard = new int*[mapHeight];
      for(int i = 0; i < mapHeight; i++){
        mapBoard[i] = new int[mapWidth];
      }

      //Create array to store string input from lines in order
      inputFileMap = new char*[mapHeight];
      for(int i = 0; i < mapWidth; i++){
        inputFileMap[i] = new char[mapWidth];
      }

      //Iterate line by line
      while(fileRead >> line){
        for(int a = 0; a < line.length(); a++){
              //inputFileMap[i] = line[i];

        }
      }

  //Populate board based on character 1 for 'X' and 0 for '-'
  for(int i = 0; i < mapHeight; i++){
    for(int j = 0; j < mapWidth; j++){
      if(inputFileMap[i][j] == '-'){
        mapBoard[i][j] = 0;
      }else if (inputFileMap[i][j] == 'X'){
        mapBoard[i][j] = 1;
      }
    }
  }

}

//Initializes map board
void GameOfLife::initializeMapBoard(){
    mapBoard = new int*[mapHeight];
    for(int i = 0; i < mapHeight; i++){
      mapBoard[i] = new int[mapWidth];
    }
}

//Create second map board to make changes to and eventually replace based on the results of the current map baord
//Updates mext board based on evaluation of current board so current board does not change while being evaluated for neighbors
void GameOfLife::initializeNextMapBoard(){
    nextMapBoard = new int*[mapHeight];
    for(int i = 0; i < mapHeight; i++)
        nextMapBoard[i] = new int[mapWidth];
}

//Populate baord withrandon
void GameOfLife::populateBoard(){
  srand(time(NULL));
  for (int i =0;i < mapHeight;i++) {
    for (int j =0;j < mapWidth;j++) {
      if (i == 0 || j == 0 || i == mapWidth-1 || j == mapHeight-1)  {
          mapBoard[i][j] = 0;
      } else {
        double randVal = rand() / double(RAND_MAX);
        if(randVal < mapPopDensity){
          mapBoard[i][j] = 1;
        }else{
          mapBoard[i][j] = 0;
        }
      }
    }
  }
}

//Print map Board
void GameOfLife::printMapBoard(){
    cout << "Gen 0 : " << endl;
    cout << mapHeight << endl;
    cout << mapWidth << endl;
    for(int i = 0; i < mapHeight; i++){
      for(int j = 0; j < mapWidth; j++){
        cout << " "<< mapBoard[i][j] << " ";
      }
      cout << endl;
    }
}

//Clears map board from memory
void GameOfLife::clearMapBoard(){
    for(int i = 0; i < mapWidth; i++){
        delete [] mapBoard[i];
    }
    delete [] mapBoard;
}
//Clears map board copy from memory

void GameOfLife::clearNextMapBoard(){
    for(int i = 0; i < mapWidth; i++){
        delete [] nextMapBoard[i];
    }
    delete [] nextMapBoard;
}

//Check for map for all neighbors and evaluate each spot based on number of neighbors
void GameOfLife::simulateLife(){
    // Loop through every spot in our 2D array and check spots neighbors
    for (int x = 0; x < mapHeight; x++) {
      for (int y = 0; y < mapWidth; y++) {
        //Add up all the states in a 3x3 surrounding grid
        for (int i = -1; i <= 1; i++) {
          for (int j = -1; j <= 1; j++) {
                cout << mapBoard[i][j]<<endl;
                mapNeighbors += mapBoard[i][j];
            }
          }
        //We searched 3x3 when we should have only checked eight neighboring spaces; If the cell we are on is bacteria, it  will not be included in the neighbors count
        mapNeighbors -= mapBoard[x][y];

        //Evaluate cases depending on number of neighbors
        if((mapBoard[x][y] == 1) && (mapNeighbors <  2)){
          nextMapBoard[x][y] = 0;
        }else if ((mapBoard[x][y] == 1) && (mapNeighbors >  3)){
          nextMapBoard[x][y] = 0;
        }else if ((mapBoard[x][y] == 0) && (mapNeighbors == 3)){
          nextMapBoard[x][y] = 1;
        }else{
          nextMapBoard[x][y] = mapBoard[x][y];
        }
      }
    }
    //Update map board
    mapBoard = nextMapBoard;

}

//Evaluate whether world has ended by checking if cells are empty
bool GameOfLife::hasWorldEnded(){
    for(int i = 1; i < mapHeight; i++){
      for(int j = 1; j < mapWidth; j++){
        if(mapBoard[i][j] == 1){
          aliveCounter++;
        }
      }
    }
    if(aliveCounter < 1){
      return true;
    }
}
