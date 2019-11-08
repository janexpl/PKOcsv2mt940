//
// Created by Janusz Kwiatkowski on 19/10/2019.
//

#pragma once
#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <cmath>
#include "csvfields.hpp"
using namespace std;
class mt940 {
public:
    mt940(shared_ptr<vector<shared_ptr<csvfields>>> data):m_data(data){}
    void generateMt940(const string &filename, const string &accountNo, const string &docNo);

private:
    string dateConvert(const string &date);
    vector<string> substring(const string &element, int chars);
    string convertDouble(double number);
    shared_ptr<vector<shared_ptr<csvfields>>> m_data;
    string getLastDay(const string &date);

};




