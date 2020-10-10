#include "GameOfLife.h"
#include <fstream>    // file I/O
#include <iostream>
#include <array>
using namespace std;

int main(int argc, char  **argv) {
    int a = 0, b = 0, c = 0,x = 0,y = 0;
    char choiceA,choiceB,inFileChar;
    string userPath = "";
    string mapLines = "";
    string inFileLine = "";
    double popDensity ;

    cout  << "Would you like to (a) use a map file or (b) generate a random assignment?" << endl;
    cin >> choiceA;
    //If user chooses 'a' prompt for map file, If user chooses 'b' prompt for dimensions and population density
    if (choiceA == 'a') {
      // User Provided Map File
      cout << "Enter map file name..."<< endl;
      cin >> userPath;

      cout << "Map File Selected....'" << userPath << "'" << endl;

      //Instantiate new GameOfLife Object "mapFile"
      GameOfLife mapFile;

      //Call methods to populate mapFile object with a mapBoard and print to console
      mapFile.populateBoardMapFromFile(userPath);
      mapFile.printMapBoard();

    } else if ( choiceA == 'b'){
      cout << "Enter Size Dimensions...." << endl;
      cout << "Width : " ;
      cin >> x;
      cout << "Height : " ;
      cin >> y;
      cout << "Width : " << x << ", Height : " << y << endl;
      cout << "Enter initial population density (Enter a decimal value 0.0 - 1.0)" << endl;
      cin >> popDensity;

      //Instantiate new GameOfLife Object "userGen"

      GameOfLife userGen(x,y,popDensity);

      //Call method to initialize mapBoard, Initialize mapBoard copy, populate the board based on population density, and output to console
      userGen.initializeMapBoard();
      userGen.initializeNextMapBoard();
      userGen.populateBoard();
      userGen.printMapBoard();
      // code to create successive generations of original mapBoard (couldn't get it to work )
      //while (userGen.hasWorldEnded()==false) {
        userGen.simulateLife();
      //}
      userGen.clearMapBoard();
      userGen.clearNextMapBoard();
    }

  return 0;
}
