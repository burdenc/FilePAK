#include <string>
#include "../Pak/filePAK.h"
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

#if !defined unix && !defined __unix__ && !defined __unix
#include <conio.h>
#endif

using namespace std;

char sys(string param);
string chooseEntry();
bool displayChanges();
vector<string> split(const string &s, char delim);
int commandPrompt(int argc, const char* argv[]);
int menuPrompt();

string progname;
filePAK pak;

int main(int argc, const char* argv[])
{
	progname = argv[0];

	if(argc > 1)
	{
		return commandPrompt(argc, argv);
	}
	else
	{
		return menuPrompt();
	}
}

int commandPrompt(int argc, const char* argv[])
{
	string flags[] = {"-c", "-r", "-a", "-d", "-u", "-f", "-v"};
	int numflags = 7;
	
	bool verbose = false;
	for(int i = 1; i < argc; i++) //check to see if verbose should be enabled
		if(!strcmp(argv[i], "-v"))
			verbose = true;

	for(int i = 1; i < argc; i++)
	{
		if(!strcmp(argv[i], "/?") || !strcmp(argv[i], "help"))
		{
			printf("Usage: %s %s", argv[0], "<-r [-a name] ... [-d name] ... [-u name] ... | -c>\n");
			printf("%-18s%s", "", "[-f folder [types]] ... -v filename");

			cout << "\n\nOptions:\n";
			printf("  %-17s", "-c");
			printf("%s%-19s%s", "Create new empty PAK file of name \"filename\",\n", "", "replaces file if one with that name already exists\n");

			printf("  %-17s", "-r");
			printf("%s", "Read PAK file of \"filename\" to edit\n");

			printf("  %-17s", "-a name");
			printf("%s", "Append file of \"name\" to PAK file\n");

			printf("  %-17s", "-d name");
			printf("%s", "Remove file of \"name\" from PAK file\n");

			printf("  %-17s", "-u name");
			printf("%s", "Output file of \"name\" from PAK file\n");

			printf("  %-17s", "-f folder types");
			printf("%s%-19s%s%-19s%s%-19s%s",
				"Append all files in folder of name \"folder\",\n",
				"",
				"and only append files that end in \"types\".\n",
				"",
				"(types is optional, seperate each with |)\n",
				"",
				"Example: \".jpg|.bmp\"\n");

			printf("  %-17s", "-v");
			printf("%s", "Enables verbose output\n\n");

			return 0;
		}
	}

	//////////////////////////////
	//Checks for correct syntax://
	//////////////////////////////

	string filename = argv[argc-1];
	for(int i = 0; i < numflags; i++) //making sure a filename is supplied as the last argument and not a flag
		if(filename.compare(flags[i]) == 0)
			sys("syntaxerr");

	bool read; //false = create mode, true = read mode
	if(strcmp(argv[1], "-c") == 0)
		read = false;

	else if(strcmp(argv[1], "-r") == 0)
		read = true;

	for(int j = 2; j < argc-1; j++)
		for(int i = 2; i < 5; i++) //making sure no -r dependent commands are called when -r is not supplied
			if(strcmp(argv[j], flags[i].c_str()) == 0 && read == false)
				sys("syntaxerr");

	if(read)
		for(int j = 2; j < argc-2; j++)
			for(int i = 2; i < 6; i++) //iterating through all flags requiring atleast 1 argument
				for(int h = 0; h < numflags; h++) //iterating through all flags
					if(strcmp(argv[j], flags[i].c_str()) == 0 && strcmp(argv[j+1], flags[h].c_str()) == 0) //make sure argument supplied after flag isn't a new flag
						sys("syntaxerr");

	
	//for(int i = 0; i < argc-2; i++)

	///////////////////////
	//End of syntax check//
	///////////////////////

	filePAK pak;
	if(read)
	{
		if(verbose) cout << "Reading " << argv[argc-1] << "\n";
		if(!pak.readPAK(argv[argc-1]))
		{
			if(verbose) cout << "Could not read pak file: " << argv[argc-1] << "\n";
			return 1;
		}
	}
	else
	{
		if(verbose) cout << "Creating " << argv[argc-1] << "\n";
		if(!pak.createPAK(argv[argc-1]))
		{
			if(verbose) cout << "Could not create pak file: " << argv[argc-1] << "\n";
			return 1;
		}

		if(verbose) cout << "Reading new pak file " << argv[argc-1] << "\n";
		if(!pak.readPAK(argv[argc-1]))
		{
			if(verbose) cout << "Reading new pak file " << argv[argc-1] << "\n";
			return 1;
		}
	}

	bool changes = false;
	for(int i = 2; i < argc - 2; i++)
	{
		if(strcmp(argv[i], "-a") == 0)
		{
			if(verbose) cout << "Appending " << argv[i + 1] << "\n";
			if(!pak.appendFile(argv[i+1]))
			{
				if(verbose) cout << "Could not append " << argv[i+1] << " to pak file\n";
				return 1;
			}
			changes = true;
		}
		if(strcmp(argv[i], "-u") == 0)
		{
			if(verbose) cout << "Unpaking " << argv[i+1] << "\n";
			if(!pak.unPAKEntry(argv[i+1], "./"))
			{
				if(verbose) cout << "Could not unpak " << argv[i+1] << " from pak file\n";
				return 1;
			}
		}
		if(strcmp(argv[i], "-d") == 0)
		{
			if(verbose) cout << "Deleting " << argv[i+1] << "\n";
			if(!pak.removeFile(argv[i+1]))
			{
				if(verbose) cout << "Could not delete " << argv[i+1] << " from pak file\n";
				return 1;
			}
			changes = true;
		}
		if(strcmp(argv[i], "-f") == 0)
		{
			bool typesarg = true;
			for(int j = 0; j < numflags; j++)
				if(!(i+2 < argc-1) || strcmp(flags[j].c_str(), argv[i+2]) == 0)
					typesarg = false;

			if(typesarg)
			{
				if(verbose) cout << "Appending folder " << argv[i+1] << " with types " << argv[i+2] << "\n";
				if(!pak.appendFolder(argv[i+1], argv[i+2]))
				{
					if(verbose) cout << "Could not append folder " << argv[i+1] << " with types " << argv[i+2] << "\n";
					return 1;
				}
			}
			else
			{
				if(verbose) cout << "Appending folder " << argv[i+1] << "\n";
				if(!pak.appendFolder(argv[i+1]))
				{
					if(verbose) cout << "Could not append folder " << argv[i+1] << "\n";
					return 1;
				}
			}
			changes = true;
		}
	}

	if(changes)
	{
		if(verbose) cout << "Rebuilding " << argv[argc-1] << "\n";
		if(!pak.rebuildPAK())
		{
			if(verbose) cout << "Could not rebuild " << argv[argc-1] << "\n";
			return 1;
		}
	}

	return 0;
}

