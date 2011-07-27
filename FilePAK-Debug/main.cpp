#include <string>
#include "filePAK.h"
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
	}
	else
	{
		cout << "Critical error: Cannot create pak\n";
		system("pause");
		return 1;
	}

	cout << "PAK file read successfully\n";
	cout << "\nTesting PAK decrypt\n";

	char *buffer; // stores data to be copied
	int ofsize; // stores size of original file
	ofstream f; //output

	buffer = pak.grabPAKEntry("Sunset.jpg");
	ofsize = pak.grabPAKEntrySize("Sunset.jpg");
	if(buffer == NULL || ofsize <= 0)
	{
		cout << "Critical error: Cannot find file listed in PAK\n";
		system("pause");
		return 1;
	}

	cout << "PAK decrypted successfully\n";
	cout << "\nWriting decrypted file to output.jpg\n";

	f.open("output.jpg", ofstream::binary); // open in binary

	if (f.is_open())  // make sure it opened
	{
		f.write(buffer, ofsize); // write the buffer to the output file with the size of the original file
	}
	else
	{
		// to do: make an crash function to display error messages and such
		cout << "Critical error: Output file could not be opened\n";
		system("pause");
		return 1;
	}

	f.close(); // close output file

	cout << "Output successful\n";

	//////////////////////////////////////////////////

	cout << "\nAbsolute success!\n";

	system("pause");

	return 0;
}