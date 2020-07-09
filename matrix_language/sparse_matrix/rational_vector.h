#pragma once

#include <iostream>
#include <cstdlib>

#include "rational_map.h"
//#include "random_access_iterator.h"


class RationalVector : public Exceptions {
	public:
		RationalMap *data;
		size_t size; // size with zero elements
		size_t real_size; // size without zero elements
		RationalVector();
		RationalVector(const char *);
		RationalVector(const RationalVector &);
		RationalVector(size_t, RationalNumber);
		~RationalVector();

		void write(const char *) const;


		RationalVector &operator=(const RationalVector &a) {
			data = (RationalMap*)realloc(data, sizeof(RationalMap) * a.real_size);
			for (size_t i = 0; i < a.real_size; ++i) {
				data[i] = a.data[i];
			}
			size = a.size;
			real_size = a.real_size;
			return *this;
		}

		char *to_string() const;

		void to_out() const;

		friend RationalVector operator-(const RationalVector &);
		friend RationalVector operator-(const RationalVector &, const RationalVector &);
		friend RationalVector operator+(const RationalVector &, const RationalVector &);
		friend RationalVector operator*(const RationalVector &, const RationalNumber &);
		friend RationalVector operator/(const RationalVector &, const RationalNumber &);
		friend RationalVector operator+(const RationalVector &, const RationalNumber &);
		friend RationalVector operator-(const RationalVector &, const RationalNumber &);

		friend RationalNumber operator*(const RationalVector &, const RationalVector &);



		RationalNumber operator[](size_t idx) const {
			if (idx >= size) {
				//exception
				throw (Exceptions(EX_OUT_OF_RANGE, this, VECTOR));
			} else {
				for (size_t i = 0; i < real_size; ++i) {
					if (data[i].position == idx) {
						return data[i].number;
					}
				}
				RationalNumber tmp(0, 1);
				return tmp;
			}

		}

		RationalNumber &operator()(size_t idx) {
			if (idx >= size) {
				throw (Exceptions(EX_OUT_OF_RANGE, this, VECTOR));
			} else {
				for (size_t i = 0; i < real_size; ++i) {
					if (data[i].position == idx) {
						return data[i].number;
					}
				}
				++real_size;
				data = (RationalMap*)realloc(data, sizeof(RationalMap) * real_size);
				RationalNumber tmp(0, 1);
				data[real_size - 1].number = tmp;
				data[real_size - 1].position = idx;
				return data[real_size - 1].number;
			}
		}

	    friend std :: ostream& operator<<(std :: ostream &strm, const RationalVector &a);
	    friend class RandomAccessIterator;
};
