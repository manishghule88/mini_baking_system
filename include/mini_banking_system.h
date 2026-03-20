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
        int mTotalAmount = 0;
        double mExistAccountNumber = 0.0f;
        bool mFoundAccount = false;
        std::string mName;
        std::ofstream mFile;
        std::string accountsFileName = "accounts.dat";

        /// Displays the banking menu and processes user input
        /// The user to select and action and calls corresponding
        /// function based on the selected option.
        void showMenu();

        /// Creates a new bank account with user details/
        /// Collects user name and initial deposit amount validates
        /// the minimum requirement, generates a unique account
        /// number and stores the account details in a file.
        void createAccout();

        /// Generates a unique account number.
        /// Reads the account file extracts the last valid account
        /// number and returns a new incremented account number.
        /// @return double
        ///     Newly generated unique account number.
        double uniqueNumberGeneration();

        /// Deposits money into an existing bank account.
        /// Verifies the account number, accepts a deposit amount,
        /// updates the account balance in the file, and rewrites the
        /// updated data using a temporary file.
        ///
        void depositMoney();
        
        /// Checks whether an account exists in the file.
        /// Reads the accounts file line by line extracts the account
        /// number, and compares it with the given account number.
        ///
        /// @param[ in ] aExistAccountNumber
        ///          Account number to search for
        /// @return true
        ///     true if account is found false otherwise
        bool findAccountInFile( double aExistAccountNumber );

        void withdrawMoney();

        void viewAllAccounts();
};

#endif