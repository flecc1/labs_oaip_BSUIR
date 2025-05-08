#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>


// Цвета для терминала
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

int getValidInt(int min, int max);
void readString(char *buffer, int max_length);
float getValidFloat(int min, int max);
void getValidString(char **str);
int my_strlen(const char *s);
char* optimizeString(char *str);
char** mem_str(int count, int string_length);
int restart_choice_func(int n);
int isSameString(const char *s1, const char *s2);