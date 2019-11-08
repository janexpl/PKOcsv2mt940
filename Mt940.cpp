//
// Created by Janusz Kwiatkowski on 19/10/2019.
//
#include <time.h>
#include "include/Mt940.hpp"

void mt940::generateMt940(const string &filename, const string &accountNo, const string &docNo) {

    ofstream m_file(filename);
    m_file << ":20:MT940" << endl;
    m_file << ":25:/PL" << accountNo << endl;
    m_file << ":28C:"<< docNo << endl;

    double startBalance;
    startBalance = m_data->at(m_data->size()-1)->balance +  m_data->at(m_data->size()-1)->amount;
    string balanceSign;
    balanceSign = startBalance < 0 ? "D" : "C";
    string sBalance = convertDouble(startBalance);

    m_file << ":60F:" << balanceSign << dateConvert(m_data->at(m_data->size()-1)->date) << m_data->at(m_data->size()-1)->currency << sBalance << endl;
    for (auto element : *m_data) {

        m_file << ":61:" << dateConvert(element->accountDate) << dateConvert(element->accountDate).erase(0,2) <<
        (element->amount < 0 ? "D":"C") << convertDouble(element->amount) << "NRTNOREF//" << element->transactionIdent.erase(0,1) << endl;
        m_file << "RT 0" << endl;
        m_file << ":86:020~00 " << "RT" << endl;
        vector<string> title = substring(element->operationTitle, 27);
        title.resize(6);
        for (unsigned i = 0; i < title.size(); i++) {
            m_file << "~2" << i << (title.at(i) != "" ? title.at(i) : " ") << endl;
        }
        element->contractorAccount.erase(std::remove_if(element->contractorAccount.begin(), element->contractorAccount.end(), ::isspace), element->contractorAccount.end());

        m_file << "~30" << (element->contractorAccount != "" ? element->contractorAccount.substr(0,8) : " ") << endl;
        m_file << "~31" << (element->contractorAccount != "" ? element->contractorAccount.substr(8,element->contractorAccount.size()) : " ")  << endl;
        vector<string> nameAddress = substring(element->contractorNameAddress, 27);
        nameAddress.resize(2);
        for (unsigned i = 0; i < nameAddress.size(); i++) {
            m_file << "~3" << i+2 << (nameAddress.at(i) != "" ? nameAddress.at(i) : " ") << endl;
        }
        m_file << (element->contractorAccount == "" ? "~38 ": "~38PL"+element->contractorAccount) << endl;
        m_file << "~60 " << endl;
        m_file << "~63 " << endl;

    }
    double endBalance;
    endBalance = m_data->at(0)->balance;
    string endBalanceSign;
    endBalanceSign = endBalance < 0 ? "D" : "C";
    string sEBalance = convertDouble(endBalance);
   

    m_file << ":62F:" << endBalanceSign << dateConvert(m_data->at(0)->date) << m_data->at(0)->currency << sEBalance << endl;
    m_file << ":64F:" << endBalanceSign << dateConvert(m_data->at(0)->date) << m_data->at(0)->currency << sEBalance << endl;
    m_file << "-";
    m_file.close();
}

vector<string> mt940::substring(const string &element, int chars) {
    vector<string> elements;

    if (element.size() == 0) return elements;
    chars = element.size() <= chars ? element.size() : chars;

    double dStrings = ceil((double)element.size() / (double)chars);
    int strings = (int)dStrings;

    for (unsigned i = 0; i < strings; i++)
    {
        elements.push_back(element.substr(i*chars, chars));
    }
    return elements;
}
string mt940::getLastDay(const string &date) 
{
    char cDate[11];
    struct tm result;
    strptime(cDate, "%Y-%m-%d", &result);
    stringstream year;
    year << result.tm_year;
    stringstream month;
    stringstream day;
    month << (result.tm_mon+1 < 10 ? "0" + to_string(result.tm_mon+1) : to_string(result.tm_mon+1));
    int monthI = stoi(month.str());
    if (monthI == 1 || monthI == 3 || monthI == 5 || monthI == 7 || monthI == 8 || monthI == 10 || monthI == 12) 
        day << "31";
    else if (monthI == 4 || monthI == 6 || monthI == 9 || monthI == 11)
        day << "30";
    else {
        if (stoi(year.str()) % 4 == 0 ){
            if (stoi(month.str()) % 100 == 0){
                if (stoi(month.str()) % 400 == 0)
                    day << "29";
            }
            day << "28";
        }
        day << "29";
    }
    
    stringstream dateStream;
    dateStream << year.str().erase(0,1) << month.str() << day.str();
    return dateStream.str(); 
}
string mt940::dateConvert(const string &date) {
    char cDate[11];
    struct tm result;

    copy(date.begin(), date.end(), cDate);

    cDate[m_data->at(0)->date.size()] = '\0';

    strptime(cDate, "%Y-%m-%d", &result);
    stringstream year;
    year << result.tm_year;
    stringstream month;
    stringstream day;
    month << (result.tm_mon+1 < 10 ? "0" + to_string(result.tm_mon+1) : to_string(result.tm_mon+1));
    day << (result.tm_mday < 10 ? "0" + to_string(result.tm_mday) : to_string(result.tm_mday));
    stringstream dateStream;
    dateStream << year.str().erase(0,1) << month.str() << day.str();
    return dateStream.str();
}

string mt940::convertDouble(double number) {

    stringstream strNumber;
    strNumber << fixed;
    strNumber << setprecision(2);
    strNumber << fabs(number);
    string sNumber = strNumber.str();
    replace(sNumber.begin(), sNumber.end(),'.', ',');

    return sNumber;
}
