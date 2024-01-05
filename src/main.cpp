#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <format>

using namespace std;

bool valdiateNumericInput(string input);
void displayRREF(const vector<vector<double>>& rrefMatrix);
bool promptForRetry();
int promptForInteger(string prompt);
void displayGuidance();
vector<vector<double>> promptForMatrix();
void assembleMatrix(vector<vector<double>>& matrix, int rows, int cols);
vector<double> promptForMatrixRow(int rowNumber, int cols);

void addRows(vector<vector<double>>& matrix, int targetRow, int rowToAdd, double scalar);
bool isZeroRow(vector<vector<double>> matrix, int rowNumber);
void multiplyRow(vector<vector<double>>& matrix, int rowNumber, int scalar);
void swapRows(vector<vector<double>>& matrix, int numRow, int numRow2);
void toRREF(vector<vector<double>>& matrix);
void normalizeRow(vector<vector<double>>& matrix, int rowNumber, double pivotValue);
int findPivot(vector<vector<double>>& matrix, int rowNumber);
int findNextPivot(vector<vector<double>>& matrix, int colNumber);
void zeroAboveAndBelow(vector<vector<double>>& matrix, int rowNumber, int colNumber);

int main(){
    // This is a test of the DisplayRREF function:
    //vector<vector<int>> h = {{9,-2,-1,26},{-8,-1,-4,-5},{-5,-1,-2,-3}};
    //vector<vector<double>> h = {{9,-2,-1},{-8,-1,-4},{-5,-1,-2}};
    displayGuidance();
    vector<vector<double>> h = promptForMatrix();
    //vector<vector<double>> h = {{0,2,1},{-2,0,1},{3,5,0}};
    toRREF(h);
    displayRREF(h);
    // This is the end of the test.
    return 0;
}

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

void displayGuidance() {
    cout << "To input a matrix, first enter the number of rows and columns. \nThen, input each row one by one, separating elements with spaces. \nExample: \nRows: 2 \nColumns: 2 \nRow 1: 1 2 \nRow 2: 3 4" << endl << endl;
}

vector<vector<double>> promptForMatrix() {
    int rows = promptForInteger("Rows: ");
    int cols = promptForInteger("Columns: ");

    // clear the rest of the instream
    string buffer;
    getline(cin, buffer);

    vector<vector<double>> matrix(rows, vector<double>(cols));

    assembleMatrix(matrix, rows, cols);
    return matrix;
}

void assembleMatrix(vector<vector<double>>& matrix, int rows, int cols) {
    vector<double> currentRow;
    for (int i = 0; i < rows; i++) {
         currentRow = promptForMatrixRow(i + 1, cols);
         matrix.at(i) = currentRow;
    }
}

vector<double> promptForMatrixRow(int rowNumber, int cols) {
    vector<double> currentRow;
    string rawString;  
    string currentCol;
    stringstream sstream;

    int count;
    bool validInput;
    do {
        // reset vector
        currentRow.clear();
        
        // clear stringstream
        sstream.str(string());

        //cout << rawString << endl;
        cout << "Row " + to_string(rowNumber) + ": ";
        validInput = true;
        getline(cin, rawString);
        sstream << rawString;
        count = 0;
        while (sstream >> currentCol) {      
            if (!valdiateNumericInput(currentCol)) {
                validInput = false;
                cout << "Invalid input! Please enter numbers only." << endl;
                break;
            }
            currentRow.push_back(stoi(currentCol));
            count++;
        }
        if (!validInput) {
            
            continue;
        }
        if (count != cols) {
            cout << "Error: Expected " + to_string(cols) + " elements for the matrix. Please re-enter row " + to_string(rowNumber) << endl;
            count = 0;
            validInput = false;
        } 
    } 
    while (!validInput);
    
    return currentRow;
}

bool promptForRetry() { //Asks user if they'd like to retry in case of failed input or operation, returns bool
    string retry;
    cout << "\nOperation or input failed, would you like to retry? (Y/N) ";
    cin >> retry;

    if(retry == "Y" || retry == "y")
        return true;
    else if(retry == "N" || retry == "n")
        return false;
    else //Calls function again if they input invalid response
        return promptForRetry();
}

int promptForInteger(string prompt) {
    string userInput;
    bool allNumbers = true;
    cout << prompt;
    cin >> userInput;

    //Checks for any non integer characters in userInput
    for(int i = 0; i < userInput.length(); i++) { 
        if(!isdigit(userInput[i])) {
            allNumbers = false;
        }   
    }

    //Returns an integer conversion if userInput is all numbers
    if(allNumbers) {
        return stoi(userInput);
    } 
    //Prompts for a new input otherwise
    else {
        return promptForInteger("Invalid input, please enter a number: ");    
    }
}

bool valdiateNumericInput(string input) {
    // loops through the string input
    for (int i = 0; i < input.size(); i++) { 
        // checks to see if the char is a number or not
        if (isalpha(input.at(i))) { 
            // returns false if its not a number
            return false; 
        }
    }
    // returns true if all chars are numbers
    return true;
} 


  




