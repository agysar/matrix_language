#pragma once

#include <iostream>
#include <stdlib.h>

//#include "rational_map.h"
#include "rational_vector.h"
//#include "random_access_iterator.h"

#define VERTICAL 201
#define HORIZONTAL 202

class RationalMatrix : public Exceptions {
	size_t rows;
	size_t cols;
	size_t real_size; // amount of non-zero rational numbers 
	size_t size;

	RationalNumber *data; // same position in data array is position in matrix, 
	size_t *x; // where x[i] and y[i] is position in matrix
	size_t *y; 

	public:

		class ProxyNumber : public RationalNumber {
		public:
			RationalMatrix *mtrx;
			size_t _x;
			size_t _y;

			ProxyNumber(RationalMatrix *a = NULL, size_t x_lol = 0, size_t y_lol = 0) 
				: mtrx(a), _x(x_lol), _y(y_lol) { }

			~ProxyNumber() { }

			operator RationalNumber() const { return (*mtrx)(_x, _y); }

			ProxyNumber operator=(const RationalNumber &a) {
				//RationalNumber tmp = (*mtrx)(_x, _y);
				ProxyNumber tmp_lol(mtrx, _x, _y);
				if (a == RationalNumber(0)) {
					size_t i = 0;
					while (i < mtrx->real_size) {
						if ((mtrx->x[i] == _x) && (mtrx->y[i] == _y)) {
							break;
						}
						++i;
					}
					for (size_t j = i + 1; j < mtrx->real_size; ++j) {
						mtrx->x[j - 1] = mtrx->x[j];
						mtrx->y[j - 1] = mtrx->y[j];
						mtrx->data[j - 1] = mtrx->data[j];
					}
					if (mtrx->real_size > 0) {
						--(mtrx->real_size);
					}
					mtrx->data = (RationalNumber*)realloc(mtrx->data, sizeof(RationalNumber) * mtrx->real_size);
					mtrx->x = (size_t*)realloc(mtrx->x, sizeof(size_t) * mtrx->real_size);
					mtrx->y = (size_t*)realloc(mtrx->y, sizeof(size_t) * mtrx->real_size);
				} else {
					//(*mtrx)(_x, _y) = a;
					//ProxyNumber prx(this, idx, idy);
					++mtrx->real_size;
					mtrx->data = (RationalNumber*)realloc(mtrx->data, sizeof(RationalNumber) * mtrx->real_size);
					mtrx->x = (size_t*)realloc(mtrx->x, sizeof(size_t) * mtrx->real_size);
					mtrx->y = (size_t*)realloc(mtrx->y, sizeof(size_t) * mtrx->real_size);
					//RationalNumber tmp(0, 1);
					mtrx->data[mtrx->real_size - 1] = a;
					mtrx->x[mtrx->real_size - 1] = _x;
					mtrx->y[mtrx->real_size - 1] = _y;
					/*prx->mtrx = *this;
					prx->_x = idx;
					prx->_y = idy;*/
					//return data[real_size - 1];
					return tmp_lol;
				}
				return tmp_lol;
			}
		};


		RationalMatrix();
		RationalMatrix(const RationalVector &, size_t); // constructor from vector
		RationalMatrix(size_t, RationalNumber); // square matrix
		RationalMatrix(size_t, size_t, RationalNumber); // non-square matrix
		RationalMatrix(const RationalMatrix &);
		RationalMatrix(const char*);
		~RationalMatrix();

		char *to_string() const;

		void write(const char *) const;

		void to_out() const;

		RationalMatrix &operator=(const RationalMatrix &a) {
			rows = a.rows;
			cols = a.cols;
			real_size = a.real_size;
			size = a.size;
			data = (RationalNumber*)realloc(data, sizeof(RationalNumber) * real_size);
			x = (size_t*)realloc(x, sizeof(size_t) * real_size);
			y = (size_t*)realloc(y, sizeof(size_t) * real_size);
			for (size_t i = 0; i < real_size; ++i) {
				data[i] = a.data[i];
				x[i] = a.x[i];
				y[i] = a.y[i];
			}			
			return *this;
		}

