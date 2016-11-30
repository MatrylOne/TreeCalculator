//
// Created by Jakub Nadolny on 25.11.2016.
//

#include "CCalculatorTree.h"

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

void CCalculatorTree::mGetIssues(std::map<char, int> &mErrors) {
    mhGetIssues(nRoot, mErrors);
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
    delete nRoot;
}

void CCalculatorTree::vInitialize() {
    this->nRoot = new CNode("");
}

double CCalculatorTree::dCalculate(std::map<char, int> &mParameters) {
    return dhCalculate(nRoot, mParameters);
}

int CCalculatorTree::iSearchAndRoot(std::string sArg) {
    return ihSearchAndRoot(nRoot, sArg);
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

void CCalculatorTree::mhGetIssues(CNode *cCurrent, std::map<char, int> &mErrors) {
    if (cCurrent != nullptr) {
        if (CCalculatorHelper::bIsOperator(cCurrent->sGetValue())) {
            if (cCurrent->nGetRight() != nullptr && cCurrent->nGetRight()->sGetValue() == "")
                mErrors[cCurrent->sGetValue()[0]] += 1;
            if (cCurrent->nGetLeft() != nullptr && cCurrent->nGetLeft()->sGetValue() == "")
                mErrors[cCurrent->sGetValue()[0]] += 1;

            mhGetIssues(cCurrent->nGetLeft(), mErrors);
            mhGetIssues(cCurrent->nGetRight(), mErrors);
        }
    }
}

//######   Printers   #######//
std::string CCalculatorTree::shInfix(CNode *cCurrent) {
    if (cCurrent != nullptr) {
        std::string left = shInfix(cCurrent->nGetLeft());
        std::string right = shInfix(cCurrent->nGetRight());
        return "(" + left + (cCurrent->sGetValue() == "" ? "[]" : ((left == "" ? "" : " ") +
                                                                   cCurrent->sGetValue() +
                                                                   (right == "" ? "" : " "))) + right + ")";
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
                cCurrent->vSetRight(new CNode(""));
                if (sSymbol != "~") cCurrent->vSetLeft(new CNode(""));
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

double CCalculatorTree::dhCalculate(CNode *cCurrent, std::map<char, int> &mParameters) {
    if (CCalculatorHelper::bIsOperator(cCurrent->sGetValue())) {
        if (cCurrent->sGetValue() == "~") {
            // Muszę sprawdzić bo tylda ma tylo jeden węzeł
            return CCalculatorHelper::dCount(cCurrent->sGetValue(), dhCalculate(cCurrent->nGetRight(), mParameters), 0);
        } else {
            return CCalculatorHelper::dCount(
                    cCurrent->sGetValue(),
                    dhCalculate(cCurrent->nGetLeft(), mParameters),
                    dhCalculate(cCurrent->nGetRight(), mParameters));
        }
    }// wartość w węzła jest operatorem
    else {
        // dMap zmienia wartość zmiennej na liczbę z mapy, lub zwraca doubla ze stringa
        return dMap(cCurrent->sGetValue(), mParameters);
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
            // Jeśli operatorem jest negacja
            if (cCurrent->nGetRight()->sGetValue() == "") { cCurrent->nGetRight()->vSetValue("0"); }
        }
        /////////////   Część rekurencyjna   ///////////////
        ihRepairTree(cCurrent->nGetLeft());
        ihRepairTree(cCurrent->nGetRight());
    }

    return 0;
}

int CCalculatorTree::ihSearchAndRoot(CNode *cNode, std::string sArg) {
    if (cNode != nullptr) {
        if ((cNode->sGetValue() + " ") == sArg) {
            // Jest już rootem
            std::cout << "jest juz rootem" << std::endl;
            return 0;
        } else {
            if (cNode->nGetLeft() != nullptr && (cNode->nGetLeft()->sGetValue() + " ") == sArg) {
                CNode *tmp = cNode->nGetLeft();
                cNode->vSetLeft(nullptr);
                vClean();
                nRoot = tmp;
                return 0;
            } else if (cNode->nGetRight() != nullptr && (cNode->nGetRight()->sGetValue() + " ") == sArg) {
                CNode *tmp = cNode->nGetRight();
                cNode->vSetRight(nullptr);
                vClean();
                nRoot = tmp;
                return 0;
            } else {
                int sReturn = ihSearchAndRoot(cNode->nGetLeft(), sArg);
                if (sReturn != 0) return ihSearchAndRoot(cNode->nGetRight(), sArg); else return sReturn;
            }
        }
    } else {
        return NODE_NOT_FOUND;
    }
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
            return bhCheckTree(cCurrent->nGetLeft()) && bhCheckTree(cCurrent->nGetRight());
        }
    }
    return true;
}

double CCalculatorTree::dMap(std::string sArg, std::map<char, int> &mParameters) {
    if (CCalculatorTree::bIsVariable(sArg)) return mParameters[sArg.c_str()[0]];
    return std::stod(sArg);
}
