/**
 * author: stephanmg
 * date: 04m07d12y
 * file: mVec.h
 */

#ifndef _MVEC_H_
#define _MVEC_H_
#include <vector>
#include <cstddef>
#include <cmath>
#include <numeric> // needed for std::inner_product
#include "common_typedefs.h"

// TODO: *) validate lin interpolate (with boost unit tests)
// TODO: *) implement bilin interp:  mathenexus.zum.de/html/geometrie/abstaende/AbstandPE_Hilfsger_Paraform.htm
// TODO  *) refactor code interp_linear in vm2ug.h!
template <class T = double, size_t i = 3> class mvec : public std::vector<T> {

		public:
			// constructors
			mvec();

			mvec(const std::vector<T>& init);

			// default destructor
			~mvec();

			// norm
			const double norm(NORM) const;

			// operators
			inline mvec<T, i> operator+(const mvec<T, i>& rhs) const { return this->add(rhs); }

			inline mvec<T, i> operator-(const mvec<T, i>& rhs) const { return this->sub(rhs); }

			inline const double operator*(const mvec<T, i>& rhs) const { return this->dot(rhs); }

			inline mvec<T, i> operator%(const mvec<T, i>& rhs) const { return this->vec(rhs); }

		    inline mvec<T, i> operator-() const { return this->neg(); }

		    inline mvec<T, i> operator+() const { return this->id(); }

		    inline mvec<T, i> operator=(const mvec<T, i>& rhs);

	        inline mvec<T, i>& operator+=(const mvec<T, i>& rhs);

	        inline mvec<T, i>& operator-=(const mvec<T, i>& rhs);

	        inline mvec<T, i>& operator%=(const mvec<T, i>& rhs);

		private:
			// add
			mvec<T, i> add(const mvec<T, i>& rhs) const;

			// sub
			mvec<T, i> sub(const mvec<T, i>& rhs) const;

			// dot product
			inline const double dot(const mvec<T, i>& rhs) const;

			// cross product
			mvec<T, i> vec(const mvec<T, i>& rhs) const;

			// negate
			mvec<T, i> neg() const;

			// identity
			mvec<T, i> id() const;
};

#include "mvec_impl.h"

#endif /* _MVEC_H_ */


