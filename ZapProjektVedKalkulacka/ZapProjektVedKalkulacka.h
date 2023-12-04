// kalkulacka_ved.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#define FOREACH_OperationType(OperationType) OperationType(Aritmeticka)   OperationType(Funkce)  OperationType(Konverze)   OperationType(KvardatickaRovnice)  OperationType(NoOp)
#define FOREACH_FunctionType(FunctionType) FunctionType(NaturalLog)   FunctionType(Log10)  FunctionType(LogChooseBase)   FunctionType(Factorial)  FunctionType(sinus) FunctionType(cosinus)   FunctionType(tangens)  FunctionType(exponential) FunctionType(NoFunc)
#define FOREACH_AriOperation(AriOperation) AriOperation(Plus)   AriOperation(Minus)  AriOperation(Multiply)   AriOperation(Divide)  AriOperation(Mod) AriOperation(Power) AriOperation(Root) AriOperation(NoAri)

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

enum OperationType {
	FOREACH_OperationType(GENERATE_ENUM)
};

static const char* opTypeStr[] = {
	FOREACH_OperationType(GENERATE_STRING)
};

enum FunctionType {
	FOREACH_FunctionType(GENERATE_ENUM)
};

static const char* funcTypeStr[] = {
	FOREACH_FunctionType(GENERATE_STRING)
};
enum AriOperation {
	FOREACH_AriOperation(GENERATE_ENUM)
};

static const char* ariOpTypeStr[] = {
	FOREACH_AriOperation(GENERATE_STRING)
};

//enum OperationType { Aritmeticka = 1, Funkce, Konverze, KvardatickaRovnice, NoOp };

//enum FunctionType { NaturalLog = 1, Log10, LogChooseBase, Factorial, sinus, cosinus, tangens, exponential, NoFunc };

//enum AriOperation { Plus = 1, Minus, Multiply, Divide, Mod, Power, Root, NoAri };
struct CalcStatus {
	double currentOutcome;
	double numbers[3];
	double memory[4];
	int numOfOperators;
	AriOperation arithmeticOperType;
	OperationType operationType;
	FunctionType funcType;
	int firstWrite;
	char prevod[30];
	double koreny[2];


};

void writeIntoHistory(struct CalcStatus* status);
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

void arithmeticOperation(CalcStatus* status);
