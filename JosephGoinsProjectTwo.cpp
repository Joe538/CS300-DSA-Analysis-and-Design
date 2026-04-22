// JosephGoinsProjectTwo.cpp
// Joseph Goins
// CS-300
// Project Two
// Due: 04/19/2026

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// This class represents a course with its name, number, and prerequisites
class Course
{
	public:
	string courseNumber;
	string courseName;
	vector<string> prerequisites;
	Course(string name, string number, vector<string> prereqs)
	{
		courseName = name;
		courseNumber = number;
		prerequisites = prereqs;
	}
};

// This function prints the welcome message
void PrintWelcomeMessage()
{
	cout << "Welcome to the course information system!" << endl;
	cout << "Please enter a file name to read course information from: " << endl;
	cout << "Avaliable files: 'CS 300 ABCU_Advising_Program_Input.csv'" << endl;
	cout << "You can also enter 'exit' to quit the program." << endl;
	cout << endl; // Print a newline for better formatting after the welcome message
}

void DisplayMenuOptions()
{
	cout << "Menu Options:" << endl;
	cout << "Option 1: Load the file data into the data structure. Note that before you can print the course information or the sorted list of courses, you must load the data into the data structure. " << endl;
	cout << "Option 2: Print an alphanumeric list of all the courses in the Computer Science department." << endl;
	cout << "Option 3: Print the course title and the prerequisites for any individual course." << endl;
	cout << "Option 9: Exit the program." << endl;
}

/* 
	* This function takes an input file stream as an argument
	* It reads the file line by line and stores each line in a vector of strings
	* It returns the vector containing all the lines from the file
*/
vector<string> GetAllFileData(ifstream& inputFile)
{
	vector<string> data; // Vector to store the lines read from the file
	string line; // Variable to hold each line read from the file
	// Read the file line by line until the end of the file is reached
	while (getline(inputFile, line))
	{
		data.push_back(line); // Add each line to the vector
	}
	return data; // Return the vector containing all the lines from the file
}

/*
	* This function takes all the lines from the file
	* It processes them into a vector of course objects
	* It does so by parsing each line, extracting the relevant information, 
	* and creating Course objects
*/
vector<Course> StoreParsedData(vector<string>& courseData, vector<Course>& courses)
{
	for (int i = 0; i < courseData.size(); ++i)
	{
		string line = courseData[i]; // Get the current line from the vector
		stringstream lineStream(line); // Create a stringstream object to parse the line
		vector<string> fields; // Vector to store the fields extracted from the line
		string temp; // Temporary variable to hold each field as it is extracted

		while (getline(lineStream, temp, ','))
		{
			fields.push_back(temp); // Add each field to the vector
		}
		// Create a Course object using the extracted fields
		if (fields.size() >= 2)
		{
			string courseNumber = fields[0];
			string courseName = fields[1];
			vector<string> prerequisites(fields.begin() + 2, fields.end());
			courses.push_back(Course(courseName, courseNumber, prerequisites));
		}
	}
	return courses; // Placeholder return statement
}
/*
	* This function prompts the user for a file name, 
	* attempts to open the specified file 
	* and reads its contents into a vector of strings.
*/
void LoadData(vector<string>& courseData, vector<Course>& courses) {
	ifstream inputFile; // Variable to hold the input file stream
	string fileName; // Variable to hold the file name input by the user
	bool fileOpened = false; // Flag to track if the file was opened successfully

	// Loop until a valid file is opened or the user chooses to exit
	while (!fileOpened)
	{
		// Prompt the user to enter a file name
		cout << "Enter file name(type 'exit' to quit): ";
		getline(cin, fileName);

		if (fileName == "exit")
		{
			cout << "Exiting the program. Goodbye!" << endl;
			return; // Exit the program
		}
		else {
			inputFile.open(fileName); // Attempt to open the specified file
			if (!inputFile.is_open()) // Check if the file was opened successfully
			{
				cout << "Error: Could not open the file '" << fileName << "'. Please check the file name and try again." << endl;
				fileOpened = false; // Set the flag to false to continue the loop
			}
			else
			{
				cout << "File '" << fileName << "' opened successfully!" << endl;
				// Read the file line by line and store the data in the vector
				courseData = GetAllFileData(inputFile);
				inputFile.close(); // Close the file after processing
				fileOpened = true; // Set the flag to true to exit the loop
			}
		}
	}

	StoreParsedData(courseData, courses);
}

