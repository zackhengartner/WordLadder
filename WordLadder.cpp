#include "WordLadder.h"
#include <iostream>
#include <fstream>
#include <list>

WordLadder::WordLadder(string lexiconFileName, int len)
{
	// Load the lexicon from the file
	ifstream fin;
	fin.open(lexiconFileName);
	if (fin.fail())
	{
		cout << "Error opening lexicon file: " << lexiconFileName << endl;
		exit(1);
	}
	string word;
	while (fin >> word)
	{
		if (word.length() == len) // only use if length of the start word
		{
			lexicon.insert(word); // insert into the lexicon
		}
	}
}

vector<string> WordLadder::getMinLadder(string start, string end)
{
	list<string> queue; // make the queue a list
	vector<string> ladder, wordsSeen, predecessors; // made a ladder, wordsSeen, and predecessors vector
	queue.push_back(start); // add the starting word to the queue
	wordsSeen.push_back(start); // add the starting word to the list of words seen
	predecessors.push_back(""); // predecessor of the start word is empty
	if (isWord(start) == false || isWord(end) == false) return ladder; 
	while (!queue.empty()) // while there is still something in the queue
	{
		string Qfront = queue.front(); //set Qfront to the front of the queue
		queue.pop_front(); // pop the first item off the queue (this will go in Qfront)
		set<string> neighbors = getNeighbors(Qfront); // get the neighbors of QFront
		//cout << "the amount of neighbors is: " << neighbors.size() << endl;
		for (auto p : neighbors) //iterate through all of the neighbors of Qfront
		{
			if (findInVector(wordsSeen, p) == -1) // if the neighbor is not in the list of words seen
			{
				if (p == end) // if the neighbor is the end word
				{
					wordsSeen.push_back(p); // add the end word to the list of words seen
					predecessors.push_back(Qfront); // set the predecessor of the end word
					auto iterator = p; // set the iterator to the end word
					while (iterator != start) // while the iterator is not the start word
					{
						ladder.push_back(iterator); // add the predecessor to the ladder
						iterator = predecessors[findInVector(wordsSeen, iterator)]; // get the predecessor of the current word
					}
					ladder.push_back(start); // add the start word to the ladder
					return ladder; // return the ladder in reverse order
				}
				else
				{
					queue.push_back(p); // add the neighbor to the queue
					wordsSeen.push_back(p); // add the neighbor to the list of words seen
					predecessors.push_back(Qfront); // set the predecessor of the neighbor
				}
			}
		}
	}	 
	return ladder; // If no ladder is found, return an empty vector
}

int WordLadder::getWordCount()
{
	if (lexicon.empty()) return 0;
	else return lexicon.size();
}

void WordLadder::displayResult(vector<string> sequence)
{
	if (sequence.empty())
	{
		cout << "Word Ladder is empty - No Solution\n";
	}
	else
	{
		cout << "A Shortest Word Ladder (" << sequence.size()-1 << " steps) is: ";
		for (int i = sequence.size() - 1; i >= 0; i--) // Display the ladder in reverse order
		{
			cout << sequence[i] << " ";
		}
	}
}

int WordLadder::findInVector(vector<string> vec, string str)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == str) return i; 
	}
	return -1; 

}

bool WordLadder::isWord(string str)
{
	if (lexicon.find(str) != lexicon.end()) return true; // The word is found in the lexicon
	else return false; // The word is not found in the lexicon
}

bool WordLadder::isWordLadder(vector<string> sequence)
{
	if (sequence.empty()) return false; // If the sequence is empty, return false
	if (sequence.size() < 2) return false; // If the sequence has less than 2 words, return false
	for (int i = 0; i < sequence.size() - 1; i++)
	{
		if (getHammingDistance(sequence[i], sequence[i + 1]) != 1) return false; // Check if the Hamming distance is 1
		if (!isWord(sequence[i])) return false; // Check if the word is in the lexicon
	}
	return true;
}	

set<string> WordLadder::getNeighbors(string word)
{
	set<string> neighbors;
	for (auto p : lexicon)
	{
		if (getHammingDistance(word, p) == 1) neighbors.insert(p);
	}
	return neighbors;
}

int WordLadder::getHammingDistance(string str1, string str2)
{
	int hamming = 0;
	if (str1.length() == str2.length())
	{
		for (int i = 0; i < str1.length(); i++)
		{
			if (str1[i] != str2[i])
			{
				hamming++; // Hamming distance of 1
			}
		}
		return hamming;
	}
	else return -1;
}
