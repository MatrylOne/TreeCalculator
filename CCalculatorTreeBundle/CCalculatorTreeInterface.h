// Created by Jakub Nadolny on 15.11.2016.

#ifndef SECOND_GEO_CTEXTINTERFACE_H
#define SECOND_GEO_CTEXTINTERFACE_H

#include <string>
#include <vector>

#include "../CHelpersBundle/CStringHelper.h"
#include "../CHelpersBundle/HErrors.h"
#include "../CHelpersBundle/HCommands.h"
#include "../CHelpersBundle/HDefaults.h"

#include "CCalculatorManager.h"

class CCalculatorTreeInterface {
private:
    bool bContinue;
    CCalculatorManager *cManager;

public:
    CCalculatorTreeInterface();

    void vBegin();
    void vPrintHello();
    void vPrintHelp();
    void vPrintBash();

    std::string vPrintErrors();

    int iRunCommand(std::string sCommand);

    ~CCalculatorTreeInterface();
};

#endif //SECOND_GEO_CTEXTINTERFACE_H
