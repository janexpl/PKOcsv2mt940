//
// Created by Janusz Kwiatkowski on 17/10/2019.
//

#ifndef CSV2MT940_CSVREADER_HPP
#define CSV2MT940_CSVREADER_HPP

#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "CsvRow.hpp"

#include "csvfields.hpp"

using namespace std;


class CSVReader {
public:
    CSVReader(const string &filename);
    shared_ptr<vector<shared_ptr<csvfields>>> ParseFile();

private:

    const string &m_filename;
    shared_ptr<csvfields> m_csvfields;
    shared_ptr<vector<shared_ptr<csvfields>>> m_result;
};


#endif //CSV2MT940_CSVREADER_HPP
