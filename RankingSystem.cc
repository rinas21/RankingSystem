#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class Student {
public:
    std::string name;
    int marks[3]; // Assuming three subjects for simplicity
    int totalMarks;
    int schoolRank;
    int classRank;

    Student(const std::string& _name, int _marks[]) : name(_name) {
        for (int i = 0; i < 3; ++i) {
            marks[i] = _marks[i];
        }
        totalMarks = marks[0] + marks[1] + marks[2];
    }
};

class Class {
public:
    std::vector<Student> students;

    void addStudent(const Student& student) {
        students.push_back(student);
    }
};

class Stream {
public:
    std::vector<Class> classes;

    void addClass(const Class& _class) {
        classes.push_back(_class);
    }
};

void calculateRanks(Stream& stream) {
    std::vector<Student*> allStudents;

    for (Class& _class : stream.classes) {
        for (Student& student : _class.students) {
            allStudents.push_back(&student);
        }
    }

    std::sort(allStudents.begin(), allStudents.end(), [](Student* a, Student* b) {
        return a->totalMarks > b->totalMarks;
    });

    for (size_t i = 0; i < allStudents.size(); ++i) {
        allStudents[i]->schoolRank = i + 1;
    }

    for (Class& _class : stream.classes) {
        std::sort(_class.students.begin(), _class.students.end(), [](Student& a, Student& b) {
            return a.totalMarks > b.totalMarks;
        });

        for (size_t i = 0; i < _class.students.size(); ++i) {
            _class.students[i].classRank = i + 1;
        }
    }
}

void writeRanksToFile(const Stream& stream, const std::string& filename) {
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open the output file." << std::endl;
        return;
    }

    for (const Class& _class : stream.classes) {
        for (const Student& student : _class.students) {
            outFile << "Name: " << student.name << std::endl;
            outFile << "Total Marks: " << student.totalMarks << std::endl;
            outFile << "School Rank: " << student.schoolRank << std::endl;
            outFile << "Class Rank: " << student.classRank << std::endl;
            outFile << "---------------------------" << std::endl;
        }
    }

    outFile.close();
}

int main() {
    // Create Bio and Math streams
    Stream bioStream, mathStream;

    // Read student data from files (customize this part)
    // Example: ReadBioDataFromFile(bioStream);
    // Example: ReadMathDataFromFile(mathStream);

    // Calculate ranks
    calculateRanks(bioStream);
    calculateRanks(mathStream);

    // Write ranks to output files
    writeRanksToFile(bioStream, "BioRanks.txt");
    writeRanksToFile(mathStream, "MathRanks.txt");

    std::cout << "Ranks calculated and written to files." << std::endl;

    return 0;
}
