#include "rational_matrix.h"

class RandomAccessIterator : public Exceptions {
	RationalVector &vctr;
	RationalMatrix &mtrx;

	long int r; // -1 - not row
	long int c; // -1 - not col

public:
	//RandomAccessIterator();
	RandomAccessIterator(RationalVector &, RationalMatrix &, int, int);
	~RandomAccessIterator();

	void sync_to();
	void sync_from();
};