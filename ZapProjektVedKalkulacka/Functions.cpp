#include "Functions.h"



void quadraticFunction(struct CalcStatus* status) {
	double a = status->numbers[0];
	double b = status->numbers[1];
	double c = status->numbers[2];
	double D = b * b - 4 * a * c;
	double koren[2];

	system("cls");
	printf("Rovnice: %.2lfx^2 + (%.2lfx) + (%.2lf) = 0\n", a, b, c);
	if (D > 0) {
		koren[0] = (-b + sqrt(D)) / (2 * a);
		koren[1] = (-b - sqrt(D)) / (2 * a);
		snprintf(status->kvadRovniceKoreny, 1024, "koreny: x_1 = %lf x_2 = %lf\n", koren[0], koren[1]);
		printf("\nKoreny:\nx_1 = %.2lf \nx_2 = %.2lf\n\n", koren[0], koren[1]);
	}
	else if (D == 0) {
		koren[0] = -b / (2 * a);
		snprintf(status->kvadRovniceKoreny, 1024, "koren je zdvojeny: x_1 = x_2 = %.2lf\n", koren[0]);
		printf("Koren je dvojity:\nx_1 = x_2 = %.2lf\n", koren[0]);
	}

	else {
		double realniCast = -b / (2 * a);
		double komplexniCast = sqrt(-D) / (2 * a);
		snprintf(status->kvadRovniceKoreny, 1024, "komplexni koreny: x_1 = %.2lf+%.2lfi and x_2 = %.2f-%.2fi\n", realniCast, komplexniCast, realniCast, komplexniCast);
		printf("\nKomplexni koreny: \nx_1 = %.2lf+%.2lfi\nx_2 = %.2f-%.2fi\n\n", realniCast, komplexniCast, realniCast, komplexniCast);
	}

}

double factorial(double input) {
	int converted_input = (int)input;
	int output = 1;
	if (converted_input == 0) {
		return 1;
	}
	for (int i = 1; i <= converted_input; i++) {
		output = output * i;
	}
	return (double)output;
}

int executeFunction(CalcStatus* status) {

	switch (status->funcType) {
	case NaturalLog:
		status->currentOutcome = log(status->numbers[0]);
		return 0;
	case Log10:
		status->currentOutcome = log10(status->numbers[0]);
		return 0;
	case LogChooseBase:
		status->currentOutcome = log2(status->numbers[0]) / log2(status->numbers[1]);
		return 0;
	case Factorial:
		system("cls");
		printf("Zvolili jste faktorial, prevadim na nejblizsi celou hodnotu.\n");
		status->currentOutcome = factorial(status->numbers[0]);
		return 0;
	case sinus:
		status->currentOutcome = sin(status->numbers[0]);
		return 0;
	case cosinus:
		status->currentOutcome = cos(status->numbers[0]);
		return 0;
	case tangens:
		status->currentOutcome = tan(status->numbers[0]);
		return 0;
	case exponential:
		status->currentOutcome = pow(status->numbers[0], status->numbers[1]);
		return 0;
	default:
		printf("Nastala neocekavana chyba!\n");
		return 1;
	}
}
