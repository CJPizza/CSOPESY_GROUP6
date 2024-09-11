#include <iostream>
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
	
	cout << "\n\nHello. Welcome to the CSOPESY Command Line!";
	cout << "\nType 'exit' to quit, 'clear' to clear the screen"; 
	cout << "\n\nEnter a command: ";
}

void userInput(const string& command)
{
	if (command == "initialize")
	{
		cout << "initialize command recognized. Doing something.\n";
	}
	
	else if (command == "screen")
	{
		cout << "screen command recognized. Doing something.\n";
	}
	
	else if (command == "schedule-test")
	{
		cout << "schedule-test command recognized. Doing something.\n";
	}
	
	else if (command == "schedule-stop")
	{
		cout << "schedule-stop command recognized. Doing something.\n";
	}
	
	else if (command == "report-util")
	{
		cout << "report-util command recognized. Doing something.\n";
	}
	
	else if (command == "clear")
	{
		system("clear || cls");
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
