// kalkulacka_ved.cpp : Defines the entry point for the application.
//

#include "ZapProjektVedKalkulacka.h"



#include <math.h>
#include <iostream>
#include <stdio.h>




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

int conversion(struct CalcStatus* status) {

	int jakyPrevod = 0;
	char jednotka1[10] = "";
	char jednotka2[10] = "";
	int zadanyPrevod = 0;
	double input = status->numbers[0];
	system("cls");
	printf("Typy prevodu:\n\n1 - C na F\n2 - F na C\n3 - C na K\n4 - F na K\n5 - K na C\n6 - K na F\n7 - Stupne na radiany\n8 - Radiany na stupne\n\nZadejte pozadovany prevod: ");


	while (zadanyPrevod == 0) {
		if (scanf(" %d", &jakyPrevod) != 1) {
			printf("Neplatny vstup!\n");
			continue;
		}
		switch (jakyPrevod)
		{
		case 1:
			//printf("INPUT: %.2lf\n", input);
			status->currentOutcome = (input * 1.8) + 32;
			strcpy(jednotka1, "C");
			strcpy(jednotka2, "F");
			zadanyPrevod = 1;
			strcpy(status->prevod, "C na F");
			//printf("curr outcome %.2lf \n", status->currentOutcome);
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
			printf("\nTypy prevodu:\n\n1 - C na F\n2 - F na C\n3 - C na K\n4 - F na K\n5 - K na C\n6 - K na F\n7 - Stupne na radiany\n8 - Radiany na stupne\n\nZadejte pozadovany prevod: ");
			scanf("@%*[^\n]");
		}
		else {
			break;
		}
	}
	system("cls");
	printf("%.2lf%s je %.2lf%s\n", input, jednotka1, status->currentOutcome, jednotka2);

	return 0;
}

int printOutcome(struct CalcStatus* status) {
	
	if (status->operationType == KvardatickaRovnice) {
		return 0;
	}
	if (status->operationType != Konverze) {
		printf("Vysledek operace: %.2lf\n", status->currentOutcome);
	}

	char saveOutcome = ' ';
	printf("\nChcete ulozit vysledek do pameti? (y/n): ");
	while (true) {
		scanf(" %c", &saveOutcome);
		system("cls");
		if (saveOutcome != 'y' && saveOutcome != 'n') {
			printf("Neplatny vstup!\n");
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

void arithmeticOperation(CalcStatus* status) {
	char* input;
	int pokracovat;
	system("cls");
	printf("Typy aritmetickych operaci:\n\n1 - Soucet\n2 - Rozdil\n3 - Soucin\n4 - Podil\n5 - Modulo\n6 - Umocnit\n7 - Odmocnit\n\n");
	printf("Vyberte operaci: ");
	while (true) {
		scanf(" %d", &status->arithmeticOperType);
		system("cls");
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
			printf("Zvolili jste operaci modulo. Koeficienty prevadim na nejblizsi cele cisla.\n");
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
			printf("\nZadali jste neplatnou operaci!");
			break;
		}
		if (pokracovat == 1)
		{
			break;
		}
		system("cls");
		printf("\nTypy aritmetickych operaci:\n\n1 - Soucet\n2 - Rozdil\n3 - Soucin\n4 - Podil\n5 - Modulo\n6 - Umocnit\n7 - Odmocnit\n\n");
		printf("Vyberte operaci: ");
	}



}

char askIfMemory() {
	char useMemory = ' ';
	while (true) {
		system("cls");
		printf("Chcete pouzit cislo z pameti? (y/n): ");
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
		printf("\nHodnoty v pameti:\n(A:%.2lf B:%.2lf C:%.2lf D:%.2lf)\n\nVyberte pametovy slot: ", status->memory[0], status->memory[1], status->memory[2], status->memory[3]);
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
	printf("Hodnoty v pameti:\n(A:%.2lf B:%.2lf C:%.2lf D:%.2lf)\n\nVyberte pametovy slot: \n", status->memory[0], status->memory[1], status->memory[2], status->memory[3]);
	scanf("%c", &memoryIndex);
	double newNum;
	printf("\nNapiste cislo ktere chcete ulozit a stisknete enter:\n");
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
	printf("Hodnoty v pameti: (A:%.2lf B:%.2lf C:%.2lf D:%.2lf)\n\nDo ktereho slotu chcete ulozit?: ", status->memory[0], status->memory[1], status->memory[2], status->memory[3]);
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
			printf("Hodnoty v pameti: (A:%.2lf B:%.2lf C:%.2lf D:%.2lf)\n\nDo ktereho slotu chcete ulozit?: ", status->memory[0], status->memory[1], status->memory[2], status->memory[3]);
		}
		if (memorySlotChosen == 1) {
			system("cls");
			break;
		}

	}
}

double getInputNumber(char name) {
	double inputNum;
	while (true) {

		system("cls");
		printf("Zadejte cislo pro promennou %c: ", name);

		if (scanf(" \n%lf", &inputNum) == 1) {
			printf("\n");
		}
		else if (scanf(" \n%lf", &inputNum) != 1) {
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
	char names[20] = { 'x', 'y', 'z' };
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
	system("cls");
	printf("Typy funkci:\n\n1 - Prirozeny logaritmus\n2 - Desitkovy logaritmus\n3 - Vlastni logaritmus: log_a (x)\n4 - Faktorial\n5 - Sinus\n6 - Kosinus\n7 - Tangens\n8 - Exponencialni funkce (x^y)\n\n");
	printf("Napiste cislo zvolene funkce: ");
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

	printf("Vyberte operaci kalkulacky:\n\n1 - Aritmeticke operace\n2 - Funkce\n3 - Konverze Jednotek\n4 - Najit koreny kvadraticke rovnice\n");
	printf("\nNapiste cislo operace a stisknete Enter: ");
	int operation = 0;
	int select_done = 0;
	while (select_done == 0) {
		if (scanf(" %d", &operation) != 1) {
			return -1;
		}
		switch (operation) {
		case 1:
			status->firstWrite = 0;
			status->numOfOperators = 2;
			status->operationType = Aritmeticka; // ASK FOR OPERATION TYPE HERE ALREADY
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
			status->operationType = Konverze; //ASK FOR CONVERSION TYPE HERE
			select_done = 1;
			break;

		case 4:
			status->firstWrite = 0;
			status->numOfOperators = 3;
			status->operationType = KvardatickaRovnice; // print some formula like ax^2 + bx + c so user knows what numbers he's inputting
			select_done = 1;
			break;
		default:
			continue;
		}
	}
	return 0;
}






