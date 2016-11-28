//
// Created by Jakub Nadolny on 25.11.2016.
//

#include "CCalculatorTree.h"
#include "../CHelpersBundle/CCalculatorHelper.h"
#include "../CHelpersBundle/CStringHelper.h"

/////////////////////////////////
//////////   Public   ///////////

//######   Constructors #######//
CCalculatorTree::CCalculatorTree() {
    vInitialize();
}

//######  Destructors #######//
CCalculatorTree::~CCalculatorTree() {
    vClean();
}

//######   Getters   #######//
CNode *CCalculatorTree::nGetRoot() {
    return this->nRoot;
}

std::string CCalculatorTree::sGetPostfix() {
    return shGetPostfix(nRoot);
}

std::string CCalculatorTree::sGetPostfixSpace() {
    return shGetPostfixSpace(nRoot);
}

//######   Setters   #######//
bool CCalculatorTree::bAdd(std::string sSymbol) {
    return bhAdd(nRoot, sSymbol);
}

//######   Printers   #######//
std::string CCalculatorTree::sInfix() {
    return shInfix(nRoot);
}

//######   Tools   #######//
void CCalculatorTree::vClean() {
    vhClean(nRoot);
}

void CCalculatorTree::vInitialize() {
    this->nRoot = new CNode("");
}

double CCalculatorTree::dCalculate() {
    return dhCalculate(nRoot);
}

int CCalculatorTree::iRepairTree() {
    return ihRepairTree(nRoot);
}

//######   Checkers   #######//
bool CCalculatorTree::bCheckTree() {
    return bhCheckTree(nRoot);
}

/////////////////////////////////
//////////   Private   /////////

//######   Getters   #######//
std::string CCalculatorTree::shGetPostfix(CNode *cCurrent) {
    if (cCurrent != nullptr) {
        std::string left = shGetPostfix(cCurrent->nGetLeft());
        std::string right = shGetPostfix(cCurrent->nGetRight());
        return left + right + (cCurrent->sGetValue() == "" ? "[] " : (cCurrent->sGetValue() + " "));
    } else {
        return "";
    }
}

std::string CCalculatorTree::shGetPostfixSpace(CNode *cCurrent) {
    if (cCurrent != nullptr) {
        std::string left = shGetPostfixSpace(cCurrent->nGetLeft());
        std::string right = shGetPostfixSpace(cCurrent->nGetRight());
        return left + right + (cCurrent->sGetValue() == "" ? "" : (cCurrent->sGetValue() + " "));
    } else {
        return "";
    }
}

//######   Printers   #######//
std::string CCalculatorTree::shInfix(CNode *cCurrent) {
    if (cCurrent != nullptr) {
        std::string left = shInfix(cCurrent->nGetLeft());
        std::string right = shInfix(cCurrent->nGetRight());
        return "(" + right + (cCurrent->sGetValue() == "" ? "[]" : ((right == "" ? "" : " ") + cCurrent->sGetValue() +
                                                                    (left == "" ? "" : " "))) + left + ")";
    } else {
        return "";
    }
}

//######   Tools   #######//
bool CCalculatorTree::bhAdd(CNode *cCurrent, std::string sSymbol) {
    if (cCurrent != nullptr) {
        if (cCurrent->sGetValue() == "") {
            cCurrent->vSetValue(sSymbol);
            if (CCalculatorHelper::bIsOperator(sSymbol)) {
                cCurrent->vSetLeft(new CNode(""));
                if (sSymbol != "~") cCurrent->vSetRight(new CNode(""));
            }
            return true;
        } else {
            bool right = bhAdd(cCurrent->nGetRight(), sSymbol);
            if (!right) {
                return bhAdd(cCurrent->nGetLeft(), sSymbol);
            }
            return right;
        }
    } else {
        return false;
    }
}

void CCalculatorTree::vhClean(CNode *cCurrent) {
    if (cCurrent != nullptr) {
        vhClean(cCurrent->nGetLeft());
        vhClean(cCurrent->nGetRight());

        delete cCurrent;
    }
}

