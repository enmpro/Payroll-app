#pragma once

// import all libraries needed ========================================================================================
#include <iostream>
#include <iomanip>
#include <Math.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <windows.h>

using namespace std;
// ======================================================================================================================

class ManagerPages {
private:
	string appName; // this is the tag name for the class
	vector<string> commaDelimetedString(string ll, char limit); // this method is use to get values from the text file
	vector<int> commaDelimetedInt(string ll, char limit); // this method is use to get values from the text file
	vector<int> clockInInfo;
	vector<int> clockOutInfo;
	vector<string> editEmployee;

	int editChoice = 0; // for editing the employee

public:
	

	int userChoice = 0;

	int returnToMain = 0;
	int managerPage = 0;
	int salaryScreen = 0;
	int editPage = 0; 

	vector<string> currentUser;
	void payManagerSalaryScreen();
	void showManagerPage();
	void clockInScreen();
	void showClockOut();
	void changeColor(int color);
	void managerPageChoices();
	void editEmployeePage();
	void viewEmployees();
	//void changeEmployeePay();
	string getSystemTime();
	string getCurrentDay(int userNumber);
	void calcuteNetPay(string marriedSingle, double gg);
	//double computeWorkedHours(vector<double> clockOut, vector<double> clockIn);
};

