//
// Created by Jakub Nadolny on 26.11.2016.
//
#include <string>
#include "CCalculatorMenager.h"


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

void CCalculatorMenager::mGetIssues(std::map<char, int> &mErrors) {
    cCalculatorTree->mGetIssues(mErrors);
}

//######   Setters   #######//
int CCalculatorMenager::iSetTask(std::string sInput) {
    std::string sSeparated = sSeparateTask(sInput);
    this->sTask = sSeparated;
    this->sOriginalTask = sSeparated;
    mParameters.clear();
    iFindVariables();
    return 0;
}

int CCalculatorMenager::iSetVariables() {
    if (!mParameters.empty()) {

        std::string sTextLine = "";

        for (std::map<char, int>::iterator it = mParameters.begin(); it != mParameters.end(); it++) {
            std::cout << std::string(1, it->first) + " => ";
            std::getline(std::cin, sTextLine);
            if (!CStringHelper::bIsInt(sTextLine)) return NOT_A_NUMBER;
            iSetMapElement(it->first, std::stoi(sTextLine));
        }

    } else return NO_VARIABLES_FOUND;
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

    for (long i = (sArgs.size() - 1); i >= 0; i--) {
        if (!cCalculatorTree->bAdd(sArgs[i])) {
            return NO_EMPTY_LEAF;
        }
    }

    return cCalculatorTree->bCheckTree() ? 0 : EMPTY_NODE;
}

double CCalculatorMenager::dCalculate() {
    return cCalculatorTree->dCalculate(mParameters);
}

int CCalculatorMenager::iFindVariables() {
    if (mParameters.empty()) {
        std::vector<std::string> vSlices = CStringHelper::vSliceString(sTask);

        for (int i = 0; i < vSlices.size(); i++) {
            if (CCalculatorTree::bIsVariable(vSlices[i])) {
                iSetMapElement(vSlices[i][0], 1);
            }
        }

        if (mParameters.empty()) {
            return NO_VARIABLES_FOUND;
        } else {
            std::cout << sPrintVariables();
        }
    } else {
        std::cout << sPrintVariables();
    }
    return 0;

}

int CCalculatorMenager::iRepairTree() {
    cCalculatorTree->iRepairTree();
    this->sTask = cCalculatorTree->sGetPostfixSpace();
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

//######   Printers   #######//
std::string CCalculatorMenager::sPrintVariables() {
    std::string sReturn = "";

    for (std::map<char, int>::iterator it = mParameters.begin(); it != mParameters.end(); it++) {
        sReturn += std::string(1, it->first) + " => " + CStringHelper::sToString(it->second) + '\n';
    }

    return sReturn;
}

//////////////////////////////////
//////////   Private   ///////////

int CCalculatorMenager::iSetMapElement(char cLetter, int iValue) {
    mParameters[cLetter] = iValue;
    return 0;
}
