#include "libPAK.h"

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <random>
#include <time.h>

#if !defined unix && !defined __unix__ && !defined __unix
#include "dirent.h" //Usually only in POSIX compilers, it allows you to find all the files contained within a folder
#else
#include <dirent.h>
#endif

libPAK::libPAK(void)
{
	pakloaded = false;
	lastEntry = 0;
}


libPAK::~libPAK(void)
{
	entries.clear();
}

bool libPAK::createPAK(string name, string entryPath, string types)
{
	pakloaded = false;
	pakname = name;
	srand((unsigned) time(NULL)); //seedin'
	ofstream PAKout;
	ifstream fileIn;
	int numberFiles = 0;

	header.additionEncrypt = ( (rand() % 2) ? true : false ); //Set random values for encrypting. The compact if-statement is used to prevent compiler warnings about casting int to a bool.
	header.encryptVal = (char) (rand() % 256);
	memcpy(header.fileID, "DBPAK\0", 6); //Using memcpy because lol char array
	memcpy(header.version, "1.0\0", 4);

	vector<string> correctTypes = split(types, '|');
	if(!entryPath.empty())
	{
		DIR *dir; //dirent.h stuff to accumulate all files within a folder
		dirent *entry = NULL;
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
						{
							string comparestr = entry->d_name;
							int found = comparestr.find_last_of('.');
							comparestr = comparestr.substr(found);

							if(!comparestr.compare(correctTypes[i]))
								correctType = true;
						}
					}


					if(correctType)
					{
						numberFiles++;
						if(!createEntry(entryPath, entry->d_name)) return false;
					}
				}
			}
		}

		delete dir, entry;
	}

	header.numberFiles = numberFiles;

	int offset = sizeof(PAKheader) + (numberFiles * sizeof(PAKfileEntry)); //there's always 1 header, and there's a PAKfileEntry for every file so find the sum of
	for(unsigned int i = 0; i < entries.size(); i++)						//their sizes to find the offset for the first file
	{
		entries[i].offset = offset; //calculate all the offsets for each file
		offset += entries[i].size;
	}

	PAKout.open(name, ofstream::binary | ofstream::trunc);
	if(PAKout.is_open())
	{
		PAKout.write((char *) &header, sizeof(header)); //write the header

		if(numberFiles) //if any files were found at all
		{
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
	}
	else return false; //PAKout not open

	return true;
}

bool libPAK::appendFolder(string folderPath, string types)
{
	vector<string> correctTypes = split(types, '|');

	DIR *dir; //dirent.h stuff to accumulate all files within a folder
	dirent *entry = NULL;
	dir = opendir(folderPath.c_str())
	if(dir)
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
					{
						string comparestr = entry->d_name;
						int found = comparestr.find_last_of('.');
						comparestr = comparestr.substr(found);

						if(!comparestr.compare(correctTypes[i]))
							correctType = true;
					}
				}


				if(correctType)
				{
					if(!appendFile(folderPath + entry->d_name)) return false;
				}
			}
		}
	}
	else
	{
		cout << "Dirent not working...\n";
		delete dir, entry;
		return false;
	}

	delete dir, entry;
	return true;
}

bool libPAK::createEntry(string path, string name)
{
	ifstream fileIn;
	PAKfileEntry fentry; //creates a new table of contents entry

	string entryName; //Sets up the path/name strings
	entryName += path;
	entryName += name;
	memcpy(fentry.name, name.c_str(), 50); //only the file name
	memcpy(fentry.fullname, entryName.c_str(), 150); //file name + folders

	fileIn.open(entryName, ifstream::binary | ifstream::ate);

	if(fileIn.is_open())
	{
		fentry.size = (unsigned int) fileIn.tellg(); //to calculate the file's size
	}
	else
	{
		return false;
	}

	fileIn.close();

	fentry.offset = 0; //unknown right now

	entries.push_back(fentry); //append to the vector

	return true;
}

bool libPAK::readPAK(string PAKpath)
{
	ifstream PAKread;
	PAKread.open(PAKpath, ios::binary);
	pakname = PAKpath;
	if(PAKread.is_open())
	{

		PAKread.read((char *) &header, sizeof(PAKheader)); //read in the header information so you can decrypt

		if(strcmp(header.fileID, "DBPAK") != 0 || strcmp(header.version, "1.0") != 0) 
		{ //if the fileIDs or versions don't match
			PAKread.close(); 
			return false;
		}

		entries.clear(); //entries could be full from createPAK()

		if(header.numberFiles > 0) //if it's not an empty pak
		{
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
		}

		PAKread.close();
		pakloaded = true;
	}
	else return false; //PAKread not open

	return true;
}

