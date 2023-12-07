#include "pch.h"
#include "smoothing.h"

void smoothing(vector<ObservationInfo>* observationInfoList, int smooth_interval, int totalsats)
{
	double lambda1 = 0.19029, v=0, mean;
	int total_epochs = observationInfoList[0].size();
	int first_smooth_interval;
	vector<double> vR0;

	if (smooth_interval == 0)
	{
		for (int i = 0; i < totalsats; i++)
		{
			for (int j = 0; j < total_epochs; j++)
			{
				observationInfoList[i][j].smoothedcode = observationInfoList[i][j].c1Value;
			}
		}

	}

	else
	{
		for (int i = 0; i < totalsats; i++)
		{
			for (int j = 0; j < total_epochs; j++)
			{
				first_smooth_interval = (j+1) - smooth_interval + 1;

				if (first_smooth_interval <= 0)
					first_smooth_interval = 1;

				if (observationInfoList[i][j].l1Value == 0)
				{
					first_smooth_interval = (j+1) + 1;
					observationInfoList[i][j].smoothedcode = observationInfoList[i][j].c1Value;
				}

				else
				{
					vR0.clear();

					for (int i1 = first_smooth_interval; i1 <= (j+1); i1++)
					{
						v = observationInfoList[i][i1-1].c1Value - observationInfoList[i][i1-1].l1Value* lambda1;
						vR0.push_back(v);
					}

					mean = 0;
					auto const count = static_cast<float>(vR0.size());
					for (int i2 = 0; i2 < count; i2++)
					{
						mean += vR0[i2];
					}
					mean = mean / count;

					observationInfoList[i][j].smoothedcode = mean + observationInfoList[i][j].l1Value* lambda1;

					if (fabs(observationInfoList[i][j].smoothedcode - observationInfoList[i][j].c1Value) > 5.0)
					{
						observationInfoList[i][j].smoothedcode = observationInfoList[i][j].c1Value;
						first_smooth_interval = (j+1) + 1;
					}

				}
			}
		}
		
	}

}