#include <cstring> //These three are
#include <cstdlib> //required for
#include <cmath>   //compiling with G++

#include <string>
#include "../libPAK/libPAK.h"
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

#if !defined unix && !defined __unix__ && !defined __unix
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#endif

using namespace std;

char sys(string param);
string chooseEntry();
bool displayChanges();
vector<string> split(const string &s, char delim);
int commandPrompt(int argc, const char* argv[]);
int menuPrompt();

string progname;
libPAK pak;

int main(int argc, const char* argv[])
{
	progname = argv[0]; //Store the program name for easy access

	if(argc > 1)
	{
		return commandPrompt(argc, argv); //Command line use
	}
	else
	{
		return menuPrompt(); //Menu use, works best on Windows
	}
}

int commandPrompt(int argc, const char* argv[])
{
	//Array of all flags that you can use
	string flags[] = {"-c", "-r", "-a", "-d", "-u", "-f", "-v"};
	int numflags = 7; //the length of the above array
	
	bool verbose = false;
	for(int i = 1; i < argc; i++) //check to see if verbose should be enabled
		if(!strcmp(argv[i], "-v"))//if so output a lot of debug info
			verbose = true;

	for(int i = 1; i < argc; i++) //check if any of the flags are the help flags
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
			sys("syntaxerr"); //outputs that there's a syntax error and print reminder of how to get help

	bool read; //false = create mode, true = read mode
	if(strcmp(argv[1], "-c") == 0)
		read = false; //create mode active

	else if(strcmp(argv[1], "-r") == 0)
		read = true; //read mode active

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

	///////////////////////
	//End of syntax check//
	///////////////////////

	libPAK pak;
	if(read)
	{
		if(verbose) cout << "Reading " << argv[argc-1] << "\n";
		if(!pak.readPAK(argv[argc-1])) //Try to read the pak file with the last argument
		{
			if(verbose) cout << "Could not read pak file: " << argv[argc-1] << "\n";
			return 1;
		}
	}
	else
	{
		if(verbose) cout << "Creating " << argv[argc-1] << "\n";
		if(!pak.createPAK(argv[argc-1])) //try to create a new empty pak file with the last argument
		{
			if(verbose) cout << "Could not create pak file: " << argv[argc-1] << "\n";
			return 1;
		}

		if(verbose) cout << "Reading new pak file " << argv[argc-1] << "\n";
		if(!pak.readPAK(argv[argc-1])) //read the new empty pak file so you can manipulate it
		{
			if(verbose) cout << "Reading new pak file " << argv[argc-1] << "\n";
			return 1;
		}
	}

	bool changes = false; //make sure flags are supplied that require changes
	for(int i = 2; i < argc - 2; i++)
	{
		if(strcmp(argv[i], "-a") == 0)
		{
			if(verbose) cout << "Appending " << argv[i + 1] << "\n";
			if(!pak.appendFile(argv[i+1])) //attempt to append file name given after -a
			{
				if(verbose) cout << "Could not append " << argv[i+1] << " to pak file\n";
				return 1;
			}
			changes = true;
		}
		if(strcmp(argv[i], "-u") == 0)
		{
			if(verbose) cout << "Unpaking " << argv[i+1] << "\n";
			if(!pak.unPAKEntry(argv[i+1])) //attempt to append file name given after -u
			{ //it unpaks to the current folder, thus the ./
				if(verbose) cout << "Could not unpak " << argv[i+1] << " from pak file\n";
				return 1;
			}
		}
		if(strcmp(argv[i], "-d") == 0)
		{
			if(verbose) cout << "Deleting " << argv[i+1] << "\n";
			if(!pak.removeFile(argv[i+1])) //attempt to remove file name given after -d
			{
				if(verbose) cout << "Could not delete " << argv[i+1] << " from pak file\n";
				return 1;
			}
			changes = true;
		}
		if(strcmp(argv[i], "-f") == 0) //appending a folder
		{
			bool typesarg = true;
			for(int j = 0; j < numflags; j++) //append folder can optionally take a 2nd argument
				if(!(i+2 < argc-1) || strcmp(flags[j].c_str(), argv[i+2]) == 0) //this is checking to see
					typesarg = false;											//if that 2nd argument is supplied or not

			if(typesarg) //if the 2nd argument was supplied
			{
				if(verbose) cout << "Appending folder " << argv[i+1] << " with types " << argv[i+2] << "\n";
				if(!pak.appendFolder(argv[i+1], argv[i+2])) //attempt to append a folder with type restrictions given
				{
					if(verbose) cout << "Could not append folder " << argv[i+1] << " with types " << argv[i+2] << "\n";
					return 1;
				}
			}
			else
			{
				if(verbose) cout << "Appending folder " << argv[i+1] << "\n";
				if(!pak.appendFolder(argv[i+1])) //appending a folder with no type restriction
				{
					if(verbose) cout << "Could not append folder " << argv[i+1] << "\n";
					return 1;
				}
			}
			changes = true;
		}
	}

	if(changes) //if arguments were given that require a rebuild then rebuild the PAK
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
			menu += "[1] Rebuild PAK\n[2] View Files\n[3] Append File\n[4] Append Folder\n[5] Remove File\n[6] Unpak File\n[7] Display Changes\n[8] Discard Changes\n[9] Load Other PAK\n";
		else
			menu += "[1] Create PAK\n[2] Load PAK\n";

		menu += "[H] Help\n[0] Quit\n";

		cout << menu;

		choice = sys("getch");

		sys("cls");

		//Exit
		if(choice == '0') //the exit command is always 0
		{
			return 0;
		}

		//Help
		else if(choice == 'H' || choice == 'h')
		{
			string help;
			help += "The following tips may help you when using the program:\n\n";
			help += "Before you can do anything with a pak file (included one just made with the\n";
			help += "Create PAK option) you need to use the Read PAK option.\n\n";

			help += "To ensure stability a PAK file will automatically be rebuilt when you append\n";
			help += "anything.\n\n";

			help += "For command line help do "; help += progname; help += " /? or "; help += progname; help += " help\n\n";

			cout << help;

			sys("pause");
		}

		//Load PAK
		else if((pak.isLoaded() && choice == '9') || (!pak.isLoaded() && choice == '2'))
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

				cout << "Please provide the name of the PAK file to create:\n";
				getline(cin, pakname);
				cout << "\nPlease provide the file path to the files to include in the PAK file: \n"; 
				getline(cin, entryname);
				cout << "\nPlease provide the file type restriction to use (optional, press enter to skip)\n";
				cout << "(Seperate each with | ex: '.jpg|.bmp' will only use jpg and bmp files):\n";
				getline(cin, types);

				//Ensure they want to create a new PAK with the following options
				sys("cls");
				cout << "Are the following options are correct?\n";
				cout << "PAK Name: " << pakname << "\n";
				cout << "Folder Path: " << entryname << "\n";
				cout << "Type Restriction: " << (types.empty() ? "None" : types) << "\n";
				cout << "Y = Yes, Others = No\n";
				char input = sys("getch");
				sys("cls");

				if(input == 'y' || input == 'Y')
				{
					if(pak.createPAK(pakname, entryname, types))
					{
						cout << "PAK file successfully created!\n\n";
					}
					else
					{
						cout << "The PAK file could not be created successfully, please check your options and try again.\n";
						cout << "Make sure you're placing your slashes in the correct place (\"/test/\" isn't the same as \"test/\")\n\n";
					}

					sys("pause");
				}
			}
		}
		//PAK Loaded Options
		else
		{
			//Rebuild PAK
			if(choice == '1')
			{

				if(displayChanges()) //displays and checks to see if you're ok with the current changes
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
						cout << "\"" << choose << "\" was successfully appended to the pak file!\nThe PAK will now be rebuilt...\n\n";

						sys("pause");
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
					else
					{
						cout << "\"" << choose << "\" could not be appended.\n Please ensure you input the file name correctly.\n\n";
					}
					sys("pause");
				}

				sys("cls");
			}

			//Append Folders
			else if(choice == '4')
			{
				string choose, types;
				cout << "Please input the folder that you wish to append:\n";
				getline(cin, choose);

				cout << "\nPlease provide the file type restriction to use (optional, press enter to skip)\n";
				cout << "(Seperate each with | ex: '.jpg|.bmp' will only use jpg and bmp files):\n";
				getline(cin, types);

				sys("cls");

				cout << "Are you sure you want to append all the files in \"" << choose << "\" to the PAK\n";
				cout << "and use the following type restriction : " << (types.empty()) ? "None" : types;
				cout << "?\n";
				cout << "Y = Yes, Others = No\n";
				char input = sys("getch");

				if(input == 'y' || input == 'Y')
				{
					sys("cls");
					if(pak.appendFolder(choose, types))
					{
						cout << "The folder \"" << choose << "\" was successfully appended to the pak file!\nThe PAK will now be rebuilt...\n\n";

						sys("pause");
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
					else
					{
						cout << "The folder \"" << choose << "\" could not be appended.\n Please ensure you input the file name correctly.\n\n";
					}
					sys("pause");
				}

				sys("cls");
			}

			//Remove Files
			else if(choice == '5')
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
			else if(choice == '6')
			{
				string choose;
				for(;;)
				{
					choose = chooseEntry();
					sys("cls");
					if(choose.empty()) break;

					cout << "Are you sure you want to unpak \"" << choose << "\" from the PAK?\n";
					cout << "Y = Yes, Others = No\n";
					char input = sys("getch");

					if(input == 'y' || input == 'Y')
					{
						sys("cls");
						if(pak.unPAKEntry(choose, "./"))
						{
							cout << "\"" << choose << "\" was successfully unpaked from the pak file!\n\n";
						}
						else
						{
							cout << "\"" << choose << "\" could not be unpaked.\n";
						}
						sys("pause");
					}
					sys("cls");
				}
			}

			//Display Changes
			else if(choice == '7')
			{
				cout << "The followning are the current staged changes:\n\n";
				displayChanges();
				sys("pause");
			}

			//Discard Changes
			else if(choice == '8')
			{
				cout << "Are you sure you wish to discard the following staged changes?\n\n";
				
				if(displayChanges())
				{

					cout << "Y = Yes, Others = No\n";
					char input = sys("getch");

					if(input == 'y' || input == 'Y')
					{
						sys("cls");
						pak.discardChanges();
						cout << "All staged changes have been discard successfully!\n\n";
						sys("pause");
					}
				}
				else sys("pause");

				sys("cls");
			}

		}

		//sys("pause");
		sys("cls");

	}

	return 0;
}

