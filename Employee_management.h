#ifndef EMPLOYEE_MANAGEMENT_H
#define EMPLOYEE_MANAGEMENT_H

#include <bits/stdc++.h>
using namespace std;

struct Emp
{
    string first_name;
    string last_name;
    string designation;
    string kerberosId;
    string date_of_birth;
    string start_date;
    string end_date;
    bool isterminated;
};

class Employee_management
{
private:
 
    map<string, int> kerberos_ids;
    vector<Emp> employee_data;

public:
    void addEmployeeInput();
    bool validateDate(string);
    bool validateAge(string, string);
    string generateId(string, string);
    void employeeDetail();
    int searchEmployee(string);
    bool filterDate_check(string, string, string);
    void filter(int);
    void terminate(string);
    void update(string);
    string age_calculator(string);
    void waitForEnter();
    string date();
    vector<int> integer_format_date(string);
    bool checker();
    void add_blank();
};

#endif // EMPLOYEE_MANAGEMENT_H