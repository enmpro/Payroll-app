#include "ManagerPages.h"
#include "AppPages.h"
// import all libraries needed ========================================================================================
#include <iostream>
#include <iomanip>
#include <Math.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdio>
#include <Windows.h>
#include <ctime>
#include <chrono>
#include <conio.h> 
#pragma warning(disable : 4996) // so that we can use local time function from ctime
#define Size 50
#undef max
using namespace std;

// this screen is for the logged in manager screen
void ManagerPages::showManagerPage() {

	system("CLS");
	changeColor(11);
	cout << "@@=================================================@@" << endl;
	cout <<  setw(28) << "Welcome " << currentUser[0] << " " << currentUser[1] << endl;
	cout << endl;
	changeColor(14);
	cout << "(1): Clock In" << endl;
	cout << "(2): Add/Edit Employee" << endl;
	cout << "(3): View Salary" << endl;
	cout << "(4): View My Employees" << endl;
	cout << "(5): Log Out" << endl;	

}


void ManagerPages::managerPageChoices() {

	system("CLS");
	
	int isFinish = 1;
	string employeeFirst = "";
	string employeeLast = "";
	double employeeHourlyRate = .0;
	string newEmpUser = "";
	string employeeTitle = "";
	string employeeUser = "", employeePass = "";
	int paidOption = 0;
	string marriedSingle = "";
	string monthOrWeekly = "";
	int weekDay = 0, monthlyPayDay = 0;
	string vv = "";
	string dummy = "";
	string line = "";
	int numOfEmployee = 0;
	string maritalString = "";
	char* maritalStr = new char[8];

	ofstream createEmployee;
	fstream employeeEdit;
	ifstream readEmployee;
	ofstream temporaryUserFile;

	createEmployee.open("users_rpa.txt", ios::app);
	employeeEdit.open("users_rpa.txt");
	readEmployee.open("users_rpa.txt");

	while (isFinish == 1) {
		userChoice = 0;
		editChoice = 0;
		line = "";
		numOfEmployee = 0;
		
		system("CLS");

		changeColor(11);
		cout << "@@=================================================@@" << endl;
		cout << setw(35) << "ADD / EDIT EMPLOYEE" << endl;
		changeColor(14);
		cout << endl;
		cout << "(1): Add New Employee" << endl;
		cout << "(2): Edit Employee" << endl;
		cout << "(3): Exit" << endl;
		cout << "Please enter a choice: ";
		cin >> userChoice;

		if (!cin) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			changeColor(12);
			cout << "Please enter a valid choice" << endl;
			changeColor(14);
			getch();
			continue;
		}

		// adding the employee algorithm
		if (userChoice == 1) {
			system("CLS");
			changeColor(11);
			cout << "@@=================================================@@" << endl;
			cout << setw(35) << "ADD EMPLOYEE" << endl;
			changeColor(14);
			cout << endl;
			cout << "First name: ";
			cin >> employeeFirst;

			cout << "Last name: ";
			cin >> employeeLast;

			employeeUser = employeeFirst + employeeLast;
			cout << "Employee Username: " << employeeUser << endl;
			cout << "Temporary Log In Password: app123" << endl;
			employeePass = "app123";

			while (true) {
				maritalString = "";
				cout << "Married or single: ";
				cin >> marriedSingle;
				strcpy(maritalStr, marriedSingle.c_str());

				for (int i = 0; i < marriedSingle.length(); i++) {

					maritalString += tolower(maritalStr[i]);

				}

				if (maritalString == "married") {
					break;
				}

				if (maritalString == "single") {
					break;
				}
				if (maritalString != "married" || maritalString != "single") {
					changeColor(12);
					cout << "Please enter valid marital status" << endl;
					changeColor(14);
				}

			}

			cout << "Employee Title: ";
			cin.ignore();
			getline(cin, employeeTitle);

			while (true) {
				cout << "Hourly rate ($ per hour): $";
				cin >> employeeHourlyRate;
				
				if (!cin) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					changeColor(12);
					cout << "Please enter a valid choice" << endl;
					changeColor(14);
					continue;
				}
				else {
					break;
				}
			}
			

			while (paidOption > 2 || paidOption < 1) {

				cout << "Weekly = 1 or Monthly = 2: ";
				cin >> paidOption;
				if (!cin || paidOption > 2 || paidOption < 1) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					changeColor(12);
					cout << "Please enter a valid choice" << endl;
					changeColor(14);
					getch();
					continue;
				}
				else {
					break;
				}

			}

			if (paidOption == 1) {
				while (weekDay > 7 || weekDay < 1) {
					cout << "Enter day this employee will get paid (monday 1 - sunday 7): ";
					cin >> weekDay;
					if (!cin || weekDay > 7 || weekDay < 1) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						changeColor(12);
						cout << "Please enter a valid choice" << endl;
						changeColor(14);
						getch();
						continue;
					}
					else {
						break;
					}
				}

			}
			else {
				while (monthlyPayDay < 1 || monthlyPayDay > 30) {
					cout << "Enter date this employee will get paid (1 - 30): ";
					cin >> monthlyPayDay;
					if (!cin || monthlyPayDay < 1 || monthlyPayDay > 30) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						changeColor(12);
						cout << "Please enter a valid choice" << endl;
						changeColor(14);
						getch();
						continue;
					}
					else {
						break;
					}
				}
			};

			if (weekDay != 0) {
				vv = weekDay;
				monthOrWeekly = "weekly";

			}
			else {
				vv = monthlyPayDay;
				monthOrWeekly = "monthly";
			};

			if (createEmployee.is_open()) { // write to the file
				// FIRST , LAST, USER , PASS, MANAGER UNDER,  MARRIED - SINGLE, TITLE, WEEK/MONTHLY, D-M, RATE,HOURS

				if (monthOrWeekly == "weekly") {

					createEmployee << employeeFirst << "," << employeeLast << "," << employeeUser << "," <<
						employeePass << "," << currentUser[0] << " " << currentUser[1] << "," << maritalString << "," << employeeTitle << "," << monthOrWeekly << ","
						<< getCurrentDay(weekDay) << "," << employeeHourlyRate << "," << "0.00" << endl;

				}


				if (monthOrWeekly == "monthly") {

					createEmployee << employeeFirst << "," << employeeLast << "," << employeeUser << "," <<
						employeePass << "," << currentUser[0] << " " << currentUser[1] << "," << maritalString << "," << employeeTitle << "," << monthOrWeekly << "," << monthlyPayDay << "," << employeeHourlyRate << "," << "0.00"
						<< endl;

				}

				system("CLS");
				changeColor(11);
				cout << "@@=================================================@@" << endl;
				cout << setw(35) << "ADD EMPLOYEE" << endl;
				changeColor(14);
				cout << endl;
				changeColor(10);
				cout << "The new employee has been successfully registered." << endl;
				changeColor(14);
				cout << "Returning to the manager menu; press any key to continue." << endl;
				getch();
				createEmployee.close();

			};

		}

		if (userChoice == 2 && editChoice == 0) { // edit employee choice
			int counter = 1;
			editChoice = 0;
			temporaryUserFile.open("edit_employee.txt");
			system("CLS");
			
			numOfEmployee = count(istreambuf_iterator<char>(readEmployee), istreambuf_iterator<char>(), '\n');

			while (editChoice < 1 || editChoice > numOfEmployee - (numOfEmployee - counter)) {
				system("CLS");
				changeColor(11);
				cout << "@@=================================================@@" << endl;
				cout << setw(35) << "EDIT EMPLOYEE" << endl;
				changeColor(14);
				cout << endl;
				
				while (getline(employeeEdit, line)) { // makes sure that the user is an employee
					vector<string> employeeInfo = commaDelimetedString(line, ',');
					string toAdd = employeeInfo.at(0) + "," + employeeInfo.at(1) + "," + employeeInfo.at(2) + "," + employeeInfo.at(3) +
						"," + employeeInfo.at(4) + "," + employeeInfo.at(5) + "," + employeeInfo.at(6) + "," + employeeInfo.at(7) + "," + employeeInfo.at(8) +
						"," + employeeInfo.at(9) + "," + employeeInfo.at(10);

					if (employeeInfo.at(4) != "M123M") {
						temporaryUserFile << toAdd << endl;;
						cout << "(" << counter << "). " << employeeInfo.at(0) << " " << employeeInfo.at(1) << endl;
						counter++;
					}

				}
				cout << endl;
				cout << "(" << numOfEmployee - (numOfEmployee - counter) << "): Exit" << endl;
				cout << "Please enter a choice: " << endl;
				
				cin >> editChoice;
				if (editChoice > numOfEmployee - (numOfEmployee - counter) || editChoice < 1) {
					changeColor(12);
					cout << "Please enter a valid choice" << endl;
					changeColor(14);
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					getch();
					editChoice = 0;
					counter = 1;
					line = "";
					employeeEdit.close();
					employeeEdit.open("users_rpa.txt");
					continue;

				}

				if (editChoice == numOfEmployee - (numOfEmployee - counter)) {

					break;

				}
				

				if (editChoice > 0 || editChoice < numOfEmployee - (numOfEmployee - counter)) {
					createEmployee.close();
					employeeEdit.close();
					readEmployee.close();
					editPage = 1;
					isFinish = 0;
					break;
					//this->editEmployeePage();
				}

			}
		}

		if (userChoice == 3) {

			isFinish = 0;

		}

		createEmployee.close();
		employeeEdit.close();
		readEmployee.close();

	};

}

