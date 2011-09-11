#include "libPAK.h"

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <random>
#include <time.h>
#include "sha1.h"

#if !defined unix && !defined __unix__ && !defined __unix
#include "dirent.h" //Usually only in POSIX compilers, it allows you to find all the files contained within a folder
#else
#include <dirent.h>
#endif

libPAK::libPAK(void)
{
	pakloaded = false;
}


libPAK::~libPAK(void)
{
	entries.clear();
	changes.clear();
}

int libPAK::createPAK(string name, int encryptType)
{
	memcpy(header.fileID, "DBPAK\0", 6); //Using memcpy because lol char array
	memcpy(header.version, "1.1\0", 4);
	header.numberFiles = 0;

	setupCrypt(encryptType);

	pakloaded = false; //reset the loaded state
	pakname = name; //save the name of the PAK file

	ofstream PAKout;

	PAKout.open(name, ofstream::binary | ofstream::trunc);
	if(PAKout.is_open())
	{
		PAKout.write((char *) &header, sizeof(header)); //write the header
	}
	else return PAK_FILE_OPEN_FAIL; //PAKout not open

	PAKout.flush();

	string hash = getChecksum(pakname);

	PAKout.write(hash.c_str(), 40);

	PAKout.close();

	return PAK_SUCCESS;
}

int libPAK::appendFolder(string folderPath, string types)
{
	//This is all essentially a copy of what's in createPAK

	vector<string> correctTypes = split(types, '|');

	DIR *dir; //dirent.h stuff to accumulate all files within a folder
	dirent *entry = NULL;
	dir = opendir(folderPath.c_str());
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
					int err = appendFile(folderPath + entry->d_name);
					if(err == PAK_SUCCESS) return err; //return error code if fails
				}
			}
		}
	}
	else
	{
		delete dir, entry;
		return PAK_DIRENT_FAIL;
	}

	delete dir, entry;
	return PAK_SUCCESS;
}

int libPAK::createEntry(string path, string name)
{
	ifstream fileIn;
	fileEntry fentry; //creates a new table of contents entry

	string entryName; //Sets up the path/name strings
	entryName += path;
	entryName += name;
	memcpy(fentry.name, name.c_str(), 50); //only the file name
	memcpy(fentry.fullname, entryName.c_str(), 150); //file name + folders

	fileIn.open(entryName, ifstream::binary | ifstream::ate);

	if(fileIn.is_open())
		fentry.size = (unsigned int) fileIn.tellg(); //to calculate the file's size
	else
		return PAK_FILE_OPEN_FAIL;

	fileIn.close();

	fentry.offset = 0; //unknown right now

	entries.push_back(fentry); //append to the vector

	return PAK_SUCCESS;
}

int libPAK::readPAK(string PAKpath)
{
	ifstream PAKread;
	pakname = PAKpath;

	string filehash = getChecksum(pakname, false);

	PAKread.open(PAKpath, ios::binary);
	
	if(PAKread.is_open())
	{
		PAKread.read((char *) &header, sizeof(PAKheader)); //read in the header information so you can decrypt

		if(strcmp(header.fileID, "DBPAK") != 0) 
		{ //if the fileIDs don't match
			PAKread.close(); 
			return PAK_BAD_PAK;
		}

		PAKread.seekg(-40, ios::end);

		char *storedhash = new char[41];
		PAKread.read(storedhash, 40);
		storedhash[40] = '\0';

		if(strcmp(filehash.c_str(), storedhash) != 0)
		{
			PAKread.close();
			return PAK_BAD_CHECKSUM;
		}

		PAKread.seekg(sizeof(PAKheader), ios::beg);


		entries.clear(); //entries could be full from createPAK()

		if(header.numberFiles > 0) //if it's not an empty pak
		{
			char *buffer;

			for(int i = 0; i < header.numberFiles; i++)
			{
				buffer = new char[sizeof(fileEntry)];
				fileEntry entry;
				PAKread.read(buffer, sizeof(fileEntry));

				crypt(buffer, sizeof(fileEntry), false, header.encryptType);

				memcpy(&entry, buffer, sizeof(fileEntry)); //store the decrypted stuff into the entry

				entries.push_back(entry); //append to the vector

				delete [] buffer;

			}
		}

		PAKread.close();
		pakname = PAKpath;
		pakloaded = true;
	}
	else return PAK_FILE_OPEN_FAIL; //PAKread not open

	return PAK_SUCCESS;
}

