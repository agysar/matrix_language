#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "rational_matrix.h"
#include "rational_vector.h"

#define MATRIX_ALLOC 20

RationalMatrix :: RationalMatrix() : Exceptions(0, NULL, 0) {
	data = NULL;
	x = NULL;
	y = NULL;
	rows = 1;
	cols = 1;
	real_size = 0;
	size = 1;
	data = (RationalNumber*)malloc(sizeof(RationalNumber));
	if (data == NULL) {
		throw(Exceptions(EX_BAD_ALLOC, this, MATRIX));
	}
	RationalNumber tmp(0, 1);
	data[0] = tmp;
	x = (size_t*)malloc(sizeof(size_t));
	if (x == NULL) {
		throw(Exceptions(EX_BAD_ALLOC, this, MATRIX));
	}

	y = (size_t*)malloc(sizeof(size_t));
	if (y == NULL) {
		throw(Exceptions(EX_BAD_ALLOC, this, MATRIX));
	}
	x[0] = 0;
	y[0] = 0;
}

RationalMatrix :: RationalMatrix(const RationalVector &a, size_t orient = VERTICAL) : Exceptions(0, NULL, 0){
	data = (RationalNumber*)malloc(sizeof(RationalNumber) * a.real_size);
	x = (size_t*)malloc(sizeof(size_t) * a.real_size);
	y = (size_t*)malloc(sizeof(size_t) * a.real_size);
	if (orient == VERTICAL) {
		rows = a.size;
		cols = 1;
		real_size = a.real_size;
		for (size_t i = 0; i < a.real_size; ++i) {
			data[i] = a.data[i].number;
			x[i] = a.data[i].position;
			y[i] = 1;
		}
	} else {
		rows = 1;
		cols = a.size;
		real_size = a.real_size;
		for (size_t i = 0; i < a.real_size; ++i) {
			data[i] = a.data[i].number;
			x[i] = 1;
			y[i] = a.data[i].position;
		}	
	}
}

RationalMatrix :: RationalMatrix(const RationalMatrix &a) : Exceptions(0, NULL, 0) {
	rows = a.rows;
	cols = a.cols;
	real_size = a.real_size;
	data = (RationalNumber*)malloc(sizeof(RationalNumber) * real_size);
	if (data == NULL) {
		throw(Exceptions(EX_BAD_ALLOC, this, MATRIX));
	}

	x = (size_t*)malloc(sizeof(size_t) * real_size);
	if (x == NULL) {
		throw(Exceptions(EX_BAD_ALLOC, this, MATRIX));
	}

	y = (size_t*)malloc(sizeof(size_t) * real_size);
	if (y == NULL) {
		throw(Exceptions(EX_BAD_ALLOC, this, MATRIX));
	}

	for (size_t i = 0; i < real_size; ++i) {
		data[i] = a.data[i];
		x[i] = a.x[i];
		y[i] = a.y[i];
	}
}

RationalMatrix :: RationalMatrix(size_t r, RationalNumber a) : Exceptions(0, NULL, 0) {
	rows = r;
	cols = r;
	data = NULL;
	x = NULL;
	y = NULL;
	if (a == RationalNumber(0, 1)) {
		real_size = 0;
		size = r * r;
	} else {
		real_size = r;
		size = r * r;
		data = (RationalNumber*)malloc(sizeof(RationalNumber) * r);
		if (data == NULL) {
			throw(Exceptions(EX_BAD_ALLOC, this, MATRIX));
		}

		x = (size_t*)malloc(sizeof(size_t) * r);
		if (x == NULL) {
			throw(Exceptions(EX_BAD_ALLOC, this, MATRIX));
		}

		y = (size_t*)malloc(sizeof(size_t) * r);
		if (y == NULL) {
			throw(Exceptions(EX_BAD_ALLOC, this, MATRIX));
		}

		for (size_t i = 0; i < r; ++i) {
			data[i] = a;
			x[i] = i;
			y[i] = i;
		}
	}
}