//Displays all changes
bool displayChanges()
{
	vector<int> changes = pak.getChanges();
	if(!changes.empty())
	{
		string remove;
		remove += "Removing: \n";

		vector<string> allentries = pak.getAllPAKEntries();

		for(unsigned int i = 0; i < changes.size(); i++)
		{
			if(changes[i] == 0) continue;

			string name = allentries[i];
			remove += name;
			remove += "\n";
		}

		cout << remove << "\n";

		return true;
	}
	else
	{
		cout << "No changes have been made to the PAK file that need rebuilding.\n\n";
		return false;
	}
}

//Abstract function for displaying all entries and letting you choose one
//Used for removing, unpaking, and viewing files in a PAK
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

//if not on windows, make our own implementation of getch
#if defined unix || defined __unix__ || defined __unix
int _getch()
{
	struct termios oldt, newt;
	int ch;
	tcgetattr( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	return ch;
}
#endif

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
				cout << "Press any key to continue...";
				_getch();
		#endif
	}
	else if(param.compare("getch") == 0)
	{
		return _getch(); // if not on windows, we defined this as our own implementation of getch up above
	}
	else if(param.compare("syntaxerr") == 0)
	{
		cout << "This is an incorrect usage of " << progname << "\n";
		cout << "Please do " << progname << " help or " << progname << " /? for correct syntax.\n\n";
		exit(0);
	}

	return NULL;
}

//Uses a string stream to easily split a string, it's so simple!
vector<string> split(const string &s, char delim) {
    vector<string> elems;
    stringstream ss(s);
	string item;
    while(getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
