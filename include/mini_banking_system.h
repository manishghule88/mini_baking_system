#ifndef MINI_BANKING_SYSTEM_H
#define MINI_BANKING_SYSTEM_H

#include <fstream>

class BankingSystem {

    public:
        BankingSystem();

        void start();

    private:
        int mAcceptInput = 0;
        int mInitialAmount = 0;
        std::string mName;
        std::ofstream mFile;
        std::string accountsFileName = "accounts.dat";

        void showMenu();
        void createAccout();
        double uniqueNumberGeneration();
        void depositMoney();
        bool findAccountInFile( double aExistAccountNumber );
};

#endif