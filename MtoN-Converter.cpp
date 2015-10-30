// MtoN-Converter will prompt the user for a value in one numerical system and convert it to another numerical system, supports up to base 36
// Programmed by Kristopher Rollins

#include <iostream>
#include "math.h"
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

void promptUser(string * m, int * mNumSys, int * nNumSys); 
int mToD(string m, int numSys);
void dToN(int i, string * n, int numSys);
char intToChar(int i);
int charToInt(char i);
void printResults(string m, string n, int mNumSys, int nNumSys);
char userContinue();

void main()
{
	string m = "";
	string n = "";
	int mNumSys;
	int nNumSys;
	int mVal;
	char keepGoing;

	do 
	{
	// prompt user for necessary input values
	promptUser(&m, &mNumSys, &nNumSys);
	// convert input value to decimal
	mVal = mToD(m, mNumSys);
	// convert the decimal representation to n numeral system
	dToN(mVal, &n, nNumSys);
	// print results of conversion
	printResults(m, n, mNumSys, nNumSys);

	// prompts the user for continue conditions 
	keepGoing = userContinue(); 
	
	// user wishes to start over with final result as new starting value
	if (keepGoing == 'a')
	{
		m = n; // store final value in start value
		mNumSys = nNumSys; // store final numeral system as starting numeral system
	}

	// user wishes to start over with all new values and numeral systems
	if (keepGoing == 'd')
		m = ""; // set the starting value to empty

	n = "";

	// quit if user input was f
	}while (keepGoing != 'f');

	return;
}

// mToD converts the string value provided by the user to a decimal value
int mToD(string m, int numSys)
{
	int mVal = 0, cVal = 0;
	// loop through each character in the value
	
	for (unsigned int i = 0; i < m.length(); i++)
	{
		// get the numeral value of the character
		cVal = charToInt(m[i]);
	
		// add the value * radix ^ position value 
		mVal += cVal * int(pow(numSys, (m.length() - i) - 1));
		
	}

	return mVal;
}

// converts a decimal to a string representation in base numSys
void dToN(int cVal, string * n, int numSys)
{
	int p;
	for(p = 0; pow(numSys, p + 1) < cVal; p++)
	{} // finds the highest power of numSys in which cVal is still less than or equal to numSys ^ power
	
	// for loops steps down through all powers of numSys down to 0
	for(int x = p; x > 0; x--)
		{
			if (pow(numSys,x) <= cVal && pow(numSys, x+1) > cVal)
			{
				int i = numSys - 1;
				while (pow(numSys, x) * i > cVal)
				{
					i--;
				}
				
				cVal -= int((pow(numSys,x) * i));
				*n += intToChar(i);
				}
			else
			*n += '0';
	}
	*n += intToChar(cVal);
}

// intToChar accepts an integer value and returns the appropriate char to represent it
char intToChar(int i)
{
	char theList[37] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return theList[i];
}

// charToInt accepts a char and returns the int value that it represents
int charToInt(char i)
{
	i = toupper(i);
	char theList[37] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
	for (int x = 0; x < 37; x++)
	{
		if (theList[x] == i)
			return x;
	}
	return -1;
}

// promptUser prompts the user for a value, and the two numeral systems used in conversion
void promptUser(string * m, int * mNumSys, int * nNumSys)
{
	//if m already has a value then the user has opted to use a previous result or starting value
	if (*m == "")
	{
		cout << "Please input the value that will be converted: ";
		cin >> *m;
		cout << endl << "Please enter the radix used for the value" << endl << "(10 = decimal, 2 = Binary, Hex = 16, up to 36): ";
		cin >> *mNumSys;
	}
	cout << endl << "Please enter the radix for the desired resulting numeral system: ";
	cin >> *nNumSys;
	cout << endl << endl;
	return;

}

// print results prints the resulting conversion
void printResults(string m, string n, int mNumSys, int nNumSys)
{
	cout << m << " in base " << mNumSys << " is converted to " << n << " in base " << nNumSys << endl << endl;
}

// userContinue prompts the user to select a continue operation
char userContinue()
{
	char userInput;
	cout << endl << "MENU: " << endl;
	cout << "[a] Again and use the final value as the starting value" << endl;
	cout << "[s] Again and reuse the previous starting value" << endl;
	cout << "[d] Again with a starting value" << endl;
	cout << "[f] Quit" << endl;
	cin >> userInput;
	return tolower(userInput);
}