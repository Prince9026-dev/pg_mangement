#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <map>
#include <limits>

using namespace std;

// ================= TENANT CLASS =================

class Tenant
{
    static int nextId;

    int tenant_id;
    string phone;
    string name;
    int roomNo;

public:
    Tenant(string pN, string s, int rn)
        : tenant_id(nextId++), phone(pN), name(s), roomNo(rn) {}

    int gettenant_id() const
    {
        return tenant_id;
    }

    string getphone() const
    {
        return phone;
    }

    string getname() const
    {
        return name;
    }

    int getRoomNo() const
    {
        return roomNo;
    }

    void updatePhoneN(string newNumber)
    {
        phone = newNumber;
    }

    int updateRoomN(int rn)
    {
        return roomNo = rn;
    }
};

int Tenant::nextId = 1001;

// ================= ROOM CLASS =================

class Room
{
    int roomNo;
    string roomType;
    double monthlyRent;
    int capacity;
    int occupiedBed;

public:
    Room(int rn, string rt, double mr, int c)
        : roomNo(rn), roomType(rt),
          monthlyRent(mr), capacity(c), occupiedBed(0) {}

    int getRoomNo() const
    {
        return roomNo;
    }

    string getRoomType() const
    {
        return roomType;
    }

    double getMonthlyRent() const
    {
        return monthlyRent;
    }

    int getCapacity() const
    {
        return capacity;
    }

    int getOccupiedBed() const
    {
        return occupiedBed;
    }

    int getAvailablebed() const
    {
        return capacity - occupiedBed;
    }


    bool addTenant()
    {
        if (occupiedBed >= capacity)
        {
            return false;
        }

        occupiedBed++;
        return true;
    }

    bool removeTenant()
    {
        if (occupiedBed <= 0)
        {
            return false;
        }

        occupiedBed--;
        return true;
    }
};

// -------payment structure--------
class PaymentTransaction{
    static int nextTransactionId;

    int transactionId;
    double transactionAmount;
    string date;
    string transactionMethod;
public:
    PaymentTransaction(int tA, string dT, string tM) {
        transactionId = ++nextTransactionId;
        transactionAmount = tA;
        date = dT;
        transactionMethod = tM;
    }

    int getTransactionId() const { return transactionId;}
    double  getTransactionAmount() const {return transactionAmount;}
    string getDate() const {return date;}
    string getTransactionMethod() const{ return transactionMethod;}
    
};

int PaymentTransaction :: nextTransactionId = 0;


class RentRecord{
    int tenantId;
    string startDate;
    string endDate;
    string dueDate;
    double totalRent;
    vector<PaymentTransaction> transactions;
    string status;
public:
    RentRecord(int tid, string sd, string ed, string dd, double tr, string st="pending"){
        tenantId = tid;
        startDate = sd;
        endDate = ed;
        dueDate = dd;
        totalRent = tr;
        status = st;
        
    }
    int getTenantId() const{return tenantId;}
    string getStartDate() const {return startDate;}
    string getEndDate() const {return endDate;}
    string getDueDate() const {return dueDate;}
    double getTotalRent() const {return totalRent;}
    string getStatus() const{return status;}

    void addPayment(PaymentTransaction payment) {
        transactions.push_back(payment);
    }

    double getTotalPaid() const {
        double totalAmount = 0;

        for (const auto& transaction : transactions) {
            totalAmount += transaction.getTransactionAmount();
        }

        return totalAmount;
    }   

    double getRemainingAmount(){
        double totalTransaction = getTotalPaid();
        double remainingAmount = getTotalRent() - totalTransaction;
        return remainingAmount;
    }

    void updateStatus() {
        if (getRemainingAmount() <= 0) {
            status = "Paid";
        }
        else if (getTotalPaid() > 0) {
            status = "Partial";
        }
        else {
            status = "Pending";
        }
    }
    void displayPaymentHistory() const {
        // Display all transactions
        cout << "PAYMENT HISTORY" << endl;
        for (const auto& transaction : transactions) {
            cout<<"Transaction ID: "<<transaction.getTransactionId()<<endl;
            cout<<"Amount: "<<transaction.getTransactionAmount()<<endl;
            cout<<"Date: "<<transaction.getDate()<<endl;
            cout<<"Method"<<transaction.getTransactionMethod()<<endl;
        }
    }
};
// ================= PG MANAGEMENT CLASS =================

