#include "Employee_management.h"
#include "Employee_management.cpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    Employee_management system;
    system.add_blank();
    while (true)
    {
        char choice;
        char x;
        cout << "\n------------------Employee Management----------------------\n"
             << endl;
        cout << "Press 1 to Add an Employee\n"
             << endl;
        cout << "Press 2 to Search an Employee\n"
             << endl;
        cout << "Press 3 to Filter Employees\n"
             << endl;
        cout << "Press 4 to Terminate an Employee\n"
             << endl;
        cout << "Press 5 to Display all Employees\n"
             << endl;
        cout << "Press 6 to Update an Employee\n"
             << endl;
        cout << "Press 7 to Exit\n"
             << endl;

        cout << "Choice Options: [1 / 2 / 3 / 4 / 5 / 6 / 7]" << endl;

        cout << "\nEnter your choice: " << endl;

        cin >> choice;

        string kerberos;
        switch (choice)
        {
        case '1':
            do
            {
                system.addEmployeeInput();
                cout << "\n\nDo you want to add another employee? (y/n)  ";
                cin >> x;
            } while (x == 'y' || x == 'Y');
            system.waitForEnter();
            break;

        case '2':
            if (system.checker())
            {
                cout << "Enter a kerberos id to search: " << endl;
                cin >> kerberos;
                cout << "\n\n";
                system.searchEmployee(kerberos);
                system.waitForEnter();
                break;
            }
            else
            {
                system.waitForEnter();
                break;
            }

        case '3':
            if (system.checker())
            {
                cout << "Press 1 to filter by isActive as of a date\n"
                     << endl;
                cout << "Press 2 to filter by title\n"
                     << endl;
                int filterChoice;
                cin >> filterChoice;
                system.filter(filterChoice);
                system.waitForEnter();
                break;
            }
            else
            {
                system.waitForEnter();
                break;
            }

        case '4':
            if (system.checker())
            {
                cout << "Enter a kerberos id to terminate: " << endl;
                cin >> kerberos;
                cout << "\n\n";
                system.terminate(kerberos);
                system.waitForEnter();
                break;
            }
            else
            {
                system.waitForEnter();
                break;
            }

        case '5':
            if (system.checker())
            {
                cout << left << setw(15) << "STATUS" << left << setw(50) << "NAME" << left << setw(45) << "KERBEROS ID" << left << setw(25) << "DESIGNATION" << left << setw(15) << "DOB" << left << setw(10) << "AGE" << left << setw(15) << "START DATE" << left << setw(15) << "END DATE"
                     << "\n\n";
                system.employeeDetail();
                system.waitForEnter();
                break;
            }
            else
            {
                system.waitForEnter();
                break;
            }

        case '6':
            if (system.checker())
            {
                cout << "Enter a kerberos id to update: " << endl;
                cin >> kerberos;
                cout << "\n\n";
                system.update(kerberos);
                system.waitForEnter();
                break;
            }
            else
            {
                system.waitForEnter();
                break;
            }

        case '7':
            exit(0);
            break;

        default:
            cout << "Please select a valid choice" << endl;
            system.waitForEnter();
            break;
        }
    }
}
