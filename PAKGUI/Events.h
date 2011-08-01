#pragma once

#include <map>

extern filePAK pak;
extern map<string, unsigned long long> fileSizes;
extern unsigned long long currentEstimatedSize;

extern inline void MarshalString ( System::String ^ s, string& os );
extern unsigned long long getFileBytes( System::String ^filename );
extern System::String ^getFileSize( unsigned long long bytes );
extern int numChecked;
extern int itemProgressed;