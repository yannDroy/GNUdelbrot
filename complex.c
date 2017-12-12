#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "complex.h"

complex add (complex c1, complex c2){
    complex sum;

    sum.re = c1.re + c2.re;
    sum.im = c1.im + c2.im;

    return sum;
}

complex mult (complex c1, complex c2){
    complex product;

    product.re = (c1.re * c2.re) - (c1.im * c2.im);
    product.im = (c1.re * c2.im) + (c1.im * c2.re);

    return product;
}

complex square (complex c){
    complex sq;

    sq.re = (c.re * c.re) - (c.im * c.im);
    sq.im = (c.re * c.im) + (c.im * c.re);

    return sq;
}

complex conjugate (complex z){
    complex conj;

    conj.re = z.re;
    conj.im = -z.im;

    return conj;
}

complex complex_sinh (complex z){
    complex s;

    s.re = sinh(z.re) * cos(z.im);
    s.im = cosh(z.re) * sin(z.im);

    return s;
}

complex complex_root (complex z){
    complex r;

    r.re = -sqrt(0.5 * (z.re + sqrt(z.re*z.re + z.im*z.im)));
    r.im = -(z.im / (2 * sqrt(0.5 * (z.re + sqrt(z.re*z.re + z.im*z.im)))));

    return r;
}

double magnitude (complex c){
    return sqrt((c.re * c.re) + (c.im * c.im));
}

complex complex_expo (complex z){
    complex e;

    e.re = exp(z.re) * cos(z.im);
    e.im = exp(z.re) * sin(z.im);

    return e;
}

complex next_term3 (complex z, complex c){
    return add(mult(square(square(z)), complex_expo(z)), c);
}
complex next_term2 (complex z, complex c){
    return add(mult(square(z), z), c);
}
complex next_term (complex z, complex c){
    return add(square(z), c);
}
