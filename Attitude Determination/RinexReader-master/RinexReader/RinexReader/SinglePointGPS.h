#pragma once
#include "pch.h"
#include "FileIO.h"
#include "Rinex2Nav.h"
#include "globals.h"
#include "math.h"
#include <numeric>
#include "externs.h"


Cart SinglePointGPS(vector<ObservationInfo>*observationInfoList, vector<Cart>SatXYZ, vector<unsigned int>SatsToIncl, Cart InitPos, int epoch, double *receiver_clock);
