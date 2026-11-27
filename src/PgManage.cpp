
#include "PgManage.h"
#include "PaymentTransaction.h"

#include <iostream>
#include <string>

// ==========================================
// ROOM MANAGEMENT
// ==========================================

void PgManage::addRoom(
    int rn,
    std::string rt,
    double mr,
    int c)
{
    if (rn <= 0 || c <= 0 || mr <= 0)
    {
        std::cout << "Invalid room details.\n";
        return;
    }

    auto result = rooms.emplace(rn, Room(rn, rt, mr, c));

    if (result.second)
    {
        std::cout << "Room " << rn << " added successfully.\n";
    }
    else
    {
        std::cout << "Room number already exists.\n";
    }
}

void PgManage::displayAvailableRooms() const
{

    bool found = false;

    for (const auto &pair : rooms)
    {

        const Room &room = pair.second;

        if (room.getAvailablebed() > 0)
        {

            found = true;

            std::cout << "\nRoom Number: " << pair.first;
            std::cout << "\nRoom Type: " << room.getRoomType();
            std::cout << "\nMonthly Rent: " << room.getMonthlyRent();
            std::cout << "\nCapacity: " << room.getCapacity();
            std::cout << "\nOccupied Beds: " << room.getOccupiedBed();
            std::cout << "\nAvailable Beds: " << room.getAvailablebed();

            std::cout << "\n----------------------\n";
        }
    }

    if (!found)
    {
        std::cout << "\nNo rooms available currently.\n";
    }
}

// ==========================================
// TENANT MANAGEMENT
// ==========================================

void PgManage::addTenant(
    std::string name,
    std::string phone,
    int roomNo)
{

    auto roomIt = rooms.find(roomNo);

    if (roomIt == rooms.end())
    {
        std::cout << "\nRoom does not exist.\n";
        return;
    }

    if (!roomIt->second.addTenant())
    {
        std::cout << "\nRoom is full. Cannot assign tenant.\n";
        return;
    }

    Tenant tenant(phone, name, roomNo);

    int id = tenant.gettenant_id();

    tenants.emplace(id, tenant);

    std::cout << "\nTenant registered successfully!\n";

    std::cout << "Tenant ID: " << id << std::endl;
    std::cout << "Tenant Name: " << tenant.getname() << std::endl;
    std::cout << "Phone: " << tenant.getphone() << std::endl;
    std::cout << "Assigned Room: " << tenant.getRoomNo() << std::endl;

    std::cout << "\nRemaining beds in room: "
              << roomIt->second.getAvailablebed() << std::endl;
}

void PgManage::displayTenants() const
{

    if (tenants.empty())
    {
        std::cout << "\nNo active tenants registered.\n";
        return;
    }

    std::cout << "\n========== ACTIVE TENANTS ==========\n";

    for (const auto &pair : tenants)
    {

        const Tenant &tenant = pair.second;

        std::cout << "\nTenant ID: " << pair.first;
        std::cout << "\nName: " << tenant.getname();
        std::cout << "\nPhone: " << tenant.getphone();
        std::cout << "\nRoom Number: " << tenant.getRoomNo();

        std::cout << "\n----------------------\n";
    }
}

void PgManage::checkoutTenant(int tenantId)
{

    auto tenantIt = tenants.find(tenantId);

    if (tenantIt == tenants.end())
    {
        std::cout << "Tenant not found in active records.\n";
        return;
    }

    if (checkedOutTenants.find(tenantId) != checkedOutTenants.end())
    {
        std::cout << "Tenant is already checked out.\n";
        return;
    }

    int roomNo = tenantIt->second.getRoomNo();

    auto roomIt = rooms.find(roomNo);

    if (roomIt == rooms.end())
    {
        std::cout << "Room does not exist!\n";
        return;
    }

    // Free the occupied bed
    if (roomIt->second.removeTenant())
    {

        // Preserve tenant details
        checkedOutTenants.emplace(tenantId, tenantIt->second);

        // Remove tenant from active records
        tenants.erase(tenantIt);

        std::cout << "Tenant checked out successfully.\n";
        std::cout << "Tenant details and rent history preserved.\n";
    }
    else
    {
        std::cout << "Tenant could not be removed.\n";
    }
}

