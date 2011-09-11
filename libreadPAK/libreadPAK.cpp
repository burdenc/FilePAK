#include "libreadPAK.h"

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <random>
#include <time.h>
#include "sha1.h"

libreadPAK::libreadPAK(void)
{
	pakloaded = false;
}


libreadPAK::~libreadPAK(void)
{
	entries.clear();
}

int libreadPAK::crypt(char * buffer, int size, bool encrypt, int type)
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

string libreadPAK::getChecksum(string filename, bool checkAll)
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
		_itoa(rawhash[i], hashbuffer, 16);
		hash += hashbuffer;
	}

	return hash;
}

fileEntry *libreadPAK::getFileEntry(string name)
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

char *libreadPAK::getFileEntryData(string name)
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

int libreadPAK::readPAK(string PAKpath)
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