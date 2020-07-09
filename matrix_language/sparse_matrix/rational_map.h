#pragma once

#include "rational_number.h"

class RationalMap : public Exceptions {

	public:
		RationalNumber number;
		size_t position;

		RationalMap();
		RationalMap(const char *);
		RationalMap(const RationalMap &a);
		~RationalMap();

		RationalMap &operator=(const RationalMap &a) {
			number = a.number;
			position = a.position;
			return *this;
		}

		friend RationalMap operator+(const RationalMap &, const RationalMap &);
		friend RationalMap operator-(const RationalMap &, const RationalMap &);
		friend RationalMap operator*(const RationalMap &, const RationalMap &);
		friend RationalMap operator/(const RationalMap &, const RationalMap &);

		friend RationalMap &operator+=(RationalMap &, const RationalMap &);
		friend RationalMap &operator-=(RationalMap &, const RationalMap &);
		friend RationalMap &operator*=(RationalMap &, const RationalMap &);
		friend RationalMap &operator/=(RationalMap &, const RationalMap &);

};	
