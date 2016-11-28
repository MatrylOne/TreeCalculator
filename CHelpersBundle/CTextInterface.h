//
// Created by Jakub Nadolny on 15.11.2016.
//

#ifndef SECOND_GEO_CTEXTINTERFACE_H
#define SECOND_GEO_CTEXTINTERFACE_H


#include <string>
#include "CStringHelper.h"
#include "HErrors.h"
#include "../CCalculatorTreeBundle/CCalculatorMenager.h"

class CTextInterface {
public:
    CTextInterface();

    ~CTextInterface();

    void vBegin();

    int iRunCommand(std::string sCommand);

    void vPrintHello();

    void vPrintHelp();

    void vPrintBash();

private:
    bool bContinue;
    CCalculatorMenager *cManager;
};


#endif //SECOND_GEO_CTEXTINTERFACE_H