void ManagerPages::viewEmployees() {

	system("CLS");
	changeColor(11);
	cout << "@@=================================================@@" << endl;
	cout << setw(35) << "VIEW EMPLOYEE(S)" << endl;
	changeColor(14);
	cout << endl;
	ifstream employeeView;
	employeeView.open("users_rpa.txt");

	if (employeeView.is_open()) {
		string data;
		int dayDetermine = 0;
		while (getline(employeeView, data)) {
			vector<string> employeeInfo = commaDelimetedString(data, ',');
			if (employeeInfo[4] != "M123M" && employeeInfo[7] == "weekly") {
				changeColor(15);
				cout << "Employee Name: " << employeeInfo[0] << " " << employeeInfo[1] << endl;
				cout << "\t Manager who registered employee: " << employeeInfo[4] << endl;
				cout << "\t Title: " << employeeInfo[6] << endl;
				cout << "\t Hourly Wage: $" << employeeInfo[9] << endl;
				cout << "\t Hours worked: " << employeeInfo[10] << endl;
				cout << "\t Paid every: " << employeeInfo[8] << endl;
				cout << "\t Marital status: " << employeeInfo[5] << endl;
				cout << endl;
			};
			if (employeeInfo[4] != "M123M" && employeeInfo[7] == "monthly") {
				changeColor(15);
				cout << "Employee Name: " << employeeInfo[0] << " " << employeeInfo[1] << endl;
				cout << "\t Manager who registered employee: " << employeeInfo[4] << endl;
				cout << "\t Title: " << employeeInfo[6] << endl;
				cout << "\t Hourly Wage: $" << employeeInfo[9] << endl;
				cout << "\t Hours worked: " << employeeInfo[10] << endl;

				dayDetermine = stoi(employeeInfo[8]);

				if (dayDetermine % 10 > 3 && dayDetermine < 10) {
					cout << "\t Paid every: " << employeeInfo[8] << "th day of the month" << endl;

				}

				if (dayDetermine % 10 == 3 && dayDetermine > 19) {
					cout << "\t Paid every: " << employeeInfo[8] << "rd day of the month" << endl;

				}
				if (10 <= dayDetermine <= 19) {
					cout << "\t Paid every: " << employeeInfo[8] << "th day of the month" << endl;

				}
				if (dayDetermine % 10 == 3) {
					cout << "\t Paid every: " << employeeInfo[8] << "rd day of the month" << endl;

				}
				if (dayDetermine % 10 == 2) {
					cout << "\t Paid every: " << employeeInfo[8] << "nd day of the month" << endl;

				}
				if (dayDetermine % 10 == 1) {
					cout << "\t Paid every: " << employeeInfo[8] << "st day of the month" << endl;

				}
				if (dayDetermine > 28) {
					cout << "\t Paid every: " << "End of the month" << endl;

				}
				cout << "\t Marital status: " << employeeInfo[5] << endl;
				cout << endl;
			};
		};
	};
	employeeView.close();
	changeColor(14);
	cout << endl;
	cout << "Press any key to exit view employee screen." << endl;
	getch();

	managerPage = 1;
	
}

