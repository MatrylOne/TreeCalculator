//
// Created by Jakub Nadolny on 26.11.2016.
//

#include <vector>
#include "CCalculatorMenager.h"
#include "../CHelpersBundle/CStringHelper.h"
#include "../CHelpersBundle/HErrors.h"

/////////////////////////////////
//////////   Public   ///////////

//######   Constructors  #######//
CCalculatorMenager::CCalculatorMenager() {
    cCalculatorTree = new CCalculatorTree();
}

//######   Destructors  #######//
CCalculatorMenager::~CCalculatorMenager() {
    delete cCalculatorTree;
}

//######   Getters   #######//
std::string CCalculatorMenager::sGetInfix() {
    return cCalculatorTree->sInfix();
}

std::string CCalculatorMenager::sGetTreeTask() {
    return cCalculatorTree->sGetPostfix();
}

std::string CCalculatorMenager::sGetTask() {
    return this->sTask;
}

std::string CCalculatorMenager::sGetParsedTask() {
    return std::string("TODO - not ended");
}

//######   Setters   #######//
int CCalculatorMenager::iSetTask(std::string sInput) {
    std::string sSeparated = sSeparateTask(sInput);
    this->sTask = sSeparated;
    this->sOriginalTask = sSeparated;
    return 0;
}

int CCalculatorMenager::iSetParameters() {
    if (mParameters.size() == 0) return NO_VARIABLES_FOUND;
    return 0;
}

//######   Checkers   #######//
bool CCalculatorMenager::bCheckTree() {
    return cCalculatorTree->bCheckTree();
}

//######   Tools   #######//
int CCalculatorMenager::iConstructTree() {
    std::vector<std::string> sArgs = CStringHelper::vSliceString(sTask);

    cCalculatorTree->vClean();
    cCalculatorTree->vInitialize();

    for (int i = (sArgs.size() - 1); i >= 0; i--) {
        if (!cCalculatorTree->bAdd(sArgs[i])) {
            return NO_EMPTY_LEAF;
        }
    }

    return cCalculatorTree->bCheckTree() ? 0 : EMPTY_NODE;
}

double CCalculatorMenager::dCalculate() {
    return cCalculatorTree->dCalculate();
}

int CCalculatorMenager::iFindParameters() {
    std::vector<std::string> vSlices = CStringHelper::vSliceString(sOriginalTask);

    for (int i = 0; i < vSlices.size(); i++) {
        if (CCalculatorTree::bIsVariable(vSlices[i])) {
            mParameters[vSlices[i]] = 1;
        }
    }

    if (mParameters.size() == 0) return NO_VARIABLES_FOUND;
    return 0;
}

int CCalculatorMenager::iRepairTree() {
    cCalculatorTree->iRepairTree();
    this->sTask = cCalculatorTree->sGetPostfix();
    return 0;
}

std::string CCalculatorMenager::sSeparateTask(std::string sTask) {
    std::vector<std::string> sArgs = CStringHelper::vSliceString(sTask);
    std::string sReturn = "";

    for (int i = 0; i < sArgs.size(); i++) {
        if (sArgs[i].size() > 1) {
            if (!CStringHelper::bIsInt(sArgs[i])) {
                std::string sTemp = sArgs[i];
                for (int j = 0; j < sTemp.size(); j++) {
                    if (!CStringHelper::bIsInt(sTemp[j]) && j > 0) sReturn += " ";
                    sReturn += sTemp[j];
                    if (!CStringHelper::bIsInt(sTemp[j]) && j == 0) sReturn += " ";
                }
            } else {
                sReturn += sArgs[i] + " ";
            }
        } else {
            sReturn += sArgs[i] + " ";
        }
    }

    return sReturn;
}