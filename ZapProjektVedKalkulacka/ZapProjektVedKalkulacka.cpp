// kalkulacka_ved.cpp : Defines the entry point for the application.
//

#include "ZapProjektVedKalkulacka.h"



#include <math.h>
#include <iostream>
#include <stdio.h>





int main()
{
	struct CalcStatus status = { .currentOutcome = 0, .numbers = (0, 0, 0), .memory = (0, 0, 0, 0), .numOfOperators = 1, .arithmeticOperType = NoAri, .operationType = NoOp, .funcType = NoFunc, .firstWrite = 0, };
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
			printf("unexpected error occured");
			return 1;
		}
		printf("vstupy: %lf %lf %lf\n", status.numbers[0], status.numbers[1], status.numbers[2]);
		printf("pamet: %lf %lf %lf %lf\n", status.memory[0], status.memory[1], status.memory[2], status.memory[3]);

		printf("Prejete si pokracovat v dalsi operaci?\n");
		scanf(" %c", &contCalc);

		if (contCalc == 'n') {
			break;
		}
	}
	return 0;
}


void quadraticFunction(struct CalcStatus* status) {
	double a = status->numbers[0];
	double b = status->numbers[1];
	double c = status->numbers[2];
	double D = b * b - 4 * a * c;
	double koren[2];
	printf("rovnice: %lfx^2 + (%lfx) + (%lf)\n", a, b, c);
	if (D > 0) {
		koren[0] = (-b + sqrt(D)) / (2 * a);
		koren[1] = (-b - sqrt(D)) / (2 * a);
		printf("koreny:\nx_1 = %lf \nx_2 = %lf\n", koren[0], koren[1]);
	}
	else if (D == 0) {
		koren[0] = -b / (2 * a);
		printf("koren je zdvojeny:\nx_1 = x_2 = %.2lf\n", koren[0]);
	}

	else {
		double realniCast = -b / (2 * a);
		double komplexniCast = sqrt(-D) / (2 * a);
		printf("komplexni koreny:\nx_1 = %.2lf+%.2lfi and x_2 = %.2f-%.2fi\n", realniCast, komplexniCast, realniCast, komplexniCast);
	}


}
int conversion(struct CalcStatus* status) {

	int jakyPrevod = 0;
	char jednotka1[10] = "";
	char jednotka2[10] = "";
	int zadanyPrevod = 0;
	double input = status->numbers[0];
	printf("Co si prejete prevest?\n1 - C na F\n2 - F na C\n3 - C na K\n4 - F na K\n5 - K na C\n6 - K na F\n7 - Stupne na radiany\n8 - Radiany na stupne\n");


	while (zadanyPrevod == 0) {
		if (scanf(" %d", &jakyPrevod) != 1) {
			printf("invalid input!, Enter new value\n");
			continue;
		}
		switch (jakyPrevod)
		{
		case 1:
			printf("INPUT: %lf\n", input);
			status->currentOutcome = (input * 1.8) + 32;
			strcpy(jednotka1, "C");
			strcpy(jednotka2, "F");
			zadanyPrevod = 1;
			strcpy(status->prevod, "C na F");
			printf("curr outcome %lf \n", status->currentOutcome);
			break;
		case 2:
			status->currentOutcome = (input - 32) * 5 / 9;
			strcpy(jednotka1, "F");
			strcpy(jednotka2, "C");
			zadanyPrevod = 1;
			strcpy(status->prevod, "F na C");
			break;
		case 3:
			status->currentOutcome = input + 273.15 ;
			strcpy(jednotka1, "C");
			strcpy(jednotka2, "K");
			zadanyPrevod = 1;
			strcpy(status->prevod, "C na K");
			break;
		case 4:
			status->currentOutcome = ((input - 32) * 5 / 9) + 273.15;
			strcpy(jednotka1, "F");
			strcpy(jednotka2, "K");
			zadanyPrevod = 1;
			strcpy(status->prevod, "F na K");
			break;
		case 5:
			status->currentOutcome = input - 273.15;
			strcpy(jednotka1, "K");
			strcpy(jednotka2, "C");
			zadanyPrevod = 1;
			strcpy(status->prevod, "K na C");
			break;
		case 6:
			status->currentOutcome = (input - 273.15) * 1.8 + 32;
			strcpy(jednotka1, "K");
			strcpy(jednotka2, "F");
			zadanyPrevod = 1;
			strcpy(status->prevod, "K na F");
			break;
		case 7:
			status->currentOutcome = input * 0.01745329;
			strcpy(jednotka1, "s");
			strcpy(jednotka2, "r");
			zadanyPrevod = 1;
			strcpy(status->prevod, "Stupne na rad");
			break;
		case 8:
			status->currentOutcome = input * 57.2957795;
			strcpy(jednotka1, "r");
			strcpy(jednotka2, "s");
			zadanyPrevod = 1;
			strcpy(status->prevod, "Rad na stupne");
			break;
		default:
			printf("\nZadali jste nespravny vstup.");
			break;
		}
		if (zadanyPrevod == 0) {
			printf("Co si prejete prevest?\n1 - C na F\n2 - F na C\n3 - C na K\n4 - F na K\n5 - K na C\n6 - K na F\n7 - Stupne na radiany\n8 - Radiany na stupne");
			scanf("@%*[^\n]");
		}
		else {
			break;
		}
	}
	printf("%lf%s je %lf%s", input, jednotka1, status->currentOutcome, jednotka2);

	return 0;
}

