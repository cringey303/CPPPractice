#include <fstream> //for getting file
#include <iostream> //for cout, cin
#include <utility> //for swap (std::swap)
#include <vector> //for matrix format
#include <iomanip> //for output formatting (std::setw)
#include <sstream> //for parsing integers from lines

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
        Matrix operator+(const Matrix& r) const {
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
        Matrix operator*(const Matrix& r) const {
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

        //non-destructive friend functions to access private members
        friend Matrix swapRows(Matrix m, int r1, int r2);
        friend Matrix swapCols(Matrix m, int c1, int c2);
        friend Matrix updateElement(Matrix m, int r, int c, int value);

};

//non-destructive
Matrix swapRows(Matrix m, int r1 = 0, int r2 = 1) {
    if (m.isRowValid(r1) && m.isRowValid(r2)) {
        //swap entire vector at once
        std::swap(m.data[r1], m.data[r2]);
        std::cout << "Matrix after swapping rows " << r1 << " and " << r2 << ":" << std::endl;
        m.print();
    } else {
        std::cout << "Error: Invalid row index." << std::endl;
    }
    return m; //return modified matrix copy
}

//non-destructive
Matrix swapCols(Matrix m, int c1 = 0, int c2 = 1) {
    if (isColValid(c1) && isColValid(c2)) {
        //swap element by element down columns
        for (int i = 0; i < m.N; ++i) {
            std::swap(m.data[i][c1], m.data[i][c2]);
        }
        std::cout << "Matrix after swapping columns " << c1 << " and " << c2 << ":" << std::endl;
        m.print();
    } else {
        std::cout << "Error: Invalid column index." << std::endl;
    }
    return m; //return modified matrix copy
}

//non-destructive. Takes in row, col, and a new value and updates that spot in matrix if it is a valid spot
Matrix updateElement(Matrix m, int r = 0, int c = 0, int value = 100) {
    if (m.isValid(r, c)) {
        m.data[r][c] = value;
        std::cout << "Matrix after updating element at (" << r << ", " << c << "):" << std::endl;
        m.print();
    } else {
        std::cout << "Error: Invalid index." << std::endl;
    }
    return m; //return modified matrix copy
}
int getIntInput(const std::string& prompt) {
    std::string input;
    int value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        
        //check for empty input or only whitespace
        if (input.empty() || input.find_first_not_of(" \t\n\r") == std::string::npos) {
            std::cout << "Invalid input. Enter a valid integer: ";
            continue;
        }
        
        //try to convert string to integer
        std::istringstream iss(input);
        if (iss >> value && iss.get() == EOF) {
            return value;
        }
        
        std::cout << "Invalid input. Enter a valid integer: ";
    }
}

int main() {
	std::string filename;
    std::cout << "Enter a matrix file: ";
    std::getline(std::cin, filename);
    //make sure filename is not empty or just whitespace
    while(filename.empty() || filename.find_first_not_of(" \t\n\r") == std::string::npos) {
        std::cout << "Invalid input. Please enter a filename: ";
        std::getline(std::cin, filename);
}

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
    Matrix C_add = A + B;
    C_add.print();

    //multiply 2 matrices
    std::cout << "\n     ---A * B---" << std::endl;
    Matrix C_mult = A * B;
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
    swapRows(A, r1, r2);
    
    //swap cols and display result
    std::cout << "\n -----Swap Columns-----" << std::endl;
    int c1 = getIntInput("Enter first column index to swap: ");
    int c2 = getIntInput("Enter second column index to swap: ");
    //A is already modified from rows swap
    swapCols(A, c1, c2);

    //update element
    std::cout << "\n -----Update Element-----" << std::endl;
    int r = getIntInput("Enter row index to update: ");
    int c = getIntInput("Enter column index to update: ");
    int value = getIntInput("Enter new value: ");
    //A is already modified from rows and cols swap
    updateElement(A, r, c, value);

    return 0;
}