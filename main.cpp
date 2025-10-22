#include <fstream> //for getting file
#include <iostream> //for cout, cin
#include <utility> //for swap
#include <vector> //for matrix format
#include <iomanip> //for output formatting (std::setw)

class Matrix {
    public:
        //sets N to size
        Matrix(int size) : N(size) {
            data.resize(N); //creates N rows
            for (int i = 0; i < N; ++i){
                data[i].resize(N,0); //resizes each row to N cols with value 0
            }
        }

        void load(std::ifstream& file) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    file >> data[i][j];
                }
            }
        }

        void print() const {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    //std::setw(5) to create set width between cols
                    std::cout << std::setw(5) << data[i][j];
                }
                std::cout << std::endl; //newline
            }
        }

        //add 2 matrices
        //returns a new matrix
        void add(const Matrix& other) const {
            Matrix result(N);
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    result.data[i][j] = this->data[i][j] + other.data[i][j];
                }
            }
            return result;
        }

        //multiply 2 matrices
        //returns a new matrix
        void multiply(const Matrix& other) const {
            Matrix result(N);
            for (int i )
        } 

        void sumOfDiagElems() {

        }

        void swapRows() {

        }

        void swapCols() {

        }

    private:
        int N; //size
        std::vector<std::vector<int>> data; //2d grid that holds the values

        bool isRowValid(int r) const {
            return r >= 0 && r < N;
        }
        bool isColValid(int c) const {
            return c >= 0 && c < N;
        }
        bool isValid(int r, int c) const {
            return isRowValid(r) && isColValid(c);
        }

};


// takes in a matrix, row, col, and a new value and updates that spot in the matrix if it is a valid spot
void updateElement(int r, int c, int value) {

}

int main() {
	std::string filename;
	std::cout << "Enter a matrix file: ";
    std::cin >> filename;

    std::ifstream file(filename);
    if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return 1; //exit with error
        }
    
    int N;
    file >> N; //reads the first character of file and stores it in N (# of rows and cols)
    if (N <= 0) {
        std::cerr << "Error: Invalid matrix size N=" << N << std::endl;
        return 1; //exit with error
    }

    //create 2 matrices of size N
    Matrix A(N);
    Matrix B(N);

    //load data from input file
    A.load(file);
    B.load(file);
    file.close();

    //print original matrices
    std::cout << "\n     ---Matrix A---" << std::endl;
    A.print();
    std::cout << "\n     ---Matrix B---" << std::endl;
    B.print();
    

    return 0;
}