#include <stdio.h>

/**
 * add_numbers - Adds two numbers.
 * @a: The first number.
 * @b: The second number.
 *
 * Return: The sum of a and b.
 */
int add_numbers(int a, int b)
{
return (a + b);
}

/**
 * main - Entry point of the program.
 *
 * Return: 0 on success.
 */
int main(void)
{
int num1 = 5;
int num2 = 7;
int sum;

sum = add_numbers(num1, num2);
printf("The sum of %d and %d is %d\n", num1, num2, sum);

return (0);
}
