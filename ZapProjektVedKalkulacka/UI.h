
#pragma once

#include "constants.h"
#include "UI.cpp"

int getNumbers(CalcStatus* status);//

void enterOutcomeIntoMemory(CalcStatus* status);//

double getInputNumber(char name);//

void getInputFromMemory(CalcStatus* status, int numberIndex);//

void enterIntoMemory(CalcStatus* status);//

char askIfMemory(); //

void arithmeticOperation(CalcStatus* status);//

int intro(CalcStatus* status);//

void askForFunctionType(CalcStatus* status);//

int printOutcome(struct CalcStatus* status);//

int conversion(struct CalcStatus* status); //