void PgManage::updateTenantRoom(
    int tenantId,
    int roomNo)
{

    auto tenantIt = tenants.find(tenantId);

    if (tenantIt == tenants.end())
    {
        std::cout << "Tenant not found!\n";
        return;
    }

    int oldRoomNo = tenantIt->second.getRoomNo();

    auto newRoomIt = rooms.find(roomNo);

    if (newRoomIt == rooms.end())
    {
        std::cout << "Room does not exist!\n";
        return;
    }

    if (oldRoomNo == roomNo)
    {
        std::cout << "You are already inside this room!\n";
        return;
    }

    if (newRoomIt->second.getAvailablebed() <= 0)
    {
        std::cout << "Room is full!\n";
        return;
    }

    auto oldRoomIt = rooms.find(oldRoomNo);

    if (oldRoomIt == rooms.end())
    {
        std::cout << "Current room does not exist!\n";
        return;
    }

    // First free the old room
    if (!oldRoomIt->second.removeTenant())
    {
        std::cout << "Could not release the current room bed!\n";
        return;
    }

    // Assign the new room
    if (newRoomIt->second.addTenant())
    {

        tenantIt->second.updateRoomN(roomNo);

        std::cout << "Tenant room updated successfully!\n";
    }
    else
    {

        // Restore old room occupancy if assignment fails
        oldRoomIt->second.addTenant();

        std::cout << "Could not assign new room!\n";
    }
}

void PgManage::searchTenant(int tenantId)
{

    auto tenantIt = tenants.find(tenantId);

    if (tenantIt == tenants.end())
    {
        std::cout << "TENANT Not Found!\n";
        return;
    }

    std::cout << "\nTenant found:\n";

    std::cout << "TENANT ID: "
              << tenantId << std::endl;

    std::cout << "TENANT NAME: "
              << tenantIt->second.getname() << std::endl;

    std::cout << "TENANT PHONE NUMBER: "
              << tenantIt->second.getphone() << std::endl;

    std::cout << "TENANT ROOM NUMBER: "
              << tenantIt->second.getRoomNo() << std::endl;

    int choice;

    do
    {

        std::cout << "\n1. Update Phone Number\n";
        std::cout << "2. Update Room Number\n";
        std::cout << "0. Exit\n";

        std::cout << "What do you want to update? ";

        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input!\n";
            return;
        }

        switch (choice)
        {

        case 1:
        {

            std::string phone;

            std::cout << "Enter new phone number: ";
            std::cin >> phone;

            tenantIt->second.updatePhoneN(phone);

            std::cout << "Phone updated successfully.\n";

            break;
        }

        case 2:
        {

            int newRoomNo;

            std::cout << "Enter new room number: ";
            std::cin >> newRoomNo;

            updateTenantRoom(tenantId, newRoomNo);

            break;
        }

        case 0:
            break;

        default:
            std::cout << "Invalid choice!\n";
        }

    } while (choice != 0);
}

// ==========================================
// RENT MANAGEMENT
// ==========================================

void PgManage::createRentRecord(
    int tenantId,
    std::string startDate,
    std::string endDate,
    std::string dueDate,
    double totalRent)
{

    // Only active tenants can receive new rent records
    auto tenant = tenants.find(tenantId);

    if (tenant == tenants.end())
    {
        std::cout << "Active tenant not found!\n";
        return;
    }

    if (totalRent <= 0)
    {
        std::cout << "Invalid rent amount!\n";
        return;
    }

    if (startDate.empty() || endDate.empty() || dueDate.empty())
    {
        std::cout << "Rent dates cannot be empty!\n";
        return;
    }

    // Check duplicate rent period
    auto &records = rentRecords[tenantId];

    for (const auto &record : records)
    {

        if (record.getStartDate() == startDate &&
            record.getEndDate() == endDate)
        {

            std::cout
                << "Rent record already exists for this period!\n";

            return;
        }
    }

    // Create new rent record
    RentRecord record(
        tenantId,
        startDate,
        endDate,
        dueDate,
        totalRent);

    records.push_back(record);

    std::cout << "Rent record created successfully!\n";
}

// ==========================================
// PAYMENT MANAGEMENT
// ==========================================

void PgManage::addRentPayment(
    int tenantId,
    double amount,
    std::string date,
    std::string method)
{

    // Check active tenant first
    auto activeTenant = tenants.find(tenantId);

    // Also allow checked-out tenants to clear old dues
    auto oldTenant = checkedOutTenants.find(tenantId);

    if (activeTenant == tenants.end() &&
        oldTenant == checkedOutTenants.end())
    {

        std::cout << "Tenant not found!\n";
        return;
    }

    if (amount <= 0)
    {
        std::cout << "Invalid payment amount!\n";
        return;
    }

    if (date.empty() || method.empty())
    {
        std::cout << "Payment date and method are required!\n";
        return;
    }

    auto records = rentRecords.find(tenantId);

    if (records == rentRecords.end() || records->second.empty())
    {
        std::cout << "No rent record found for this tenant!\n";
        return;
    }

    // Find the oldest rent record with an outstanding balance
    RentRecord *pendingRecord = nullptr;

    for (auto &record : records->second)
    {

        if (record.getRemainingAmount() > 0)
        {

            pendingRecord = &record;
            break;
        }
    }

    if (pendingRecord == nullptr)
    {
        std::cout << "All rent records are fully paid!\n";
        return;
    }

    if (amount > pendingRecord->getRemainingAmount())
    {
        std::cout << "Payment exceeds remaining rent!\n";
        std::cout << "Remaining amount: "
                  << pendingRecord->getRemainingAmount() << std::endl;
        return;
    }

    PaymentTransaction payment(amount, date, method);

    if (pendingRecord->addPayment(payment))
    {

        std::cout << "Payment added successfully!\n";

        std::cout << "Remaining rent: "
                  << pendingRecord->getRemainingAmount() << std::endl;

        std::cout << "Rent status: "
                  << pendingRecord->getStatus() << std::endl;
    }

    std::cout << "Remaining rent: "
              << pendingRecord->getRemainingAmount() << std::endl;

    std::cout << "Rent status: "
              << pendingRecord->getStatus() << std::endl;
}

