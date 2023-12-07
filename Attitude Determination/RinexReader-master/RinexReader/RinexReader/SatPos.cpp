#include "pch.h"
#include "SatPos.h"
#include "math.h"
#include <numeric>


void GetSatPosECEF(double *sat_clk_corr, double *group_delay, vector<Cart> *SatPos, vector<ObservationInfo>* observationInfoList, double transit_time, unsigned int sat, unsigned int epochNo)
{
	double transmit_time = 0, a=0, tj = 0, muj=0, Ej=0, Ej_backup=0, dEj=0, fj=0;
	double o_fj = 0, wj, rj, ij, Omega, mRotation[3][2], dt, rel;
	unsigned int iter = 0;
	Cart sat_pos;

	transmit_time = observationInfoList[sat][epochNo].SOW - transit_time;

	// Sat Coordinates calc.

	a = pow(NavGlobal[sat][0].Sqrt_a, 2.0) ;

	// Time elapsed since toe
		tj = transmit_time - NavGlobal[sat][0].TOE;
	
	// Format the time
		if (tj > 302400)
		{
			tj = tj - 604800;
		}

		else if(tj < -302400)
		{
			tj = tj + 604800;
		}

		//Mean anomaly time tj
		  muj = NavGlobal[sat][0].Mo + (sqrt(gra / pow(a, 3.0)) + NavGlobal[sat][0].Delta_n) * tj;

		// Iterative solution for Ej
		  Ej = muj;
		  iter = 0;

		  while (1)
		  {
			  iter = iter + 1;
			  Ej_backup = Ej;
			  Ej = muj + NavGlobal[sat][0].Eccentricity * sin(Ej);
			  dEj = Ej - Ej_backup;
			  if (abs(dEj) < 1.0e-13)
			  {
				  break;
			  }
			  if (iter > 10)
			  {
				  throw runtime_error("error: The calculation of satellite position can not converge!!!");
				  
		      }
		  }

		  // True anomaly
			  fj = atan2(sqrt(1.0 - pow(NavGlobal[sat][0].Eccentricity, 2.0)) * sin(Ej), cos(Ej) - NavGlobal[sat][0].Eccentricity);
		  // omega + fj
			  o_fj = fj + NavGlobal[sat][0].Omega;
		  // Argument of perigee
			  wj = o_fj + NavGlobal[sat][0].Cuc * cos(2.0 * o_fj) + NavGlobal[sat][0].Cus * sin(2.0 * o_fj);
		  // Radial distance
			  rj = a * (1.0 - NavGlobal[sat][0].Eccentricity * cos(Ej)) + NavGlobal[sat][0].Crc * cos(2.0 * o_fj) + NavGlobal[sat][0].Crs * sin(2.0 * o_fj);
		  // Inclination
			  ij = NavGlobal[sat][0].Io + NavGlobal[sat][0].IDOT * tj + NavGlobal[sat][0].Cic * cos(2.0 * o_fj) + NavGlobal[sat][0].CIS * sin(2.0 * o_fj);
		  // Longitude for ascending node
			  Omega = NavGlobal[sat][0].OMEGA + (NavGlobal[sat][0].Omega_dot - rot_rate) * tj - rot_rate * NavGlobal[sat][0].TOE;

			  //Rotation matrix
			  mRotation[0][0] = cos(Omega);
			  mRotation[0][1] = -cos(ij) * sin(Omega);
			  mRotation[1][0] = sin(Omega);
			  mRotation[1][1] = cos(ij) * cos(Omega);
			  mRotation[2][0] = 0;
			  mRotation[2][1] = sin(ij);

		//Satellite position in ECEF in meters, before earth rotation

	      sat_pos.X = mRotation[0][0] * cos(wj) * rj + mRotation[0][1] * sin(wj) * rj;
		  sat_pos.Y = mRotation[1][0] * cos(wj) * rj + mRotation[1][1] * sin(wj) * rj;
		  sat_pos.Z = mRotation[2][0] * cos(wj) * rj + mRotation[2][1] * sin(wj) * rj;


		// Satellite clock correction

			  dt = transmit_time - NavGlobal[sat][0].gpsTime;
		// Format the time
			  if (dt > 302400.0)
			  {
				  dt = dt - 604800.0;
			  }

		      else if(dt < -302400.0)
			  {
				  dt = dt + 604800.0;
			  }

		// Relativistic correction
			  rel = (-4.442807633e-10) * NavGlobal[sat][0].Eccentricity * NavGlobal[sat][0].Sqrt_a * sin(Ej);

		// Satellite clock correction
			  *sat_clk_corr = NavGlobal[sat][0].clockBias + NavGlobal[sat][0].clockDrift * dt + NavGlobal[sat][0].clockDriftRate * dt * dt + rel;

		// Group delay
			  *group_delay = NavGlobal[sat][0].TGD;

			  (SatPos)->push_back(sat_pos);
	
}