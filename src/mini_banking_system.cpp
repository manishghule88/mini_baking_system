#include <iostream>
#include <string>
#include <fstream>
#include <random>

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
    random_device radDevice;
    mt19937 get( radDevice());

    uniform_int_distribution<> dist( 0, 999999 );

    return dist( radDevice );
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

        mFile <<"|" << accountNumber << "|" << mName << "|" << mInitialAmount << std::endl;

        mFile.close();
        std::cout << "Your Account Successfully Created\n";
    } else {
        std::cout << "Please Deposit Sufficient amount to create account\n";
    }
}