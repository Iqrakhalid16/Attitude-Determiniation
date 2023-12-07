#pragma once
#include "pch.h"
#include "FileIO.h"
#include "Rinex2Nav.h"
#include "globals.h"
#include "math.h"
#include <numeric>
#include "externs.h"

Cart ECEF2ENU(Cart SatPos, Cart InitPos);
