#pragma once
#include "pch.h"
#include "FileIO.h"
#include "Rinex2Nav.h"
#include "globals.h"
#include "math.h"
#include <numeric>
#include "externs.h"


double Norm(double X, double Y, double Z);

// matrix multiplier
void VecMult(vector<vector<double>>& vec, vector<vector<double>>& Matr1, vector<vector<double>>& Matr2);

// takes transpose of input vecB and outputs vecA
void TransMat(vector<vector<double>>& vecA, vector<vector<double>>& vecB);

void Matr_decomp(vector<vector<double>>& vecA, vector<vector<double>>& vecB, int y, int z);

double determinant(vector<vector<double>>& vec);

double Sign(int a, int b);

void adjoint4(vector<vector<double>>& out, vector<vector<double>>& in1);

void Inverse(vector<vector<double>>& out, vector<vector<double>>& in1);


