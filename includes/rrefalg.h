#ifndef RREFALG_H
#define RREFALG_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <format>

using namespace std;

void addRows(vector<vector<double>>& matrix, int targetRow, int rowToAdd, double scalar);
bool isZeroRow(vector<vector<double>> matrix, int rowNumber);
void multiplyRow(vector<vector<double>>& matrix, int rowNumber, int scalar);
void swapRows(vector<vector<double>>& matrix, int numRow, int numRow2);
void toRREF(vector<vector<double>>& matrix);
void normalizeRow(vector<vector<double>>& matrix, int rowNumber, double pivotValue);
int findPivot(vector<vector<double>>& matrix, int rowNumber);
int findNextPivot(vector<vector<double>>& matrix, int colNumber);
void zeroAboveAndBelow(vector<vector<double>>& matrix, int rowNumber, int colNumber);

#endif