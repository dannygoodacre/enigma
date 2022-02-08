#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/* path of letter through the machine:
	keyboard -> plugboard -> right rotor -> middle rotor -> left rotor -> reflector -> left rotor -> middle rotor -> right rotor -> plugboard -> display
*/

// rotor and reflector swaps in cyclic notation (index n represents (n+1)th rotor)
const vector<string> rotors[8] = { {"AELTPHQXRU","BKNW","CMOY","DFG","IV","JZ","S"}, 
								 {"FIXVYOMW","CDKLHUP","ESZ","BJ","GR","NT","A","Q"}, 
								 {"ABDHPEJT","CFLVMZOYQIRWUKXSG","N"}, 
								 {"AEPLIYWCOXMRFZBSTGJQNH","DV","KU"}, 
								 {"AVOLDRWFIUQ","BZKSMNHYC","EGTJPX"}, 
								 {"AJQDVLEOZWIYTS","CGMNHFUX","BPRK"}, 
								 {"ANOUPFRIMBZTLWKSVEGCJYDHXQ"}, 
								 {"AFLSETWUNDHOZVICQ","BKJ","GXY","MPR"} };

// index 0 = A, 1 = B, 2 = C
const vector<string> reflectors[3] = { {"AE","BJ","CM","DZ","FL","GY","HX","IV","KW","NR","OQ","PU","ST"},
									   {"AY","BR","CU","DH","EQ","FS","GL","IP","JX","KN","MO","TZ","VW"},
								       {"AF","BV","CP","DJ","EI","GO","HY","KR","LZ","MX","NW","TQ","SU"} };

// nth index represents (n+1)th rotors double stepping points
// when the rotor ticks into these positions, the left adjacent rotor ticks once
const vector<int> doubleSteps[8] = { {17},{5},{22},{10},{0},{0,13},{0,13},{0,13} };

string rotorPositions[] = { "Left", "Middle", "Right" };
int possibleRotorChoices[] = { 1,2,3,4,5,6,7,8 };

// L M R
int chosenRotors[3]; 
int rotorSettings[3]; 
int ringSettings[3]; 

int initialRotorSettings[3];
int initialRingSettings[3];

int chosenReflector;

vector<string> plugboardPairs({"##", "##", "##", "##", "##", "##", "##", "##", "##", "##", "##", "##", "##"});

// clears cin buffer
void clearBuffer()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// returns a (mod b), requires b > 0
int mod(int a, int b)
{ 
	a %= b;

	while (a < 0)
	{
		a += b;
	}

	return a;
}

// gets which reflector from user
int getReflectorChoice()
{
	string choice;
	bool valid = false;

	while (!valid)
	{
		cout << "Reflector: ";
		cin >> choice;
		transform(choice.begin(), choice.end(), choice.begin(), toupper);

		if (choice.length() > 1 || (int)choice[0] < 65 || (int)choice[0] > 67) // must be either A, B, or C
		{
			cout << "\nInvalid choice\n\n";
		}
		else // valid choice
		{
			valid = true;
		}
	}

	cout << endl;
	return (int)choice[0] - 65;
}

// gets which rotors go in which positions (L M R) from user
void getRotorChoices()
{
	int i = 0;
	for (string rotor : rotorPositions)
	{
		bool valid;
		do
		{
			string choice;
			cout << rotor + " rotor choice: ";
			getline(cin, choice);

			// these will point to the end of the array if not found
			int *locationInPossibleChoices = find(begin(possibleRotorChoices), end(possibleRotorChoices), (int)choice[0] - 48); // pointer of choice in possible choices
			int *locationInAlreadyChosen = find(begin(chosenRotors), end(chosenRotors), (int)choice[0] - 48); // pointer of choice in already chosen
			
			if (choice.length() != 1 || choice[0] < 49 || choice[0] > 56 || locationInPossibleChoices == end(possibleRotorChoices)) // can only be from 1-8
			{
				cout << "\nInvalid choice\n";
				valid = false;
			}
			else if (locationInAlreadyChosen != end(chosenRotors)) // rotor already chosen
			{
				cout << "\nThat rotor has already been chosen for another position\n";
				valid = false;
			}
			else // valid choice
			{
				chosenRotors[i] = (int)choice[0]-48;
				valid = true;
			}

			cout << endl;
		} while (!valid);

		i++;
	}
}

// gets ring and rotor settings from user
int* getSettings(string settingName)
{
	static int tempSettings[3]; // temporarily stores settings to which the function can return a pointer

	int i = 0;
	for (string rotor : rotorPositions)
	{
		bool valid;
		do
		{
			cout << rotor + " " + settingName + " setting: ";
			string s;
			getline(cin, s);

			char setting = toupper(s[0]); // get first character as uppercase
			int settingValue = (int)setting - 65; // stored as 0-25

			if (s.length() != 1 || settingValue < 0 || settingValue > 25) // input string is longer than 1 or not in A-Z
			{
				cout << "\nInvalid choice\n";
				valid = false;
			}
			else // valid input
			{
				tempSettings[i] = settingValue;
				valid = true;
			}

			cout << endl;
		} while (!valid);

		i++;
	}

	return tempSettings;
}
	
