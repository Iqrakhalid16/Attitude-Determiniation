#pragma once
#include "pch.h"
#include "FileIO.h"
#include "Rinex2Nav.h"

using namespace std;

#define MAXSATs 12
#define sol 299792458

//Earth gravitational parameter  in m ^ 3 / s ^ 2
#define gra 398600800000000.0

// Earth rotation rate in rad / s
#define rot_rate  0.000072921151467

// Earth radius in meters
#define Earth_R 6378137.0000

// Earth semiminor in meters
#define semi_minor 6356752.3142

#define pi 3.14159265358979323846   // pi

// Define a structure to hold observation information
struct ObservationInfo {
	string prn;
	string obsTimeHMS;
	double SOW;
	double c1Value;
	double corrected_c1Value;
	double smoothedcode;
	double corrected_smoothedcode;
	double l1Value;
	double doppler;
	int clockBias;         // Clock Bias field
	int clockDrift;        // Clock Drift field
	int clockDriftRate;    // Clock Drift Rate field
};

// Cartesian coordinate system
struct Cart {
	double X; 
	double Y; 
	double Z; 
};

// Spherical coordinate system
struct llh {
	double lat; // latitude in degrees
	double lon; // longitude in degrees
	double alt; // altitude in degrees
};

