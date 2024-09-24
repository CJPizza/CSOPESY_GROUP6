#include <cstdio>
#include <iostream>
#include <ostream>
#include <windows.h>
#include <string>
#include <sstream>
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
	cout << "Type 'exit' to quit, 'clear' to clear the screen" << endl;
	SetConsoleTextAttribute(color, 7);
	cout << "Enter a command: ";
}

void userInput(const string& sInput)
{

  // uses stringstream to slice input into substring
  stringstream s_in(sInput);

  string command;
  string param;
  string name;

  // assumes command parameter will only be one use while loop if more than one
  s_in >> command;
  s_in >> param;

  cout << command << std::endl;

  cout << param;

	if (command == "initialize")
	{
		cout << "initialize command recognized. Doing something.\n";
		cout << "\nEnter a command: ";
	}

	else if (command == "screen")
	{
		cout << "initialize command recognized. Doing something.\n";
    if (param == "-s") {
      s_in >> name;
    } else if (param == "-r") {
      cout << "screen -r command";
    
    } else if (param =="-ls") {
      cout << "screen -ls command";
    }
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
	string sInput;
	printHeader();
	
	while (true)
	{
		getline(cin, sInput);
		userInput(sInput);
	}
	
	return 0;
}

