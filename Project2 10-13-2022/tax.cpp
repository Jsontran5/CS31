#include <iostream>
using namespace std;
#include <string>

int main()
{
	cout << "Name: "; //ask user for name
	string name;
	getline(cin, name);
	if (name == "") //if provided an empty string, prompt an error and end the program.
	{
		cout << "---" << endl;
		cout << "You must enter a name" << endl;

		return 1;
	}


	cout << "Taxable income: "; //ask user for their income
	double income;
	cin >> income;
	cin.ignore(10000, '\n');
	if (income < 0) //check to see if they provided a negative income, and exit if they do.
	{
		cout << "---" << endl;
		cout << "The taxable income must not be negative" << endl;

		return 2;
	}



	cout << "Occupation: "; //ask user of occupation
	string occupation;
	getline(cin, occupation);
	if (occupation == "") //if they provide nothing, then exit the program
	{
		cout << "---" << endl;
		cout << "You must enter an occupation" << endl;

		return 3;
	}


	cout << "Number of children: "; //ask for children
	int children;
	cin >> children;
	if (children < 0) //if they provide a negative number, then exit the program
	{
		cout << "---" << endl;
		cout << "The number of children must not be negative" << endl;

		return 4;
	}

	double tax1 = 0; //intiate the tax for the 3 brackets
	double tax2 = 0;
	double tax3 = 0;

	//1st bracket tax calculation
	if (income >= 55000 || income < 55000) //to make sure that despite the income being over 55000, they still get taxed by the 1st bracket
	{
		if (income <= 55000)
		{
			tax1 = income * .04;
		}
		else // we know that if their income is above 55000, the tax for the 1st bracket will always be the same
		{
			tax1 = 55000 * .04;
		}
	}

	//2nd bracket tax calculation
	if (income <= 125000 || income > 125000) //to make sure that despite the income being over 125000, they still get taxed.
	{
		if (income > 125000) // we know that if their income is above 55000, the tax for the 2nd bracket will always be the same
		{
			if (occupation == "nurse" || occupation == "teacher") //different rates for teacher and nurse
			{
				tax2 = 70000 * .05;
			}
			else
			{
				tax2 = 70000 * .07;
			}
		}
		else if (income <= 125000 && income > 55000) //checks if their income is between the 2nd bracket
		{
			double tax2income = income - 55000; //captures only the income that is subjected to the 2nd bracket.
			if (occupation == "nurse" || occupation == "teacher")
			{
				tax2 = tax2income * .05;
			}
			else
			{
				tax2 = tax2income * .07;
			}
		}

	}

	//3rd bracket tax calculation
	if (income > 125000) 
	{
		double tax3income = income - 125000; //captures only the income subjected to the 3rd bracket.
		tax3 = tax3income * .093;

	}

	double unreducedTax = tax1 + tax2 + tax3; //tax from all 3 brackets that isn't subjected to the kid discount yet
	double finalTax = 0;
	cout.setf(ios::fixed);
	cout.precision(2);

	if (income < 125000) //check to see if they qualify for the reduction based on their INCOME.
	{
		double reduction = 200 * children; //how much the tax gets reduced
		finalTax = unreducedTax - reduction;

		if (finalTax <= 0) //if the tax is lower than or 0, it will always output 0.00
		{
			cout << "---" << endl;
			cout << name << " would pay $0.00" << endl;

			return 0;
		}
		else
		{
			cout << "---" << endl;
			cout << name << " would pay $" << finalTax << endl;

			return 0;
		}
	}
	else //if they aren't subjected to the kid reduction than their tax stays the same.
	{
		finalTax = unreducedTax;
		cout << "---" << endl;
		cout << name << " would pay $" << finalTax << endl;

		return 0;
	}

}
