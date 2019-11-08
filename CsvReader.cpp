//
// Created by Janusz Kwiatkowski on 17/10/2019.
//

#include <vector>
#include <sstream>
#include "include/CsvReader.hpp"
std::istream& operator>>(std::istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}
CSVReader::CSVReader(const string &filename): m_filename(filename) {

}

shared_ptr<vector<shared_ptr<csvfields> > > CSVReader::ParseFile() {
    ifstream m_file(m_filename);
    m_result = make_shared<vector<shared_ptr<csvfields> > >();
    CSVRow row('"');
    CSVRow operation('|');
    CSVRow operDetails(':');
    int line = 0;

    while (m_file >> row)
    {

       if (line != 0){
           m_csvfields = make_shared<csvfields>();
           m_csvfields->date = row[0];
           m_csvfields->accountDate = row[1];
           stringstream m_descTemp;
           m_descTemp << row[2];
           while (m_descTemp >> operation)
           {
               for (unsigned i = 0; i < operation.size(); i++) {
                   stringstream operDetailsTemp;
                   operDetailsTemp << operation[i];
                   operDetailsTemp >> operDetails;
                   string opd = operDetails[1];
                   opd.erase(0,1);
                   if (operDetails[0] == "Rachunek kontrahenta") m_csvfields->contractorAccount = opd;
                   if (operDetails[0] == "Nazwa i adres Kontrahenta") m_csvfields->contractorNameAddress = opd;
                   if (operDetails[0] == "Tytuł") m_csvfields->operationTitle = opd;
                   if (operDetails[0] == "Identyfikator transakcji") m_csvfields->transactionIdent = opd;
                   if (operDetails[0] == "Data i czas operacji") m_csvfields->operationDate = opd;
                   if (operDetails[0] == "Kwota CashBack") m_csvfields->cashBackamount = opd;
                   if (operDetails[0] == "Oryginalna kwota operacji") m_csvfields->orgOperationAmount = stod(opd);
                   if (operDetails[0] == "Numer karty") m_csvfields->cardNumber = opd;
                   if (operDetails[0] == "Lokalizacja") m_csvfields->operationLoc = opd;
               }
           }
           m_csvfields->operationType = row[3];
           m_csvfields->amount = stod( row[4]);
           m_csvfields->currency = row[5];
           m_csvfields->balance = stod(row[6]);
           if (m_csvfields->operationType == "Płatność kartą" && m_csvfields->contractorNameAddress == "") m_csvfields->contractorNameAddress = m_csvfields->operationLoc;
           m_result->push_back(m_csvfields);

           operation.clear();
           m_descTemp.str(string());
       }
       line++;
    }
    m_file.close();
    return m_result;
}


