#include "matrix.h"

Matrix* create_matrix_from_file(FILE* file) {
  int totalRows;
  int totalColumns;
  
  if(fscanf(file, "%11d\n%11d\n", &totalRows, &totalColumns) != 2) {
	if(ferror(file)) {
	  printf("Error reeading from file\n");
	} else {
	  printf("Incorrect data format\n");
	}
	return NULL;
  }
  
  if((totalColumns <= 0) || (totalRows <= 0)) {
	printf("Incorrect value of rows or/and columns\n These must be above zero\n");
	return NULL;
  }
  
  Matrix* p_matrix = create_matrix(totalRows, totalColumns);
  
  if(p_matrix == NULL) {
	return NULL;
  }
  
  for(size_t curRow = 0; curRow < (size_t)totalRows; ++curRow) {
	for(size_t curCol = 0; curCol < (size_t)totalColumns; ++curCol) {
	  double buf;		//следует объявлять внутри цикла или снаружи для эффективности?
						//буде ли компилятор оптимизировать это?
	  if(fscanf(file, "%lf", &buf) != 1) {
		if(ferror(file)) {
		  printf("Error reeading from file\n");
		} else {
		  printf("Incorrect data format\n");
		}
		free_matrix(p_matrix);
		return NULL;
	  }
	  set_elem(p_matrix, curRow, curCol, buf);
	}
	
	char temp;		//доп. задание проверка правильности входной матрицы матрицы
	while(!feof(file)) {
	  temp = getc(file);
	  //printf("%c\n", temp);
	  if(temp == '\n') {
		break;
	  }
	  if(!isspace((int)temp)) {
		printf("Letter differs from space detected before the end of the line\n");
        free_matrix(p_matrix);
		return NULL;
	  }
	}
  }
  return p_matrix;
}

Matrix* create_matrix(int row, int col) {
  
  if((row <= 0) || (col <= 0)) {
	return NULL;
  }
  
  Matrix* p_matrix = (Matrix*)malloc((sizeof(Matrix)));
  p_matrix->columns = col;
  p_matrix->rows = row;
  
  p_matrix->p_beg = (double**)malloc(sizeof(double*) * row);
  if(p_matrix->p_beg == NULL) {
	return NULL;
  }
  
  for(size_t i = 0; i < row; ++i) {
	p_matrix->p_beg[i] = (double*)malloc(sizeof(double) * col);
	if(p_matrix->p_beg[i] == NULL) {
	  return NULL;
	}
  }
  
  return p_matrix;
}

void free_matrix(Matrix* matrix) {
  if(matrix == NULL) return;
  
  for(size_t i = 0; i < matrix->rows; ++i) {
	free(matrix->p_beg[i]);
  }
  free(matrix->p_beg);
  free(matrix);
}
double get_elem(Matrix* matrix, int row, int col) {
  if((row >= matrix->rows) || (col >= matrix->columns) || (row < 0) || (col < 0)) {
    return DBL_MAX; //возвращаем наибольшее double-число
  }
    
  
  return matrix->p_beg[row][col];
}
void set_elem(Matrix* matrix, int row, int col, double val) {
  //понадеемся, что row и col введены корректно, функция по условию void -> нечем вывести ошибку
  //если assert и exit нельзя использовать
  matrix->p_beg[row][col] = val; //меняем значение
}
int get_rows(Matrix* matrix) {
  return (int)matrix->rows;
}
int get_cols(Matrix* matrix) {
  return (int)matrix->columns;
}
//TODO
