//
// Created by Jakub Nadolny on 16.10.2016.
//
#include "CStringHelper.h"

/////////////////////////////////
//////////   Static   ///////////

//######   Checkers #######//
bool CStringHelper::bIsDouble(const char *cStr) {
    char *endptr = 0;
    strtod(cStr, &endptr);

    return !(*endptr != '\0' || endptr == cStr);
}

bool CStringHelper::bIsInt(char sText) {
    std::string sTemp = "";
    sTemp += sText;
    return bIsInt(sTemp);
}

bool CStringHelper::bIsInt(std::string sText) {
    std::string::const_iterator it = sText.begin();
    while ((it != sText.end() && std::isdigit(*it))) ++it;
    return !sText.empty() && it == sText.end();
}

//######   Converters #######//
std::string CStringHelper::sToString(int iNumber) {
    std::stringstream ss;
    ss << iNumber;
    std::string sText = ss.str();
    return sText;
}

std::string CStringHelper::sDoubleToString(double dNumber) {
    std::ostringstream sstream;
    sstream << dNumber;
    return sstream.str();
}

//######   Tools #######//
std::vector<std::string> CStringHelper::vSliceString(std::string sText) {
    std::vector<std::string> vSlices;
    std::stringstream ss(sText);
    std::string trim;

    while (std::getline(ss, trim, ' ')) {
        vSlices.push_back(trim);
    }

    return vSlices;
}

std::string CStringHelper::sParseVector(std::vector<std::string> vArgs) {
    return sParseVector(vArgs, 0);
}

std::string CStringHelper::sParseVector(std::vector<std::string> vArgs, int iFrom) {
    std::string sOutput = "";

    for (int i = iFrom; i < vArgs.size(); i++) {
        sOutput += vArgs[i] + " ";
    }

    return sOutput;
}
