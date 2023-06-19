#include <iostream>
#include <vector>
using namespace std;

class Person{
    public:
        Person(string name, int age)
        :name(name), age(age){}
        void display() const {
            cout << "name = " << name << ", age = " << age << endl;
        }
        ~Person(){
            cout << "~Person()" << endl;
        }
    private:
        string name;
        int age;
};

class Employee
:public Person{
public:
    Employee(string name, int age, string department, double salary)
    :Person(name, age), department(department), salary(salary){}
    void display ()const {
        Person::display();
        cout << "department = " << department << ", salary = " << salary << endl;
    }
    ~Employee(){
        cout << "~Employee()" << endl;
    }
    double getSalary() const {
        return salary;
    }
private:
    string department;
    double salary;
};

int main(){
    vector<Employee> employees;
    Employee e1("zhangsan", 20, "department1", 10000);
    employees.push_back(e1);
    Employee e2("lisi", 21, "department2", 20000);
    employees.push_back(e2);
    Employee e3("wangwu", 22, "department3", 30000);
    employees.push_back(e3);
    // e1.display();
    // e2.display();
    // e3.display();
    //cout << "average salary = " << (e1.getSalary() + e2.getSalary() + e3.getSalary()) / 3 << endl;
    double sum = 0;
    for(auto & e : employees){
        e.display();
        sum += e.getSalary();
    }
    cout << "the count of employee is " << employees.size() << endl;
    cout << "average salary = " << sum / employees.size() << endl;
    return 0;
}