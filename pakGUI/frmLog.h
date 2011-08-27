/*
	This file is part of pakGUI.

	pakGUI is a user-friendly graphical user interface for libPAK which allows the
	packing and un-packing of several files into one easily manageable resource file.

	pakGUI, pakEXE, and libPAK
	Copyright © 2011  Drew Burden, Hogg Studios

	pakGUI was developed by Drew Burden in cooperation with Cassidy Burden
	and released by Hogg Studios under the GPLv3 License.

	pakGUI is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	pakGUI is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with pakGUI. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

namespace pakGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for frmLog
	/// </summary>
	public ref class frmLog : public System::Windows::Forms::Form
	{
	public:
		System::Windows::Forms::TextBox^  txtLog;
		frmLog(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		System::Void displayMsg( String ^msg ) {
			txtLog->AppendText( msg + Environment::NewLine );
		}

		System::Void addBreak( void ) {
			txtLog->AppendText( "------------------------------" + Environment::NewLine );
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~frmLog()
		{
			if (components)
			{
				delete components;
			}
		}
	protected: 

	protected: 
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Button^  btnClear;

	private: System::Windows::Forms::Button^  btnOK;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->txtLog = (gcnew System::Windows::Forms::TextBox());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->btnClear = (gcnew System::Windows::Forms::Button());
			this->btnOK = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1->SuspendLayout();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// txtLog
			// 
			this->txtLog->AcceptsReturn = true;
			this->txtLog->AcceptsTab = true;
			this->txtLog->Dock = System::Windows::Forms::DockStyle::Fill;
			this->txtLog->Location = System::Drawing::Point(3, 3);
			this->txtLog->Multiline = true;
			this->txtLog->Name = L"txtLog";
			this->txtLog->ReadOnly = true;
			this->txtLog->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->txtLog->Size = System::Drawing::Size(577, 279);
			this->txtLog->TabIndex = 0;
			this->txtLog->WordWrap = false;
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				100)));
			this->tableLayoutPanel1->Controls->Add(this->txtLog, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->panel1, 0, 1);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 40)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(583, 325);
			this->tableLayoutPanel1->TabIndex = 3;
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->btnClear);
			this->panel1->Controls->Add(this->btnOK);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(3, 288);
			this->panel1->Name = L"panel1";
			this->panel1->Padding = System::Windows::Forms::Padding(5);
			this->panel1->Size = System::Drawing::Size(577, 34);
			this->panel1->TabIndex = 1;
			// 
			// btnClear
			// 
			this->btnClear->Dock = System::Windows::Forms::DockStyle::Left;
			this->btnClear->Location = System::Drawing::Point(5, 5);
			this->btnClear->Name = L"btnClear";
			this->btnClear->Size = System::Drawing::Size(75, 24);
			this->btnClear->TabIndex = 1;
			this->btnClear->Text = L"Clear Log";
			this->btnClear->UseVisualStyleBackColor = true;
			this->btnClear->Click += gcnew System::EventHandler(this, &frmLog::btnClear_Click);
			// 
			// btnOK
			// 
			this->btnOK->Dock = System::Windows::Forms::DockStyle::Right;
			this->btnOK->Location = System::Drawing::Point(497, 5);
			this->btnOK->Name = L"btnOK";
			this->btnOK->Size = System::Drawing::Size(75, 24);
			this->btnOK->TabIndex = 0;
			this->btnOK->Text = L"OK";
			this->btnOK->UseVisualStyleBackColor = true;
			this->btnOK->Click += gcnew System::EventHandler(this, &frmLog::btnOK_Click);
			// 
			// frmLog
			// 
			this->AcceptButton = this->btnOK;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(583, 325);
			this->Controls->Add(this->tableLayoutPanel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::SizableToolWindow;
			this->MinimumSize = System::Drawing::Size(191, 127);
			this->Name = L"frmLog";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->Text = L"Log";
			this->TopMost = true;
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &frmLog::frmLog_FormClosing);
			this->Shown += gcnew System::EventHandler(this, &frmLog::frmLog_Shown);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: inline System::Void btnOK_Click(System::Object^  sender, System::EventArgs^  e);
	private: inline System::Void frmLog_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
	private: inline System::Void btnClear_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void frmLog_Shown(System::Object^  sender, System::EventArgs^  e)
			 {
				 // Scrolls txtbox to the bottom
				 // This has to be done in this separate event for the sole reason that the visiblechanged event causes the ScrollToCaret method to fail the first time the dialog is shown.
				 txtLog->Focus();
				 txtLog->Select( txtLog->Text->Length, 0 ); // put the caret at the bottom
				 txtLog->ScrollToCaret(); // scroll to the caret
			 }
};
}
