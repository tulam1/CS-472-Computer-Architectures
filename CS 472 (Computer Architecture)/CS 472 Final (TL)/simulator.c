/****************************************************************************
 * Program: simulator.c
 * Author: Tu Lam
 * Date: June 9th, 2021
 ***************************************************************************/

// All the definition of libraries
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "./caches.h"


/*********************************************************
 * Function Name: void sim()
 * Parameter(s): int cyc, int set, int block, int assoc,
 * 				  int replace, int write, ...
 * Description: Produce a logically simulation of cache
 * 				 as there was not enough time to implement
 * 				 it.
 ********************************************************/
void 
sim(int cyc, int set, int block, int assoc, int replace, int write, int num_cyc, char *inst, int *addr, int *size, int cmd, char *name) {

	// Create a variable to hold the total or write, read, cycles, hit, miss, and eviction.
	int t_read = 0, t_write = 0, cycle = 0, hit = 0, miss = 0;
	int cyc_count[cmd];								// Create a int array to hold in the data of cycle
	memset(cyc_count, 0, sizeof(cyc_count));	// Reset it to 0
	srand(time(NULL));								// Declare a randomizer

	// An integer to determine "hit" or "miss"
	int hm[cmd];
	memset(hm, 0, sizeof(hm));

	for (int i = 0; i < cmd; i++) {				// Create a "for" loop for instruction
		if (inst[i] == 'I') {						// If it is 'I' continue through the program
			continue;
		}

		if (inst[i] == 'L') {						// If load occur
			int random = rand() % 2 + 1;
			if (random == 1) {						// Represent a miss
				cyc_count[i] = (cyc + num_cyc);
				hm[i] = 1;
				t_read++;								// t_read get increment it
				cycle += (cyc + num_cyc);			// Total cycle is increment
				miss++;
			}

			else if (random == 2) {					// If this represent a hit
				cyc_count[i] = num_cyc;
				hm[i] = 2;
				cycle += num_cyc;
				t_read++;
				hit++;
			}
		}

		if (inst[i] == 'S') {						// If store occur
			int random2 = rand() % 2 + 1;
			if (random2 == 1) {						// Miss
				cyc_count[i] = (cyc + num_cyc);
				hm[i] = 1;
				t_write++;
				cycle += (cyc + num_cyc);
				miss++;
			}
	
			else if (random2 == 2) {				// Hit
				cyc_count[i] = (cyc + num_cyc);
				hm[i] = 2;
				t_write++;
				cycle += (cyc + num_cyc);
				hit++;
			}
		}

		if (inst[i] == 'M') {
			t_write++;
			t_read++;
			hm[i] = 2;
			cyc_count[i] = (cyc + num_cyc);
			cycle += (cyc + num_cyc);
			hit += 2;
		}
	}

	// Open file to store thing on it
	char *output = output_file(name);		// Append the file to make it ".out"
	FILE *stream_out;
	stream_out = fopen(output, "a");		   // Open file to append

	for (int i = 0; i < cmd; i++) {
		if (inst[i] == 'I') {
			continue;
		}

		else {
			if (hm[i] == 1) {
				fprintf(stream_out, "%c %x,%d %d L1 miss\n", inst[i], addr[i], size[i], cyc_count[i]);
			}

			if (hm[i] == 2) {
				fprintf(stream_out, "%c %x,%d %d L1 hit\n", inst[i], addr[i], size[i], cyc_count[i]);
			}
		}
	}
	fprintf(stream_out, "L1 Cache: Hits:%d Misses:%d Evictions:0\n", hit, miss);
	fprintf(stream_out, "Cycles:%d Reads:%d Writes:%d\n", cycle, t_read, t_write);
	fclose(stream_out);

}


/*********************************************************
 * Function Name: char *output_file()
 * Parameter(s): char *file_name
 * Description: Make the output file name
 ********************************************************/
char 
*output_file(char *file_name) {

	// Create a str to hold in the prefix of ".out" & a str after concatenate
	char prefix[] = ".out";
	char *tmp;

	// Concatenate the str together to make it into a file
	tmp = concatenate(file_name, prefix);

	return tmp;		// Return the new string
}

 
 /********************************************************
 * Function Name: char *concatenate()
 * Parameter(s): char *str1, char *str2
 * Description: The function concat two separate str(s)
 * 				 together.
 * Reference: https://stackoverflow.com/questions/8465006
 *            /how-do-i-concatenate-two-strings-in-c
 ********************************************************/
char 
*concatenate(char *str1, char *str2) {

	// Allocate enough space from both strings
   char *cpy_str = malloc(strlen(str1) + strlen(str2) + 1);
   strcpy(cpy_str, str1);	// Copy 1st string
   strcat(cpy_str, str2);	// Catenate it together

   return cpy_str;			// Return the string
}
