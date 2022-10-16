#include "EmployeePages.h"
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
#include <cctype>
#include <chrono>
#include <conio.h>
#pragma warning(disable : 4996) // so that we can use local time function from ctime
#define Size 50
#undef max
using namespace std;


/*
	DEVELOP BY: ENMANUEL, ALBERT
	This method is to show the screen for the logged in employee
*/


void EmployeePages::showEmployeePage() {
	system("CLS");

	int choice = 0;
	int exitChoice = 0;
	bool isClockedIn = false;
	string passwordCheck;
	string newPassword;
	string newPasswordCheck;
	string oldPassword = currentUser[3];


	while (choice < 1 || choice > 4) { // shows employee information
		system("CLS");
		changeColor(11);
		cout << "@@=================================================@@" << endl;
		cout << setw(35) << "Employee Page" << endl;
		changeColor(14);

		cout << endl;
		cout << "\tEmployee name: " << currentUser[0] << " " << currentUser[1] << endl;
		cout << "\tEmployee title: " << currentUser[6] << endl;
		cout << "\tEmployee Hourly Wage: $" << currentUser[9] << endl;
		cout << "\tEmployee Username: " << currentUser[2] << endl;
		cout << endl;
		cout << endl;

		cout << "(1): Clock In" << endl;
		cout << "(2): View Pay" << endl;
		cout << "(3): Change Password" << endl;
		cout << "(4): Log Out" << endl;
		cin >> choice;
	}


	if (choice == 1) {
		this->clockInScreen();
	};

	if (choice == 2) {
		this->payEmployeeSalaryScreen();
	}

	if (choice == 3) {

		string lineToChange = this->currentUser[0] + "," + this->currentUser[1] + "," + this->currentUser[2] + ","
			+ this->currentUser[3] + "," + this->currentUser[4] + "," + this->currentUser[5] + "," + this->currentUser[6] + ","
			+ this->currentUser[7] + "," + this->currentUser[8] + "," + this->currentUser[9] + "," + this->currentUser[10];
		string newData = this->currentUser[0] + "," + this->currentUser[1] + "," + this->currentUser[2] + ",";
		string line = "";
		string userLine = "";
		ofstream temporaryFileWrite;
		ifstream usersFile;

		// opens the text file that will be use to change values
		temporaryFileWrite.open("password_change.txt", ios::app);

		// open user file
		usersFile.open("users_rpa.txt");

		do { // changing password algorithm
			system("CLS");
			changeColor(11);
			cout << "@@=================================================@@" << endl;
			cout << setw(35) << "Password Change" << endl;
			changeColor(14);

			cout << endl;
			cout << "Enter old password: ";
			cin >> passwordCheck;

			if (passwordCheck.compare(oldPassword) != 0) {
				changeColor(12);
				cout << "Passwords do not match, try again." << endl;
				cout << endl;
				changeColor(14);
				getch();
			}

		} while (passwordCheck.compare(oldPassword) != 0);


		do {

			cout << endl;
			cout << "Enter new password: ";
			cin >> newPassword;

			cout << "Re-enter new password: ";
			cin >> newPasswordCheck;

			if (newPassword.compare(newPasswordCheck) != 0) {
				changeColor(12);
				cout << "Passwords do not match, try again." << endl;
				cout << endl;
				changeColor(14);
				getch();
				system("CLS");
			}

			if (newPassword.compare(oldPassword) == 0) {
				changeColor(12);
				cout << "New password cannot be the same as the old!" << endl;
				cout << endl;
				changeColor(14);
				getch();
				system("CLS");
			}

		} while (newPassword.compare(newPasswordCheck) != 0 && newPassword.compare(oldPassword) == 0);

		// add the new password to the new data
		newData += newPassword + "," + this->currentUser[4] + "," + this->currentUser[5] + "," + this->currentUser[6] + ","
			+ this->currentUser[7] + "," + this->currentUser[8] + "," + this->currentUser[9] + "," + this->currentUser[10];

		// copy contents to new file

		while (getline(usersFile, line)) {
			if (line != lineToChange) {
				temporaryFileWrite << line << endl;
			}
			else {
				temporaryFileWrite << newData << endl;
			}
		}

		temporaryFileWrite.close();
		usersFile.close();

		// checks if the files are open
		if (temporaryFileWrite.is_open()) {
			changeColor(12);
			cout << "Error: File is still opened, cannot modify passwords." << endl;
		}

		if (!temporaryFileWrite.is_open()) {
			cout << "";
		}

		if (usersFile.is_open()) {
			changeColor(12);
			cout << "Error: File is still opened, cannot modify passwords." << endl;
		}
		if (!usersFile.is_open()) {
			cout << "";
		}

		remove("users_rpa.txt"); // remove the file

		if (remove("users_rpa.txt") == 0) { // final check if user is removed

			cout << "" << endl;

		}
		currentUser[5] = newPassword; // makes sure the password is changed

		rename("password_change.txt", "users_rpa.txt"); // rename the file so that the password change is successful

		cout << endl;
		changeColor(10);
		cout << "Passwords have been changed." << endl;
		cout << endl;
		changeColor(14);
		cout << "Please re-login with your new password." << endl;
		cout << "Returning to the main menu; press any key to continue." << endl;
		getch();

		returnToMain = 1; // return to the main page

	}

	if (choice == 4) { // exit choice

		cout << "Are you sure you want to exit?" << endl;
		cout << "(1): Yes" << endl;
		cout << "(2): No" << endl;
		cin >> exitChoice;

		if (exitChoice == 1) {
			this->currentUser.clear();
			returnToMain = 1; // return to the main page
		}
		if (exitChoice == 2) {
			this->showEmployeePage();
		}

	};
};



