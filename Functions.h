#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <sstream>
#include <vector>
#include <regex>

using std::string;

string ValidatePavadinimas();
bool usedSymbols(const char& character);
string lowerAndRemove(string eilute);
void visasTekstas(string pavadinimas);
void visasTekstasEilutem(string pavadinimas);
void raskURL(string pavadinimas);
void menu(string pavadinimas);

#endif