//
//			PAK File Compression
//
//		Packs any set of files (best used on resource files in a program. Images, sounds, etc.) into one .pak file.
//		Each file is encrypted with the caesar encryption, it's really simple: choose a random value between 0 and 255 and
//		randomly choose to either add or subtract then store those values in the files header. Then whenever you store a
//		file you add or subtract that value to every byte.
//
//		Reminder: char represents a byte


#ifndef FILEPAK_H
#define FILEPAH_H

#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

class filePAK
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
	int lastEntry;
	PAKheader header; //the header
	vector<PAKfileEntry> entries; //table of contents of all the entries
	vector<int> changes; //corresponds with entries: -1 = deleted, 0 = normal, 1 = added

	//Used to split the parameter types in createPAK() into a vector 
	vector<string> filetypes(string types);

	//Create PAKfileEntry
	bool createEntry(string fullname, string name);

public:
	filePAK(void);
	~filePAK(void);

	//Creates new PAK file
	//name - name of PAK file to be created
	//entryPath - path to the folder that contains all the files you want in the PAK file
	//filetypes - all filetypes to be included, seperate by |, ex: ".jpg|.png|.bmp"
	//Returns true if nothing goes wrong
	bool createPAK(string name, string entryPath, string types = "");

	//Reads a PAK file's header and entries into memory so you can manipulate it/decrypt files stored within it
	//PAKpath - path to the PAK file to read
	//Returns true if nothing goes wrong
	bool readPAK(string PAKpath);

	//----------------------------------------------------------
	// The following functions require readPAK to be run first:
	//----------------------------------------------------------

	//Appends file to PAK
	//Run rebuildPAK() to flush changes
	//filePath - path to file to append
	//Returns true if nothing goes wrong
	//TODO: implement
	bool appendFile(string filePath);

	//Rebuilds the PAK file with buffered changes
	//Returns true if nothing goes wrong, also returns false if there are no changes to flush
	bool rebuildPAK();

	//
	bool removeFile(string name);

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
	bool unPAKEntry(string name, string path);

};

#endif