		ProxyNumber operator()(size_t idx, size_t idy) {
			ProxyNumber prx(this, idx, idy);
			if ((idx >= rows) || (idy >= cols)) {
				throw (Exceptions(EX_OUT_OF_RANGE, this, MATRIX));
			} else {
				for (size_t i = 0; i < real_size; ++i) {
					if ((x[i] == idx) && (y[i] == idy)) {
						//return data[i];
						return prx;
					}
				}
				++real_size;
				data = (RationalNumber*)realloc(data, sizeof(RationalNumber) * real_size);
				x = (size_t*)realloc(x, sizeof(size_t) * real_size);
				y = (size_t*)realloc(y, sizeof(size_t) * real_size);
				RationalNumber tmp(0, 1);
				data[real_size - 1] = tmp;
				x[real_size - 1] = idx;
				y[real_size - 1] = idy;
				/*prx->mtrx = *this;
				prx->_x = idx;
				prx->_y = idy;*/
				//return data[real_size - 1];
				return prx;
			}
		}

		RationalNumber operator()(size_t idx, size_t idy) const {
			if ((idx >= rows) || (idy >= cols)) {
				throw (Exceptions(EX_OUT_OF_RANGE, this, MATRIX));
			} else {
				for (size_t i = 0; i < real_size; ++i) {
					if ((x[i] == idx) && (y[i] == idy)) {
						return data[i];
					}
				}
				RationalNumber tmp(0, 1);
				return tmp;
			}
		}

		RationalMatrix operator~() const {
			RationalMatrix tmp = *this;
			tmp.rows = this->cols;
			tmp.cols = this->rows;
			for (size_t i = 0; i < tmp.real_size; ++i) {
				size_t lol;
				lol = tmp.x[i];
				tmp.x[i] = tmp.y[i];
				tmp.y[i] = lol;
			}

			return tmp;
		}

		RationalMatrix operator-(const RationalMatrix &);

		friend RationalMatrix operator+(const RationalMatrix &, const RationalMatrix &);
		friend RationalMatrix operator-(const RationalMatrix &, const RationalMatrix &);
		friend RationalMatrix operator*(const RationalMatrix &, const RationalMatrix &);
		friend RationalMatrix operator^(const RationalMatrix &, size_t);

		friend class MatrixCoords;
		friend class MatrixRowCoords;
		friend class MatrixColCoords;
		friend class RandomAccessIterator;
};

class MatrixCoords : public RationalNumber {
	RationalMatrix *mtrx;

public:
	MatrixCoords() : mtrx(NULL) { }
	//MatrixCoords(const RationalMatrix &a) : mtrx(&a) { } 
	MatrixCoords(RationalMatrix &a) : mtrx(&a) { } 
	~MatrixCoords() { }

	RationalNumber operator()(size_t idx, size_t idy) const {
		if (mtrx == NULL) {
			throw (Exceptions(EX_PTR_IS_NULL, mtrx, MATRIX));
		}
		if ((idx >= mtrx->rows) || (idy >= mtrx->cols)) {
			throw (Exceptions(EX_OUT_OF_RANGE, mtrx, MATRIX));
		} else {
			for (size_t i = 0; i < mtrx->real_size; ++i) {
				if ((mtrx->x[i] == idx) && (mtrx->y[i] == idy)) {
					return mtrx->data[i];
				}
			}
			RationalNumber tmp(0, 1);
			return tmp;
		}
	}
};

class MatrixRowCoords : public RationalVector {
	RationalMatrix *mtrx;

public:
	MatrixRowCoords() : mtrx(NULL) { }
	//MatrixRowCoords(const RationalMatrix &a) : mtrx(&a) { }	
	MatrixRowCoords(RationalMatrix &a) : mtrx(&a) { }	
	~MatrixRowCoords() { }

	RationalVector operator[](size_t n) const{
		if (mtrx == NULL) {
			throw (Exceptions(EX_PTR_IS_NULL, mtrx, MATRIX));
		}

		RationalVector tmp(mtrx->cols, RationalNumber(0, 1));
		for (size_t i = 0; i < mtrx->cols; ++i) {
			tmp(i) = (*mtrx)(n, i);
		}

		return tmp;
	}

};

class MatrixColCoords : public RationalVector {
	RationalMatrix *mtrx;

public:
	MatrixColCoords() : mtrx(NULL) { }
	//MatrixColCoords(const RationalMatrix &a) : mtrx(&a) { }	
	MatrixColCoords(RationalMatrix &a) : mtrx(&a) { }	
	~MatrixColCoords() { }

	RationalVector operator[](size_t m) const{
		if (mtrx == NULL) {
			throw (Exceptions(EX_PTR_IS_NULL, mtrx, MATRIX));
		}

		RationalVector tmp(mtrx->rows, RationalNumber(0, 1));
		for (size_t i = 0; i < mtrx->rows; ++i) {
			tmp(i) = (*mtrx)(m, i);
		}

		return tmp;
	}


};