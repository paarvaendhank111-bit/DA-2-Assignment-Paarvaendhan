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
    Student() {}

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
             << " | " << getAttendancePercent() << "%\n";
    }

    string serialize() {
        string data = regNo + "," + name + ",";
        for(char c : attendance) data += c;
        return data;
    }

    void deserialize(string line) {
        attendance.clear();
        int i = line.find(',');
        int j = line.find(',', i+1);

        regNo = line.substr(0, i);
        name = line.substr(i+1, j-i-1);

        for(int k = j+1; k < line.length(); k++) {
            attendance.push_back(line[k]);
        }
    }
};

class AttendanceManager {
private:
    vector<Student> students;

public:
    void loadFromFile() {
        ifstream file("data.txt");
        if(!file) return;

        string line;
        while(getline(file, line)) {
            Student s;
            s.deserialize(line);
            students.push_back(s);
        }
        file.close();
    }

    void saveToFile() {
        ofstream file("data.txt");
        for(auto &s : students) {
            file << s.serialize() << endl;
        }
        file.close();
    }

    void addStudent() {
        string reg, name;
        cout << "Enter RegNo: "; cout.flush();
        cin >> reg;

        for(auto &s : students) {
            if(s.getRegNo() == reg) {
                cout << "Duplicate student!\n";
                return;
            }
        }

        cout << "Enter Name: "; cout.flush();
        cin >> name;

        students.push_back(Student(reg, name));
        saveToFile();
    }

    void markAttendance() {
        char status;
        for(auto &s : students) {
            cout << "Mark " << s.getName() << " (P/A): "; cout.flush();
            cin >> status;

            if(status != 'P' && status != 'A') {
                cout << "Invalid!\n";
                return;
            }

            s.markAttendance(status);
        }
        saveToFile();
    }

    void showAll() {
        for(auto &s : students) {
            s.display();
        }
    }

    void shortage() {
        for(auto &s : students) {
            if(s.getAttendancePercent() < 75) {
                s.display();
            }
        }
    }

    void average() {
        double total = 0;
        for(auto &s : students) {
            total += s.getAttendancePercent();
        }

        if(students.size() == 0) {
            cout << "No data\n";
            return;
        }

        cout << "Class Avg: " << total / students.size() << "%\n";
    }
};

int main() {
    AttendanceManager am;
    am.loadFromFile();

    int choice;

    do {
        cout << "\n1.Add\n2.Mark\n3.Show\n4.Shortage\n5.Average\n0.Exit\nChoice: ";
        cout.flush();
        cin >> choice;

        switch(choice) {
            case 1: am.addStudent(); break;
            case 2: am.markAttendance(); break;
            case 3: am.showAll(); break;
            case 4: am.shortage(); break;
            case 5: am.average(); break;
        }

    } while(choice != 0);

    return 0;
}
