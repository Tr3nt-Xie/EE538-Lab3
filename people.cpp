#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

class Person {
public:
    Person(const std::string& name, int age) : name(name), age(age) {}
    std::string getName() const { return name; }
    int getAge() const { return age; }
    virtual void displayInfo(std::ostream& out) const = 0;
    virtual void introduce(std::ostream& out) const {
        out << "I am a person. My name is " << getName() << ".\n";
    }
    virtual ~Person() = default;

private:
    std::string name;
    int age;
};

class Student : public Person {
public:
    Student(const std::string& name, int age,
            const std::string& studentID, double gpa)
        : Person(name, age), studentID(studentID), gpa(gpa) {}

    void displayInfo(std::ostream& out) const override {
        out << "Student: " << getName() << ", Age: " << getAge()
            << ", ID: " << studentID << ", GPA: "
            << std::fixed << std::setprecision(1) << gpa << '\n';
    }

    void introduce(std::ostream& out) const override {
        out << "I am a student. My name is " << getName() << ".\n";
    }

private:
    std::string studentID;
    double gpa;
};

class Teacher : public Person {
public:
    Teacher(const std::string& name, int age,
            const std::string& subject, int yearsOfExperience)
        : Person(name, age), subject(subject),
          yearsOfExperience(yearsOfExperience) {}

    void displayInfo(std::ostream& out) const override {
        out << "Teacher: " << getName() << ", Age: " << getAge()
            << ", Subject: " << subject << ", Experience: "
            << yearsOfExperience << " years\n";
    }

    void introduce(std::ostream& out) const override {
        out << "I am a teacher. My name is " << getName() << ".\n";
    }

private:
    std::string subject;
    int yearsOfExperience;
};

int main() {
    int n = 0;
    std::cin >> n;

    std::vector<Person*> people;
    for (int i = 0; i < n; ++i) {
        std::string role, name;
        int age = 0;
        std::cin >> role >> name >> age;
        if (role == "Student") {
            std::string studentID;
            double gpa = 0.0;
            std::cin >> studentID >> gpa;
            people.push_back(new Student(name, age, studentID, gpa));
        } else {
            std::string subject;
            int years = 0;
            std::cin >> subject >> years;
            people.push_back(new Teacher(name, age, subject, years));
        }
    }

    // One traversal: virtual dispatch only, no role tests or downcasts.
    for (const Person* p : people) {
        p->displayInfo(std::cout);
        p->introduce(std::cout);
    }

    for (Person* p : people) {
        delete p;
    }
    return 0;
}
