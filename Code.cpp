#include <iostream>
#include <cstring>
#include <fstream>
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
    char username[20];
    char password[20];

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