RationalMatrix :: RationalMatrix(size_t r, size_t c, RationalNumber a) : Exceptions(0, NULL, 0) {
	rows = r;
	cols = c;
	data = NULL;
	x = NULL;
	y = NULL;
	if (a == RationalNumber(0, 1)) {
		real_size = 0;
		size = r * c;
	} else {
		real_size = (r < c) ? r : c;
		size = r * c;
		data = (RationalNumber*)malloc(sizeof(RationalNumber) * real_size);
		if (data == NULL) {
			throw(Exceptions(EX_BAD_ALLOC, this, MATRIX));
		}

		x = (size_t*)malloc(sizeof(size_t) * real_size);
		if (x == NULL) {
			throw(Exceptions(EX_BAD_ALLOC, this, MATRIX));
		}

		y = (size_t*)malloc(sizeof(size_t) * real_size);
		if (y == NULL) {
			throw(Exceptions(EX_BAD_ALLOC, this, MATRIX));
		}

		for (size_t i = 0; i < real_size; ++i) {
			data[i] = a;
			x[i] = i;
			y[i] = i;
		}
	}
}

RationalMatrix :: RationalMatrix(const char *file_name) : Exceptions(0, NULL, 0) {
	x = NULL;
	y = NULL;
	if (file_name == NULL) {
		throw(Exceptions(EX_WRONG_FILE_NAME, this, MATRIX));
	}

	FILE *f;

	f = fopen(file_name, "r+");

	if (f == NULL) {
		throw(Exceptions(EX_CANNOT_OPEN_FILE, this, MATRIX));
	}

	char c;
	char v[] = {"matrix"};

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
		throw(Exceptions(EX_FILE_HAVE_NO_MATRIX, this, MATRIX));
	}

	//c = getc(f);

	if (c != ' ') {
		throw(Exceptions(EX_FILE_HAVE_NO_MATRIX, this, MATRIX));
	}
	free(tmp);
	tmp = NULL;

	i = 1;
	tmp = (char*)malloc(sizeof(char));
	while (((c = getc(f)) != EOF) && (c != '\n') && (c != ' ')) {
		tmp = (char*)realloc(tmp, i + 1);
		tmp[i - 1] = c;
		++i;
	}
	tmp[i - 1] = '\0';
	rows = strtoul(tmp, NULL, 0);
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
	cols = strtoul(tmp, NULL, 0);
	free(tmp);
	tmp = NULL;

	size = rows * cols;

	i = 0;
	size_t q = 0; // for real size
	data = NULL;
	while (i < size) {
		tmp = (char*)malloc(sizeof(char) * 50);
		if (tmp == NULL) {
			throw(Exceptions(EX_BAD_ALLOC, this, MATRIX));
		}
		tmp[0] = '\0';
		fgets(tmp, 50, f);
		if (tmp == NULL) {
			throw(Exceptions(EX_END_OF_FILE, this, MATRIX));
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

		size_t j = 1;
		char *lol = NULL;
		while (tmp[j - 1] != ' ' && tmp[j - 1] != '\n' && tmp[j - 1] != '\0') {
			lol = (char*)realloc(lol, sizeof(char) * (j + 1));
			lol[j - 1] = tmp[j - 1];
			++j;
		}
		lol[j - 1] = '\0';

		RationalMap kappa(tmp + j);
		if (kappa.number != RationalNumber(0, 1)) {

			x = (size_t*)realloc(x, sizeof(size_t) * (q + 1));
			x[q] = strtoul(lol, NULL, 0);
			
		
			y = (size_t*)realloc(y, sizeof(size_t) * (q + 1));
			y[q] = kappa.position;


			data = (RationalNumber*)realloc(data, sizeof(RationalNumber) * (q + 1));
			data[q] = kappa.number;
			++q;
		}
		++i;
		free(lol);
		lol = NULL;
		free(tmp);
		tmp = NULL;
	}
	real_size = q;

	fclose(f);
}

RationalMatrix :: ~RationalMatrix() {
	if (data != NULL) {
		free(data);
		data = NULL;
	}

	if (x != NULL) {
		free(x);
		x = NULL;
	}

	if (y != NULL) {
		free(y);
		y = NULL;
	}
}

void RationalMatrix :: to_out() const {
	if (!real_size) {
		std :: cout << "MATRIX IS EMPTY" << std :: endl;
	}
	for (size_t i = 0; i < this->real_size; ++i) {
		std :: cout << this->x[i] << " " << this->y[i] << " " << this->data[i] << std :: endl;
	}
}

