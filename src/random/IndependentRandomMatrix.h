/*
 * IndependentRandomMatrix.h
 *
 *  Created on: 2016. júl. 3.
 *      Author: Gabor
 */

#ifndef SRC_RANDOM_INDEPENDENTRANDOMMATRIX_H_
#define SRC_RANDOM_INDEPENDENTRANDOMMATRIX_H_

#include "RandomBaseMatrix.h"
#include "../utils/Wrapper.h"
#include "Random.h"

class IndependentRandomMatrix : public RandomBaseMatrix{

public:
	IndependentRandomMatrix(unsigned long Size, const Wrapper<RandomBase>& innerGenerator);

	virtual IndependentRandomMatrix* clone() const;
	virtual void GetUniforms(boost::numeric::ublas::matrix<double>& variates);
	virtual void Skip(unsigned long NumberOfPaths);
	virtual void SetSeed(unsigned long Seed);
	virtual void Reset();

private:
	Wrapper<RandomBase> InnerGenerator;
};



#endif /* SRC_RANDOM_INDEPENDENTRANDOMMATRIX_H_ */
