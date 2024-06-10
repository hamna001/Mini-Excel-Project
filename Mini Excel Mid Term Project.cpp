#include <iostream>
#include <vector>

class MiniExcel {
private:
    class Cell {
    public:
        char data;
        Cell* up;
        Cell* down;
        Cell* left;
        Cell* right;

        Cell() : data(' '), up(nullptr), down(nullptr), left(nullptr), right(nullptr) {}
    };

    Cell* root;
    Cell* current;
    int rows;
    int cols;

public:
    MiniExcel(int rows, int cols) : rows(rows), cols(cols) {
        root = new Cell();
        current = root;
        buildGrid(rows, cols);
    }

    void buildGrid(int rows, int cols) {
        // Construct the grid with the specified number of rows and columns
        Cell* prevRow = root;
        Cell* prevCol = root;

        for (int i = 0; i < rows; i++) {
            Cell* currentRow = prevRow;
            for (int j = 0; j < cols; j++) {
                Cell* cell = new Cell();
                currentRow->right = cell;
                cell->left = currentRow;
                cell->up = prevCol;
                if (prevCol) {
                    prevCol->down = cell;
                }
                prevCol = cell;
                currentRow = currentRow->right;
            }
            prevRow = prevRow->down;
        }
    }

    void moveRight() {
        if (current->right) {
            current = current->right;
        }
    }

    void moveLeft() {
        if (current->left) {
            current = current->left;
        }
    }

    void moveUp() {
        if (current->up) {
            current = current->up;
        }
    }

    void moveDown() {
        if (current->down) {
            current = current->down;
        }
    }

    void setData(char data) {
        if (current) {
            current->data = data;
        }
    }

    char getData() {
        if (current) {
            return current->data;
        }
        return ' ';
    }

    void moveToTopLeft() {
        while (current->up) {
            moveUp();
        }
        while (current->left) {
            moveLeft();
        }
    }

    void InsertRowAbove() {
        if (current && current->up) {
            Cell* newRow = new Cell();
            Cell* currentCell = current;

            while (currentCell) {
                Cell* cellAbove = currentCell->up;
                Cell* newCell = new Cell();

                newCell->down = currentCell;
                currentCell->up = newCell;

                newCell->up = cellAbove;
                if (cellAbove) {
                    cellAbove->down = newCell;
                }

                newCell->left = currentCell->left;
                newCell->right = currentCell->right;

                if (currentCell->left) {
                    currentCell->left->right = newCell;
                }

                if (currentCell->right) {
                    currentCell->right->left = newCell;
                }

                currentCell = currentCell->right;
            }

            current = newRow;
            rows++;
        }
    }

    void InsertRowBelow() {
        if (current) {
            Cell* newRow = new Cell();
            Cell* currentCell = current;

            while (currentCell) {
                Cell* cellBelow = currentCell->down;
                Cell* newCell = new Cell();

                newCell->up = currentCell;
                currentCell->down = newCell;

                newCell->down = cellBelow;
                if (cellBelow) {
                    cellBelow->up = newCell;
                }

                newCell->left = currentCell->left;
                newCell->right = currentCell->right;

                if (currentCell->left) {
                    currentCell->left->right = newCell;
                }

                if (currentCell->right) {
                    currentCell->right->left = newCell;
                }

                currentCell = currentCell->right;
            }

            while (current->up) {
                moveUp();
            }
            rows++;
        }
    }

    void InsertColumnToRight() {
        if (current) {
            Cell* newColumn = new Cell();
            Cell* currentCell = current;

            while (currentCell) {
                Cell* cellRight = currentCell->right;
                Cell* newCell = new Cell();

                newCell->left = currentCell;
                currentCell->right = newCell;

                newCell->right = cellRight;
                if (cellRight) {
                    cellRight->left = newCell;
                }

                newCell->up = currentCell->up;
                newCell->down = currentCell->down;

                if (currentCell->up) {
                    currentCell->up->down = newCell;
                }

                if (currentCell->down) {
                    currentCell->down->up = newCell;
                }

                currentCell = currentCell->down;
            }

            while (current->left) {
                moveLeft();
            }
            cols++;
        }
    }

    void InsertColumnToLeft() {
        if (current && current->left) {
            Cell* newColumn = new Cell();
            Cell* currentCell = current;

            while (currentCell) {
                Cell* cellLeft = currentCell->left;
                Cell* newCell = new Cell();

                newCell->right = currentCell;
                currentCell->left = newCell;

                newCell->left = cellLeft;
                if (cellLeft) {
                    cellLeft->right = newCell;
                }

                newCell->up = currentCell->up;
                newCell->down = currentCell->down;

                if (currentCell->up) {
                    currentCell->up->down = newCell;
                }

                if (currentCell->down) {
                    currentCell->down->up = newCell;
                }

                currentCell = currentCell->down;
            }

            while (current->right) {
                moveRight();
            }
            cols++;
        }
    }

