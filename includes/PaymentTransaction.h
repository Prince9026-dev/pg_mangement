
#pragma once
#include <string>

class PaymentTransaction {
private:
    static int nextTransactionId;

    int transactionId;
    double transactionAmount;
    std::string date;
    std::string transactionMethod;

public:
    PaymentTransaction(
        double amount,
        std::string date,
        std::string method
    );

    int getTransactionId() const;
    double getTransactionAmount() const;
    std::string getDate() const;
    std::string getTransactionMethod() const;
};
