//
//			PAK File Compression
//
//		Packs any set of files (best used on resource files in a program. Images, sounds, etc.) into one .pak file.
//		Each file is encrypted with the caesar encryption, it's really simple: choose a random value between 0 and 255 and
//		randomly choose to either add or subtract then store those values in the files header. Then whenever you store a
//		file you add or subtract that value to every byte.
//
//		Reminder: char represents a byte


#ifndef LIBPAK_H
#define LIBPAK_H

///////////////
//Error Codes//
///////////////

#define PAK_SUCCESS				0
#define	PAK_FAIL				!0
#define PAK_CRIT_ERR			-1

#define PAK_BAD_PAK				-100
#define PAK_APPEND_SELF			-101
#define PAK_NOT_LOADED			-102
#define PAK_NO_CHANGES			-103
#define PAK_ENTRY_EXISTS		-104
#define PAK_BAD_CHECKSUM		-105

#define PAK_FILE_OPEN_FAIL		-200
#define PAK_FILE_WRITE_FAIL		-201
#define PAK_FILE_READ_FAIL		-202
#define PAK_FILE_BAD_BUFFER		-203

#define PAK_DIRENT_FAIL			-300

///////////////////
//End Error Codes//
///////////////////

#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

class libPAK
{
private:
	struct PAKheader //The header for the .pak file, the only thing not encyrpted
	{
		char fileID[6]; //Identifier to make sure this is the type of .pak we want (and not some other sort of compression someone else made), I use "DBPAK"
		char version[4]; //Version of the format
		int numberFiles; //Total number of files
		bool additionEncrypt; //Random, whether to add or subtract "encryptVal" from each byte
		char encryptVal; //Random, value that is added or subtracted from each byte
	};

	struct PAKfileEntry //Basically an entry in a table of contents for each file stored in the .pak file
	{
		char name[50]; //name of the file, must be unique from other files
		char fullname[150]; //name of the file + the folder it is in
		unsigned int size; //size of the file in bytes
		unsigned int offset; //offset of where the files in located in the .pak file in bytes
	};

	string pakname; //name of the pak file
	bool pakloaded; //set to true after readPAK() is used
	PAKheader header; //the header
	vector<PAKfileEntry> entries; //table of contents of all the entries
	vector<int> changes; //corresponds with entries: -1 = deleted, 0 = normal, 1 = added

	//Used to split the parameter types in createPAK() into a vector 
	vector<string> split(const string &s, char delim);

	//Create PAKfileEntry
	int createEntry(string fullname, string name);

public:
	libPAK(void);
	~libPAK(void);

	//Creates new PAK file
	//$name = name of PAK file to be created
	//$entryPath = path to the folder that contains all the files you want in the PAK file
	//$types = all filetypes to be included, seperate by |, ex: ".jpg|.png|.bmp"
	//@returns = 0, -200 (Refer to error codes above)
	int createPAK(string name, string entryPath = "", string types = "");

	//Reads a PAK file's header and entries into memory so you can manipulate it/decrypt files stored within it
	//PAKpath - path to the PAK file to read
	//@returns - Refer to error codes
	int readPAK(string PAKpath);

	//@return
	//	true - readPAK() has successfully loaded the pak file
	bool isLoaded();

	//----------------------------------------------------------
	// The following functions require readPAK to be run first:
	//----------------------------------------------------------

	//Appends file to PAK
	//Run rebuildPAK() to flush changes
	//filePath - path to file to append
	//@return - Refer to error codes
	int appendFile(string filePath);

	//Appends folder contents to PAK
	//Run rebuildPAK() to flush changes
	//folderPath - path to folder
	//types - all filetypes to be included, seperate by |, ex: ".jpg|.png|.bmp"
	//@return
	//	0 - Success
	//	-1 - Fo
	int appendFolder(string folderPath, string types = "");

	//Removes file to PAK
	//Run rebuildPAK() to flush changes
	//filePath - path to file to append
	//Returns true if nothing goes wrong
	int removeFile(string filePath);

	//Rebuilds the PAK file with buffered changes
	//Returns true if nothing goes wrong, also returns false if there are no changes to flush
	int rebuildPAK();

	//Returns changes made
	vector<int> getChanges();

	//Discards all removes and appends made to the pak file
	void discardChanges();

	//Get a file data stored in the PAK file
	//name - name of the file stored in the PAK file (don't include the folder/path)
	//Returns a pointer to the file data in memory
	char* getPAKEntryData(string name);

	//Get a file stored in the PAK file
	//name - name of the file stored in the PAK file (don't include the folder/path)
	//Returns a pointer to the PAKfileEntry
	PAKfileEntry *getPAKEntry(string name);

	//name - name of the file stored in the PAK file (don't include the folder/path)
	//Returns size of a file in the PAK file
	int getPAKEntrySize(string name);

	//Returns names of all PAK entries within the
	vector<string> getAllPAKEntries();

	//Returns the number of entries in the pak file
	int getNumPAKEntries();

	//Unpaks a PAK entry
	//name - entry to unPAK
	//path - folder to unPAK to
	//Returns true if nothing goes wrong
	int unPAKEntry(string name, string path = "");

};

#endif
