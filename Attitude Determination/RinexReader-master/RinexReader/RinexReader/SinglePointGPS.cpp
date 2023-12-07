#include "pch.h"
#include "SinglePointGPS.h"
#include "math.h"
#include <numeric>



Cart SinglePointGPS(vector<ObservationInfo> *observationInfoList, vector<Cart>SatXYZ, vector<unsigned int>SatsToIncl, Cart InitPos, int epoch, double *receiver_clock)
{
    int iteration = 0;
    double clock_err_meter, vRou0[MAXSATs];// vL[MAXSATs], A[MAXSATs][4];
    vector<vector<double>>vL(SatsToIncl.size(), vector<double>(1, 0.0));
    vector<vector<double>> A(SatsToIncl.size(), vector<double>(4, 0.0));
    Cart Pos, diff;
    vector<vector<double>> Abar;
    vector<vector<double>> res1;
    vector<vector<double>> res2;
    vector<vector<double>> res3;
    vector<vector<double>>vDeltaXYZt;

    // Initialization
        Pos = InitPos;
        clock_err_meter = 0;

    // Start the adjsutment
        while (iteration < 10)
        {
            for (unsigned int satid = 0; satid < SatsToIncl.size(); satid++)
            {
                //Construct the matrix A and L
                diff.X = SatXYZ[SatsToIncl[satid]].X - Pos.X;
                diff.Y = SatXYZ[SatsToIncl[satid]].Y - Pos.Y;
                diff.Z = SatXYZ[SatsToIncl[satid]].Z - Pos.Z;

                vRou0[satid] = Norm(diff.X, diff.Y, diff.Z);
                vL[satid][0] = observationInfoList[SatsToIncl[satid]][epoch].corrected_smoothedcode - vRou0[satid] - clock_err_meter;

                    A[satid][0] = -1 *(SatXYZ[SatsToIncl[satid]].X - Pos.X) / vRou0[satid];
                    A[satid][1] = -1 *(SatXYZ[SatsToIncl[satid]].Y - Pos.Y) / vRou0[satid];
                    A[satid][2] = -1 *(SatXYZ[SatsToIncl[satid]].Z - Pos.Z) / vRou0[satid];
                

                    A[satid][3] = 1.0;
            }

                // Get the update  vDeltaXYZt = inv(A'*A)*A' * vL;
                TransMat(Abar, A);
                VecMult(res1, Abar, A);
                VecMult(res2, Abar, vL);

                Inverse(res3, res1);
                VecMult(vDeltaXYZt, res3, res2);
               

            // Exit of the adjustment
            if (Norm(vDeltaXYZt[0][0], vDeltaXYZt[1][0], vDeltaXYZt[2][0]) < 1.0e-7)
            {
                break;
            }
            

                // Adjustment
                Pos.X = Pos.X + vDeltaXYZt[0][0];
                Pos.Y = Pos.Y + vDeltaXYZt[1][0];
                Pos.Z = Pos.Z + vDeltaXYZt[2][0];
                clock_err_meter = clock_err_meter + vDeltaXYZt[3][0];
            iteration = iteration + 1;
        }

        *receiver_clock = clock_err_meter / sol;  // Convert from meter to second

        return Pos;
}