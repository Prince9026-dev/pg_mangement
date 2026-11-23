
#pragma once

#include <string>
using namespace std;

class Tenant {
private:
    static int nextId;

    int tenant_id;
    string phone;
    string name;
    int roomNo;

public:
    Tenant(string pN, string s, int rn);

    int gettenant_id() const;
    string getphone() const;
    string getname() const;
    int getRoomNo() const;

    void updatePhoneN(string newNumber);
    int updateRoomN(int rn);
};
