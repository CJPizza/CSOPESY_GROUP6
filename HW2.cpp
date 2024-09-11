#include <iostream>
#include <windows.h>
#include <string>
#include <cstdlib>
using namespace std;

void printHeader()
{
	cout << "  ____ ____   ___  ____  _____ ______   __";
	cout << "\n";
	cout << " / ___/ ___| / _ \\|  _ \\| ____/ ___\\ \\ / /";
	cout << "\n";
	cout << "| |   \\___ \\| | | | |_) |  _| \\___ \\\\ V / ";
	cout << "\n";
	cout << "| |___ ___) | |_| |  __/| |___ ___) || |";
	cout << "\n";
	cout << " \\____|____/ \\___/|_|   |_____|____/ |_|";
	cout << "\n                  GROUP 6";
	
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 10);
	cout << "\n\nHello. Welcome to the CSOPESY Command Line!" << endl;
	SetConsoleTextAttribute(color, 14);
	cout << "\nType 'exit' to quit, 'clear' to clear the screen" << endl;
	SetConsoleTextAttribute(color, 7);
	cout << "\n\nAvailable commands: intialize, screen, scheduler-test, scheduler-stop, report-util" << endl;
	cout << "\n\nEnter a command: ";
}

void userInput(const string& command)
{
	if (command == "initialize")
	{
		cout << "initialize command recognized. Doing something.\n";
		cout << "\nEnter a command: ";
	}
	
	else if (command == "screen")
	{
		cout << "screen command recognized. Doing something.\n";
		cout << "\nEnter a command: ";
	}
	
	else if (command == "scheduler-test")
	{
		cout << "scheduler-test command recognized. Doing something.\n";
		cout << "\nEnter a command: ";
	}
	
	else if (command == "scheduler-stop")
	{
		cout << "scheduler-stop command recognized. Doing something.\n";
		cout << "\nEnter a command: ";
	}
	
	else if (command == "report-util")
	{
		cout << "report-util command recognized. Doing something.\n";
		cout << "\nEnter a command: ";
	}
	
	else if (command == "clear")
	{
		system("CLS");
		printHeader();
	}
	
	else if (command == "exit")
	{
		cout << "exit command recognized. Doing something.\n";
		exit(0);
	}
	
	else
	{
		cout << "Unknown command.";
		cout << "\n\nEnter a command: ";
	}
}

int main()
{	
	string command;
	printHeader();
	
	while (true)
	{
		getline(cin, command);
		userInput(command);
	}
	
	return 0;
}

