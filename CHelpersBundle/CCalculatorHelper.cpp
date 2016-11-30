//
// Created by Jakub Nadolny on 25.11.2016.
//

#include "CCalculatorHelper.h"

/////////////////////////////////
//////////   Static   ///////////

//######  Checkers  #######//
bool CCalculatorHelper::bIsOperator(std::string sValue) {
    return sValue == "+" || sValue == "-" || sValue == "*" || sValue == "/" || sValue == "~";
}

//######  Calculations  #######//
double CCalculatorHelper::dCount(std::string sOperator, double sFirst, double sSecond) {
    if (bIsOperator(sOperator)) {
        if (sOperator == "*") {
            return sFirst * sSecond;
        } else if (sOperator == "-") {
            return sFirst - sSecond;
        } else if (sOperator == "+") {
            return sFirst + sSecond;
        } else if (sOperator == "/") {
            return sFirst / sSecond;
        } else if (sOperator == "~") {
            return -1 * sFirst;
        }
        return 0;
    } else {
        return 0;
    }
}