char *RationalMatrix :: to_string() const {
	char *tmp = NULL, *tmp_num = NULL;
	char temp[] = {"MATRIX HASN`T GOT ANY NON-ZERO ELEMENTS\n"};
	size_t len = MATRIX_ALLOC * 3; // hardcode
	tmp = (char*)malloc(sizeof(char));
	tmp[0] = '\0';
	if (!real_size) {
		tmp = (char*)realloc(tmp, sizeof(char) * len);
		strcat(tmp, temp);
		return tmp;
	}

	size_t k = 0;
	tmp = (char*)realloc(tmp, sizeof(char) * len);
	for (size_t i = 0; i < rows; ++i) {
		tmp[k] = '[';
		++k;
		tmp[k] = '\0';
		++k;
		for (size_t j = 0; j < cols; ++j) {
			//tmp_num = (char*)malloc(sizeof(char) * MATRIX_ALLOC);
			tmp_num = (*this)(i, j).to_string();
			k += strlen(tmp_num);
			strcat(tmp, tmp_num);
			if (j != cols - 1) { 
				strcat(tmp, ",");
				++k;
			}
			//len += strlen(tmp_num);
			len += MATRIX_ALLOC;
			tmp = (char*)realloc(tmp, sizeof(char) * len);
			free(tmp_num);
			tmp_num = NULL;
		}
		--k;
		tmp[k] = ']';
		++k;
		tmp[k] = '\n';
		++k;
	}
	tmp[k] = '\0';
	/*for (size_t i = 0; i < real_size; ++i) {
		tmp = (char*)realloc(tmp, sizeof(char) * len);
		tmp_x = (char*)malloc(sizeof(char) * MATRIX_ALLOC); // hardcode
		tmp_y = (char*)malloc(sizeof(char) * MATRIX_ALLOC); // hardcode
		sprintf(tmp_x, "%lu", x[i]);
		sprintf(tmp_y, "%lu", y[i]);
		tmp_num = data[i].to_string();
		strcat(tmp, tmp_x);
		strcat(tmp, " ");
		strcat(tmp, tmp_y);
		strcat(tmp, " ");
		strcat(tmp, tmp_num);
		strcat(tmp, "\n");

		free(tmp_x);
		tmp_x = NULL;
		free(tmp_y);
		tmp_y = NULL;
		free(tmp_num);
		tmp_num = NULL;
		len += MATRIX_ALLOC * 3;
	}*/

	return tmp;
}

void RationalMatrix :: write(const char *file_name) const {
	if (file_name == NULL) {
		throw(Exceptions(EX_WRONG_FILE_NAME, this, MATRIX));
	}

	FILE *f;

	f = fopen(file_name, "w+");

	if (f == NULL) {
		throw(Exceptions(EX_CANNOT_OPEN_FILE, this, MATRIX));
	}

	char *tmp = this->to_string();
	char *tmp_p = NULL, *tmp_rows = NULL, *tmp_cols = NULL;
	tmp_p = (char*)malloc(strlen(tmp) + MATRIX_ALLOC * 2);
	tmp_p[0] = '\0';
	tmp_rows = (char*)malloc(MATRIX_ALLOC);
	tmp_cols = (char*)malloc(MATRIX_ALLOC);
	sprintf(tmp_rows, "%lu", this->rows);
	sprintf(tmp_cols, "%lu", this->cols);
	strcat(tmp_p, "matrix ");
	strcat(tmp_p, tmp_rows);
	strcat(tmp_p, " ");
	strcat(tmp_p, tmp_cols);
	strcat(tmp_p, "\n");
	strcat(tmp_p, tmp);

	fprintf(f, "%s\n", tmp_p);
	free(tmp);
	tmp = NULL;
	free(tmp_p);
	tmp_p = NULL;
	free(tmp_rows);
	tmp_rows = NULL;
	free(tmp_cols);
	tmp_cols = NULL;
	fclose(f);
	return;
}

