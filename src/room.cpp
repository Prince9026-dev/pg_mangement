
#include "Room.h"

Room::Room(int rn, std::string rt, double mr, int c)
    : roomNo(rn),
      roomType(rt),
      monthlyRent(mr),
      capacity(c),
      occupiedBed(0) {}

int Room::getRoomNo() const {
    return roomNo;
}

std::string Room::getRoomType() const {
    return roomType;
}

double Room::getMonthlyRent() const {
    return monthlyRent;
}

int Room::getCapacity() const {
    return capacity;
}

int Room::getOccupiedBed() const {
    return occupiedBed;
}

int Room::getAvailablebed() const {
    return capacity - occupiedBed;
}

bool Room::addTenant() {
    if (occupiedBed >= capacity) {
        return false;
    }

    occupiedBed++;
    return true;
}

bool Room::removeTenant() {
    if (occupiedBed <= 0) {
        return false;
    }

    occupiedBed--;
    return true;
}
