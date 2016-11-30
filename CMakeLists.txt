cmake_minimum_required(VERSION 3.6)
project(ZMPO3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++03")

set(SOURCE_FILES main.cpp CHelpersBundle/CStringHelper.h CHelpersBundle/CStringHelper.cpp CCalculatorTreeBundle/CCalculatorTreeInterface.h CCalculatorTreeBundle/CCalculatorTreeInterface.cpp CHelpersBundle/HDefaults.h CHelpersBundle/HErrors.cpp CCalculatorTreeBundle/CNode.cpp CCalculatorTreeBundle/CNode.h CCalculatorTreeBundle/CCalculatorTree.cpp CCalculatorTreeBundle/CCalculatorTree.h CHelpersBundle/CCalculatorHelper.cpp CHelpersBundle/CCalculatorHelper.h CCalculatorTreeBundle/CCalculatorManager.cpp CCalculatorTreeBundle/CCalculatorManager.h CHelpersBundle/HCommands.cpp CHelpersBundle/HCommands.h)
add_executable(ZMPO3 ${SOURCE_FILES})