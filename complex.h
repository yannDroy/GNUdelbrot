#include <stdio.h>
#include <stdlib.h>

typedef struct complex {
    double re;
    double im;
} complex;

complex add (complex c1, complex c2);

complex square (complex c);

complex next_term (complex z, complex c);
complex next_term2 (complex z, complex c);
complex next_term3 (complex z, complex c);

double magnitude (complex c);
