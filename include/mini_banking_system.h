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

        /// Withdraws money from an existing bank account
        /// Verifies the account number, accept a withdrawal amount, 
        /// updates the account balance, rewrites the updated data to the file
        /// usiing a temporary file.
        void withdrawMoney();

        /// Display all accounts stored in the file.
        /// Reads the accounts file line by line parses account number,
        /// name, and balance and prints them to the console.
        void viewAllAccounts();

        /// Closes and existing bank account.
        /// Function verifies the account number removes the corresponding
        /// account entry from the file and rewrities the remaining data
        /// using a temporary file.
        void closeAccount();
};

#endif