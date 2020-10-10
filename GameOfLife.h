#include <iostream>
#include <string>

class GameOfLife{

    public:
        GameOfLife();
        GameOfLife(int width, int height, double popDensity);
        ~GameOfLife();

        int** mapBoard;
        int** nextMapBoard;
        int** temp;
        char** inputFileMap;

        int mapHeight;
        int mapWidth;
        double mapPopDensity;
        bool worldEnd;
        int aliveCounter;
        int mapNeighbors;

        void populateBoard();
        void initializeMapBoard();
        void initializeNextMapBoard();
        void printMapBoard();
        void populateBoardMapFromFile(std::string fileName);

        void clearMapBoard();
        void clearNextMapBoard();

        void simulateLife();

        bool hasWorldEnded();


};
