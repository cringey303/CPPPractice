# Matrix Manipulation with File I/O

This is a C++ program that implements string-based arithmetic operations in C++ without converting strings to built-in numeric types

## Features

* **File Input:** Reads pairs of numbers from a user-specified file.
* **String-Only Arithmetic:** Implements string-only addition, handling positive/negative numbers and decimal alignment.
* **Custom Validation:** Validates each number string with strict formatting rules (`(+|-)A(.B)`) without using `try-catch` or standard conversion functions.
* **Error Handling:** Detects and reports bad file and invalid number formats.

## How to Run

1.  Download this project and open it in a terminal.
2.  Run the `make` command:

    ```bash
    make
    ```

3.  This will use the `g++` compiler (with `-std=c++11` and `-Wall`) to build the executable file named `main`.

Once built, you can run the program from your terminal.

4.  Execute the program:

    ```bash
    ./main
    ```

5.  The program will then prompt you to enter the name of the file containing the matrices (e.g., `input.txt`).

### Example Usage

```bash
$ make
g++ -std=c++11 -Wall -g -o calculator main.cpp

$ ./main
Enter a matrix file: input.txt

     ---Matrix A---
    1    2    3    4
    5    6    7    8
    9   10   11   12
   13   14   15   16

     ---Matrix B---
   13   14   15   16
    9   10   11   12
    5    6    7    8
    1    2    3    4

     ---A + B---
   14   16   18   20
   14   16   18   20
   14   16   18   20
   14   16   18   20

     ---A * B---
   50   60   70   80
  162  188  214  240
  274  316  358  400
  386  444  502  560

 -----Diagonal Sums-----
-Matrix A
Main diagonal sum: 34
Secondary diagonal sum: 34

-Matrix B
Main diagonal sum: 34
Secondary diagonal sum: 34

 -----Swap Rows-----
Enter first row index to swap: 3
Enter second row index to swap: 2
Matrix after swapping rows 3 and 2:
    1    2    3    4
    5    6    7    8
   13   14   15   16
    9   10   11   12

 -----Swap Columns-----
Enter first column index to swap: 3
Enter second column index to swap: 2
Matrix after swapping columns 3 and 2:
    1    2    4    3
    5    6    8    7
    9   10   12   11
   13   14   16   15

 -----Update Element-----
Enter row index to update: 3
Enter column index to update: 2
Enter new value: 
Invalid input. Enter a valid integer: Enter new value: 3
Matrix after updating element at (3, 2):
    1    2    3    4
    5    6    7    8
    9   10   11   12
   13   14    3   16
...
