#include <fstream> //for getting file
#include <iostream> //for cout, cin
#include <utility> //for swap (std::swap)
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
        Matrix add(const Matrix& r) const {
            Matrix result(N);
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    result.data[i][j] = this->data[i][j] + r.data[i][j];
                }
            }
            return result;
        }

        //multiply 2 matrices
        //returns a new matrix
        Matrix multiply(const Matrix& r) const {
            //use square multiplication algorithm
            Matrix result(N);
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    result.data[i][j] = 0;
                    for (int k = 0; k < N; ++k) {
                        result.data[i][j] += this->data[i][k] * r.data[k][j];
                    }
                }
            }
            return result;
        } 

        void printDiagSums() const {
            int mainSum = 0;
            int secSum = 0;
            for (int i = 0; i < N; ++i) {
                mainSum += data[i][i]; //from top left to bottom right
                secSum += data[i][N-i-1]; //from top right to bottom left
            }
            std::cout << "Main diagonal sum: " << mainSum << std::endl;
            std::cout << "Secondary diagonal sum: " << secSum << std::endl;
        }

        //modifies this matrix
        void swapRows(int r1, int r2) {
            if (isRowValid(r1) && isRowValid(r2)) {
                //swap entire vector at once
                std::swap(data[r1], data[r2]);
                std::cout << "Matrix after swapping rows " << r1 << " and " << r2 << ":" << std::endl;
                print();
            } else {
                std::cout << "Error: Invalid row index." << std::endl;
            }
        }

        //modifies this matrix
        void swapCols(int c1, int c2) {
            if (isColValid(c1) && isColValid(c2)) {
                //swap element by element down columns
                for (int i = 0; i < N; ++i) {
                    std::swap(data[i][c1], data[i][c2]);
                }
                std::cout << "Matrix after swapping columns " << c1 << " and " << c2 << ":" << std::endl;
                print();
            } else {
                std::cout << "Error: Invalid column index." << std::endl;
            }
        }

        // takes in row, col, and a new value and updates that spot in matrix if it is a valid spot
        void updateElement(int r, int c, int value) {
            if (isValid(r, c)) {
                data[r][c] = value;
                std::cout << "Matrix after updating element at (" << r << ", " << c << "):" << std::endl;
                print();
            } else {
                std::cout << "Error: Invalid index." << std::endl;
            }
        }
    private:
        int N; //size
        std::vector<std::vector<int>> data; //2d grid that holds values

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


int getIntInput(const std::string& prompt) {
    int value;
    std::cout << prompt;
    while (!(std::cin >> value)) {
        std::cout << "Invalid input. Enter a valid integer: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    return value;
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
    file >> N; //reads first character of file and stores it in N (# of rows and cols)

    //check if file can be read
    if (file.fail()) {
        std::cerr << "ErrorCould not read matrix size N from file" << std::endl;
        return 1; //exit with error
    }
    //check if N <= 0
    if (N <= 0) {
        std::cerr << "Error: Invalid matrix size N=" << N << std::endl;
        return 1; //exit with error
    }

    //create 2 matrices of size N
    Matrix A(N);
    Matrix B(N);

    //load data from input file
    A.load(file);
    if (file.fail()) { //check if matrix is too small or has bad data (e.g. strings instead of ints)
        std::cerr << "Error: Failed loading Matrix A; incomplete or contains bad data." << std::endl;
        return 1;
    }

    B.load(file);
    if (file.fail()) {
        std::cerr << "Error: Failed loading Matrix B; incomplete or contains bad data." << std::endl;
        return 1;
    }

    file.close();

    //print original matrices
    std::cout << "\n     ---Matrix A---" << std::endl;
    A.print();
    std::cout << "\n     ---Matrix B---" << std::endl;
    B.print();
    
    //add 2 matrices
    std::cout << "\n     ---A + B---" << std::endl;
    Matrix C_add = A.add(B);
    C_add.print();

    //multiply 2 matrices
    std::cout << "\n     ---A * B---" << std::endl;
    Matrix C_mult = A.multiply(B);
    C_mult.print();

    //print diagonal sums
    std::cout << "\n -----Diagonal Sums-----" << std::endl;
    std::cout << "-Matrix A" << std::endl;
    A.printDiagSums();
    std::cout << "\n-Matrix B" << std::endl;
    B.printDiagSums();

    //swap rows and display result
    std::cout << "\n -----Swap Rows-----" << std::endl;
    int r1 = getIntInput("Enter first row index to swap: ");
    int r2 = getIntInput("Enter second row index to swap: ");
    A.swapRows(r1, r2);
    
    //swap cols and display result
    std::cout << "\n -----Swap Columns-----" << std::endl;
    int c1 = getIntInput("Enter first column index to swap: ");
    int c2 = getIntInput("Enter second column index to swap: ");
    //A is already modified from rows swap
    A.swapCols(c1, c2);

    //update element
    std::cout << "\n -----Update Element-----" << std::endl;
    int r = getIntInput("Enter row index to update: ");
    int c = getIntInput("Enter column index to update: ");
    int value = getIntInput("Enter new value: ");
    //A is already modified from rows and cols swap
    A.updateElement(r, c, value);

    return 0;
}