#include "pch.h"
#include "SeekEpheEpoch.h"
#include "Rinex2Nav.h"
//#include "globals.h"

int SeekEpheEpoch(vector<ObservationInfo>* observationInfoList, int sizeprn) {
    int totalrec = 0;
    /*const map<int, vector<Rinex2Nav::DataGPS>>* _navDataGPS;*/

    // declare iterator
    vector<Rinex2Nav::DataGPS>::iterator iter;

    // use iterator with for loop
    for (iter = NavGlobal[0].begin(); iter != NavGlobal[0].end(); ++iter) {
  
        totalrec++;
    }

    //for (const auto& prnDataPair : *_navDataGPS) {
    //    if (prnDataPair.first == satID) {
    //        totalrec = static_cast<int>(prnDataPair.second.size());
    //        break;
    //    }
    //}

    //int epoch = 0;
    //int findepoch = 0;

    //for (int i = 0; i < totalrec - 1; ++i) {
    //    double diff1 = abs(time - mEphTime[satID][i]);
    //    double diff2 = abs(time - mEphTime[satID][i + 1]);

    //    if (diff1 < diff2) {
    //        epoch = i;
    //        findepoch = 1;
    //        break;
    //    }
    //}

    //if (findepoch == 0) {
    //    if (abs(time - mEphTime[satID][totalrec - 1]) < 7200) {
    //        epoch = totalrec - 1;
    //    }
    //    else {
    //        throw runtime_error("No proper ephemeris found!!!!");
    //    }
    //}

    //return epoch;
    return 1;
}