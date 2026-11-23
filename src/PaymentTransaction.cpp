
#include "PaymentTransaction.h"

int PaymentTransaction::nextTransactionId = 0;

PaymentTransaction::PaymentTransaction(
    double amount,
    std::string date,
    std::string method
)
    : transactionId(++nextTransactionId),
      transactionAmount(amount),
      date(date),
      transactionMethod(method) {}

int PaymentTransaction::getTransactionId() const {
    return transactionId;
}

double PaymentTransaction::getTransactionAmount() const {
    return transactionAmount;
}

std::string PaymentTransaction::getDate() const {
    return date;
}

std::string PaymentTransaction::getTransactionMethod() const {
    return transactionMethod;
}
