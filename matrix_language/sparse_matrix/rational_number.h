#pragma once

#include <iostream>
#include <string.h>
#include <stdint.h>

#include "exceptions.h"

class RationalNumber : public Exceptions {
    uint32_t numerator;
    uint32_t denominator;

    public:
        int sgn; // 0 - plus, 1 - minus, -1 - bad number or NaN (exception)

        RationalNumber();
        RationalNumber(uint32_t, uint32_t);
        RationalNumber(int);
        RationalNumber(char *, char *);
        RationalNumber(char *);
        RationalNumber(const RationalNumber &);
        ~RationalNumber();
    
        void make_canonical();
        RationalNumber get_integer_part() const;
        RationalNumber get_fractional_part() const;

        operator int() const;
        operator long int() const;
        operator short int() const;
        operator double() const;

        int gcd(uint32_t a, uint32_t b) const;
        void make_irreversible();

        RationalNumber floor() const;
        RationalNumber round() const;

        void set_numerator(uint32_t);
        void set_denominator(uint32_t);
        void set_sgn(int);

        uint32_t get_numerator() const;
        uint32_t get_denominator() const;
        uint32_t get_sgn() const;

        int get_amount_of_digits(uint32_t) const;

        char *to_string() const;

        RationalNumber &operator=(const RationalNumber &b) {
            numerator = b.numerator;
            denominator = b.denominator;
            sgn = b.sgn;
            return *this;
        }

        friend RationalNumber operator+(const RationalNumber &a, const RationalNumber &b);
        friend RationalNumber operator-(const RationalNumber &a, const RationalNumber &b);
        friend RationalNumber operator*(const RationalNumber &a, const RationalNumber &b);
        friend RationalNumber operator/(const RationalNumber &a, const RationalNumber &b);

        friend RationalNumber &operator+=(RationalNumber &a, const RationalNumber &b);
        friend RationalNumber &operator-=(RationalNumber &a, const RationalNumber &b);
        friend RationalNumber &operator*=(RationalNumber &a, const RationalNumber &b);
        friend RationalNumber &operator/=(RationalNumber &a, const RationalNumber &b);

        RationalNumber &operator++() { numerator += denominator; return *this; } 
        RationalNumber operator++(int a) { RationalNumber tmp(*this); numerator += denominator; return tmp; }

        friend bool operator==(const RationalNumber &, const RationalNumber &); 
        friend bool operator>(const RationalNumber &, const RationalNumber &);
        friend bool operator<(const RationalNumber &, const RationalNumber &);
        friend bool operator<=(const RationalNumber &, const RationalNumber &);
        friend bool operator>=(const RationalNumber &, const RationalNumber &);
        friend bool operator!=(const RationalNumber &, const RationalNumber &);

        friend std :: ostream& operator<<(std :: ostream &strm, const RationalNumber &a);
};
