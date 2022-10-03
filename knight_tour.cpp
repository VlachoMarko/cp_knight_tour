#include<iostream>
#include<vector>
#include<sstream>
#include<string>
#include<cstdlib>
#include"board.h"
#include"matrix.h"


void printVectors(std::vector<char> letters, std::vector<int> numbers);

void checkParams(chessMatrix<std::string> coordinates, std::string start, std::string end);

bool findKnightsTour(Board gameBoard, std::string start, std::string end);

std::string getKnightMoves(Board gameBoard, std::string start);

int getIndex(std::vector<char> letters, char start_x);

std::vector<int> pushMoves(int x, int y, std::vector<int>& moves, int operations);



int main(int argc, char *argv[]){
    try {
        
        std::istringstream iss1(argv[1]);

        int size;
        iss1 >> size;

    
        if (argc != 4 || size > 26){
            throw std::runtime_error("invalid parameter list");
        }

        std::istringstream iss2(argv[2]);
        std::istringstream iss3(argv[3]);

        std::string start, end;
        iss2 >> start;
        iss3 >> end; 

        Board gameBoard(size);

        gameBoard.coordinates.initChessSquares(gameBoard.letters, gameBoard.numbers);
        gameBoard.visitedSquares.allFalse();
        
        checkParams(gameBoard.coordinates, start, end);
        bool isTour = findKnightsTour(gameBoard, start, end);
        std::cout << "Tour is: " << isTour << "\n";

    
    }
    
    catch (std::runtime_error& excpt){
        std::cout << std::endl;
        std::cout << "Error: ";
        std::cout << excpt.what() << std::endl;
    }
    return 0;
}



void printVectors(std::vector<char> letters, std::vector<int> numbers){

    for (int i=0; i<letters.size(); i++){
        std::cout << letters.at(i) << numbers.at(i) << "\n";
    }
    
}

void checkParams(chessMatrix<std::string> coordinates, std::string start, std::string end){

    if (!coordinates.isExists(start) || !coordinates.isExists(end)){

        throw std::runtime_error ("invalid parameter list");
    }

}

bool findKnightsTour(Board gameBoard, std::string start, std::string end){

    if (start == end) return true;
    
    std::string knightMoves = getKnightMoves(gameBoard, start);

    //TODO: Get coordinates as int x and int y, cause isExists will be always true cause of getKnightMoves.
    // Convert to string after it has been checked in visitedSquares. So it can be passed to knight_tour;


    for(int i=0; i<knightMoves.size(); i = i+2){
        std::string tempStr;
        tempStr += knightMoves.at(i);
        tempStr += knightMoves.at(i+1);
        
        // if (gameBoard.coordinates.isExists(tempStr) && !gameBoard.visitedSquares.at(tempStr)){
        //     gameBoard.visitedSquares.at(tempStr) = true;
        // }
    }


    return false;
}


std::string getKnightMoves(Board gameBoard, std::string start){

    char start_x = start.at(0);
    int x = getIndex(gameBoard.letters, start_x);
    int y = stoi(start.substr(1,1)) - 1;

    std::cout << "x : " << x << " y: " << y << "\n";
    
    if (x == -1){
        throw std::runtime_error ("Out of range square");
    }

    std::vector<int> intMoves;
    
    for (int i=0; i<4; i++){
        pushMoves(x, y, intMoves, i);
    }
    
    std::string strMoves;

    for (int i=0; i<intMoves.size(); i = i+2){
        int x = intMoves.at(i);
        int y = intMoves.at(i+1);
        if ((0 <= x && x <= 25) && (0 <= y && y <= 25)) { 
            strMoves += gameBoard.letters.at(x);
            strMoves += std::to_string(y);
        }
        
    }

    // for (int i=0; i<strMoves.size(); i++){
    //     std::cout << strMoves.at(i) << "\n";
    // }


    return strMoves;
    
}

int getIndex(std::vector<char> letters, char start_x){

    for (int i=0; i<letters.size(); i++){
        if (letters.at(i) == start_x){
            return i;
        }
    }
    return -1;
}

std::vector<int> pushMoves(int x, int y, std::vector<int>& moves, int operations){

    switch (operations){
        case 0: 
            moves.push_back(x-1);
            moves.push_back(y-2);
            moves.push_back(x-2);
            moves.push_back(y-1);
        break;

        case 1:
            moves.push_back(x-1);
            moves.push_back(y+2);
            moves.push_back(x-2);
            moves.push_back(y+1);
        break;

        case 2:
            moves.push_back(x+1);
            moves.push_back(y+2);
            moves.push_back(x+2);
            moves.push_back(y+1);
        break;

        case 3:
            moves.push_back(x+1);
            moves.push_back(y-2);
            moves.push_back(x+2);
            moves.push_back(y-1);
        break;
    }

    return moves;
}