
#pragma once

#include <string>
#include <vector>

#include "PaymentTransaction.h"

class RentRecord {

private:

    int tenantId;

    std::string startDate;
    std::string endDate;
    std::string dueDate;

    double totalRent;

    std::vector<PaymentTransaction> transactions;

    std::string status;

public:

    RentRecord(
        int tid,
        std::string sd,
        std::string ed,
        std::string dd,
        double tr,
        std::string st = "Pending"
    );

    int getTenantId() const;

    std::string getStartDate() const;
    std::string getEndDate() const;
    std::string getDueDate() const;

    double getTotalRent() const;
    std::string getStatus() const;

    // Returns true if payment is accepted
    bool addPayment(const PaymentTransaction& payment);

    double getTotalPaid() const;
    double getRemainingAmount() const;

    void updateStatus();

    void displayPaymentHistory() const;
};
