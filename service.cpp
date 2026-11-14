#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Info{
    static vector<int> personIdss;
    static vector<int> roomNos;
    static vector<int> phoneNos;
    static vector<string> personNames;
    static int count;

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
};
vector<int>Info::personIdss;
vector<int>Info::roomNos;
vector<int>Info::phoneNos;
vector<string>Info::personNames;
int Info::count = 0;



int main(){
   char choice;
    do {
        Info person;          // Create an object
        // person.getDetails();  // Get input from user
        person.store();       // Store it in the static vectors (checks room limit)
        person.prinf();
        cout << "Do you want to add another person? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    // Print all records stored in the static vectors
    Info::prinf();
    return 0;
}