#pragma once 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define MAX_K 100           // Определение максимальной длины строки
#define BLUE "\033[0;34m"    // Определение цветовой схемы для вывода (синий)
#define RESET "\033[0m"      // Сброс цветовой схемы
#define MAX_K 100 // Максимальная длина строки

int is_phrase_palindrome(char *phrase);
int is_phrase_palindrome_recursive(char *phrase, int left, int right);
void print_words_in_phrase(char *phrase);
int get_val(char *prompt);
char ****mem_matrices(int n1, int n, int m);
void clear_matrices(char ****matrices, int n1, int n, int m);
void input_matrix(char ****matrices, int n1, int n, int m);
void print_matrix(char ****matrices, int n1, int n, int m);
void count_palindromes(char ****matrices, int n1, int n, int m, int *palindrome_counts);
void print_results(int *palindrome_counts, int n1);
int choice_func(int n);
int egor_strlen(char *str);
int egor_tolower(int c);