int libPAK::rebuildPAK()
{
	if(changes.empty()) return PAK_NO_CHANGES; //if no changes are buffered
	if(pakloaded)
	{
		ofstream PAKout;
		ifstream PAKin;

		PAKout.open(pakname+".new", ofstream::binary); //temporary new file to write to

		int numberFiles = 0;

		vector<fileEntry> original(entries);

		for(unsigned int i = 0; i < changes.size(); i++)
			if(changes[i] >= 0) //count all changes that aren't deletions
				numberFiles++;

		header.numberFiles = numberFiles;

		int offset = sizeof(PAKheader) + (numberFiles * sizeof(fileEntry));
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

				buffer = new char[sizeof(fileEntry)]; //char array to hold each table of contents entry
				memcpy(buffer, &(entries[i]), sizeof(fileEntry)); //copy over the current entry in the for loop

				crypt(buffer, sizeof(fileEntry), true, header.encryptType);

				PAKout.write(buffer, sizeof(fileEntry)); //finally write the entry

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
						crypt(buffer, entries[i].size, true, header.encryptType);
					}

					PAKout.write(buffer, entries[i].size);
				}
				else
				{
					original.clear();
					return PAK_FILE_OPEN_FAIL;
				}

				PAKin.close();

				delete [] buffer;
			}

			original.clear();
		}
		else
		{
			original.clear();
			return PAK_FILE_OPEN_FAIL;
		}
		PAKout.flush();

		string hash = getChecksum(pakname+".new");
		PAKout.write(hash.c_str(), 40);

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
		delete [] filename;

		/*int err = updateChecksum();
		if(err != PAK_SUCCESS)
		{
			return err;
		}*/
	}
	else return PAK_NOT_LOADED;

	for(unsigned int i = 0; i < entries.size(); i++) //erase all deletions
		if(changes[i] == -1)
			entries.erase(entries.begin()+i, entries.begin()+i+1);

	changes.clear();

	return PAK_SUCCESS;
}

vector<int> libPAK::getChanges()
{
	return changes;
}

int libPAK::appendFile(string name)
{
	if(pakloaded)
	{
		if(name.compare(pakname) == 0) return PAK_APPEND_SELF; //trying to append pak file to itself

		int found = name.find_last_of("/\\"); //separating path from filename
		string path = name.substr(0, found+1);
		string file = name.substr(found+1);

		for(unsigned int i = 0; i < entries.size(); i++) //if file name already exists
			if(!file.compare(entries[i].name))
				return PAK_ENTRY_EXISTS;

		if(changes.empty()) changes.assign(entries.size(), 0); //if there's no changes fill the changes vector with 0's (0 = no change)
		changes.push_back(1); //1 = append

		return createEntry(path, file); //should return PAK_SUCCESS
	}
	return PAK_NOT_LOADED;
}

fileEntry *libPAK::getFileEntry(string name)
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

vector<string> libPAK::getAllFileEntries()
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

int libPAK::unPAKEntry(string name, string path)
{
	if(pakloaded)
	{
		ofstream output;
		output.open(path+name, ofstream::binary | ofstream::trunc);
		if(output.is_open())
		{
			char *buffer = getFileEntryData(name);
			if(buffer == NULL || sizeof(buffer) <= 0) return PAK_FILE_BAD_BUFFER;

			output.write(buffer, getFileEntry(name)->size);
			delete [] buffer;
		}
		else
		{
			return PAK_FILE_OPEN_FAIL;
		}

		output.close();
		return PAK_SUCCESS;
	}
	return PAK_NOT_LOADED;
}