void ManagerPages::editEmployeePage() { // edit the employee variables

	string line = "";
	int counter = 0;
	int editCounter = 0;
	vector<string> employeeInfo;
	int userChoice = 0;
	int isFinish = 1;
	int newPay;
	string maritalString = "";
	char* maritalStr = new char[8];
	string maritalStatus = "";
	ifstream editReadEmployee;
	ifstream readEmployee;
	ofstream temporaryEmployeeEdit;
	editReadEmployee.open("edit_employee.txt");
	readEmployee.open("users_rpa.txt");
	int numOfEmployee = count(istreambuf_iterator<char>(readEmployee), istreambuf_iterator<char>(), '\n');

	system("CLS");

	if (numOfEmployee > 0) { // gets the employee info of the selected employee
		counter = 0;
		for (int i = 1; i < numOfEmployee + 1; i++) {
			line = "";
			if (editChoice == i) {
				while (getline(editReadEmployee, line)) {
					counter++;
					if (counter == editChoice) {
						employeeInfo = commaDelimetedString(line, ',');
					}
				}
			}
		}
		string toAdd = employeeInfo.at(0) + "," + employeeInfo.at(1) + "," + employeeInfo.at(2) + "," + employeeInfo.at(3) +
			"," + employeeInfo.at(4) + "," + employeeInfo.at(5) + "," + employeeInfo.at(6) + "," + employeeInfo.at(7) + "," + employeeInfo.at(8) +
			"," + employeeInfo.at(9) + "," + employeeInfo.at(10);
		editReadEmployee.close();
		readEmployee.close();

		

		while (isFinish == 1) {

			ifstream readTheEmployee;
			ofstream tempUser;
			
				
			if (editCounter > 0) {
				readTheEmployee.open("users_rpa.txt");
				tempUser.open("edit_employee.txt");
				tempUser << toAdd << endl;
				readTheEmployee.close();
				tempUser.close();
			}
			

			line = "";
			system("CLS");
			changeColor(11);
			cout << "@@=================================================@@" << endl;
			cout << setw(22) << "EDIT " << employeeInfo.at(0) << " " << employeeInfo.at(1) << endl;
			changeColor(14);

			cout << "(1): Edit Pay" << endl;
			cout << "(2): Edit Marital Status" << endl;
			cout << "(3): Edit Title" << endl;
			cout << "(4): Remove Employee" << endl;
			cout << "(5): Exit" << endl;
			cout << "Please choose an option: ";

			cin >> userChoice;

			if (!cin) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				changeColor(12);
				cout << "Please enter a valid choice" << endl;
				changeColor(14);
				getch();
				continue;
			}
			else {
				editCounter++;
			}

			if (userChoice == 1) {
				
				temporaryEmployeeEdit.open("employee_temp_edit.txt");
				stringstream newerPay;
				string payWrite;
				string lineToChange = employeeInfo[0] + "," + employeeInfo[1] + "," + employeeInfo[2] + ","
					+ employeeInfo[3] + "," + employeeInfo[4] + "," + employeeInfo[5] + "," + employeeInfo[6] + ","
					+ employeeInfo[7] + "," + employeeInfo[8] + "," + employeeInfo[9] + "," + employeeInfo[10];
				string newData = employeeInfo[0] + "," + employeeInfo[1] + "," + employeeInfo[2] + ","
					+ employeeInfo[3] + "," + employeeInfo[4] + "," + employeeInfo[5] + "," + employeeInfo[6] + ","
					+ employeeInfo[7] + "," + employeeInfo[8] + ",";

				while (true) {
					system("CLS");
					changeColor(11);
					cout << "@@=================================================@@" << endl;
					cout << setw(22) << "EDIT " << employeeInfo.at(0) << " " << employeeInfo.at(1) << endl;
					changeColor(14);
					cout << endl;
					cout << "Enter the new pay: ";
					cin >> newPay;
					

					if (!cin) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						changeColor(12);
						cout << "Please enter a valid choice" << endl;
						changeColor(14);
						getch();
						continue;
					}
					else {
						newerPay << newPay;
						newerPay >> payWrite;
						break;
					}

				}
				
				cout << payWrite << endl;
				getch();
				

				readEmployee.open("users_rpa.txt");


				newData += payWrite + "," + employeeInfo[10];

				// copy contents to new file

				while (getline(readEmployee, line)) {
					if (line != lineToChange) {
						temporaryEmployeeEdit << line << endl;
					}
					else {
						temporaryEmployeeEdit << newData << endl;
					}
				}

				cout << newData << endl;

				temporaryEmployeeEdit.close();
				readEmployee.close();
				editReadEmployee.close();

				// checks if the files are open
				if (temporaryEmployeeEdit.is_open()) {
					changeColor(12);
					cout << "Error: File is still opened, cannot modify passwords." << endl;
				}

				if (readEmployee.is_open()) {
					changeColor(12);
					cout << "Error: File is still opened, cannot modify passwords." << endl;
				}
				
				if (editReadEmployee.is_open()) {
					changeColor(12);
					cout << "Error: File is still opened, cannot modify passwords." << endl;
				}
				

				remove("users_rpa.txt"); // remove the file
				remove("edit_employee.txt");

				if (remove("users_rpa.txt") == 0) { // final check if user is removed

					cout << "" << endl;

				}

				if (remove("edit_employee.txt") == 0) { // final check if user is removed

					cout << "" << endl;

				}

				rename("employee_temp_edit.txt", "users_rpa.txt"); // rename the file so that the password change is successful

				cout << endl;
				changeColor(10);
				cout << "Pay has been changed successfully to $" << newPay << " for " << employeeInfo.at(0) << " " << employeeInfo.at(1) << "." << endl;
				cout << endl;
				changeColor(14);
				cout << "Returning to the manager menu; press any key to continue." << endl;
				getch();
				isFinish = 0;
				
			}

			
			if (userChoice == 2) {
				string lineToChange = employeeInfo[0] + "," + employeeInfo[1] + "," + employeeInfo[2] + ","
					+ employeeInfo[3] + "," + employeeInfo[4] + "," + employeeInfo[5] + "," + employeeInfo[6] + ","
					+ employeeInfo[7] + "," + employeeInfo[8] + "," + employeeInfo[9] + "," + employeeInfo[10];
				string newData = employeeInfo[0] + "," + employeeInfo[1] + "," + employeeInfo[2] + ","
					+ employeeInfo[3] + "," + employeeInfo[4] + ",";

				
				while (true) {
					maritalString = "";
					cout << "Enter the new marital status: ";;
					cin >> maritalStatus;
					strcpy(maritalStr, maritalStatus.c_str());

					for (int i = 0; i < maritalStatus.length(); i++) {

						maritalString += tolower(maritalStr[i]);

					}

					if (maritalString == "married") {
						break;
					}

					if (maritalString == "single") {
						break;
					}
					if (maritalString != "married" || maritalString != "single") {
						changeColor(12);
						cout << "Please enter valid marital status" << endl;
						changeColor(14);
					}

				}

				temporaryEmployeeEdit.open("employee_temp_edit.txt");

				readEmployee.open("users_rpa.txt");

				newData += maritalString + "," + employeeInfo[6] + ","
					+ employeeInfo[7] + "," + employeeInfo[8] + "," + employeeInfo[9] + "," + employeeInfo[10];

				// copy contents to new file

				while (getline(readEmployee, line)) {
					if (line != lineToChange) {
						temporaryEmployeeEdit << line << endl;
					}
					else {
						temporaryEmployeeEdit << newData << endl;
					}
				}

				temporaryEmployeeEdit.close();
				readEmployee.close();

				// checks if the files are open
				if (temporaryEmployeeEdit.is_open()) {
					changeColor(12);
					cout << "Error: File is still opened, cannot modify passwords." << endl;
				}

				if (!temporaryEmployeeEdit.is_open()) {
					cout << "";
				}

				if (readEmployee.is_open()) {
					changeColor(12);
					cout << "Error: File is still opened, cannot modify passwords." << endl;
				}
				if (!readEmployee.is_open()) {
					cout << "";
				}

				remove("users_rpa.txt"); // remove the file

				if (remove("users_rpa.txt") == 0) { // final check if user is removed

					cout << "" << endl;

				}

				rename("employee_temp_edit.txt", "users_rpa.txt"); // rename the file so that the password change is successful

				cout << endl;
				changeColor(10);
				cout << "Marital status has been changed successfully to " << maritalStatus << " for " << employeeInfo.at(0) << " " << employeeInfo.at(1) << "." << endl;
				cout << endl;
				changeColor(14);
				cout << "Returning to the manager menu; press any key to continue." << endl;
				getch();
				isFinish = 0;

				
			}

			if (userChoice == 3) {
				string newTitle = "";
				string lineToChange = employeeInfo[0] + "," + employeeInfo[1] + "," + employeeInfo[2] + ","
					+ employeeInfo[3] + "," + employeeInfo[4] + "," + employeeInfo[5] + "," + employeeInfo[6] + ","
					+ employeeInfo[7] + "," + employeeInfo[8] + "," + employeeInfo[9] + "," + employeeInfo[10];
				string newData = employeeInfo[0] + "," + employeeInfo[1] + "," + employeeInfo[2] + ","
					+ employeeInfo[3] + "," + employeeInfo[4] + "," + employeeInfo[5] + ",";


				cout << "Enter a new title: ";
				cin.ignore();
				getline(cin, newTitle);

				temporaryEmployeeEdit.open("employee_temp_edit.txt");

				readEmployee.open("users_rpa.txt");

				newData += newTitle + "," + employeeInfo[7] + ","
					+ employeeInfo[8] + "," + employeeInfo[9] + "," + employeeInfo[10];

				// copy contents to new file

				while (getline(readEmployee, line)) {
					if (line != lineToChange) {
						temporaryEmployeeEdit << line << endl;
					}
					else {
						temporaryEmployeeEdit << newData << endl;
					}
				}

				temporaryEmployeeEdit.close();
				readEmployee.close();

				// checks if the files are open
				if (temporaryEmployeeEdit.is_open()) {
					changeColor(12);
					cout << "Error: File is still opened, cannot modify passwords." << endl;
				}

				if (!temporaryEmployeeEdit.is_open()) {
					cout << "";
				}

				if (readEmployee.is_open()) {
					changeColor(12);
					cout << "Error: File is still opened, cannot modify passwords." << endl;
				}
				if (!readEmployee.is_open()) {
					cout << "";
				}

				remove("users_rpa.txt"); // remove the file

				if (remove("users_rpa.txt") == 0) { // final check if user is removed

					cout << "" << endl;

				}

				rename("employee_temp_edit.txt", "users_rpa.txt"); // rename the file so that the password change is successful

				cout << endl;
				changeColor(10);
				cout << "Title has been changed successfully to " << newTitle << " for " << employeeInfo.at(0) << " " << employeeInfo.at(1) << "." << endl;
				cout << endl;
				changeColor(14);
				cout << "Returning to the manager menu; press any key to continue." << endl;
				getch();
				isFinish = 0;


			}

			if (userChoice == 4) {
				string newTitle = "";
				string lineToChange = employeeInfo[0] + "," + employeeInfo[1] + "," + employeeInfo[2] + ","
					+ employeeInfo[3] + "," + employeeInfo[4] + "," + employeeInfo[5] + "," + employeeInfo[6] + ","
					+ employeeInfo[7] + "," + employeeInfo[8] + "," + employeeInfo[9] + "," + employeeInfo[10];
				string newData = "";

				temporaryEmployeeEdit.open("employee_temp_edit.txt");
				readEmployee.open("users_rpa.txt");

				// copy contents to new file

				while (getline(readEmployee, line)) {
					if (line != lineToChange) {
						temporaryEmployeeEdit << line << endl;
					}
					else {
						cout << "";
					}
				}

				temporaryEmployeeEdit.close();
				readEmployee.close();

				// checks if the files are open
				if (temporaryEmployeeEdit.is_open()) {
					changeColor(12);
					cout << "Error: File is still opened, cannot modify passwords." << endl;
				}

				if (!temporaryEmployeeEdit.is_open()) {
					cout << "";
				}

				if (readEmployee.is_open()) {
					changeColor(12);
					cout << "Error: File is still opened, cannot modify passwords." << endl;
				}
				if (!readEmployee.is_open()) {
					cout << "";
				}

				remove("users_rpa.txt"); // remove the file

				if (remove("users_rpa.txt") == 0) { // final check if user is removed

					cout << "" << endl;

				}

				rename("employee_temp_edit.txt", "users_rpa.txt"); // rename the file so that the password change is successful

				cout << endl;
				changeColor(10);
				cout << employeeInfo.at(0) << " " << employeeInfo.at(1) << " has been removed successfully." << endl;
				cout << endl;
				changeColor(14);
				cout << "Returning to the manager menu; press any key to continue." << endl;
				getch();
				isFinish = 0;


			}
			

			if (userChoice == 5) {
				editChoice = 0;
				employeeInfo.clear();
				readEmployee.close();
				temporaryEmployeeEdit.close();
				editReadEmployee.close();
				employeeInfo.clear();
				isFinish = 0;
				managerPage = 1;
				

			}


		}

	}
	employeeInfo.clear();
	readEmployee.close();
	temporaryEmployeeEdit.close();
	editReadEmployee.close();
	editChoice = 0;
}