    void InsertCellByRightShift() {
        if (current) {
            Cell* newCell = new Cell();
            Cell* currentCell = current;

            while (currentCell->right) {
                Cell* cellRight = currentCell->right;
                currentCell->right = newCell;
                newCell->left = currentCell;

                newCell->right = cellRight;
                if (cellRight) {
                    cellRight->left = newCell;
                }

                newCell->up = currentCell->up;
                newCell->down = currentCell->down;

                if (currentCell->up) {
                    currentCell->up->down = newCell;
                }

                if (currentCell->down) {
                    currentCell->down->up = newCell;
                }

                currentCell = cellRight;
                newCell = newCell->right = new Cell();
            }
            cols++;
        }
    }

    void InsertCellByDownShift() {
        if (current) {
            Cell* newCell = new Cell();
            Cell* currentCell = current;

            while (currentCell->down) {
                Cell* cellBelow = currentCell->down;
                currentCell->down = newCell;
                newCell->up = currentCell;

                newCell->down = cellBelow;
                if (cellBelow) {
                    cellBelow->up = newCell;
                }

                newCell->left = currentCell->left;
                newCell->right = currentCell->right;

                if (currentCell->left) {
                    currentCell->left->right = newCell;
                }

                if (currentCell->right) {
                    currentCell->right->left = newCell;
                }

                currentCell = cellBelow;
                newCell = newCell->down = new Cell();
            }
            rows++;
        }
    }

    void DeleteCellByLeftShift() {
        if (current && current->left) {
            Cell* cellToDelete = current;
            Cell* cellLeft = cellToDelete->left;

            if (cellLeft->right == cellToDelete) {
                cellLeft->right = cellToDelete->right;
                if (cellToDelete->right) {
                    cellToDelete->right->left = cellLeft;
                }

                Cell* cellAbove = cellToDelete->up;
                if (cellAbove) {
                    cellAbove->down = nullptr;
                }

                current = cellLeft;
                delete cellToDelete;
                cols--;
            }
        }
    }

    void DeleteCellByUpShift() {
        if (current && current->up) {
            Cell* cellToDelete = current;
            Cell* cellAbove = cellToDelete->up;

            cellAbove->down = cellToDelete->down;

            if (cellToDelete->down) {
                cellToDelete->down->up = cellAbove;
            }

            current = cellAbove;
            delete cellToDelete;
            rows--;
        }
    }

    void PrintGrid() {
        moveToTopLeft();
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << "+---+ ";
                moveRight();
            }
            std::cout << std::endl;
            for (int j = 0; j < cols; j++) {
                std::cout << "| " << getData() << " | ";
                moveRight();
            }
            std::cout << std::endl;
            for (int j = 0; j < cols; j++) {
                std::cout << "+---+ ";
            }
            std::cout << std::endl;
            moveDown();
        }
    }

    void InsertDataToCell(char data) {
        // Set data to the current cell
        setData(data);
    }

    void NavigateGrid(int row, int col) {
        // Move to the specified row and column
        moveToTopLeft();
        for (int i = 0; i < row; i++) {
            moveDown();
        }
        for (int j = 0; j < col; j++) {
            moveRight();
        }
    }

    int getRows() {
        return rows;
    }

    int getCols() {
        return cols;
    }
};

int main() {
    int rows, cols;
    std::cout << "Enter the number of rows and columns for the grid: ";
    std::cin >> rows >> cols;

    MiniExcel excel(rows, cols);
    char input;

    std::cout << "Use the following keys to perform actions:" << std::endl;
    std::cout << "r - InsertRowAbove" << std::endl;
    std::cout << "R - InsertRowBelow" << std::endl;
    std::cout << "c - InsertColumnToRight" << std::endl;
    std::cout << "C - InsertColumnToLeft" << std::endl;
    std::cout << "s - InsertCellByRightShift" << std::endl;
    std::cout << "S - InsertCellByDownShift" << std::endl;
    std::cout << "l - DeleteCellByLeftShift" << std::endl;
    std::cout << "u - DeleteCellByUpShift" << std::endl;
    std::cout << "i - for insertingdata" << std::endl;
    std::cout << "q - Quit" << std::endl;

    excel.PrintGrid();

    while (true) {
        std::cout << "Enter a key: ";
        std::cin >> input;

        switch (input) {
        case 'r':
            excel.InsertRowAbove();
            break;
        case 'R':
            excel.InsertRowBelow();
            break;
        case 'c':
            excel.InsertColumnToRight();
            break;
        case 'C':
            excel.InsertColumnToLeft();
            break;
        case 's':
            excel.InsertCellByRightShift();
            break;
        case 'S':
            excel.InsertCellByDownShift();
            break;
        case 'l':
            excel.DeleteCellByLeftShift();
            break;
        case 'u':
            excel.DeleteCellByUpShift();
            break;

        case 'i': {
            char data;
            std::cout << "Enter data to insert: ";
            std::cin >> data;
            int row, col;
            std::cout << "Enter row and column (e.g., 1 2): ";
            std::cin >> row >> col;
            excel.NavigateGrid(row, col);
            excel.InsertDataToCell(data);
            break;
        }
        case 'q':
            return 0; // Exit the program
        default:
            std::cout << "Invalid input. Please try again." << std::endl;
        }

        excel.PrintGrid();
    }

    return 0;
}
