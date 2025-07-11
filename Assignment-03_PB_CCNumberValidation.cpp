/****************************************************************
*
 * File: Assignment-01_PB_CCNumberValidation.cpp
 * By: Liecie Salvador
 * Date: 7-10-25
 *
 * Description: This program implements a system which checks
 * the validity of a credit card number.
 *
 ****************************************************************/
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;


bool isvalidcc(const string&);

int main()
{
	//
	// PLEASE DO NOT CHANGE function main
	//
	vector<string> cardnumbers = {
		 "371449635398431", "4444444444444448", "4444424444444440", "4110144110144115",
		"4114360123456785", "4061724061724061", "5500005555555559", "5115915115915118",
		"5555555555555557", "6011016011016011", "372449635398431", "4444544444444448",
		"4444434444444440", "4110145110144115", "4124360123456785", "4062724061724061",
		"5501005555555559", "5125915115915118", "5556555555555557", "6011116011016011",
		 "372449635397431", "4444544444444448", "4444434444544440", "4110145110184115",
		"4124360123457785", "4062724061724061", "5541005555555559", "5125115115915118",
		"5556551555555557", "6011316011016011"
	};

	int i;
	vector<string>::iterator itr;

	for (i = 1, itr = cardnumbers.begin(); itr != cardnumbers.end(); ++itr, i++) {
		cout << setw(2)  << i << " " 
			 << setw(17) << *itr 
			 << ((isvalidcc(*itr)) ? " is valid" : " is not valid") << endl;
	}

	return 0;
}

bool isvalidcc(const string& ccString) { // Function to check credit card number

	int sumDouble = 0;
	int sumOdd = 0;
	int digit;

	for (int i = 0; i < ccString.length(); i++) {
		digit = ccString[i] - '0';
		int position = ccString.length() - i;

		if (position % 2 == 0) { // Checking if position in line is even
			digit = digit * 2;
			if (digit > 9) {
				digit = (digit / 10) + (digit % 10); // Add the digits together
			}
			sumDouble = sumDouble + digit; // Add all even
		} else {
			sumOdd = sumOdd + digit; // Add all odd
		}
	}

	int result = sumDouble + sumOdd;
	return (result % 10 == 0); // Checks if divisible by 10
}