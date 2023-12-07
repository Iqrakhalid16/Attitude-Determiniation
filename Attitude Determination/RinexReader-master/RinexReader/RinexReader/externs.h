#pragma once
#include "pch.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "FileIO.h"
#include <string.h>
#include "Rinex2Nav.h"
#include "ECEF2ENU.h"

using namespace std;

extern vector<Rinex2Nav::DataGPS> NavGlobal[12];

extern Cart ECEF2ENU(Cart SatPos, Cart InitPos);

extern llh ECEF2LLH(Cart XYZ);

extern Cart EarthRotation(double transit_time, Cart SatPos);

extern Cart SinglePointGPS(vector<ObservationInfo>* observationInfoList, vector<Cart>SatXYZ, vector<unsigned int>SatsToIncl, Cart InitPos, int epoch, double* receiver_clock);

extern double Norm(double X, double Y, double Z);

extern void VecMult(vector<vector<double>>& vec, vector<vector<double>>& Matr1, vector<vector<double>>& Matr2);

extern void TransMat(vector<vector<double>>& vecA, vector<vector<double>>& vecB);

extern void Matr_decomp(vector<vector<double>>& vecA, vector<vector<double>>& vecB, int y, int z);

extern double determinant(vector<vector<double>>& vec);

extern double Sign(int a, int b);

extern void adjoint4(vector<vector<double>>& out, vector<vector<double>>& in1);

extern void Inverse(vector<vector<double>>& out, vector<vector<double>>& in1);