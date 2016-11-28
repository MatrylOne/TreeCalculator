//
// Created by Jakub Nadolny on 25.11.2016.
//

#ifndef ZMPO3_CTREE_H
#define ZMPO3_CTREE_H


#include <string>
#include "CNode.h"
#include "../CHelpersBundle/CCalculatorHelper.h"
#include "../CHelpersBundle/CStringHelper.h"

class CCalculatorTree {
public:
    CCalculatorTree();

    ~CCalculatorTree();

    bool bAdd(std::string sSymbol);

    void vClean();

    CNode *nGetRoot();

    double dCalculate();

    std::string sInfix();

    void vInitialize();

    std::string sGetPostfix();

    std::string sGetPostfixSpace();

    int iRepairTree();

    bool bCheckTree();

    static bool bIsVariable(std::string sArgument);

private:
    CNode *nRoot;

    bool bhAdd(CNode *cCurrent, std::string sSymbol);

    void vhClean(CNode *cCurrent);

    double dhCalculate(CNode *cCurrent);

    std::string shInfix(CNode *cCurrent);

    std::string shGetPostfix(CNode *cCurrent);

    std::string shGetPostfixSpace(CNode *cCurrent);

    int ihRepairTree(CNode *cCurrent);

    bool bhCheckTree(CNode *cCurrent);
};


#endif //ZMPO3_CTREE_H
