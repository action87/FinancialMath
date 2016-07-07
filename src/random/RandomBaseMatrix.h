/*
 * RandomBaseMatrix.h
 *
 *  Created on: 2016. júl. 2.
 *      Author: Gabor
 */

#ifndef SRC_RANDOM_RANDOMBASEMATRIX_H_
#define SRC_RANDOM_RANDOMBASEMATRIX_H_

#include <boost/numeric/ublas/matrix.hpp>

class RandomBaseMatrix{
public:
	RandomBaseMatrix(unsigned long Size, unsigned long Dimensionality);

	inline unsigned long GetDimensionality() const;
	inline unsigned long GetSize() const;

	virtual RandomBaseMatrix* clone() const=0;
	virtual void GetUniforms(boost::numeric::ublas::matrix<double>& variates)=0;
	virtual void Skip(unsigned long NumberOfPaths)=0;
	virtual void SetSeed(unsigned long Seed)=0;
	virtual void Reset()=0;

	virtual void GetGaussians(boost::numeric::ublas::matrix<double>& variates);
	virtual void ResetDimensionality(unsigned long NewDimensionality);
	virtual void ResetSize(unsigned long NewSize);

	virtual ~RandomBaseMatrix(){}

private:
	unsigned long Dimensionality;
	unsigned long Size;

};

unsigned long RandomBaseMatrix::GetDimensionality() const{
    return Dimensionality;
}

unsigned long RandomBaseMatrix::GetSize() const{
    return Size;
}


#endif /* SRC_RANDOM_RANDOMBASEMATRIX_H_ */
