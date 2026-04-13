#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Student {
private:
    string regNo;
    string name;
    vector<char> attendance;

public:
    Student(string r, string n) {
        regNo = r;
        name = n;
    }

    string getRegNo() { return regNo; }
    string getName() { return name; }

    void markAttendance(char status) {
        attendance.push_back(status);
    }

    double getAttendancePercent() {
        if(attendance.size() == 0) return 0;
        int present = 0;
        for(char c : attendance) {
            if(c == 'P') present++;
        }
        return (present * 100.0) / attendance.size();
    }

    void display() {
        cout << regNo << " - " << name 
             << " | Attendance: " << getAttendancePercent() << "%" << endl;
    }

    vector<char>& getAttendance() {
        return attendance;
    }
};

class AttendanceManager {
private:
    vector<Student> students;

public:
    void addStudent() {
        string reg, name;
        cout << "Enter RegNo: ";
        cin >> reg;

        // check duplicate
        for(auto &s : students) {
            if(s.getRegNo() == reg) {
                cout << "Student already exists!\n";
                return;
            }
        }

        cout << "Enter Name: ";
        cin >> name;

        students.push_back(Student(reg, name));
    }

    void markAttendance() {
        char status;
        for(auto &s : students) {
            cout << "Mark attendance for " << s.getName() << " (P/A): ";
            cin >> status;

            if(status != 'P' && status != 'A') {
                cout << "Invalid input!\n";
                return;
            }

            s.markAttendance(status);
        }
    }

    void showAll() {
        for(auto &s : students) {
            s.display();
        }
    }

    void shortageList() {
        cout << "\nStudents below 75%:\n";
        for(auto &s : students) {
            if(s.getAttendancePercent() < 75) {
                s.display();
            }
        }
    }

    void classAverage() {
        double total = 0;
        for(auto &s : students) {
            total += s.getAttendancePercent();
        }

        if(students.size() == 0) {
            cout << "No students\n";
            return;
        }

        cout << "Class Average: " << total / students.size() << "%\n";
    }
};

int main() {
    AttendanceManager am;
    int choice;

    do {
        cout << "\n1. Add Student\n2. Mark Attendance\n3. Show All\n4. Shortage List\n5. Class Average\n0. Exit\nChoice: ";
        cin >> choice;

        switch(choice) {
            case 1: am.addStudent(); break;
            case 2: am.markAttendance(); break;
            case 3: am.showAll(); break;
            case 4: am.shortageList(); break;
            case 5: am.classAverage(); break;
        }

    } while(choice != 0);

    return 0;
}
