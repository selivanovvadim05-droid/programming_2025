#include "Student.h"
#include <algorithm> 
#include <iterator> 

using namespace std;

vector<string> Student::getUniqueSortedDebts() const {
    vector<string> sorted_unique_debts = debts;
    sort(sorted_unique_debts.begin(), sorted_unique_debts.end());
    sorted_unique_debts.erase(unique(sorted_unique_debts.begin(), sorted_unique_debts.end()), sorted_unique_debts.end());
    return sorted_unique_debts;
}

Student::Student(const string& name, const string& surname, const vector<string>& debts)
    : name(name), surname(surname), debts(debts) {
    cout << "Student " << this->name << " " << this->surname << " created." << endl;
}

Student::~Student() {
    if (!debts.empty()) 
        debts.clear(); 
    cout << "Student " << name << " " << surname << " destroyed, debts cleared." << endl;
}

Student::Student(const Student& other)
    : name(other.name), surname(other.surname), debts(other.debts) {
    cout << "Student " << this->name << " " << this->surname << " copied." << endl;
}

Student& Student::operator=(const Student& other) {
    if (this == &other) 
        return *this;
    this->name = other.name;
    this->surname = other.surname;
    this->debts = other.debts; 
    cout << "Student " << this->name << " " << this->surname << " assigned." << endl;
    return *this;
}


Student Student::operator+(const Student& other) const {
    string newName = this->name + " and " + other.name;
    string newSurname = this->surname + " and " + other.surname;


    vector<string> this_sorted_unique_debts = this->getUniqueSortedDebts();
    vector<string> other_sorted_unique_debts = other.getUniqueSortedDebts();
    
    vector<string> combined_debts;
    set_union(this_sorted_unique_debts.begin(), this_sorted_unique_debts.end(),
                   other_sorted_unique_debts.begin(), other_sorted_unique_debts.end(),
                   back_inserter(combined_debts));

    return Student(newName, newSurname, combined_debts);
}


Student& Student::operator-=(const Student& other) {
    this->name = this->name + " without " + other.name;
    this->surname = this->surname + " without " + other.surname;

    vector<string> this_sorted_unique_debts = this->getUniqueSortedDebts();
    vector<string> other_sorted_unique_debts = other.getUniqueSortedDebts();
    
    vector<string> remaining_debts;
    set_difference(this_sorted_unique_debts.begin(), this_sorted_unique_debts.end(),
                        other_sorted_unique_debts.begin(), other_sorted_unique_debts.end(),
                        back_inserter(remaining_debts));
    this->debts = remaining_debts; 

    return *this;
}

Student Student::operator/(const Student& other) const {
    string newName = this->name + " and " + other.name;
    string newSurname = this->surname + " and " + other.surname;

    vector<string> this_sorted_unique_debts = this->getUniqueSortedDebts();
    vector<string> other_sorted_unique_debts = other.getUniqueSortedDebts();
    
    vector<string> common_debts;
    set_intersection(this_sorted_unique_debts.begin(), this_sorted_unique_debts.end(),
                          other_sorted_unique_debts.begin(), other_sorted_unique_debts.end(),
                          back_inserter(common_debts));

    return Student(newName, newSurname, common_debts);
}

ostream& operator<<(ostream& os, const Student& student) {
    os << "Student: " << student.name << " " << student.surname << endl;
    os << "  Debts: [";
    if (!student.debts.empty()) {
        for (size_t i = 0; i < student.debts.size(); ++i) {
            os << student.debts[i];
            if (i < student.debts.size() - 1) 
                os << ", ";
        }
    } else 
        os << "No debts";
    os << "]" << endl;
    return os;
}
