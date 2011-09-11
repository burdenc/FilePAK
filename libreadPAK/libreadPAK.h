#ifndef LIBREADPAK_H
#define LIBREADPAK_H

///////////////
//Error Codes//
///////////////

#define PAK_SUCCESS				0
#define PAK_CRIT_ERR			-1		//Shouldn't happen ever

#define PAK_BAD_PAK				-100	//Header information is wrong
#define PAK_NOT_LOADED			-102	//PAK is not loaded
#define PAK_BAD_CHECKSUM		-105	//Bad checksum
#define PAK_BAD_ARG				-106	//Bad argument supplied

#define PAK_FILE_OPEN_FAIL		-200	//Stream is not open
#define PAK_FILE_BAD_BUFFER		-203	//Buffer failed to load

///////////////////
//End Error Codes//
///////////////////

#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

struct fileEntry
{
	char name[50];
	char fullname[150];
	int size;
	int offset;
};


class libreadPAK
{
private:
	struct PAKheader //The header for the .pak file, the only thing not encrypted
	{
		char fileID[6]; //Identifier to make sure this is the type of .pak we want, I use "DBPAK"
		char version[4]; //Version of the format
		int numberFiles; //Total number of files
		int encryptData[4];
		short encryptType;
	};

	string pakname; //name of the pak file
	bool pakloaded; //set to true after readPAK() is used
	PAKheader header; //the header
	vector<fileEntry> entries; //table of contents of all the entries


	//*******************************************
	//Reads a PAK file's header and entries into
	//memory so you can manipulate it/decrypt
	//files stored within it
	//
	//$buffer = buffer to en/decrypt
	//
	//$size = size of the buffer
	//
	//$encrypt = if true encrypt buffer, otherwise
	//decrypt it.
	//
	//$type = encryption algorithm to use:
	//			0 - None
	//			1 - Caesar
	//
	//@returns =
	//		PAK_SUCCESS
	//		PAK_BAD_ARG
	//********************************************
	int crypt(char * buffer, int size, bool encrypt, int type);

	//*******************************************
	//Gets the checksum of the PAK file
	//Automatically ignores the last 40 bytes as
	//those are the old checksum.
	//
	//$filename = file to hash
	//
	//$checkAll = if false it will not include
	//the last 40 bytes in the checksum because
	//that's what the old checksum is
	//
	//@returns =
	//		string
	//		""
	//*******************************************
	string getChecksum(string filename, bool checkAll = true);

public:
	libreadPAK(void);
	~libreadPAK(void);

	//*******************************************
	//Get a file stored in the PAK file
	//
	//$name = name of the file stored in the PAK
	//file (don't include the folder/path)
	//
	//@returns =
	//		PAKfileEntry *
	//*******************************************
	fileEntry *getFileEntry(string name);

	//*******************************************
	//Get a file data stored in the PAK file
	//
	//$name - name of entry to pull
	//
	//@returns =
	//		char *
	//*******************************************
	char *getFileEntryData(string name);

	//*******************************************
	//Returns name of the pak file
	//
	//@returns =
	//		string
	//*******************************************
	string getName()
	{ return pakname; }

	//*******************************************
	//Ensure the PAK file is loaded
	//
	//@returns =
	//		bool
	//*******************************************
	bool isLoaded()
	{ return pakloaded; }

	//*******************************************
	//Reads a PAK file's header and entries into
	//memory so you can manipulate it/decrypt
	//files stored within it
	//
	//$PAKpath = path to the PAK file to read
	//
	//@returns =
	//		PAK_SUCCESS
	//		PAK_BAD_PAK
	//		PAK_FILE_OPEN_FAIL
	//		PAK_BAD_CHECKSUM
	//********************************************
	int readPAK(string PAKpath);
};

#endif