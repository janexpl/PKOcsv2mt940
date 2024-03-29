//
// Created by Janusz Kwiatkowski on 17/10/2019.
//

#include <sstream>
#include "include/CsvRow.hpp"

std::string const &CSVRow::operator[](std::size_t index) const {
    return m_data[index];
}

std::size_t CSVRow::size() const {
    return m_data.size();
}

void CSVRow::readNextRow(std::istream &str) {
    std::string line;
    std::getline(str,line);
    std::stringstream   lineStream(line);
    std::string         cell;

    m_data.clear();

    while(std::getline(lineStream, cell, m_separator))
    {

        if (cell != "," && cell != "") {
           m_data.push_back(cell);
        }
    }
    if (!lineStream && cell.empty())
    {
        // If there was a trailing comma then add an empty element.
        m_data.push_back("");
    }

}

void CSVRow::clear() {
    m_data.clear();
}
