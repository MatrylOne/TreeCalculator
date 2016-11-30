//
// Created by Jakub Nadolny on 25.11.2016.
//

#ifndef ZMPO3_CTREE_H
#define ZMPO3_CTREE_H


#include <string>
#include <map>

#include "../CHelpersBundle/CCalculatorHelper.h"
#include "../CHelpersBundle/HDefaults.h"
#include "../CHelpersBundle/CStringHelper.h"
#include "../CHelpersBundle/HErrors.h"

#include "CNode.h"

class CCalculatorTree {
private:
    CNode *nRoot;

public:
    CCalculatorTree();

    void vInitialize();
    void vClean();

    void mGetIssues(std::map<char, int> &mErrors);

    int iRepairTree();

    int iSearchAndRoot(std::string sArg);

    double dCalculate(std::map<char, int> &mParameters);

    bool bAdd(std::string sSymbol);

    bool bCheckTree();

    CNode *nGetRoot();

    std::string sInfix();
    std::string sGetPostfix();
    std::string sGetPostfixSpace();

    static bool bIsVariable(std::string sArgument);

    ~CCalculatorTree();

private:

    void mhGetIssues(CNode *cCurrent, std::map<char, int> &mErrors);

    int ihRepairTree(CNode *cCurrent);
    int ihSearchAndRoot(CNode *cNode, std::string sArg);

    double dMap(std::string sArg, std::map<char, int> &mParameters);
    double dhCalculate(CNode *cCurrent, std::map<char, int> &mParameters);

    bool bhAdd(CNode *cCurrent, std::string sSymbol);

    bool bhCheckTree(CNode *cCurrent);

    std::string shInfix(CNode *cCurrent);
    std::string shGetPostfix(CNode *cCurrent);
    std::string shGetPostfixSpace(CNode *cCurrent);
};


#endif //ZMPO3_CTREE_H
