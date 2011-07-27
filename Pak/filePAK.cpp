#include "filePAK.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <windows.h>
#include <random>
#include <time.h>

#ifdef _WINDOWS_
#include "dirent.h" //Usually only in MacOSX or Linux, it allows you to find all the files contained within a folder
#else
#include <dirent.h>
#endif

filePAK::filePAK(void)
{
	pakloaded = false;
}


filePAK::~filePAK(void)
{
}

bool filePAK::createPAK(string name, string entryPath, string types)
{
	pakname = name;
	srand((unsigned) time(NULL)); //seedin'
	ofstream PAKout;
	ifstream fileIn;
	int numberFiles = 0;

	header.additionEncrypt = ( (rand() % 2) ? true : false ); //Set random values for encrypting. The compact if-statement is used to prevent compiler warnings about casting int to a bool.
	header.encryptVal = (char) (rand() % 256);
	memcpy(header.fileID, "DBPAK\0", 6); //Using memcpy because lol char array
	memcpy(header.version, "1.0\0", 4);

	vector<string> correctTypes = filetypes(types);
	DIR *dir; //dirent.h stuff to accumulate all files within a folder
	dirent *entry;
	if(dir = opendir(entryPath.c_str()))
	{
		while(entry = readdir(dir))
		{
			if(entry->d_type != DT_DIR && entry->d_type == DT_REG) //if it's not a folder and a regular file
			{
				bool correctType = false;
				if(types.empty()) correctType = true;
				else
				{
					for(unsigned int i = 0; i < correctTypes.size(); i++)
						if(!entry->d_name+correctTypes[i].compare(entry->d_name))
							correctType = true;
				}

				
				if(correctType)
				{
					numberFiles++;

					PAKfileEntry fentry; //creates a new table of contents entry

					string entryName; //Sets up the path/name strings
					entryName += entryPath;
					entryName += entry->d_name;
					memcpy(fentry.name, entry->d_name, 50); //only the file name
					memcpy(fentry.fullname, entryName.c_str(), 100); //file name + folders
				
					fileIn.open(entryName, ifstream::binary | ifstream::ate);

					if(fileIn.is_open())
					{
						fentry.size = (unsigned int) fileIn.tellg(); //to calculate the file's size
						fileIn.close();
					}
					else return false;

					fentry.offset = 0; //unknown right now

					entries.push_back(fentry); //append to the vector
				}

			}
		}
	}

	header.numberFiles = numberFiles;

	int offset = sizeof(PAKheader) + (numberFiles * sizeof(PAKfileEntry)); //there's always 1 header, and there's a PAKfileEntry for every file so find the sum of
	for(unsigned int i = 0; i < entries.size(); i++)						//their sizes to find the offset for the first file
	{
		entries[i].offset = offset; //calculate all the offsets for each file
		offset += entries[i].size;
	}

	if(numberFiles) //if any files were found at all
	{
		PAKout.open(name, ofstream::binary | ofstream::trunc);
		if(PAKout.is_open())
		{
			PAKout.write((char *) &header, sizeof(header)); //write the header

			char *buffer;

			for(unsigned int i = 0; i < entries.size(); i++)
			{
				buffer = new char[sizeof(PAKfileEntry)]; //char array to hold each table of contents entry
				memcpy(buffer, &(entries[i]), sizeof(PAKfileEntry)); //copy over the current entry in the for loop

				for(int j = 0; j < sizeof(PAKfileEntry); j++)
				{
					if(header.additionEncrypt) buffer[j] += header.encryptVal; //encrypt each byte
					else buffer[j] -= header.encryptVal;
				}

				PAKout.write(buffer, sizeof(PAKfileEntry)); //finally write the entry

				delete [] buffer; //no memory leaks in this code, no sir
			}
			for(unsigned int i = 0; i < entries.size(); i++)
			{
				int size = entries[i].size;
				buffer = new char[size];

				fileIn.open(entries[i].fullname, ifstream::binary);
				if(fileIn.is_open())
				{
					fileIn.read(buffer, size); //read in the file so it can be encrypted then written into the PAK file

					for(int j = 0; j < size; j++)
					{
						if(header.additionEncrypt) buffer[j] += header.encryptVal; //more encryptan'
						else buffer[j] -= header.encryptVal;
					}

					PAKout.write(buffer, size); //write it out

					delete [] buffer;
					fileIn.close();
				}
				else return false; //fileIn not open
			}

			PAKout.close();
		}
		else return false; //PAKout not open
	}

	if(numberFiles < 1) return false; //no files found :(

	return true;
}

