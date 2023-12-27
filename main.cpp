#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

bool valdiateNumericInput(string input);
void displayRREF(const vector<vector<int>>& rrefMatrix);
void addRows(vector<vector<int>>& matrix, int targetRow, int rowToAdd, int scalar);
bool isZeroRow(vector<vector<int>> matrix, int rowNumber);
void multiplyRow(vector<vector<int>>& matrix, int rowNumber, int scalar);
void swapRows(vector<vector<int>>& matrix, int numRow, int numRow2);
bool promptForRetry();
int promptForInteger(string prompt);
void toRREF(vector<vector<int>>& matrix);
void normalizeRow(vector<vector<int>>& matrix, int rowNumber, int pivot);
int findPivot(vector<vector<int>>& matrix, int colNumber);
void zeroAboveAndBelow(vector<vector<int>>& matrix, int rowNumber, int colNumber);

int main(){
    // This is a test of the DisplayRREF function:
    //vector<vector<int>> h = {{9,-2,-1,26},{-8,-1,-4,-5},{-5,-1,-2,-3}};
    //vector<vector<int>> h = {{9,-2,-1},{-8,-1,-4},{-5,-1,-2}};
    vector<vector<int>> h = {{1,2,1},{-2,-3,1},{3,5,0}};
    toRREF(h);
    displayRREF(h);
    // This is the end of the test.
    return 0;
}

// Display a matrix that is already in RREF form.
// Expects the matrix to be in RREF form.
void displayRREF(const vector< vector<int> >& rrefMatrix) {
    cout << "The Reduced Row Echelon Form is:" << endl;
    for (const vector<int>& row : rrefMatrix) {
        for (const int& value : row) {
            cout << " " << value;
        }
        cout << endl;
    }
}

// Goes row by row
// Finds pivot value (at col number)
// Normalizes current row based on the pivot value found (to make pivot 1)
// Zeroes the rows above and below the current row based on the pivot column 
void toRREF(vector<vector<int>>& matrix) {
    int numCols = matrix.at(0).size();
    int numRows = matrix.size();
    int pivot;
    int pivotValue;
    for (int i = 0; i < numRows; i++) {
        pivot = findPivot(matrix, i);
        if (pivot == -1) {
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
void zeroAboveAndBelow(vector<vector<int>>& matrix, int rowNumber, int colNumber) {
    int numRows = matrix.size();
    int numCols = matrix.at(0).size();
    for (int i = 0; i < numRows; i++) {
        if (i == rowNumber) {
            continue;
        }   
        addRows(matrix, i, rowNumber, -(matrix.at(i).at(colNumber)));
    }
}

// Finds first non-zero column based on a given row
int findPivot(vector<vector<int>>& matrix, int rowNumber) {
    int numRows = matrix.size();
    for (int i = 0; i < numRows; i++) {
        if (matrix.at(rowNumber).at(i) != 0) {
            return i;
        }
    }
    return -1;
}

// Divides entire row by a pivot value
void normalizeRow(vector<vector<int>>& matrix, int rowNumber, int pivot) {
    int numCols = matrix.at(rowNumber).size();
    for (int i = 0; i < numCols; i++) {
        matrix.at(rowNumber).at(i) /= pivot;
    }
}

// Adds a row to a targetRow multiplied by a scalar
void addRows(vector<vector<int>>& matrix, int targetRow, int rowToAdd, int scalar) {
    int rowLength = matrix.at(targetRow).size();
    for (int i = 0; i < rowLength; i++) {
        matrix.at(targetRow).at(i) += (matrix.at(rowToAdd).at(i) * scalar);
    }
}

// Checks if entire row is zeroes
bool isZeroRow(vector<vector<int>> matrix, int rowNumber) {
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
void multiplyRow(vector<vector<int>>& matrix, int rowNumber, int scalar) {
    int rowLength = matrix.at(rowNumber).size();
    for (int i = 0; i < rowLength; i++) {
        matrix.at(rowNumber).at(i) *= scalar;
    }
}

void swapRows(vector<vector<int>>& matrix, int numRow, int numRow2) {
    vector<int> temp = matrix.at(numRow);
    matrix.at(numRow) = matrix.at(numRow2);
    matrix.at(numRow2) = temp;
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
    cout << endl << prompt;
    cin >> userInput;

    for(int i = 0; i < userInput.length(); i++){ //Checks for any non integer characters in userInput
        if(!isdigit(userInput[i]))
            allNumbers = false;
    }

    if(allNumbers) //Returns an integer conversion if userInput is all numbers
        return stoi(userInput);
    else //Prompts for a new input otherwise
        return promptForInteger("Invalid input, please enter a number: ");    
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


  




