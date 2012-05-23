/*
 * unit_test_helper.h
 *
 *  Created on: Apr 27, 2012
 *      Author: stephan grein
 */

#ifndef _UNIT_TEST_HELPER_H_
#define _UNIT_TEST_HELPER_H_

#include <limits>
#include <cmath>

namespace ug {
namespace membrane_potential_mapping {

static const double SMALL = 0.0001;
static const double VERY_SMALL = 0.0000001;

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	#include <functional>
	  template <class T> function<bool(T)> isInRange(T low, T high) {
      return [low,high](T value) { return std::fabs(value - low) >= std::numeric_limits<T>::epsilon() \
                                       && std::fabs(value - high) <= std::numeric_limits<T>::epsilon(); }; }
#endif

const bool SameDoubles(const double& a, const double& b) {
   return std::fabs(a - b) < std::numeric_limits<double>::epsilon();
}

}
}
#endif /* _UNIT_TEST_HELPER_H_ */
