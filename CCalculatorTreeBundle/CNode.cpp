// Created by Jakub Nadolny on 25.11.2016.
#include "CNode.h"

//  Public
//  Constructors
CNode::CNode() {
    vConstructor("", nullptr, nullptr);
}

CNode::CNode(std::string sValue) {
    vConstructor(sValue, nullptr, nullptr);
}

CNode::CNode(CNode &nNode) {
    if (DEBUG) std::cout << "copy constructor allert" << std::endl;
}

//######    Getters   #######//
const std::string &CNode::sGetValue() const {
    return sValue;
}

CNode *CNode::nGetLeft() const {
    return nLeft;
}

CNode *CNode::nGetRight() const {
    return nRight;
}

//  Setters
void CNode::vSetValue(const std::string sValue) {
    if (DEBUG)
        std::cout << "Ustawiam " + (sGetValue() == "" ? "pusty węzeł" : sGetValue()) + " na " +
                     (sValue == "" ? "pusty węzeł" : sValue) << std::endl;
    this->sValue = sValue;
}

void CNode::vSetLeft(CNode *nLeft) {
    this->nLeft = nLeft;
}

void CNode::vSetRight(CNode *nRight) {
    this->nRight = nRight;
}

//  Printers
void CNode::vPrint() {
    std::cout << "Node : '" + sValue + "'" << std::endl;
}

//  Destructors
CNode::~CNode() {
    if (this->nGetLeft() != nullptr) delete nGetLeft();
    if (this->nGetRight() != nullptr) delete nGetRight();
    if (DEBUG) std::cout << "Usuwam " + (sGetValue() == "" ? "pusty węzeł" : sGetValue()) << std::endl;
}

//  Private
//  Utilities
void CNode::vConstructor(std::string sValue, CNode *nLeft, CNode *nRight) {
    this->sValue = sValue;
    this->nLeft = nLeft;
    this->nRight = nRight;

    if (DEBUG) std::cout << "Dodaję " + (sGetValue() == "" ? "pusty węzeł" : sGetValue()) << std::endl;
}
