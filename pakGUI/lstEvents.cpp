#include "stdafx.h"
#include "events.h"

using namespace pakGUI;


// This event occurs every time an item in the PAK Contents list is checked or unchecked.
System::Void frmMain::lstPakContents_ItemCheck(System::Object^  sender, System::Windows::Forms::ItemCheckEventArgs^  e)
{
	string tmp;
	MarshalString( lstPakContents->Items[ e->Index ]->Text, tmp );
	long long checkedsize = fileSizes[ tmp ];

	// determine if the event was triggered by either a check or an uncheck
	if ( e->CurrentValue == CheckState::Unchecked ) // If the event was triggered by a check
	{
		++numChecked;
		currentEstimatedSize += std::max( checkedsize, (long long) 1024 ); // calculate the new size (remember, still in bytes). also, we want to at least display 1KB of difference
	}
	else // If the event was triggered by an uncheck
	{
		--numChecked;
		currentEstimatedSize -= std::max( checkedsize, (long long) 1024 ); // calculate the new size (remember, still in bytes). also, we want to at least display 1KB of difference
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

	updateStatus();
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

	lstPakContents->BeginUpdate();
	// cycle through all the files that were dragged and add them to the list
	for each ( String ^p in s )
	{
		// this is mainly to detect if the user dropped a folder
		if ( !File::Exists( p ) )
		{
			continue;
		}

		// calc file size
		long long bytes = getFileBytes( p );
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
		if ( p->LastIndexOf('.') == -1 )
		{
			item->SubItems->Add( "" ); // extension column
		}
		else
		{
			item->SubItems->Add( p->Substring( p->LastIndexOf('.') ) ); // extension column
		}
		item->Checked = true; // defaults to checked. since you are manually adding the file, it's assumed that you want to include it in your pak
		lstPakContents->Items->Add( item ); // finally add the item to the list
	}
	lstPakContents->EndUpdate();

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

inline System::Void frmMain::lstPakContents_ColumnClick(System::Object^  sender, System::Windows::Forms::ColumnClickEventArgs^  e)
{
	lstPakContents->BeginUpdate();

	if ( sorting == ASCENDING )
	{
		sorting = DESCENDING;
	}
	else
	{
		sorting = ASCENDING;
	}

	lstPakContents->ListViewItemSorter = gcnew ListViewItemComparer( e->Column, sorting );

	lstPakContents->EndUpdate();
}