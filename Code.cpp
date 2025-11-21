#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <windows.h>
using namespace std;

struct Student{
    char rollNo[20];
    char name[50];
    char dept[50];
    int noOfSubs;
    int marks[10];
    float average;
    char grade;
};

bool rollExists(Student* students, int count, const char roll[]){
    for(int i = 0; i < count; i++){
        if(strcmp(students[i].rollNo, roll) == 0){
        return true;
    }
    }
    return false;
}

char calcGrade(float average){
    if(average >= 85) return 'A';
    else if(average >= 70) return 'B';
    else if(average >= 60) return 'C';
    else if(average >= 50) return 'D';
    else return 'F';
}

void addStudent(Student* students, int &count, int size){
    if(count == size){
        cout << "No more space!";
        return;
    }

    char tempRollNo[20];
    
    cout << "Enter Roll Number: " << endl;
    cin >> ws;
    cin.getline(tempRollNo, 20);

    if(rollExists(students, count, tempRollNo)){
        cout << "Roll Number already exists!" << endl;
        return;
    }

    strcpy(students[count].rollNo, tempRollNo);

    cout << "Enter name: " << endl;
    cin >> ws;
    cin.getline(students[count].name, 50);

    cout << "Enter department: " << endl;
    cin >> ws;
    cin.getline(students[count].dept, 50);

    cout << "Enter number of subjects: " << endl;
    cin >> students[count].noOfSubs;

    for(int i = 0; i < students[count].noOfSubs; i++){
        cout << "Enter marks for subject " << i + 1 << ": " << endl;
        cin >> students[count].marks[i];
        if(students[count].marks[i] < 0 || students[count].marks[i] > 100){
            cout << "Enter valid marks(0-100)!";
            return;
        }
    }

    float sum = 0;

    for(int i = 0; i < students[count].noOfSubs; i++){
        sum = sum + students[count].marks[i];
    }

    students[count].average = sum / students[count].noOfSubs;

    students[count].grade = calcGrade(students[count].average);

    count++;

    cout << "Student added successfully!" << endl;
}

void displayStudents(Student* students, int count){
    if(count == 0){
        cout << "No student records to display." << endl;
        return;
    }

    cout << "\n---------------------------------------" << endl;
    cout << "            STUDENT RECORDS            " << endl;
    cout << "---------------------------------------" << endl;

    for(int i = 0; i < count; i++){
        cout << "STUDENT " << i + 1 << endl;
        cout << "Roll Number: " << students[i].rollNo << endl;
        cout << "Name: " << students[i].name << endl;
        cout << "Department: " << students[i].dept << endl;
        
        for(int j = 0; j < students[i].noOfSubs; j++){
            cout << "Marks " << j + 1 << ": " << students[i].marks[j] << endl;
        }

        cout << "Average: " << students[i].average << endl;
        cout << "Grade: " << students[i].grade << endl;

    }
   

    cout << "\n---------------------------------------" << endl;
}
 void saveToFile(Student* students, int count, const char* filename) 
    {
        ofstream fout(filename);
        if (!fout) 
        {
            cout << "Error opening file for writing!" << endl;
            return;
        }
        fout << count << endl;  

        for (int i = 0; i < count; i++) 
        {
            fout << students[i].rollNo << endl;
            fout << students[i].name << endl;
            fout << students[i].dept << endl;
            fout << students[i].noOfSubs << endl;

            for (int j = 0; j < students[i].noOfSubs; j++)
             {
            fout << students[i].marks[j] << " ";
            }
            fout << endl;

        fout << students[i].average << endl;
        fout << students[i].grade << endl;
    }
    fout.close();
    cout << "All student records saved successfully to file!" << endl;
}
void loadFromFile(Student* students, int &count, const char* filename)
 {
    ifstream fin(filename);
    if (!fin)
     {
        cout << "File not found or could not be opened!" << endl;
        return;
    }

    fin >> count ;
    fin >> ws;
 

    for (int i = 0; i < count; i++) {
        fin.getline(students[i].rollNo, 20);
        fin.getline(students[i].name, 50);
        fin.getline(students[i].dept, 50);
        fin >> students[i].noOfSubs;

        for (int j = 0; j < students[i].noOfSubs; j++) {
            fin >> students[i].marks[j];
        }

        fin >> students[i].average;
        fin >> students[i].grade;
        fin >> ws;
    }
    fin.close();
    cout << "Student records loaded successfully from file!" << endl;
}
struct DepartmentStats
 {
    char dept[50];
    int studentCount;
    float totalAverage;
    float deptAverage;
    int gradeA, gradeB, gradeC, gradeD, gradeF;

    DepartmentStats() 
    {
        dept[0] = '\0';
        studentCount = 0;
        totalAverage = deptAverage = 0;
        gradeA = gradeB = gradeC = gradeD = gradeF = 0;
    }
};

