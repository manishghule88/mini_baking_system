#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <algorithm>

#include "mini_banking_system.h"

using namespace std;

BankingSystem::
BankingSystem() {
    // Nothing to do yet
}

void BankingSystem::
start() {
    showMenu();
}

void BankingSystem::
showMenu() {
    
    std::cout << "Actions that you perform as per your need\n";
    std::cin >> mAcceptInput;

    if ( mAcceptInput == 1 ) {
        createAccout();
    }
}

double BankingSystem::
uniqueNumberGeneration() {
    ifstream file( accountsFileName );
    string line;
    int lastAccount = 100000;

    while( getline( file, line )) {
        size_t first = line.find( '|' );
        size_t second = line.find( '|', first + 1 );

        if ( first != string::npos && second != string::npos ) {
            string accStr = line.substr( first + 1, 
                    second - first - 1 );

            if ( !accStr.empty() && all_of( accStr.begin(), 
                    accStr.end(), ::isdigit )) 
            {
                int acc = stoi( accStr );
                lastAccount = acc;
            }
        }
    }
    return lastAccount + 1;
}

void BankingSystem::
createAccout() {
    std::cout << "You Select Account Creation : \n";

    std::cout << "Enter Your Name:\n";
    std::cin >> mName;

    std::cout << "To Create Accout You Need to pay minimum 1000 Rs\n";
    std::cin >> mInitialAmount;

    double accountNumber = uniqueNumberGeneration();

    if ( mInitialAmount >= 1000 ) {
        
        std::ofstream mFile;
        mFile.open( accountsFileName, std::ios::app );

        if ( !mFile.is_open()) {
            std::cout << "Error: in creating file\n";
            return;
        }

        mFile <<"|" << accountNumber << "|" << mName << "|" 
                << mInitialAmount << std::endl;

        mFile.close();
        std::cout << "Your Account Successfully Created\n";
        std::cout << "Account Number: " << accountNumber;
    } else {
        std::cout << "Please Deposit Sufficient amount to create account\n";
    }
}