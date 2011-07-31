#include "stdafx.h"
#include "Events.h"

using namespace PAKGUI;


// This event occurs every time an item in the PAK Contents list is checked or unchecked.
System::Void frmMain::lstPakContents_ItemCheck(System::Object^  sender, System::Windows::Forms::ItemCheckEventArgs^  e)
{
	IEnumerator^ item = lstPakContents->CheckedIndices->GetEnumerator(); // This is an enum for cycling through the checked items
	int numChecked = 0; // The number of items checked
	while ( item->MoveNext() )
	{
		++numChecked;
	}

	string tmp;
	MarshalString( lstPakContents->Items[ e->Index ]->Text, tmp );
	unsigned long long checkedsize = fileSizes[ tmp ];

	// Because of the way the checked items are updated in relation to the event, we have to account for a difference of 1 on two occasions.
	// these if-statements also allow us to perform actions specific to a check or uncheck event
	if ( e->CurrentValue == CheckState::Unchecked ) // If the event was triggered by a check
	{
		++numChecked;
		//lblPakSizeAfterPak->Text = atoi( cursize.c_str() ) + atoi( checkedsize.c_str() ) + " KB"; // Update Estimated size of PAK file after PAK'ing
		currentEstimatedSize += std::max( checkedsize, (unsigned long long) 1024 ); // calculate the new size (remember, still in bytes). also, we want to at least display 1KB of difference
	}
	else // If the event was triggered by an uncheck
	{
		--numChecked;
		//lblPakSizeAfterPak->Text = atoi( cursize.c_str() ) - atoi( checkedsize.c_str() ) + " KB"; // Update Estimated size of PAK file after PAK'ing
		currentEstimatedSize -= std::max( checkedsize, (unsigned long long) 1024 ); // calculate the new size (remember, still in bytes). also, we want to at least display 1KB of difference
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

// This event occurs when the user drags a file into the pak contents area
System::Void frmMain::lstPakContents_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
{

	// NOTE: drag/drop'ing folders are not working right now, and they might not ever be

	DataObject^ o = gcnew DataObject( DataFormats::FileDrop, e->Data->GetData(DataFormats::FileDrop) );
	if (!o->ContainsFileDropList() ) // probably shouldn't ever happen
	{
		// this error is worth the user's immediate attention
		MessageBox::Show( "Error adding files:\nNo eligible files could be found.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error  );
		log->displayMsg( "Error adding files:" + Environment::NewLine + "\tNo eligible files could be found." ); // still add it to the log anyways
		log->addBreak();
	}

	System::Collections::Specialized::StringCollection ^s = o->GetFileDropList();

	bool errors = false; // if there were errors adding files, this will be true
	// cycle through all the files that were dragged and add them to the list
	for each ( String ^p in s )
	{
		// calc file size
		unsigned long long bytes = getFileBytes( p );
		if ( bytes <= 0 )
		{
			if ( errors )
			{
				log->displayMsg( "\tFile \"" + p->Substring( p->LastIndexOf('\\')+1 ) + "\" contains no data." );
			}
			else
			{
				errors = true;
				log->displayMsg( "Error adding files: " + Environment::NewLine + "\tFile \"" + p->Substring( p->LastIndexOf('\\')+1 ) + "\" contains no data." );
			}
			continue;
		}
		string tmp;
		MarshalString( p->Substring( p->LastIndexOf('\\') + 1 ), tmp );
		if ( fileSizes[tmp] != 0 )
		{
			if ( errors )
			{
				log->displayMsg( "\tDuplicate file entry detected: \"" + p->Substring( p->LastIndexOf('\\')+1 ) + "\"" );
			}
			else 
			{
				errors = true;
				log->displayMsg( "Error adding file: " + Environment::NewLine + "\tDuplicate file entry detected: \"" + p->Substring( p->LastIndexOf('\\')+1 ) + "\"" );
			}
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

	if ( errors ) // if there were errors and the log isn't visible, warn them that there were errors and ask to display the log, otherwise we don't want to bug the user
	{
		log->addBreak();
		if ( !log->Visible )
		{
			System::Windows::Forms::DialogResult result = MessageBox::Show( "There were errors performing the previous action. Would you like to view the error log?",  "Errors", MessageBoxButtons::YesNo, MessageBoxIcon::Error );
			if ( result == System::Windows::Forms::DialogResult::Yes )
			{
				log->Visible = true;
			}
		}
	}

}