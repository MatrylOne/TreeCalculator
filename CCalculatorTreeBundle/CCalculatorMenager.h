//
// Created by Jakub Nadolny on 26.11.2016.
//

#ifndef ZMPO3_CCALCULATORMENAGER_H
#define ZMPO3_CCALCULATORMENAGER_H

#include <map>
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

    int iFindParameters();

    int iSetParameters();

    std::string sGetInfix();

    double dCalculate();

    int iRepairTree();

    std::string sSeparateTask(std::string sTask);

    bool bCheckTree();

private:
    std::string sTask;
    std::string sOriginalTask;
    CCalculatorTree *cCalculatorTree;
    std::map<std::string, int> mParameters;
};


#endif //ZMPO3_CCALCULATORMENAGER_H
