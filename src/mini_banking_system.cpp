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
    
    while ( true ) {

        std::cout << "1. Create Account" << std::endl;
        std::cout << "2. Deposit Money" << std::endl;
        std::cout << "3. Withdraw Money" << std::endl;
        std::cout << "4. View All Accounts" << std::endl;
        std::cout << "5. Close Account" << std::endl;
        std::cout << "0 Exit Program" << std::endl;
         
        std::cout << "Actions that you perform as per your need\n";
        std::cin >> mAcceptInput;
    
        if ( mAcceptInput == 1 ) {
            createAccout();
        } else if ( mAcceptInput == 2 ) {
            depositMoney();
        } else if ( mAcceptInput == 3 ) {
            withdrawMoney();
        } else if ( mAcceptInput == 4 ) {
            viewAllAccounts();
        } else if ( mAcceptInput == 5 ) {
            closeAccount();
        } else if ( mAcceptInput == 0 ) {
            std::cout << "Exiting Mini Banking System...\n";
            break;
        } else {
            std::cout << "Invalid option\n";
        }
    }
}

double BankingSystem::
uniqueNumberGeneration() {
    ifstream file( accountsFileName );
    string line;
    int lastAccount = 100000;

    while( getline( file, line )) {

        if ( line.empty()) {
            continue;
        }

        size_t pos = line.find( '|' );
        if ( pos == std::string::npos ) {
            continue;
        }

        std::string accStr = line.substr( 0, pos );

        try {
            int acc = std::stoi( accStr );
            lastAccount = acc;
        } catch ( ... ) {
            continue;
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
    std::cout << "\n";

    double accountNumber = uniqueNumberGeneration();
    std::cout << "Account number : " << accountNumber << std::endl;
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
        std::cout << "Account Number: " << accountNumber << "\n";
        std::cout << "\n------------------------------------------\n";
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
    int depositAmount = 0;

    std::cout << "Enter Account Number:" << std::endl;
    std::cin >> mExistAccountNumber;

    mFoundAccount = findAccountInFile( mExistAccountNumber );
    
    std::cout << "\n------------------------------------------\n";
    if ( mFoundAccount ) {
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

        if ( accNo == mExistAccountNumber ) {
            mTotalAmount = balance + depositAmount;
            std::cout << "Deposit Successfully!" << std::endl;
            std::cout << "Updated Balance: " << mTotalAmount << std::endl;
            std::cout << "\n------------------------------------------\n";
        }

        tempFile << accNo << "|" << name << "|" << mTotalAmount << std::endl;
    }

    inFile.close();
    tempFile.close();

    remove( "accounts.dat" );
    rename( "temp.dat", "accounts.dat" );
}

void BankingSystem::
withdrawMoney() {
    int withdrawAmount = 0;

    std::cout << "Enter Account Number:" << std::endl;
    std::cin >> mExistAccountNumber;

    mFoundAccount = findAccountInFile( mExistAccountNumber );
    
    std::cout << "\n------------------------------------------\n";
    if ( mFoundAccount ) {
        std::cout << "Account Found!" << std::endl;
    } else {
        std::cout << "Account not Found!" << std::endl;
        return;
    }

    std::cout << "Please enter the amout that you want to withdraw" << std::endl;
    std::cin >> withdrawAmount;

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

        if ( accNo == mExistAccountNumber ) {
            mTotalAmount = balance - withdrawAmount;
            std::cout << "Withdraw Money Successfully!" << std::endl;
            std::cout << "Updated Balance: " << mTotalAmount << std::endl;
            std::cout << "\n------------------------------------------\n";
        }

        tempFile << accNo << "|" << name << "|" << mTotalAmount << std::endl;
    }    

    inFile.close();
    tempFile.close();

    remove( "accounts.dat" );
    rename( "temp.dat", "accounts.dat" );
}

void BankingSystem::
viewAllAccounts() {

    std::ifstream inFile( accountsFileName );
    std::string line;

    std::cout << "\n-------- All Accounts ---------\n"; 
    while ( std::getline( inFile, line )) {
        if ( line.empty()) {
            continue;
        }

        size_t pos1 = line.find( "|" );
        size_t pos2 = line.find( "|", pos1 + 1 );

        std::string accNo = line.substr( 0, pos1 );
        std::string name  = line.substr( pos1 + 1, pos2 - pos1 - 1 );
        std::string bal   = line.substr( pos2 + 1 );

        std::cout << "Account No: " << accNo
                  << " | Name: " << name
                  << " | Balance: " << bal << std::endl;
        std::cout << "\n------------------------------------------\n";
    }

    inFile.close();
}

void BankingSystem::
closeAccount() {

    bool found = false;

    std::cout << "Enter Account Number to close account permentantly :" << std::endl;
    std::cin >> mExistAccountNumber;

    mFoundAccount = findAccountInFile( mExistAccountNumber );
    
    std::cout << "\n------------------------------------------\n";
    if ( mFoundAccount ) {
        std::cout << "Account Found!" << std::endl;
    } else {
        std::cout << "Account not Found!" << std::endl;
        return;
    }

    std::ifstream inFile( accountsFileName );
    std::ofstream tempFile( "temp.dat" );
    
    if ( !inFile.is_open() || !tempFile.is_open()) {
        std::cout << "Error opening file\n";
        return;
    }

    std::string line;

    while ( std::getline( inFile, line )) {
        if ( line.empty()) {
            continue;
        }

        size_t pos1 = line.find( "|" );

        int accNo = std::stoi( line.substr( 0, pos1 ));

        if ( accNo == mExistAccountNumber ) {
            found = true;
            std::cout << "Account Closed Successfully" << std::endl;
            std::cout << "\n------------------------------------------\n";
            continue;
        }

        tempFile << line << std::endl;
    }

    inFile.close();
    tempFile.close();

    remove( "accounts.dat" );
    rename( "temp.dat", "accounts.dat" );

    if ( !found ) {
        std::cout << "Account not found\n";
    }
}