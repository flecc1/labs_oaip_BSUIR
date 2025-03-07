#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int **memAloc(int rows, int cols);
void fill0(int **matrix, int rows, int cols);
void output_matrix(int **matrix, int rows, int cols);
void clearMatrix(int **matrix, int rows);
int square_matrix_size(int n);
int choice_func(int n);
int proverka2(int a, int y);
int get_valid_input(char *prompt);
void inst_input(int **matrix, int rows, int cols);
int checkOverlap(int **matrix, int size, int row, int col, int rectHeight, int rectWidth);
int kol_vo_Rectangles(int **matrix, int n);
int choice_func2(int n);

#endif
