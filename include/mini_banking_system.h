#ifndef MINI_BANKING_SYSTEM_H
#define MINI_BANKING_SYSTEM_H

class BankingSystem {

    public:
        BankingSystem();

        void start();

    private:
        int mAcceptInput = 0;
        int mInitialAmount = 0;
        std::string mName;

        void showMenu();
        void createAccout();
};

#endif