bool libPAK::rebuildPAK()
{
	if(changes.empty()) return false; //if no changes are buffered
	if(pakloaded)
	{
		ofstream PAKout;
		ifstream PAKin;

		PAKout.open(pakname+".new", ofstream::binary); //temporary new file to write to

		int numberFiles = 0;

		vector<PAKfileEntry> original(entries);

		for(unsigned int i = 0; i < changes.size(); i++)
			if(changes[i] >= 0) //count all changes that aren't deletions
				numberFiles++;

		header.numberFiles = numberFiles;

		int offset = sizeof(PAKheader) + (numberFiles * sizeof(PAKfileEntry));
		for(unsigned int i = 0; i < entries.size(); i++) //find out new offsets
		{
			if(changes[i] == -1) continue; //don't factor in deletions
			entries[i].offset = offset;
			offset += entries[i].size;
		}

		if(PAKout.is_open())
		{
			PAKout.write((char *) &header, sizeof(header)); //write out header
			
			char *buffer;

			for(unsigned int i = 0; i < entries.size(); i++)
			{
				if(changes[i] == -1) //if this change is a deletion
				{
					continue;
				}

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
				if(changes[i] == -1) continue; //again, don't factor in deletions
				if(changes[i] == 1)
				{
					PAKin.open(entries[i].fullname, ifstream::binary); //if it's an addition, load the file
				}
				else //if it's already in the PAK file, load it from there
				{
					PAKin.open(pakname, ifstream::binary);
					PAKin.seekg(original[i].offset);
				}

				if(PAKin.is_open())
				{
					buffer = new char[entries[i].size];
					PAKin.read(buffer, entries[i].size);

					if(changes[i] == 1)
					{
						for(unsigned int j = 0; j < entries[i].size; j++)
						{
							if(header.additionEncrypt) buffer[j] += header.encryptVal; //encrypt each byte
							else buffer[j] -= header.encryptVal;
						}
					}

					PAKout.write(buffer, entries[i].size);
				}
				else
				{
					original.clear();
					return false;
				}

				PAKin.close();

				delete [] buffer;
			}

			original.clear();
		}
		else
		{
			original.clear();
			return false;
		}

		PAKout.close();

		remove(pakname.c_str()); //deleting old PAK

		char* filename = new char[150];

		// windows complains when we don't use the secure alternatives to strcpy and strcat,
		// so we might as well use them and reap whatever benefits they may provide
#if !defined unix && !defined __unix__ && !defined __unix
		strcpy_s(filename, 150, pakname.c_str()); // I'm not exactly sure what the middle argument should be, but I found that 150 doesn't give me errors :/
		strcat_s(filename, 150, ".new");
#else
		strcpy(filename, pakname.c_str());
		strcat(filename, ".new");
#endif

		rename(filename, pakname.c_str());
		delete []filename;
	}
	else return false;

	for(unsigned int i = 0; i < entries.size(); i++) //erase all deletions
		if(changes[i] == -1)
			entries.erase(entries.begin()+i, entries.begin()+i+1);

	changes.clear();

	return true;
}

vector<int> libPAK::getChanges()
{
	return changes;
}

bool libPAK::appendFile(string name)
{
	int found = name.find_last_of("/\\"); //seperating path from filename
	string path = name.substr(0, found+1);
	string file = name.substr(found+1);

	for(unsigned int i = 0; i < entries.size(); i++) //if file name already exists
		if(!file.compare(entries[i].name))
			return false;

	if(changes.empty()) changes.assign(entries.size(), 0);
	changes.push_back(1);

	if(!createEntry(path, file)) return false;

	return true;
}

char* libPAK::getPAKEntryData(string name)
{
	if( PAKfileEntry *entry = getPAKEntry( name ) )
	{
		char *buffer = NULL;

		ifstream PAKread;
		PAKread.open(pakname, ios::binary);
		if(PAKread.is_open())
		{
			buffer = new char[entry->size];
			PAKread.seekg(entry->offset, ifstream::beg); //seek to the offset of the file in the .pak file
			PAKread.read(buffer, entry->size); //read everything into the buffer

			for(unsigned int j = 0; j < entry->size; j++)
			{
				if(header.additionEncrypt) buffer[j] -= header.encryptVal; //decrypt it
				else buffer[j] += header.encryptVal;
			}

			return buffer; //return it all
		}
		else
		{
			return buffer; //NULL
		}
	}

	return NULL; //PAK file isn't loaded, or entry isn't found
}

libPAK::PAKfileEntry *libPAK::getPAKEntry(string name)
{
	if(pakloaded)
	{
		for(int i = 0; i < header.numberFiles; i++)
		{
			if(strcmp(entries[i].name, name.c_str()) == 0)
			{
				return &entries[i];
			}
		}
	}

	return NULL; //PAK file isn't loaded, or entry isn't found
}

int libPAK::getPAKEntrySize(string name)
{
	if(pakloaded)
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
	return -2; //PAK file isn't loaded
}

vector<string> libPAK::getAllPAKEntries()
{
	vector<string> allentries;
	if(pakloaded && header.numberFiles > 0)
	{
		for(unsigned int i = 0; i < entries.size(); i++)
		{
			allentries.push_back(entries[i].name);
		}
	}

	return allentries; //NULL if pakloaded == false
}

bool libPAK::unPAKEntry(string name, string path)
{
	if(pakloaded)
	{
		ofstream output;
		output.open(path+name, ofstream::binary | ofstream::trunc);
		if(output.is_open())
		{
			char *buffer = getPAKEntryData(name);
			int size = getPAKEntrySize(name);
			if(buffer == NULL || size <= 0) return false;

			output.write(buffer, size);
			delete [] buffer;
		}
		else
		{
			return false;
		}

		output.close();
		return true;
	}
	return false;
}

vector<string> libPAK::split(const string &s, char delim) {
	vector<string> elems;
	stringstream ss(s);
	string item;
	while(getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

int libPAK::getNumPAKEntries()
{
	return header.numberFiles;
}

bool libPAK::removeFile(string name)
{
	if(pakloaded)
	{
		for(unsigned int i = 0; i < entries.size(); i++)
		{
			if(name.compare(entries[i].name) == 0)
			{
				if(changes.empty()) changes.assign(entries.size(), 0);
				changes[i] = -1;
				return true;
			}
		}
	}
	return false;
}

bool libPAK::isLoaded()
{
	return pakloaded;
}

void libPAK::discardChanges()
{
	if(changes.empty()) return;
	for(unsigned int i = 0; i < entries.size(); i++)
		if(changes[i] == 1)
			entries.erase(entries.begin()+i, entries.begin()+i+1);
	changes.clear();
}