int getDepartmentStats(Student* students, int count, DepartmentStats* stats, int maxDepts) {
    if (count == 0) return 0;

    int deptCount = 0;

    for (int i = 0; i < count; i++)
     {
        int index = -1;
        for (int j = 0; j < deptCount; j++) {
            if (strcmp(students[i].dept, stats[j].dept) == 0) 
            {
                index = j;
                break;
            }
        }
        if (index == -1 && deptCount < maxDepts)
         {
            index = deptCount++;
            strcpy(stats[index].dept, students[i].dept);
        }
        stats[index].studentCount++;
        stats[index].totalAverage += students[i].average;

        switch (students[i].grade)
         {
            case 'A': stats[index].gradeA++; break;
            case 'B': stats[index].gradeB++; break;
            case 'C': stats[index].gradeC++; break;
            case 'D': stats[index].gradeD++; break;
            case 'F': stats[index].gradeF++; break;
        }
    }
    for (int i = 0; i < deptCount; i++) {
        if (stats[i].studentCount > 0)
            stats[i].deptAverage = stats[i].totalAverage / stats[i].studentCount;
    }

    return deptCount;
}
void searchStudentbyRollNo(Student* students, int count) {
    char rollNum[20];
    cout << "Enter the roll number to search with: ";
    cin >> ws;
    cin.getline(rollNum, 20);

    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].rollNo, rollNum) == 0) {
            cout << "Student found!" << endl;
            cout << "Name: " << students[i].name << endl;
            cout << "Department: " << students[i].dept << endl;
            cout << "Average: " << students[i].average << endl;
            cout << "Grade: " << students[i].grade << endl;
            return;
        }
    }
    cout << "Student not found!" << endl;
}
void updateStudentRecord(Student* students, int &count) {
    char roll[20];
    cout << "Enter roll number to update: ";
    cin >> ws;
    cin.getline(roll, 20);

    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].rollNo, roll) == 0) {
            cout << "Enter the new name: ";
            cin.getline(students[i].name, 50);
            cout << "Enter the new department: ";
            cin.getline(students[i].dept, 50);

            cout << "Enter number of subjects: ";
            cin >> students[i].noOfSubs;

            int sum = 0;
            for (int j = 0; j < students[i].noOfSubs; j++) {
                do {
                    cout << "Enter marks for subject " << j + 1 << " (0-100): ";
                    cin >> students[i].marks[j];
                    if (students[i].marks[j] < 0 || students[i].marks[j] > 100) {
                        cout << "Invalid marks! Please enter a value between 0 and 100." << endl;
                    }
                } while (students[i].marks[j] < 0 || students[i].marks[j] > 100);
                sum += students[i].marks[j];
            }

            students[i].average = (float)sum / students[i].noOfSubs;
            students[i].grade = calcGrade(students[i].average);

            cout << "Record updated successfully!" << endl;
            return;
        }
    }
    cout << "Student not found!" << endl;
}
void deleteStudentRecord(Student* students, int &count) {
    if (count == 0) {
        cout << "No records to delete." << endl;
        return;
    }

    char roll[20];
    cout << "Enter roll number to delete: ";
    cin >> ws;
    cin.getline(roll, 20);

    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].rollNo, roll) == 0) {
            for (int j = i; j < count - 1; j++) {
                students[j] = students[j + 1];
            }
            count--;
            cout << "Student record deleted successfully!" << endl;
            return;
        }
    }

    cout << "Student not found!" << endl;
}

void displayTopStudent(Student* students, int count){
    if(count == 0){
        cout << "No records available." << endl;
        return;
    }

    float highestavg = students[0].average;

    for(int i = 0; i < count; i++){
        if(students[i].average > highestavg){
            highestavg = students[i].average;
        }
    }
    
    cout << "\n---------------------------------------" << endl;
    cout << "              TOP STUDENTS              " << endl;
    cout << "---------------------------------------" << endl;
    for(int i = 0; i < count; i++){
        if(students[i].average == highestavg){
            cout << "Roll Number: " << students[i].rollNo << endl;
        cout << "Name: " << students[i].name << endl;
        cout << "Department: " << students[i].dept << endl;
        
        for(int j = 0; j < students[i].noOfSubs; j++){
            cout << "Marks " << j + 1 << ": " << students[i].marks[j] << endl;
        }

        cout << "Average: " << students[i].average << endl;
        cout << "Grade: " << students[i].grade << endl;
        cout << "\n---------------------------------------" << endl;
        }
    }
}

