//
// Created by Jakub Nadolny on 25.11.2016.
//

#include "CCalculatorHelper.h"
#include "CStringHelper.h"

/////////////////////////////////
//////////   Static   ///////////

//######  Checkers  #######//
bool CCalculatorHelper::bIsOperator(std::string sValue) {
    return sValue == "+" || sValue == "-" || sValue == "*" || sValue == "/" || sValue == "~";
}

//######  Calculations  #######//
double CCalculatorHelper::dCount(std::string sOperator, double sFirst, double sSecound) {
    if (bIsOperator(sOperator)) {
        if (sOperator == "*") {
            return sFirst * sSecound;
        } else if (sOperator == "-") {
            return sFirst - sSecound;
        } else if (sOperator == "+") {
            return sFirst + sSecound;
        } else if (sOperator == "/") {
            return sFirst / sSecound;
        } else if (sOperator == "~") {
            return -1 * sFirst;
        }
    } else {
        return 0;
    }
}

double CCalculatorHelper::dCount(std::string sOperator, std::string sFirst, std::string sSecound) {
    if (CStringHelper::bIsInt(sFirst) && CStringHelper::bIsInt(sSecound)) {
        return dCount(sOperator, std::stod(sFirst), std::stod(sSecound));
    } else {
        return 0;
    }
}

double CCalculatorHelper::dCount(std::string sOperator, std::string sFirst, double sSecound) {
    if (CStringHelper::bIsInt(sFirst)) {
        return dCount(sOperator, std::stod(sFirst), sSecound);
    } else {
        return 0;
    }
}

double CCalculatorHelper::dCount(std::string sOperator, double sFirst, std::string sSecound) {
    if (CStringHelper::bIsInt(sSecound)) {
        return dCount(sOperator, sFirst, std::stod(sSecound));
    } else {
        return 0;
    }
}
