#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

bool ValdiateNumericInput(string input) {
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

// Display a matrix that is already in RREF form.
// Expects the matrix to be in RREF form.
void DisplayRREF(const vector< vector<int> >& rrefMatrix) {
    cout << "The Reduced Row Echelon Form is:" << endl;
    for (const vector<int>& row : rrefMatrix) {
        for (const int& value : row) {
            cout << " " << value;
        }
        cout << endl;
    }

}

void addRows(vector<vector<int>>& matrix, int targetRow, int rowToAdd, int scalar) {
    int rowLength = matrix.at(targetRow).size();
    for (int i = 0; i < rowLength; i++) {
        matrix.at(targetRow).at(i) += (matrix.at(rowToAdd).at(i) * scalar);
    }
}

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

void swapRows(vector<vector<int>>& matrix, int numRow, int numRow2){
    vector<int> temp = matrix.at(numRow);
    matrix.at(numRow) = matrix.at(numRow2);
    matrix.at(numRow2) = temp;
}

bool PromptForRetry(){ //Asks user if they'd like to retry in case of failed input or operation, returns bool
    string retry;
    cout << "\nOperation or input failed, would you like to retry? (Y/N) ";
    cin >> retry;

    if(retry == "Y" || retry == "y")
        return true;
    else if(retry == "N" || retry == "n")
        return false;
    else //Calls function again if they input invalid response
        return PromptForRetry();
}

int PromptForInteger(string prompt){
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
        return PromptForInteger("Invalid input, please enter a number: ");    
}

int main(){
    // This is a test of the DisplayRREF function:
    vector< vector<int> > h = {{1,2,3}, {4,5,6}, {7,8,9}};
    DisplayRREF(h);
    // This is the end of the test.

    return 0;
}
  




