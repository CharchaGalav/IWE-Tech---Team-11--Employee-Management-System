#include "Employee_management.h"

void Employee_management ::add_blank() // add a blank employee to the vector for search optimization
{
    Emp blan;
    blan.first_name = "";
    blan.last_name = "";
    blan.designation = "";
    blan.kerberosId = "";
    blan.date_of_birth = "";
    blan.start_date = "";
    blan.end_date = "";
    blan.isterminated = false;

    employee_data.push_back(blan);
}

string Employee_management ::date() // get current date
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    int current_date = ltm->tm_mday;
    int current_month = 1 + ltm->tm_mon;
    int current_year = 1900 + ltm->tm_year;
    string date = to_string(current_date) + "/" + to_string(current_month) + "/" + to_string(current_year);
    return date;
}

vector<int> Employee_management ::integer_format_date(string date) // convert date to integer format
{
    vector<int> date_vector;
    string T;
    stringstream X(date);
    while (getline(X, T, '/'))
    {
        if (T.length() == 0 || !isdigit(T[0]))
        {
            T = "0";
            date_vector.push_back(stoi(T));
        }
        else
            date_vector.push_back(stoi(T));
    }
    return date_vector;
}

string Employee_management ::age_calculator(string date_of_birth) // calculate age of the employee
{
    string today_date = date();
    vector<int> today_date_vector = integer_format_date(today_date);

    int current_date = today_date_vector[0];
    int current_month = today_date_vector[1];
    int current_year = today_date_vector[2];
    vector<int> int_dob = integer_format_date(date_of_birth);
    int dd = int_dob[0];
    int mm = int_dob[1];
    int yyyy = int_dob[2];

    if (dd > current_date)
    {
        current_month = current_month - 1;
    }

    if (mm > current_month)
    {
        current_year = current_year - 1;
        current_month = current_month + 12;
    }

    int calculated_month = current_month - mm;
    int calculated_year = current_year - yyyy;

    string age = to_string(calculated_year) + "y " + to_string(calculated_month) + "m";
    return age;
}

bool Employee_management ::validateDate(string dte) // date validation
{
    string today_date = date();
    vector<int> today_date_vector = integer_format_date(today_date);
    int current_date = today_date_vector[0];
    int current_month = today_date_vector[1];
    int current_year = today_date_vector[2];

    vector<int> date_vector = integer_format_date(dte);
    int dd = date_vector[0];
    int mm = date_vector[1];
    int yyyy = date_vector[2];

    int leap = 0;
    if (((yyyy % 4 == 0) && (yyyy % 100 != 0)) || (yyyy % 400 == 0))
    {
        leap = 1;
    }
    if (dd > 31 || dd < 1)
    {
        cout << "Invalid Date" << endl;
        return false;
    }
    else if (mm > 12 || mm < 1)
    {
        cout << "Invalid Date" << endl;
        return false;
    }
    else if (yyyy > current_year || yyyy < 1900)
    {
        cout << "Invalid Date" << endl;
        return false;
    }
    else if (mm == 2 && leap == 1 && dd > 29)
    {
        cout << "Invalid Date" << endl;
        return false;
    }
    else if (mm == 2 && leap == 0 && dd > 28)
    {
        cout << "Invalid Date" << endl;
        return false;
    }
    else if ((mm == 4 || mm == 6 || mm == 9 || mm == 11) && dd > 30)
    {
        cout << "Invalid Date" << endl;
        return false;
    }
    else if (yyyy == current_year && mm == current_month && dd > current_date)
    {
        cout << "Invalid Date" << endl;
        return false;
    }
    else if (yyyy == current_year && mm > current_month)
    {
        cout << "Invalid Date" << endl;
        return false;
    }
    else if (yyyy > current_year)
    {
        cout << "Invalid Date" << endl;
        return false;
    }
    else
    {
        return true;
    }
}

bool Employee_management ::validateAge(string start_date, string date_of_birth) // validate age of employee, it should not be less than 18 years
{
    vector<int> start_date_vector = integer_format_date(start_date);
    int start_dd = start_date_vector[0];
    int start_mm = start_date_vector[1];
    int start_yyyy = start_date_vector[2];

    vector<int> int_dob = integer_format_date(date_of_birth);
    int dd = int_dob[0];
    int mm = int_dob[1];
    int yyyy = int_dob[2];

    if (dd > start_dd)
    {
        start_mm = start_mm - 1;
    }

    if (mm > start_mm)
    {
        start_yyyy = start_yyyy - 1;
        start_mm = start_mm + 12;
    }

    int calculated_year = start_yyyy - yyyy;

    if (calculated_year < 18)
    {
        cout << "Employee age should be atleast 18 years." << endl;
        return false;
    }
    else
    {
        return true;
    }
}

