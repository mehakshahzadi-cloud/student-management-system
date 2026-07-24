#include <iostream>
#include <algorithm>
#include <limits>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

const int subjects = 5;
string subjectName[subjects] = {"PF", "PF Lab", "DM", "AP", "Calculus"};

const int Class = 5;
string className[Class] = {"Section A", "Section B", "Section C", "Section D", "Section E"};

const int max_student = 10;

struct student
{
    int id;
    string name;
    int marks[subjects];
    float total_marks;
    float percentage;
    float gpa;
    char grade;
    string status;
};

// Function Prototypes
int validatechoice(int min, int max);
void addstudent(int &count, student studentc[Class][max_student]);
void calculateresult(int i, int j, student studentc[Class][max_student]);
void searchstudent(student studentc[Class][max_student]);
void updatestudent(student studentc[Class][max_student], int &count);
void deletestudent(student studentc[Class][max_student], int &count);
void DisplayAllstudent(student studentc[Class][max_student]);
void DisplayTopperstudents(student studentc[Class][max_student]);
void DisplayAllReports(student studentc[Class][max_student]);         // Case 7
void displayClassPassFailRatio(student studentc[Class][max_student]); // Case 8
void saveToFile(student studentc[Class][max_student], int count);
void loadFromFile(student studentc[Class][max_student], int &count);

int main()
{
    student studentc[Class][max_student];
    for (int i = 0; i < Class; i++)
    {
        for (int j = 0; j < max_student; j++)
        {
            studentc[i][j].id = 0; // Initialize all IDs to 0
        }
    }

    int count = 0;
    loadFromFile(studentc, count);

    int choice;
    do
    {
        cout << "\n========= Welcome to Student Management System =========\n\n";

        cout << left << setw(35) << "1. Add Student"
             << "2. Search Student" << endl
             << endl;

        cout << left << setw(35) << "3. Update Student"
             << "4. Delete Student" << endl
             << endl;

        cout << left << setw(35) << "5. Display All/Specific Students"
             << "6. Display Topper Students" << endl
             << endl;

        cout << left << setw(35) << "7. Display All Students Reports"
             << "8. Class Pass/Fail Ratio" << endl
             << endl;

        cout << left << setw(35) << "9. Save & Exit" << endl;

        cout << "\nEnter Choice (1-9): ";
        choice = validatechoice(1, 9);

        switch (choice)
        {
        case 1:
            addstudent(count, studentc);
            break;
        case 2:
            searchstudent(studentc);
            break;
        case 3:
            updatestudent(studentc, count);
            break;
        case 4:

            deletestudent(studentc, count);
            break;
        case 5:
            DisplayAllstudent(studentc);
            break;
        case 6:
            DisplayTopperstudents(studentc);
            break;
        case 7:
            DisplayAllReports(studentc);
            break;
        case 8:
            displayClassPassFailRatio(studentc);
            break;
        case 9:
            saveToFile(studentc, count);
            cout << "Data saved successfully!\n";
            cout << "Exiting program...\n";
            return 0;
        }
    } while (true);

    return 0;
}

int validatechoice(int min, int max)
{
    string input;
    int choice;

    while (true)
    {
        getline(cin, input); // Read the entire line

        // Check if input is empty
        if (input.empty())
        {
            cout << "Invalid input! Enter a number: ";
            continue;
        }

        // Check if all characters are digits
        bool isNumber = true;
        for (char c : input)
        {
            if (!isdigit(c))
            {
                isNumber = false;
                break;
            }
        }

        if (!isNumber)
        {
            cout << "Invalid input! Enter a valid number: ";
            continue;
        }

        // Convert string to integer
        choice = stoi(input);

        // Check if choice is within range
        if (choice < min || choice > max)
        {
            cout << "Invalid input! Enter a number between " << min << "-" << max << ": ";
            continue;
        }

        return choice; // Valid input
    }
}

