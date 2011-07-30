#include "stdafx.h"
#include "Events.h"

using namespace PAKGUI;

// This event occurs when the user clicks the Check all button
System::Void frmMain::btnCheckAll_Click(System::Object^  sender, System::EventArgs^  e)
{
	for each ( ListViewItem^ item in lstPakContents->Items )
	{
		item->Checked = true;
	}
}

// This event occurs when the user clicks the Check none button
System::Void frmMain::btnCheckNone_Click(System::Object^  sender, System::EventArgs^  e)
{
	for each ( ListViewItem^ item in lstPakContents->Items )
	{
		item->Checked = false;
	}
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

	bool errors = false;

	for each ( String ^file in files )
	{
		// calc file size
		long bytes = getFileBytes( file );
		string tmp;
		MarshalString( file->Substring( file->LastIndexOf('\\') + 1 ), tmp );
		if ( fileSizes[tmp] != 0 )
		{
			if ( errors )
			{
				log->displayMsg( "\tDuplicate file entry detected: \"" + file->Substring( file->LastIndexOf('\\') + 1 ) + "\"" );
			}
			else
			{
				errors = true;
				log->displayMsg( "Error adding files: " + Environment::NewLine + "\tDuplicate file entry detected: \"" + file->Substring( file->LastIndexOf('\\') + 1 ) + "\"" );
			}
			continue;
		}
		fileSizes[tmp] = bytes;
		String ^size = getFileSize( bytes );
		if ( size == "0 KB" )
		{
			if ( errors )
			{
				log->displayMsg( "\tFile \"" + file->Substring( file->LastIndexOf('\\')+1 ) + "\" contains no data." );
			}
			else
			{
				errors = true;
				log->displayMsg( "Error adding files: " + Environment::NewLine + "\tFile \"" + file->Substring( file->LastIndexOf('\\')+1 ) + "\" contains no data." );
			}
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

	log->addBreak();

	if ( !log->Visible && errors ) // if there were errors and the log isn't visible, warn them that there were errors and ask to display the log, otherwise we don't want to bug the user
	{
		System::Windows::Forms::DialogResult result = MessageBox::Show( "There were errors performing the previous action. Would you like to view the error log?",  "Errors", MessageBoxButtons::YesNo, MessageBoxIcon::Error );
		if ( result == System::Windows::Forms::DialogResult::Yes )
		{
			log->Visible = true;
		}
	}
}