#include <iostream>
#include <iomanip>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>

#include "rational_number.h"
#include "exceptions.h"

RationalNumber :: RationalNumber() : Exceptions(0, NULL, 0) {
    numerator = 0;
    denominator = 1;
    sgn = 0;
}

RationalNumber :: ~RationalNumber() { }

RationalNumber :: RationalNumber(uint32_t a, uint32_t b) : Exceptions(0, NULL, 0) {
    numerator = std :: abs(a);
    denominator = b;
    sgn = (a * b >= 0) ? 0 : 1;
    // exception
    if (!b) {
    	sgn = -1;
    	throw Exceptions(EX_DIVIDE_BY_ZERO, this, NUMBER);
    }
}

RationalNumber :: RationalNumber(int a) : Exceptions(0, NULL, 0) {
	//std :: cout << "kappa" << std :: endl;
	numerator = abs(a);
	denominator = 1;
	sgn = (a >= 0) ? 0 : 1;
}

RationalNumber :: RationalNumber(char *a, char *b) : Exceptions(0, NULL, 0) {
	uint32_t p, q;
	p = strtoul(a, NULL, 0);
	q = strtoul(b, NULL, 0);

    sgn = (p * q >= 0) ? 0 : 1;

    // exception
	if (!q) {
		sgn = -1;
		throw Exceptions(EX_DIVIDE_BY_ZERO, this, NUMBER);
	}
	numerator = p;
	denominator = q;
}

RationalNumber :: RationalNumber(char *a) : Exceptions(0, NULL, 0) {
	uint32_t p, q;
	size_t i = 0;
	char *tmp;
	sgn = 0;
	tmp = strstr(a, "/");
	if (tmp == NULL) {
		denominator = 1;
		if (a[i] == '-') {
			sgn = 1;
			++i;
		} else {
			sgn = 0;
		}
		numerator = strtoul(a, NULL, 0);

	} else {
		q = strtoul(tmp + 1, NULL, 0);
		int l = tmp - a;
		tmp = (char*)malloc(l + 1);
		// exception
		if (tmp == NULL) {
			sgn = -1;
			//std :: cout << "Memory wasn`t allocated at RationalNumber" << std :: endl;
			throw Exceptions(EX_BAD_ALLOC, this, NUMBER);
		}
		for (int i = 0; i < l; ++i) {
			tmp[i] = a[i];
		}
		tmp[l] = '\0';
		if (tmp[0] == '-') {
			sgn = 1;
			p = strtoul(tmp + 1, NULL, 0);
		} else {
			p = strtoul(tmp, NULL, 0);
		}

		numerator = p;
		denominator = q;
		//sgn = (p >= 0) ? 0 : 1;
		// exception
		if (!q) {
			sgn = -1;
    		throw Exceptions(EX_DIVIDE_BY_ZERO, this, NUMBER);
		}
        free(tmp);
	}
}

RationalNumber :: RationalNumber(const RationalNumber &a) : Exceptions(0, NULL, 0) {
	numerator = a.numerator;
	denominator = a.denominator;
	sgn = a.sgn;
}

void RationalNumber :: make_irreversible() {
	int greatcd = gcd(numerator, denominator);
	numerator /= greatcd;
	denominator /= greatcd;
}

void RationalNumber :: make_canonical() {
	this->make_irreversible();
}

RationalNumber RationalNumber :: floor() const {
	RationalNumber tmp = *(this);
	tmp -= tmp.get_fractional_part();
	tmp.make_irreversible();
	return tmp;
}

RationalNumber RationalNumber :: round() const {
	RationalNumber tmp(1, 2);
	RationalNumber tmp_1 = *(this);
	if (tmp_1.get_fractional_part() >= tmp) {
		tmp_1 = tmp_1.floor();
		tmp_1.numerator += tmp_1.denominator;
	} else {
		tmp_1 = tmp_1.floor();
	}
	tmp_1.make_irreversible();
	return tmp_1;
}

void RationalNumber :: set_numerator(uint32_t a) {
	numerator = a;
}

void RationalNumber :: set_denominator(uint32_t a) {
	denominator = a;
}

void RationalNumber :: set_sgn(int a) {
	if (a >= 0) {
		sgn = 0;
	} else {
		sgn = 1;
	}
}

uint32_t RationalNumber :: get_numerator() const {
	return numerator;
}

uint32_t RationalNumber :: get_denominator() const {
	return denominator;
}

uint32_t RationalNumber :: get_sgn() const {
	return (sgn) ? -1 : 1;
}


int RationalNumber :: get_amount_of_digits(uint32_t a) const {
	uint32_t tmp = a;
	int cnt = 0;
	if (!a) {
		return 1;
	}
	while (tmp > 0) {
		++cnt;
		tmp /= 10;
	}
	return cnt;
}