class PgManage
{
    unordered_map<int, Tenant> tenants;
    unordered_map<int, Room> rooms;

public:
    // Add room
    void addRoom(int rn, string rt, double mr, int c)
    {

        if (c <= 0 || mr < 0)
        {
            cout << "Invalid room details.\n";
            return;
        }

        auto result = rooms.emplace(rn, Room(rn, rt, mr, c));

        if (result.second)
        {
            cout << "Room " << rn << " added successfully.\n";
        }
        else
        {
            cout << "Room number already exists.\n";
        }
    }
    // Display available rooms
    void displayAvailableRooms() const
    {

        bool found = false;

        for (const auto &pair : rooms)
        {

            if (pair.second.getAvailablebed() > 0)
            {

                found = true;

                cout << "\nRoom Number: " << pair.first;

                cout << "\nRoom Type: "
                     << pair.second.getRoomType();

                cout << "\nMonthly Rent: "
                     << pair.second.getMonthlyRent();

                cout << "\nCapacity: "
                     << pair.second.getCapacity();

                cout << "\nOccupied Beds: "
                     << pair.second.getOccupiedBed();

                cout << "\nAvailable Beds: "
                     << pair.second.getAvailablebed();

                cout << "\n----------------------\n";
            }
        }

        if (!found)
        {
            cout << "\nNo rooms available currently.\n";
        }
    }

    // Register tenant and assign room
    void addTenant(string n, string p, int roomNo)
    {

        // Step 1: Find selected room
        auto it = rooms.find(roomNo);

        // Step 2: Check whether room exists
        if (it == rooms.end())
        {
            cout << "\nRoom does not exist.\n";
            return;
        }

        // Step 3: Check room availability
        if (!it->second.addTenant())
        {
            cout << "\nRoom is full. Cannot assign tenant.\n";
            return;
        }

        // Step 4: Create Tenant object
        Tenant t(p, n, roomNo);

        // Step 5: Get generated tenant ID
        int id = t.gettenant_id();

        // Step 6: Store Tenant object in map
        tenants.emplace(id, t);

        // Step 7: Display confirmation
        cout << "\nTenant registered successfully!\n";

        cout << "Tenant ID: " << id << endl;
        cout << "Tenant Name: " << t.getname() << endl;
        cout << "Phone: " << t.getphone() << endl;
        cout << "Assigned Room: " << t.getRoomNo() << endl;

        cout << "\nRemaining beds in room: "
             << it->second.getAvailablebed() << endl;
    }

    // Display all tenants
    void displayTenants() const
    {

        if (tenants.empty())
        {
            cout << "\nNo tenants registered.\n";
            return;
        }

        for (const auto &pair : tenants)
        {

            const Tenant &t = pair.second;

            cout << "\nTenant ID: " << pair.first;
            cout << "\nName: " << t.getname();
            cout << "\nPhone: " << t.getphone();
            cout << "\nRoom Number: " << t.getRoomNo();

            cout << "\n----------------------\n";
        }
    }

    void checkoutTenant(int tenantId)
    {
        auto id = tenants.find(tenantId); // id is an iterator pointing to the map entry.
        // 1. Find tenant using tenantId
        if (id != tenants.end())
        {
            cout << "tenant find " << tenantId << endl;
            int roomNO = id->second.getRoomNo();
            cout << "room no is:- " << roomNO;

            auto roomid = rooms.find(roomNO);
            cout << "room :- " << roomid->first << endl;

            if (roomid != rooms.end())
            {
                cout << "room exist! " << endl;
                if (roomid->second.removeTenant())
                {
                    // Occupancy successfully decreased
                    cout << "Tenant remove successfully" << endl;
                    tenants.erase(id);
                }
                else
                {
                    cout << "Tenant could not remove" << endl;
                }
            }
            else
            {
                cout << "Room does not exist! " << endl;
            }
        }
        else
        {
            cout << "Tenant not find";
        }
    }

    void updateTenantRoom(int tenantId, int roomn)
    {
        // 1. Find tenant
        auto id = tenants.find(tenantId);
        if (id != tenants.end())
        {
            cout << "found" << endl;
            int oldRoomNo = id->second.getRoomNo();
            auto newRoomN = rooms.find(roomn);
            
            if (newRoomN == rooms.end())
            {
                cout << "Room does not exist!" << endl;
            }
            else if (oldRoomNo == roomn)
            {
                cout << "You are already inside this room!" << endl;
            }
            else if (newRoomN->second.getAvailablebed() <= 0)
            {
                cout << "Room is full!" << endl;
            }
            else
            {
                cout << "Room is available!" << endl;
                auto rmn = rooms.find(oldRoomNo);
                rmn->second.removeTenant();
                newRoomN->second.addTenant();
                id->second.updateRoomN(roomn);
            }
        }
    }