string validateName()
{
    string name;
    while (true)
    {
        getline(cin, name);
        bool valid = true;

        if (name.empty())
            valid = false;

        for (char c : name)
        {
            if (!isalpha(c) && c != ' ')
            {
                valid = false;
                break;
            }
        }

        if (valid)
            return name;
        cout << "Invalid name! Use alphabets only: ";
    }
}

void calculateresult(int i, int j, student studentc[Class][max_student])
{
    studentc[i][j].total_marks = 0;
    for (int k = 0; k < subjects; k++)
    {
        studentc[i][j].total_marks += studentc[i][j].marks[k];
    }

    studentc[i][j].percentage = (studentc[i][j].total_marks / (subjects * 100)) * 100;

    if (studentc[i][j].percentage >= 85)
        studentc[i][j].gpa = 4.0;
    else if (studentc[i][j].percentage >= 80)
        studentc[i][j].gpa = 3.7;
    else if (studentc[i][j].percentage >= 75)
        studentc[i][j].gpa = 3.3;
    else if (studentc[i][j].percentage >= 70)
        studentc[i][j].gpa = 3.0;
    else if (studentc[i][j].percentage >= 65)
        studentc[i][j].gpa = 2.7;
    else if (studentc[i][j].percentage >= 60)
        studentc[i][j].gpa = 2.3;
    else if (studentc[i][j].percentage >= 50)
        studentc[i][j].gpa = 2.0;
    else if (studentc[i][j].percentage >= 40)
        studentc[i][j].gpa = 1.0;
    else if (studentc[i][j].percentage >= 33)
        studentc[i][j].gpa = 0.5;
    else
        studentc[i][j].gpa = 0.0;

    if (studentc[i][j].gpa >= 4.0)
        studentc[i][j].grade = 'A';
    else if (studentc[i][j].gpa >= 3.0)
        studentc[i][j].grade = 'B';
    else if (studentc[i][j].gpa >= 2.0)
        studentc[i][j].grade = 'C';
    else if (studentc[i][j].gpa >= 1.0)
        studentc[i][j].grade = 'D';
    else if (studentc[i][j].gpa >= 0.5)
        studentc[i][j].grade = 'E';
    else
        studentc[i][j].grade = 'F';

    studentc[i][j].status = (studentc[i][j].percentage >= 33) ? "PASS" : "FAIL";
}

void addstudent(int &count, student studentc[Class][max_student])
{
    if (count >= max_student * Class)
    {
        cout << "Record Limit Reached!\n";
        return;
    }

    int cl, stdnt;
    cout << "Select Class:\n";
    for (int i = 0; i < Class; i++)
    {
        cout << i + 1 << ". " << className[i] << endl;
    }
    cout << "Enter choice: ";

    cl = validatechoice(1, 5);
    cout << "Enter Number of Students to add (1-10): ";
    stdnt = validatechoice(1, 10);

    int classIndex = cl - 1;

    for (int s = 0; s < stdnt; s++)
    {
        // Find empty slot
        int emptySlot = -1;
        for (int k = 0; k < max_student; k++)
        {
            if (studentc[classIndex][k].id == 0)
            {
                emptySlot = k;
                break;
            }
        }

        if (emptySlot == -1)
        {
            cout << className[classIndex] << " is full!\n";

            break;
        }

        cout << "\n--- Student " << s + 1 << " in " << className[classIndex] << " ---\n";
        // Get ID
        while (true)
        {
            cout << "Enter ID (1-9999): ";
            int id = validatechoice(1, 9999);

            bool idExists = false;
            for (int i = 0; i < Class; i++)
            {
                for (int k = 0; k < max_student; k++)
                {
                    if (studentc[i][k].id == id)
                    {
                        idExists = true;
                        break;
                    }
                }
                if (idExists)
                    break;
            }

            if (!idExists)
            {
                studentc[classIndex][emptySlot].id = id;
                break;
            }
            else
            {
                cout << "ID already exists! Enter different ID.\n";
            }
        }

        cout << "Enter Name: ";

        studentc[classIndex][emptySlot].name = validateName();

        for (int k = 0; k < subjects; k++)
        {
            cout << "Enter marks for " << subjectName[k] << " (0-100): ";

            studentc[classIndex][emptySlot].marks[k] = validatechoice(0, 100);
        }

        calculateresult(classIndex, emptySlot, studentc);
        count++;
        cout << "Student added successfully!\n";
    }
}

