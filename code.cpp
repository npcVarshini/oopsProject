#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class ticket {
public:
    string name;
    string slot;
    string time;
    string ticketType;
    string Price;
    string day;

    ticket() : name(""), slot(""), ticketType(""), day(""), time(""), Price("") {}
    ticket(string n1, string s1, string t1, string d1, string tt1, string p1) {
        name = n1;
        slot = s1;
        ticketType = t1;
        day = d1;
        time = tt1;
        Price = p1;
    }

    void setData() {
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "\n1. Morning slot (FN) -- 9:00AM--11:00AM" << endl;
        cout << "2. Afternoon slot (AN) -- 4:00PM--6:00PM" << endl;
        cout << "Enter slot ( 1 for FN or 2 for AN ): ";
        int a;
        cin >> a;
        switch (a) {
            case 1:
                slot = "fn";
                time = "9:00AM--11:00AM";
                break;
            case 2:
                slot = "an";
                time ="4:00PM--6:00PM";
                break;
        }
        cout << "\n1. Normal -- Free" << endl;
        cout << "2. VIP -- Rs.300/-" << endl;
        cout << "Enter ticket type ( 1 for Normal or 2 for VIP): ";
        int b;
        cin >> b;
        switch (b) {
            case 1:
                ticketType = "normal";
                Price = "Free";
                break;
            case 2:
                ticketType = "vip";
                Price = "300/-";
                break;
        }
        cout << "\nEnter day: (1-Monday , 2-tuesday....., 7-sunday) : ";
        int c;
        cin >> c;
        switch (c) {
            case 1:
                day = "monday";
                break;
            case 2:
                day = "tuesday";
                break;
            case 3:
                day = "wednesday";
                break;
            case 4:
                day = "thursday";
                break;
            case 5:
                day = "friday";
                break;
            case 6:
                day = "saturday";
                break;
            case 7:
                day = "sunday";
                break;
        }
    }

    void display_details() const {
        cout << "Name: " << name << endl;
        cout << "Slot: " << slot << endl;
        cout<<"Time: "<<time<<endl;
        cout << "Ticket Type: " << ticketType << endl;
        cout<<"Price: "<<Price<<endl;
        cout << "Day: " << day << endl;
    }

    string getName() const {
        return name;
    }
    
    string getSlot() const {
        return slot;
    }
    
    string getTime()const
    {
        return time;
    }
    
    string getType() const {
        return ticketType;
    }

    string getPrice()const
    {
        return Price;
    }

    string getDay() const {
        return day;
    }
};

ostream& operator<<(ostream& out, const ticket& t1) {
    out << t1.getName() << "\t\t" << t1.getSlot() << "\t\t" << t1.getType() << "\t\t" << t1.getDay() <<"\t\t" << t1.getTime() <<"\t\t" << t1.getPrice() << endl;
    return out;
}

istream& operator>>(istream& in, ticket& t1) {
    in >> t1.name >> t1.slot >> t1.ticketType >> t1.day >> t1.time >> t1.Price;
    return in;
}

class ticketDataBase {
private:
    string myFile;
    static const int MAX_NORMAL_TICKETS = 3;
    static const int MAX_VIP_TICKETS = 2;

public:
    ticketDataBase(const string& f1) : myFile(f1) {} // Added constructor

    void addTicket() {
        ofstream outFile(myFile, ios::app);
        ticket t1;
        t1.setData();

        int normalCount = countTickets(t1.getDay(), t1.getSlot(), "normal");
        int vipCount = countTickets(t1.getDay(), t1.getSlot(), "vip");

        if (t1.getType() == "normal" && normalCount < MAX_NORMAL_TICKETS) {
            outFile << t1;
            cout << "Normal ticket booked successfully!" << endl;
        } else if (t1.getType() == "vip" && vipCount < MAX_VIP_TICKETS) {
            outFile << t1;
            cout << "VIP ticket booked successfully!" << endl;
        } else {
            cout << "No vacant slots for the specified day, slot, and ticket type." << endl;
        }

        outFile.close();
    }

