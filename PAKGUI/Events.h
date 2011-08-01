#pragma once

#include <map>


#define		IDLE	"Idle"
#define		UNPAK	"UnPAK'ing - "
#define		PAK		"PAK'ing - "
#define		DONE	"Done"
#define		CANCEL	"Cancelled"


extern	filePAK								pak;
extern	map<string, unsigned long long>		fileSizes;
extern	unsigned long long					currentEstimatedSize;
extern	int									numChecked;
extern	int									itemProgressed;
extern	int									percentProg;
extern	string								prog;


extern	inline void			MarshalString ( System::String ^ s, string& os );
extern	unsigned long long	getFileBytes( System::String ^filename );
extern	System::String		^getFileSize( unsigned long long bytes );