#pragma once
#include "globals.h"
#include "externs.h"
#include "math.h"
#include <numeric>
void smoothing(vector<ObservationInfo>* observationInfoList, int smooth_interval, int totalsats);