#ifndef MATRIX_H
#define MATRIX_H

template <typename T> class chessMatrix{

    public:

        chessMatrix(){};
        
        void init(int row_size, int column_size){

            if (row_size > 26 || column_size > 26) {
                throw std::runtime_error ("invalid parameter list");
            }
            this->data.resize(row_size*column_size);
            this->row_size = row_size;
            this->column_size = column_size;
        };


        void initChessSquares(std::vector<char> letters, std::vector<int> numbers){
            std::string tempStr;

            for (int i=0; i<letters.size(); i++){

                for(int j=0; j<numbers.size(); j++){
                    tempStr = letters.at(i) + std::to_string(numbers.at(j));
                    loadTo(i, j, tempStr);
                }
            }

        };

        void printSquares(){
            for (int i=0; i<data.size(); i++){
                std::cout << this->data.at(i) << std::endl;
            }
        };

        bool isExists(std::string compareString){
            for (int i=0; i<this->data.size(); i++){
                if (this->data.at(i) == compareString){
                    return true;
                }
            }

            return false;
        };

        void allFalse(){
            for (int i=0; i<this->data.size(); i++){
                this->data.at(i) = false;
            }
            
        };

        //TODO
        T at(std::string coordinate){
            char row = coordinate(0)
            int column = coordinate(1)

        }

        void loadTo(int row, int column, T inputData){
            if (this->row_size*row+column > data.size()){
                throw std::runtime_error("Out of range");
            }
            data.at(this->row_size*row+column) = inputData;
        };

       


    private:
        std::vector<T> data;
        int row_size;
        int column_size;

};

#endif