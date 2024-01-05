#ifndef DISPLAY_H
#define DISPLAY_H

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

#endif