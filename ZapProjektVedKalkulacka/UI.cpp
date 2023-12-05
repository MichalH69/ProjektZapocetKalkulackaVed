#include "UI.h"
#include "constants.h"



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
// option to enter into memory without having an outcome
void enterIntoMemory(CalcStatus* status) {
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
			status->currentOutcome = pow(status->numbers[0], status->numbers[1]);
			pokracovat = 1;
			break;
		case 7:
			status->currentOutcome = pow(status->numbers[0], 1 / status->numbers[1]);
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
			status->currentOutcome = input + 273.15;
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
