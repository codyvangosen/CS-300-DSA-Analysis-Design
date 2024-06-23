//Cody VanGosen, CS 300 DSA: Analysis & Design, 06/22/2024
//Version 1.1

/* This program prompts a user to input the file name of a .csv
* course file. The user can then display the avaiable courses as well
* as display the prequisites that a course might require.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <limits> // For numeric_limits

using namespace std;

// Structure to represent a course
struct Course {
    string courseNumber; // Course number (e.g., CSCI100)
    string name; // Course name (e.g., Introduction to Computer Science)
    vector<string> prerequisites; // List of prerequisite course numbers
};

// Function to load course data from a file
map<string, Course> loadDataFromFile(string filename) {
    map<string, Course> courses; // Map to store courses with courseNumber as key
    ifstream file(filename); // Input file stream to read the file
    string line; // Variable to store each line read from the file

    // Check if the file opened successfully
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return courses;
    }

    // Read the file line by line
    while (getline(file, line)) {
        stringstream ss(line); // String stream to parse the line
        string courseNumber, name, prereq; // Variables to store course details
        getline(ss, courseNumber, ','); // Get course number
        getline(ss, name, ','); // Get course name
        Course course; // Create a new Course object
        course.courseNumber = courseNumber;
        course.name = name;

        // Read prerequisites, if any
        while (getline(ss, prereq, ',')) {
            course.prerequisites.push_back(prereq); // Add each prerequisite to the course
        }

        courses[courseNumber] = course; // Add the course to the map
    }

    file.close(); // Close the file
    return courses; // Return the map of courses
}

// Function to print the list of courses
void printCourseList(map<string, Course>& courses) {
    vector<string> courseNumbers; // Vector to store course numbers for sorting

    // Collect all course numbers
    for (const auto& pair : courses) {
        courseNumbers.push_back(pair.first);
    }

    // Sort the course numbers alphabetically
    sort(courseNumbers.begin(), courseNumbers.end());

    // Print each course in the sorted order
    for (const auto& courseNumber : courseNumbers) {
        cout << courseNumber << ", " << courses[courseNumber].name << endl;
    }
}

// Function to print information about a specific course
void printCourse(map<string, Course>& courses, string courseNumber) {
    // Convert courseNumber to uppercase for case-insensitive comparison
    transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);

    // Check if the course exists in the map
    if (courses.find(courseNumber) != courses.end()) {
        Course course = courses[courseNumber]; // Get the course from the map
        cout << course.courseNumber << ", " << course.name << endl; // Print course number and name
        cout << "Prerequisites: ";

        // Print prerequisites, if any
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1) {
                cout << ", "; // Print comma between prerequisites
            }
        }
        cout << endl;
    }
    else {
        cout << "Course not found." << endl; // Print error if course is not found
    }
}

// Function to safely read an integer input from the user
int readInteger() {
    int number;
    while (true) {
        cin >> number;
        if (cin.fail()) {
            // If input is not an integer, clear the error flag and ignore the invalid input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer: ";
        }
        else {
            // Valid integer input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return number;
        }
    }
}

// Function to clear the courses data
void clearCourses(map<string, Course>& courses) {
    courses.clear(); // Clear the map of courses
    cout << "Courses data cleared." << endl;
}

int main() {
    map<string, Course> courses; // Map to store the loaded courses
    int choice; // Variable to store user's menu choice
    string filename; // Variable to store the filename
    string courseNumber; // Variable to store the course number for querying

    cout << "Welcome to the course planner." << endl;

    // Loop to display the menu and process user input
    while (true) {
        cout << "\n1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";

        choice = readInteger(); // Read and validate user's menu choice

        switch (choice) {
        case 1:
            // Option 1: Load course data from a file
            cout << "Enter the file name: ";
            cin >> filename; // Read the filename from user
            courses = loadDataFromFile(filename); // Load the data into courses map
            cout << "Loading data from " << filename << "..." << endl;
            if (!courses.empty()) {
                cout << "Data loaded successfully!" << endl;
            }
            else {
                cout << "Failed to load data. Please check the file and try again." << endl;
            }
            break;
        case 2:
            // Option 2: Print the course list
            if (!courses.empty()) {
                cout << "Here is a sample schedule:\n" << endl;
                printCourseList(courses); // Print the list of courses
            }
            else {
                cout << "No data loaded. Please load data first." << endl;
            }
            break;
        case 3:
            // Option 3: Print information about a specific course
            if (!courses.empty()) {
                cout << "What course do you want to know about? ";
                cin >> courseNumber; // Read the course number from user
                printCourse(courses, courseNumber); // Print course information
            }
            else {
                cout << "No data loaded. Please load data first." << endl;
            }
            break;
        case 9:
            // Option 9: Exit the program
            cout << "Thank you for using the course planner!" << endl;
            clearCourses(courses); // Clear the courses data before exiting
            return 0; // Exit the program
        default:
            // Handle invalid menu options
            cout << choice << " is not a valid option." << endl;
            break;
        }
    }

    return 0;
}
