#define __STDC_WANT_LIB_EXT1__ 1

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
#include <cctype>
#include <Windows.h>
#include <cctype>
#include <cstring>
#include <conio.h>
#pragma warning(disable : 4996) // so that we can use getch
#undef max 
using namespace std;
using std::cout;
// ======================================================================================================================
// // FIRST , LAST, USER , PASS, MANAGER UNDER,  MARRIED - SINGLE, TITLE, WEEK/MONTHLY, D-M, RATE,HOURS \\ \\


AppPages::AppPages(string name) {
	this->appName = name;
	
};

void AppPages::exitPage() {
	system("CLS");
	changeColor(11);
	cout << "@@=================================================@@" << endl;
	cout << setw(25) << "EXIT" << endl;
	cout << endl;
	changeColor(15);
	cout << "Thank you for using the " << appName << "!" << endl;
	cout << "Have a nice day!" << endl;

}

// this  screen is for the main screen
void AppPages::showMainPage() {
	int userChoice = 0;
	
	while (userChoice <1 || userChoice > 3) {
		system("CLS");
		changeColor(11);
		cout << "@@=================================================@@" << endl;
		cout << setw(35) << this->appName << endl;
		changeColor(14);

		cout << endl;
		cout << "(1): LogIn" << endl;
		cout << "(2): Register" << endl;
		cout << "(3): Exit Program" << endl;
		cout << "Enter a choice: ";
		cin >> userChoice;
		
		if (!cin) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // makes sure the cin is not failing
			changeColor(12);
			cout << "Please enter a valid choice" << endl;
			changeColor(14);
			getch();
		}
		
	}
	
	system("CLS");
	if (userChoice == 1) { // choices for the menu
		logInChoice = 1;
	}else if (userChoice == 2) {
		logInChoice = 2;
	}
	else if (userChoice == 3) {
		logInChoice = 3;

	}
};

// this screen is for the login screen
void AppPages::showLogInPage() {
	
	// gather all data from user logging in
	string userName;
	string passWord;

	// open the file that contains all the user credentials
	ifstream userFilesReader;
	ifstream employeeFilesReader;

	userFilesReader.open("users_rpa.txt");
	employeeFilesReader.open("tmp_users_rpa.txt");

	changeColor(11);
	cout << "@@=================================================@@" << endl;
	cout << setw(35) << this->appName << " LOGIN" << endl;
	changeColor(14);

	cout << endl;
	cout << "Username: ";
	cin >> userName;
	cout << "Password: ";
	cin >> passWord;

	system("CLS");

	if (userFilesReader.is_open()) {
		string lined; // store the value of each line

		
		while (getline(userFilesReader, lined)) {
			vector<string> targetUser = this->commaDelimetedString(lined,',');  // store all the user creds here
			user = targetUser;
			if ((userName._Equal(targetUser.at(2)) ) && (passWord._Equal(targetUser.at(3)))) {
				this->currentUser = targetUser;

				if (targetUser.at(6) == "manager") {
					userFilesReader.close();
					employeeFilesReader.close();
					logInManager = 1; // manager page
					break;
					
				}else {
					userFilesReader.close();
					employeeFilesReader.close();
					logInEmployee = 1; // employee page
					break;
					
				}

			}
			
			
		};

		

		while (getline(employeeFilesReader, lined)) {
			vector<string> targetUser = this->commaDelimetedString(lined,',');  // store all the user creds here

			if ((userName._Equal(targetUser.at(2))) && (passWord._Equal(targetUser.at(3)))) {
				user = targetUser;
				if (passWord == "app123") {
					userFilesReader.close();
					employeeFilesReader.close();
					firstTimeLogin = 1; // first time employee setup page
					break;
					
					
				};
			};

		}
		userFilesReader.close();
		employeeFilesReader.close();

		if (logInManager == 0 && logInEmployee == 0 && firstTimeLogin == 0) {
			this->loginCheck(userName, passWord);
		}
		
	};
	

};