void adminSignUp(){
    char username[20], password[20];

    cout << "\n-------CREATE ADMIN ACCOUNT-------";

    cout << "Enter Admin Username: " << endl;
    cin >> ws;
    cin.getline(username, 20);

    cout << "Enter Password: " << endl;
    cin >> ws;
    cin.getline(password, 20);

    ofstream out("admin.txt");
    out << username << endl << password;
    out.close();

    cout << "Account created successfully!" << endl;
}

bool adminLogin(){
    char inputUser[20], inputPass[20], savedUser[20], savedPass[20];
     
    ifstream in("admin.txt");

    if(!in){
        cout << "No admin account found!" << endl;
        return false;
    }

    in.getline(savedUser, 20);
    in.getline(savedPass, 20);
    in.close();

    cout << "Enter Username: " << endl;
    cin >> ws;
    cin.getline(inputUser, 20);

    cout << "Enter Password: " << endl;
    cin >> ws;
    cin.getline(inputPass, 20);

    if(strcmp(inputUser, savedUser) == 0 && strcmp(inputPass, savedPass) == 0){
        cout << "Login Successful!";
        return true;
    } else{
        cout << "Incorrect Username or Password!";
        return false;
    }
}

oid studentSignUp(){
    char rollNo[20], password[20];

    cout << "\n-------CREATE STUDENT  ACCOUNT-------";

    cout << "Enter Student Roll No: " << endl;
    cin >> ws;
    cin.getline(rollNo, 20);

    cout << "Enter Password: " << endl;
    cin >> ws;
    cin.getline(password, 20);

    ofstream out("student.txt");
    out << rollNo << endl << password;
    out.close();

    cout << "Account created successfully!" << endl;
}

void viewOwnRecord(Student* students, int count, const char roll[]){
    bool found = false;

    for(int i = 0; i < count; i++){
        if(strcmp(students[i].rollNo, roll) == 0){
            found = true;

            cout << "\n--------- YOUR RECORD ---------\n";
            cout << "Roll Number: " << students[i].rollNo << endl;
            cout << "Name: " << students[i].name << endl;
            cout << "Department: " << students[i].dept << endl;
            
            for(int j = 0; j < students[i].noOfSubs; j++){
                cout << "Marks " << j + 1 << ": " << students[i].marks[j] << endl;
            }

            cout << "Average: " << students[i].average << endl;
            cout << "Grade: " << students[i].grade << endl;
            cout << "--------------------------------\n";

            break;
        }
    }

    if(!found){
        cout << "\nNo record found for this roll number.\n";
    }
}

