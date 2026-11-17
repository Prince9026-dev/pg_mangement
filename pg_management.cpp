#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

class Tenant{
    static int nextId;
    int tenant_id;
    string phone;
    string name;

public:
    // Constructor with parameter and initializing member function using setter func
    Tenant(string pN, string s):tenant_id(nextId++), phone(pN), name(s){}

    // getter functions
    int gettenant_id() const{  return tenant_id; }
    string getphone() const{ return phone; }
    string getname() const{ return name; }

    // update Phone no using setter function
    void updatePhoneN(string newNumber){
        phone = newNumber;
    }
};

int Tenant :: nextId = 1001;

class Room{
    int roomNo;
    string roomType;
    double monthlyRent;
    int capacity;
    int occupiedBed;

public:
    Room(int rn, string rt, double mr, int c, int ob) 
    : roomNo(rn), roomType(rt),monthlyRent(mr), capacity(c), occupiedBed(ob){  }

    int getRoomNo() const { return roomNo; }
    string getRoomType() const { return roomType; }
    double getMonthlyRent() const { return monthlyRent; }
    int getCapacity() const { return capacity; }
    int getOccupiedBed() const { return occupiedBed; }

    int getAvailablebed() const {
        return capacity-occupiedBed;
    }

    bool addTenant(){
        if(roomType == "single" && occupiedBed == capacity
            || roomType == "double" && occupiedBed == capacity  
            || roomType == "triple" && occupiedBed == capacity)
        { 
                return false; 
        }
        else{
            occupiedBed++; 
            return true;
        }
    }

    bool removeTenant(){
        if(occupiedBed <= 0){
            return false;
        }
        else{
            occupiedBed--;
            return true;
        }
    }

};

class PgManage{
    unordered_map<int, Tenant> tenants;
    unordered_map<int, Room> rooms;
public:
    void displayAvailableRooms() const {

        for (const auto& pair : rooms) {

            // Check whether any bed is available
            if (pair.second.getAvailablebed() > 0) {

                cout << "\nRoom Number: "
                    << pair.first << endl;

                cout << "Room Type: "
                    << pair.second.getRoomType() << endl;

                cout << "Monthly Rent: "
                    << pair.second.getMonthlyRent() << endl;

                cout << "Available Beds: "
                    << pair.second.getOccupiedBed() << endl;

                cout << "----------------------\n";
            }
        }
    }
    void addRoom(int rn, string rt, double mr, int c) {
        rooms.emplace(rn, Room(rn, rt, mr, c, 0));
    }
    void addTenant(string n, string p){
        
    }
};

int main() {
    PgManage pg;

    // Add rooms to PG
    pg.addRoom(101, "double", 4000, 2);
    pg.addRoom(102, "single", 7000, 1);
    pg.addRoom(103, "triple", 3500, 3);

    cout << "\n===== PG MANAGEMENT SYSTEM =====\n";

    cout << "\nAvailable Rooms:\n";

    pg.displayAvailableRooms();

    return 0;
    
}