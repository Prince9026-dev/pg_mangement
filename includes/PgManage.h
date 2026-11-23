
#pragma once

#include <string>
#include <unordered_map>

#include "tenants.h"
#include "Room.h"

class PgManage {
private:
    std::unordered_map<int, Tenant> tenants;
    std::unordered_map<int, Room> rooms;

public:
    void addRoom(int rn, std::string rt, double mr, int c);

    void displayAvailableRooms() const;

    void addTenant(
        std::string name,
        std::string phone,
        int roomNo
    );

    void displayTenants() const;

    void checkoutTenant(int tenantId);

    void updateTenantRoom(int tenantId, int roomNo);

    void searchTenant(int tenantId);
};
