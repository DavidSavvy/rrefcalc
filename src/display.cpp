#include "display.h"

void displayGuidance() {
    cout << "To input a matrix, first enter the number of rows and columns. \nThen, input each row one by one, separating elements with spaces. \nExample: \nRows: 2 \nColumns: 2 \nRow 1: 1 2 \nRow 2: 3 4" << endl << endl;
}

// Begins the process of filling matrix
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

// Edits matrix row by row
void assembleMatrix(vector<vector<double>>& matrix, int rows, int cols) {
    vector<double> currentRow;
    for (int i = 0; i < rows; i++) {
         currentRow = promptForMatrixRow(i + 1, cols);
         matrix.at(i) = currentRow;
    }
}

// Prompts for each individual matrix row
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

// Automatic retry prompt
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

// Prompts for a single integer with a string output beforehand
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