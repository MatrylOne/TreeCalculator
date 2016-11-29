//
// Created by Jakub Nadolny on 26.11.2016.
//

#ifndef ZMPO3_CCALCULATORMENAGER_H
#define ZMPO3_CCALCULATORMENAGER_H

#include <map>
#include <vector>
#include "../CHelpersBundle/CStringHelper.h"
#include "../CHelpersBundle/HErrors.h"
#include "CCalculatorTree.h"

class CCalculatorMenager {
public:
    CCalculatorMenager();

    ~CCalculatorMenager();

    std::string sGetTask();

    std::string sGetParsedTask();

    std::string sGetTreeTask();

    int iSetTask(std::string sInput);

    int iConstructTree();

    int iFindVariables();

    std::string sPrintVariables();

    int iSetVariables();

    std::string sGetInfix();

    double dCalculate();

    int iRepairTree();

    std::string sSeparateTask(std::string sTask);

    bool bCheckTree();

    void mGetIssues(std::map<char, int> &mErrors);

private:
    std::string sTask;
    std::string sOriginalTask;
    CCalculatorTree *cCalculatorTree;
    std::map<char, int> mParameters;

    int iSetMapElement(char cLetter, int iValue);
};


#endif //ZMPO3_CCALCULATORMENAGER_H
