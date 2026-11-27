
#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "tenants.h"
#include "Room.h"
#include "RentRecord.h"

class PgManage {

private:

    // Active tenants
    std::unordered_map<int, Tenant> tenants;

    // Room records
    std::unordered_map<int, Room> rooms;

    // Checked-out tenants (preserve their details)
    std::unordered_map<int, Tenant> checkedOutTenants;

    // Multiple rent records for each tenant
    std::unordered_map<int, std::vector<RentRecord>> rentRecords;


public:

    // ==============================
    // ROOM MANAGEMENT
    // ==============================

    void addRoom(int rn, std::string rt, double mr, int c);

    void displayAvailableRooms() const;


    // ==============================
    // TENANT MANAGEMENT
    // ==============================

    void addTenant(std::string name, std::string phone, int roomNo);

    void displayTenants() const;

    void checkoutTenant(int tenantId);

    void updateTenantRoom(int tenantId, int roomNo);

    void searchTenant(int tenantId);


    // ==============================
    // RENT MANAGEMENT
    // ==============================

    void createRentRecord(
        int tenantId,
        std::string startDate,
        std::string endDate,
        std::string dueDate,
        double totalRent
    );


    // ==============================
    // PAYMENT MANAGEMENT
    // ==============================

    void addRentPayment(
        int tenantId,
        double amount,
        std::string date,
        std::string method
    );


    // ==============================
    // REPORTS AND HISTORY
    // ==============================

    void displayRentHistory(int tenantId) const;

    void displayPendingRent() const;

};
