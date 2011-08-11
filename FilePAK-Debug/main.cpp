#include <string>
#include "../Pak/filePAK.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#if !defined unix && !defined __unix__ && !defined __unix
#include <conio.h>
#endif

using namespace std;

char sys(string param);
string chooseEntry();

filePAK pak;

int main()
{
	char choice;

	for(;;)
	{
		string menu;
		if(pak.isLoaded())
			menu += "[1] Rebuild PAK\n[2] View Files\n[3] Append File\n[4] Remove File\n[5] Unpak File\n[6] Load Other PAK\n";
		else
			menu += "[1] Create PAK\n[2] Load PAK\n";

		menu += "[9] Help\n[0] Quit\n";

		cout << menu;

		choice = sys("getch");

		sys("cls");

		//Exit
		if(choice == '0')
		{
			cout << "Exiting...\n";
			sys("pause");
			return 0;
		}

		//Help
		else if(choice == '9')
		{
			string help;
			help += "The following tips may help you when using the program:\n\n";
			help += "Before you can do anything with a pak file (included one just made with the\n";
			help += "Create PAK option) you need to use the Read PAK option.\n\n";

			cout << help;

			sys("pause");
		}

		//Load PAK
		else if((pak.isLoaded() && choice == '6') || (!pak.isLoaded() && choice == '2'))
		{
			string pakname;
			cout << "Please provide the name of the pak file to load:\n";
			getline(cin, pakname);
			sys("cls");

			if(pak.readPAK(pakname))
			{
				cout << "PAK file successfully loaded!\n";
			}
			else
			{
				cout << "The PAK file could not be loaded. Make sure the provided PAK file was made by this program.\n";
			}

			sys("pause");
		}

		//No PAK Loaded options
		else if(!pak.isLoaded())
		{
			//Create PAK
			if(choice == '1')
			{
				string pakname, entryname, types;
				for(;;)
				{
					cout << "Please provide the name of the PAK file to create:\n";
					getline(cin, pakname);
					cout << "\nPlease provide the file path to the files to include in the PAK file: \n"; 
					getline(cin, entryname);
					cout << "\nPlease provide the file type restriction to use (optional, press enter to skip)\n";
					cout << "(Seperate each with | ex: '.jpg|.bmp' will only use jpg and bmp files):\n";
					getline(cin, types);

					sys("cls");
					cout << "Are the following options are correct?\n";
					cout << "PAK Name: " << pakname << "\n";
					cout << "Folder Path: " << entryname << "\n";
					cout << "Type Restriction: " << (types.empty() ? "None" : types) << "\n";
					cout << "Y = Yes, Others = No\n";
					char input = sys("getch");
					if(input == 'y' || input == 'Y') { sys("cls"); break; }

					sys("cls");

				}

				if(pak.createPAK(pakname, entryname, types.empty() ? "" : types))
				{
					cout << "PAK file successfully created!\n";
				}
				else
				{
					cout << "The PAK file could not be created successfully, please check your options and try again.\n";
					cout << "Make sure you're placing your slashes in the correct place (\"/test/\" isn't the same as \"test/\")\n";
				}

				sys("pause");
			}
		}
		//PAK Loaded Options
		else
		{
			//Rebuild PAK
			if(choice == '1')
			{

			}

			//View Files
			else if(choice == '2')
			{
				string choose;
				for(;;)
				{
					choose = chooseEntry();
					sys("cls");
					if(choose.empty()) break;

					int size = pak.getPAKEntry(choose)->size;

					cout << choose << ": \n\n";
					cout.width(15); cout << "Original Path: " << left << pak.getPAKEntry(choose)->fullname << "\n";
					cout.width(15); cout << "Offset: " << left << pak.getPAKEntry(choose)->offset << "\n";
					cout.width(15); cout << "Size: " << left << size << " bytes (~" << (double) ((size/1024)/1024) << " MB)\n\n";

					sys("pause");
					sys("cls");
				}

			}

			//Append Files
			else if(choice == '3')
			{

			}

			//Remove Files
			else if(choice == '4')
			{

			}

			//UnPAK Files
			else if(choice == '5')
			{

			}
		}

		//sys("pause");
		sys("cls");

	}

	return 0;
}

string chooseEntry()
{
	vector<string> entries = pak.getAllPAKEntries();
	char choice;
	int pages, page = 0;
	pages = (int) ceil(entries.size()/7.0);

	for(;;)
	{
		string menu;
		int numchoices = 7;

		for(unsigned int i = 0; i < 7; i++)
		{
			if(i + (7 * page) >= entries.size())
			{
				numchoices = i;
				break;
			}

			stringstream ss;
			ss << (i+1);

			menu += "[";
			menu += ss.str();
			menu += "] ";
			menu += entries[i + (7 * page)];
			menu += "\n";
		}

		if(page > 0) menu += "[8] Prev Page\n";
		if(page+1 < pages) menu += "[9] Next Page\n";
		menu += "[0] Back\n";

		cout << menu;

		choice = sys("getch");

		if(choice == '0')
		{
			return "";
		}
		else if(choice == '8' && page > 0)
		{
			page--;
		}
		else if(choice == '9' && page+1 < pages)
		{
			page++;
		}
		else if(choice == '1' || choice == '2' || choice == '3' || choice == '4' || choice == '5' || choice == '6' || choice == '7')
		{
			cout << atoi(&choice) + (7 * page);
			if(!(atoi(&choice)-1 > numchoices))
				return entries[atoi(&choice) + (7 * page)-1];
		}
	}
}

char sys(string param)
{
	if(param.compare("cls") == 0)
	{
		#if !defined unix && !defined __unix__ && !defined __unix
				system("cls");
		#else
				system("clear");
		#endif
	}
	else if(param.compare("pause") == 0)
	{
		#if !defined unix && !defined __unix__ && !defined __unix
				system("pause");
		#else
				system("read -n 1 -s -p \"Press any key to continue...\""); //should silently read only 1 character then return
		#endif
	}
	else if(param.compare("getch") == 0)
	{
		#if !defined unix && !defined __unix__ && !defined __unix
			return _getch();
		#else
			system("read -n 1 -s"); //should silently read only 1 character then return
		#endif
	}

	return NULL;
}

/*int main()
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

		if (!pak.removeFile("Aether.bmp"))
		{
			cout << "Critical error: Cannot remove 'Aether.bmp'\n";
			system("pause");
			return 1;
		}

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
}*/