// this screen is for the register screen
void AppPages::showRegisterPage() {
	string nManagerFirst, nManagerLast, nManagerUser, nManagerPass, dummy,nManagerMarriedSingle;

	string maritalString = "";
	char* maritalStr = new char[8];
	double hourlyPay;
	int paidOption = 0;
	int weekDay = 0;
	int monthlyDay = 0;
	int vv = 0;
	string weeklyMonthly;
	ofstream generalManagerWriter;
	generalManagerWriter.open("users_rpa.txt", ios::app);

	// begin the manager registration process
	changeColor(11);
	cout << "@@=================================================@@" << endl;
	cout << "Manager Registration: Authorized Users Only " << endl;
	cout << "\n";
	changeColor(14);
	cout << "Please enter your first name: ";
	cin >> nManagerFirst;
	cout << "Please enter your last name: ";
	cin >> nManagerLast;
	cout << "Create a username: ";
	cin >> nManagerUser;
	cout << "Create a password: ";
	cin >> nManagerPass;

	while (true) {
		maritalString = "";
		cout << "Married or single: ";
		cin >> nManagerMarriedSingle;
		strcpy(maritalStr, nManagerMarriedSingle.c_str());

		for (int i = 0; i < nManagerMarriedSingle.length(); i++) {

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
	
	
	while (paidOption > 2 || paidOption < 1) {

		cout << "Weekly = 1 or Monthly = 2: ";
		cin >> paidOption;

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
			break;
		}
		
	}

	if (paidOption == 1) {
		while (weekDay > 7 || weekDay < 1) {
			cout << "Enter day this manager will get paid (monday 1 - sunday 7): ";
			cin >> weekDay;

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
				break;
			}
			
		}

	}
	else {
		while (monthlyDay < 1 || monthlyDay > 30) {
			cout << "Enter date this manager will get paid (1 - 30): ";
			cin >> monthlyDay;

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
				break;
			}
		}
	};

	if (weekDay != 0) {
		vv = weekDay;
		weeklyMonthly = "weekly";

	}
	else {
		vv = monthlyDay;
		weeklyMonthly = "monthly";
	};

	while (true) {
		cout << "Hourly pay: $";
		cin >> hourlyPay;
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
			break;
		}
		
	}

	system("CLS");
	changeColor(11);
	cout << "@@=================================================@@" << endl;
	cout << "Manager Registration: Authorized Users Only " << endl;
	cout << "\n";
	changeColor(14);
	if (generalManagerWriter.is_open()) { // write to file

		if (weeklyMonthly == "weekly") {

			generalManagerWriter << nManagerFirst << "," << nManagerLast << "," << nManagerUser << "," << nManagerPass << "," << "M123M" << "," << maritalString << "," <<
				"manager" << "," << weeklyMonthly << "," << getCurrentDay(weekDay) << "," << hourlyPay << "," << "0.0" << endl;

		}


		if (weeklyMonthly == "monthly") {

			generalManagerWriter << nManagerFirst << "," << nManagerLast << "," << nManagerUser << "," << nManagerPass << "," << "M123M" << "," << maritalString << "," <<
				"manager" << "," << weeklyMonthly << "," << vv << "," << hourlyPay << "," << "0.0" << endl;

		}

		
		changeColor(10);
		cout << "Manager successfully registered;" << endl;
		changeColor(14);
		cout << "Please re-login for manager access." << endl;
		cout << "Press any key to continue." << endl;
		generalManagerWriter.close();
		getch();
		
	};


};

void AppPages::loginCheck(string username, string password) {
	// invalid login check, too many and the program exits
	// open the file that contains all the user credentials
	ifstream userFilesReader;
	ifstream employeeFilesReader;
	string lined = "";

	userFilesReader.open("users_rpa.txt");
	employeeFilesReader.open("tmp_users_rpa.txt");

	while (getline(userFilesReader, lined)) {
		vector<string> targetUser = this->commaDelimetedString(lined, ',');  // store all the user creds here

		if (username != targetUser.at(2) || password != targetUser.at(3)) {
			changeColor(11);
			cout << "@@=================================================@@" << endl;
			cout << setw(35) << this->appName << " LOGIN" << endl;
			changeColor(14);
			cout << endl;
			if (loginCounter >= 3) {

				changeColor(12);
				cout << "Too many failed login attempts, exiting the program." << endl;
				exit(0);

			}
			changeColor(12);
			cout << "Invalid login; please try again." << endl;
			changeColor(14);
			getch();
			loginCounter += 1;
			break;
		}

	}

}

// to extract the day for the file write on the user/manager files
string AppPages::getCurrentDay(int userNumber) { 
	vector<string> days = { "monday" , "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday" };
	
	string theDay = days.at(userNumber - 1);
	return theDay;

}

// change the text color function
void AppPages::changeColor(int color) {

	static const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);

}


// <OTHERS> 
// extracting information from the files
vector<string> AppPages::commaDelimetedString(string ll, char limit) {
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
vector<int> AppPages::commaDelimetedInt(string ll, char limit) {
	vector<int> res;
	stringstream s_stream(ll);

	while (s_stream.good()) {
		string s;
		getline(s_stream, s, limit);
		res.push_back(stoi(s));
	};
	return res;
};

// clocking in function
double AppPages::computeWorkedHours(vector<int> clockOut, vector<int> clockIn) {
	int result;
	vector<int> diffResult;
	// hh mm ss
	if (clockIn.at(2) > clockOut.at(2)) // sec
	{
		--clockOut.at(1); // min
		clockOut.at(2) += 60; //sec
	}

	diffResult.push_back(clockOut.at(2) - clockIn.at(2));
	if (clockIn.at(1) > clockOut.at(1))
	{
		--clockOut.at(0);
		clockOut.at(1) += 60;
	}
	diffResult.push_back(clockOut.at(1) - clockIn.at(1));
	diffResult.push_back(clockOut.at(0) - clockIn.at(0));
	result = diffResult.at(2) +  (diffResult.at(1) * (1 / 60)) + (diffResult.at(0) * (1 / 3600));
	return result;
};