int printOutcome(struct CalcStatus* status) {

	if (status->operationType == KvardatickaRovnice) {
		return 0;
	}
	if (status->operationType != Konverze) {
		printf("Vysledek operace: %lf", status->currentOutcome);
	}

	char saveOutcome = ' ';
	printf("chcete ulozit vysledek do pameti? y/n\n");
	while (true) {
		scanf(" %c", &saveOutcome);
		system("cls");
		if (saveOutcome != 'y' && saveOutcome != 'n') {
			printf("nevalidni input! Zadejte znova\n");
			printf("save outcome: %c\n", saveOutcome);
			printf("chcete ulozit status->currentOutcome do pameti? y/n\n");
			scanf("%*[^\n]");
		}
		else {
			break;
		}
	}
	if (saveOutcome == 'y') {
		enterOutcomeIntoMemory(status);
	}
	return 0;
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
	case 1:
		status->currentOutcome = log(status->numbers[0]);
		return 0;
	case 2:
		status->currentOutcome = log10(status->numbers[0]);
		return 0;
	case 3:
		status->currentOutcome = log2(status->numbers[0]) / log2(status->numbers[1]);
		return 0;
	case 4:
		printf("You chose factorial, converting your input number to closest integer\n");
		status->currentOutcome = factorial(status->numbers[0]);
		return 0;
	case 5:
		status->currentOutcome = sin(status->numbers[0]);
		return 0;
	case 6:
		status->currentOutcome = cos(status->numbers[0]);
		return 0;
	case 7:
		status->currentOutcome = tan(status->numbers[0]);
		return 0;
	case 8:
		status->currentOutcome = pow(status->numbers[0], status->numbers[1]);
		return 0;
	default:
		printf("unexpected error occured...\n");
		return 1;
	}
}

