#include <iostream>
#include <fstream>

using namespace std;

int main() {
    string name, choice;
    int age;
    bool fileRead = false;
    ifstream pfile;
    ofstream opfile;

    //ask user if file or user input
    cout << "Would you like to read the data from a file? " << endl;
    cin >> choice;
    cin.ignore(3, '\n');

    //make sure file is open
    if( choice == "yes" ) {
        //will read from file not user input
        fileRead = true;
        pfile.open("iperson.txt");
        if( !pfile ) {
            cerr << "Can't open person.txt for read." << endl;
            return 1;
        }
    }

    opfile.open("operson.txt");

    //read from file
    if( fileRead ) {
        getline( pfile, name );
        pfile >> age;
        pfile.ignore(3, '\n');
        if( !pfile ) {
            choice = "no";
        }
    }

    //set reading a new person to yes
    choice = "yes";

    //if new person
    while( choice != "no" ) {
        //if user input
        if( !fileRead ) {
            cout << "Please enter your name followed by your age." << endl;
            getline( cin, name );
            cin >> age;
            cin.ignore(3, '\n');
        }

        //print out the user input or file data
        opfile << name << endl;
        opfile << age << endl;;

        //get new user input
        if( !fileRead ) {
            cout << "Do you want to read in another person (yes/no)? " << endl;
            cin >> choice;
            cin.ignore(3, '\n');
        //get new file data
        } else {
            if( !pfile ) {
                choice = "no";
            }
            getline( pfile, name );
            pfile >> age;
            pfile.ignore(3, '\n');
        }
    }

    //close file if reading from file
    if( fileRead ) {
        pfile.close();
    }
    opfile.close();

    return 0;
}
