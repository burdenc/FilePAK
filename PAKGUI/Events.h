#pragma once

#include <map>


#define		IDLE		"Idle"
#define		UNPAK		"UnPAK'ing - "
#define		PAK			"PAK'ing - "
#define		DONE		"Done"
#define		CANCEL		"Cancelled"

#define		ASCENDING	1
#define		DESCENDING	-1


extern	libPAK								pak;
extern	map<string, long long>				fileSizes;
extern	long long							currentEstimatedSize;
extern	int									numChecked;
extern	int									itemProgressed;
extern	int									percentProg;
extern	string								prog;
extern	int									sorting;


extern	inline void			MarshalString ( System::String ^ s, string& os );
extern	inline long long	getFileBytes( System::String ^filename );
extern	System::String		^getFileSize( long long bytes );