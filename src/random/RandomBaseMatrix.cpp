/*
 * RandomBaseMatrix.cpp
 *
 *  Created on: 2016. júl. 2.
 *      Author: Gabor
 */

#include "Normals.h"
#include <cstdlib>
#include <boost/numeric/ublas/matrix.hpp>
#include "RandomBaseMatrix.h"

// the basic math functions should be in
// namespace std but aren’t in VCPP6
#if !defined(_MSC_VER)
using namespace std;
#endif

using namespace boost::numeric::ublas;


RandomBaseMatrix::RandomBaseMatrix(unsigned long Size_, unsigned long Dimensionality_):
		Dimensionality(Dimensionality_),Size(Size_)
{
}



void RandomBaseMatrix::ResetDimensionality(unsigned long NewDimensionality){
    Dimensionality=NewDimensionality;
}

void RandomBaseMatrix::ResetSize(unsigned long NewSize){
    Size=NewSize;
}


void RandomBaseMatrix::GetGaussians(matrix<double>& variates){

    GetUniforms(variates);

    for(unsigned long i=0;i<Size;i++){
    	for(unsigned long j=0;j<Dimensionality; j++){
    	        double x=variates(i,j);
    	        variates(i,j) = InverseCumulativeNormal(x);
    	    }
    }

}