// the salary page for the manager side
void ManagerPages::payManagerSalaryScreen() {
	system("CLS");
	changeColor(11);
	cout << "@@=================================================@@" << endl;
	cout << setw(35) << "MANAGER SALARY SCREEN" << endl;
	changeColor(15);
	cout << endl;
	cout << "\tSALARY EVERY: " << currentUser[7] << " - " << currentUser[8] << endl;
	cout << "\tHOURS: " << stod(currentUser[10]) << endl;
	int dayDetermine = 0;
	double extraOver = stod(currentUser[10]) - 40;
	double gross = (stod(currentUser[10]) * stod(currentUser[9]));
	cout << "\tGROSS ";
	if (extraOver < 0) {
		cout << "(NO OVER TIME) $" << gross << endl;
	}
	else {
		gross += (extraOver * 1.5);
		cout << "(WITH OVER TIME) $" << gross << endl;
	};
	cout << endl;

	cout << "PAYMENT EVERY: ";
	if (currentUser[7] == "monthly") {

		dayDetermine = stoi(currentUser[8]);

		if (dayDetermine % 10 > 3 && dayDetermine < 10) {
			cout << "MONTH => " << currentUser[8] << "th day of the month" << endl;

		}

		if (dayDetermine % 10 == 3 && dayDetermine > 19) {
			cout << "MONTH => " << currentUser[8] << "rd day of the month" << endl;

		}
		if (10 <= dayDetermine <= 19) {
			cout << "MONTH => " << currentUser[8] << "th day of the month" << endl;

		}
		if (dayDetermine % 10 == 3) {
			cout << "MONTH => " << currentUser[8] << "rd day of the month" << endl;

		}
		if (dayDetermine % 10 == 2) {
			cout << "MONTH => " << currentUser[8] << "nd day of the month" << endl;

		}
		if (dayDetermine % 10 == 1) {
			cout << "MONTH => " << currentUser[8] << "st day of the month" << endl;

		}
		if (dayDetermine > 28) {
			cout << "MONTH => " << "End of the month" << endl;

		}
		
	}
	else {
		cout << currentUser[8] << " of the week" << endl;
	};


	if (true) {
		calcuteNetPay(currentUser[5], gross);
	}
	cout << endl;
	changeColor(14);
	cout << endl;
	cout << "Press any key to return to the manager menu." << endl;
	getch();

	managerPage = 1;

};