bool studentLogin(Student* students, int count){
    char inputRoll[20], inputPass[20];
    char savedRoll[20], savedPass[20];

    ifstream in("student.txt");

    if(!in){
        cout << "No student account found! Please sign up first.\n";
        return false;
    }

    in.getline(savedRoll, 20);
    in.getline(savedPass, 20);
    in.close();

    cout << "Enter Roll No: ";
    cin >> ws;
    cin.getline(inputRoll, 20);

    cout << "Enter Password: ";
    cin >> ws;
    cin.getline(inputPass, 20);

    if(strcmp(inputRoll, savedRoll) == 0 && strcmp(inputPass, savedPass) == 0){
        cout << "\nLogin Successful!\n";

        viewOwnRecord(students, count, inputRoll);

        return true;
    }
    else{
        cout << "Incorrect Roll No or Password!\n";
        return false;
    }
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void displayEverything(Student* students, int count) {
    if (count == 0) {
        setColor(12); // Red
        cout << "No student records to display!" << endl;
        setColor(7); // Reset to white
        return;
    }

    setColor(11); // Cyan
    cout << "\n=========================================\n";
    cout << "          COMPLETE STUDENT REPORT        \n";
    cout << "=========================================\n";
    setColor(7);

    for (int i = 0; i < count; i++) {
        setColor(9); // Blue
        cout << "\nStudent #" << i + 1 << endl;
        cout << "-----------------------------------------" << endl;
        setColor(7);

        setColor(15); cout << "Roll No: "; setColor(7); cout << students[i].rollNo << endl;
        setColor(15); cout << "Name: "; setColor(7); cout << students[i].name << endl;
        setColor(15); cout << "Department: "; setColor(7); cout << students[i].dept << endl;

        cout << "Marks: ";
        for (int j = 0; j < students[i].noOfSubs; j++) {
            cout << students[i].marks[j];
            if (j < students[i].noOfSubs - 1) cout << ", ";
        }
        cout << endl;

        setColor(15); cout << "Average: "; setColor(7);
        cout << fixed << setprecision(2) << students[i].average << endl;

        switch (students[i].grade) {
            case 'A': setColor(10); break; // Green
            case 'B': setColor(11); break; // Cyan
            case 'C': setColor(14); break; // Yellow
            case 'D': setColor(13); break; // Pink
            case 'F': setColor(12); break; // Red
            default: setColor(7); break; // White
        }
        cout << "Grade: " << students[i].grade << endl;
        setColor(7); // reset
    }

    setColor(11);
    cout << "\n=========================================\n";
    cout << "          DEPARTMENT STATISTICS          \n";
    cout << "=========================================\n";
    setColor(15);

    DepartmentStats stats[50];
    int deptCount = getDepartmentStats(students, count, stats, 50);

    cout << left << setw(20) << "Department"
         << setw(15) << "Students"
         << setw(15) << "Avg Marks"
         << setw(8) << "A"
         << setw(8) << "B"
         << setw(8) << "C"
         << setw(8) << "D"
         << setw(8) << "F" << endl;

    setColor(8);
    cout << "--------------------------------------------------------------" << endl;
    setColor(7);

    for (int i = 0; i < deptCount; i++) {
        cout << left << setw(20) << stats[i].dept
             << setw(15) << stats[i].studentCount
             << setw(15) << fixed << setprecision(2) << stats[i].deptAverage
             << setw(8) << stats[i].gradeA
             << setw(8) << stats[i].gradeB
             << setw(8) << stats[i].gradeC
             << setw(8) << stats[i].gradeD
             << setw(8) << stats[i].gradeF << endl;
    }

    setColor(11);
    cout << "\n=========================================\n";
    cout << "              TOP STUDENT(S)             \n";
    cout << "=========================================\n";
    setColor(7);

    float highestAvg = students[0].average;
    for (int i = 1; i < count; i++)
        if (students[i].average > highestAvg)
            highestAvg = students[i].average;

    for (int i = 0; i < count; i++) {
        if (students[i].average == highestAvg) {
            setColor(10);
            cout << "\n⭐ Top Student ⭐" << endl;
            setColor(15); cout << "Name: "; setColor(7); cout << students[i].name << endl;
            setColor(15); cout << "Roll No: "; setColor(7); cout << students[i].rollNo << endl;
            setColor(15); cout << "Dept: "; setColor(7); cout << students[i].dept << endl;
            setColor(15); cout << "Average: "; setColor(10); cout << students[i].average << endl;
            setColor(15); cout << "Grade: "; setColor(10); cout << students[i].grade << endl;
            setColor(7);
        }
    }

    setColor(11);
    cout << "\n=========================================\n";
    setColor(7);
}
 
int main() 
{
    system("cls"); 
    setColor(11); // Cyan
    cout << "=============================================\n";
    cout << "   🎓 STUDENT RECORD MANAGEMENT SYSTEM 🎓\n";
    cout << "=============================================\n\n";
    setColor(7); 

    const char* filename = "students.txt";
    const int SIZE = 100;
    Student students[SIZE];
    int count = 0;
    bool loggedIn = false;

    int choice;
    while (true) {
        setColor(14); // Yellow
        cout << "\n1. Admin Login\n2. Admin Sign Up\n3. Exit\n";
        setColor(7);
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            if (adminLogin()) {
                loggedIn = true;
                break;
            } else {
                setColor(12);
                cout << "\nLogin failed. Try again.\n";
                setColor(7);
            }
        } else if (choice == 2) {
            adminSignUp();
        } else if (choice == 3) {
            setColor(12);
            cout << "Exiting program...\n";
            setColor(7);
            return 0;
        } else {
            setColor(12);
            cout << "Invalid option! Try again.\n";
            setColor(7);
````````````        }
    }

    loadFromFile(students, count, filename);

    do {
        setColor(11);
        cout << "\n=============================================\n";
        cout << "                MAIN MENU\n";
        cout << "=============================================\n";
        setColor(7);
        cout << "1. Add Student Record\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student by Roll No\n";
        cout << "4. Update Student Record\n";
        cout << "5. Delete Student Record\n";
        cout << "6. Display Complete Report\n";
        cout << "7. Save Records to File\n";
        cout << "8. Load Records from File\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        system("cls"); 

        switch (choice) {
            case 1:
                addStudent(students, count, SIZE);
                break;
            case 2:
                displayStudents(students, count);
                break;
            case 3:
                searchStudentbyRollNo(students, count);
                break;
            case 4:
                updateStudentRecord(students, count);
                break;
            case 5:
                deleteStudentRecord(students, count);
                break;
            case 6:
                displayEverything(students, count);
                break;
            case 7:
                saveToFile(students, count, filename);
                break;
            case 8:
                loadFromFile(students, count, filename);
                break;
            case 9:
                setColor(12);
                cout << "\nSaving and exiting program...\n";
                setColor(7);
                saveToFile(students, count, filename);
                return 0;
            default:
                setColor(12);
                cout << "Invalid choice! Please try again.\n";
                setColor(7);
        }

        setColor(8);
        cout << "\nPress any key to continue...";
        setColor(7);
        cin.ignore();
        cin.get();
        system("cls");

    } while (true);
}
