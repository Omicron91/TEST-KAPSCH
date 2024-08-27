# include "factorization.h"


void factorize(uint16_t num, int *len, uint16_t *factors)
{
    *len = 0;

    if (num < 2)
    {
        factors[0] = num;
        (*len)++;
        return;
    }

    for (uint16_t i = 2; i <= num; i++)
    {
        if (factors[0] == 0 && i >= sqrt(num))
        {
            /* There is no more factors to find => Is a prime number*/
            factors[0] = num;
            (*len)++;
            return;
        }
        /* Look for all factors for each 'i' */
        while (num % i == 0)
        {
            factors[*len] = i;
            (*len)++;
            num /= i;
        }
    }
}
