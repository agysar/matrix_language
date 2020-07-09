#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "rational_vector.h"

#define VECTOR_ALLOC 20

RationalVector :: RationalVector() : Exceptions(0, NULL, 0) {
	data = (RationalMap*)malloc(sizeof(RationalMap));
	data[0].position = 0;
	data[0].number = RationalNumber(0, 1);
	size = 1;
	real_size = 0;
}

RationalVector :: RationalVector(const RationalVector &a) : Exceptions(0, NULL, 0) {
	data = (RationalMap*)malloc(sizeof(RationalMap) * a.real_size);
	real_size = a.real_size;
	size = a.size;
	for (size_t i = 0; i < real_size; ++i) {
		data[i] = a.data[i];
	}
}

RationalVector :: RationalVector(size_t size_, RationalNumber a) : Exceptions(0, NULL, 0) {
	size = size_;
	if (a != RationalNumber(0, 1)) {
		real_size = size_;
	} else {
		real_size = 0;
	}
	data = (RationalMap*)malloc(sizeof(RationalMap) * size);
	for (size_t i = 0; i < size; ++i) {
		data[i].position = i;
		data[i].number = a;
	}
}

RationalVector :: RationalVector(const char *file_name) : Exceptions(0, NULL, 0) {
	if (file_name == NULL) {
		throw(Exceptions(EX_WRONG_FILE_NAME, this, VECTOR));
	}

	FILE *f;

	f = fopen(file_name, "r+");

	if (f == NULL) {
		throw(Exceptions(EX_CANNOT_OPEN_FILE, this, VECTOR));
	}

	char c;
	char v[] = {"vector"};

	size = 0;
	real_size = 0;

	while (((c = getc(f)) != EOF) && (c == '#')) {
		while (((c = getc(f)) != EOF) && (c != '\n')) { }
	}
		
	size_t i = 0;
	char *tmp = (char*)malloc(sizeof(char) * 7);
	while ((i < 6) && (c != EOF) && (c != '\n') && (c != '#')) {
		tmp[i] = c;
		++i;
		c = getc(f);
	}

	tmp[6] = '\0';

	if (strcmp(tmp, v)) {
		throw(Exceptions(EX_FILE_HAVE_NO_VECTOR, this, VECTOR));
	}

	//c = getc(f);

	if (c != ' ') {
		throw(Exceptions(EX_FILE_HAVE_NO_VECTOR, this, VECTOR));
	}

	free(tmp);
	tmp = NULL;
	i = 1;
 	tmp = (char*)malloc(sizeof(char));
	while (((c = getc(f)) != EOF) && (c != '\n')) {
		tmp = (char*)realloc(tmp, i + 1);
		tmp[i - 1] = c;
		++i;
	}
	tmp[i - 1] = '\0';
	size = strtoul(tmp, NULL, 0);
	//size = real_size;

	free(tmp);
	tmp = NULL;
	//tmp = (char*)malloc(sizeof(char) * 100);
	i = 0;
	size_t j = 0;
	data = NULL;
	while (i < size) {
		tmp = (char*)malloc(sizeof(char) * 50);
		if (tmp == NULL) {
			throw(Exceptions(EX_BAD_ALLOC, this, VECTOR));
		}
		tmp[0] = '\0';
		fgets(tmp, 50, f);
		if (tmp == NULL) {
			throw(Exceptions(EX_END_OF_FILE, this, VECTOR));
		}
		if (!strcmp(tmp, "")) {
			free(tmp);
			tmp = NULL;
			break;
		}
		if (!strcmp(tmp, "\n")) {
			free(tmp);
			tmp = NULL;
			continue;
		}
		RationalMap kappa(tmp);
		/*if (kappa.position > size) {
			size = kappa.position + 1;
		}*/
		free(tmp);
		tmp = NULL;
		if (kappa.number != RationalNumber(0, 1)) {
			data = (RationalMap*)realloc(data, sizeof(RationalMap) * (j + 1));
			data[j] = kappa;
			++j;
		}
		++i;
	}
	real_size = j;

	fclose(f);
}

RationalVector :: ~RationalVector() {
	if (size) {
		free(data);
		data = NULL;
	}
}

char *RationalVector :: to_string() const {
	char *str, *tmp;
	size_t len = 0;
	str = (char*)malloc(sizeof(char) * VECTOR_ALLOC * 3);
	size_t k = 0;
	

	for (size_t i = 0; i < this->size; ++i) {
		//printf("%lu\n", i);
		str[k] = '[';
		++k;
		str[k] = '\0';
		//++k;
		tmp = (*this)[i].to_string();
		k += strlen(tmp);
		strcat(str, tmp);
		strcat(str, "]\n");
		k += 2;
		//tmp_len = strlen(str);
		
		/*str[tmp_len] = '\n';
		str[tmp_len + 1] = '\0';*/
		len += VECTOR_ALLOC;
		str = (char*)realloc(str, len);
		free(tmp);
		tmp = NULL;
	}
	str[k] = '\0';
	return str;
}

RationalVector operator-(const RationalVector &a) {
	RationalVector tmp = a;
	for (size_t i = 0; i < tmp.real_size; ++i) {
		tmp.data[i].number.sgn = (tmp.data[i].number.sgn) ? 0 : 1;
	}
	return tmp;
}

