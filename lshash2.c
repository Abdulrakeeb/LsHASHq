/*
* This is the implementation of LsHASH2 algorithm by Abdulrakeeb Al-Ssulami
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
	int j, i, q, t, r, l, delta, k, sh, mMinus1, mMinus2, H[65536];
	bool B[65536];
	q=2; t=2;l=65536;
	uint16_t Si, Sir, Sj;
	int Hash = 0;
	int Mask = 3;
	int Prefix_Hash[1];
	if (m < q) return -1;
	mMinus1 = m - 1;
	mMinus2 = m - 2;
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
		Mask = 3; delta = q-1;
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
		Sj = (x[j - 1] << t) ^ x[j];
		H[Sj] = mMinus1 - j;
		B[Sj] = true;
	}
	Sj = (x[j - 1] << t) ^ x[j];
	B[Sj] = true;
	END_PREPROCESSING
	/*Searching Phase--------------*/
	BEGIN_SEARCHING    
	sh = 2*mMinus1;
	r = m - q + 1;
	i = mMinus1;
	memcpy(y+n, x, m);
	while (i < n)
	{
		Si = (y[i - 1] << t) ^ y[i];
		Sir = (y[i + mMinus2] << t) ^ y[i + mMinus1];
		while (!(B[Si] || B[Sir]))
		{
			i = i + sh;
			Si = (y[i - 1] << t) ^ y[i];
			Sir = (y[i + mMinus2] << t) ^ y[i + mMinus1];
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