// this screen is for first time employee login
void EmployeePages::showOneTime() {
	vector<string> archive;
	string passy = "app123";
	string lineToChange = this->currentUser[0] + "," + this->currentUser[1] + "," + this->currentUser[2] + "," +
		this->currentUser[3] + "," + this->currentUser[4] + "," + this->currentUser[5] + "," + this->currentUser[6] +
		"," + this->currentUser[7] + "," + this->currentUser[8] + "," + this->currentUser[9] + "," + this->currentUser[10];
	string newData = this->currentUser[0] + "," + this->currentUser[1] + "," + this->currentUser[2] + ",";
	string line = "";
	ofstream usersFile;
	ofstream temporaryFileWrite;

	ifstream temporaryFile;

	// opens the text file that contains all users creds (users_rpa.txt) to add the change password
	usersFile.open("users_rpa.txt", ios::app);

	// opens temporary text file to read whats in it
	temporaryFile.open("users_rpa.txt");

	// opens the text file that will be use to change values
	temporaryFileWrite.open("password_change.txt");

	// ask user to change password
	while (passy == "app123") {
		system("CLS");
		changeColor(11);
		cout << "@@=================================================@@" << endl;
		cout << setw(35) << "FIRST TIME LOGIN SETUP" << endl;
		cout << endl;
		changeColor(14);
		cout << this->currentUser[0] << ", please create your own password." << endl;
		cout << "Create Password: ";
		cin >> passy;
	};

	// add the new password to the new data
	newData += passy + "," + this->currentUser[4] + "," + this->currentUser[5] + "," + this->currentUser[6] +
		"," + this->currentUser[7] + "," + this->currentUser[8] + "," + this->currentUser[9] + "," + this->currentUser[10];

	// copy contents to new file

	while (getline(temporaryFile, line)) {
		if (line != lineToChange) {
			temporaryFileWrite << line << endl;
		}
		else {
			temporaryFileWrite << newData << endl;
		}
	}

	temporaryFileWrite.close();
	usersFile.close();
	temporaryFile.close();

	// checks if the files are open
	if (temporaryFileWrite.is_open()) {
		changeColor(12);
		cout << "Error: File is still opened, cannot modify passwords." << endl;
	}

	if (!temporaryFileWrite.is_open()) {
		cout << "";
	}

	if (usersFile.is_open()) {
		changeColor(12);
		cout << "Error: File is still opened, cannot modify passwords." << endl;
	}
	if (!usersFile.is_open()) {
		cout << "";
	}

	remove("users_rpa.txt"); // remove the file

	if (remove("users_rpa.txt") == 0) { // final check if user is removed

		cout << "" << endl;

	}


	rename("password_change.txt", "users_rpa.txt"); // rename the file so that the password change is successful

	usersFile << newData << endl;
	usersFile.close();
	temporaryFile.close();
	temporaryFileWrite.close();

	changeColor(10);
	cout << "Password change successful." << endl;
	changeColor(14);
	cout << "Please re-login with new password; press any key to continue." << endl;
	getch();

	returnToMain = 1;

}


// the salary page for the employee side
void EmployeePages::payEmployeeSalaryScreen() {

	system("CLS");
	changeColor(11);
	cout << "@@=================================================@@" << endl;
	cout << setw(35) << "EMPLOYEE SALARY SCREEN" << endl;
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
	cout << endl;
	changeColor(14);
	cout << "Press any key to return to the employee menu." << endl;
	getch();
	this->showEmployeePage();

};


// clocking in function which adds on to the hours based on the time passed in real time
void EmployeePages::clockInScreen() {
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
		string employeeInfo = currentUser.at(0) + "," + currentUser.at(1) + "," + currentUser.at(2) + "," + currentUser.at(3) +
			"," + currentUser.at(4) + "," + currentUser.at(5) + "," + currentUser.at(6) + "," + currentUser.at(7) + "," + currentUser.at(8) +
			"," + currentUser.at(9) + "," + currentUser.at(10);
		string newEmployeeInfo = currentUser.at(0) + "," + currentUser.at(1) + "," + currentUser.at(2) + "," + currentUser.at(3) +
			"," + currentUser.at(4) + "," + currentUser.at(5) + "," + currentUser.at(6) + "," + currentUser.at(7) + "," + currentUser.at(8) +
			"," + currentUser.at(9) + "," + f;


		ifstream employeeReder;
		vector<string> archive;
		employeeReder.open("users_rpa.txt");
		string line = "";
		while (getline(employeeReder, line)) {
			if (line != employeeInfo) {
				archive.push_back(line);
			};
		};
		employeeReder.close();
		ofstream employeeReWriter;
		employeeReWriter.open("user_change.txt");
		for (int i = 0; i < archive.size(); i++) {
			employeeReWriter << archive.at(i) << endl;
		};
		employeeReWriter << newEmployeeInfo << endl;

		employeeReWriter.close();

		remove("users_rpa.txt");
		rename("user_change.txt", "users_rpa.txt");


		this->showClockOut();
	}
	else {
		this->showEmployeePage();
	};

};

// clock out screen
void EmployeePages::showClockOut() {
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



// to get the time for the clock in/out logging
string EmployeePages::getSystemTime() {

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

// to extract the day for the file write on the user files
string EmployeePages::getCurrentDay(int userNumber) {
	vector<string> days = { "monday" , "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday" };

	string theDay = days.at(userNumber - 1);
	return theDay;

}

// change the text color function
void EmployeePages::changeColor(int color) {

	static const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);

}


// <OTHERS> 
// extracting information from the files
vector<string> EmployeePages::commaDelimetedString(string ll, char limit) {
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
vector<int> EmployeePages::commaDelimetedInt(string ll, char limit) {
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
void EmployeePages::calcuteNetPay(string marriedSingle, double gg) {
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