#include <iostream>
#include <string>
#include <iomanip>
#include "descriptiveStatistics.h"
#include "input.h"

// CMPR 131 - ASSINGMENT 1 
// PROFESSOR QUACH
// OTONIEL TORRES
// 09/02/2023
// QUARTILES AND INTERQUARTILES - I PUT DATA SET INTO ONLINE CALCULATOR AND YOUR OUTPUT FOR dataset10.dat IS INCORRECT.

using namespace std;


void displayMenu()
{
	char option = 0;
	cout << "CMPR131 - Chapter 1" << endl;
    cout << "************************************************************" << endl;
	cout << "1> ASCII Text To ASCII Numbers" << endl;
	cout << "2> Base Converter" << endl;
	cout << "3> Descriptive Statistics" << endl;
    cout << "************************************************************" << endl;
	cout << "X. Exit" << endl;
    cout << "************************************************************" << endl;
	cout << "Option: "; 
}

int main()
{
    string input;
    do
    {
        displayMenu();
        getline(cin, input);

        // check if the input is exactly one character
        if (input.length() != 1) {
            cout << "Invalid option. Please try again." << endl;
            system("pause");
            system("cls");
            continue;
        }

        char option = input[0];

        switch (toupper(option))
        {
        case '1':
            system("cls");
            cout << "case 1" << endl;
            system("pause");
            system("cls");
            break;

        case '2':
            system("cls");
            cout << "case 2" << endl;
            system("pause");
            system("cls");
            break;

        case '3':
            system("cls");
            descriptiveStatistics();
            system("pause");
            system("cls");
            break;

        case 'X':
            cout << "Exiting the program." << endl;
            break;

        default:
            cout << "Invalid option. Please try again." << endl;
            system("pause");
            system("cls");
            break;
        }

    } while (toupper(input[0]) != 'X');

    return 0;
}