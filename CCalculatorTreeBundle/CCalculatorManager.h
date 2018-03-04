//
// Created by Jakub Nadolny on 26.11.2016.
//

#ifndef ZMPO3_CCALCULATORMENAGER_H
#define ZMPO3_CCALCULATORMENAGER_H

#include <map>
#include <vector>
#include <string>

#include "../CHelpersBundle/CStringHelper.h"
#include "../CHelpersBundle/HErrors.h"

#include "CCalculatorTree.h"

class CCalculatorManager {
private:
    std::string sTask;
    std::string sOriginalTask;
    CCalculatorTree *cCalculatorTree;
    std::map<char, int> mParameters;

public:
    CCalculatorManager();

    bool bCheckTree();

    int iSetTask(std::string sInput);
    int iConstructTree();
    int iFindVariables();
    int iSetVariables();
    int iRepairTree();
    int iSearchAndRoot(std::string sArg);

    double dCalculate();

    std::string sGetTask();
    std::string sGetParsedTask();
    std::string sGetTreeTask();
    std::string sPrintVariables();
    std::string sGetInfix();
    std::string sSeparateTask(std::string sTask);

	void vdONothing();

	void vGetIssues(std::map<char, int> &mErrors);

    ~CCalculatorManager();
private:
    int iSetMapElement(char cLetter, int iValue);
    int iUpdateTask();
};

#endif