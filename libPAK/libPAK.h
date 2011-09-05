//
//			PAK File Compression
//
//		Packs any set of files (best used on resource files in a program. Images, sounds, etc.) into one .pak file.
//		Each file is encrypted with the Caesar encryption, it's really simple: choose a random value between 0 and 255 and
//		randomly choose to either add or subtract then store those values in the files header. Then whenever you store a
//		file you add or subtract that value to every byte.
//
//		Reminder: char represents a byte


#ifndef LIBPAK_H
#define LIBPAK_H

#if defined unix || defined __unix__ || defined __unix
#define NULL 0
#endif

///////////////
//Error Codes//
///////////////

#define PAK_SUCCESS				0
#define PAK_CRIT_ERR			-1		//Shouldn't happen ever

#define PAK_BAD_PAK				-100	//Header information is wrong
#define PAK_APPEND_SELF			-101	//Trying to append pak to itself
#define PAK_NOT_LOADED			-102	//PAK is not loaded
#define PAK_NO_CHANGES			-103	//No changes made
#define PAK_ENTRY_EXISTS		-104	//Trying to append duplicate entry
#define PAK_BAD_CHECKSUM		-105	//Bad checksum, TODO: Implement

#define PAK_FILE_OPEN_FAIL		-200	//Stream is not open
#define PAK_FILE_WRITE_FAIL		-201	//Write operation failed, TODO: Implement
#define PAK_FILE_READ_FAIL		-202	//Read operation failed, TODO: Implement
#define PAK_FILE_BAD_BUFFER		-203	//Buffer failed to load

#define PAK_DIRENT_FAIL			-300

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
	unsigned int size;
	unsigned int offset;
};

class libPAK
{
private:
	struct PAKheader //The header for the .pak file, the only thing not encrypted
	{
		char fileID[6]; //Identifier to make sure this is the type of .pak we want (and not some other sort of compression someone else made), I use "DBPAK"
		char version[4]; //Version of the format
		int numberFiles; //Total number of files
		bool additionEncrypt; //Random, whether to add or subtract "encryptVal" from each byte
		char encryptVal; //Random, value that is added or subtracted from each byte
	};

	string pakname; //name of the pak file
	bool pakloaded; //set to true after readPAK() is used
	PAKheader header; //the header
	vector<fileEntry> entries; //table of contents of all the entries
	vector<int> changes; //corresponds with entries: -1 = deleted, 0 = normal, 1 = added

	//Used to split the parameter types in createPAK() into a vector 
	vector<string> split(const string &s, char delim);

	//*******************************************
	//Create PAKfileEntry
	//
	//$fullname = folder to entry + name
	//
	//$name = only the name of the entry
	//
	//@returns =
	//		PAK_SUCCESS
	//		PAK_FILE_OPEN_FAIL
	//*******************************************
	int createEntry(string fullname, string name);

public:

	libPAK(void);
	~libPAK(void);

	//*******************************************
	//Creates new PAK file
	//
	//$name = name of PAK file to be created
	//
	//@returns =
	//		PAK_SUCCESS
	//		PAK_FILE_OPEN_FAIL
	//*******************************************
	int createPAK(string name);

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
	//********************************************
	int readPAK(string PAKpath);

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
	//@returns =
	//		char *
	//********************************************
	void crypt(char * buffer, int size, bool encrypt);

	//*******************************************
	//Ensure the PAK file is loaded
	//
	//@returns =
	//		bool
	//*******************************************
	bool isLoaded();

	//----------------------------------------------------------
	// The following functions require readPAK to be run first:
	//----------------------------------------------------------

	//*******************************************
	//Appends file to PAK
	//Run rebuildPAK() to flush changes
	//
	//$filePath - path to file to append
	//
	//@returns =
	//		createEntry()
	//		PAK_NOT_LOADED
	//		PAK_APPEND_SELF
	//		PAK_ENTRY_EXISTS
	//*******************************************
	int appendFile(string filePath);

	//*******************************************
	//Appends folder contents to PAK
	//Run rebuildPAK() to flush changes
	//
	//$folderPath = path to folder
	//
	//$types = all file types to be included,
	//separate by | ex: ".jpg|.png|.bmp"
	//
	//@returns =
	//		PAK_SUCCESS
	//		PAK_DIRENT_FAIL
	//		appendFile()
	//*******************************************
	int appendFolder(string folderPath, string types = "");

	//*******************************************
	//Removes file from PAK
	//Run rebuildPAK() to flush changes
	//
	//$filePath = path to file to remove
	//
	//@returns =
	//		PAK_SUCCESS
	//		PAK_NOT_LOADED
	//*******************************************
	int removeFile(string filePath);

	//*******************************************
	//Rebuilds the PAK file with buffered changes
	//
	//@returns =
	//		PAK_SUCCESS
	//		PAK_NO_CHANGES
	//		PAK_FILE_OPEN_FAIL
	//		PAK_NOT_LOADED
	//*******************************************
	int rebuildPAK();

	//*******************************************
	//Returns changes made
	//
	//@returns =
	//		vector<int>
	//*******************************************
	vector<int> getChanges();

	//*******************************************
	//Discards all removes and appends made to
	//the pak file
	//
	//@returns =
	//		void
	//*******************************************
	void discardChanges();

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
	//Returns names of all PAK entries within the
	//PAK File
	//
	//@returns =
	//		vector<string>
	//*******************************************
	vector<string> getAllFileEntries();

	//*******************************************
	//Returns the number of entries in the pak
	//file
	//
	//@returns =
	//		int
	//*******************************************
	int getNumPAKEntries()
	{ return header.numberFiles; }

	//*******************************************
	//Unpaks a PAK entry
	//
	//$name = entry to unPAK
	//
	//$path = folder to unPAK to
	//
	//@returns =
	//		PAK_SUCCESS
	//		PAK_NOT_LOADED
	//		PAK_FILE_OPEN_FAIL
	//*******************************************
	int unPAKEntry(string name, string path = "");

	//*******************************************
	//Returns name of the pak file
	//
	//@returns =
	//		string
	//*******************************************
	string getName()
	{ return pakname; }

	//*******************************************
	//Get a file data stored in the PAK file
	//
	//$name - name of entry to pull
	//
	//@returns =
	//		char *
	//*******************************************
	char *getFileEntryData(string name);
};

#endif
