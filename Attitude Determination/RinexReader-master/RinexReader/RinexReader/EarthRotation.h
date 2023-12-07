#pragma once
#include "pch.h"
#include "FileIO.h"
#include "Rinex2Nav.h"
#include "globals.h"
#include "math.h"
#include <numeric>
#include "externs.h"


Cart EarthRotation(double transit_time, Cart SatPos);
