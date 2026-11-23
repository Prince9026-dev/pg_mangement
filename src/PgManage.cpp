
#include "PgManage.h"
#include <iostream>

void PgManage::addRoom(
    int rn,
    std::string rt,
    double mr,
    int c
) {
    if (c <= 0 || mr < 0) {
        std::cout << "Invalid room details.\n";
        return;
    }

    auto result = rooms.emplace(rn, Room(rn, rt, mr, c));

    if (result.second) {
        std::cout << "Room " << rn << " added successfully.\n";
    }
    else {
        std::cout << "Room number already exists.\n";
    }
}

void PgManage::displayAvailableRooms() const {
    bool found = false;

    for (const auto& pair : rooms) {
        const Room& room = pair.second;

        if (room.getAvailablebed() > 0) {
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

    if (!found) {
        std::cout << "\nNo rooms available currently.\n";
    }
}

void PgManage::addTenant(
    std::string name,
    std::string phone,
    int roomNo
) {
    auto roomIt = rooms.find(roomNo);

    if (roomIt == rooms.end()) {
        std::cout << "\nRoom does not exist.\n";
        return;
    }

    if (!roomIt->second.addTenant()) {
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

void PgManage::displayTenants() const {
    if (tenants.empty()) {
        std::cout << "\nNo tenants registered.\n";
        return;
    }

    for (const auto& pair : tenants) {
        const Tenant& tenant = pair.second;

        std::cout << "\nTenant ID: " << pair.first;
        std::cout << "\nName: " << tenant.getname();
        std::cout << "\nPhone: " << tenant.getphone();
        std::cout << "\nRoom Number: " << tenant.getRoomNo();

        std::cout << "\n----------------------\n";
    }
}

void PgManage::checkoutTenant(int tenantId) {
    auto tenantIt = tenants.find(tenantId);

    if (tenantIt == tenants.end()) {
        std::cout << "Tenant not found.\n";
        return;
    }

    int roomNo = tenantIt->second.getRoomNo();

    auto roomIt = rooms.find(roomNo);

    if (roomIt == rooms.end()) {
        std::cout << "Room does not exist!\n";
        return;
    }

    if (roomIt->second.removeTenant()) {
        tenants.erase(tenantIt);

        std::cout << "Tenant removed successfully.\n";
    }
    else {
        std::cout << "Tenant could not be removed.\n";
    }
}

void PgManage::updateTenantRoom(
    int tenantId,
    int roomNo
) {
    auto tenantIt = tenants.find(tenantId);

    if (tenantIt == tenants.end()) {
        std::cout << "Tenant not found!\n";
        return;
    }

    int oldRoomNo = tenantIt->second.getRoomNo();

    auto newRoomIt = rooms.find(roomNo);

    if (newRoomIt == rooms.end()) {
        std::cout << "Room does not exist!\n";
    }
    else if (oldRoomNo == roomNo) {
        std::cout << "You are already inside this room!\n";
    }
    else if (newRoomIt->second.getAvailablebed() <= 0) {
        std::cout << "Room is full!\n";
    }
    else {
        auto oldRoomIt = rooms.find(oldRoomNo);

        if (oldRoomIt == rooms.end()) {
            std::cout << "Current room does not exist!\n";
            return;
        }

        if (newRoomIt->second.addTenant()) {
            oldRoomIt->second.removeTenant();

            tenantIt->second.updateRoomN(roomNo);

            std::cout << "Tenant room updated successfully!\n";
        }
    }
}

void PgManage::searchTenant(int tenantId) {
    auto tenantIt = tenants.find(tenantId);

    if (tenantIt == tenants.end()) {
        std::cout << "TENANT Not Found!\n";
        return;
    }

    std::cout << "Tenant found:\n";

    std::cout << "TENANT ID: "
              << tenantId << std::endl;

    std::cout << "TENANT NAME: "
              << tenantIt->second.getname() << std::endl;

    std::cout << "TENANT PHONE NUMBER: "
              << tenantIt->second.getphone() << std::endl;

    std::cout << "TENANT ROOM NUMBER: "
              << tenantIt->second.getRoomNo() << std::endl;

    int choice;

    do {
        std::cout << "\n1. Update Phone Number\n";
        std::cout << "2. Update Room Number\n";
        std::cout << "0. Exit\n";

        std::cout << "What do you want to update? ";
        std::cin >> choice;

        switch (choice) {

            case 1: {
                std::string phone;

                std::cout << "Enter new phone number: ";
                std::cin >> phone;

                tenantIt->second.updatePhoneN(phone);

                std::cout << "Phone updated successfully.\n";
                break;
            }

            case 2: {
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