string Employee_management ::generateId(string first_name, string last_name) // generate unique id for employee
{
    string id = "";
    string s = first_name + last_name;
    int n = s.size();
    srand(time(NULL));
    while (1)
    {
        int i = rand() % n;
        id += s[i];
        if (kerberos_ids[id] == 0)
            break;
    }
    return id;
}

void Employee_management ::employeeDetail() // display details of employee
{
    for (int i = 1; i < employee_data.size(); i++)
    {
        string name = employee_data[i].first_name + " " + employee_data[i].last_name;
        string age = age_calculator(employee_data[i].date_of_birth);
        string status;
        if (employee_data[i].isterminated == true)
        {
            status = "Terminated";
        }
        else
        {
            status = "Active";
        }

        cout << left << setw(15) << status << left << setw(50) << name << left << setw(45) << employee_data[i].kerberosId << left << setw(25) << employee_data[i].designation << left << setw(15) << employee_data[i].date_of_birth << left << setw(10) << age << left << setw(15) << employee_data[i].start_date << left << setw(15) << employee_data[i].end_date;
        cout << "\n\n";
    }
}

void Employee_management ::addEmployeeInput() //Function to add employee details in vector
{
    Emp employee;
    cout << "Enter First Name: ";
    cin >> employee.first_name;
    cout << "Enter Last Name: ";
    cin >> employee.last_name;
    cout << "Enter Designation: ";
    getline(cin >> ws, employee.designation);
    cout << "Enter Date of Birth (Format: dd/mm/yyyy): ";
    cin >> employee.date_of_birth;

    while (validateDate(employee.date_of_birth) == 0 || validateAge(date(), employee.date_of_birth) == 0)
    {
        cout << "Enter Date of Birth (Format: dd/mm/yyyy): ";
        cin >> employee.date_of_birth;
    }

    cout << "Enter Date of Joining (Format: dd/mm/yyyy) (Employee age should be atleast 18 years from date of joining): ";
    cin >> employee.start_date;

    while (validateDate(employee.start_date) == 0 || validateAge(employee.start_date, employee.date_of_birth) == 0)
    {
        cout << "Enter Date of Joining (Format: dd/mm/yyyy) (Employee age should be atleast 18 years from date of joining): ";
        cin >> employee.start_date;
    }

    employee.end_date = "31/12/9999";
    employee.isterminated = false;

    employee.kerberosId = generateId(employee.first_name, employee.last_name);
    cout << "\nYour Kerberos Id is: " << employee.kerberosId << "    (Please remember your Kerberos Id !)" << endl;

    cout << "\n\t\tEmployee Data Saved !!!" << endl;
    
    int i = employee_data.size();
    kerberos_ids[employee.kerberosId] = i;

    employee_data.push_back(employee);
}

int Employee_management ::searchEmployee(string kerberos) // search any employee
{
    int flag = 0;
    if (kerberos_ids[kerberos])
    {
        int i = kerberos_ids[kerberos];
        if (employee_data[i].isterminated == false)
        {
            string name = employee_data[i].first_name + " " + employee_data[i].last_name;
            string age = age_calculator(employee_data[i].date_of_birth);
            cout << left << setw(50) << "NAME" << left << setw(45) << "KERBEROS ID" << left << setw(25) << "DESIGNATION" << left << setw(20) << "DATE OF BIRTH" << left << setw(15) << "AGE" << left << setw(15) << "START DATE" << left << setw(15) << "END DATE"
                 << "\n\n";
            cout << left << setw(50) << name << left << setw(45) << employee_data[i].kerberosId << left << setw(25) << employee_data[i].designation << left << setw(20) << employee_data[i].date_of_birth << left << setw(15) << age
                 << left << setw(15) << employee_data[i].start_date << left << setw(15) << employee_data[i].end_date;
            cout << "\n\n";
            flag = 1;
        }
    }

    if (flag == 0)
    {
        cout << "Employee with given Kerberos Id not found / terminated !!! " << endl;
    }
    return flag;
}

bool Employee_management ::filterDate_check(string filter_date, string start_date, string end_date) //checks if filter_date is between start_date and end_date
{
    vector<int> checkDate = integer_format_date(filter_date);
    int check_dd = checkDate[0];
    int check_mm = checkDate[1];
    int check_yyyy = checkDate[2];

    vector<int> startingDate = integer_format_date(start_date);
    int start_dd = startingDate[0];
    int start_mm = startingDate[1];
    int start_yyyy = startingDate[2];

    vector<int> endingDate = integer_format_date(end_date);
    int end_yyyy = endingDate[2];

    if (check_yyyy < start_yyyy || check_yyyy > end_yyyy)
        return false;
    if (check_yyyy == start_yyyy && check_mm < start_mm)
        return false;
    if (check_yyyy == start_yyyy && check_mm == start_mm && check_dd < start_dd)
        return false;

    return true;
}

