// Created by Jakub Nadolny on 25.11.2016.
#ifndef ZMPO3_CNODE_H
#define ZMPO3_CNODE_H

#include <string>
#include <iostream>

#include "../CHelpersBundle/HDefaults.h"

class CNode {
private:
    // Private atributes
    std::string sValue;
    CNode *nLeft;
    CNode *nRight;

public:
    CNode();
    CNode(CNode &nNode);
    CNode(std::string sValue);

    CNode *nGetLeft() const;
    CNode *nGetRight() const;

    const std::string &sGetValue() const;

    void vSetValue(const std::string sValue);
    void vSetRight(CNode *nRight);
    void vSetLeft(CNode *nLeft);
    void vPrint();

    ~CNode();

private:
    void vConstructor(std::string sValue, CNode *nLeft, CNode *nRight);
};

#endif
