#include "pch.h"
#include "fnc.h"

double Norm(double X, double Y, double Z)
{
	double out;

	out = sqrt(pow(X, 2.0) + pow(Y, 2.0) + pow(Z, 2.0));


	return out;
}

void VecMult(vector<vector<double>> &vec, vector<vector<double>> &Matr1, vector<vector<double>> &Matr2)
{
	//Number of columns
	int num_col1 = Matr1[0].size();
	int num_col2 = Matr2[0].size();

	// Number of rows
	int num_row1 = Matr1.size();
	int num_row2 = Matr2.size();

	vec.clear();
	vec.resize(num_row1, vector<double>(num_col2, 0.0));

	if (num_col1 == num_row2)
	{
		//// Initializing a single row
		//vector<double> row(num_col2, 0.0);

		//// Initializing the 2-D vector
		//vector<vector<double>> v(num_row1, row);

		for (int i = 0; i < num_row1; i++)
		{
			for (int j = 0; j < num_col2; j++)
			{
				for (int k = 0; k < num_col1; k++)
				{
					vec[i][j] += Matr1[i][k] *  Matr2[k][j];
				}
			}
		}
	}

	else
	{
		printf("Vectors can't be multiplied");
	}
}

void Inverse(vector<vector<double>>& out, vector<vector<double>>& in1)
{
	double determ = 0.0;
	determ = determinant(in1);

	adjoint4(out, in1);

	for (unsigned int i = 0; i < 4; i++)
	{
		for (unsigned int j = 0; j < 4; j++)
		{
			out[i][j] = out[i][j] / determ;
		}
	}
}

double determinant(vector<vector<double>>& vec)
{
	double a, b, c, d, det = 0.0, int1 = 0.0, int2 = 0.0, int3[4][3];
	int y = 0;

	//Number of columns
	int num_col1 = vec[0].size();

	// Number of rows
	int num_row1 = vec.size();

	vector<vector<double>> vecA[4];
	vector<vector<double>> vecB[4][3];

	for (int z = 0; z < 4; z++)
	{
		Matr_decomp(vecA[z], vec, y, z);

		for (int z1 = 0; z1 < 3; z1++)
		{
			Matr_decomp(vecB[z][z1], vecA[z], y, z1);
		}
	}

	for (unsigned f = 0; f < 4; f++)
	{
		vector<int> f2;

		for (int r1 = 0; r1 < 4; r1++)
		{
			if (r1 != f)
			{
				f2.push_back(r1);
			}
		}

		for (unsigned int f1 = 0; f1 < 3; f1++)
		{
			int3[f][f1] = vec[0][f] * Sign(0, f) * vec[1][f2[f1]] * Sign(0, f1) * (vecB[f][f1][0][0] * vecB[f][f1][1][1] - vecB[f][f1][0][1] * vecB[f][f1][1][0]);
			det += int3[f][f1];
		}

		f2.clear();
	}


	return det;
}

double Sign(int a, int b)
{
	int c = (a + b) % 2;
	double d = 0;

	if (c == 0)
	{
		d = 1.0;
	}

	else
	{
		d = -1.0;
	}

	return d;
}

void Matr_decomp(vector<vector<double>>& vecA, vector<vector<double>>& vecB, int y, int z)
{

	//Number of columns
	int num_col1 = vecB[0].size();

	// Number of rows
	int num_row1 = vecB.size();

	//
	vector<int>a1;
	vector<int>a2;


	for (int i = 0; i < vecB.size(); i++)
	{
		if (i != z)
		{
			a1.push_back(i);

		}
	}

	for (int i = 0; i < vecB.size(); i++)
	{
		if (i != y)
		{
			a2.push_back(i);

		}
	}


	vecA.resize((num_col1 - 1), vector<double>((num_row1 - 1), 0.0));

	for (unsigned int i = 0; i < (num_col1 - 1); i++)
	{
		for (unsigned int j = 0; j < (num_col1 - 1); j++)
		{
			vecA[i][j] = vecB[a2[i]][a1[j]];
		}
	}
}

// takes transpose of input vecB and outputs vecA
void TransMat(vector<vector<double>>& vecA, vector<vector<double>>& vecB)
{
	//Number of columns
	int num_col2 = vecB[0].size();

	// Number of rows
	int num_row2 = vecB.size();

	vecA.resize(num_col2, vector<double>(num_row2, 0.0));

	for (int j = 0; j < num_row2; j++)
	{
		for (int k = 0; k < num_col2; k++)
		{
			vecA[k][j] = vecB[j][k];
		}
	}

}

// adjoint of 4 by 4 matrix
void adjoint4(vector<vector<double>>& out, vector<vector<double>>& in)
{
	double a, b, c, d, det = 0.0, int1 = 0.0, int2 = 0.0, int3[4][3], int4[4] = { 0,0,0,0 };

	vector<vector<double>>out1;
	//TransMat(in, in1);

	//Number of columns
	int num_col1 = in[0].size();

	// Number of rows
	int num_row1 = in.size();

	out1.resize(4, vector<double>(4, 0.0));

	vector<vector<double>> vecA[4][4];
	vector<vector<double>> vecB[4][4][3];

	for (unsigned k = 0; k < 4; k++)
	{
		for (int z = 0; z < 4; z++)
		{
			Matr_decomp(vecA[k][z], in, k, z);

			for (int z1 = 0; z1 < 3; z1++)
			{
				Matr_decomp(vecB[k][z][z1], vecA[k][z], 0, z1);
			}
		}
	}

	vector<int>f3;

	for (unsigned int k = 0; k < 4; k++)
	{

		for (int r1 = 0; r1 < 4; r1++)
		{
			if (r1 != k)
			{
				f3.push_back(r1);
			}
		}

		for (unsigned f = 0; f < 4; f++)
		{
			vector<int> f2;

			for (int r1 = 0; r1 < 4; r1++)
			{
				if (r1 != f)
				{
					f2.push_back(r1);
				}
			}

			for (unsigned int f1 = 0; f1 < 3; f1++)
			{
				int3[f][f1] = Sign(k, f) * in[f3[0]][f2[f1]] * Sign(0, f1) * (vecB[k][f][f1][0][0] * vecB[k][f][f1][1][1] - vecB[k][f][f1][0][1] * vecB[k][f][f1][1][0]);
				int4[f] += int3[f][f1];

			}

			out1[k][f] = int4[f];
			int4[f] = 0;



			f2.clear();
		}

		f3.clear();
	}
	TransMat(out, out1);
}




