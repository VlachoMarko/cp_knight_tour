#ifndef MATRIX_H
#define MATRIX_H

template <typename T> class Matrix{

    public:
        Matrix(){};
        
        void init(int size){
            if (size > 26) {
                throw std::runtime_error ("invalid parameter list");
            }
            this->data.resize(size*size);
            this->row_size = size;
            this->column_size = size;
        };


        void initCoordinates(std::vector<char> letters, std::vector<int> numbers){
            std::string tempStr;

            for (int i=0; i<letters.size(); i++){

                for(int j=0; j<numbers.size(); j++){
                    tempStr = letters.at(i) + std::to_string(numbers.at(j));
                    loadTo(i, j, tempStr);
                }
            }

        };

        bool notContains(std::string compareString){
            for (int i=0; i<this->data.size(); i++){
                if (this->data.at(i) == compareString){
                    return false;
                }
            }

            return true;
        };

        void setAllFalse(){
            for (int i=0; i<this->data.size(); i++){
                this->data.at(i) = false;
            }
        };

        T at(int row, int column){
            if (this->row_size*row+column > data.size()){
                throw std::runtime_error("Out of range");
            }
           
            return data.at(this->row_size*row+column);
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