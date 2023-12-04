// kalkulacka_ved.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>

enum OperationType { Aritmeticka = 1, Funkce, Konverze, KvardatickaRovnice, NoOp };

enum FunctionType { NaturalLog = 1, Log10, LogChooseBase, Factorial, sinus, cosinus, tangens, exponential, NoFunc };

enum AriOperation { Plus = 1, Minus, Multiply, Divide, Mod, Power, Root, NoAri };
struct CalcStatus {
	double currentOutcome;
	double numbers[3];
	double memory[4];
	int numOfOperators;
	AriOperation arithmeticOperType;
	OperationType operationType;
	FunctionType funcType;
	int firstWrite;

};

int printOutcome(struct CalcStatus* status);
void quadraticFunction(struct CalcStatus* status);

int conversion(struct CalcStatus* status);

void enterOutcomeIntoMemory(CalcStatus* status);

double factorial(double input);
int executeFunction(CalcStatus* status);

void askForFunctionType(CalcStatus* status);

int intro(CalcStatus* status);

double getInputNumber(char name);

int getNumbers(CalcStatus* status);

void getInputFromMemory(CalcStatus* status, int numberIndex);

void enterIntoMemory(CalcStatus* status);

char askIfMemory();

