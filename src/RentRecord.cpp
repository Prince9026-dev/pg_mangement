
#include "RentRecord.h"
#include <iostream>

RentRecord::RentRecord(
    int tid,
    std::string sd,
    std::string ed,
    std::string dd,
    double tr,
    std::string st
)
    : tenantId(tid),
      startDate(sd),
      endDate(ed),
      dueDate(dd),
      totalRent(tr),
      status(st) {}

int RentRecord::getTenantId() const {
    return tenantId;
}

std::string RentRecord::getStartDate() const {
    return startDate;
}

std::string RentRecord::getEndDate() const {
    return endDate;
}

std::string RentRecord::getDueDate() const {
    return dueDate;
}

double RentRecord::getTotalRent() const {
    return totalRent;
}

std::string RentRecord::getStatus() const {
    return status;
}

void RentRecord::addPayment(
    const PaymentTransaction& payment
) {
    transactions.push_back(payment);
    updateStatus();
}

double RentRecord::getTotalPaid() const {
    double totalAmount = 0;

    for (const auto& transaction : transactions) {
        totalAmount += transaction.getTransactionAmount();
    }

    return totalAmount;
}

double RentRecord::getRemainingAmount() const {
    return totalRent - getTotalPaid();
}

void RentRecord::updateStatus() {
    if (getRemainingAmount() <= 0) {
        status = "Paid";
    }
    else if (getTotalPaid() > 0) {
        status = "Partial";
    }
    else {
        status = "Pending";
    }
}

void RentRecord::displayPaymentHistory() const {
    std::cout << "\nPAYMENT HISTORY\n";

    for (const auto& transaction : transactions) {
        std::cout << "Transaction ID: "
                  << transaction.getTransactionId() << std::endl;

        std::cout << "Amount: "
                  << transaction.getTransactionAmount() << std::endl;

        std::cout << "Date: "
                  << transaction.getDate() << std::endl;

        std::cout << "Method: "
                  << transaction.getTransactionMethod() << std::endl;
    }

    std::cout << "Total Paid: " << getTotalPaid() << std::endl;

    std::cout << "Remaining Amount: "
              << getRemainingAmount() << std::endl;

    std::cout << "Current Status: "
              << getStatus() << std::endl;
}
