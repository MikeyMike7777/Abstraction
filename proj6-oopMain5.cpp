#include <iostream>
#include <fstream>

using namespace std;

const int PLIST_SIZE = 10;

class Person {
private:
    string name;
    int age;

public:
    string getName() { return name; }
    void readPerson(istream &);
    void writePerson(ostream &);
};

void Person::readPerson(istream &in) {
    getline(in, name);
    in >> age;
    in.ignore(3, '\n');
}

void Person::writePerson(ostream &out) {
    out << name << endl;
    out << age << endl;
}



class Customer {
private:
    string name;
    int age;
    double shippingRate;

public:
    Customer();
    string getName() { return name; }
    double getShippingRate() { return shippingRate; }
    void readCustomer( istream & );
    void writeCustomer( ostream & );
};

Customer::Customer() {
    string name;
    int age;
    shippingRate = 5.0;
}

void Customer::readCustomer(istream &in) {
    getline(in, name);
    in >> age;
    in.ignore(3, '\n');
    in >> shippingRate;
    in.ignore(3, '\n');
}

void Customer::writeCustomer(ostream &out) {
    out << name << endl;
    out << age << endl;
    out << shippingRate << endl;
}




class MegaCustomer {
private:
    string name;
    int age;
    double shippingRate;
public:
    MegaCustomer();
    string getName() { return name; }
    double getShippingRate() { return shippingRate; }
    void readMegaCustomer( istream & );
    void writeMegaCustomer( ostream & );
};

MegaCustomer::MegaCustomer() {
    string name;
    int age;
    shippingRate = 0;
}

void MegaCustomer::readMegaCustomer( istream & in ) {
    getline(in, name);
    in >> age;
    in.ignore(3, '\n');
}

void MegaCustomer::writeMegaCustomer( ostream &out ){
    out << name << endl;
    out << age << endl;
    out << shippingRate << endl;
}



void requestInfo(ostream &out, string msg) {
    out << msg << endl;
}

string readAgain(ostream &out, istream &in) {
    string choice;

    out << "Do you want to read in another person (yes/no)? " << endl;
    in >> choice;
    in.ignore(3, '\n');

    return choice;
}

int findPerson(Person *pList[], Customer *cList[], MegaCustomer *mList[], string name, string choice) {
    int pos = -1, index = 0;

    while (choice == "person" and pos == -1 and index < PLIST_SIZE) {
        if (pList[index]->getName() == name) {
            pos = index;
            choice = "person";
        }
        index++;
    }

    while (choice == "customer" and pos == -1 && index < PLIST_SIZE) {
        if (cList[index]->getName() == name) {
            pos = index;
        }
        index++;
    }

    while (choice == "mega" and pos == -1 && index < PLIST_SIZE) {
        if (mList[index]->getName() == name) {
            pos = index;
        }
        index++;
    }

    return pos;
}



int main() {
    Person **pList = new Person *[PLIST_SIZE];
    Customer **cList = new Customer *[PLIST_SIZE];
    MegaCustomer **mList = new MegaCustomer *[PLIST_SIZE];
    string choice, pTypeChoice, msg = "Please enter your name followed by your age.";
    int index = 0;
    bool fileRead = false;
    ifstream pfile;
    ofstream opfile;

    cout << "Would you like to read the data from a file (yes/no)? " << endl;
    cin >> choice;
    cin.ignore(3, '\n');

    if (choice == "yes") {
        fileRead = true;
        pfile.open("iperson.txt");

        if (!pfile) {
            cerr << "Can't open person.txt for read." << endl;
            return 1;
        }
        pfile >> pTypeChoice;
        pfile.ignore(3, '\n');

    } else {
        cout << "What type of Person? (person/customer/mega)" << endl;
        cin >> pTypeChoice;
        cin.ignore(3, '\n');
    }

    choice = "yes";
    if (pTypeChoice == "person") {
        for (int i = 0; i < PLIST_SIZE; i++) {
            //person list
            pList[i] = new Person;
        }
        //use different function per type of person
        if (fileRead) {
            pList[index]->readPerson(pfile);
            if (!pfile) {
                choice = "no";
            }
        }


        //get more people
        while (choice != "no" && index < PLIST_SIZE) {
            if (!fileRead) {
                requestInfo(cout, msg);
                pList[index]->readPerson(cin);
            }

            pList[index]->writePerson(opfile);

            index++;
            if (!fileRead) {
                choice = readAgain(cout, cin);
            } else {
                pList[index]->readPerson(pfile);
                if (!pfile) {
                    choice = "no";
                }
            }
        }
    } else if(pTypeChoice == "customer"){
        for (int i = 0; i < PLIST_SIZE; i++) {
            //customer list
            cList[i] = new Customer;
        }
        msg = "Please enter your name followed by your age then shipping rate.";

        //use different function per type of person
        if (fileRead) {
            cList[index]->readCustomer(pfile);
            if (!pfile) {
                choice = "no";
            }
        }

        //get more customers
        while (choice != "no" && index < PLIST_SIZE) {
            if (!fileRead) {
                requestInfo(cout, msg);
                cList[index]->readCustomer(cin);
            }

            cList[index]->writeCustomer(opfile);

            index++;
            if (!fileRead) {
                choice = readAgain(cout, cin);
            } else {
                cList[index]->readCustomer(pfile);
                if (!pfile) {
                    choice = "no";
                }
            }
        }

    } else if (pTypeChoice == "mega"){
        for( int i = 0; i < PLIST_SIZE; i++ ) {
            //megacustomer list
            mList[i] = new MegaCustomer;
        }

        //use different function per type of person
        if (fileRead) {
            mList[index]->readMegaCustomer(pfile);
            if (!pfile) {
                choice = "no";
            }
        }

        //get more megacustomers
        while (choice != "no" && index < PLIST_SIZE) {
            if (!fileRead) {
                requestInfo(cout, msg);
                mList[index]->readMegaCustomer(cin);
            }

            mList[index]->writeMegaCustomer(opfile);

            index++;
            if (!fileRead) {
                choice = readAgain(cout, cin);
            } else {
                mList[index]->readMegaCustomer(pfile);
                if (!pfile) {
                    choice = "no";
                }
            }
        }
    }

    opfile.open("operson.txt");

    choice = "yes";

    if (fileRead) {
        pfile.close();
    }
    opfile.close();

    cout << "Which person are you looking for? " << endl;
    getline(cin, choice);

    //find person based on type of person
    if ((findPerson(pList, cList, mList, choice, pTypeChoice)) != -1) {
        index = findPerson(pList, cList, mList, choice, pTypeChoice);
        cout << "Found your person: " << endl;
        if (pTypeChoice == "person") {
            pList[index]->writePerson(cout);
        }
        if (pTypeChoice == "customer") {
            cList[index]->writeCustomer(cout);
        }
        if (pTypeChoice == "mega") {
            mList[index]->writeMegaCustomer(cout);
        }
    } else {
        cout << "Couldn't find your person: " << choice << endl;
    }

    for( int i = 0; i < PLIST_SIZE; i++ ){
        delete pList[i];
    }
    delete [] pList;

    return 0;
}