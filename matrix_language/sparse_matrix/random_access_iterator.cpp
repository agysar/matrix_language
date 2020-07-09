#include "random_access_iterator.h"

RandomAccessIterator :: RandomAccessIterator(RationalVector &vector_, RationalMatrix &matrix_, int row, int col) 
	: Exceptions(0, NULL, 0), vctr(vector_), mtrx(matrix_), r(row), c(col) { }

RandomAccessIterator :: ~RandomAccessIterator() { }

void RandomAccessIterator :: sync_to() {
	RationalNumber tmp(0, 1);
	if (r * c > 0) {
		throw(Exceptions(EX_UNKNOWN, this, ITERATOR));
	}
	if (r == -1) { // vertical vector
		//size_t j = 0;
		vctr.size = mtrx.rows;
		//vctr.real_size = 0;
		//vctr->data = (RationalMap*)realloc(vctr->data, sizeof(RationalMap) * mtrx.rows);
		for (size_t i = 0; i < mtrx.rows; ++i) {
			if ((vctr[i] != tmp) || (mtrx(i, c) != tmp)) {
				vctr(i) = mtrx(i, c);
				//++vctr.real_size;
			//	++j;
			}
		}
		//vctr.real_size = j;
	} else { // horizontal vector
		//size_t j = 0;
		vctr.size = mtrx.cols;
		//vctr.real_size = 0;
		//vctr->data = (RationalMap*)realloc(vctr->data, sizeof(RationalMap) * mtrx.cols);
		for (size_t i = 0; i < mtrx.cols; ++i) {
			if ((mtrx(r, i) != tmp) || (vctr[i] != tmp)) {
				vctr(i) = mtrx(r, i);
				//++vctr.real_size;
			//	++j;
			}
		}
		//vctr.real_size = j;
	}
}

void RandomAccessIterator :: sync_from() {
	RationalNumber tmp(0, 1);
	if (r * c > 0) {
		throw(Exceptions(EX_UNKNOWN, this, ITERATOR));
	}

	if (r == -1) { // vertical vector
		if (mtrx.rows != vctr.size) {
			throw(Exceptions(EX_ITERATOR_SIZE_IS_NOT_EQUAL, this, ITERATOR));
		}
		//size_t j = 0;
		for (size_t i = 0; i < mtrx.rows; ++i) {
			if ((vctr[i] != tmp) || (mtrx(i, c) != tmp)) {
				mtrx(i, c) = vctr[i]; 
			}
		}
	} else { // horizontal vector
		if (mtrx.cols != vctr.size) {
			throw(Exceptions(EX_ITERATOR_SIZE_IS_NOT_EQUAL, this, ITERATOR));
		}

		for (size_t i = 0; i < mtrx.cols; ++i) {
			if ((vctr[i] != tmp) || (mtrx(r, i) != tmp)) {
				mtrx(r, i) = vctr[i]; 
			}
		}
	}
}
