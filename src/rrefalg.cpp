#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <format>

#include "rrefalg.h"

// Display a matrix that is already in RREF form.
// Expects the matrix to be in RREF form.
void displayRREF(const vector<vector<double>>& rrefMatrix) {
    cout << "The Reduced Row Echelon Form is:" << endl;
    for (const vector<double>& row : rrefMatrix) {
        for (const double& value : row) {
            if (abs(value) < 0.001) {
                cout << " " << 0; 
            } else {
                cout << " " << setprecision(2) << value;  
            }
                  
        }
        cout << endl;
    }
}

// Goes row by row
// Finds pivot value (at col number)
// Normalizes current row based on the pivot value found (to make pivot 1)
// Zeroes the rows above and below the current row based on the pivot column 
void toRREF(vector<vector<double>>& matrix) {
    int numCols = matrix.at(0).size();
    int numRows = matrix.size();
    int pivot;
    double pivotValue;
    for (int i = 0; i < numRows; i++) {
        pivot = findPivot(matrix, i);
        if (pivot == -1 || pivot != i) {
            if (i != (numRows - 1)) {
                int nextPivot = findNextPivot(matrix, i);
                swapRows(matrix, i, nextPivot);
                //displayRREF(matrix);
                i -= 1;
                continue;
            }
            continue;
        }
        pivotValue = matrix.at(i).at(pivot);
        
        normalizeRow(matrix, i, pivotValue);
        zeroAboveAndBelow(matrix, i, pivot);
    }
}

// Goes row by row
// If row is the row number with given, skips
// Otherwise, runs algorithm 
void zeroAboveAndBelow(vector<vector<double>>& matrix, int rowNumber, int colNumber) {
    int numRows = matrix.size();
    int numCols = matrix.at(0).size();
    for (int i = 0; i < numRows; i++) {
        if (i == rowNumber) {
            continue;
        }   
        if (isZeroRow(matrix, i)) {
            continue;
        }
        addRows(matrix, i, rowNumber, -(matrix.at(i).at(colNumber)));
    }
}

// Finds first non-zero column based on a given row
int findPivot(vector<vector<double>>& matrix, int rowNumber) {
    int numCols = matrix.at(0).size();
    for (int i = 0; i < numCols; i++) {
        if (matrix.at(rowNumber).at(i) != 0) {
            return i;
        }
    }
    return -1;
}

int findNextPivot(vector<vector<double>>& matrix, int colNumber) {
    int numRows = matrix.size();
    for (int i = 0; i < numRows; i++) {
        if (matrix.at(i).at(colNumber) != 0) {
            return i;
        }
    }
    return -1;
}

// Divides entire row by a pivot value
void normalizeRow(vector<vector<double>>& matrix, int rowNumber, double pivotValue) {
    int numCols = matrix.at(rowNumber).size();
    for (int i = 0; i < numCols; i++) {
        matrix.at(rowNumber).at(i) /= pivotValue;
    }
}

// Adds a row to a targetRow multiplied by a scalar
void addRows(vector<vector<double>>& matrix, int targetRow, int rowToAdd, double scalar) {
    int rowLength = matrix.at(targetRow).size();
    for (int i = 0; i < rowLength; i++) {
        matrix.at(targetRow).at(i) += (matrix.at(rowToAdd).at(i) * scalar);
    }
}

// Checks if entire row is zeroes
bool isZeroRow(vector<vector<double>> matrix, int rowNumber) {
    int rowLength = matrix.at(rowNumber).size();
    bool isZero = true;
    for (int i = 0; i < rowLength; i++) {
        if (matrix.at(rowNumber).at(i) != 0) {
            isZero = false;
        }
    }
    return isZero;
}

// Takes the 2d vector matrix as a reference
void multiplyRow(vector<vector<double>>& matrix, int rowNumber, int scalar) {
    int rowLength = matrix.at(rowNumber).size();
    for (int i = 0; i < rowLength; i++) {
        matrix.at(rowNumber).at(i) *= scalar;
    }
}

void swapRows(vector<vector<double>>& matrix, int numRow, int numRow2) {
    vector<double> temp = matrix.at(numRow);
    matrix.at(numRow) = matrix.at(numRow2);
    matrix.at(numRow2) = temp;
}