/**********************************************************************
 * Program: amicable.c
 * Author: Tu Lam
 * Date: April 10th, 2021
 * Description: A short C code written to find two integers that form
 * 				 an amicable pair together.
 *********************************************************************/

// Pre-defined library goes here

// Any define function(s) goes here


/***********************************************************************
	Returns 1 if the two integers form an amicable pair, 0 otherwise.
	This code needs to function correctly regardless of the ordering.
	For example, check_amicable(220, 284) should return 1, as should
	check_amicable(284, 220).
	This function must work correctly for all integers up to 2 billion.
	Be sure that the function prototype remains intact.
***********************************************************************/
int check_amicable(int a, int b) {
	int sum = 0;									// Create a var to hold in the sum of the total

	for (int i = 1; i < a; i++) {				// Create a loop to find the number divisor
		if ((a % i) == 0) {						// If there's no remainder, add to sum
			sum = sum + i;
		}
	}
		
	// This part check for the sum to the integer b to see if it is
	// an amicable pair
	if (sum == b) {								// If true, return 1
		return 1;
	}

	else {											// Else, return 0
		return 0;
	}
}


/**************************************************************************
	Short program to determine whether two numbers form an amicable pair.
	Do not change the code below (except for the values of num_a and num_b)
**************************************************************************/
int main() {
	const int num_a = 1982313333;
	const int num_b = 1892277387;

	return check_amicable(num_a, num_b);
}
