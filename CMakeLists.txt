cmake_minimum_required(VERSION 3.13)
project(PKOcsv2mt940, VERSION 0.1 DESCRIPTION "PKOBP CSV to MT940 converter")

set(CMAKE_CXX_STANDARD 17)

add_library(PKOcsv2mt940 csv2mt940.cpp CsvReader.cpp CsvRow.cpp  Mt940.cpp)
set_target_properties(PKOcsv2mt940 PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(PKOcsv2mt940 PROPERTIES PUBLIC_HEADER include/csv2mt940.hpp)
set_target_properties(PKOcsv2mt940 PROPERTIES CXX_STANDARD 17)