void arithmeticOperation(CalcStatus* status) {
	char* input;
	int pokracovat;
	printf("\nVyberte si aritmetickou operaci: Soucet - 1, Rozdil - 2, Soucin - 3, Podil - 4, Modulo - 5, Umocnit - 6, Odmocnit - 7");
	while (true) {
		scanf(" %d", &status->arithmeticOperType);
		
		switch (status->arithmeticOperType)
		{
		case 1:
			status->currentOutcome = status->numbers[0] + status->numbers[1];
			pokracovat = 1;
			break;
		case 2:
			status->currentOutcome = status->numbers[0] - status->numbers[1];
			pokracovat = 1;
			break;
		case 3:
			status->currentOutcome = status->numbers[0] * status->numbers[1];
			pokracovat = 1;
			break;
		case 4:
			status->currentOutcome = status->numbers[0] / status->numbers[1];
			pokracovat = 1;
			break;
		case 5:
			printf("\nZvolili jste operaci modulo. Koeficienty prevadim na nejblizsi cele cisla.");
			status->currentOutcome = (int)status->numbers[0] % (int)status->numbers[1];
			pokracovat = 1;
			break;
		case 6:
			status->currentOutcome = pow(status->numbers[0],status->numbers[1]);
			pokracovat = 1;
			break;
		case 7:
			status->currentOutcome = pow(status->numbers[0],1/status->numbers[1]);
			pokracovat = 1;
			break;

		default:
			printf("Zadali jste neplatnou operaci!");
			break;
		}
		if (pokracovat == 1)
		{
			break;
		}
		printf("\nVyberte si aritmetickou operaci: Soucet - 1, Rozdil - 2, Soucin - 3, Podil - 4, Modulo - 5, Umocnit - 6, Odmocnit - 7");
	}



}

char askIfMemory() {
	char useMemory = ' ';
	while (true) {
		printf("Do you want to use a number from memory? y/n\n");
		if (scanf(" %c", &useMemory) != 1) {
			printf("scanf failed!");
		}
		if (useMemory == 'y') {
			return 'y';
		}
		else
			if (useMemory == 'n') {
				return 'n';
			}

		system("cls");
	}
}

void getInputFromMemory(CalcStatus* status, int numberIndex) {
	char memoryIndex = ' ';
	while (true) {
		int memoryIsFilled = 0;
		printf("which memory slot you want to use? (A:%lf B:%lf C:%lf D:%lf)\n", status->memory[0], status->memory[1], status->memory[2], status->memory[3]);
		scanf(" %c", &memoryIndex);
		memoryIndex = toupper(memoryIndex);
		switch (memoryIndex) {
		case 'A':
			status->numbers[numberIndex] = status->memory[0];
			memoryIsFilled = 1;
			break;
		case 'B':
			status->numbers[numberIndex] = status->memory[1];
			memoryIsFilled = 1;
			break;
		case 'C':
			status->numbers[numberIndex] = status->memory[2];
			memoryIsFilled = 1;
			break;
		case 'D':
			status->numbers[numberIndex] = status->memory[2];
			memoryIsFilled = 1;
			break;
		default:
			break;
		}
		if (memoryIsFilled == 1) {
			break;
		}

	}
}

void enterIntoMemory(CalcStatus* status) {
	// TODO enter memory question and use answer to fill A,B,C,D
	char memoryIndex;
	printf("which memory slot you want to use? (A:%lf B:%lf C:%lf D:%lf)\n", status->memory[0], status->memory[1], status->memory[2], status->memory[3]);
	scanf("%c", &memoryIndex);
	double newNum;
	printf("\nWrite the number you want to save and press enter:\n");
	scanf("%lf", &newNum);
	switch (memoryIndex) {
	case 'A':
		status->memory[0] = newNum;
		break;
	case 'B':
		status->memory[1] = newNum;
		break;
	case 'C':
		status->memory[2] = newNum;
		break;
	case 'D':
		status->memory[3] = newNum;
		break;
	}
}