double CCalculatorTree::dhCalculate(CNode *cCurrent) {
    if (CCalculatorHelper::bIsOperator(cCurrent->sGetValue())) {
        if (cCurrent->sGetValue() == "~") {
            // Jeżeli to tylda (tylko lewy węzeł)
            return CCalculatorHelper::dCount(cCurrent->sGetValue(), dhCalculate(cCurrent->nGetLeft()), 0);
        } else if (!CCalculatorHelper::bIsOperator(cCurrent->nGetLeft()->sGetValue()) &&
                   !CCalculatorHelper::bIsOperator(cCurrent->nGetRight()->sGetValue())) {
            // jeżeli lewy i prawy węzeł to nie operator
            // CCalculatorHelper wykrywa jaką operację ma wykonać
            return CCalculatorHelper::dCount(cCurrent->sGetValue(), cCurrent->nGetLeft()->sGetValue(),
                                             cCurrent->nGetRight()->sGetValue());
        } else if (!CCalculatorHelper::bIsOperator(cCurrent->nGetLeft()->sGetValue()) &&
                   CCalculatorHelper::bIsOperator(cCurrent->nGetRight()->sGetValue())) {
            // jeżeli prawy węzeł to operator a lewy nie
            return CCalculatorHelper::dCount(cCurrent->sGetValue(), cCurrent->nGetLeft()->sGetValue(),
                                             dhCalculate(cCurrent->nGetRight()));
        } else if (CCalculatorHelper::bIsOperator(cCurrent->nGetLeft()->sGetValue()) &&
                   !CCalculatorHelper::bIsOperator(cCurrent->nGetRight()->sGetValue())) {
            // jeżeli lewy węzeł to operator a prawy nie
            return CCalculatorHelper::dCount(cCurrent->sGetValue(), dhCalculate(cCurrent->nGetLeft()),
                                             cCurrent->nGetRight()->sGetValue());
        } else {
            // jeżeli oba węzły to operator
            return CCalculatorHelper::dCount(cCurrent->sGetValue(), dhCalculate(cCurrent->nGetLeft()),
                                             dhCalculate(cCurrent->nGetRight()));
        }
    }// wartość w węzła jest operatorem
    else {
        return std::stod(cCurrent->sGetValue());
    }// wartość węzła nie jest operatorem
}

int CCalculatorTree::ihRepairTree(CNode *cCurrent) {

    if (cCurrent != nullptr) {
        if (cCurrent->sGetValue() == "+" ||
            cCurrent->sGetValue() == "-") {
            // Jeśli operatorem jest dodawanie lub odejmowanie
            if (cCurrent->nGetLeft()->sGetValue() == "") { cCurrent->nGetLeft()->vSetValue("0"); }
            if (cCurrent->nGetRight()->sGetValue() == "") { cCurrent->nGetRight()->vSetValue("0"); }
        } else if (cCurrent->sGetValue() == "*" ||
                   cCurrent->sGetValue() == "/") {
            // Jeśli operatorem jest mnożenie lub dzielenie
            if (cCurrent->nGetLeft()->sGetValue() == "") { cCurrent->nGetLeft()->vSetValue("1"); }
            if (cCurrent->nGetRight()->sGetValue() == "") { cCurrent->nGetRight()->vSetValue("1"); }
        } else if (cCurrent->sGetValue() == "~") {
            // Jeśli operatorem jest mnożenie lub dzielenie
            if (cCurrent->nGetLeft()->sGetValue() == "") { cCurrent->nGetLeft()->vSetValue("0"); }
        }
        ////////    Część rekurencyjna    //////////
        ihRepairTree(cCurrent->nGetLeft());
        ihRepairTree(cCurrent->nGetRight());
    }

    return 0;
}

//######   Checkers   #######//
bool CCalculatorTree::bIsVariable(std::string sArgument) {
    return !CStringHelper::bIsInt(sArgument) && !CCalculatorHelper::bIsOperator(sArgument);
}

bool CCalculatorTree::bhCheckTree(CNode *cCurrent) {
    if (cCurrent != nullptr) {
        if (cCurrent->sGetValue() == "") {
            return false;
        } else {
            bool bTest = bhCheckTree(cCurrent->nGetLeft());
            if (bTest == true) bTest = bhCheckTree(cCurrent->nGetRight());
            return bTest;
        }
    } else {
        return true;
    }
}