char *RationalNumber :: to_string() const {
	char *tmp;
	int num_cnt = 1, den_cnt = 1;
	char *num, *den;
	num_cnt = this->get_amount_of_digits(numerator);
	den_cnt = this->get_amount_of_digits(denominator);
	num = (char*)malloc(sizeof(char) * (num_cnt + 2));
	den = (char*)malloc(sizeof(char) * (den_cnt + 2));

	tmp = (char*)malloc(sizeof(char) * (num_cnt + den_cnt + 5));
	sprintf(num, "%u", numerator);
	sprintf(den, "%u", denominator);

	if (sgn) {
		tmp[0] = '-';
		tmp[1] = '\0';
		strcat(tmp, num);
		tmp[num_cnt + 1] = '/';
		tmp[num_cnt + 2] = '\0';
	} else {
		strcpy(tmp, num);
		tmp[num_cnt] = '/';
		tmp[num_cnt + 1] = '\0';
	}
	
	strcat(tmp, den);
	free(num);
	free(den);
	//printf("%s\n",tmp);
	return tmp;
}

RationalNumber RationalNumber :: get_integer_part() const {
	RationalNumber tmp;
	tmp.numerator =  numerator / denominator;
	tmp.denominator = 1;
	return tmp;
}

RationalNumber RationalNumber :: get_fractional_part() const {
	RationalNumber tmp;
	tmp = *(this) - this->get_integer_part();
	return tmp;
}

RationalNumber :: operator int() const {
	RationalNumber tmp = this->get_integer_part();
	int val;
	if ((tmp.numerator >= (uint32_t)INT_MIN) && (tmp.numerator <= (uint32_t)INT_MAX)) {
		val = (sgn) ? -1 : 1;
		val *= tmp.numerator;
		return val;
	} else {
		//exception
		throw Exceptions(EX_OVERFLOW, this, NUMBER);
	}
}

RationalNumber :: operator long int() const {
	RationalNumber tmp = this->get_integer_part();
	long int val;
	if ((tmp.numerator >= (uint32_t)LONG_MIN) && (tmp.numerator <= (uint32_t)LONG_MAX)) {
		val = (sgn) ? -1 : 1;
		val *= tmp.numerator;
		return val;
	} else {
		//exception
		throw Exceptions(EX_OVERFLOW, this, NUMBER);
	}
}

RationalNumber :: operator short int() const {
	RationalNumber tmp = this->get_integer_part();
	short int val;
	if ((tmp.numerator >= (uint32_t)SHRT_MIN) && (tmp.numerator <= (uint32_t)SHRT_MAX)) {
		val = (sgn) ? -1 : 1;
		val *= tmp.numerator;
		return val;
	} else {
		//exception
		throw Exceptions(EX_OVERFLOW, this, NUMBER);
	}
}

RationalNumber :: operator double() const {
	RationalNumber tmp = this->get_integer_part();
	double val = 0;
	val += tmp.numerator;
	tmp = this->get_fractional_part();
	val += (tmp.numerator % tmp.denominator);
	return val;
}

int RationalNumber :: gcd(uint32_t a, uint32_t b) const {
	return b ? gcd(b, a % b) : a;
}

RationalNumber operator+(const RationalNumber &a, const RationalNumber &b) {
	RationalNumber tmp;
	long long int tmp_lol = 0;
	int opa, opb;
	opa = (a.sgn == 0) ? 1 : -1;
	opb = (b.sgn == 0) ? 1 : -1;
	tmp_lol = (long long int)(a.numerator * b.denominator) * opa + (long long int)(a.denominator * b.numerator) * opb;
	tmp.denominator = b.denominator * a.denominator;
   	tmp.sgn = (tmp_lol >= 0) ? 0 : 1;
   	tmp.numerator = abs(tmp_lol);
   	return tmp;
}

RationalNumber operator-(const RationalNumber &a, const RationalNumber &b) {
	RationalNumber tmp;
	long long int tmp_lol = 0;
	int opa, opb;
	opa = (a.sgn == 0) ? 1 : -1;
	opb = (b.sgn == 0) ? 1 : -1;
	tmp_lol = (long long int)(a.numerator * b.denominator) * opa - (long long int)(a.denominator * b.numerator) * opb;
	tmp.denominator = b.denominator * a.denominator;
   	tmp.sgn = (tmp_lol >= 0) ? 0 : 1;
   	tmp.numerator = abs(tmp_lol);
   	//std :: cout << tmp_lol << std :: endl;
   	return tmp;
}