void searchstudent(student studentc[Class][max_student])
{
    int id, cl;
    cout << "Enter Student ID to search: ";
    id = validatechoice(1, 9999);

    cout << "Enter Class (1-5, or 0 to search all classes): ";
    cl = validatechoice(0, 5);

    bool found = false;

    if (cl == 0)
    {
        for (int i = 0; i < Class; i++)
        {
            for (int j = 0; j < max_student; j++)
            {
                if (studentc[i][j].id == id)
                {
                    cout << "\nStudent Found in Class " << i + 1 << endl;
                    cout << "ID: " << studentc[i][j].id << endl;
                    cout << "Name: " << studentc[i][j].name << endl;
                    cout << "Class: " << className[i] << endl;

                    cout << "Marks:\n";
                    for (int k = 0; k < subjects; k++)
                    {
                        cout << subjectName[k] << ": " << studentc[i][j].marks[k] << endl;
                    }

                    cout << "\nTotal Marks: " << studentc[i][j].total_marks << endl;
                    cout << "Percentage: " << fixed << setprecision(2) << studentc[i][j].percentage << "%" << endl;
                    cout << "GPA: " << studentc[i][j].gpa << endl;
                    cout << "Grade: " << studentc[i][j].grade << endl;
                    cout << "Status: " << studentc[i][j].status << endl;
                    found = true;
                }
            }
        }
    }
    else
    {
        int classIndex = cl - 1;
        for (int j = 0; j < max_student; j++)
        {
            if (studentc[classIndex][j].id == id)
            {
                cout << "\nStudent Found\n";
                cout << "ID: " << studentc[classIndex][j].id << endl;
                cout << "Name: " << studentc[classIndex][j].name << endl;
                cout << "Class: " << className[classIndex] << endl;

                cout << "Marks:\n";
                for (int k = 0; k < subjects; k++)
                {
                    cout << subjectName[k] << ": " << studentc[classIndex][j].marks[k] << endl;
                }

                cout << "\nTotal Marks: " << studentc[classIndex][j].total_marks << endl;
                cout << "Percentage: " << fixed << setprecision(2) << studentc[classIndex][j].percentage << "%" << endl;
                cout << "GPA: " << studentc[classIndex][j].gpa << endl;
                cout << "Grade: " << studentc[classIndex][j].grade << endl;
                cout << "Status: " << studentc[classIndex][j].status << endl;
                found = true;
                break;
            }
        }
    }

    if (!found)
    {
        cout << "Student not found!\n";
    }
}

void updatestudent(student studentc[Class][max_student], int &count)
{
    int id, cl;
    cout << "Enter Student ID to update: ";
    id = validatechoice(1, 9999);

    cout << "Enter Class (1-5): ";
    cl = validatechoice(1, 5);

    int classIndex = cl - 1;
    bool found = false;

    for (int j = 0; j < max_student; j++)
    {
        if (studentc[classIndex][j].id == id)
        {
            found = true;
            cout << "\nCurrent Details:\n";
            cout << "Name: " << studentc[classIndex][j].name << endl;
            cout << "Enter new Name: ";
            cin.ignore();
            studentc[classIndex][j].name = validateName();

            cout << "Enter new marks (0-100) for each subject:\n";
            for (int k = 0; k < subjects; k++)
            {
                cout << subjectName[k] << ": ";

                studentc[classIndex][j].marks[k] = validatechoice(0, 100);
            }

            calculateresult(classIndex, j, studentc);
            cout << "Student updated successfully!\n";
            break;
        }
    }

    if (!found)
    {
        cout << "Student not found!\n";
    }
}

