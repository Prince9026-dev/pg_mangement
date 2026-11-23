#include "tenants.h"

int Tenant::nextId = 1001;

Tenant::Tenant(string pN, string s, int rn)
    : tenant_id(nextId++),
      phone(pN),
      name(s),
      roomNo(rn) {}

int Tenant::gettenant_id() const {
    return tenant_id;
}

string Tenant::getphone() const {
    return phone;
}

string Tenant::getname() const {
    return name;
}

int Tenant::getRoomNo() const {
    return roomNo;
}

void Tenant::updatePhoneN(string newNumber) {
    phone = newNumber;
}

int Tenant::updateRoomN(int rn) {
    return roomNo = rn;
}
