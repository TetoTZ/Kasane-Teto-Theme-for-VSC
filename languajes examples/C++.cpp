#include <iostream>
#include <vector>
#include <string>

class Student {
public:
    std::string name;
    double grade;

    Student(std::string name, double grade)
        : name(name), grade(grade) {}

    bool passed() const {
        return grade >= 60.0;
    }
};

int main() {
    const int maxStudents = 10;
    std::vector<Student> students;

    // Test comment
    std::cout << "Enter grade: " << std::endl;

    double grade = 95.5;

    if (grade >= 60.0) {
        std::cout << "Passed" << std::endl;
    } else {
        std::cout << "Failed" << std::endl;
    }

    return 0;
}