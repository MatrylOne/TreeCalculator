//
// Created by Jakub Nadolny on 16.10.2016.
//

#include "HErrors.h"

int HErrors::vRecognizeError(int iError) {
    switch (iError) {
        case 0 :
            // Everything is ok
            break;
        case NUMBER_OUT_OF_RANGE :
            std::cout << "BŁĄD ! Liczba poza zakresem." << std::endl;
            break;
        case NUMBER_IS_NEGATIVE :
            std::cout << "BŁĄD ! : Podano ujemną liczbę." << std::endl;
            break;
        case NUMBER_NOT_POSITIVE :
            std::cout << "BŁĄD ! : Podano liczbę mneiszą, lub równą zero." << std::endl;
            break;
        case TEXT_IS_EMPTY :
            std::cout << "BŁĄD ! Podany tekst jest pusty." << std::endl;
            break;
        case WRONG_NUMBER_OF_ARGUMENTS :
            std::cout << "BŁĄD ! Podano błędną liczbę argumentów." << std::endl;
            break;
        case NOT_A_NUMBER :
            std::cout << "BŁĄD ! Podana wartość nie jest liczbą." << std::endl;
            break;
        case NOT_A_DOUBLE :
            std::cout << "BŁĄD ! Podana wartość nie jest liczbą zmiennoprzecinkową." << std::endl;
            break;
        case NOT_TEXT :
            std::cout << "BŁĄD ! Podana wartość nie jest tekstem." << std::endl;
            break;
        case WRONG_COMMAND :
            std::cout << "Nie ma takiej komendy. Wpisz HELP." << std::endl;
            break;
        case NO_EMPTY_LEAF :
            std::cout << "Liczba argumentów zbyt duża dla zadanych operatorów." << std::endl
                      << "Nadmiar został pominięty." << std::endl
                      << "Wpisz fix aby nie wyświetlać tego komunikatu." << std::endl;
            break;
        case EMPTY_NODE :
            std::cout << "Liczba argumentów zbyt mała dla zadanych operatorów." << std::endl
                      << "Brakujące argumenty wyświetlane jako []." << std::endl
                      << "Wpisz print aby wypisać wyrażenie." << std::endl
                      << "Wpisz infix aby wypisać wyrażenie w postaci infix'owej." << std::endl
                      << "Wpisz fix aby naprawić." << std::endl;
            break;
        case NO_VARIABLES_FOUND :
            std::cout << "Nie znaleziono zmiennych." << std::endl;
            break;
        case MAP_NOT_EMPTY :
            std::cout << "Mapa parametrów jest już ustawiona." << std::endl;
            break;
        default:
            std::cout << "NIEZNANY BŁĄD !!!" << std::endl;
            break;
    }
    return iError;
}