void deletestudent(student studentc[Class][max_student], int &count)
{

    int id, cl;
    cout << "Enter Student ID to delete: ";
    id = validatechoice(1, 9999);

    cout << "Enter Class (1-5): ";
    cl = validatechoice(1, 5);

    int classIndex = cl - 1;
    bool found = false;

    for (int j = 0; j < max_student; j++)
    {
        if (studentc[classIndex][j].id == id)
        {
            found = true;
            count--;

            // Clear the record
            studentc[classIndex][j].id = 0;
            studentc[classIndex][j].name = "";
            for (int k = 0; k < subjects; k++)
            {
                studentc[classIndex][j].marks[k] = 0;
            }
            studentc[classIndex][j].total_marks = 0;
            studentc[classIndex][j].percentage = 0;
            studentc[classIndex][j].gpa = 0;
            studentc[classIndex][j].grade = ' ';
            studentc[classIndex][j].status = "";

            cout << "Student deleted successfully!\n";
            break;
        }
    }

    if (!found)
    {
        cout << "Student not found!\n";
    }
}

void DisplayAllstudent(student studentc[Class][max_student])
{
    int option;
    cout << "1. Display All Students\n";
    cout << "2. Display Specific Class\n";
    cout << "Enter option: ";
    option = validatechoice(1, 2);

    if (option == 1)
    {
        for (int i = 0; i < Class; i++)
        {
            bool classHasStudents = false;
            for (int j = 0; j < max_student; j++)
            {
                if (studentc[i][j].id != 0)
                {
                    if (!classHasStudents)
                    {
                        cout << "Class: " << className[i];

                        classHasStudents = true;
                    }
                    cout << "ID: " << studentc[i][j].id << " | Name: " << studentc[i][j].name;
                    cout << " | Marks: ";
                    for (int k = 0; k < subjects; k++)
                    {
                        cout << subjectName[k] << ":" << studentc[i][j].marks[k] << " ";
                    }

                    cout << "| Total: " << studentc[i][j].total_marks;
                    cout << " | %: " << fixed << setprecision(2) << studentc[i][j].percentage << "%";
                    cout << " | Status: " << studentc[i][j].status << endl;
                }
            }
            if (!classHasStudents)
            {
                cout << "\n=== " << className[i] << " ===\n";

                cout << "No students\n";
            }
        }
    }
    else
    {
        int cl;
        cout << "Enter Class (1-5): ";
        cl = validatechoice(1, 5);

        int classIndex = cl - 1;
        bool hasStudents = false;

        cout << "\n=== " << className[classIndex] << " STUDENTS ===\n";

        for (int j = 0; j < max_student; j++)
        {
            if (studentc[classIndex][j].id != 0)
            {
                hasStudents = true;
                cout << "ID: " << studentc[classIndex][j].id << " | Name: " << studentc[classIndex][j].name;
                cout << " | Marks: ";
                for (int k = 0; k < subjects; k++)
                {
                    cout << studentc[classIndex][j].marks[k] << " ";
                }
                cout << "| Total: " << studentc[classIndex][j].total_marks;
                cout << " | %: " << fixed << setprecision(2) << studentc[classIndex][j].percentage << "%";
                cout << " | Status: " << studentc[classIndex][j].status << endl;
            }
        }

        if (!hasStudents)
        {
            cout << "No students in this class\n";
        }
    }
}