// clocking in function which adds on to the hours based on the time passed in real time
void ManagerPages::clockInScreen() {
	system("CLS");
	changeColor(11);
	cout << "@@=================================================@@" << endl;
	cout << setw(35) << "CLOCK IN SCREEN" << endl;
	changeColor(15);
	cout << endl;
	string dummy;

	time_t clockinTime;
	time_t clockOutTime;
	time(&clockinTime);
	time(&clockOutTime);

	cout << "Clock in successful at " << this->getSystemTime() << "." << endl;
	changeColor(14);
	cout << "Press any key to clock out." << endl;
	getch();

	string passwordVer;


	while (passwordVer != currentUser[3]) {
		cout << "To clock out please enter your password: ";
		cin >> passwordVer;

		if (passwordVer != currentUser[3]) {
			system("CLS");
			changeColor(12);
			cout << "Invalid password, please try again." << endl;
			changeColor(14);

		}

	}


	time(&clockOutTime);
	if (passwordVer == currentUser[3]) {

		double hours = difftime(clockOutTime, clockinTime) / 1;

		double total = hours + stod(currentUser.at(9));
		string f = "" + to_string(total);
		string lineToChange = currentUser.at(0) + "," + currentUser.at(1) + "," + currentUser.at(2) + "," + currentUser.at(3) +
			"," + currentUser.at(4) + "," + currentUser.at(5) + "," + currentUser.at(6) + "," + currentUser.at(7) + "," + currentUser.at(8) +
			"," + currentUser.at(9) + "," + currentUser.at(10);
		string newData = currentUser.at(0) + "," + currentUser.at(1) + "," + currentUser.at(2) + "," + currentUser.at(3) +
			"," + currentUser.at(4) + "," + currentUser.at(5) + "," + currentUser.at(6) + "," + currentUser.at(7) + "," + currentUser.at(8) +
			"," + currentUser.at(9) + "," + f;


		ifstream employeeReder;
		ofstream employeeReWriter;
		vector<string> archive;
		employeeReWriter.open("user_change.txt");
		employeeReder.open("users_rpa.txt");
		string line = "";


		while (getline(employeeReder, line)) {
			if (line != lineToChange) {
				employeeReWriter << line << endl;
			}
			else {
				employeeReWriter << newData << endl;
			}
		}

		employeeReder.close();
		employeeReWriter.close();

		remove("users_rpa.txt");
		rename("user_change.txt", "users_rpa.txt");


		this->showClockOut();
	}
	

};

