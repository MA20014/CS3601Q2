#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>

class Matrix {
private:
    std::vector<std::vector<int>> data; // Matrix data stored as a vector of vectors
    bool isNaM; // Flag to indicate if the matrix is Not a Matrix

public:
    // Constructor to initialize the matrix from a string representation
    Matrix(const std::string& matrixString) {
        // Parse the string to extract matrix elements
        std::istringstream iss(matrixString);
        char discard;
        int num;
        std::vector<int> row;
        while (iss >> discard) {
            if (discard == '(') {
                while (iss >> num) {
                    row.push_back(num);
                    if (iss.peek() == ',')
                        iss.ignore();
                    else if (iss.peek() == ')') {
                        iss.ignore();
                        break;
                    }
                }
                // Store the parsed row in the matrix data
                data.push_back(row);
                row.clear();
            }
        }
        // Check if the matrix is valid
        isNaM = false;
        int cols = data[0].size();
        for (size_t i = 1; i < data.size(); ++i) {
            if (data[i].size() != cols) {
                isNaM = true;
                break;
            }
        }
    }

    // Destructor to free memory (not needed in this case as the vector will manage its own memory)

    // Function to check if the matrix is Not a Matrix
    bool IsNaM() const {
        return isNaM;
    }

    // Indexing operator to access individual elements in the matrix
    int& operator()(size_t row, size_t col) {
        return data[row][col];
    }

    // Function to perform matrix addition
    Matrix Add(const Matrix& other) const {
        // Check if matrices have compatible dimensions for addition
        if (data.size() != other.data.size() || data[0].size() != other.data[0].size())
            throw std::invalid_argument("Matrix dimensions are not compatible for addition.");

        Matrix result("(");
        // Perform element-wise addition
        for (size_t i = 0; i < data.size(); ++i) {
            std::vector<int> row;
            for (size_t j = 0; j < data[i].size(); ++j) {
                row.push_back(data[i][j] + other.data[i][j]);
            }
            result.data.push_back(row);
        }
        return result;
    }

    // Function to perform matrix subtraction
    Matrix Subtract(const Matrix& other) const {
        // Check if matrices have compatible dimensions for subtraction
        if (data.size() != other.data.size() || data[0].size() != other.data[0].size())
            throw std::invalid_argument("Matrix dimensions are not compatible for subtraction.");

        Matrix result("(");
        // Perform element-wise subtraction
        for (size_t i = 0; i < data.size(); ++i) {
            std::vector<int> row;
            for (size_t j = 0; j < data[i].size(); ++j) {
                row.push_back(data[i][j] - other.data[i][j]);
            }
            result.data.push_back(row);
        }
        return result;
    }

    // Function to perform matrix multiplication
    Matrix Multiply(const Matrix& other) const {
        // Check if matrices have compatible dimensions for multiplication
        if (data[0].size() != other.data.size())
            throw std::invalid_argument("Matrix dimensions are not compatible for multiplication.");

        Matrix result("(");
        // Perform matrix multiplication
        for (size_t i = 0; i < data.size(); ++i) {
            std::vector<int> row;
            for (size_t j = 0; j < other.data[0].size(); ++j) {
                int sum = 0;
                for (size_t k = 0; k < other.data.size(); ++k) {
                    sum += data[i][k] * other.data[k][j];
                }
                row.push_back(sum);
            }
            result.data.push_back(row);
        }
        return result;
    }

    // Function to print the matrix
    void Print() const {
        for (size_t i = 0; i < data.size(); ++i) {
            std::cout << "(";
            for (size_t j = 0; j < data[i].size(); ++j) {
                std::cout << data[i][j];
                if (j < data[i].size() - 1)
                    std::cout << " ";
            }
            std::cout << ")" << std::endl;
        }
    }
};

int main() {
    try {
        // Example usage:
        Matrix m1("(14,28,32),(48,50,62),(72,87,93)");
        Matrix m2("(96,81,79),(61,59,42),(37,21,17)");

        std::cout << "Matrix 1:" << std::endl;
        m1.Print();

        std::cout << "\nMatrix 2:" << std::endl;
        m2.Print();

        if (m1.IsNaM() || m2.IsNaM()) {
            std::cout << "One or more matrices are Not a Matrix." << std::endl;
            return 1;
        }

        Matrix result_add = m1.Add(m2);
        std::cout << "\nMatrix Addition Result:" << std::endl;
        result_add.Print();

        Matrix result_sub = m1.Subtract(m2);
        std::cout << "\nMatrix Subtraction Result:" << std::endl;
        result_sub.Print();

        Matrix result_mul = m1.Multiply(m2);
        std::cout << "\nMatrix Multiplication Result:" << std::endl;
        result_mul.Print();
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
