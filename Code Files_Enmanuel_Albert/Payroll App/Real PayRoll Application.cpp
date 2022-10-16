/*
		Group Members: Albert, Enmanuel, John, Kayla, Nicholas
		Date: 4/26/2022

		Payroll Application
		-This application will calculate hourly, monthly, and yearly pay for the managers/employees
		- Managers can only register to the software 
		- Mangers creates employees and employees login credentials

		Programmers: Enmanuel Proano, Albert Ang
		Tax Algorithm: Nicholas Taormina

*/

// import all libraries needed ========================================================================================
#include <iostream>
#include <iomanip>
#include <Math.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <conio.h>
#pragma warning(disable : 4996) // so that we can use getch
#include "AppPages.h"
#include "EmployeePages.h"
#include "ManagerPages.h"
#undef max
using namespace std;
// ======================================================================================================================

int main(){

	bool programRun = true;
	


	// changing the font size to become more legible
	static CONSOLE_FONT_INFOEX fontex;
	fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetCurrentConsoleFontEx(hOut, 0, &fontex);
	fontex.FontWeight = 500;
	fontex.dwFontSize.X = 30;
	fontex.dwFontSize.Y = 30;
	SetCurrentConsoleFontEx(hOut, NULL, &fontex);

	AppPages myApp("Awaken Payroll Application"); // this constructor from the AppPages class names the application

	// makes sure the program runs
	while (programRun == true) {

		
		EmployeePages employee;
		ManagerPages manager;
		myApp.showMainPage();
		myApp.logInEmployee = 0;
		myApp.logInManager = 0;
		myApp.firstTimeLogin = 0;

		if (myApp.logInChoice == 1) { // based on the choices from the myApp class, will call other functions

			myApp.showLogInPage();

			while (myApp.logInManager == 1) { // the manager functions
				int exitChoice = 0;
				int manager_choice = 0;
				manager.currentUser = myApp.user;
				
				// the manager choices displayed and must be selected by user
				while (manager_choice < 1 || manager_choice > 4 && manager.managerPage == 1) {
					manager.showManagerPage();
					cin >> manager_choice;
					cout << "" << endl;
					if (!cin) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Please enter a valid input" << endl;
						getch();
						continue;
					}
					else {
						manager.managerPage = 0;
						break;
					}
				}

				if (manager_choice == 1) {

					manager.clockInScreen();
					break;

				}


				if (manager_choice == 2) { // manager choices of adding or editing employee or exiting
					manager.managerPageChoices();
					if (manager.editPage == 1) {
						manager.editEmployeePage();
						manager.editPage = 0;
					}
				}
				if (manager_choice == 3) { // the salary of employee
					manager.payManagerSalaryScreen();
					manager.salaryScreen = 0;
				}

				if (manager_choice == 4) { // view all the employees made
					manager.viewEmployees();
				}

				if (manager_choice == 5) {
					// show the main page (log out)
					cout << "Are you sure you want to exit?" << endl;
					cout << "(1): Yes" << endl;
					cout << "(2): No" << endl;
					cin >> exitChoice;

					if (exitChoice == 1) {
						break;
					}
					if (exitChoice == 2) {
						continue;
					}

				};
				

			}

			// the employee functions
			if (myApp.logInEmployee == 1) {
				employee.currentUser = myApp.user;
				
				employee.showEmployeePage();
				if (employee.returnToMain == 1) {
					myApp.logInEmployee == 0;
				}

			}

			// first time employee setup
			if (myApp.firstTimeLogin == 1) {
				employee.currentUser = myApp.user;
				employee.showOneTime();
			}

		} 

		// registering a new manager
		if (myApp.logInChoice == 2) {
			myApp.showRegisterPage();

		}

		if (myApp.logInChoice == 3) { // exits the programm
			
			myApp.exitPage();
			programRun = false;
			
		}
	}
}