vector<string> libPAK::split(const string &s, char delim)
{
	vector<string> elems;
	stringstream ss(s);
	string item;

	while(getline(ss, item, delim))
		elems.push_back(item);

	return elems;
}

int libPAK::removeFile(string name)
{
	if(pakloaded)
	{
		for(unsigned int i = 0; i < entries.size(); i++)
		{
			if(name.compare(entries[i].name) == 0)
			{
				if(changes.empty()) changes.assign(entries.size(), 0);
				changes[i] = -1; //-1 = deletion
				return PAK_SUCCESS;
			}
		}
	}
	return PAK_NOT_LOADED;
}

bool libPAK::isLoaded()
{
	return pakloaded;
}

void libPAK::discardChanges()
{
	//delete all changes
	if(changes.empty()) return;
	for(unsigned int i = 0; i < entries.size(); i++)
		if(changes[i] == 1)
			entries.erase(entries.begin()+i, entries.begin()+i+1);
	changes.clear();
}

int libPAK::crypt(char * buffer, int size, bool encrypt, int type)
{
	if(type < 0 || type > 1)
		return PAK_BAD_ARG;
	if(type == 1) //Caesar
	{
		srand((unsigned int) header.encryptData[1]); //seeding
		char randEncryptVal; //when using the same seed you should get the same exact random numbers
		for(int j = 0; j < size; j++)
		{
			randEncryptVal = (rand() % 256);
			if(header.encryptData[0] == 0) buffer[j] += (((encrypt) ? 1 : -1) * randEncryptVal);
			else buffer[j] -= (((encrypt) ? 1 : -1) * randEncryptVal);
		}
	}

	return PAK_SUCCESS;
}

char *libPAK::getFileEntryData(string name)
{
	ifstream pakread;
	char* buffer;
	fileEntry* fentry = getFileEntry(name);
	pakread.open(pakname);


	if(pakread.is_open())
	{
		pakread.seekg(fentry->offset, ios_base::beg);
		buffer = new char[fentry->size];
		pakread.read(buffer, fentry->size);

		crypt(buffer, fentry->size, false, header.encryptType);

		return buffer;
	}

	return NULL;
}

string libPAK::getChecksum(string filename, bool checkAll)
{
	unsigned int len;

	string hash;
	unsigned rawhash[5];
	
	ifstream PAKin;

	//char* buffer = new char[1024];
	unsigned char buffer[1024];

	SHA1 sha;
	sha.Reset();

	PAKin.open(filename, ios::binary);

	PAKin.seekg(0, ios::end);
	int length = ((int) PAKin.tellg());
	length -= (checkAll) ? 0 : 40;
	PAKin.seekg(0, ios::beg);

	if(length < 0) return "";

	bool escape = true;
	if(PAKin.is_open())
	{
		do
		{
			len = 1024;
			if((length - PAKin.tellg()) <= len)
			{ len = (length - (unsigned int) PAKin.tellg()); escape = false; }

			PAKin.read((char *)buffer,len);
			sha.Input(buffer, len);
		} while(escape);
	}
	else { return ""; }
	PAKin.close();

	sha.Result(rawhash);
	char hashbuffer[10];
	for(int i = 0; i < 5; i++)
	{
		itoa(rawhash[i], hashbuffer, 16);
		hash += hashbuffer;
	}

	return hash;
}

int libPAK::setupCrypt(int type)
{
	if(strcmp(header.fileID, "DBPAK") == 0) //quick check to see if the function
	{							//is called via createPAK or when file is loaded
		if(type < 1 || type > 1)
			return PAK_BAD_ARG;
		header.encryptType = type;
		if(type == 1) //Caesar
		{
			srand((unsigned) time(NULL));
			header.encryptData[0] = (rand() % 2);
			header.encryptData[1] = (rand() % 256);
		}
	}

	return PAK_SUCCESS;
}