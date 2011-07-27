#include <string>
#include "filePAK.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "dirent.h"
#include <vector>

using namespace std;

int main()
{
	//Basically below I pack everything in the folder test into lol.pak
	//I then load Sunset.jpg from the pak file and write it to output.jpg
	filePAK pak;
	if(pak.createPAK("lol.pak", "test/", ".jpg|.bmp"))
	{
		if(!pak.readPAK("lol.pak"))
		{
			cout << "Critical error: Can't read pak\n";
			return 1;
		}
	}
	else
	{
		cout << "Critical error: Can't create pak\n";
		return 1;
	}

	char *buffer, *buffer2; // stores data to be copied
	int ofsize, ofsize2; // stores size of original file

	buffer = pak.grabPAKEntry("Sunset.jpg");
	ofsize = pak.grabPAKEntrySize("Sunset.jpg");
	if(buffer == NULL || ofsize <= 0)
	{
		cout << "Critical error: Cannot find file: Sunset\n";
		system("pause");
		return 1;
	}

	buffer2 = pak.grabPAKEntry("Aether.bmp");
	ofsize2 = pak.grabPAKEntrySize("Aether.bmp");
	if(buffer2 == NULL || ofsize2 <= 0)
	{
		cout << "Critical error: Cannot find file: Aether\n";
		system("pause");
		return 1;
	}

	//////////////////////////////////////////////////
	///////////////////  INPUT  //////////////////////
	//////////////////////////////////////////////////

	/*ifstream of; //sunset
	of.open("test/sunset.jpg", ofstream::binary); // open in binary

	if (of.is_open()) { // make sure it opened

		of.seekg (0, ios::end); // seek to the end of the file
		ofsize = of.tellg(); // store the end of the file's position as the length (will give a warning. not an issue)
		of.seekg(0, ios::beg); // go back to the beginning of the original file

		buffer = new char [ofsize]; // new buffer with the size of the original

		of.read(buffer, ofsize); // read a chunk of data into buffer from the beginning of the original file to the end
	}
	else {
		// to do: make an crash function to display error messages and such
		cout << "Critical error: Input file could not be opened\n";
		return 1;
	}

	of.close(); // close original file*/
	
	//////////////////////////////////////////////////
	/////////////////////  OUTPUT  ///////////////////
	//////////////////////////////////////////////////

	ofstream f; //output
	f.open("output.jpg", ofstream::binary); // open in binary

	if (f.is_open()) { // make sure it opened

		/*int PAKEntrySize = pak.grabPAKEntrySize("Sunset.jpg");
		if (PAKEntrySize <= 0) {
			cout << "Critical error: No data in PAK\n";
			return 1;
		}*/

		f.write(buffer, ofsize); // write the buffer to the output file with the size of the original file
	}
	else {
		// to do: make an crash function to display error messages and such
		cout << "Critical error: Output file could not be opened\n";
		return 1;
	}

	f.close(); // close output file

	f.open("output.bmp", ofstream::binary); // open in binary

	if (f.is_open()) { // make sure it opened

		/*int PAKEntrySize = pak.grabPAKEntrySize("Sunset.jpg");
		if (PAKEntrySize <= 0) {
			cout << "Critical error: No data in PAK\n";
			return 1;
		}*/

		f.write(buffer2, ofsize2); // write the buffer to the output file with the size of the original file
	}
	else {
		// to do: make an crash function to display error messages and such
		cout << "Critical error: Output file could not be opened\n";
		return 1;
	}

	f.close(); // close output file

	//////////////////////////////////////////////////

	system("pause");

	return 0;
}