// ==========================================
// TENANT RENT HISTORY
// ==========================================

void PgManage::displayRentHistory(int tenantId) const
{

    std::string tenantName;
    bool tenantFound = false;

    // Search active tenants
    auto activeTenant = tenants.find(tenantId);

    if (activeTenant != tenants.end())
    {

        tenantName = activeTenant->second.getname();
        tenantFound = true;
    }

    // Search checked-out tenants
    if (!tenantFound)
    {

        auto oldTenant = checkedOutTenants.find(tenantId);

        if (oldTenant != checkedOutTenants.end())
        {

            tenantName = oldTenant->second.getname();
            tenantFound = true;
        }
    }

    if (!tenantFound)
    {
        std::cout << "Tenant not found!\n";
        return;
    }

    auto records = rentRecords.find(tenantId);

    if (records == rentRecords.end() || records->second.empty())
    {
        std::cout << "No rent history available!\n";
        return;
    }

    std::cout << "\n====================================\n";
    std::cout << "             RENT HISTORY           \n";
    std::cout << "====================================\n";

    std::cout << "Tenant ID: " << tenantId << std::endl;
    std::cout << "Tenant Name: " << tenantName << std::endl;

    for (const auto &record : records->second)
    {

        std::cout << "\n------------------------\n";

        std::cout << "Rent Period: "
                  << record.getStartDate() << " to "
                  << record.getEndDate() << std::endl;

        std::cout << "Due Date: "
                  << record.getDueDate() << std::endl;

        std::cout << "Total Rent: "
                  << record.getTotalRent() << std::endl;

        record.displayPaymentHistory();
    }
}

// ==========================================
// PENDING RENT REPORT
// ==========================================

void PgManage::displayPendingRent() const
{

    std::cout << "\n========================================\n";
    std::cout << "             PENDING RENT REPORT        \n";
    std::cout << "========================================\n";

    bool found = false;

    // Check all tenants' rent records
    for (const auto &tenantRecords : rentRecords)
    {

        int tenantId = tenantRecords.first;

        std::string tenantName;
        bool tenantExists = false;

        // Search active tenants
        auto activeTenant = tenants.find(tenantId);

        if (activeTenant != tenants.end())
        {

            tenantName = activeTenant->second.getname();
            tenantExists = true;
        }

        // Search checked-out tenants
        if (!tenantExists)
        {

            auto oldTenant = checkedOutTenants.find(tenantId);

            if (oldTenant != checkedOutTenants.end())
            {

                tenantName = oldTenant->second.getname();
                tenantExists = true;
            }
        }

        if (!tenantExists)
        {
            continue;
        }

        // Check every rent record
        for (const auto &record : tenantRecords.second)
        {

            double remaining = record.getRemainingAmount();

            if (remaining > 0)
            {

                found = true;

                std::cout << "\nTenant ID: "
                          << tenantId << std::endl;

                std::cout << "Tenant Name: "
                          << tenantName << std::endl;

                std::cout << "Rent Period: "
                          << record.getStartDate()
                          << " to "
                          << record.getEndDate() << std::endl;

                std::cout << "Due Date: "
                          << record.getDueDate() << std::endl;

                std::cout << "Total Rent: Rs. "
                          << record.getTotalRent() << std::endl;

                std::cout << "Paid Amount: Rs. "
                          << record.getTotalPaid() << std::endl;

                std::cout << "Remaining Amount: Rs. "
                          << remaining << std::endl;

                std::cout << "Rent Status: "
                          << record.getStatus() << std::endl;

                std::cout
                    << "----------------------------------------\n";
            }
        }
    }

    if (!found)
    {
        std::cout << "\nNo pending rent found!\n";
    }

    std::cout << "========================================\n";
}
