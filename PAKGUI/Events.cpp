#include "stdafx.h"
#include "FrmMain.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <map>


using namespace PAKGUI;

filePAK pak;

map<string, long> fileSizes;
long currentEstimatedSize = 0;

// convert System::String (String ^) to std::string for use with LibPAK
void MarshalString ( String ^ s, string& os )
{
	using namespace Runtime::InteropServices;
	const char* chars = 
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

long getFileBytes( String ^filename )
{
	string dir;
	MarshalString( filename, dir );
	// Calculate file size in bytes
	long beg, end;
	ifstream file ( dir, ios::in|ios::binary); // open file
	beg = (long)file.tellg(); // beginning of file
	file.seekg (0, ios::end); // seek to end
	end = (long)file.tellg(); // end of file
	file.close(); // close file

	return end - beg;
}

String ^getFileSize( long bytes )
{
	// Convert
	int i; // number of iterations through the loop determine what unit to use
	double sizeconvert = bytes; // the size of the file in bytes
	if ( sizeconvert == 0 )
	{
		return gcnew String( "0 KB" ); // there was nothing in the file
	}
	for ( i = 0; sizeconvert > 1024.0; ++i, sizeconvert /= 1024.0 ) {} // convert from bytes to a more readable unit

	stringstream size; // this holds the final string to be returned
	size << (int) ceil( sizeconvert ); // get rid of decimals (round up)

	// append size unit to the end of the stringstream (GB = max supported unit, KB = min supported unit)
	// we only need decimal places for MB and GB
	if ( i == 1 )
	{
		size << " KB";
	}
	else if ( i == 2 )
	{
		size.str(string()); // clear stringstream
		size.setf( ios::fixed, ios::floatfield ); // set decimal
		size.precision(1);
		size << sizeconvert;
		size << " MB";
	}
	else if ( i >= 3 )
	{
		size.str(string()); // clear stringstream
		size.setf( ios::fixed, ios::floatfield ); // set decimal
		size.precision(2);
		size << sizeconvert;
		size << " GB";
	}
	else // if less than 1KB, round up to 1KB
	{
		size.str(string()); // clear stringstream
		size << "1 KB";
	}

	return gcnew String( size.str().c_str() );
}


// This event occurs every time an item in the PAK Contents list is checked or unchecked.
System::Void frmMain::lstPakContents_ItemCheck(System::Object^  sender, System::Windows::Forms::ItemCheckEventArgs^  e)
{
	/////////////////////////////
	// Item Progress Label
	/////////////////////////////
	IEnumerator^ myEnum1 = lstPakContents->CheckedIndices->GetEnumerator(); // This is an enum for cycling through the checked items
	int numChecked = 0; // The number of items checked
	while ( myEnum1->MoveNext() )
	{
		++numChecked;
	}

	string tmp;
	MarshalString( lstPakContents->Items[ e->Index ]->Text, tmp );
	long checkedsize = fileSizes[ tmp ];

	// Because of the way the checked items are updated in relation to the event, we have to account for a difference of 1 on two occasions.
	// these if-statements also allow us to perform actions specific to a check or uncheck event
	if ( e->CurrentValue == CheckState::Unchecked ) // If the event was triggered by a check
	{
		++numChecked;
		//lblPakSizeAfterPak->Text = atoi( cursize.c_str() ) + atoi( checkedsize.c_str() ) + " KB"; // Update Estimated size of PAK file after PAK'ing
		currentEstimatedSize += checkedsize; // calculate the new size (remember, still in bytes)
	}
	else // If the event was triggered by an uncheck
	{
		--numChecked;
		//lblPakSizeAfterPak->Text = atoi( cursize.c_str() ) - atoi( checkedsize.c_str() ) + " KB"; // Update Estimated size of PAK file after PAK'ing
		currentEstimatedSize -= checkedsize; // calculate the new size (remember, still in bytes)
	}

	// finally, determine the new units
	lblPakSizeAfterPak->Text = getFileSize( currentEstimatedSize );

	if ( numChecked > 0 ) // If there's items selected, enable buttons that depend on having selected items
	{
		btnPak->Enabled = true; // Pak button
		btnUnpak->Enabled = true; // Unpak button
		menuPak->Enabled = true; // menu pak button
		menuUnpak->Enabled = true; // menu unpak button
	}
	else if ( btnPak->Enabled || btnUnpak->Enabled ) // Otherwise, disable them if they are enabled
	{
		btnPak->Enabled = false; // Pak button
		btnUnpak->Enabled = false; // Unpak button
		menuPak->Enabled = false; // menu pak button
		menuUnpak->Enabled = false; // menu unpak button
	}

	lblItemProg->Text = "0 / " + numChecked; // Update the item progress label
}

// This event occurs when the Browse button is hit to add an entire directory to the PAK
System::Void frmMain::btnBrowseDir_Click(System::Object^  sender, System::EventArgs^  e)
{
	folderBrowserDialog->ShowDialog(); // This displays the folder selection dialog

	if ( folderBrowserDialog->SelectedPath->Length <= 0 ) // if the user didn't select any files
	{
		return;
	}

	array<String^> ^files = Directory::GetFiles( folderBrowserDialog->SelectedPath );

	for each ( String ^file in files )
	{
		// calc file size
		long bytes = getFileBytes( file );
		string tmp;
		MarshalString( file->Substring( file->LastIndexOf('\\') + 1 ), tmp );
		if ( fileSizes[tmp] != 0 )
		{
			MessageBox::Show( "Error adding file: \nDuplicate file entry detected: \"" + file->Substring( file->LastIndexOf('\\') + 1 ) + "\"",  "Error", MessageBoxButtons::OK, MessageBoxIcon::Error ); // CHANGE THIS LATER
			continue;
		}
		fileSizes[tmp] = bytes;
		String ^size = getFileSize( bytes );
		if ( size == "0 KB" )
		{
			MessageBox::Show( "Error adding file: \nFile \"" + file->Substring( file->LastIndexOf('\\')+1 ) + "\" contains no data.",  "Error", MessageBoxButtons::OK, MessageBoxIcon::Error ); // CHANGE THIS LATER
			continue;
		}

		// add an item with all the columns
		ListViewItem^ item = gcnew ListViewItem( file->Substring( file->LastIndexOf('\\') + 1 ) ); // create the item and give it name column
		item->SubItems->Add( file ); // directory column
		item->SubItems->Add( size ); // file size column
		item->SubItems->Add( "Not in PAK" ); // origin column. since you're manually adding the file, it can't already be in the pak
		item->SubItems->Add( file->Substring( file->LastIndexOf('.') ) ); // extension column
		item->Checked = true; // defaults to checked. since you are manually adding the file, it's assumed that you want to include it in your pak
		lstPakContents->Items->Add( item ); // finally add the item to the list

	}
}

// This event occurs when the Open menu item is clicked
System::Void frmMain::openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{

	if ( progressBar->Enabled ) // if the progress bar is enabled, this signifies that there is currently an operation being performed
	{
		// display a message box asking if the user is sure they want to interrupt the current operation
		System::Windows::Forms::DialogResult result = MessageBox::Show( "You are currently PAK'ing or UnPAK'ing a file. Interrupting the current operation may cause loss or corruption of data! Are you sure you want to open a PAK file?", "Operation in progress", MessageBoxButtons::YesNo, MessageBoxIcon::Warning, MessageBoxDefaultButton::Button2 );
		if ( result != System::Windows::Forms::DialogResult::Yes )
		{
			return;
		}
		else // perform resets on items in the form that are specific to performing an operation
		{
			progressBar->Value = 0;
			progressBar->Enabled = false;
			lblPercentProg->Text = "Idle";
			stsStatus->Text = "Idle";
			lblItemProg->Text = "0 " + lblItemProg->Text->Substring( lblItemProg->Text->IndexOf('/') );
		}
	}
	if ( lstPakContents->Items->Count ) // if the contents list contains any items, this signifies that there is a PAK file open
	{
		// display a message box asking if the user is sure they want to lose their current pak work
		System::Windows::Forms::DialogResult result = MessageBox::Show( "You currently have a PAK file open. If you open a PAK file, any unsaved changes to the currently open PAK will be lost! Are you sure you want to open a PAK file?", "PAK File already opened", MessageBoxButtons::YesNo, MessageBoxIcon::Warning, MessageBoxDefaultButton::Button2 );
		if ( result != System::Windows::Forms::DialogResult::Yes )
		{
			return;
		}
	}

	openPakDialog->ShowDialog(); // display file selection dialog
	string dir = ""; // will hold the full path to the pak
	MarshalString( openPakDialog->FileName, dir ); // convert the dialog result to a string that we can use
	if ( pak.readPAK( dir ) && pak.getNumPAKEntries() > 0 ) {

		// clear the content list
		for each ( ListViewItem ^item in lstPakContents->Items )
		{
			item->Remove();
		}

		fileSizes.clear();

		// adjust controls to reflect a new pak open
		lblItemProg->Text = "0 / " + pak.getNumPAKEntries();
		btnUnpak->Enabled = true;
		btnPak->Enabled = true;
		menuPak->Enabled = true;
		menuUnpak->Enabled = true;

		for each ( string name in pak.getAllPAKEntries() )
		{
			// add an item with all the columns
			String ^filename = gcnew String( name.c_str() ); // get the name, and convert it to a System::String

			// calc file size
			String ^size = getFileSize( pak.getPAKEntry( name )->size );

			ListViewItem^ item = gcnew ListViewItem( filename ); // create the item and give it name column
			item->SubItems->Add( openPakDialog->FileName ); // directory column
			item->SubItems->Add( size ); // file size column
			item->SubItems->Add( "In PAK" ); // origin column. since you're opening the pak, it must be in the pak
			item->SubItems->Add( filename->Substring( filename->LastIndexOf('.') ) ); // extension column
			item->Checked = true; // defaults to checked. since you are manually adding the file, it's assumed that you want to include it in your pak
			lstPakContents->Items->Add( item ); // finally add the item to the list

			long bytes = getFileBytes( openPakDialog->FileName );
			string tmp;
			MarshalString( filename, tmp );
			fileSizes[tmp] = bytes;

			lblPakSize->Text = getFileSize( bytes );
			lblPakSizeAfterPak->Text = lblPakSize->Text;
			lblNumFiles->Text = pak.getNumPAKEntries() + " Files";
			txtSaveDir->Text = openPakDialog->FileName;
			lblOrigDir->Text = openPakDialog->FileName;

		}

	}
	else
	{
		MessageBox::Show( "Error reading PAK:\nInvalid or corrupt PAK file.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error );
		return;
	}
}

// This event occurs when the New menu item is clicked
System::Void frmMain::newToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	if ( progressBar->Enabled ) // if the progress bar is enabled, this signifies that there is currently an operation being performed
	{
		// display a message box asking if the user is sure they want to interrupt the current operation
		System::Windows::Forms::DialogResult result = MessageBox::Show( "You are currently PAK'ing or UnPAK'ing a file. Interrupting the current operation may cause loss or corruption of data! Are you sure you want to make a new PAK file?", "Operation in progress", MessageBoxButtons::YesNo, MessageBoxIcon::Warning, MessageBoxDefaultButton::Button2 );
		if ( result != System::Windows::Forms::DialogResult::Yes )
		{
			return;
		}
		else // perform resets on items in the form that are specific to performing an operation
		{
			progressBar->Value = 0;
			progressBar->Enabled = false;
			lblPercentProg->Text = "Idle";
			stsStatus->Text = "Idle";
			lblItemProg->Text = "0 " + lblItemProg->Text->Substring( lblItemProg->Text->IndexOf('/') );
		}
	}
	if ( lstPakContents->Items->Count ) // if the contents list contains any items, this signifies that there is a PAK file open
	{
		// display a message box asking if the user is sure they want to lose their current pak work
		System::Windows::Forms::DialogResult result = MessageBox::Show( "You currently have a PAK file open. If you make a new PAK file, any unsaved changes to the currently open PAK will be lost! Are you sure you want to make a new PAK file?", "PAK File already opened", MessageBoxButtons::YesNo, MessageBoxIcon::Warning, MessageBoxDefaultButton::Button2 );
		if ( result != System::Windows::Forms::DialogResult::Yes )
		{
			return;
		}
	}

	// reset all items in the form to their original values
	lblItemProg->Text = "0 / 0";
	btnUnpak->Enabled = false;
	btnPak->Enabled = false;
	menuPak->Enabled = false;
	menuUnpak->Enabled = false;
	txtSaveDir->Text = "";
	lblOrigDir->Text = "None";
	lblPakSize->Text = "0 KB";
	lblPakSizeAfterPak->Text = "0 KB";
	lblNumFiles->Text = "0 Files";

	// clear the content list
	for each ( ListViewItem ^item in lstPakContents->Items )
	{
		item->Remove();
	}
}

// This event occurs when the user drags a file into the pak contents area
System::Void frmMain::lstPakContents_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
{

	// NOTE: folders are not working right now, and they might not ever be

	DataObject^ o = gcnew DataObject( DataFormats::FileDrop, e->Data->GetData(DataFormats::FileDrop) );
	if (!o->ContainsFileDropList() ) // should never happen
	{
		MessageBox::Show( "Error adding files:\nNo eligible files could be found.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error  );
	}

	System::Collections::Specialized::StringCollection ^s = o->GetFileDropList();

	// cycle through all the files that were dragged and add them to the list
	for each ( String ^p in s )
	{
		// calc file size
		long bytes = getFileBytes( p );
		if ( bytes <= 0 )
		{
			MessageBox::Show( "Error adding file: \nFile \"" + p->Substring( p->LastIndexOf('\\')+1 ) + "\" contains no data.",  "Error", MessageBoxButtons::OK, MessageBoxIcon::Error );
			continue;
		}
		string tmp;
		MarshalString( p->Substring( p->LastIndexOf('\\') + 1 ), tmp );
		if ( fileSizes[tmp] != 0 )
		{
			MessageBox::Show( "Error adding file: \nDuplicate file entry detected: \"" + p->Substring( p->LastIndexOf('\\')+1 ) + "\"",  "Error", MessageBoxButtons::OK, MessageBoxIcon::Error );
			continue;
		}
		fileSizes[tmp] = bytes;
		String ^size = getFileSize( bytes );

		// add an item with all the columns
		ListViewItem^ item = gcnew ListViewItem( p->Substring( p->LastIndexOf('\\') + 1 ) ); // create the item and give it name column
		item->SubItems->Add( p ); // directory column
		item->SubItems->Add( size ); // file size column
		item->SubItems->Add( "Not in PAK" ); // origin column. since you're manually adding the file, it can't already be in the pak
		item->SubItems->Add( p->Substring( p->LastIndexOf('.') ) ); // extension column
		item->Checked = true; // defaults to checked. since you are manually adding the file, it's assumed that you want to include it in your pak
		lstPakContents->Items->Add( item ); // finally add the item to the list
	}
}

// This event occurs when the user clicks the Select all button
System::Void frmMain::btnSelectAll_Click(System::Object^  sender, System::EventArgs^  e)
{
	for each ( ListViewItem^ item in lstPakContents->Items )
	{
		item->Checked = true;
	}
}

// This event occurs when the user clicks the Select none button
System::Void frmMain::btnSelectNone_Click(System::Object^  sender, System::EventArgs^  e)
{
	for each ( ListViewItem^ item in lstPakContents->Items )
	{
		item->Checked = false;
	}
}

// This event occurs when the user clicks the Unpak button
System::Void frmMain::btnUnpak_Click(System::Object^  sender, System::EventArgs^  e) 
{
	folderBrowserDialog->ShowDialog(); // open folder browser
}

// This event occurs when the user clicks the browse button for the pak directory
System::Void frmMain::btnSaveDirBrowse_Click(System::Object^  sender, System::EventArgs^  e)
{
	// if text is present in the save file text box and it appears to be a directory
	if ( txtSaveDir->Text->Length > 0 && ( txtSaveDir->Text->LastIndexOf( '\\' ) != -1 || txtSaveDir->Text->LastIndexOf( '/' ) != -1 ) )
	{
		// make that the initial directory and file for the dialog
		savePakDialog->InitialDirectory = txtSaveDir->Text->Substring( 0, txtSaveDir->Text->LastIndexOf( '\\' ) );

		// account for both types of slashes
		if ( txtSaveDir->Text->Length >= txtSaveDir->Text->LastIndexOf( '\\' ) ) // make sure there is a file present after the last slash
		{
			savePakDialog->FileName = txtSaveDir->Text->Substring( txtSaveDir->Text->LastIndexOf( '\\' )+1 );
		}
		else if ( txtSaveDir->Text->Length >= txtSaveDir->Text->LastIndexOf( '/' ) ) // make sure there is a file present after the last slash
		{
			savePakDialog->FileName = txtSaveDir->Text->Substring( txtSaveDir->Text->LastIndexOf( '/' )+1 );
		}
		else
		{
			savePakDialog->FileName = ""; // the user didn't enter a file after the directory
		}
	}
	else // otherwise, we can't ascertain any sort of directory structure
	{
		// so 
		savePakDialog->InitialDirectory = "";
		savePakDialog->FileName = "";
	}

	savePakDialog->ShowDialog();

	// if the user didn't select a file, then it returns the previously selected file without the full path (hence no slashes)
	// this can be a problem because we always want the full path in the directory text box
	if ( savePakDialog->FileName->IndexOf( '\\' ) != -1 || savePakDialog->FileName->IndexOf( '/' ) != -1 ) // if the user didn't select a file
	{
		txtSaveDir->Text = savePakDialog->FileName; // put that path in the save file text box
	}
}