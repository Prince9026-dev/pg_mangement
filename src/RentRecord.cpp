
#include "RentRecord.h"

#include <iostream>

// ==========================================
// CONSTRUCTOR
// ==========================================

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
      status(st)
{
    updateStatus();
}


// ==========================================
// GETTERS
// ==========================================

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


// ==========================================
// PAYMENT MANAGEMENT
// ==========================================

bool RentRecord::addPayment(
    const PaymentTransaction& payment
) {

    double amount = payment.getTransactionAmount();

    // Validate payment
    if (amount <= 0) {
        std::cout << "Invalid payment amount!\n";
        return false;
    }

    // Check outstanding balance
    if (amount > getRemainingAmount()) {
        std::cout << "Payment exceeds remaining rent!\n";
        return false;
    }

    transactions.push_back(payment);

    updateStatus();

    return true;
}


// ==========================================
// PAYMENT CALCULATIONS
// ==========================================

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


// ==========================================
// UPDATE RENT STATUS
// ==========================================

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


// ==========================================
// DISPLAY PAYMENT HISTORY
// ==========================================

void RentRecord::displayPaymentHistory() const {

    std::cout << "\n========== PAYMENT HISTORY ==========\n";

    if (transactions.empty()) {

        std::cout << "No payments recorded yet.\n";
    }

    for (const auto& transaction : transactions) {

        std::cout << "\nTransaction ID: "
                  << transaction.getTransactionId() << std::endl;

        std::cout << "Amount: Rs. "
                  << transaction.getTransactionAmount() << std::endl;

        std::cout << "Date: "
                  << transaction.getDate() << std::endl;

        std::cout << "Method: "
                  << transaction.getTransactionMethod() << std::endl;
    }

    std::cout << "\nTotal Paid: Rs. "
              << getTotalPaid() << std::endl;

    std::cout << "Remaining Amount: Rs. "
              << getRemainingAmount() << std::endl;

    std::cout << "Current Status: "
              << getStatus() << std::endl;

    std::cout << "=====================================\n";
}
