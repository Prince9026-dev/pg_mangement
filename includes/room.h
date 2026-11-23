#pragma once
#include <string>

class Room {
private:
    int roomNo;
    std::string roomType;
    double monthlyRent;
    int capacity;
    int occupiedBed;

public:
    Room(int rn, std::string rt, double mr, int c);

    int getRoomNo() const;
    std::string getRoomType() const;
    double getMonthlyRent() const;
    int getCapacity() const;
    int getOccupiedBed() const;
    int getAvailablebed() const;

    bool addTenant();
    bool removeTenant();
};
