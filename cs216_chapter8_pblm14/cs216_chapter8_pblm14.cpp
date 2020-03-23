/*
Programmer: Kyle Absten
Date: 03/17/2020
Description: This program will simulate a drink machine.  DrinkMachine class is an object that replicates a vending machine.  Main function creates a DrinkMachine
object.
*/

#include <iostream>
#include <iomanip>
using namespace std;

class DrinkMachine {  // Class declaration

	struct DrinkType {  // Struct to hold drink type info
		string drinkName; //String; Name of drink
		double cost;  //Double; Cost of 1 drink
		int amntAvailable;  //Int; Quantity in the machin
	};


private:
	DrinkType inventory[5] = { {"Cola", 1.00, 20}, {"Root beer", 1.00, 20}, {"Orange soda", 1.00, 20}, //An array of 5, with initilization values
	{"Grape soda", 1.00, 20}, {"Bottled water", 1.50, 20} };
	double userBalance;  //Double; current balance of money input by customer
	double salesTotal;  //Double; total amount of sales

	void inputMoney(int);  //Private Member function prototype; takes an int; returns void
	void dailyReport();  //Private member function prototype; takes no arguments, returns void
	char validResponse();  //Private Member function prototype; takes to arguments; returns a character

public:

	DrinkMachine(); //Constructor prototype
	~DrinkMachine(); //Destructor prototype

	void displayChoices(); // Public member function prototype; takes no arguments and returns void

	void buyDrink(int drinkChoice);  //Public member function prototype; takes an int; returns void

	double getBalance() {  //Public member get function prototype; takes no arguments; returns an double
		return userBalance;
	}



};

int validateChoice(int); //Function prototype;  takes int; returns int

//Main function call

int main() {

	DrinkMachine drinkMachine;  //The DrinkMachine class object
	int selection;  //Int; users selection
	do //Loop
	{
		drinkMachine.displayChoices();//Call object member function; displays the menu
		selection = validateChoice(6);//Call the validateChoice function to make sure the response is in range; argument is the largest menu choice
		if (selection != 6) { //If selection is not exit
			drinkMachine.buyDrink(selection - 1); //Call the object buyDrink function; offset by 1 to accomodate for 0 start of array
		}

	} while (selection != 6);//Until the selection is 6

	if (drinkMachine.getBalance() > 0) { //If the remaining balance is not 0
		cout << "Here is your change $" << drinkMachine.getBalance() << endl;//Give the user their money back.
	}

	return 0;
}

//DrinkMachine class implementation code

DrinkMachine::DrinkMachine() {  //Constructor; sets balance to 0
	userBalance = 0;
	salesTotal = 0;
}

DrinkMachine::~DrinkMachine() {  //Destructor
	dailyReport();
}

void DrinkMachine::buyDrink(int drinkChoice) { //Public member function; takes an int and returns void

	char confirm; //Character; yes or no confrimation
	int decision;  //Int; 1 or 2 decision making

	if (inventory[drinkChoice].amntAvailable < 1) { //If there are no more drinks, say sorry and return to main menu.
		cout << "Sorry, we are sold out of " << inventory[drinkChoice].drinkName << ".\n";
		return;
	}
	while (userBalance < inventory[drinkChoice].cost) {// Not enough money for purchase
		cout << "You have not input enough money to make that purchase.\n";
		cout << "What would you like to do?\n";

		cout << "1. Make a deposit.\n";
		cout << "2. Cancel selection\n";

		cin >> decision;  //Take user decision input

		while (decision != 1 && decision != 2) {  //Validate decision input
			cout << "That is not a valid response\n";
			cout << "1. Make a deposit.\n";
			cout << "2. Cancel selection\n";
		}

		if (decision == 1) {//User has decided to make a deposit
			inputMoney(drinkChoice);  // Call input money function
		}
		else if (decision == 2) {//User has decided to cancel the purchase.  Exit the function
			return;
		}
	}
	
	cout << "Would you like to confirm your purchase of 1 " << inventory[drinkChoice].drinkName << "? (Y/N)";  //User has enough money, do they still want to make the purchase
	confirm = validResponse();  //Call the valid response function to make sure their response is a y or no

	if (confirm == 'Y' || confirm == 'y') {//User has responded y
		cout << "Here is your " << inventory[drinkChoice].drinkName << endl; //Deliver their drink
		inventory[drinkChoice].amntAvailable -= 1; //Update the quantity of the drink available
		salesTotal += inventory[drinkChoice].cost;
		userBalance -= inventory[drinkChoice].cost;  //Update the balance of the current user
		cout << "Your remaining balance is $" << userBalance << endl << endl;//inform the user of their remaining balance
	}

}

void DrinkMachine::displayChoices() {//This public member function displays the menu
	
	cout << "Please make a selection:\n";

	for (int selection = 0; selection < 5; selection++) {//Loop throught the five structs in the inventory array
		cout << fixed << setprecision(2);
		cout << selection + 1 << ": " << inventory[selection].drinkName << " $" << inventory[selection].cost << endl;//Print the name and price of the current drink
	}
	cout << "6: Quit and get change.\n";  //Give the user the option to be done and get their change.
}

void DrinkMachine::inputMoney(int drinkChoice) {//Private member function for depositing money
	double deposit;  //Double; amount to deposit
	cout << "Your selection costs $" << inventory[drinkChoice].cost << endl;
	cout << "Your current balance is $" << userBalance << endl;
	cout << "How much would you like to deposit? $";
	cin >> deposit;  // Read the users amount to deposit
	cin.ignore();
	userBalance += deposit;  //Update the balance to account for the deposit
		
}

void DrinkMachine::dailyReport() { //Member function to report remaining stock and sales total
	cout << "Remaining inventory:\n";
	for (int drink = 0; drink < 5; drink++) { //Loop through array of structs
		cout << drink + 1 << ". " << inventory[drink].drinkName << ":  " << inventory[drink].amntAvailable << endl;//Print remaining number for each object
	}

	cout << "Total sales: $" << salesTotal; //Print sales total
}

char DrinkMachine::validResponse() { //Member function to make sure response is either y or n
	char response;  //Character; users respone
	response = cin.get();  //Record user response
	cin.ignore();  //Ignore the new line character
	while (response != 'y' && response != 'Y' && response != 'n' && response != 'N') {  //Loop until response is either y or n
		cout << "That is not a valid response.  Please respond with 'Y' or 'N' ";
		response = cin.get();
		cin.ignore();
	}
	return response;  //Return the character of either y or n
}

//Function

int validateChoice(int maximum) {  //Function to validate menu choice.

	int selection;  //Int; users selection
	cin >> selection;  //Record users selection
	cin.ignore();  //Ignore the new line character

	while (selection < 1 || selection > maximum) {  //Loop until the selection is in range
		cout << "Sorry that is not a valid selection.  Please try again: ";
		cin >> selection;
		cin.ignore();
	}
	return selection;  //Return the valid response
}





