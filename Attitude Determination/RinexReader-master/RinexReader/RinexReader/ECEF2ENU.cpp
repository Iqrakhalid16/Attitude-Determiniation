#include "pch.h"
#include "ECEF2ENU.h"

Cart ECEF2ENU(Cart SatPos, Cart InitPos) 
{
	double lat, lon, mR[3][3];
	llh LLH;
	Cart Baseline, ENU;

	LLH = ECEF2LLH(InitPos);

	lat = LLH.lat;
	lon = LLH.lon;

	//Baseline differences
	Baseline.X = SatPos.X - InitPos.X;
	Baseline.Y = SatPos.Y - InitPos.Y;
	Baseline.Z = SatPos.Z - InitPos.Z;

	//Rotation matrix
	mR[0][0] = -sin(lon);
	mR[0][1] = cos(lon);
	mR[0][2] = 0;
	mR[1][0] = -sin(lat) * cos(lon);
	mR[1][1] = -sin(lat) * sin(lon);
	mR[1][2] = cos(lat);
	mR[2][0] = cos(lat) * cos(lon);
	mR[2][1] = cos(lat) * sin(lon);
	mR[2][2] = sin(lat);

	ENU.X = mR[0][0] * Baseline.X + mR[0][1] * Baseline.Y + mR[0][2] * Baseline.Z;
	ENU.Y = mR[1][0] * Baseline.X + mR[1][1] * Baseline.Y + mR[1][2] * Baseline.Z;
	ENU.Z = mR[2][0] * Baseline.X + mR[2][1] * Baseline.Y + mR[2][2] * Baseline.Z;
	
	return ENU;
}