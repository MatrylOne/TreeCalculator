//
// Created by Jakub Nadolny on 15.11.2016.
//

#include "CCalculatorTreeInterface.h"

/////////////////////////////////
//////////   Public   ///////////

//######   Constructors #######//
CCalculatorTreeInterface::CCalculatorTreeInterface() {
    bContinue = true;
    this->cManager = new CCalculatorMenager();
}

//######  Destructors #######//
CCalculatorTreeInterface::~CCalculatorTreeInterface() {
    delete cManager;
}

//######  Tools #######//
void CCalculatorTreeInterface::vBegin() {
    bContinue = true;
    std::string sTextLine = "";

    vPrintHello();

    while (bContinue) {
        vPrintBash();
        std::getline(std::cin, sTextLine);
        HErrors::vRecognizeError(iRunCommand(sTextLine));
    }
}

int CCalculatorTreeInterface::iRunCommand(std::string sCommand) {
    std::vector<std::string> vArgs = CStringHelper::vSliceString(sCommand);
    if (vArgs.size() > 0) {

        if (vArgs[0] == COMMAND_INPUT) {
            if (vArgs.size() > 1) {
                cManager->iSetTask(CStringHelper::sParseVector(vArgs, 1));
                int iReturn = cManager->iConstructTree();
                if (iReturn != 0) {
                    std::cout << std::endl;
                    std::cout << cManager->sGetTreeTask() << std::endl << std::endl;
                    std::cout << vPrintErrors() << std::endl;
                }
                return iReturn;
            } else {
                return WRONG_NUMBER_OF_ARGUMENTS;
            }
        }

        if (vArgs[0] == COMMAND_PRINT) {
            if (vArgs.size() == 1) {
                std::cout << cManager->sGetTreeTask() << std::endl;
                if (!cManager->bCheckTree()) return EMPTY_NODE;
                return 0;
            } else {
                return WRONG_NUMBER_OF_ARGUMENTS;
            }
        }

        if (vArgs[0] == COMMAND_INFIX) {
            if (vArgs.size() == 1) {
                std::cout << cManager->sGetInfix() << std::endl;
                if (!cManager->bCheckTree()) return EMPTY_NODE;
                return 0;
            } else {
                return WRONG_NUMBER_OF_ARGUMENTS;
            }
        }

        if (vArgs[0] == COMMAND_VARIABLES) {
            if (vArgs.size() == 1) {
                return cManager->iFindVariables();
            } else {
                return WRONG_NUMBER_OF_ARGUMENTS;
            }
        }

        if (vArgs[0] == COMMAND_SET) {
            if (vArgs.size() == 1) {
                return cManager->iSetVariables();
            } else {
                return WRONG_NUMBER_OF_ARGUMENTS;
            }
        }

        if (vArgs[0] == COMMAND_FIX) {
            if (vArgs.size() == 1) {
                cManager->iRepairTree();
                std::cout << cManager->sGetTreeTask() << std::endl;
                return 0;
            } else {
                return WRONG_NUMBER_OF_ARGUMENTS;
            }
        }

        if (vArgs[0] == COMMAND_CALCULATE) {
            if (vArgs.size() == 1) {
                int iStatus = cManager->iConstructTree();
                if (iStatus == 0) {
                    std::cout << "Wynik operacji : " + CStringHelper::sDoubleToString(cManager->dCalculate())
                              << std::endl;
                    return 0;
                } else {
                    return iStatus;
                }
            } else {
                return WRONG_NUMBER_OF_ARGUMENTS;
            }
        }

        if (vArgs[0] == COMMAND_HELP) {
            if (vArgs.size() == 1) {
                vPrintHelp();
                return 0;
            } else {
                return WRONG_NUMBER_OF_ARGUMENTS;
            }
        }

        if (vArgs[0] == COMMAND_EXIT) {
            if (vArgs.size() == 1) {
                bContinue = false;
                return 0;
            } else {
                return WRONG_NUMBER_OF_ARGUMENTS;
            }
        }

        return WRONG_COMMAND;

    }//if(vArgs.size() > 0)
    else {
        return TEXT_IS_EMPTY;
    }
}

//######  Printers #######//
void CCalculatorTreeInterface::vPrintHello() {
    std::cout << "Witaj w programie" << std::endl;
    std::cout << "" + PROGRAM_NAME + " " + PROGRAM_VERSION << std::endl;
    std::cout << "Wpisz " + COMMAND_HELP + " aby uzyskac liste komend" << std::endl;
}

void CCalculatorTreeInterface::vPrintHelp() {
    std::cout << "////// JAKUB NADOLNY //////" << std::endl;
    std::cout << "////// " + PROGRAM_NAME + " " + PROGRAM_VERSION + " //////" << std::endl;
    std::cout << "////// LISTA KOMEND  //////" << std::endl;
    std::cout << "" << std::endl;
    std::cout << DEFINITION_INPUT << std::endl;
    std::cout << COMMAND_INPUT + " <wyrażenie>" << std::endl;
    std::cout << "" << std::endl;
    std::cout << DEFINITION_PRINT << std::endl;
    std::cout << COMMAND_PRINT << std::endl;
    std::cout << "" << std::endl;
    std::cout << DEFINITION_INFIX << std::endl;
    std::cout << COMMAND_INFIX << std::endl;
    std::cout << "" << std::endl;
    std::cout << DEFINITION_VARIABLES << std::endl;
    std::cout << COMMAND_VARIABLES << std::endl;
    std::cout << "" << std::endl;
    std::cout << DEFINITION_SET << std::endl;
    std::cout << COMMAND_SET << std::endl;
    std::cout << "" << std::endl;
    std::cout << DEFINITION_FIX << std::endl;
    std::cout << COMMAND_FIX << std::endl;
    std::cout << "" << std::endl;
    std::cout << DEFINITION_CALCULATE << std::endl;
    std::cout << COMMAND_CALCULATE << std::endl;
    std::cout << "" << std::endl;
    std::cout << DEFINITION_HELP << std::endl;
    std::cout << COMMAND_HELP << std::endl;
    std::cout << "" << std::endl;
    std::cout << DEFINITION_EXIT << std::endl;
    std::cout << COMMAND_EXIT << std::endl;
}

void CCalculatorTreeInterface::vPrintBash() {
    std::cout << std::endl << "#>";
}

std::string CCalculatorTreeInterface::vPrintErrors() {
    std::map<char, int> mErrors;
    std::string sReturn = "";
    cManager->mGetIssues(mErrors);

    if (!mErrors.empty()) {
        for (std::map<char, int>::iterator it = mErrors.begin(); it != mErrors.end(); it++) {
            sReturn +=
                    std::string(1, it->first) + " => " + CStringHelper::sToString(it->second) + " pustych argumentów." +
                    '\n';
        }
    }

    return sReturn;
}
