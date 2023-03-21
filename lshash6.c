/*
* This is the implementation of LsHASH6 algorithm by Abdulrakeeb Al-Ssulami
* Copyright(C) 2022 Abdulrakeeb Al-Ssulami
* Citaion:
* Abdulrakeeb M. Al-Ssulami, Aqil M. Azmi, Hassan Mathkour, and Hatim Aboalsamh.
* LsHASHq: A string matching algorithm exploiting longer q-gram shifting
* Information Processing and Management, 59(2022):103057.
*/
#include "include/define.h"
#include "include/main.h"
//************************************************************************//
int search(unsigned char *x, int m, unsigned char *y, int n)
{
	int j, i, q, t, r, k, l, delta, sh, H[65536];
	bool B[65536];
	q=6; t=2; l=65536;
	uint16_t Si, Sir, Sj;
	int Hash = 0;
	int Mask = 3;
	int Prefix_Hash[5];
	if (m < q) return -1;
	int mMinus1 = m - 1;
	int mMinus2 = m - 2;
	int mMinus3 = m - 3;
	int mMinus4 = m - 4;
	int mMinus5 = m - 5;
	int mMinus6 = m - 6;
	int mMinus7 = m - 7;
	int mMinus8 = m - 8;
	int mMinus9 = m - 9;
	int mMinus10 = m - 10;
	int count = 0;
	/*Preprocessing phase-----------*/
	BEGIN_PREPROCESSING
	for (k = 0; k < q-1; k++)
		Prefix_Hash[k] = 0;
	for (k = 0; k < q-1; k++)
	{
		Hash = (Hash << t) ^ x[k];
		Prefix_Hash[k] = Hash & Mask;
		Mask = (Mask << t) | Mask;
	}
	for (j = 0; j < l; j++)
	{
		Mask = 1023; delta = q-1;
		while ((delta > 0) && (Prefix_Hash[delta-1] != (j & Mask)))
		{
			Mask = Mask >> t;
			delta--;
		}
		H[j] = m - delta;
		B[j] = false;
	}
	for (j = q-1; j < mMinus1; ++j)
	{
		Sj = (((((((((x[j - 5] << t) ^ x[j - 4]) << t) ^ x[j - 3]) << t) ^ x[j - 2]) << t) ^ x[j-1]) << t) ^ x[j];
		H[Sj] = mMinus1 - j;
		B[Sj] = true;
	}
	Sj = (((((((((x[j - 5] << t) ^ x[j - 4]) << t) ^ x[j - 3]) << t) ^ x[j - 2]) << t) ^ x[j-1]) << t) ^ x[j];
	B[Sj] = true;
	END_PREPROCESSING
	/*Searching Phase--------------*/
	BEGIN_SEARCHING    
	sh = 2*mMinus5;
	r = m - q + 1;
	i = mMinus1;
	memcpy(y+n, x, m);
	while (i < n)
	{
		Si = (((((((((y[i - 5] << t) ^ y[i - 4]) << t) ^ y[i - 3]) << t) ^ y[i-2]) << t) ^ y[i-1]) << t) ^ y[i];
		Sir = (((((((((y[i + mMinus10] << t) ^ y[i + mMinus9]) << t) ^ y[i + mMinus8]) << t) ^ y[i + mMinus7]) << t) ^ y[i + mMinus6]) << t) ^ y[i + mMinus5];
		while (!(B[Si] || B[Sir]))
		{
			i = i + sh;
			Si = (((((((((y[i - 5] << t) ^ y[i - 4]) << t) ^ y[i - 3]) << t) ^ y[i-2]) << t) ^ y[i-1]) << t) ^ y[i];
			Sir = (((((((((y[i + mMinus10] << t) ^ y[i + mMinus9]) << t) ^ y[i + mMinus8]) << t) ^ y[i + mMinus7]) << t) ^ y[i + mMinus6]) << t) ^ y[i + mMinus5];
		}
		if (B[Si])
		{
			j = 0;
			while ((j < m) && (x[j] == y[i - mMinus1 + j])) j++;
			if ((j >= m) && (i < n))
				count++;
		}
		i = i + H[Si];
	}
	END_SEARCHING
	return count;
}