    void displayAll() {
        ifstream inFile(myFile);
        ticket t1;
        while (inFile >> t1) {
            t1.display_details();
            cout << endl;
        }
        inFile.close();
    }

    void displayTicket(const string& n, const string& d) {
        ifstream inFile(myFile);
        ticket t1;

        bool found = false;

        while (inFile >> t1) {
            if (t1.getName() == n && t1.getDay() == d) {
                t1.display_details();
                found = true;
                break;
            }
        }

        inFile.close();

        if (!found) {
            cout << "Ticket not found with this name: " << n << " on this day: " << d << endl;
        }
    }

    int countTickets(const string& day, const string& slot, const string& ticketType) {
        ifstream inFile(myFile);
        ticket t1;

        int count = 0;

        while (inFile >> t1) {
            if (t1.getDay() == day && t1.getSlot() == slot && t1.getType() == ticketType) {
                count++;
            }
        }

        inFile.close();
        return count;
    }

    void displayVacancies(const string& inputDay) {
        ifstream inFile(myFile);
        ticket t1;

        int normalCountMorning = 0;
        int vipCountMorning = 0;
        int normalCountAfternoon = 0;
        int vipCountAfternoon = 0;

        while (inFile >> t1) {
            if (t1.getDay() == inputDay) {
                if (t1.getSlot() == "fn") { // Morning Slot
                    if (t1.getType() == "normal") { // Normal Ticket
                        normalCountMorning++;
                    } else if (t1.getType() == "vip") { // VIP Ticket
                        vipCountMorning++;
                    }
                } else if (t1.getSlot() == "an") { // Afternoon Slot
                    if (t1.getType() == "normal") { // Normal Ticket
                        normalCountAfternoon++;
                    } else if (t1.getType() == "vip") { // VIP Ticket
                        vipCountAfternoon++;
                    }
                }
            }
        }

        inFile.close();


        cout<<"Vacancies for Day " << inputDay << ":\n";
        cout<<"\tslot\t\tnormal-booked\tnormal-vacant\tVIP-booked\tVIP-vacant\n";
        cout<<"Morning Slot: \t\t"<<normalCountMorning<<"\t\t"<<MAX_NORMAL_TICKETS - normalCountMorning<<"\t\t"<<vipCountMorning<<"\t\t"<<MAX_VIP_TICKETS - vipCountMorning<<"\n";
        cout<<"Afternoon Slot: \t"<<normalCountAfternoon<<"\t\t"<<MAX_NORMAL_TICKETS - normalCountAfternoon<<"\t\t"<<vipCountAfternoon<<"\t\t"<<MAX_VIP_TICKETS - vipCountAfternoon<<"\n";
        

    }
};

int main() {
    cout<<"\n\n              !!!! TEMPLE TICKET BOOKING SYSTEM !!!! \n\n"<<endl;
    cout<<"Ticket counter will be open for only current week."<<endl;
    cout<<"Each day will have 2 slots in a week - FN & AN."<<endl;
    cout<<"Each slot will total only 5 tickets."<<endl;
    cout<<"3 normal tickets in each slot which costs free."<<endl;
    cout<<"2 vip tickets in each slot which costs Rs.300/-."<<endl;
    ticketDataBase db1("list.txt");
    int choice;
    string name;
    string day;
    do {
        cout << "\nMENU\n1. Book a Ticket " << endl;
        cout << "2. Show booked details " << endl;
        cout << "3. Show my ticket " << endl;
        cout << "4. Show vacancies " << endl;
        cout << "5. Exit" << endl;
        cin >> choice;
        switch (choice) {
            case 1:
                db1.addTicket();
                break;
            case 2:
                db1.displayAll();
                break;
            case 3:
                cout << "Enter name and day to display ticket: " << endl;
                cin >> name >> day;
                db1.displayTicket(name, day);
                break;
            case 4:
                cout << "Enter day to check vacancies: ";
                cin >> day;
                db1.displayVacancies(day);
                break;
            case 5:
                cout << "Exiting Program";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
    
}
