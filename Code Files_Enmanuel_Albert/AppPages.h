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

class AppPages{
private:
	string appName; // this is the tag name for the class
	vector<string> currentUser;
	vector<string> commaDelimetedString(string ll,char limit); // this method is use to get values from the text file
	vector<int> commaDelimetedInt(string ll, char limit); // this method is use to get values from the text file
	vector<int> clockInInfo;
	vector<int> clockOutInfo;
	

	double computeWorkedHours(vector<int> clockOut, vector<int> clockIn);
public:
	string name = appName;
	AppPages(string name);

	int loginCounter = 1;
	int logInChoice = 0;
	int logInManager = 0;
	int logInEmployee = 0;
	int firstTimeLogin = 0;

	vector<string>user;

	void showMainPage();
	void exitPage();
	void showLogInPage();
	void showRegisterPage();
	void changeColor(int color);
	void loginCheck(string username, string password);
	string getCurrentDay(int userNumber);
	double computeWorkedHours(vector<double> clockOut, vector<double> clockIn);
	//void updateField(string lineToChange,int pos,string data,string  fromF, string toF);
};

