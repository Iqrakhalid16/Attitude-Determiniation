#pragma once
#include "pch.h"
#include "FileIO.h"
#include "Rinex2Nav.h"
#include "globals.h"
#include "math.h"
#include <numeric>
#include "externs.h"



void GetSatPosECEF(double* sat_clk_corr, double* group_delay, vector<Cart> *SatPos, vector<ObservationInfo>* observationInfoList, double transit_time, unsigned int sat, unsigned int epochNo);
