#pragma once
#include "pch.h"
#include "FileIO.h"
#include "Rinex2Nav.h"
#include "globals.h"
#include "math.h"
#include <numeric>
#include "externs.h"

#define MaskAngle 10.0

void SPP(vector<ObservationInfo>* observationInfoList, int sats);