void DisplayTopperstudents(student studentc[Class][max_student])
{
    int option;
    cout << "1. Display Toppers of All Classes\n";
    cout << "2. Display Topper of Specific Class\n";
    cout << "Enter option: ";
    option = validatechoice(1, 2);

    if (option == 1)
    {
        for (int i = 0; i < Class; i++)
        {
            float maxPercentage = -1;
            int topIndex = -1;

            for (int j = 0; j < max_student; j++)
            {
                if (studentc[i][j].id != 0 && studentc[i][j].percentage > maxPercentage)
                {
                    maxPercentage = studentc[i][j].percentage;
                    topIndex = j;
                }
            }

            cout << "\n=== " << className[i] << " TOPPER ===\n";
            if (topIndex != -1)
            {
                cout << "Name: " << studentc[i][topIndex].name << endl;
                cout << "ID: " << studentc[i][topIndex].id << endl;
                cout << "Percentage: " << fixed << setprecision(2) << studentc[i][topIndex].percentage << "%" << endl;
                cout << "GPA: " << studentc[i][topIndex].gpa << endl;
                cout << "Grade: " << studentc[i][topIndex].grade << endl;
                cout << "Status: " << studentc[i][topIndex].status << endl;
            }
            else
            {
                cout << "No students\n";
            }
        }
    }
    else
    {
        int cl;
        cout << "Enter Class (1-5): ";
        cl = validatechoice(1, 5);

        int classIndex = cl - 1;
        float maxPercentage = -1;
        int topIndex = -1;

        for (int j = 0; j < max_student; j++)
        {
            if (studentc[classIndex][j].id != 0 && studentc[classIndex][j].percentage > maxPercentage)
            {
                maxPercentage = studentc[classIndex][j].percentage;
                topIndex = j;
            }
        }

        cout << "\n=== " << className[classIndex] << " TOPPER ===\n";

        if (topIndex != -1)
        {
            cout << "Name: " << studentc[classIndex][topIndex].name << endl;
            cout << "ID: " << studentc[classIndex][topIndex].id << endl;
            cout << "Percentage: " << fixed << setprecision(2) << studentc[classIndex][topIndex].percentage << "%" << endl;
            cout << "GPA: " << studentc[classIndex][topIndex].gpa << endl;
            cout << "Grade: " << studentc[classIndex][topIndex].grade << endl;
            cout << "Status: " << studentc[classIndex][topIndex].status << endl;
        }
        else
        {
            cout << "No students in this class\n";
        }
    }
}

// Case 7: Display All Students Reports
void DisplayAllReports(student studentc[Class][max_student])
{
    cout << "\n============= ALL STUDENTS REPORTS =============\n";

    bool anyRecords = false;
    int totalStudents = 0;

    for (int i = 0; i < Class; i++)
    {
        bool classHasStudents = false;
        int classStudentCount = 0;

        for (int j = 0; j < max_student; j++)
        {
            if (studentc[i][j].id != 0)
            {
                if (!classHasStudents)
                {
                    cout << "\n--------------- " << className[i] << " ---------------\n";

                    classHasStudents = true;
                }

                anyRecords = true;
                classStudentCount++;
                totalStudents++;

                student s = studentc[i][j];

                cout << "\nStudent " << classStudentCount << ":\n";
                cout << "  ID: " << s.id << endl;
                cout << "  Name: " << s.name << endl;
                cout << className[i] << ": " << endl;

                cout << "  Marks:\n";
                for (int k = 0; k < subjects; k++)
                {
                    cout << "   " << subjectName[k] << ": " << s.marks[k] << endl;
                }

                cout << endl;

                cout << "  Total Marks: " << s.total_marks << "/" << (subjects * 100) << endl;
                cout << "  Percentage: " << fixed << setprecision(2) << s.percentage << "%" << endl;
                cout << "  GPA: " << s.gpa << endl;
                cout << "  Grade: " << s.grade << endl;
                cout << "  Status: " << s.status << endl;
                cout << "  ---------------------------------\n";
            }
        }

        if (!classHasStudents)
        {
            cout << "\n--------------- " << className[i] << " ---------------\n";

            cout << "No student records found.\n";
        }
    }

    if (!anyRecords)
    {
        cout << "\nNo student data available in the system.\n";
    }
    else
    {
        cout << "\n============================================\n";
        cout << "TOTAL STUDENTS: " << totalStudents << endl;
        cout << "============================================\n";
    }
}

