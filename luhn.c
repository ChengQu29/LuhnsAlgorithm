#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

long get_long(const char *prompt);
void validate(long number);
bool is_valid(int check_sum);
int first_two_digits(long number);

int main(void)
{

    long number = get_long("Number: ");
    validate(number);
    printf("You entered: %ld\n", number);
    return 0;

}

long get_long(const char *prompt)
{
    long number;
    char term;
    bool valid_input = false;

    while (!valid_input)
    {
        printf("%s", prompt);
        if (scanf("%ld%c", &number, &term) != 2 || (term != '\n' && term != '\0'))
        {
            printf("Invalid input. Please enter a valid long integer.\n");
            // Clear input buffer
            while (getchar() != '\n');
        }
        else if (number < LONG_MIN || number > LONG_MAX)
        {
            printf("Input out of range. Please enter a valid long integer.\n");
        }
        else
        {
            valid_input = true;
        }
    }

    return number;
}

void validate(long number) {

    long original_number = number;

    int num_digits = 0;

    int harvest_second_last = 0;

    int harvest_rest = 0;

    int position = 0 ;

    int count_digits = 0;

    int second_last_total = 0;

    int rest_total = 0;

    int check_sum_less_last_digit = 0;

    int check_sum = 0;

    int last_digit = 0;

    last_digit = number%10;

    while (number > 0) {

        number = number / 10; //floor division in C , same as // in python e.g 12345/10 = 1234

        if (position % 2 == 0 ) { //e.g. 12345%10=5
            harvest_second_last = number % 10;

            //need to add products' digits i.e. not the products themselves together here:
            int double_digit = harvest_second_last*2;
            second_last_total += (double_digit > 9) ? (double_digit - 9) : double_digit;
            //printf("Harvest second last: %i\n", harvest_second_last);

        } else {
            harvest_rest = number%10;
            rest_total += harvest_rest;
            //("Harvest rest: %ld\n", number%10);
        }

        position++;
        count_digits++;
    }

    check_sum_less_last_digit = second_last_total + rest_total;
    check_sum += check_sum_less_last_digit + last_digit;

    //printf("Last digit: %i\n", last_digit);
    //printf("Second last total: %i\n", second_last_total);
    //printf("Rest total: %i\n", rest_total);
    //printf("check sum: %i\n", check_sum);

    int first_two = first_two_digits(original_number);

    if (is_valid(check_sum)) {
        if (first_two == 34 || first_two == 37) {
            if (count_digits == 15) {
                printf("AMEX\n");
            } else {
                printf("INVALID\n");
            }
        }
        else if (first_two == 51 || first_two == 52 || first_two == 53 || first_two == 54 || first_two == 55)
        {
            printf("MASTERCARD\n");

        } else if (first_two/10 == 4) {

            if (count_digits == 13 || count_digits == 16) {
                printf("VISA\n");
            } else {
                printf("INVALID\n");
            }
        } else {
            printf("INVALID\n");
        }

    } else {
        printf("INVALID\n");
    }
}

int first_two_digits(long number) {
    // Continue dividing the number by 10 until it has only two digits
    while (number >= 100) {
        number /= 10;
    }

    return (int)number;
}

bool is_valid(int check_sum) {

    if (check_sum % 10 == 0) {
        return true;
    } else {
        return false;
    }

}
