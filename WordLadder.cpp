// WordLadder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//WordLadder owl.txt clash clown
//WordLadder owl.txt clash ZZZZZ
//Wordladder Tiny.txt cat zzz
#include <iostream>
#include <string>
#include <fstream>
#include "WordLadder.h" // Assuming HUFF.h contains the definition of the HUFF class and its methods

using namespace std;

void toUpper(string& word);

int main(int argc, char* argv[])
{
	if (argc != 4) { cout << "there is not 4 arguements like required\n"; return 1; }
	//need to fine the lengths of the first and last words in the ladder
	string start = argv[2];
	string end = argv[3];
	if (start.length() != end.length()) { cout << "the first and last words must be the same length.\n"; return 1;}
	string lexiconFileName = argv[1];
	toUpper(start); toUpper(end); // convert the words to upper case
	cout << start << " to " << end << endl;
	WordLadder ladder(lexiconFileName, start.length());
	ladder.displayResult(ladder.getMinLadder(start, end));
}

void toUpper(string& word)
{
	for (int i = 0; i < word.length(); i++)
	{
		word[i] = toupper(word[i]);
	}
}
//	Make the start and end words upper - case
//	Get the result from getMinLadder(start, end);
//Display the contents of the result with displayResult().
