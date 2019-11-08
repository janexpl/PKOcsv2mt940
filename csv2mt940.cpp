#include "include/csv2mt940.hpp"

#include <iostream>

bool generateMt940(string inFile, string ouFile, string accNo, string docNo) {
    shared_ptr<vector<shared_ptr<csvfields> > > m_result;
    CSVReader *reader = new CSVReader(inFile);
    m_result = reader->ParseFile();
    mt940 parser(m_result);
    parser.generateMt940(ouFile, accNo, docNo);
    return true;
}
