/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** CsvParser
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <cstring>
#include <cstdlib>

std::vector<std::string> csv_read_row(const std::string &line);

std::vector<std::vector<std::string>> csvToTable(const std::string &filepath);

std::vector<std::string> csvToVector(const std::string &filepath);

std::vector<std::string> splitStr(std::string str, std::string sep);
