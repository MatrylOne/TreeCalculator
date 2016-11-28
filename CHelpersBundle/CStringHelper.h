//
// Created by Jakub Nadolny on 16.10.2016.
//

#ifndef FIRST_CSTRINGHELPER_H
#define FIRST_CSTRINGHELPER_H

#include <string>
#include <vector>
#include <sstream>

class CStringHelper {
public:
    static std::vector<std::string> vSliceString(std::string sText);

    static bool bIsInt(std::string sText);

    static bool bIsInt(char sText);

    static bool bIsDouble(const char *str);

    static std::string sToString(int iNumber);

    static std::string sDoubleToString(double dNumber);

    static std::string sParseVector(std::vector<std::string> vArgs);

    static std::string sParseVector(std::vector<std::string> vArgs, int iFrom);


};


#endif //FIRST_CSTRINGHELPER_H