RationalMatrix RationalMatrix :: operator-(const RationalMatrix &a) {
	RationalMatrix tmp = a;
	for (size_t i = 0; i < a.real_size; ++i) {
		tmp.data[i] *= -1;
	}
	return tmp;
}

RationalMatrix operator+(const RationalMatrix &a, const RationalMatrix &b) {
	if ((a.rows != b.rows) || (a.cols != b.cols)) {
		throw(Exceptions(EX_SIZE_OF_MATRIX_ARE_DIFFERENT, &a, MATRIX));
	}

	//RationalMatrix tmp(a.rows, a.cols, 0);
	RationalMatrix tmp = a;
	for (size_t i = 0; i < a.real_size; ++i) {
		if (a.data[i] != RationalNumber(0,1)) {
			tmp(a.x[i], a.y[i]) = tmp(a.x[i], a.y[i]) + a.data[i];
		}
	}

	for (size_t i = 0; i < b.real_size; ++i) {
		if (b.data[i] != RationalNumber(0, 1)) {
			tmp(b.x[i], b.y[i]) = tmp(b.x[i], b.y[i]) + b.data[i];
		}
	}

	return tmp;
}

RationalMatrix operator-(const RationalMatrix &a, const RationalMatrix &b) {
	if ((a.rows != b.rows) || (a.cols != b.cols)) {
		throw(Exceptions(EX_SIZE_OF_MATRIX_ARE_DIFFERENT, &a, MATRIX));
	}

	//RationalMatrix tmp(a.rows, a.cols, 0);
	RationalMatrix tmp = a;
	for (size_t i = 0; i < a.real_size; ++i) {
		if (a.data[i] != RationalNumber(0,1)) {
			tmp(a.x[i], a.y[i]) = tmp(a.x[i], a.y[i]) - a.data[i];
		}
	}

	for (size_t i = 0; i < b.real_size; ++i) {
		if (b.data[i] != RationalNumber(0, 1)) {
			tmp(b.x[i], b.y[i]) = tmp(b.x[i], b.y[i]) - b.data[i];
		}
	}

	return tmp;
}

RationalMatrix operator*(const RationalMatrix &a, const RationalMatrix &b) {
	if (a.cols != b.rows) {
		throw(Exceptions(EX_SIZE_OF_MATRIX_ARE_DIFFERENT, &a, MATRIX));
	}

	RationalMatrix tmp(a.rows, b.cols, 0);
	//std :: cout << "tmp matrix\n" << tmp.to_string() << "\n";
	if (!(a.real_size * b.real_size)) {
		return tmp;
	}
	for (size_t i = 0; i < a.rows; ++i) {
		for (size_t j = 0; j < b.cols; ++j) {
			tmp(i, j) = RationalNumber(0, 1);
			for (size_t r = 0; r < a.cols; ++r) {
				//std::cout <<tmp(i,j) << tmp.real_size << std::endl;
				//tmp(i, j) += a(i, r) * b(r, j);
				tmp(i, j) = tmp(i, j) + a(i, r) * b(r, j);
				//std::cout << "  " << tmp(i,j) << "   " << a(i,r) * b(r,j) << /* "   " << a(i,r) << "   " << b(r,j) <<*/ "   " << i << "   " << j << "   " << r << std::endl;
			}
			tmp(i, j).make_canonical();
	//		std :: cout << tmp(i, j) << std :: endl;
		}
	}

	return tmp;
}

RationalMatrix operator^(const RationalMatrix &a, size_t n) {
	if (a.cols != a.rows) {
		throw(Exceptions(EX_SIZE_OF_MATRIX_ARE_DIFFERENT, &a, MATRIX));
	}

	RationalMatrix tmp(a.rows, a.cols, 1);
	RationalMatrix tmp_a(a);
	while (n) {
		if (n & 1) {
			tmp = tmp * tmp_a;
		} 
		tmp_a = tmp_a * tmp_a;
		n >>= 1;
	}
	/*if (!n) {
		RationalMatrix tmp(a.rows, a.cols, 1);
		return tmp;
	}

	if (n == 1) {
		RationalMatrix tmp = a;
		return a;
	}

	RationalMatrix tmp;
	for (size_t i = 0; i < n - 1; ++i) {
		tmp = tmp * a;
	}*/

	return tmp;
}
