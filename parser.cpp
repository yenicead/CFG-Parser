#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <utility>
#include <queue>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

vector<char> terminals;					// For the terminals (alphabet) of the languages.
vector<char> nonTerminals;				// For the Non-terminals of the grammar.

vector< pair<char, string> > rules; 	// For the rules of the grammers. 

queue <string> states;					// For the words.
queue <string> paths;					// for the word paths. 

// patch is used to convert the int to string.
namespace patch
{
	template < typename T > std::string to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
}

// Breadht First Traversal algorithm to find the terminals of the grammers in language.
int BFS(string state, string path)
{
	// This means that state can be 'S', if it is then print "YES" and return 1.
	if (state.length() == 1)
	{
		cout << "YES" << endl;
		cout << path[0];	// If the program finds the nonterminal then print all the processed paths.
		for (int i = 1; i < path.length(); i++)
		{
			cout << ' ' << path[i];
		}
		cout << endl;
		return 1;
	}

	// Iterate the BFS to number of rule size. This will control all rules for current word.
	for (int i = 0; i < rules.size(); i++)
	{
		int location = state.find(rules[i].second);	// Check if the word can fit the any rule. 			

		if (location != string::npos) // If not end of string
		{
			string tempString = state;
			tempString.replace(location, rules[i].second.length(), &rules[i].first);	// Apply the rule to current word.
			states.push(tempString);													// Push the word to states queue.
			paths.push(path + patch::to_string(i + 1));		// Push the processed rule to paths vector.
		}
	}
	return 0;		// If any rules cannot fit the word, then return 0.
}

// Most effective way to clear all queue
void clearQueue(queue <string> &q)
{
	queue<string> empty;
	swap(q, empty);
}


// Main program
int main()
{
	freopen("grammar.txt", "r", stdin);			// For reading the grammer.txt file.
	freopen("result.txt", "w", stdout);			// For writing the output to result.txt file.
	char tempC;
	string line;
	getline(cin, line);		// Get the first line of grammer.txt

	//Read terminals and push them on terminals vector.	
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] != ' ')		// If line includes a space then ignore it. 
		{
			terminals.push_back(line[i]);
		}
	}

	getline(cin, line);		// Get the second line of grammer.txt

	//Read nonterminals and push them on nonTerminals vector.
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] != ' ')		// If line includes a space then ignore it.  
		{
			nonTerminals.push_back(line[i]);
		}
	}


	getline(cin, line);		// Get the next line from grammer.txt


	//Read rules, rule number = vector location + 1
	for (int i = 0; cin; i++)
	{
		pair <char, string> tempPair;		// Create temporary pair vector.
		tempPair.first = line[2];			// Take the nonterminal letter to the tempPair.first which is char.
		string second;
		for (int j = 7; j < line.size(); j++) 	// It start from 7 cause the rule is start from 7 to end of line.
		{
			if (line[j] != ' ')
			{
				second.push_back(line[j]);		// push the rule to the string.
			}
		}
		tempPair.second = second;			// take the rule to the tempPair.second which is string.
		rules.push_back(tempPair);		// push this temp rule to the rules vector.
		getline(cin, line);					// Take the next line.
	}



	ifstream words;
	words.open("words.txt");	 	// Open the words.txt file.
	string tempPath = "";			// Create temp string.

	// Take line until end of line.
	while (words >> line)
	{
		states.push(line);		// Push the line to the states vector.
		paths.push(tempPath);	// Push the tempPath to the paths vector.
		int result = 0;			// This is used to control the result. 

		while (!states.empty())			//  Continue until states is empty.
		{
			string currentState = states.front();	// Take the first element of the states vector to the currentState
			states.pop();							// Delete the taken element.
			string currentPath = paths.front();		// Take the first element of the paths vector to the currentPath
			paths.pop();							// Delete the taken paths.

			if (BFS(currentState, currentPath) == 1)	// Control with BFS. If result is 1, then this word is for this language.  
			{
				result = 1;
				break;		// Using break, the program take the next word.
			}
		}


		if (result == 0)		// If result is zero, this means that given word is not for this language.
		{
			cout << "NO" << endl;
		}
		clearQueue(states);		// clear states queue for new word.
		clearQueue(paths);		// clear paths queue for new word.
	}
}
