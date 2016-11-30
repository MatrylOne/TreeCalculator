//
// Created by Jakub Nadolny on 25.11.2016.
//

#ifndef ZMPO3_CCALCULATORHELPER_H
#define ZMPO3_CCALCULATORHELPER_H


#include <string>

#include "CStringHelper.h"

class CCalculatorHelper {
public:
    static bool bIsOperator(std::string sValue);

    static double dCount(std::string sOperator, double sFirst, double sSecond);
};


#endif //ZMPO3_CCALCULATORHELPER_H
