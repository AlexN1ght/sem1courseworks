#include <stdio.h>
#include <math.h>

double eps = 7.0 / 3.0 - 4.0 / 3.0 - 1.0;

double f1(double x) {
	return(x * tan(x) - 1.0 / 3.0);
}

double f2(double x) {
	return(tan(x / 2.0) - 1 / tan(x / 2.0) + x);
}

double pr1(double x) {
	return(tan(x) + x / pow(cos(x), 2));
}

double pr2(double x) {
	return(1 / pow(cos(x / 2), 2) + 1 / pow(sin(x / 2), 2) + 1);
}

double Fx_x1(double x) {
	return(x - 1 * (x * tan(x) - 1.0 / 3.0));
}

double Fx_x2(double x) {
	return(x - 0.001 * (tan(x / 2.0) - 1 / tan(x / 2.0) + x));
}

double DEH(double f(double x), double a, double b) {
	double c;
	while (fabs(a - b) > eps * 2) {
         c = (a + b) / 2.0;
         if (f(a) * f(c) > 0) {
         	a = c;
         } else b = c;
	}
	return c;
}

double IT(double Fx_x(double x), double a, double b) {
	double x = (a + b) / 2.0;
	double x1;
	do {
		x1 = x;
		x = Fx_x(x);
		//printf("%.20lf\n", x);
		}while(fabs(x1 - x) > fabs(eps));
	return x;
}

double NEW(double f(double x),double pr(double x), double a, double b) {
    double x = (a + b) / 2.0;
    double x1 = x + 1.0;
    while(fabs(x1 - x) > eps) {
    	x1 = x;
    	x = x - f(x) / pr(x);
    }
    return x;

}

int main(void)
{
	printf("DEH\t\t\tIT\t\tNEW\n");	
	printf("%.15f %.15f %.15f\n", DEH(f1, 0.2, 1.0), IT(Fx_x1, 0.2, 1.0), NEW(f1, pr1, 0.2, 1.0));
	printf("%.15f %.15f %.15f\n", DEH(f2, 1.0, 2.0), IT(Fx_x2, 1.0, 2.0), NEW(f2, pr2, 1.0, 2.0));
	return 0;
}