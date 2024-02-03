//============================================================================
// Name        : Inlupp5b.cpp
// Author      : Viktor Lundberg (vilu6614)
// Date        : 2022-07-13
// Description : Inlämningsuppgift 5, del B
//
//				 This program will take a text, and print a chart containing
// 				 how many characters of each letter was seen in that text.
//				 It will also guess what the most probable language the text
//				 was written in.
//
//============================================================================

#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// Constants
const int N_LETTERS = 26;
const int N_LANGUAGES = 4;

// 2D array with letter frequencies for four languages
// Index 0 = english, 1 = french, 2 = swedish, 3 = german
const double INTERPRETING_CHART[N_LANGUAGES][N_LETTERS] =
{
{ 8.27, 1.48, 2.94, 4.03, 11.78, 2.22, 1.72, 6.77, 7.39, 0.12, 0.81, 3.76, 2.85,
		6.71, 7.79, 1.54, 0.05, 5.95, 6.69, 9.07, 2.66, 1.13, 2.14, 0.19, 1.89,
		0.03 },
{ 7.97, 1.40, 3.55, 3.79, 16.89, 1.02, 1.00, 0.75, 7.08, 0.38, 0.04, 5.51, 2.82,
		8.11, 5.19, 2.78, 1.01, 6.69, 8.35, 7.22, 6.09, 1.35, 0.02, 0.54, 0.30,
		0.15 },
{ 9.50, 1.11, 1.53, 5.30, 8.94, 1.74, 3.57, 3.94, 3.98, 0.89, 3.26, 4.93, 3.41,
		8.46, 5.01, 1.77, 0.00, 6.73, 5.56, 9.20, 1.94, 2.42, 0.00, 0.05, 0.45,
		0.00 },
{ 5.12, 1.95, 3.57, 5.07, 16.87, 1.35, 3.00, 5.79, 8.63, 0.19, 1.14, 3.68, 3.12,
		10.64, 1.74, 0.42, 0.01, 6.30, 6.99, 5.19, 3.92, 0.77, 1.79, 0.01, 0.69,
		1.24 } };

// Class declaration
class Text
{

private:
	// Class variables
	string txt;
	int n;
	int chartAbs[N_LETTERS];
	double chartRel[N_LETTERS];

public:
	// Constructor
	Text();

	// Getters and setters
	void setText(const string &txt_);

	// Other methods
	bool calculateChartAbs();
	void writeChartAbs();
	void absToRel();
	void printChartRel();
	void calculateCharts();
	string assignLanguageAi();
};

// Function declarations for main
string fileName_reader();
string file_reader(string fileName);

// Main program
int main()
{
	// Declare variables
	string text;
	Text myTextObject;

	string fileName = fileName_reader();
	text = file_reader(fileName);

	myTextObject.setText(text);
	myTextObject.calculateCharts();

	return 0;
}

// Main function implementations
// Asks the user to enter a fileName. If user does not enter .txt at the end we add it
string fileName_reader()
{
	string fileName = "";

	cout << "Ange filnamn: ";
	getline(cin, fileName);
	cout << endl;

	// if user didn't put .txt at the end, we add .txt at the end
	if (fileName.rfind(".txt") == string::npos)
	{
		fileName.append(".txt");
	}

	return fileName;
}

// Reads the file with fileName as input, using ifstream, char by char
string file_reader(string fileName)
{
	string myText;
	char next;

	ifstream input(fileName);

	// file does not exist
	if (!input.is_open())
	{
		cout << "Det finns ingen fil med namnet " << fileName << endl;
		exit(0);
	}

	// read char by char and add to myText at the end
	while (input.get(next))
	{
		myText.push_back(next);
	}

	input.close();

	return myText;
}

// Class function implementations
// Default constructor
Text::Text()
{
	// Initialize variables
	txt = "";
	n = 0;

	// Fill arrays with 0 to avoid nonsense empty values
	for (int i = 0; i < N_LETTERS; i++)
	{
		chartAbs[i] = 0;
		chartRel[i] = 0;
	}
}

// Setter, sets text txt to input string txt_
void Text::setText(const string &txt_)
{
	txt = txt_;
}

// Calculates a chart with absolute values
bool Text::calculateChartAbs()
{
	// If user input is empty string, return false
	if (txt.empty())
	{
		return false;
	}

	// For each char in the text, convert to upper, find out index and calculate how
	// many times we seen it.
	for (int i = 0; i < txt.length(); i++)
	{
		char next = toupper(txt[i]);

		if (isalpha(next))
		{
			int nextIndex = next - 'A';

			chartAbs[nextIndex] += 1;
			n++;
		}
	}

	return true;
}

// Writes the previous calculated chart
void Text::writeChartAbs()
{
	cout << "Resultat för bokstäverna A-Z, abs" << endl;
	cout << "Totala antalet bokstäver: " << n << endl;
	cout << "Bokstavsfördelning:" << endl;

	for (int i = 0; i < N_LETTERS; i++)
	{
		char letter = (char) (i) + 'A';

		cout << letter << ": " << chartAbs[i] << endl;
	}
}

// Converts absolute chart to relative chart
void Text::absToRel()
{
	// Convert all in chartAbs to rel
	for (int i = 0; i < N_LETTERS; i++)
	{
		if (chartAbs[i] > 0)
		{
			chartRel[i] = (double) chartAbs[i] / n;
		}
	}
}

// Prints rel chart
void Text::printChartRel()
{
	cout << "Resultat för bokstäverna A-Z, rel" << endl;
	cout << "Totala antalet bokstäver: " << n << endl;
	cout << "Bokstavsfördelning:" << endl;

	for (int i = 0; i < N_LETTERS; i++)
	{
		char letter = (char) i + 'A';

		cout << letter << ": ";

		if (chartRel[i] > 0)
		{
			int stars = chartRel[i] * 100 * 2;

			for (int i = 0; i < stars; i++)
			{
				cout << "*";
			}
		}
		cout << endl;
	}
}

// Calls and prints the chart functions
void Text::calculateCharts()
{
	// if this is true, user entered a file containing some text
	bool success = calculateChartAbs();
	writeChartAbs();

	// run rest of methods
	if (success)
	{
		absToRel();
		printChartRel();
		assignLanguageAi();
	}
	else
	{
		cout << "Tom input, inget relativt histogram visas" << endl;
	}

}

// Using letter frequency, calculates the most probable language.
string Text::assignLanguageAi()
{
	string languages[N_LANGUAGES] = { "engelska", "franska", "svenska", "tyska" };
	double lowestSum = numeric_limits<double>::max();
	string language = "";

	// calculate quadratic sum
	for (int i = 0; i < N_LANGUAGES; i++)
	{
		double sum = 0.0;

		for (int j = 0; j < N_LETTERS; j++)
		{
			double current = (INTERPRETING_CHART[i][j] - chartRel[j] * 100)
					* (INTERPRETING_CHART[i][j] - chartRel[j] * 100);
			sum += current;
		}

		cout << "Kvadratsumman för " << languages[i] << " är: " << sum << endl;

		if (sum < lowestSum)
		{
			lowestSum = sum;
			language = languages[i];
		}
	}

	cout << "Troligt språk är " << language << " eftersom " << lowestSum
			<< " var den lägsta summan." << endl;
	cout << endl;

	return language;
}