// Case 8: Class Pass/Fail Ratio
void displayClassPassFailRatio(student studentc[Class][max_student])
{
    int cl;
    cout << "Enter Class to check Pass/Fail ratio (1-5): ";
    cl = validatechoice(1, 5);

    int classIndex = cl - 1;
    int totalStudents = 0;
    int passCount = 0;
    int failCount = 0;

    // Count students
    for (int j = 0; j < max_student; j++)
    {
        if (studentc[classIndex][j].id != 0)
        {
            totalStudents++;
            if (studentc[classIndex][j].status == "PASS")
            {
                passCount++;
            }
            else
            {
                failCount++;
            }
        }
    }

    cout << "\n======== " << className[classIndex] << " PASS/FAIL RATIO ========\n";

    if (totalStudents == 0)
    {
        cout << "No students found in " << className[classIndex] << endl;

        return;
    }

    // Calculate percentages
    float passPercentage = (float)passCount / totalStudents * 100;
    float failPercentage = (float)failCount / totalStudents * 100;

    // Display statistics
    cout << "Total Students: " << totalStudents << endl;
    cout << "Pass Students: " << passCount << endl;
    cout << "Fail Students: " << failCount << endl;
    cout << "------------------------------------\n";
    cout << "Pass Percentage: " << fixed << setprecision(2) << passPercentage << "%" << endl;
    cout << "Fail Percentage: " << fixed << setprecision(2) << failPercentage << "%" << endl;
    cout << "------------------------------------\n";

    // Analysis
    cout << "------------------------------------\n";
    cout << "Analysis:\n";
    if (passPercentage == 100)
    {
        cout << "Excellent! All students passed!\n";
    }
    else if (passPercentage >= 80)
    {
        cout << "Very Good performance!\n";
    }
    else if (passPercentage >= 60)
    {
        cout << "Good performance!\n";
    }
    else if (passPercentage >= 40)
    {
        cout << "Average performance - needs improvement\n";
    }
    else if (passPercentage >= 20)
    {
        cout << "Poor performance - Needs attention\n";
    }
    else
    {
        cout << "Critical - Immediate action required!\n";
    }

    // Student-wise status
    cout << "\nStudent-wise Status:\n";
    cout << "ID\tName\t\t\tStatus\n";
    cout << "------------------------------------\n";

    for (int j = 0; j < max_student; j++)
    {
        if (studentc[classIndex][j].id != 0)
        {
            student s = studentc[classIndex][j];
            cout << s.id << "\t" << left << setw(20) << s.name << s.status << endl;
        }
    }
    cout << "====================================\n";
}

// Save data to file
void saveToFile(student studentc[Class][max_student], int count)
{
    ofstream outFile("students.txt");

    if (!outFile)
    {
        cout << "Error creating file!\n";
        return;
    }

    outFile << count << endl;

    for (int i = 0; i < Class; i++)
    {
        for (int j = 0; j < max_student; j++)
        {
            if (studentc[i][j].id != 0)
            {
                outFile << i << "|" << j << "|";
                outFile << studentc[i][j].id << "|";
                outFile << studentc[i][j].name << "|";

                for (int k = 0; k < subjects; k++)
                {
                    outFile << studentc[i][j].marks[k] << " ";
                }

                outFile << "|"
                        << studentc[i][j].total_marks << "|"
                        << studentc[i][j].percentage << "|"
                        << studentc[i][j].gpa << "|"
                        << studentc[i][j].grade << "|"
                        << studentc[i][j].status << endl;
            }
        }
    }
    outFile.close();
}

// Load data from file
void loadFromFile(student studentc[Class][max_student], int &count)
{
    ifstream inFile("students.txt");

    if (!inFile)
        return;

    inFile >> count;
    inFile.ignore();

    int loadedCount = 0;

    while (loadedCount < count && inFile.good())
    {
        int i, j;
        char sep;

        inFile >> i >> sep >> j >> sep;
        inFile >> studentc[i][j].id >> sep;

        getline(inFile, studentc[i][j].name, '|');

        for (int k = 0; k < subjects; k++)
        {
            inFile >> studentc[i][j].marks[k];
        }

        inFile >> sep;
        inFile >> studentc[i][j].total_marks >> sep;
        inFile >> studentc[i][j].percentage >> sep;
        inFile >> studentc[i][j].gpa >> sep;
        inFile >> studentc[i][j].grade >> sep;
        inFile >> studentc[i][j].status;

        inFile.ignore(numeric_limits<streamsize>::max(), '\n');
        loadedCount++;
    }

    inFile.close();
    cout << "Previous data loaded successfully! (" << loadedCount << " students)\n";
}