// calls getSettings and stores values in arrays for ring and rotor settings
void storeSettings() 
{
	int* p = getSettings("ring");
	for (int i = 0; i < 3; i++)
	{
		ringSettings[i] = *(p + i);
		initialRingSettings[i] = *(p + i);
	}
	int* q = getSettings("rotor");
	for (int i = 0; i < 3; i++)
	{
		rotorSettings[i] = *(q + i);
		initialRotorSettings[i] = *(q + i);
	}
}

// gets plugboard pairs from user
void getPlugboardPairs()
{
	int num; //number of plugboard pairs
	bool valid;

	do
	{
		cout << "Number of plugboard pairs: ";
		cin >> num;

		if ((cin.good() && !(num < 0 || num > 13))) // ensures choice is an integer and from 0-13
		{
			valid = true;
		}
		else
		{
			//cin.clear();
			//cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nInvalid choice\n\n";
			valid = false;
		}
	} while (!valid);

	for (int i = 1; i <= num; i++)
	{
		valid = false;

		do
		{
			string p; // inputted pair
			cout << "\nPair " << i << ":";
			cin >> p;
			transform(p.begin(), p.end(), p.begin(), toupper);

			if (p.length() == 2 && (int)p[0] > 64 && (int)p[0] < 91 && (int)p[1] > 64 && (int)p[1] < 91) // must be a pair of characters in A-Z
			{
				for (string pair : plugboardPairs) // checks if any letters in the pair have already been chosen
				{
					if (pair.find(p.at(0)) != string::npos || pair.find(p.at(1)) != string::npos) // letter found
					{
						cout << "\nOne or both of those letters has already been chosen for another pair\n";
						valid = false;
						break;
					}
					else // valid choice
					{
						valid = true;
					}
				}

				if (valid)
				{
					plugboardPairs.at(i - 1) = p;
				}
			}
			else // invalid choice
			{
				cout << "\nInvalid choice\n\n";
				valid = false;
			}



		} while (!valid);
	}
}

// used to swap letters as they pass between rotors (from the first rotor to the second
// As = first rotor setting, Ar = first rotor ring setting, Bs =  Second rotor setting,  Br = Second rotor ring setting
char swapBetween(char x, int As, int Ar, int Bs, int Br)
{
	return mod((int)x - 65 + (Ar - As) - (Br - Bs), 26) + 65;
}

// performs letter swap within rotor (and reflector, the value of isMovingTowardsReflector makes no difference)
char swapWithin(char x, bool isMovingTowardReflector, vector<string> rotor)
{
	int index = 0, len = 0;
	string cycleWithInput; // the cycle we want

	for (string cycle : rotor)
	{
		auto a = find(cycle.begin(), cycle.end(), x); // looks for letter in all cycles

		if (a != cycle.end()) // if letter found in a cycle
		{
			index = distance(cycle.begin(), a); // index of letter in cycle
			len = cycle.length(); // number of letters in cycle
			cycleWithInput = cycle;
			break;
		}
	}

	if (isMovingTowardReflector)
	{
		return cycleWithInput[mod(index + 1, len)];
	}
	else
	{
		return cycleWithInput[mod(index - 1, len)];
	}
}

// swaps letters using plugboard
char plugboardSwap(char x)
{
	bool found = false;
	string pairContainingLetter;
	int index;

	for (string pair : plugboardPairs)
	{
		int location = pair.find(x); // 0 or 1
		if (location != string::npos) // pair contains letter
		{
			found = true;
			pairContainingLetter = pair;
			index = location;
			break;
		}	
	}

	if (!found) // letter not found in plugboard, so returns original letter
	{
		return x;
	}
	else
	{
		return pairContainingLetter[1 - index]; // if location is 1, then return at 0, and vice versa
	}
}

// handles rotor ticking with letters being entered
void doubleSteppingMechanism()
{
	rotorSettings[2]++; // right rotor ticks with every letter

	if (rotorSettings[2] == 26) // right rotor full rotation, ticks middle rotor
	{
		rotorSettings[2] = 0;
		rotorSettings[1]++;
	}
	if (rotorSettings[1] == 26) // middle rotor full rotation, ticks left rotor
	{
		rotorSettings[1] = 0;
		rotorSettings[0]++;
	}
	if (rotorSettings[0] == 26) // left rotor full rotation
	{
		rotorSettings[0] = 0;
	}

	for (int j = 2; j > 0; j--)
	{
		for (int i = 0; i < 8; i++)
		{
			if (chosenRotors[j] == i+1 && find(begin(doubleSteps[i]), end(doubleSteps[i]), rotorSettings[j]) != end(doubleSteps[i])) // checks if the middle and right rotors are in the setting to double step
			{
				rotorSettings[j-1]++; // tick left adjacent rotor
			}
		}
	}
}

