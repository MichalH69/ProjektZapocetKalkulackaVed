
#pragma once
#include "ZapProjektVedKalkulacka.h"


int main()
{
	struct CalcStatus status = { .currentOutcome = 0, .numbers = (0, 0, 0), .memory = (0, 0, 0, 0), .numOfOperators = 1, .arithmeticOperType = NoAri, .operationType = NoOp, .funcType = NoFunc, .firstWrite = 0, .prevod =""};
	status.currentOutcome = 0;
	char contCalc = 'a';

	while (true) {
		if (intro(&status) == -1) {
			return -1;
		}

		system("cls");

		if (getNumbers(&status) == -1) {
			return -1;
		}

		switch (status.operationType) {

		case Aritmeticka:
			arithmeticOperation(&status);
			break;

		case Funkce:
			executeFunction(&status);
			break;

		case Konverze:
			conversion(&status);
			break;

		case KvardatickaRovnice:
			quadraticFunction(&status);
			break;
		
		default:
			break;
		}

		if (printOutcome(&status) != 0) {
			printf("Neocekavana chyba");
			return 1;
		}

		writeIntoHistory(&status);
		printf("Prejete si pokracovat v dalsi operaci? (a/n): ");
		scanf(" %c", &contCalc);
		system("cls");

		if (contCalc == 'n') {
			break;
		}
	}
	return 0;
}

void writeIntoHistory(struct CalcStatus* status) {
	char path[100] = "";
	FILE *f;

	if (status->firstWrite == 0) {
		fopen_s(&f,"history.txt", "a");
		status->firstWrite = 1;
	}
	else {
		fopen_s(&f, "history.txt", "w");
	}


	if (status->operationType == Funkce) {

		if (status->funcType == LogChooseBase || status->funcType == exponential) {
			fprintf(f, "Typ Operace: %s Typ funkce: %s inputs: %.2lf %.2lf Outcome: %.2lf\n", opTypeStr[status->operationType], funcTypeStr[status->funcType], status->numbers[0], status->numbers[1], status->currentOutcome);
			fflush(f);
		}
		else {

			fprintf(f, "Typ Operace: %s Typ funkce: %s input: %lf Outcome: %lf\n", opTypeStr[status->operationType], funcTypeStr[status->funcType], status->numbers[0], status->currentOutcome);
			fflush(f);
		}
		
	}

	if (status->operationType == Aritmeticka) {
		fprintf(f, "Typ Operace: %s Typ Aritmeticke operace: %s inputs: %.2lf %.2lf Outcome: %.2lf\n", opTypeStr[status->operationType], ariOpTypeStr[status->funcType], status->numbers[0], status->numbers[1], status->currentOutcome);
		fflush(f);
	}

	if (status->operationType == Konverze) {
		fprintf(f, "Typ Operace: %s Prevod: %s input: %.2lf Outcome: %.2lf\n", opTypeStr[status->operationType], status->prevod,  status->numbers[0], status->currentOutcome);
		fflush(f);
	}

	if (status->operationType == KvardatickaRovnice) {

		fprintf(f, "Typ Operace: %s Rovnice %lfx^2 + (%lfx) + (%lf) %s\n", opTypeStr[status->operationType], status->numbers[0], status->numbers[1], status->numbers[2], status->kvadRovniceKoreny);

		fflush(f);
	}
	
	fclose(f);
}


















