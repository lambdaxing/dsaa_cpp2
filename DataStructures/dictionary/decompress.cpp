// Decompress using Ziv-Lempel-Welch

#include <fstream>
#include <iostream>
#include <cstring>

// constants
const int MAX_CODES = 4096,		// 2^12
BYTE_SIZE = 8,
EXCESS = 4,			// 12 - BYTE_SIZE
ALPHA = 256,		// 2^BYTE_SIZE
MASK = 15;			// 2^EXCESS - 1

typedef std::pair<int, char> pairType;

// globals
pairType ht[MAX_CODES];		// dictionary
char s[MAX_CODES];			// used to reconstruct text
int size;					// size of reconstructed text
int leftOver;				// code bits yet to be output
bool bitsLeftOver = false;	// false means no bits in leftOver
std::ifstream in;			// input file
std::ofstream out;			// output file

void setFiles(int argc,char* argv[])
{// Determine file name.
	char outputFile[50], inputFile[54];

	// see if file name provided
	if (argc == 2)
		std::strcpy(outputFile, argv[1]);
	else
	{// name not provided, ask for it
		std::cout << "Enter name of file to decompress" << std::endl;
		std::cout << "Omit the extension .zzz" << std::endl;
		std::cin >> outputFile;
	}

	std::strcpy(inputFile, outputFile);
	std::strcat(inputFile, ".zzz");

	// open files in binary mode
	in.open(inputFile, std::ios::binary);
	if (in.fail())
	{
		std::cerr << "Cannot open " << inputFile << std::endl;
		exit(1);
	}
	out.open(outputFile, std::ios::binary);
}

bool getCode(int& code);
void output(int code);

void decompress()
{// Decompress a compressed file.
	int codesUsed = ALPHA;	// codes codesUser so far

	// input and decompress
	int pcode,	// previous code
		ccode;	// current code
	if (getCode(pcode))
	{// file if not empty
		s[0] = pcode;		// character for pcode
		out.put(s[0]);		// output string for pcode
		size = 0;			// s[size] is first character of last string output

		while (getCode(ccode))
		{// there is another code
			if (ccode < codesUsed)
			{// code is defined
				output(ccode);
				if(codesUsed < MAX_CODES)
				{// create new code 
					ht[codesUsed].first = pcode;
					ht[codesUsed++].second = s[size];
				}
			}
			else
			{// special case, undefined code
				ht[codesUsed].first = pcode;
				ht[codesUsed++].second = s[size];
				output(ccode);
			}
			pcode = ccode;
		}
	}

	out.close();
	in.close();
}

bool getCode(int& code)
{// Put next code in compressend file into code.
 // Return false if no more codes.
	int c, d;
	if ((c = in.get()) == EOF)
		return false;	// no more codes

	// see if any left over bits from before
	// if yes, concatenate with left over 4 bits
	if (bitsLeftOver)
		code = (leftOver << BYTE_SIZE) | c;
	else
	{// no left over bits,need four more bits to complete code
		d = in.get();		// another 8 bits
		code = (c << EXCESS) | (d >> EXCESS);
		leftOver = d & MASK;	// save 4 bits
	}
	bitsLeftOver = !bitsLeftOver;
	return true;
}

void output(int code)
{// Output string corresponding to code.
	size = -1;
	while (code >= ALPHA)
	{// suffix in dictionary
		s[++size] = ht[code].second;
		code = ht[code].first;
	}
	s[++size] = code;	// code < ALPHA

	// decompressed string is s[size] ... s[0]
	for (int i = size; i >= 0; --i)
		out.put(s[i]);
}

int main(int argc, char* argv[])
{
	setFiles(argc, argv);
	decompress();
}