/**
 * Program that calculates the sinus from an angle in radians that it receives from the user
 *
 * 
 * @author Lior Kashanovsky
 */
#include <stdio.h>
#include <math.h>

#define PRECISION_POINT 0.000001

/**
 * Calculates the sinus of a given Radian, 
 * using the taylor series formula.
 * 
 * 
 * @return the sinus of a Radian
 */
double my_sin(double);

int main()
{
    double x;
    printf("Enter a value in Radians: \n");
    scanf("%lf", &x);
    /* Boundary Checks*/
    if (x < -25 || x > 25)
        printf("[-] Invalid Input - Not in Range ([-25, 25]) \n");
    else
    {
        printf("The entered value's sinus is (using custom function): %f \n", my_sin(x));
        printf("The entered value's sinus is (using library function): %f \n", sin(x));
    }
    return 0;
}

/**
 * Calculates the sinus of a given Radian, 
 * using the taylor series formula.
 * 
 * @param x angle in radians    
 * @return the sinus of a Radian
 */
double my_sin(double x)
{
    double sin = x, nextItem = x;
    double denominator;
    int i;
    /* Checking if we reached the desired precision point*/
    for (i = 1; PRECISION_POINT <= fabs(nextItem); i++)
    {
        /* instad of calculating every item's factorial, 
        we multiply the last item with x^2 divided by the missing product of the factorial
        for example:
        2nd taylor item: x^3 / 3!
        how we calculate:
        x_n = (x_n-1 * x^2) / (2n * (2n + 1))
        => x_2 = (x_1 * x^2) / (2 * 3) = (x / 1) * (x^2 / 2 * 3) = x^3 / 1 * 2 * 3 = x^3 / 3!
        */
        denominator = 2 * i * ((2 * i) + 1);
        nextItem = (-nextItem * x * x) / denominator;
        sin += nextItem;
    }
    return sin;
}