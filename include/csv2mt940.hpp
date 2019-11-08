#ifndef PKOCSV2MT940_CSV2MT940_HPP
#define PKOCSV2MT940_CSV2MT940_HPP
#include <iostream>
#include "Mt940.hpp"
#include "CsvReader.hpp"

using namespace std;
bool generateMt940(string inFile, string ouFile, string accNo, string docNo);

#endif //PKOCSV2MT940_CSV2MT940_HPP
