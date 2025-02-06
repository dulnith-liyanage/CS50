#include <stdio.h>
#include <cs50.h>

int get_pin_length(long pin);
bool check_sum(long pin);

int get_first_digit(long pin);
int get_second_digit(long pin);
int get_first_two_digits(int first_digit, int second_digit);
string get_card_type(long pin);

int main(void)
{
    long pin = get_long("Number: ");
    string card_type = get_card_type(pin);
    printf("%s\n", card_type);
}

string get_card_type(long pin)
{
    int pin_length = get_pin_length(pin);
    int first_digit = get_first_digit(pin);
    int second_digit = get_second_digit(pin);
    int first_two_digits = get_first_two_digits(first_digit, second_digit);

    if (check_sum(pin))
    {

        if (pin_length == 15 && (first_two_digits == 34 || first_two_digits == 37))
        {
            return "AMEX";
        }
        else if (pin_length == 13 && first_digit == 4)
        {
            return "VISA";
        }
        else if (pin_length == 16)
        {
            if (first_two_digits == 51 || first_two_digits == 52 || first_two_digits == 53 || first_two_digits == 54 || first_two_digits == 55)
            {
                return "MASTERCARD";
            }
            else if (first_digit == 4)
            {
                return "VISA";
            }
            else
            {
                return "INVALID";
            }
        }
        else
        {
            return "INVALID";
        }
    }
    else
    {
        return "INVALID";
    }
}

int get_first_two_digits(int first_digit, int second_digit)
{
    int first_two_digits = first_digit * 10 + second_digit;
    return first_two_digits;
}

int get_first_digit(long pin)
{
    int pin_length = get_pin_length(pin);
    int first_digit;
    for (int i = 0; i < pin_length; i++)
    {
        first_digit = pin % 10; // Used to obtain the last digit in the pin
        pin /= 10;              // Removes the last digit
    }
    return first_digit;
}

int get_second_digit(long pin)
{
    int pin_length = get_pin_length(pin);
    int second_digit;

    for (int i = 0; i < pin_length - 1; i++)
    {
        second_digit = pin % 10; // Used to obtain the last digit in the pin
        pin /= 10;               // Removes the last digit
    }
    return second_digit;
}

int get_pin_length(long pin)
{
    int count = 0;
    while (pin != 0)
    {
        pin /= 10; // Removes the last digit in the pin
        count++;   // Used to determine the length of the pin
    }
    return count;
}

bool check_sum(long pin)
{
    int last_digit;
    int count = 0;
    int sum1 = 0;
    int sum2 = 0;

    while (pin != 0)
    {
        last_digit = pin % 10; // Used to obtain the last digit in the pin
        pin /= 10;             // Removes the last digit

        // Used to differentiate odd and even digits starting from the second to last digit
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

        count++; // Used to move thorugh each single digit
    }

    if ((sum1 + sum2) % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}