// encrypts/decrypts given letter
char encrypt(char letter)
{
	doubleSteppingMechanism();

	letter = plugboardSwap(letter); // plugboard
	letter = swapBetween(letter, 0, 0, rotorSettings[2], ringSettings[2]); // static rotor (from plugboard) to right rotor
	letter = swapWithin(letter, true, rotors[chosenRotors[2]]); // right rotor
	letter = swapBetween(letter, rotorSettings[2], ringSettings[2], rotorSettings[1], ringSettings[1]); // right rotor to middle rotor
	letter = swapWithin(letter, true, rotors[chosenRotors[1]]); // middle rotor
	letter = swapBetween(letter, rotorSettings[1], ringSettings[1], rotorSettings[0], ringSettings[0]); // middle rotor to left rotor
	letter = swapWithin(letter, true, rotors[chosenRotors[0]]); // left rotor
	letter = swapBetween(letter, rotorSettings[0], ringSettings[0], 0, 0); // left rotor to reflector
	letter = swapWithin(letter, true, reflectors[chosenReflector]); // reflector
	letter = swapBetween(letter, 0, 0, rotorSettings[0], ringSettings[0]); // reflector to left rotor
	letter = swapWithin(letter, false, rotors[chosenRotors[0]]); // left rotor
	letter = swapBetween(letter, rotorSettings[0], ringSettings[0], rotorSettings[1], ringSettings[1]); // left rotor to middle rotor
	letter = swapWithin(letter, false, rotors[chosenRotors[1]]); // middle rotor
	letter = swapBetween(letter, rotorSettings[1], ringSettings[1], rotorSettings[2], ringSettings[2]); // middle rotor to right rotor
	letter = swapWithin(letter, false, rotors[chosenRotors[2]]); // right rotor
	letter = swapBetween(letter, rotorSettings[2], ringSettings[2], 0, 0); // right rotor to static rotor (plugboard)
	letter = plugboardSwap(letter); // plugboard

	return letter;
}

int main() // TODO: fix integer input validation for menu choice
{
	cout << string(100, '\n');

	// initial setup
	getReflectorChoice();
	clearBuffer();
	getRotorChoices();
	storeSettings();
	getPlugboardPairs();
	clearBuffer();

	cout << string(100, '\n');

	string choice;
	bool exit = false;
	while (!exit)
	{
		cout << "\n1 - encrypt/decrypt a word or phrase\n"
			"2 - reset to initial settings\n"
			"3 - change initial settings and rotors\n"
			"4 - change plugboard pairs\n"
			"5 - exit\n\n"
			"Choice: ";

		cin >> choice;
		
		if ((int)choice[0] < 49 || (int)choice[0] > 53) // choice not 1-5
		{
			cout << string(100, '\n') << "Invalid choice\n";
		} 
		else
		{
			switch ((int)choice[0]-48)
			{
				case 1: // encrypt/decrypt
				{
					string phrase;
					bool valid;
					do
					{
						valid = true;
						cout << "Word or Phrase: ";
						cin >> phrase;
						transform(phrase.begin(), phrase.end(), phrase.begin(), toupper); // allow lowercase letters and make them uppercase

						for (size_t i = 0; i < phrase.length(); i++) // checks input is only A-Z by looking at each letter
						{
							if (!isalpha(phrase[i]))
							{
								cout << string(100, '\n') << "Invalid input - input must only contain A-Z\n\n";
								valid = false;
								break;
							}
						}
					} while (!valid);

					string input = phrase;
					transform(phrase.begin(), phrase.end(), phrase.begin(), encrypt); // encrypt input

					cout << string(100, '\n');
					cout << " Input: " << input << endl;
					cout << "Output: " << phrase << endl;
					break;
				}
				case 2: // reset to initial settings
				{
					for (int i = 0; i < 3; i++)
					{
						rotorSettings[i] = initialRotorSettings[i];
					}

					cout << string(500, '\n');
					cout << "Rotor settings have been reset to initial values\n";

					break;
				}
				case 3: // change initial settings and rotors
				{
					cout << string(100, '\n');
					
					fill_n(chosenRotors, 3, 0);
					fill_n(rotorSettings, 3, 0);
					fill_n(ringSettings, 3, 0);

					getReflectorChoice();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					getRotorChoices();
					storeSettings();

					cout << string(100, '\n');
					cout << "Rotors and intitial settings have been changed\n";

					break;
				}
				case 4:
				{
					cout << string(100, '\n');
					fill(plugboardPairs.begin(), plugboardPairs.end(), "##");
					getPlugboardPairs();
					cout << string(100, '\n');
					break;
				}
				case 5: // exit program BROKEN
				{
					cout << string(100, '\n');
					cout << "Goodbye!" << endl;
					exit = true;
					break;
				}
				default:
				{
					cout << string(500, '\n') << "Invalid choice";
				}
			}
		}
	}
}