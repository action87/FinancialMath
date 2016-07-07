/*
 * main.cpp
 *
 *  Created on: 2016. jún. 26.
 *      Author: Gabor
 */

#include "../random/AntiThehetic.h"
#include "../random/ParkMiller.h"
#include "../random/ParkMillerWithShuffling.h"
#include "../utils/Arrays.h"
#include "../random/IndependentRandomMatrix.h"
#include <iostream>

using namespace std;
using namespace boost::numeric::ublas;


void testingRandom();

int main(){

	testingRandom();

    return 0;
}

void testingRandom(){
	unsigned long NumberOfPaths = 10;
	RandomParkMiller generator(5);
	AntiThetic GenTwo(generator);
	IndependentRandomMatrix GenMatrix(2, GenTwo);

	matrix<double> Variates(2,5);
	cout<< "size_1 = " << Variates.size1()<< endl;
	cout<< "size_2 = " << Variates.size2()<< endl;

	cout << "GenMatrix.GetDimensionality() = " << GenMatrix.GetDimensionality() << endl;
	cout << "GenMatrix.GetSize() = " << GenMatrix.GetSize() << endl;

	for (unsigned long i=0; i < NumberOfPaths; i++){
		GenMatrix.GetGaussians(Variates);
		cout<< "======== Path " << i << " =========="<< endl;
		for(unsigned long j=0; j<Variates.size1();j++ ){
			for(unsigned long k=0; k<Variates.size2();k++)
			cout << "(" << j << ", " << k<<") = " << Variates(j,k)<< endl;
		}
	}


	GenMatrix.ResetDimensionality(10);
	GenMatrix.ResetSize(10);
	cout << "GenMatrix.GetDimensionality() = " << GenMatrix.GetDimensionality() << endl;
	cout << "GenMatrix.GetSize() = " << GenMatrix.GetSize() << endl;

	GenMatrix.ResetDimensionality(5);
	GenMatrix.ResetSize(2);
	GenMatrix.Skip(2);
	for (unsigned long i=0; i < NumberOfPaths; i++){
		GenMatrix.GetGaussians(Variates);
		cout<< "======== Path " << i << " =========="<< endl;
		for(unsigned long j=0; j<Variates.size1();j++ ){
			for(unsigned long k=0; k<Variates.size2();k++)
			cout << "(" << j << ", " << k<<") = " << Variates(j,k)<< endl;
		}
	}

	GenMatrix.SetSeed(1000);
	GenMatrix.Reset();



}
