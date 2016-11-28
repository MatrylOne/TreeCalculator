//
// Created by Jakub Nadolny on 25.11.2016.
//

#ifndef ZMPO3_CNODE_H
#define ZMPO3_CNODE_H

#include <string>
#include <iostream>

class CNode {
public:
    CNode();

    CNode(CNode &nNode);

    CNode(std::string sValue);

    ~CNode();

    const std::string &sGetValue() const;

    void vSetValue(const std::string sValue);

    CNode *nGetLeft() const;

    void vSetLeft(CNode *nLeft);

    CNode *nGetRight() const;

    void vSetRight(CNode *nRight);

    void vPrint();


private:
    std::string sValue;
    CNode *nLeft;
    CNode *nRight;

    void vConstructor(std::string sValue, CNode *nLeft, CNode *nRight);
};

#endif //ZMPO3_CNODE_H
