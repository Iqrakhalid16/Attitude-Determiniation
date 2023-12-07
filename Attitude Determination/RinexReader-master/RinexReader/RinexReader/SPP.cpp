#include "pch.h"
#include "SPP.h"
#include "SatPos.h"

void SPP(vector<ObservationInfo>* observationInfoList, int sats)
{
	double transit_time = 0, sat_clk_corr, group_delay, angle, receiver_clock=0;
	vector<Cart>SatPos;
	vector<Cart>SatXYZ;
	vector<Cart>PosAll;
	vector<int>KeySat;
	vector<double>ElevAngle;
	vector<double>sat_clk_correction;
	vector<double>GroupDelay;
	int MaxAnglePRN;
	vector<int>lowAngle;
	vector<unsigned int>HighAngle;
	Cart SatENU;
	Cart InitPos;

	sat_clk_correction.resize(sats, 1);
	GroupDelay.resize(sats, 1);

	for (unsigned int r1 = 0; r1 < sats; r1++)
	{
		sat_clk_correction[r1] = 0.0;
		GroupDelay[r1] = 0.0;

	}


	for (unsigned int i1 = 0; i1 < observationInfoList[0].size(); i1++)
	{
		if (i1 == 0)
		{
			InitPos.X = 1;
			InitPos.Y = 1;
			InitPos.Z = 1;
		}

		else
		{
			InitPos = PosAll[i1-1];			
		}

		for (unsigned int j1 = 0; j1 < sats; j1++)
		{
			transit_time = observationInfoList[j1][i1].c1Value / sol + sat_clk_correction[j1] - receiver_clock - GroupDelay[j1];
			GetSatPosECEF(&sat_clk_corr, &group_delay, &SatPos, observationInfoList, transit_time, j1, i1);

			sat_clk_correction[j1] = sat_clk_corr;
			GroupDelay[j1] = group_delay;

			//Filter out the satellite with low elevation angle
				SatENU = ECEF2ENU(SatPos[j1], InitPos);

				angle = atan(SatENU.Z / sqrt(pow(SatENU.X, 2.0) + pow(SatENU.Y, 2.0))) * 180 / pi;
				ElevAngle.push_back(angle);

				if (j1 != 0)
				{
					if (ElevAngle[j1] > ElevAngle[j1 - 1])
					{
						MaxAnglePRN = NavGlobal[j1][0].PRN;
					}
				}
				
				else
				{
					MaxAnglePRN = NavGlobal[j1][0].PRN;
				}

				if ((angle < MaskAngle) && (i1 != 0))
				{
					lowAngle.push_back(NavGlobal[j1][0].PRN);
			    }

				else if ((angle > MaskAngle)||(i1==0))
				{
					HighAngle.push_back(j1);
				}

		    //Correct the code data by removing receiver clock error,
			// satellite clock error, group delay for smoothed and raw code data
			observationInfoList[j1][i1].corrected_smoothedcode = observationInfoList[j1][i1].smoothedcode - receiver_clock * sol +
				sat_clk_corr * sol - group_delay * sol;
			observationInfoList[j1][i1].corrected_c1Value = observationInfoList[j1][i1].c1Value - receiver_clock * sol +
				sat_clk_corr * sol - group_delay * sol;

			SatXYZ.push_back(EarthRotation(transit_time, SatPos[j1]));


		}

		KeySat.push_back(MaxAnglePRN);

		// Single point positioning using smoothed code data
		PosAll.push_back(SinglePointGPS(observationInfoList, SatXYZ, HighAngle, InitPos, i1, &receiver_clock));
		

		ElevAngle.clear();
		SatPos.clear();
		SatXYZ.clear();
		lowAngle.clear();
		HighAngle.clear();
	}

}