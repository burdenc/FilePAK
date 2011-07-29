#include <string>
#include "../Pak/filePAK.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
//#include "dirent.h"
#include <vector>

using namespace std;

int main()
{
	//Basically below I pack everything in the folder test into lol.pak
	//I then load Sunset.jpg from the pak file and write it to output.jpg
	filePAK pak;
	cout << "Creating PAK file\n";
	if(pak.createPAK("lol.pak", "test/", ".jpg|.bmp"))
	{
		cout << "PAK file created successfully\n";
		cout << "\nReading PAK\n";
		if(!pak.readPAK("lol.pak"))
		{
			cout << "Critical error: Cannot read pak\n";
			system("pause");
			return 1;
		}

		if(!pak.appendFile("test/loltest.txt"))
		{
			cout << "Critical error: Cannot append file\n";
			system("pause");
			return 1;
		}

		cout << "\nloltest.txt appended\n";

		if(!pak.rebuildPAK())
		{
			cout << "Critical error: Cannot rebuild pak\n";
			system("pause");
			return 1;
		}
	}
	else
	{
		cout << "Critical error: Cannot create pak\n";
		system("pause");
		return 1;
	}

	cout << "\nPAK file read successfully\n";
	cout << "\nTesting PAK decrypt\n";

	char *buffer; // stores data to be copied
	int ofsize; // stores size of original file
	ofstream f; //output

	buffer = pak.getPAKEntryData("loltest.txt");
	ofsize = pak.getPAKEntrySize("loltest.txt");
	if(buffer == NULL || ofsize <= 0)
	{
		cout << "Critical error: Cannot find file listed in PAK\n";
		system("pause");
		return 1;
	}

	cout << "PAK decrypted successfully\n";
	cout << "\nWriting decrypted file to loltest.txt\n";

	f.open("loltest.txt", ofstream::binary); // open in binary

	if (f.is_open())  // make sure it opened
	{
		f.write(buffer, ofsize); // write the buffer to the output file with the size of the original file
	}
	else
	{
		// to do: make an crash function to display error messages and such
		delete [] buffer;
		cout << "Critical error: Output file could not be opened\n";
		system("pause");
		return 1;
	}

	delete [] buffer;

	f.close(); // close output file

	cout << "\nOutput successful\n";

	//////////////////////////////////////////////////

	cout << "\nAbsolute success!\n";

	system("pause");

	return 0;
}