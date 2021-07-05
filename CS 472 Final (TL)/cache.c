/****************************************************************************
 * Program: cache.c
 * Author: Tu Lam
 * Date: June 9th, 2021
 ***************************************************************************/

// All the definition of libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "./caches.h"


/*********************************************************
 * Function Name: int main()
 * Parameter(s): int argc, char *argv[]
 * Description: Run the entire cache simulator.
 ********************************************************/
int 
main(int argc, char *argv[]) {

	// Check to see if the user provide enough argument in the command line
	if (argc < 3) {
		printf("\nERROR! You did not provide enough arguments on the cmd line. Please provide as the following:\n");
		printf("Example: cache_sim  <config>  <trace>\n");
		printf("\n");
		exit(1);							
	}

	// Read in the file from the command line argv[1]
	char r_config[1000];
	memset(r_config, '\0', sizeof(r_config));

	FILE *stream1;
	stream1 = fopen(argv[1], "r");
	fread(&r_config, sizeof(char), 1000, stream1);
	fclose(stream1);

	// Calling the parse_config() function to parse data
	// [Also create variables to store in data]
	int L1 = 0, cyc = 0, set = 0, block = 0, assoc = 0;
	int replace = 0, write = 0, num_cyc = 0;
	parse_config(r_config, &L1, &cyc, &set, &block, &assoc, &replace, &write, &num_cyc);
	
	//printf("L1: %d, Cyc: %d, Set: %d, Block: %d, Assoc: %d, Re: %d, Wr: %d, Num_C: %d\n",
	//	    L1, cyc, set, block, assoc, replace, write, num_cyc);	

	// Read in the file from the command line argv[2]
	char r_trace[1000000];
	memset(r_trace, '\0', sizeof(r_trace));

	FILE *stream2;
	stream2 = fopen(argv[2], "r");
	fread(&r_trace, sizeof(char), 1000000, stream2);
	fclose(stream2);

	// Parsing the data of trace file into the correct index
	// [Create variable to store data]
	int cmd = 0;
	char inst[100000]; 
	int addr[100000], size[100000];
	
	// Set them to make sure they are 0 & call parse_trace() function;						
	memset(inst, '\0', sizeof(inst));
	memset(addr, 0, sizeof(addr));
	memset(size, 0, sizeof(size));
	parse_trace(r_trace, &inst[0], &addr[0], &size[0], &cmd);
	
	// Testing output (Work)
	//char *output_f = output_file(argv[2]);
	// FILE *out_t;
	//out_t = fopen(output_f, "a");
	/*for (int i = 0; i < cmd; i++) {
		printf("%d - Inst: %c,  Addr: %x,  Size: %d\n", i+1, inst[i], addr[i], size[i]);
	}*/
  	sim(cyc, set, block, assoc, replace, write, num_cyc, inst, addr, size, cmd, argv[2]);
	//fclose(out_t);

	return 0;
}


/*********************************************************
 * Function Name: void parse_config()
 * Parameter(s): char *config, int *L1, int *cyc, int *set, 
 *               int *block, int *assoc, int *replace, 
 *               int *write, int *num_cyc
 * Description: Parsing the data of the file "config"
 * 		       from argument in main().
 ********************************************************/
void 
parse_config(char *config, int *L1, int *cyc, int *set, int *block, int *assoc, int *replace, int *write, int *num_cyc) {

	// Begin to parse the data by reading the str
	// Store the L1 content
	char *token = strtok(config, "\n");
	*L1 = atoi(token);

	// Store the number of cycles [main memory]
	token = strtok(NULL, "\n");
	*cyc = atoi(token);

	// Store the number of sets in cache
	token = strtok(NULL, "\n");
	*set = atoi(token);

	// Store the block size
	token = strtok(NULL, "\n");
	*block = atoi(token);

	// Store the level of associativity
	token = strtok(NULL, "\n");
	*assoc = atoi(token);

	// Store the replacement policy
	token = strtok(NULL, "\n");
	*replace = atoi(token);

	// Store the write policy
	token = strtok(NULL, "\n");
	*write = atoi(token);

	// Store the number of cycles [cache]
	token = strtok(NULL, "\n");
	*num_cyc = atoi(token);
}


/*********************************************************
 * Function Name: void parse_trace()
 * Parameter(s): char *trace, char *inst, char *addr,
 *               int *size, int *cmd
 * Description: Parsing the data of the file "trace"
 * 		       from argument in main().
 ********************************************************/
void 
parse_trace(char *trace, char *inst, int *addr, int *size, int *cmd) {

	// Define couple variables to help out with the function
	int length = 0, counter = 0, x = 0, y = 0, z = 0;
	char tmp[100000];

	length = strlen(trace);						// Get the length of the str
	
	for (int i = 0; i < length; i++) {		// Make a "for" loop through the data 
		// Check to see if it is a '==' (Comment) or not
		if ((trace[i] == '=') && (trace[i + 1] == '=')) {
			continue;
		}

		// Check to see if the code found an instruction
		if (trace[i - 1] == ' ' && (trace[i] == 'M' || trace[i] == 'I' || trace[i] == 'S' || trace[i] == 'L') 
                                                                                    && trace[i + 1] == ' ') {
			inst[x] = trace[i];					// Assign the content at that idx
			x += 1;									// Increment the counter for x
			counter += 1;							// Also, increment the counter

			// Check to see if the file has the operation addr
			if ((isdigit(trace[i + 2]) != 0) || (isalpha(trace[i + 2]) != 0)) {
				int idx = 0;						// Create a tmp index & reset tmp str to 0
				memset(tmp, '\0', sizeof(tmp));
			
				// Create a "for" loop through the addr
				for (int j = i + 2; j < length; j++) {
					if ((isdigit(trace[j]) != 0) || (isalpha(trace[j]) != 0)) {
						tmp[idx] = trace[j];		// Assign the content to tmp
						idx += 1;					// Increment the tmp index
					}

					else if (trace[j] == ',') {	
						break;						// Break out of for loop if found ','
					}
				}
				// Convert to HEX and store in addr
				addr[y] = (int)strtol(tmp, NULL, 16);
				y += 1;								// Increment 'Y'
			}
		}

		// Check to see if it is the size of operation is there
		if ((trace[i] == ',') && (isdigit(trace[i + 1]) != 0)) {
			int t_idx = 0;							// Create a tmp index & reset str
			memset(tmp, '\0', sizeof(tmp));

			// Create a "for" loop to store the size of operation
			for (int k = i + 1; k < length; k++) {
				if (isdigit(trace[k]) != 0) {
					tmp[t_idx] = trace[k];		// Assign the content to tmp
					t_idx += 1;						// Increment the tmp index
				}

				else if ((trace[k] == '\n') || (trace[k] == '\0')) {
					break;							// Exit for loop, if '\n' or '\0'
				}
			}
			size[z] = atoi(tmp);					// Convert to int and assign to size[]
			z += 1;									// Increment the 'Z'
		}
	}
	
	*cmd = counter;								// Counter is assign to the cmd
}