int menuPrompt()
{
	char choice;

	for(;;)
	{
		string menu;
		if(pak.isLoaded())
			menu += "[1] Rebuild PAK\n[2] View Files\n[3] Append File\n[4] Remove File\n[5] Unpak File\n[6] Discard Changes\n[7] Load Other PAK\n";
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
		else if((pak.isLoaded() && choice == '7') || (!pak.isLoaded() && choice == '2'))
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

				if(displayChanges())
				{
					cout << "Are you sure you wish to rebuild the PAK with the following changes?\n\n";
					cout << "Y = Yes, Others = No\n";
					char input = sys("getch");
					if(input == 'y' || input == 'Y')
					{
						sys("cls");
						if(pak.rebuildPAK())
						{
							cout << "The PAK was successfully rebuilt!\n";
						}
						else
						{
							cout << "The PAK could not be rebuilt.\n";
						}

					}
				}

				sys("pause");
				sys("cls");
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
				cout << "Caution, there is no check for files being appended multiple times.\nUse at your own discretion.\n\n";
				sys("pause");
				sys("cls");

				string choose;
				cout << "Please put in the file (including path to) that you wish to append:\n";
				getline(cin, choose);
				sys("cls");

				cout << "Are you sure you want to append \"" << choose << "\" to the PAK?\n";
				cout << "Y = Yes, Others = No\n";
				char input = sys("getch");

				if(input == 'y' || input == 'Y')
				{
					sys("cls");
					if(pak.appendFile(choose))
					{
						cout << "\"" << choose << "\" was successfully appended to the pak file!\n(Use Rebuild PAK to flush changes)\n\n";
					}
					else
					{
						cout << "\"" << choose << "\" could not be appended. Please ensure you input the file name correctly.\n";
					}
					sys("pause");
				}

				sys("cls");
			}

			//Remove Files
			else if(choice == '4')
			{
				string choose;
				for(;;)
				{
					choose = chooseEntry();
					sys("cls");
					if(choose.empty()) break;

					cout << "Are you sure you want to remove \"" << choose << "\" from the PAK?\n";
					cout << "Y = Yes, Others = No\n";
					char input = sys("getch");

					if(input == 'y' || input == 'Y')
					{
						sys("cls");
						if(pak.removeFile(choose))
						{
							cout << "\"" << choose << "\" was successfully removed from the pak file!\n(Use Rebuild PAK to flush changes)\n\n";
						}
						else
						{
							cout << "\"" << choose << "\" could not be removed.\n";
						}
						sys("pause");
					}
					sys("cls");
				}
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

bool displayChanges()
{
	vector<int> changes = pak.getChanges();
	if(!changes.empty())
	{
		string append, remove;
		append += "Appending: \n";
		remove += "Removing: \n";

		for(unsigned int i = 0; i < changes.size(); i++)
		{
			if(changes[i] == 0) continue;

			string name = pak.getPAKEntry(pak.getAllPAKEntries().at(i))->name;
			cout << name;
			if(changes[i] == 1) append += name; else remove += name;
			if(changes[i] == 1) append += "\n"; else remove += "\n";
		}

		cout << append << remove << "\n";

		return true;
	}
	else
	{
		cout << "No changes have been made to the PAK file that need rebuilding\n";
		return false;
	}
}

string chooseEntry()
{
	vector<string> entries = pak.getAllPAKEntries();
	char choice;
	int pages, page = 0;
	pages = ceil((double) entries.size()/7);

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
				system("read -n1 -s -r -p \"Press any key to continue...\""); //should silently read only 1 character then return
		#endif
	}
	else if(param.compare("getch") == 0)
	{
		#if !defined unix && !defined __unix__ && !defined __unix
			return _getch();
		#else
			system("read -n1 -s -r"); //should silently read only 1 character then return
		#endif
	}
	else if(param.compare("syntaxerr") == 0)
	{
		cout << "This is an incorrect usage of " << progname << "\n";
		cout << "Please do " << progname << " help or " << progname << " /? for correct syntax.\n\n";
		exit(0);
	}

	return NULL;
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    stringstream ss(s);
	string item;
    while(getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
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