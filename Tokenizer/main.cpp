#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <vector>
#include <algorithm>

using namespace std;

/**
* Node contains a word and a count of the frequency of the word
*/
struct node 
{
	string word;
	int count;
};

/**
* Function used to sort the nodes by their counts
*/
bool compareCount(const node &a, const node &b)
{
	return a.count > b.count;
}

/**Function Declarations*/

/**
* Removes punctuation and capitaliztion
* Returns vector of nodes
*/
vector<node> formatStrings(string);

/**
* Prints the results to the designated output file
*/
void printResults(vector<node>, string);


/**
* Command line arguements:
*	1-input file
*	2-output file
*/
int main(int argc, char *argv[])
{
	if (argc != 3) {
		printf("Input should contain 2 command line arguements (input and output files)");
		return 0;
	}
	vector<node> strgs = formatStrings(argv[1]);
	printResults(strgs, argv[2]);
	return 0;
}

/**
* Function Definition
*/
vector<node> formatStrings(string inputFile)
{
	ifstream infile(inputFile);
	vector<node> formattedStrings;
	string str;
	locale loc;
	while (!infile.eof())
	{
		infile >> str;
		string lowerCase;
		string noPunc;
		/*! Changes capitalized letters to lower case. */
		for (unsigned int k = 0; k < str.length(); k++)
		{
			lowerCase = lowerCase + tolower(str[k], loc);
		}
		/*! Removes punctuation. */
		for (const auto c : lowerCase) 
		{
			if (!ispunct(c)) {
				noPunc.push_back(c);
			}
		}
		bool seen = false; /*! Flag set if node is seen with same word. */
		for (unsigned int j = 0; j < formattedStrings.size(); j++)
		{
			/*! If node exists with given word, increment its count. */
			if (noPunc == formattedStrings.at(j).word) 
			{
				formattedStrings.at(j).count++;
				seen = true;
			}
		}
		/*! If word wasn't found, add it to formattedStrings. */
		if (seen == false)
		{
			node k;
			k.count = 1;
			k.word = noPunc;
			formattedStrings.push_back(k);
		}
	}
	infile.close();
	return formattedStrings;
}

/**
* Function Definition
*/
void printResults(vector<node> res, string output)
{
	ofstream outFile(output);
	sort(res.begin(), res.end(), compareCount);		/*!Sort by count member*/
	for (unsigned int k = 0; k < res.size(); k++)
	{
		outFile << res.at(k).word << " " << res.at(k).count << endl;
	}
	outFile.close();
}