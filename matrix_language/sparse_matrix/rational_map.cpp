#include <iostream>
#include <cstdlib>

#include "rational_map.h"

RationalMap :: RationalMap() : Exceptions(0, NULL, 0) {}

RationalMap :: RationalMap(const RationalMap &a) : Exceptions(0, NULL, 0) {
	number = a.number;
	position = a.position;
}

RationalMap :: RationalMap(const char *s) : Exceptions(0, NULL, 0) {
	if (s == NULL) {
		throw(Exceptions(EX_WRONG_FILE_NAME, this, MAP));
	}

	//char c;
	size_t i = 0;
	char *tmp;
	while ((s[i] != '\0') && (s[i] != '\n')) {
		if (s[i] == '#') {
			++i;
			continue;
		}
		while (s[i] == ' ') {
			if (s[i] == '#') {
				++i;
				continue;
			}
			++i; 
		}
		const char *tmp_chr;
		tmp_chr = strchr(s + i, ' ');
		tmp = (char*)malloc(sizeof(char) * (tmp_chr - (s + i) + 1));
		strncpy(tmp, s + i, tmp_chr - (s + i));
		tmp[tmp_chr - (s + i)] = '\0';
		position = strtoul(tmp, NULL, 0);
		free(tmp);
		tmp = NULL;
		size_t j = 1;
		i = tmp_chr - (s + i);
		tmp = (char*)malloc(sizeof(char));
		while ((s[i] != '\0') && (s[i] != '\n'))  {
			if ((s[i] == '#') || (s[i] == ' ')) {
				++i;
				continue;
			}
			tmp = (char*)realloc(tmp, sizeof(char) * (j + 1));
			tmp[j - 1] = s[i];
			++j;
			++i;
		}
		tmp[j - 1] = '\0';
		//number = strtoul(tmp, NULL, 0);
		number = RationalNumber(tmp);
		free(tmp);
 	}
}

RationalMap :: ~RationalMap() {}

RationalMap operator+(const RationalMap &a, const RationalMap &b) {
	if (a.position != b.position) {
		//exception
		throw(Exceptions(EX_SIZE_OF_VECTORS_ARE_DIFFERENT, &a, MAP));
	}
	RationalMap tmp;
	tmp.number = a.number + b.number;
	tmp.position = a.position;
	return tmp;
}

RationalMap operator-(const RationalMap &a, const RationalMap &b) {
	if (a.position != b.position) {
		//exception
		throw(Exceptions(EX_SIZE_OF_VECTORS_ARE_DIFFERENT, &a, MAP));
	}
	RationalMap tmp;
	tmp.number = a.number - b.number;
	tmp.position = a.position;
	return tmp;
}

RationalMap operator*(const RationalMap &a, const RationalMap &b) {
	if (a.position != b.position) {
		//exception
		throw(Exceptions(EX_SIZE_OF_VECTORS_ARE_DIFFERENT, &a, MAP));
	}
	RationalMap tmp;
	tmp.number = a.number * b.number;
	tmp.position = a.position;
	return tmp;
}

RationalMap operator/(const RationalMap &a, const RationalMap &b) {
	if (a.position != b.position) {
		//exception
		throw(Exceptions(EX_SIZE_OF_VECTORS_ARE_DIFFERENT, &a, MAP));
	}
	RationalMap tmp;
	tmp.number = a.number / b.number;
	tmp.position = a.position;
	return tmp;
}

RationalMap &operator+=(RationalMap &a, const RationalMap &b) {
	if (a.position != b.position) {
		//exception
		throw(Exceptions(EX_SIZE_OF_VECTORS_ARE_DIFFERENT, &a, MAP));
	}
	a.number += b.number;
	return a;
}

RationalMap &operator-=(RationalMap &a, const RationalMap &b) {
	if (a.position != b.position) {
		//exception
		throw(Exceptions(EX_SIZE_OF_VECTORS_ARE_DIFFERENT, &a, MAP));
	}
	a.number -= b.number;
	return a;
}

RationalMap &operator*=(RationalMap &a, const RationalMap &b) {
	if (a.position != b.position) {
		//exception
		throw(Exceptions(EX_SIZE_OF_VECTORS_ARE_DIFFERENT, &a, MAP));
	}
	a.number *= b.number;
	return a;
}

RationalMap &operator/=(RationalMap &a, const RationalMap &b) {
	if (a.position != b.position) {
		//exception
		throw(Exceptions(EX_SIZE_OF_VECTORS_ARE_DIFFERENT, &a, MAP));
	}
	a.number /= b.number;
	return a;
}