int Partition(vector<Course>& courses, int low, int high) {
	int mid = low + (high - low) / 2; // Calculate the middle index
	Course pivot = courses[mid]; // Choose the middle element as the pivot
	bool isDone = false; // Flag to track when the partitioning is complete

	while (!isDone) {
		// Move the low index up until an element greater than or equal to the pivot is found
		while (courses[low].courseNumber < pivot.courseNumber) {
			low++; // Move the low index up until an element greater than or equal to the pivot is found
		}

		// Move the high index down until an element less than or equal to the pivot is found
		while (pivot.courseNumber < courses[high].courseNumber) {
			high--; // Move the high index down until an element less than or equal to the pivot is found
		}

		if (low >= high) {
			isDone = true; // If the low index is greater than or equal to the high index, the partitioning is complete
		}
		else {
			swap(courses[low], courses[high]); // Swap the elements at the low and high indices
			low++; // Move the low index up
			high--; // Move the high index down
		}
	}

	return high; // Return the index of the pivot
}

void QuickSort(vector<Course>& courses, int low, int high) {
	if (low >= high) {
		return; // Base case: if the low index is greater than or equal to the high index, return
	}

	int lowEndIndex = Partition(courses, low, high); // Partition the array and get the index of the pivot
	QuickSort(courses, low, lowEndIndex); // Recursively sort elements before the partition
	QuickSort(courses, lowEndIndex + 1, high); // Recursively sort elements after the partition
}

void PrintDataAlphanumerically(vector<Course>& courses) {
	QuickSort(courses, 0, courses.size() - 1); // Sort the courses alphanumerically using QuickSort

	for (int i = 0; i < courses.size(); ++i) {
		cout << courses[i].courseNumber << ": " << courses[i].courseName << ", "; // Print the course number and name

		if (!courses[i].prerequisites.empty()) {
			cout << "Prerequisites: ";

			for (int j = 0; j < courses[i].prerequisites.size(); ++j) {
				cout << courses[i].prerequisites[j] << " "; // Print each prerequisite
			}

			cout << endl; // Print a newline after the prerequisites
		}
	}
}

void FindCourseAndPrintData(const vector<Course>& courses, const string& courseNumber) {
	for (int i = 0; i < courses.size(); ++i) {
		if (courses[i].courseNumber == courseNumber) { // Check if the course number matches the input
			cout << "Course Title: " << courses[i].courseName; // Print the course title
			if (!courses[i].prerequisites.empty()) {
				cout << "Prerequisites: ";
				for (int j = 0; j < courses[i].prerequisites.size(); ++j) {
					cout << courses[i].prerequisites[j] << " "; // Print each prerequisite
				}
				cout << endl; // Print a newline after the prerequisites
			}
			return; // Exit the function after finding and printing the course information
		}
	}
}

int main()
{
	vector <string> courseData; // Vector to store the course data read from the file
	vector<Course> courses; // Vector to store the Course objects created from the cleaned data
	int option; // Variable to hold user input for menu options
	bool dataLoaded = false; // Flag to track if the data has been loaded successfully

	// Welcome message and prompt for file name
	PrintWelcomeMessage();

	do {
		DisplayMenuOptions(); // Function to display menu options (not implemented in the provided code)
		cout << "Enter your option: ";
		cin >> option; // Get the user's menu option input
		cout << endl; // Print a newline for better formatting

		switch (option) {
		case 1:
			if (dataLoaded) {
				cout << "Data has already been loaded. Please choose another option." << endl;
			}
			else {
				cin.ignore(); // Clear the input buffer before reading the file name
				LoadData(courseData, courses); // Call the function to load data from the file
				dataLoaded = true; // Set the flag to true after loading data
				cout << endl; // Print a success message after loading data
			}
			break;
		case 2:
			if (!dataLoaded) {
				cout << "Please load the data first (Option 1)." << endl;
			}
			else {
				cin.ignore(); // Clear the input buffer before printing the course list
				// Calls function to print an alphanumeric list of all the courses in 
				// the Computer Science department would go here
				PrintDataAlphanumerically(courses);
				cout << endl; // Print a newline for better formatting after displaying the course list
			}
			break;
		case 3:
			if (!dataLoaded) {
				cout << "Please load the data first (Option 1)." << endl;
			}
			else {
				cin.ignore(); // Clear the input buffer before prompting for course number
				// Calls function to print the course title and 
				// the prerequisites for any individual course would go here
				string courseNumber;
				cout << "Enter the course number: ";
				cin >> courseNumber;
				FindCourseAndPrintData(courses, courseNumber);
				cout << endl; // Print a newline for better formatting after displaying course information
			}
			break;
		case 9:
			cout << "Exiting the program. Goodbye!" << endl;
			break;
		}
	} while (option != 9);

	return 0; // End of the program
}