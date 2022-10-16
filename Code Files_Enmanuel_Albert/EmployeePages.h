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

class EmployeePages {
private:
	
	vector<string> commaDelimetedString(string ll, char limit); // this method is use to get values from the text file
	vector<int> commaDelimetedInt(string ll, char limit); // this method is use to get values from the text file
	vector<int> clockInInfo;
	vector<int> clockOutInfo;

	void calcuteNetPay(string marriedSingle, double gg);
	//double computeWorkedHours(vector<int> clockOut, vector<int> clockIn);

public:

	int returnToMain = 0;
	int clockIn = 0;
	int clockOut = 0;
	vector<string> currentUser;
	void clockInScreen();
	void payEmployeeSalaryScreen();
	void showOneTime();
	void showEmployeePage(); 
	void showClockOut();
	void changeColor(int color);
	string getSystemTime();
	string getCurrentDay(int userNumber);
	//double computeWorkedHours(vector<double> clockOut, vector<double> clockIn);
};

