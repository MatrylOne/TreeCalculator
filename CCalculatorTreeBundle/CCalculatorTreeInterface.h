//
// Created by Jakub Nadolny on 15.11.2016.
//

#ifndef SECOND_GEO_CTEXTINTERFACE_H
#define SECOND_GEO_CTEXTINTERFACE_H


#include <string>
#include "../CHelpersBundle/CStringHelper.h"
#include "../CHelpersBundle/HErrors.h"
#include "CCalculatorMenager.h"

class CCalculatorTreeInterface {
public:
    CCalculatorTreeInterface();

    ~CCalculatorTreeInterface();

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
