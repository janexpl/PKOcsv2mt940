//
// Created by Janusz Kwiatkowski on 17/10/2019.
//

#pragma once
#include <iostream>
#include <vector>
class CSVRow {
public:
    CSVRow(char separator) : m_separator(separator) {};

    std::string const &operator[](std::size_t index) const;
    
    std::size_t size() const;
    void clear();
    void readNextRow(std::istream &str);
    ~CSVRow(){
        m_data.clear();
    }
private:
    std::vector<std::string> m_data;
    char m_separator;
};