// clock out screen
void ManagerPages::showClockOut() {

	system("CLS");
	changeColor(11);
	cout << "@@=================================================@@" << endl;
	cout << setw(35) << "CLOCK OUT SCREEN" << endl;
	changeColor(15);

	cout << endl;
	cout << "You have clocked out successfully at " << this->getSystemTime() << "." << endl;
	changeColor(14);
	cout << "Please re-login for an updated salary display; press any key to return to main menu." << endl;
	getch();

	returnToMain = 1;
}



// to extract the day for the file write on the user files
string ManagerPages::getCurrentDay(int userNumber) {
	vector<string> days = { "monday" , "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday" };

	string theDay = days.at(userNumber - 1);
	return theDay;

}

// change the text color function
void ManagerPages::changeColor(int color) {

	static const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);

}

// to get the time for the clock in/out logging
string ManagerPages::getSystemTime() {

	time_t t;
	struct tm* tmp;
	char TIME_NOW[Size];
	time(&t);

	// localtime() uses pointer t for time and uses tm strcutre for the local time specifier
	tmp = localtime(&t);

	// using strftime function for the time display
	strftime(TIME_NOW, sizeof(TIME_NOW), "%x - %I:%M:%S %p %Z", tmp);

	return TIME_NOW;

}


// <OTHERS> 
// extracting information from the files
vector<string> ManagerPages::commaDelimetedString(string ll, char limit) {
	vector<string> res;
	stringstream s_stream(ll);

	while (s_stream.good()) {
		string s;
		getline(s_stream, s, limit);
		res.push_back(s);
	};
	return res;
};

