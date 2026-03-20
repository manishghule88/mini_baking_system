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
    } else if ( mAcceptInput == 2 ) {
        depositMoney();
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
        
        mFile.open( accountsFileName, std::ios::app );

        if ( !mFile.is_open()) {
            std::cout << "Error: in creating file\n";
            return;
        }

        mFile << accountNumber << "|" << mName << "|" 
                << mInitialAmount << std::endl;

        mFile.close();
        std::cout << "Your Account Successfully Created\n";
        std::cout << "Account Number: " << accountNumber;
    } else {
        std::cout << "Please Deposit Sufficient amount to create account\n";
    }
}

bool BankingSystem::
findAccountInFile( double aExistAccountNumber ) {
        std::ifstream file( "accounts.dat" );

    if ( !file.is_open() ) {
        std::cout << "Error opening file\n";
        return false;
    }

    std::string line;

    while ( std::getline( file, line ) ) {
        
        // skip empty line
        if ( line.empty()) {
            continue;
        }
        
        // check if '|' exists
        size_t pos = line.find( "|" );
        if ( pos == std::string::npos ) {
            continue;
        }

        // extract account number part
        std::string accStr = line.substr( 0, pos );

        try {
            // convert safely
            int fileAccNo = std::stoi( accStr );

            // compare
            if ( fileAccNo == aExistAccountNumber ) {
                file.close();
                return true;
            }
        } catch ( ... ) {
            continue;
        }
    }

    file.close();
    return false;
}

void BankingSystem::
depositMoney() {
    double existAccountNumber = 0.0f;
    int depositAmount = 0;
    int totalAmount = 0;
    bool foundAccount = false;

    std::cout << "Enter Account Number:" << std::endl;
    std::cin >> existAccountNumber;

    foundAccount = findAccountInFile( existAccountNumber );
    
    if ( foundAccount ) {
        std::cout << "Account Found!" << std::endl;
    } else {
        std::cout << "Account not Found!" << std::endl;
        return;
    }
    
    std::cout << "Please enter the amout that you want to deposit" << std::endl;
    std::cin >> depositAmount;

    std::ifstream inFile( accountsFileName );
    std::ofstream tempFile( "temp.dat" );
    std::string line;

    while ( std::getline( inFile, line )) {
        if ( line.empty()) {
            continue;
        }

        size_t pos1 = line.find( "|" );
        size_t pos2 = line.find( "|", pos1 + 1 );

        int accNo = std::stoi( line.substr( 0, pos1 ));
        std::string name = line.substr( pos1 + 1, pos2 - pos1 - 1 );
        int balance = std::stoi( line.substr( pos2 + 1 )); 

        if ( accNo == existAccountNumber ) {
            totalAmount = balance + depositAmount;
            std::cout << "Deposit Successfully!" << std::endl;
            std::cout << "Updated Balance: " << totalAmount << std::endl;
        }

        tempFile << accNo << "|" << name << "|" << totalAmount << std::endl;
    }

    inFile.close();
    tempFile.close();

    remove( "accounts.dat" );
    rename( "temp.dat", "accounts.dat" );
}