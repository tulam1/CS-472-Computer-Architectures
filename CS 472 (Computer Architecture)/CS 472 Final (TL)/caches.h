/****************************************************************************
 * Program: caches.h
 * Author: Tu Lam
 * Date: June 9th, 2021
 ***************************************************************************/

// All the definition of libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// All the functions declaration
void sim(int cyc, int set, int block, int assoc, int replace, int write, int num_cyc, char *inst, int *addr, int *size, int cmd, char *name);
void parse_config(char *config, int *L1, int *cyc, int *set, int *block, int *assoc, int *replace, int *write, int *num_cyc);
void parse_trace(char *trace, char *inst, int *addr, int *size, int *cmd);
char *output_file(char *file_name);
char *concatenate(char *str1, char *str2);