// extracting information from the files
vector<int> ManagerPages::commaDelimetedInt(string ll, char limit) {
	vector<int> res;
	stringstream s_stream(ll);

	while (s_stream.good()) {
		string s;
		getline(s_stream, s, limit);
		res.push_back(stoi(s));
	};
	return res;
};


// algorithms used for calculating the taxes applied to the income
void ManagerPages::calcuteNetPay(string marriedSingle, double gg) {
	double calculatedGross = gg;
	double calculatedNet = 0.0;
	double IncomePercent, incomeO;
	double FederalPercent, federalO;
	const double  SOCIALPERCENT = 0.062;
	const double  MEDICAREPERCENT = 0.0145;
	const double FAMILYLEAVE = .00511;
	const double DIS = .005;

	// logic for income tax
	if ((calculatedGross >= 0.0) && (calculatedGross <= 8500.00)) {
		IncomePercent = 0.04;
		incomeO = calculatedGross - (IncomePercent * calculatedGross);

	}
	else if ((calculatedGross >= 8501.0) && (calculatedGross <= 11700.00)) {
		IncomePercent = .045; //350 + 4.5% of  (gross - 8500 )
		incomeO = calculatedGross - (350 + (IncomePercent * (calculatedGross - 8500)));
	}
	else if ((calculatedGross >= 11701.0) && (calculatedGross <= 13900.00)) {
		IncomePercent = 0.0525; // 484 + 5.25% of (gross - 11700)
		incomeO = calculatedGross - (484 + (IncomePercent * (calculatedGross - 11700)));
	}
	else if ((calculatedGross >= 13901.0) && (calculatedGross <= 21400.00)) {
		IncomePercent = .059; // 600 + 5.9% of (gross - 13900)
		incomeO = calculatedGross - (600 + (IncomePercent * (calculatedGross - 13900)));
	}
	else if ((calculatedGross >= 21401.0) && (calculatedGross <= 80650.00)) {
		IncomePercent = .0597; // 1042 + 5.97% of (gross - 21400)
		incomeO = calculatedGross - (1042 + (IncomePercent * (calculatedGross - 21400)));
	}
	else if ((calculatedGross >= 80651.0) && (calculatedGross <= 215400.00)) {
		IncomePercent = .0633; // 4579 + 6.33% of  (gross - 80650)
		incomeO = calculatedGross - (4579 + (IncomePercent * (calculatedGross - 80650)));
	}
	else if ((calculatedGross >= 215401.0) && (calculatedGross <= 1077550.00)) {
		IncomePercent = 0.0685; // 13109 + 6.85% of (gross - 215400)
		incomeO = calculatedGross - (13109 + (IncomePercent * (calculatedGross - 215400)));
	}
	else if ((calculatedGross >= 1077550.0) && (calculatedGross <= 5000000.00)) {
		IncomePercent = .0965; // 72166 + 9.65% of  (gross - 1077550)
		incomeO = calculatedGross - (72166 + (IncomePercent * (calculatedGross - 1077550)));
	}
	else if ((calculatedGross >= 5000001.0) && (calculatedGross <= 25000000.00)) {
		IncomePercent = .1030; //  450683 + 10.30% of (gross - 5000000)
		incomeO = calculatedGross - (450683 + (IncomePercent * (calculatedGross - 5000000)));
	}
	else if ((calculatedGross >= 25000001.0)) {
		IncomePercent = .1090; // 2510683 +  10.90% of  (grss - 25000000)
		incomeO = calculatedGross - (2510683 + (IncomePercent * (calculatedGross - 25000000)));
	};

	//logic for federal tax  SINGLE
	if (marriedSingle == "single") {
		if (calculatedGross < 10275.00) {
			FederalPercent = 0.10;
			federalO = (calculatedGross - (FederalPercent * calculatedGross));
		}
		else if ((calculatedGross > 10275.00) && (calculatedGross < 41775.00)) {
			FederalPercent = 0.12; // 995 + 12% of (gross - 9950)
			federalO = (calculatedGross - (1027.50 + (FederalPercent * (calculatedGross - 10275.00))));
		}
		else if ((calculatedGross > 41775.00) && (calculatedGross < 89075.00)) {
			FederalPercent = 0.22; // 4664 + 22% of (gross - 40525)
			federalO = (calculatedGross - (4807.50 + (FederalPercent * (calculatedGross - 41775.00))));
		}
		else if ((calculatedGross > 89075.00) && (calculatedGross < 170050.00)) {
			FederalPercent = 0.24; // 14751 + 24% of (gross - 86375)
			federalO = (calculatedGross - (15213.50 + (FederalPercent * (calculatedGross - 89075.00))));
		}
		else if ((calculatedGross > 170050.00) && (calculatedGross < 215950.00)) {
			FederalPercent = 0.32; // 33603 + 32% of  (gross - 164925)
			federalO = (calculatedGross - (34647.50 + (FederalPercent * (calculatedGross - 170050.00))));
		}
		else if ((calculatedGross > 215950.00) && (calculatedGross < 539900.00)) {
			FederalPercent = .35; // 47843 + 35% of (gross - 209425)
			federalO = (calculatedGross - (49335.50 + (FederalPercent * (calculatedGross - 215950.00))));
		}
		else {
			if (calculatedGross > 539900.00) {
				FederalPercent = .37; // 157804.25 +  37% of (gross - 523600)
				federalO = (calculatedGross - (162718.00 + (FederalPercent * (calculatedGross - 539900.00))));
			};
		};
	}


	// MARRIED
	if (marriedSingle == "married") {
		if (calculatedGross < 10275.00) {
			FederalPercent = 0.10;
			federalO = (calculatedGross - (FederalPercent * calculatedGross));
		}
		else if ((calculatedGross > 10275.00) && (calculatedGross < 41775)) {
			FederalPercent = 0.12; // 995 + 12% of (gross - 9950)
			federalO = (calculatedGross - (1027.50 + (FederalPercent * (calculatedGross - 10275.00))));
		}
		else if ((calculatedGross > 41775.00) && (calculatedGross < 89075.00)) {
			FederalPercent = 0.22; // 4664 + 22% of (gross - 40525)
			federalO = (calculatedGross - (4807.50 + (FederalPercent * (calculatedGross - 41775.00))));
		}
		else if ((calculatedGross > 89075) && (calculatedGross < 170050)) {
			FederalPercent = 0.24; // 14751 + 24% of (gross - 86375)
			federalO = (calculatedGross - (15213.50 + (FederalPercent * (calculatedGross - 89075))));
		}
		else if ((calculatedGross > 170050.00) && (calculatedGross < 215950.00)) {
			FederalPercent = 0.32; // 33603 + 32% of  (gross - 164925)
			federalO = (calculatedGross - (34647.50 + (FederalPercent * (calculatedGross - 170050))));
		}
		else if ((calculatedGross > 215950.00) && (calculatedGross < 323925.00)) {
			FederalPercent = .35; // 47843 + 35% of (gross - 209425)
			federalO = (calculatedGross - (49335.50 + (FederalPercent * (calculatedGross - 215950.00))));
		}
		else {
			if (calculatedGross > 323925.00) {
				FederalPercent = .37; // 157804.25 +  37% of (gross - 523600)
				federalO = (calculatedGross - (86127.00 + (FederalPercent * (calculatedGross - 323925.00))));
			};
		};
	}

	double ss = calculatedGross - (calculatedGross * SOCIALPERCENT);
	double mm = (calculatedGross * MEDICAREPERCENT);
	double nfl = calculatedGross - (calculatedGross * FAMILYLEAVE);
	double dd = calculatedGross - (calculatedGross * DIS);
	double tax = IncomePercent + FederalPercent + SOCIALPERCENT + MEDICAREPERCENT + FAMILYLEAVE + DIS;
	calculatedNet = calculatedGross - (calculatedGross * tax);
	cout << endl;
	cout << "\tSOCIAL SECURITY: \t$" << ss << endl;
	cout << "\tMEDICARE: \t\t$" << mm << endl;
	cout << "\tFAMILY LEAVE: \t\t$" << nfl << endl;
	cout << "\tDISABILITY: \t\t$" << dd << endl;
	cout << "\tFEDERAL: \t\t$" << federalO << endl;
	cout << "\tINCOME: \t\t$" << incomeO << endl;
	cout << endl;
	cout << "\tGROSS NET INCOME: \t$" << calculatedNet;

}