#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


class Info{
    static vector<int> personIdss;
    static vector<int> roomNos;
    static vector<int> phoneNos;
    static vector<string> personNames;
    static int count;
protected:
    int personId;
    int roomNo;
    int phoneNo;
    string personName;

public:
    Info(){
        cout<<"enter personId:- ";
        cin>>personId;
        cout<<"enter roomNo :-";
        cin>>roomNo;
        cout<<"enter phoneNo:-";
        cin>>phoneNo;
        cout<<"enter name:- ";
        cin>>personName;
    }

    void store(){
        int c = 0;
        for(int i=0; i<roomNos.size(); i++){
            if(roomNo == roomNos[i]) c++;
        }

        if(c >= 3){
            cout<<"THIS ROOMS ARE FIELD ENTER ANOTHER ROOM NO:"<<endl;
        }else{
            roomNos.push_back(roomNo);
            personIdss.push_back(personId);
            personNames.push_back(personName);
            phoneNos.push_back(phoneNo);
            count++;
        }
    }
    static void prinf() {
        cout << "\n--- All Records ---" << endl;
        for (size_t i = 0; i < roomNos.size(); i++) {
            cout << personIdss[i] << " | " << personNames[i] << " | " << phoneNos[i] << " | Room: " << roomNos[i] << endl;
        }
    }
    int getPersonId() const { return personId; }
    int getRoomNo() const { return roomNo; }
};
vector<int>Info::personIdss;
vector<int>Info::roomNos;
vector<int>Info::phoneNos;
vector<string>Info::personNames;
int Info::count = 0;

class StayDetails : public Info{
protected:
    // static vector<int>monthStayed;
    int monthlyRent = 5000;
    int monthsInput = 0;

public:
    void monthStay(){
        cout<<"ENTER NO. OF MONTH TO STAY HERE:- ";
        cin>>monthsInput;
        monthlyRent *= monthsInput;
    }
};

// vector<int>StayDetails::monthStayed;

class RentDetails : public StayDetails{
    vector<bool> monthsPayed; // Individual tracking per tenant

public:
    void initializeRent() {
        monthStay();
        // Initially, all months are unpaid (false)
        monthsPayed.resize(monthsInput, false);
    }

    // Update rent for the next pending month without touching personal details!
    bool payNextMonth() {
        for (size_t i = 0; i < monthsPayed.size(); i++) {
            if (!monthsPayed[i]) {
                monthsPayed[i] = true;
                cout << "[✓] Rent successfully paid for Month " << (i + 1) << " for " << personName << " (ID: " << personId << ")\n";
                return true;
            }
        }
        cout << "[!] All months are already fully paid for this tenant!\n";
        return false;
    }

    void displayRecord() const {
        cout << "\n--------------------------------------------------" << endl;
        cout << "Tenant ID: " << personId << " | Name: " << personName << endl;
        cout << "Phone: " << phoneNo << " | Room No: " << roomNo << endl;
        cout << "Total Stay: " << monthsInput << " months | Monthly Rent: " << monthlyRent << endl;
        
        cout << "Payment Sequence: [ ";
        int unpaidCount = 0;
        for (size_t i = 0; i < monthsPayed.size(); i++) {
            if (monthsPayed[i]) {
                cout << "M" << (i + 1) << ":PAID ";
            } else {
                cout << "M" << (i + 1) << ":PENDING ";
                unpaidCount++;
            }
        }
        cout << "]" << endl;
        cout << "Remaining Dues: Rs. " << (unpaidCount * monthlyRent) << " (" << unpaidCount << " months pending)" << endl;
        cout << "--------------------------------------------------" << endl;
    }
};

int main(){
    vector<RentDetails> tenants;
    int choice;

    do {
        cout << "\n===== PG MANAGEMENT SYSTEM =====" << endl;
        cout << "1. Add New Tenant" << endl;
        cout << "2. Pay Rent (Verify by Person ID & Room No)" << endl;
        cout << "3. Tenant Checkout (Person Leaves)" << endl;
        cout << "4. Display All Tenant Records" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                RentDetails newTenant;
                newTenant.initializeRent();

                // Check room capacity (max 3 people per room)
                int currentRoom = newTenant.getRoomNo();
                int roomCount = 0;
                for (const auto& t : tenants) {
                    if (t.getRoomNo() == currentRoom) roomCount++;
                }

                if (roomCount >= 3) {
                    cout << "\n[!] Room " << currentRoom << " is FULL! Max capacity is 3.\n";
                } else {
                    tenants.push_back(newTenant);
                    cout << "\n[✓] Tenant added successfully!\n";
                }
                break;
            }
            case 2: {
                int searchId, searchRoom;
                cout << "\n--- Rent Payment Verification ---" << endl;
                cout << "Enter Tenant Person ID: ";
                cin >> searchId;
                cout << "Enter Room No: ";
                cin >> searchRoom;

                bool found = false;
                for (auto& t : tenants) {
                    // Verifies both ID and Room match simultaneously
                    if (t.getPersonId() == searchId && t.getRoomNo() == searchRoom) {
                        t.payNextMonth();
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "\n[!] Verification Failed: No active tenant with ID " << searchId 
                         << " found in Room " << searchRoom << ".\n";
                }
                break;
            }
            case 3: {
                int searchId, searchRoom;
                cout << "\n--- Tenant Checkout ---" << endl;
                cout << "Enter Tenant Person ID: ";
                cin >> searchId;
                cout << "Enter Room No: ";
                cin >> searchRoom;

                auto it = remove_if(tenants.begin(), tenants.end(), [searchId, searchRoom](const RentDetails& t) {
                    return (t.getPersonId() == searchId && t.getRoomNo() == searchRoom);
                });

                if (it != tenants.end()) {
                    tenants.erase(it, tenants.end());
                    cout << "\n[✓] Tenant checked out successfully! Room vacancy updated.\n";
                } else {
                    cout << "\n[!] Tenant not found with ID " << searchId << " in Room " << searchRoom << ".\n";
                }
                break;
            }
            case 4:
                if (tenants.empty()) {
                    cout << "\n[!] No active tenants in the PG.\n";
                } else {
                    cout << "\n========== ACTIVE PG TENANTS ==========";
                    for (const auto& t : tenants) {
                        t.displayRecord();
                    }
                }
                break;
            case 5:
                cout << "Exiting system. Goodbye!\n";
                break;
            default:
                cout << "[!] Invalid choice. Try again.\n";
        }
    } while (choice != 5);
    return 0;
}
