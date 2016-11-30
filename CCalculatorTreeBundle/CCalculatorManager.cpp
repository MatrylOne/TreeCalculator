//
// Created by Jakub Nadolny on 26.11.2016.
//
#include "CCalculatorManager.h"


/////////////////////////////////
//////////   Public   ///////////

//######   Constructors  #######//
CCalculatorManager::CCalculatorManager() {
	cCalculatorTree = new CCalculatorTree();
}

//######   Getters   #######//
std::string CCalculatorManager::sGetInfix() {
	return cCalculatorTree->sInfix();
}

std::string CCalculatorManager::sGetTreeTask() {
	return cCalculatorTree->sGetPostfix();
}

std::string CCalculatorManager::sGetTask() {
	return this->sTask;
}

std::string CCalculatorManager::sGetParsedTask() {
	return std::string("TODO - not ended");
}

void CCalculatorManager::vGetIssues(std::map<char, int> &mErrors) {
	cCalculatorTree->mGetIssues(mErrors);
}

//######   Setters   #######//
int CCalculatorManager::iSetTask(std::string sInput) {

	std::string sSeparated = sSeparateTask(sInput);

	this->sTask = sSeparated;
	this->sOriginalTask = sSeparated;

	mParameters.clear();
	iFindVariables();

	return 0;
}

int CCalculatorManager::iSetVariables() {
	if (!mParameters.empty()) {

		std::string sTextLine = "";

		for (std::map<char, int>::iterator it = mParameters.begin(); it != mParameters.end(); it++) {
			std::cout << std::string(1, it->first) + " => ";
			std::getline(std::cin, sTextLine);
			if (!CStringHelper::bIsInt(sTextLine)) return NOT_A_NUMBER;
			iSetMapElement(it->first, std::stoi(sTextLine));
		}

	} else return NO_VARIABLES_FOUND;
	return 0;
}

//######   Checkers   #######//
bool CCalculatorManager::bCheckTree() {
	return cCalculatorTree->bCheckTree();
}

//######   Tools   #######//
int CCalculatorManager::iConstructTree() {
	std::vector<std::string> sArgs = CStringHelper::vSliceString(sTask);

	cCalculatorTree->vClean();
	cCalculatorTree->vInitialize();

	for (long i = (sArgs.size() - 1); i >= 0; i--) {
		if (!cCalculatorTree->bAdd(sArgs[i])) {
			return NO_EMPTY_LEAF;
		}
	}

	return cCalculatorTree->bCheckTree() ? 0 : EMPTY_NODE;
}

int CCalculatorManager::iFindVariables() {
	if (mParameters.empty()) {
		std::vector<std::string> vSlices = CStringHelper::vSliceString(sTask);

		for (int i = 0; i < vSlices.size(); i++) {
			if (CCalculatorTree::bIsVariable(vSlices[i])) iSetMapElement(vSlices[i][0], 1);
		}

		if (mParameters.empty()) {
			return NO_VARIABLES_FOUND;
		} else {
			std::cout << sPrintVariables();
		}
	} else {
		std::cout << sPrintVariables();
	}
	return 0;
}

int CCalculatorManager::iRepairTree() {
	cCalculatorTree->iRepairTree();
	iUpdateTask();
	return 0;
}

int CCalculatorManager::iSearchAndRoot(std::string sArg) {
	int iReturn = cCalculatorTree->iSearchAndRoot(sArg);
	iUpdateTask();
	return iReturn;
}

double CCalculatorManager::dCalculate() {
	return cCalculatorTree->dCalculate(mParameters);
}

std::string CCalculatorManager::sSeparateTask(std::string sTask) {
	std::vector<std::string> sArgs = CStringHelper::vSliceString(sTask);
	std::string sReturn = "";

	for (int i = 0; i < sArgs.size(); i++) {
		if (sArgs[i].size() > 1 && !CStringHelper::bIsInt(sArgs[i])) {
			std::string sTemp = sArgs[i];
			int iTmpSize = sTemp.size();
			for (int j = 0; j < iTmpSize; j++) {
				sReturn += sTemp[j];
				if (sArgs[i] != "") sReturn += " ";
			}
		} else {
			if (sArgs[i] != "") sReturn += sArgs[i] + " ";
		}
	}

	return sReturn;
}

//######   Printers   #######//
std::string CCalculatorManager::sPrintVariables() {
	std::string sReturn = "";

	for (std::map<char, int>::iterator it = mParameters.begin(); it != mParameters.end(); it++) {
		sReturn += std::string(1, it->first) + " --> " + CStringHelper::sToString(it->second) + '\n';
	}

	return sReturn;
}

//######   Destructors  #######//
CCalculatorManager::~CCalculatorManager() {
	delete cCalculatorTree;
}

//////////////////////////////////
//////////   Private   ///////////

int CCalculatorManager::iSetMapElement(char cLetter, int iValue) {
	mParameters[cLetter] = iValue;
	return 0;
}

int CCalculatorManager::iUpdateTask() {
	this->sTask = cCalculatorTree->sGetPostfixSpace();
	return 0;
}
