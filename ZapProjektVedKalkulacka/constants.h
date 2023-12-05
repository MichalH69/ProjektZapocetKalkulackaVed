#pragma once

#include <iostream>
#include <stdio.h>
#include <math.h>



#define FOREACH_OperationType(OperationType) OperationType(Aritmeticka)   OperationType(Funkce)  OperationType(Konverze)   OperationType(KvardatickaRovnice)  OperationType(NoOp)
#define FOREACH_FunctionType(FunctionType) FunctionType(NaturalLog)   FunctionType(Log10)  FunctionType(LogChooseBase)   FunctionType(Factorial)  FunctionType(sinus) FunctionType(cosinus)   FunctionType(tangens)  FunctionType(exponential) FunctionType(NoFunc)
#define FOREACH_AriOperation(AriOperation) AriOperation(Plus)   AriOperation(Minus)  AriOperation(Multiply)   AriOperation(Divide)  AriOperation(Mod) AriOperation(Power) AriOperation(Root) AriOperation(NoAri)

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

enum OperationType { //enum OperationType { Aritmeticka = 1, Funkce, Konverze, KvardatickaRovnice, NoOp };
	FOREACH_OperationType(GENERATE_ENUM)
};

static const char* opTypeStr[] = {
	FOREACH_OperationType(GENERATE_STRING)
};

enum FunctionType { //enum FunctionType { NaturalLog = 1, Log10, LogChooseBase, Factorial, sinus, cosinus, tangens, exponential, NoFunc };
	FOREACH_FunctionType(GENERATE_ENUM)
};

static const char* funcTypeStr[] = {
	FOREACH_FunctionType(GENERATE_STRING)
};
enum AriOperation { //enum AriOperation { Plus = 1, Minus, Multiply, Divide, Mod, Power, Root, NoAri };
	FOREACH_AriOperation(GENERATE_ENUM)
};

static const char* ariOpTypeStr[] = {
	FOREACH_AriOperation(GENERATE_STRING)
};


struct CalcStatus {
	double currentOutcome;
	double numbers[3];
	double memory[4];
	int numOfOperators;
	AriOperation arithmeticOperType;
	OperationType operationType;
	FunctionType funcType;
	int firstWrite;
	char prevod[1024];
	char kvadRovniceKoreny[1024];

};
