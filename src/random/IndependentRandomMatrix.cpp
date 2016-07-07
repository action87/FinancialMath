/*
 * IndependentRandomMatrix.cpp
 *
 *  Created on: 2016. júl. 3.
 *      Author: Gabor
 */

#include "IndependentRandomMatrix.h"
#include "Random.h"
#include <boost/numeric/ublas/matrix.hpp>
#include "../utils/Arrays.h"

// the basic math functions should be in
// namespace std but aren’t in VCPP6
#if !defined(_MSC_VER)
using namespace std;
#endif

using namespace boost::numeric::ublas;

IndependentRandomMatrix::IndependentRandomMatrix(unsigned long Size, const Wrapper<RandomBase>& innerGenerator):
	RandomBaseMatrix(Size, innerGenerator->GetDimensionality()),InnerGenerator(innerGenerator)
{
}

IndependentRandomMatrix* IndependentRandomMatrix::clone() const{
	return new IndependentRandomMatrix(*this);
}

void IndependentRandomMatrix::GetUniforms(matrix<double>& variates){

	for(unsigned long i=0;i<GetSize();i++){
		MJArray innnervariates(GetDimensionality());
		InnerGenerator->GetUniforms(innnervariates);
		for(unsigned long j=0;j<GetDimensionality();j++){
			variates(i,j) = innnervariates[j];
		}
	}
}


void IndependentRandomMatrix::Skip(unsigned long numberOfPaths){
	MJArray tmp(InnerGenerator->GetDimensionality());

	for(unsigned long i=0;i<GetSize();i++){
		for(unsigned long j=0;j<numberOfPaths;j++){
			InnerGenerator->GetUniforms(tmp);
		}
	}

}

void IndependentRandomMatrix::SetSeed(unsigned long Seed){
	InnerGenerator->SetSeed(Seed);
}

void IndependentRandomMatrix::Reset(){
	InnerGenerator->Reset();
}
