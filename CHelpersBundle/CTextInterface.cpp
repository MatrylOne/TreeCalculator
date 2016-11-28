//
// Created by Jakub Nadolny on 15.11.2016.
//

#include <vector>
#include "CTextInterface.h"
#include "HCommands.h"
#include "HDefaults.h"

/////////////////////////////////
//////////   Public   ///////////

//######   Constructors #######//
CTextInterface::CTextInterface() {
    bContinue = true;
    this->cManager = new CCalculatorMenager();
}

//######  Destructors #######//
CTextInterface::~CTextInterface() {
    delete cManager;
}

//######  Tools #######//
void CTextInterface::vBegin() {
    bContinue = true;
    std::string sTextLine = "";

    vPrintHello();

    while (bContinue) {
        vPrintBash();
        std::getline(std::cin, sTextLine);
        HErrors::vRecognizeError(iRunCommand(sTextLine));
    }
}

int CTextInterface::iRunCommand(std::string sCommand) {
    std::vector<std::string> vArgs = CStringHelper::vSliceString(sCommand);
    if (vArgs.size() > 0) {

        if (vArgs[0] == COMMAND_INPUT) {
            if (vArgs.size() > 1) {
                int iAnswer = cManager->iSetTask(CStringHelper::sParseVector(vArgs, 1));
                if (iAnswer == 0) {
                    return cManager->iConstructTree();
                } else {
                    return iAnswer;
                }
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
                return cManager->iFindParameters();
            } else {
                return WRONG_NUMBER_OF_ARGUMENTS;
            }
        }

        if (vArgs[0] == COMMAND_SET) {
            if (vArgs.size() == 1) {
                return cManager->iSetParameters();
            } else {
                return WRONG_NUMBER_OF_ARGUMENTS;
            }
        }

        if (vArgs[0] == COMMAND_FIX) {
            if (vArgs.size() == 1) {
                return cManager->iRepairTree();
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
void CTextInterface::vPrintHello() {
    std::cout << "Witaj w programie" << std::endl;
    std::cout << "" + PROGRAM_NAME + " " + PROGRAM_VERSION << std::endl;
    std::cout << "Wpisz " + COMMAND_HELP + " aby uzyskac liste komend" << std::endl;
}

void CTextInterface::vPrintHelp() {
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

void CTextInterface::vPrintBash() {
    std::cout << std::endl << "#>";
}