RationalVector operator-(const RationalVector &a, const RationalVector &b) {
	if (a.size != b.size) {
		//exception
		throw(Exceptions(EX_SIZE_OF_VECTORS_ARE_DIFFERENT, &a, VECTOR));
	}
	RationalVector tmp = a;
	for (size_t i = 0; i < b.real_size; ++i) {
		tmp(b.data[i].position) -= (b.data[i].number);
	}	
	/*for (size_t i = 0; i < tmp.size; ++i) {
		if (b[i] != RationalNumber(0, 1)) {
			tmp(i) -= b[i];
		}
	}*/
	return tmp;
}

RationalVector operator+(const RationalVector &a, const RationalVector &b) {
	if (a.size != b.size) {
		//exception
		throw(Exceptions(EX_SIZE_OF_VECTORS_ARE_DIFFERENT, &a, VECTOR));
	}
	RationalVector tmp = a;
	for (size_t i = 0; i < b.real_size; ++i) {
		tmp(b.data[i].position) += (b.data[i].number);
	}
	/*
	for (size_t i = 0; i < tmp.size; ++i) {
		if (b[i] != RationalNumber(0, 1)) {
			tmp(i) += b[i];
		}
	}*/
	return tmp;
}

RationalVector operator*(const RationalVector &a, const RationalNumber &b) {
	RationalVector tmp = a;
	for (size_t i = 0; i < a.real_size; ++i) {
		(tmp.data[i].number) *= b;	
	}
	/*for (size_t i = 0; i < tmp.size; ++i) {
		if (tmp[i] != RationalNumber(0, 1)) {
			tmp(i) *= b;
		}
	}*/
	return tmp;
}

RationalVector operator*(const RationalNumber &a, const RationalVector &b) {
	RationalVector tmp = b;
	for (size_t i = 0; i < b.real_size; ++i) {
		(tmp.data[i].number) *= a;
	}
	/*for (size_t i = 0; i < tmp.size; ++i) {
		if (tmp[i] != RationalNumber(0, 1)) {
			tmp(i) *= a;
		}
	}*/
	return tmp;
}

RationalVector operator/(const RationalVector &a, const RationalNumber &b) {
	RationalVector tmp = a;
	for (size_t i = 0; i < a.real_size; ++i) {
		tmp(a.data[i].position) /= b;
	}
	/*for (size_t i = 0; i < tmp.size; ++i) {
		tmp(i) /= b;
	}*/
	return tmp;
}

RationalNumber operator*(const RationalVector &a, const RationalVector &b) {
	RationalNumber tmp(0, 1);
	//RationalNumber tmp_p(0, 1);
	if (a.size != b.size) {
		//exception
		throw(Exceptions(EX_SIZE_OF_VECTORS_ARE_DIFFERENT, &a, VECTOR));
	}
	for (size_t i = 0; i < a.real_size; ++i) {
		if ((a.data[i].number != RationalNumber(0, 1)) && (b[a.data[i].position]) != RationalNumber(0, 1)) {
			tmp += a.data[i].number * b[a.data[i].position];
		}
		//tmp_p = a[i] * b[i];
	}
	return tmp;
}

RationalVector operator+(const RationalVector &a, const RationalNumber &b) {
	RationalVector tmp;
	tmp.real_size = a.real_size;
	tmp.size = a.size;
	tmp.data = (RationalMap*)malloc(sizeof(RationalMap) * tmp.size);
	for (size_t i = 0; i < tmp.size; ++i) {
		tmp(i) += b;
	}
	return tmp;
}

RationalVector operator+(const RationalNumber &a, const RationalVector &b) {
	RationalVector tmp;
	tmp.real_size = b.real_size;
	tmp.size = b.size;
	tmp.data = (RationalMap*)malloc(sizeof(RationalMap) * tmp.size);
	for (size_t i = 0; i < tmp.size; ++i) {
		tmp(i) += a;
	}
	return tmp;
}

RationalVector operator-(const RationalVector &a, const RationalNumber &b) {
	RationalVector tmp;
	tmp.real_size = a.size;
	tmp.size = a.size;
	tmp.data = (RationalMap*)malloc(sizeof(RationalMap) * tmp.size);
	for (size_t i = 0; i < tmp.size; ++i) {
		tmp(i) -= b;
	}
	return tmp;
}

std :: ostream& operator<<(std :: ostream &strm, const RationalVector &a) {
	char *tmp;
	tmp = a.to_string();

	strm << tmp;
	free(tmp);
	tmp = NULL;
	return strm;
}

void RationalVector :: to_out() const {
	for (size_t i = 0; i < this->real_size; ++i) {
		std :: cout << this->data[i].position << " " << this->data[i].number << std :: endl;
	}
	return;
}

void RationalVector :: write(const char *file_name) const {
	if (file_name == NULL) {
		throw(Exceptions(EX_WRONG_FILE_NAME, this, VECTOR));
	}

	FILE *f;

	f = fopen(file_name, "w+");
	if (f == NULL) {
		throw(Exceptions(EX_CANNOT_OPEN_FILE, this, VECTOR));
	}

	//printf("We are in the ::write before to_string\n");
	char *tmp = this->to_string();
	//printf("After to_string\n");
	fprintf(f, "%s\n", tmp);
	free(tmp);
	tmp = NULL;
	fclose(f);
	return;
}