void Employee_management ::filter(int choice) // filter employees by date and designation
{
    if (choice == 1)
    {
        int count = 0;
        string filter_date;
        cout << "Enter filter date: \n";
        cin >> filter_date;
        while (validateDate(filter_date) == 0)
        {
            cout << "Enter filter date: \n";
            cin >> filter_date;
        }
        cout << "\n\n";
        for (int i = 1; i < employee_data.size(); i++)
        {
            string name = employee_data[i].first_name + " " + employee_data[i].last_name;

            if (filterDate_check(filter_date, employee_data[i].start_date, employee_data[i].end_date))
            {
                if (employee_data[i].isterminated == false)
                {
                    count++;
                    if (count == 1)
                    {
                        cout << left << setw(50) << "NAME" << left << setw(10) << "KERBEROS ID"
                             << "\n\n";
                    }
                    cout << left << setw(50) << name << left << setw(10) << employee_data[i].kerberosId << "\n\n";
                }
            }
        }
        if (count == 0)
        {
            cout << "No employee found on given date !!! " << endl;
        }
    }

    if (choice == 2)
    {
        int count = 0;
        cout << "Enter Designation: \n";
        string title;
        cin >> title;
        cout << "\n\n";

        for (int i = 1; i < employee_data.size(); i++)
        {
            if (title == employee_data[i].designation && employee_data[i].isterminated == false)
            {
                count++;
                if (count == 1)
                {
                    cout << left << setw(50) << "NAME" << left << setw(45) << "KERBEROS ID" << left << setw(50) << "DESIGNATION"
                         << "\n\n";
                }
                string name = employee_data[i].first_name + " " + employee_data[i].last_name;
                cout << left << setw(50) << name << left << setw(45) << employee_data[i].kerberosId << left << setw(50) << employee_data[i].designation << "\n\n";
            }
        }
        if (count == 0)
        {
            cout << "No employee found with given designation !!! " << endl;
        }
    }
}

void Employee_management ::terminate(string kerberos) // terminate any employee
{
    int flag = 0;
    if (kerberos_ids[kerberos])
    {
        int i = kerberos_ids[kerberos];

        if (employee_data[i].isterminated == false)
        {
            flag = 1;
            employee_data[i].end_date = date();
            employee_data[i].isterminated = true;
            cout << "\n\t\tEmployee Terminated !!!" << endl;
        }
    }
    if (flag == 0)
    {
        cout << "Employee with given Kerberos Id not found / terminated !!! " << endl;
    }
}

void Employee_management ::update(string kerberos) // uodate details of any employee
{
    cout << "Preveous Record of Employee is: \n"
         << endl;
    int flag = searchEmployee(kerberos);
    if (flag == 1)
    {
        cout << "Enter New Details of Employee: \n"
             << endl;

        int i = kerberos_ids[kerberos];

        if (employee_data[i].isterminated == false)
        {
            string f_name = employee_data[i].first_name;
            string l_name = employee_data[i].last_name;
            cout << "Enter First Name: ";
            cin >> employee_data[i].first_name;
            cout << "Enter Last Name: ";
            cin >> employee_data[i].last_name;
            cout << "Enter Designation: ";
            getline(cin >> ws, employee_data[i].designation);
            cout << "Enter Date of Birth (Format: dd/mm/yyyy): ";
            cin >> employee_data[i].date_of_birth;

            while (validateDate(employee_data[i].date_of_birth) == 0)
            {
                cout << "Enter Date of Birth (Format: dd/mm/yyyy): ";
                cin >> employee_data[i].date_of_birth;
            }

            cout << "Enter Date of Joining (Format: dd/mm/yyyy) (Employee age should be atleast 18 years from date of joining): ";
            cin >> employee_data[i].start_date;

            while (validateDate(employee_data[i].start_date) == 0 || validateAge(employee_data[i].start_date, employee_data[i].date_of_birth) == 0)
            {
                cout << "Enter Date of Joining (Format: dd/mm/yyyy) (Employee age should be atleast 18 years from date of joining): ";
                cin >> employee_data[i].start_date;
            }

            if (f_name != employee_data[i].first_name || l_name != employee_data[i].last_name)
            {
                employee_data[i].kerberosId = generateId(employee_data[i].first_name, employee_data[i].last_name);
                kerberos_ids.erase(kerberos);
                kerberos_ids[employee_data[i].kerberosId] = i;
                cout << "\nYour new Kerberos Id is : " << employee_data[i].kerberosId << "     (Please remember your Kerberos Id !)" << endl;
            }

            cout << "\n\t\tEmployee Data Updated !!!" << endl;
        }
    }
}

void Employee_management ::waitForEnter(void)
{
    cout << "\n\n Press enter to go back \n\n";
    cin.get();
    cin.get();
}

bool Employee_management ::checker() // check if user is using menu functinalities without adding any employee
{
    if (employee_data.size() == 1)
    {
        cout << "\nNo employee data found. Please add employee data first." << endl;
        return false;
    }
    else
        return true;
}