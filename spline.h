#pragma once

#include <cmath.h>

int spline (int n, int end1, int end2,
            double slope1, double slope2,
            double x[], double y[],
            double b[], double c[], double d[],
            int *iflag);
double seval (int n, double u,
              double x[], double y[],
              double b[], double c[], double d[],
              int *last);