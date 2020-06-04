#include <stdio.h>
#include <stdlib.h>

#include "sqrt.h"

int main()
{
	double input;	/* user input variable */

	printf("%s", "Please enter a positive real number: ");
	scanf("%lf", &input);
	
	printf("%s%lf\n", "The square root is ", SquareRoot(input));

	return 0;
}

/* EOF */
