#include "sqrt.h"

double SquareRoot(double value)
{
	float lower, middle, higher;
	
	lower = 0;
	higher = value;
	middle = value / 2;
	
	while (((value - (middle*middle)) > 0.00001) || (((middle*middle)) - value > 0.00001))		/* Checks if the guess value is within error range */
	{
		middle = lower + ((higher - lower) / 2);		/* bisects the interval to get the new guess value */
		
		if (value > (middle*middle))				/* if the guess is too low */
		{
			lower = middle;
		}
		else if (value < (middle*middle))			/* if the guess is too high */
		{
			higher = middle;
		}
		else if (value == (middle*middle))			/* if the guess is correct */
		{
			return middle;
		}	
	}

	return middle;	
	
}

/* EOF */