    void searchTenant(int tenantId)
    {
        auto id = tenants.find(tenantId);
        if (id != tenants.end())
        {
            cout << "Tenant found :- " << endl;
            cout << "TENANT ID :- " << tenantId << endl;
            cout << "TENANT NAME IS :- " << id->second.getname() << endl;
            cout << "TENANT PHONE NUMBER :- " << id->second.getphone() << endl;
            cout << "TENANT ROOM NUMBER :- " << id->second.getRoomNo() << endl;

            int c;
            do
            {
                cout << "1. for Update Phone Number :- " << endl;
                cout << "2. for Update Room Number :- " << endl;
                cout << "0. for exit" << endl;
                cout << "what do you want to update? ";
                cin >> c;

                switch (c){
                    case 1:{
                        string phone;
                        cout << "enter New Phone No. :- " << endl;
                        cin >> phone;
                        id->second.updatePhoneN(phone);
                        break;
                    }
                    case 2:{
                        int roomn;
                        cout << "Enter your new room no. :- " << endl;
                        cin >> roomn;
                        updateTenantRoom(tenantId, roomn);
                        break;
                    }
                }

            } while (c != 0);
        }
        else
        {
            cout << "TENANT Not Found!" << endl;
        }
    }
};



// ================= MAIN FUNCTION =================

int main()
{

    PgManage pg;

    // Owner adds rooms
    pg.addRoom(101, "double", 4000, 2);
    pg.addRoom(102, "single", 7000, 1);
    pg.addRoom(103, "triple", 3500, 3);

    cout << "\n===== PG MANAGEMENT SYSTEM =====\n";

    string name;
    string phone;
    int roomNo;
    int choice;

    PaymentTransaction p(2000, "01/12/2026", "cash");
    p.getDate();
    p.getTransactionAmount();
    p.getTransactionId();
    p.getTransactionMethod();
    PaymentTransaction p1(2000, "2026-11-20", "Cash");
    PaymentTransaction p2(3000, "2026-11-21", "UPI");
    PaymentTransaction p3(1500, "2026-11-22", "Bank Transfer");
    cout << "Transaction ID: " << p1.getTransactionId() << endl;
    cout << "Amount: " << p1.getTransactionAmount() << endl;
    cout << "Date: " << p1.getDate() << endl;
    cout << "Method: " << p1.getTransactionMethod() << endl;
    // Collect tenant details
    // do
    // {
    //     cout << "\n1. Yes";
    //     cout << "\n2. No";
    //     cout << "\nDo you want to continue? ";
    //     cin >> choice;

    //     switch (choice)
    //     {
    //     case 1:
    //     {
    //         int c;

    //         cout << "\n1. Add Tenant";
    //         cout << "\n2. Remove Tenant";
    //         cout<<"\n3. update tenant info";
    //         cout<<"\n 0. for exit";
    //         cout << "\nEnter your choice: ";
    //         cin >> c;

    //         switch (c)
    //         {
    //             case 0 : break;

    //         case 1:
    //             cin.ignore(numeric_limits<streamsize>::max(), '\n');

    //             cout << "Enter your name: ";
    //             getline(cin, name);

    //             cout << "Enter your phone number: ";
    //             getline(cin, phone);

    //             pg.displayAvailableRooms();

    //             cout << "Enter room number: ";
    //             cin >> roomNo;

    //             pg.addTenant(name, phone, roomNo);
    //             pg.displayTenants();
    //             break;

    //         case 2:
    //         {
    //             int tenantId;
    //             cout << "Enter tenant ID: ";
    //             cin >> tenantId;

    //             pg.checkoutTenant(tenantId);
    //             pg.displayTenants();
    //             break;
    //         }

    //         case 3:{
    //             int id;
    //             cout<<"Enter tenant id :- ";
    //             cin>>id;
    //             pg.searchTenant(id);
    //         }
    //         default:
    //             cout << "Invalid choice!" << endl;
    //         }
    //         break;
    //     }

    //     case 2:
    //         cout << "Exiting program." << endl;
    //         break;

    //     default:
    //         cout << "Invalid choice!" << endl;
    //     }

    // } while (choice != 2);
    return 0;
}