RationalNumber operator*(const RationalNumber &a, const RationalNumber &b) {
	RationalNumber tmp;
	tmp.numerator = a.numerator * b.numerator;
	tmp.denominator = a. denominator * b.denominator;
	tmp.sgn = ((a.sgn ^ b.sgn) == 0) ? 0 : 1;
	return tmp;
}

RationalNumber operator/(const RationalNumber &a, const RationalNumber &b) {
	// exception
	if (!b.numerator) {
		throw Exceptions(EX_DIVIDE_BY_ZERO, &b, NUMBER);
	}
	RationalNumber tmp;
	tmp.numerator = a.numerator * b.denominator;
	tmp.denominator = a. denominator * b.numerator;
	tmp.sgn = ((a.sgn ^ b.sgn) == 0) ? 0 : 1;
	return tmp;
}

RationalNumber &operator+=(RationalNumber &a, const RationalNumber &b) {
	/*long int tmp_lol;
	int opa, opb;
	opa = (a.sgn == 0) ? 1 : -1;
	opb = (b.sgn == 0) ? 1 : -1;
	tmp_lol = (long int)(a.numerator * b.denominator * opa) + (long int)(a.denominator * b.numerator * opb);
	a.denominator = b.denominator * a.denominator;
   	a.sgn = (tmp_lol >= 0) ? 0 : 1;
   	a.numerator = abs(tmp_lol);*/
   	a = a + b;
   	return a;
}
RationalNumber &operator-=(RationalNumber &a, const RationalNumber &b) {
	/*long int tmp_lol;
	int opa, opb;
	opa = (a.sgn == 0) ? 1 : -1;
	opb = (b.sgn == 0) ? 1 : -1;
	tmp_lol = (long int)(a.numerator * b.denominator * opa) - (long int)(a.denominator * b.numerator * opb);
	//std :: cout << "tmp_lol: " << tmp_lol << std :: endl;
	a.denominator = b.denominator * a.denominator;
   	a.sgn = (tmp_lol >= 0) ? 0 : 1;
   	a.numerator = abs(tmp_lol);*/
   	a = a - b;
   	return a;
}

RationalNumber &operator*=(RationalNumber &a, const RationalNumber &b) {
	a.numerator = a.numerator * b.numerator;
	a.denominator = a.denominator * b.denominator;
	a.sgn = ((a.sgn ^ b.sgn) == 0) ? 0 : 1;
	return a;
}

RationalNumber &operator/=(RationalNumber &a, const RationalNumber &b) {
	// exception
	if (!b.numerator) {
		throw Exceptions(EX_DIVIDE_BY_ZERO, &b, NUMBER);
	}
	a.numerator = a.numerator * b.denominator;
	a.denominator = a. denominator * b.numerator;
	a.sgn = ((a.sgn ^ b.sgn) == 0) ? 0 : 1;
	return a;
}

bool operator==(const RationalNumber &a, const RationalNumber &b) {
	RationalNumber tmp_a = a;
	RationalNumber tmp_b = b;
	tmp_a.make_irreversible();
	tmp_b.make_irreversible();
	if ((tmp_a.numerator == tmp_b.numerator) && (tmp_a.denominator == tmp_b.denominator) && (tmp_a.sgn == tmp_b.sgn)) {
		return true;
	} else {
		return false;
	}
}

bool operator>(const RationalNumber &a, const RationalNumber &b) {
	if (a.numerator * b.denominator > a.denominator * b.numerator) {
		return true;
	} else {
		return false;
	}
}

bool operator<(const RationalNumber &a, const RationalNumber &b) {
	if (a.numerator * b.denominator < a.denominator * b.numerator) {
		return true;
	} else {
		return false;
	}
}

bool operator<=(const RationalNumber &a, const RationalNumber &b) {
	if (a.numerator * b.denominator <= a.denominator * b.numerator) {
		return true;
	} else {
		return false;
	}	
}

bool operator>=(const RationalNumber &a, const RationalNumber &b) {
	if (a.numerator * b.denominator >= a.denominator * b.numerator) {
		return true;
	} else {
		return false;
	}	
}

bool operator!=(const RationalNumber &a, const RationalNumber &b) {
	if ((a.numerator == b.numerator) && (a.denominator == b.denominator) && (a.sgn == b.sgn)) {
		return false;
	} else {
		return true;
	}
}

std :: ostream& operator<<(std :: ostream &strm, const RationalNumber &a) {
    if ((a.denominator == 1) || (a.numerator == 0)) {
        strm << (long long)a.numerator * (a.sgn == 0 ? 1 : -1);
    } else {
    	strm << (long long)a.numerator * (a.sgn == 0 ? 1 : -1) << "/" << a.denominator;
    }
    return strm;
}