bool filePAK::readPAK(string PAKpath)
{
	ifstream PAKread;
	PAKread.open(PAKpath, ios::binary);
	if(PAKread.is_open())
	{

		PAKread.read((char *) &header, sizeof(PAKheader)); //read in the header information so you can decrypt

		if(strcmp(header.fileID, "DBPAK") != 0 || !(header.numberFiles > 0) || strcmp(header.version, "1.0") != 0) 
		{ //if the fileIDs or versions don't match or if there's 0 or less files
			PAKread.close(); 
			return false;
		}

		entries.clear(); //entries could be full from createPAK()

		char *buffer;

		for(int i = 0; i < header.numberFiles; i++)
		{
			buffer = new char[sizeof(PAKfileEntry)];
			PAKfileEntry entry;
			PAKread.read(buffer, sizeof(PAKfileEntry));

			for(int j = 0; j < sizeof(PAKfileEntry); j++)
			{
				if(header.additionEncrypt) buffer[j] -= header.encryptVal; //decrypt each byte
				else buffer[j] += header.encryptVal;
			}

			memcpy(&entry, buffer, sizeof(PAKfileEntry)); //store the decrypted stuff into the entry

			entries.push_back(entry); //append to the vector

			delete [] buffer;

		}

		PAKread.close();
	}
	else return false; //PAKread not open

	return true;
}

char* filePAK::grabPAKEntry(string name)
{
	for(int i = 0; i < header.numberFiles; i++)
	{
		if(strcmp(entries[i].name, name.c_str()) == 0)
		{
			char *buffer = NULL;

			ifstream PAKread;
			PAKread.open(pakname, ios::binary);
			if(PAKread.is_open())
			{
				buffer = new char[entries[i].size];
				PAKread.seekg(entries[i].offset, ifstream::beg); //seek to the offset of the file in the .pak file
				PAKread.read(buffer, entries[i].size); //read everything into the buffer

				for(unsigned int j = 0; j < entries[i].size; j++)
				{
					if(header.additionEncrypt) buffer[j] -= header.encryptVal; //decrypt it
					else buffer[j] += header.encryptVal;
				}

				return buffer; //return it all
			}
			else
			{
				cout << "Critical error: grabPAKEntry() stream not open\n";
				return buffer; //NULL
			}
		}
	}

	return NULL;
}

int filePAK::grabPAKEntrySize(string name)
{
	for(int i = 0; i < header.numberFiles; i++)
	{
		if(strcmp(entries[i].name, name.c_str()) == 0)
		{
			return entries[i].size;
		}
	}
	return -1; // This shouldn't happen. Treat as a critical error.
}

vector<string> filePAK::filetypes(string types)
{
	vector<string> splittypes;
	if(types.empty()) return splittypes;
	int numtypes = 0;
	size_t pos = -1;

	do
	{
		pos = types.find('|', pos+1);
		if(pos == string::npos) { numtypes++; break; }
		numtypes++;
	} while(true);

	string splittype;
	pos = -1;

	for(int i = 0; i < numtypes; i++)
	{
		splittype = types.substr(pos+1, types.find('|', pos+1));
		pos = types.find('|', pos+1);
		splittypes.push_back(splittype);
	}

	return splittypes;
}