void enterOutcomeIntoMemory(CalcStatus* status) {
	char memoryIndex;
	printf("which memory slot you want to use? (A:%lf B:%lf C:%lf D:%lf)\n", status->memory[0], status->memory[1], status->memory[2], status->memory[3]);
	int memorySlotChosen = 0;
	while (true) {


		if (scanf(" %c", &memoryIndex) == 1) {

			switch (memoryIndex) {
			case 'A':
				status->memory[0] = status->currentOutcome;
				memorySlotChosen = 1;
				break;
			case 'B':
				status->memory[1] = status->currentOutcome;
				memorySlotChosen = 1;
				break;
			case 'C':
				status->memory[2] = status->currentOutcome;
				memorySlotChosen = 1;
				break;
			case 'D':
				status->memory[3] = status->currentOutcome;
				memorySlotChosen = 1;
				break;
			default:
				break;
			}
		}
		else {
			system("cls");
			printf("Nespravny index pameti vybran.\n");
			printf("Ktery index pameti chcete pouzit? (A:%lf B:%lf C:%lf D:%lf)\n", status->memory[0], status->memory[1], status->memory[2], status->memory[3]);
		}
		if (memorySlotChosen == 1) {
			break;
		}

	}
}

double getInputNumber(char name) {
	double inputNum;
	while (true) {


		printf("Write a number and press enter for variable %c:  \n", name);
		if (scanf(" %lf", &inputNum) != 1) {
			system("cls");
			printf("invalid input! \n");
			scanf("%*[^\n]");
			continue;
		}
		break;


	}

	return inputNum;
}
int getNumbers(CalcStatus* status) {
	int i = 0;
	char names[3] = { 'x', 'y', 'z' };
	if (status->operationType == KvardatickaRovnice) {
		names[0] = 'a';
		names[1] = 'b';
		names[2] = 'c';
	}
	if (status->operationType == Funkce && status->funcType == LogChooseBase) {
		names[0] = 'x';
		names[1] = 'a';
	}
	while (i < status->numOfOperators)
	{

		if (askIfMemory() == 'y') {
			getInputFromMemory(status, i);
		}
		else {
			status->numbers[i] = getInputNumber(names[i]);
		}
		i++;
	}
	return 0;
}


void askForFunctionType(CalcStatus* status) {
	int funcNo;
	printf("vyberte si typ funkce:\n \
		prirozeny logaritmus(1) desitkovy logaritmus(2) vlastni logaritmus: log a (x)(3)\n\
		faktorial (4) sinus (5) kosinus (6) tangens (7) exponencialni funkci (x^y) (8)\n");
	printf("napiste cislo funkce: ");
	scanf(" %d", &funcNo);
	switch (funcNo) {
	case 1:
		status->funcType = NaturalLog;
		break;
	case 2:
		status->funcType = Log10;
		break;
	case 3:
		status->funcType = LogChooseBase;
		break;
	case 4:
		status->funcType = Factorial;
		break;
	case 5:
		status->funcType = sinus;
		break;
	case 6:
		status->funcType = cosinus;
		break;
	case 7:
		status->funcType = tangens;
		break;
	case 8:
		status->funcType = exponential;
		break;
	}
	if (funcNo == 8 || funcNo == 3) {
		status->numOfOperators = 2;
	}
	else {
		status->numOfOperators = 1;
	}

}

int intro(CalcStatus* status) {

	printf("Vyberte operaci kalkulacky: Aritmeticka operace(1) Funkce(2) Konverze Jednotek(3) Vyresit Kvardaticka Rovnice(4)\n");
	printf("Napiste cislo operace a stiskněte Enter:\n");
	int operation = 0;
	int select_done = 0;
	while (select_done == 0) {
		if (scanf(" %d", &operation) != 1) {
			return -1;
		}
		switch (operation) {
		case 1:
			printf("enter arithmetic");
			status->firstWrite = 0;
			status->numOfOperators = 2;
			status->operationType = Aritmeticka;
			select_done = 1;
			break;

		case 2:
			status->firstWrite = 0;
			status->operationType = Funkce;
			askForFunctionType(status);
			select_done = 1;
			break;

		case 3:
			status->firstWrite = 0;
			status->numOfOperators = 1;
			status->operationType = Konverze;
			select_done = 1;
			break;

		case 4:
			status->firstWrite = 0;
			status->numOfOperators = 3;
			status->operationType = KvardatickaRovnice;
			select_done = 1;
			break;
		default:
			continue;
		}
	}
	return 0;
}






