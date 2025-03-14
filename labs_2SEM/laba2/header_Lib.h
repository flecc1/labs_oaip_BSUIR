#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>


int getValidInt(int min, int max);
void readString(char *buffer, int max_length);
float getValidFloat(int min, int max);
void getValidString(char **str);
int my_strlen(const char *s);
char* optimizeString(char *str);
int restart_choice_func(int n);