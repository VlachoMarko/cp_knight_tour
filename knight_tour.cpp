#include<iostream>
#include<vector>
#include<sstream>
#include<string>
#include<cstdlib>
#include<cassert>
#include"board.h"
#include"matrix.h"


void checkParams(Matrix<std::string> coordinates, std::string start, std::string end);

bool findKnightsTour(Board gameBoard, std::vector<int> start, std::vector<int> end,  std::vector<std::string>& knight_tour);

std::vector<int> getKnightMoves(Board gameBoard, std::vector<int> start);

int getIndex(std::vector<char> letters, char start_x);

std::vector<int> pushToMoves(int x, int y, std::vector<int>& moves, int operations);

std::vector<int> getIntCoordinates(Board gameBoard, std::string start);

std::string getStringCoordinates(Board gameBoard, int x, int y);

void printVector(std::vector<int> vector);


int main(int argc, char *argv[]){
    try {
        
        if (argc != 4){
            throw std::runtime_error("invalid parameter list");
        }

        std::istringstream iss1(argv[1]);

        int size;
        iss1 >> size;
    
        if (size > 26){
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
        std::vector<std::string> knight_tour = {start};
        // std::cout << "start of knight tour: " << knight_tour.at(0) << "\n";

        std::vector<int> startInts = getIntCoordinates(gameBoard, start);
        std::vector<int> endInts = getIntCoordinates(gameBoard, end);
        gameBoard.visitedSquares.loadTo(startInts.at(0), startInts.at(1), true);


        bool isTour = findKnightsTour(gameBoard, startInts, endInts, knight_tour);
        
        // std::cout << "isTour is: " << isTour << " actual tour: ";

        if (isTour){
            for (int i=0; i<knight_tour.size(); i++){
            std::cout << knight_tour.at(i) << " ";
            }
        }
        else {
            std::cout << "could not find a knight's tour";
        }
        

    
    }
    
    catch (std::runtime_error& excpt){
        std::cout << excpt.what() << std::endl;
    }
    return 0;
}

void checkParams(Matrix<std::string> coordinates, std::string start, std::string end){

    if (!coordinates.isExists(start) || !coordinates.isExists(end)){

        throw std::runtime_error ("invalid parameter list");
    }

}

// TODO: Switch x and y everywhere

bool findKnightsTour(Board gameBoard, std::vector<int> start, std::vector<int> end, std::vector<std::string>& knight_tour){

    // std::cout << "end: " << end.at(0) << end.at(1);
    if (start.at(0) == end.at(0) && start.at(1) == end.at(1)) return true;
    
    // std::cout  << "raw : " << "x: " << start.at(0) << " y: " << start.at(1) << "\n";
    
    std::vector<int> knightMoves = getKnightMoves(gameBoard, start);

     for (int i=0; i<knightMoves.size(); i++){
        int x = knightMoves.at(i);
        int y = knightMoves.at(i+1);

        // std::cout << "\n In the loop: " << x <<  " " << y << "\n";


        if ((0 <= x && x < gameBoard.size) && (0 <= y && y < gameBoard.size)) { 

            if (gameBoard.visitedSquares.at(x,y)){
                i++;
                continue;
            }
            assert(!gameBoard.visitedSquares.at(x,y));

            std::string coordinates = getStringCoordinates(gameBoard, x, y);
            knight_tour.push_back(coordinates);

            // std::cout << "moves to: " << "x: " <<  x << " y: " << y << "\n";
            gameBoard.visitedSquares.loadTo(x, y, true);
            std::vector<int> newStart = {x, y};

            bool success = findKnightsTour(gameBoard, newStart, end, knight_tour);
            if (success) {
                return true;
            }
            else { 
                // std::cout << "moves back to: " << coordinates << " ";
                // std::cout  << "x: " << x << " y: " << y << "\n";
                gameBoard.visitedSquares.loadTo(x,y,false);
                knight_tour.pop_back();
            }
        }

        i++;
    }

    return false;
}


std::vector<int> getKnightMoves(Board gameBoard, std::vector<int> moves){

    int y = moves.back();
    moves.pop_back();
    int x = moves.back();
    moves.pop_back();
    
    // std::cout << "getKnightMoves:  X: " << x << " Y: " << y << "\n";

    for (int i=0; i<4; i++){
        pushToMoves(x, y, moves, i);
    }

    // printVector(moves);
    return moves;    
}

std::vector<int> getIntCoordinates(Board gameBoard, std::string start){
    std::vector<int> ints; 

    char start_x = start.at(0);
    // std::cout << "getIntCoordinates: start_x: " << start_x << "\n";

    int x = getIndex(gameBoard.letters, start_x);
    assert(x >= 0);
    int y = stoi(start.substr(1,start.size()-1))-1;
    assert (y >= 0);

    ints.push_back(x);
    ints.push_back(y);

    // std::cout << "not gud x: " << ints.at(0) << " not gud y: " << ints.at(1) <<"\n";

    return ints;
}

std::string getStringCoordinates(Board gameBoard, int x, int y){

    std::string coordinates = "";

    assert(x < 26 && y < 26);

    coordinates += gameBoard.letters.at(x);
    coordinates += std::to_string(y+1);

    return coordinates;
}

    

int getIndex(std::vector<char> letters, char start_x){

    for (int i=0; i<letters.size(); i++){
        if (letters.at(i) == start_x){
            return i;
        }
    }
    return -5;
}

std::vector<int> pushToMoves(int x, int y, std::vector<int>& moves, int operations){

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


void printVector(std::vector<int> vector){

    for (int i=0; i<vector.size(); i++){

        std::cout << vector.at(i) << "\n";

    }
}