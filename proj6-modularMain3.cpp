#include <iostream>
#include <fstream>

using namespace std;

const int PLIST_SIZE = 10;

void readPerson( istream &in, string &name, int &age ) {
    getline( in, name );
    in >> age;
    in.ignore(3, '\n');
}

void readCustomer( istream &in, string &name, int &age, double shippingRate ) {
    getline( in, name );
    in >> age;
    in >> shippingRate;
    in.ignore(3, '\n');
}

void writePerson( ostream &out, string name, int age ) {
    out << name << endl;
    out << age << endl;
}

void writeCustomer( ostream &out, string name, int age, double shippingRate ) {
    out << name << endl;
    out << age << endl;
    out << shippingRate << endl;
}

void requestInfo( ostream &out ) {
    out << "Please enter your name followed by your age." << endl;
}

string readAgain( ostream &out, istream &in ) {
    string choice;

    out << "Do you want to read in another person (yes/no)? " << endl;
    in >> choice;
    in.ignore(3, '\n');

    return choice;
}

int findPerson( string nameList[], string name ) {
    int pos = -1, index = 0;
    //linear search
    while( pos == -1 && index < PLIST_SIZE ) {
        if( nameList[index] == name ) {
            pos = index;
        }
        index++;
    }

    return pos;
}

int main() {
    int pAgeList[PLIST_SIZE];
    string pNameList[PLIST_SIZE];
    double cShip[PLIST_SIZE];

    string name, choice, pTypeChoice;
    int index = 0;
    bool fileRead = false;
    ifstream pfile;
    ofstream opfile;

    cout << "Would you like to read the data from a file (yes/no)? " << endl;
    cin >> choice;
    cin.ignore(3, '\n');

    //read another == yes
    if( choice == "yes" ) {
        //read from file
        fileRead = true;
        pfile.open("iperson.txt");
        if( !pfile ) {
            cerr << "Can't open person.txt for read." << endl;
            return 1;
        }
    }

    opfile.open("operson.txt");

    choice = "yes";
    //if reading from file
    if( fileRead ) {
        pfile >> pTypeChoice;
        pfile.ignore(3, '\n');
    }
    //if getting from user input
    else {
        cout << "What type of Person? (person/customer)" << endl;
        cin >> pTypeChoice;
        cin.ignore(3, '\n');
    }

    opfile.open("operson.txt");

    //if reading a person
    if( pTypeChoice == "person" ) {
        //get new person
        choice = "yes";
        //read new person from file
        if (fileRead) {
            pfile >> pNameList[index];
            pfile >> pAgeList[index];
            if (!pfile) {
                choice = "no";
            }
        }
        while (choice != "no" and index < PLIST_SIZE) {
            //if not reading a person from a file
            if (!fileRead) {
                requestInfo(cout);
                readPerson(cin, pNameList[index], pAgeList[index]);
            }
            writePerson(opfile, pNameList[index], pAgeList[index]);
            index++;

            //if not reading from file
            if (!fileRead) {
                //get another person?
                choice = readAgain(cout, cin);
            } else {
                //get another person from the file if they exist
                readPerson(pfile, pNameList[index], pAgeList[index]);
                if (!pfile) {
                    choice = "no";
                }
            }
        }
        if (fileRead) {
            pfile.close();
        }
        opfile.close();

        cout << "Which person are you looking for? " << endl;
        getline(cin, choice);

        if (findPerson(pNameList, choice) != -1) {
            index = findPerson(pNameList, choice);
            cout << "Found your person: " << endl;
            writePerson(cout, pNameList[index], pAgeList[index]);
        } else {
            cout << "Couldn't find your person: " << choice << endl;
        }
    }
    else {
        opfile.open("ocustomer.txt");
        choice = "yes";

        if (fileRead) {
           readCustomer(pfile, pNameList[index], pAgeList[index], cShip[index]);
            if (!pfile) {
                choice = "no";
            }
        }
        while (choice != "no" and index < PLIST_SIZE) {
            //if not reading a person from a file
            if (!fileRead) {
                requestInfo(cout);
                readCustomer(pfile, pNameList[index], pAgeList[index], cShip[index]);
            }
            writeCustomer( opfile, pNameList[index], pAgeList[index], cShip[index]);
            index++;

            //if not reading from file
            if (!fileRead) {
                //get another person?
                choice = readAgain(cout, cin);
            } else {
                //get another person from the file if they exist
                readPerson(pfile, pNameList[index], pAgeList[index]);
                if (!pfile) {
                    choice = "no";
                }
            }
        }
        if (fileRead) {
            pfile.close();
        }
        opfile.close();

        cout << "Which person are you looking for? " << endl;
        getline(cin, choice);

        if (findPerson(pNameList, choice) != -1) {
            index = findPerson(pNameList, choice);
            cout << "Found your person: " << endl;
            writeCustomer(cout, pNameList[index], pAgeList[index], cShip[index]);
        } else {
            cout << "Couldn't find your person: " << choice << endl;
        }
    }

    return 0;
}