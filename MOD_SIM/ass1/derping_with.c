#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

int main(int argc, char* argv[]){
    float float_std;
    double double_std;
    long double long_double_std;

    int size_float;
    int size_double;
    int size_long_double;

    size_float = sizeof(float_std);
    size_double = sizeof(double_std);
    size_long_double = sizeof(long_double_std);
    printf("Size of float: %d\n", size_float);
    printf("Size of double: %d\n", size_double);
    printf("Size of long double: %d\n", size_long_double);

    printf("\n");

    float max_mantissa_float;
    int max_exp;
    float max_float;
    max_mantissa_float = 1 + 0b11111111111111111111111 * pow(2,-23);
    max_exp = 0b11111110;
    max_float = max_mantissa_float * pow(2, max_exp - 127);
    printf("Max float: %g\nActual max: %g\n", max_float, FLT_MAX);

    float min_mantissa_float;
    int min_exp;
    float min_float;
    min_mantissa_float = 1 + 0b00000000000000000000000 * pow(2,-23);
    min_exp = 0b00000001;
    min_float = min_mantissa_float * pow(2, min_exp - 127);
    printf("Min float: %g\nActual min: %g\n", min_float, FLT_MIN);

    printf("\n");

    double max_mantissa_double;
    double max_double;
    max_mantissa_double = 1 + 
        0b1111111111111111111111111111111111111111111111111111 * pow(2, -52);
    max_exp = 0b11111111110;
    max_double = max_mantissa_double * pow(2, max_exp - 1023);
    printf("Max double: %g\nActual max: %g\n", max_double, DBL_MAX);

    double min_mantissa_double;
    double min_double;
    min_mantissa_double = 1 + 
        0b0000000000000000000000000000000000000000000000000000 * pow(2,-52);
    min_exp = 0b00000000001;
    min_double = min_mantissa_double * pow(2, min_exp - 1023);
    printf("Min Double: %g\nActual min: %g\n", min_double, DBL_MIN);

    printf("\n");

    long double max_mantissa_long_double;
    long double max_long_double = 1;
    // max_mantissa_long_double = 1 + 
    //     0b1111111111111111111111111111111111111111111111111111111111111111 * 
    //         pow(2, -52);
    // max_exp = 0b111111111111110;
    // max_long_double = max_mantissa_long_double * pow(2, max_exp - 1023);
    printf("Max double: %lf\nActual max: %Lf\n", max_long_double, LDBL_MAX);

    long double min_mantissa_long_double;
    long double min_long_double;
    min_mantissa_long_double = 1 + 
        0b0000000000000000000000000000000000000000000000000000 * pow(2,-52);
    min_exp = 0b00000000001;
    min_long_double = min_mantissa_long_double * pow(2, min_exp - 1023);
    printf("Min Double: %lf\nActual min: %lf\n", min_long_double, LDBL_MIN);

    union
    {
        int i;
        long double f;
    } u;

}