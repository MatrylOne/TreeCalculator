//
// Created by Jakub Nadolny on 16.10.2016.
//

#ifndef FIRST_HERRORS_H
#define FIRST_HERRORS_H

#include <iostream>

///////////////////////////
//////////////////////////
// Numbers errors

#define NUMBER_OUT_OF_RANGE 1
#define NUMBER_IS_NEGATIVE 2
#define NUMBER_NOT_POSITIVE 3

// Texts errors
#define TEXT_IS_EMPTY 10
#define WRONG_NUMBER_OF_ARGUMENTS 11
#define WRONG_COMMAND 12

// Type errors
#define NOT_A_NUMBER 100
#define NOT_TEXT 101
#define NOT_A_DOUBLE 102

// Data errors
#define NO_EMPTY_LEAF 200
#define EMPTY_NODE 201
#define NO_VARIABLES_FOUND 202
#define MAP_NOT_EMPTY 203
#define NODE_NOT_FOUND 204

///////////////////////////
///////////////////////////

class HErrors {
public :
    static int vRecognizeError(int iError);
};

#endif //FIRST_HERRORS_H
