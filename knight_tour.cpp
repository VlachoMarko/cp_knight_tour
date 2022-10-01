#include<iostream>
#include<vector>
#include<sstream>
#include<string>



class Board {
public:
    std::vector<char> letters;
    std::vector<int> numbers;
    
    //TODO: 2D <int,int> vector for easy coordinate construction with the indices.
    //TODO: Map for visited tiles. Boolean map 0: Not visited, 1: Visited


    Board(int size){
        char baseAscii = 97;
        
        for (int i=0; i<size; i++){
            this->letters.push_back(baseAscii+i);
            this->numbers.push_back(i+1);
        }
    };

};

void printVectors(std::vector<char> letters, std::vector<int> numbers);

void checkParams(std::vector<char> letters, std::vector<int> numbers, std::string start, std::string end);

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
        printVectors(gameBoard.letters, gameBoard.numbers);
        std::cout << "size: " << size << std::endl;

        checkParams(gameBoard.letters, gameBoard.numbers, start, end);
        


        
        

        


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

void checkParams(std::vector<char> letters, std::vector<int> numbers, std::string start, std::string end){

    std::string tempStr;
    bool found1 = false, found2 = false;

    //TODO: Map can be made here, also these nested loops can be put into a different function.
    // Here is enough to check if the parameters are in the Map or not.

    for (int i=0; i<letters.size(); i++){

        for(int j=0; j<numbers.size(); j++){
            tempStr = letters.at(i) + std::to_string(numbers.at(j));

            if (start == tempStr) {
                found1 = true;
            }

            if (end == tempStr){
                found2 = true;
            }
        }
    }
    
    if (!found1 || !found2){
        throw std::runtime_error("invalid parameter list");
    }

}