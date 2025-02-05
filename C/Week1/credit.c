#include <stdio.h>
#include <cs50.h>

int check_sum(long pin);
int get_pin_length(long pin);

int main(void)
{
    long pin = get_long("Number: ");

    check_sum(pin);
}

int get_pin_length(long pin)
{
    int count = 0;
    while (pin != 0)
    {
        pin /= 10;
        count++;
    }
    return count;
}

int check_sum(long pin)
{
    int last_digit;
    int count = 0;
    int sum1 = 0;
    int sum2 = 0;

    while (pin != 0)
    {
        last_digit = pin % 10;
        pin /= 10;

        if (count % 2 == 1)
        {
            int last_digit_doubled = last_digit * 2;
            while (last_digit_doubled != 0)
            {
                sum1 += last_digit_doubled % 10;
                last_digit_doubled /= 10;
            }
        }
        else
        {
            sum2 += last_digit;
        }

        count++;
    }

    printf("sum1: %i, sum2: %i\n", sum1, sum2);
    if ((sum1 + sum2) % 10 == 0)
    {
        printf("VALID\n");
    }
    else
    {
        printf("INVALID\n");
    }
}