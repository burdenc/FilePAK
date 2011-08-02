#pragma once

#include "frmLog.h"

namespace PAKGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;


	/// <summary>
	/// Summary for frmMain
	/// </summary>

	public ref class frmMain : public System::Windows::Forms::Form
	{

		//private: System::Windows::Forms::Form ^log;
	private: frmLog ^log;

	public:
		frmMain(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			log = gcnew frmLog();
			log->VisibleChanged += gcnew System::EventHandler(this, &frmMain::frmLog_VisibleChanged);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~frmMain()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 

	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  editToolStripMenuItem;








	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Button^  btnUnpak;
	private: System::Windows::Forms::Button^  btnPak;







	private: System::Windows::Forms::Panel^  panel3;
	private: System::Windows::Forms::Button^  btnBrowseDir;






	private: System::Windows::Forms::ProgressBar^  progressBar;






	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  lblItemProg;


	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  lblPercentProg;

	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^  stsLblStatus;

	private: System::Windows::Forms::ToolStripStatusLabel^  stsStatus;


	private: System::Windows::Forms::ToolStripMenuItem^  newToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  menuCheckAll;
	private: System::Windows::Forms::ToolStripMenuItem^  menuCheckNone;




	private: System::Windows::Forms::ToolStripMenuItem^  pAKToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  menuPak;
	private: System::Windows::Forms::ToolStripMenuItem^  menuUnpak;
	private: System::Windows::Forms::Button^  btnCheckNone;




	private: System::Windows::Forms::Button^  btnCheckAll;


	private: System::Windows::Forms::OpenFileDialog^  openPakDialog;
	private: System::Windows::Forms::SaveFileDialog^  savePakDialog;



	private: System::Windows::Forms::FolderBrowserDialog^  addFolderBrowserDialog;
	private: System::Windows::Forms::Button^  btnAddFiles;

	private: System::Windows::Forms::Button^  btnDeleteSelected;
	private: System::Windows::Forms::ListView^  lstPakContents;
	private: System::Windows::Forms::ColumnHeader^  columnHeader1;
	private: System::Windows::Forms::ColumnHeader^  columnHeader2;
	private: System::Windows::Forms::ColumnHeader^  columnHeader3;
	private: System::Windows::Forms::ColumnHeader^  columnHeader4;

	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;



	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  txtSaveDir;



	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  btnSaveDirBrowse;

	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  lblNumFiles;

	private: System::Windows::Forms::Label^  lblPakSizeAfterPak;

	private: System::Windows::Forms::Label^  lblPakSize;

	private: System::Windows::Forms::ColumnHeader^  columnHeader5;
	private: System::Windows::Forms::Label^  lblOrigDir;

	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::ToolStripMenuItem^  viewToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  logToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem2;
	private: System::Windows::Forms::ToolStripMenuItem^  selectAllToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  selectNoneToolStripMenuItem;
	private: System::Windows::Forms::FolderBrowserDialog^  unpakFolderBrowserDialog;
	private: System::Windows::Forms::Button^  btnCancel;
	private: System::Windows::Forms::ToolStripMenuItem^  menuCancel;






	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->editToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuCheckAll = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuCheckNone = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->selectAllToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->selectNoneToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->viewToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->logToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pAKToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuPak = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuUnpak = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuCancel = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->lstPakContents = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader5 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader4 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
			this->btnAddFiles = (gcnew System::Windows::Forms::Button());
			this->btnBrowseDir = (gcnew System::Windows::Forms::Button());
			this->btnDeleteSelected = (gcnew System::Windows::Forms::Button());
			this->btnCheckNone = (gcnew System::Windows::Forms::Button());
			this->btnCheckAll = (gcnew System::Windows::Forms::Button());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->lblPercentProg = (gcnew System::Windows::Forms::Label());
			this->lblItemProg = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->progressBar = (gcnew System::Windows::Forms::ProgressBar());
			this->btnUnpak = (gcnew System::Windows::Forms::Button());
			this->btnPak = (gcnew System::Windows::Forms::Button());
			this->btnCancel = (gcnew System::Windows::Forms::Button());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->stsLblStatus = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->stsStatus = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->openPakDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->savePakDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->addFolderBrowserDialog = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->lblOrigDir = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->lblNumFiles = (gcnew System::Windows::Forms::Label());
			this->lblPakSizeAfterPak = (gcnew System::Windows::Forms::Label());
			this->lblPakSize = (gcnew System::Windows::Forms::Label());
			this->btnSaveDirBrowse = (gcnew System::Windows::Forms::Button());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->txtSaveDir = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->unpakFolderBrowserDialog = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->menuStrip1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->panel3->SuspendLayout();
			this->statusStrip1->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->fileToolStripMenuItem, 
				this->editToolStripMenuItem, this->viewToolStripMenuItem, this->pAKToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Margin = System::Windows::Forms::Padding(10);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(820, 24);
			this->menuStrip1->TabIndex = 2;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->newToolStripMenuItem, 
				this->openToolStripMenuItem, this->toolStripMenuItem1, this->exitToolStripMenuItem});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// newToolStripMenuItem
			// 
			this->newToolStripMenuItem->Name = L"newToolStripMenuItem";
			this->newToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::N));
			this->newToolStripMenuItem->Size = System::Drawing::Size(146, 22);
			this->newToolStripMenuItem->Text = L"New";
			this->newToolStripMenuItem->Click += gcnew System::EventHandler(this, &frmMain::newToolStripMenuItem_Click);
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
			this->openToolStripMenuItem->Size = System::Drawing::Size(146, 22);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &frmMain::openToolStripMenuItem_Click);
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(143, 6);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Alt | System::Windows::Forms::Keys::F4));
			this->exitToolStripMenuItem->Size = System::Drawing::Size(146, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &frmMain::exitToolStripMenuItem_Click);
			// 
			// editToolStripMenuItem
			// 
			this->editToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->menuCheckAll, 
				this->menuCheckNone, this->toolStripMenuItem2, this->selectAllToolStripMenuItem, this->selectNoneToolStripMenuItem});
			this->editToolStripMenuItem->Name = L"editToolStripMenuItem";
			this->editToolStripMenuItem->Size = System::Drawing::Size(39, 20);
			this->editToolStripMenuItem->Text = L"Edit";
			// 
			// menuCheckAll
			// 
			this->menuCheckAll->Name = L"menuCheckAll";
			this->menuCheckAll->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::A));
			this->menuCheckAll->Size = System::Drawing::Size(209, 22);
			this->menuCheckAll->Text = L"Check all";
			this->menuCheckAll->Click += gcnew System::EventHandler(this, &frmMain::checkAllToolStripMenuItem_Click);
			// 
			// menuCheckNone
			// 
			this->menuCheckNone->Name = L"menuCheckNone";
			this->menuCheckNone->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::D));
			this->menuCheckNone->Size = System::Drawing::Size(209, 22);
			this->menuCheckNone->Text = L"Check none";
			this->menuCheckNone->Click += gcnew System::EventHandler(this, &frmMain::checkNoneToolStripMenuItem_Click);
			// 
			// toolStripMenuItem2
			// 
			this->toolStripMenuItem2->Name = L"toolStripMenuItem2";
			this->toolStripMenuItem2->Size = System::Drawing::Size(206, 6);
			// 
			// selectAllToolStripMenuItem
			// 
			this->selectAllToolStripMenuItem->Name = L"selectAllToolStripMenuItem";
			this->selectAllToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Shift) 
				| System::Windows::Forms::Keys::A));
			this->selectAllToolStripMenuItem->Size = System::Drawing::Size(209, 22);
			this->selectAllToolStripMenuItem->Text = L"Select all";
			// 
			// selectNoneToolStripMenuItem
			// 
			this->selectNoneToolStripMenuItem->Name = L"selectNoneToolStripMenuItem";
			this->selectNoneToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Shift) 
				| System::Windows::Forms::Keys::D));
			this->selectNoneToolStripMenuItem->Size = System::Drawing::Size(209, 22);
			this->selectNoneToolStripMenuItem->Text = L"Select none";
			// 
			// viewToolStripMenuItem
			// 
			this->viewToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->logToolStripMenuItem});
			this->viewToolStripMenuItem->Name = L"viewToolStripMenuItem";
			this->viewToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->viewToolStripMenuItem->Text = L"View";
			// 
			// logToolStripMenuItem
			// 
			this->logToolStripMenuItem->CheckOnClick = true;
			this->logToolStripMenuItem->Name = L"logToolStripMenuItem";
			this->logToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::L));
			this->logToolStripMenuItem->Size = System::Drawing::Size(134, 22);
			this->logToolStripMenuItem->Text = L"Log";
			this->logToolStripMenuItem->Click += gcnew System::EventHandler(this, &frmMain::logToolStripMenuItem_Click);
			// 
			// pAKToolStripMenuItem
			// 
			this->pAKToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->menuPak, 
				this->menuUnpak, this->menuCancel});
			this->pAKToolStripMenuItem->Name = L"pAKToolStripMenuItem";
			this->pAKToolStripMenuItem->Size = System::Drawing::Size(41, 20);
			this->pAKToolStripMenuItem->Text = L"PAK";
			// 
			// menuPak
			// 
			this->menuPak->Enabled = false;
			this->menuPak->Name = L"menuPak";
			this->menuPak->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::P));
			this->menuPak->Size = System::Drawing::Size(183, 22);
			this->menuPak->Text = L"PAK / RePAK";
			this->menuPak->Click += gcnew System::EventHandler(this, &frmMain::menuPak_Click);
			// 
			// menuUnpak
			// 
			this->menuUnpak->Enabled = false;
			this->menuUnpak->Name = L"menuUnpak";
			this->menuUnpak->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::U));
			this->menuUnpak->Size = System::Drawing::Size(183, 22);
			this->menuUnpak->Text = L"UnPAK";
			this->menuUnpak->Click += gcnew System::EventHandler(this, &frmMain::menuUnpak_Click);
			// 
			// menuCancel
			// 
			this->menuCancel->Enabled = false;
			this->menuCancel->Name = L"menuCancel";
			this->menuCancel->Size = System::Drawing::Size(183, 22);
			this->menuCancel->Text = L"Cancel";
			this->menuCancel->Visible = false;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->lstPakContents);
			this->groupBox2->Controls->Add(this->btnAddFiles);
			this->groupBox2->Controls->Add(this->btnBrowseDir);
			this->groupBox2->Controls->Add(this->btnDeleteSelected);
			this->groupBox2->Controls->Add(this->btnCheckNone);
			this->groupBox2->Controls->Add(this->btnCheckAll);
			this->groupBox2->Location = System::Drawing::Point(14, 151);
			this->groupBox2->Margin = System::Windows::Forms::Padding(5);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Padding = System::Windows::Forms::Padding(10);
			this->groupBox2->Size = System::Drawing::Size(792, 334);
			this->groupBox2->TabIndex = 8;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"PAK Contents";
			// 
			// lstPakContents
			// 
			this->lstPakContents->AllowColumnReorder = true;
			this->lstPakContents->AllowDrop = true;
			this->lstPakContents->CheckBoxes = true;
			this->lstPakContents->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(5) {this->columnHeader1, 
				this->columnHeader2, this->columnHeader5, this->columnHeader4, this->columnHeader3});
			this->lstPakContents->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->lstPakContents->FullRowSelect = true;
			this->lstPakContents->Location = System::Drawing::Point(10, 58);
			this->lstPakContents->Name = L"lstPakContents";
			this->lstPakContents->Size = System::Drawing::Size(772, 266);
			this->lstPakContents->TabIndex = 7;
			this->lstPakContents->UseCompatibleStateImageBehavior = false;
			this->lstPakContents->View = System::Windows::Forms::View::Details;
			this->lstPakContents->ColumnClick += gcnew System::Windows::Forms::ColumnClickEventHandler(this, &frmMain::lstPakContents_ColumnClick);
			this->lstPakContents->ItemCheck += gcnew System::Windows::Forms::ItemCheckEventHandler(this, &frmMain::lstPakContents_ItemCheck);
			this->lstPakContents->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &frmMain::lstPakContents_DragDrop);
			this->lstPakContents->DragOver += gcnew System::Windows::Forms::DragEventHandler(this, &frmMain::lstPakContents_DragOver);
			// 
			// columnHeader1
			// 
			this->columnHeader1->Text = L"File name";
			this->columnHeader1->Width = 180;
			// 
			// columnHeader2
			// 
			this->columnHeader2->Text = L"Directory";
			this->columnHeader2->Width = 264;
			// 
			// columnHeader5
			// 
			this->columnHeader5->Text = L"Size";
			this->columnHeader5->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->columnHeader5->Width = 105;
			// 
			// columnHeader4
			// 
			this->columnHeader4->Text = L"Currently in PAK\?";
			this->columnHeader4->Width = 111;
			// 
			// columnHeader3
			// 
			this->columnHeader3->Text = L"File extension";
			this->columnHeader3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->columnHeader3->Width = 86;
			// 
			// btnAddFiles
			// 
			this->btnAddFiles->Location = System::Drawing::Point(205, 26);
			this->btnAddFiles->Margin = System::Windows::Forms::Padding(30, 3, 3, 3);
			this->btnAddFiles->Name = L"btnAddFiles";
			this->btnAddFiles->Size = System::Drawing::Size(75, 23);
			this->btnAddFiles->TabIndex = 4;
			this->btnAddFiles->Text = L"Add file(s)";
			this->btnAddFiles->UseVisualStyleBackColor = true;
			// 
			// btnBrowseDir
			// 
			this->btnBrowseDir->Location = System::Drawing::Point(419, 26);
			this->btnBrowseDir->Margin = System::Windows::Forms::Padding(30, 3, 3, 3);
			this->btnBrowseDir->Name = L"btnBrowseDir";
			this->btnBrowseDir->Size = System::Drawing::Size(94, 23);
			this->btnBrowseDir->TabIndex = 6;
			this->btnBrowseDir->Text = L"Add directory";
			this->btnBrowseDir->UseVisualStyleBackColor = true;
			this->btnBrowseDir->Click += gcnew System::EventHandler(this, &frmMain::btnBrowseDir_Click);
			// 
			// btnDeleteSelected
			// 
			this->btnDeleteSelected->Location = System::Drawing::Point(286, 26);
			this->btnDeleteSelected->Name = L"btnDeleteSelected";
			this->btnDeleteSelected->Size = System::Drawing::Size(100, 23);
			this->btnDeleteSelected->TabIndex = 5;
			this->btnDeleteSelected->Text = L"Delete highlighted";
			this->btnDeleteSelected->UseVisualStyleBackColor = true;
			this->btnDeleteSelected->Click += gcnew System::EventHandler(this, &frmMain::btnDeleteSelected_Click);
			// 
			// btnCheckNone
			// 
			this->btnCheckNone->Location = System::Drawing::Point(97, 26);
			this->btnCheckNone->Name = L"btnCheckNone";
			this->btnCheckNone->Size = System::Drawing::Size(75, 23);
			this->btnCheckNone->TabIndex = 3;
			this->btnCheckNone->Text = L"Check none";
			this->btnCheckNone->UseVisualStyleBackColor = true;
			this->btnCheckNone->Click += gcnew System::EventHandler(this, &frmMain::btnCheckNone_Click);
			// 
			// btnCheckAll
			// 
			this->btnCheckAll->Location = System::Drawing::Point(16, 26);
			this->btnCheckAll->Name = L"btnCheckAll";
			this->btnCheckAll->Size = System::Drawing::Size(75, 23);
			this->btnCheckAll->TabIndex = 2;
			this->btnCheckAll->Text = L"Check all";
			this->btnCheckAll->UseVisualStyleBackColor = true;
			this->btnCheckAll->Click += gcnew System::EventHandler(this, &frmMain::btnCheckAll_Click);
			// 
			// panel3
			// 
			this->panel3->Controls->Add(this->lblPercentProg);
			this->panel3->Controls->Add(this->lblItemProg);
			this->panel3->Controls->Add(this->label2);
			this->panel3->Controls->Add(this->label1);
			this->panel3->Controls->Add(this->progressBar);
			this->panel3->Controls->Add(this->btnUnpak);
			this->panel3->Controls->Add(this->btnPak);
			this->panel3->Controls->Add(this->btnCancel);
			this->panel3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel3->Location = System::Drawing::Point(3, 16);
			this->panel3->Margin = System::Windows::Forms::Padding(10);
			this->panel3->Name = L"panel3";
			this->panel3->Padding = System::Windows::Forms::Padding(0, 5, 0, 0);
			this->panel3->Size = System::Drawing::Size(786, 53);
			this->panel3->TabIndex = 5;
			// 
			// lblPercentProg
			// 
			this->lblPercentProg->Location = System::Drawing::Point(70, 8);
			this->lblPercentProg->Name = L"lblPercentProg";
			this->lblPercentProg->Size = System::Drawing::Size(99, 13);
			this->lblPercentProg->TabIndex = 6;
			this->lblPercentProg->Text = L"Idle";
			this->lblPercentProg->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// lblItemProg
			// 
			this->lblItemProg->Location = System::Drawing::Point(70, 25);
			this->lblItemProg->Name = L"lblItemProg";
			this->lblItemProg->Size = System::Drawing::Size(99, 13);
			this->lblItemProg->TabIndex = 5;
			this->lblItemProg->Text = L"0 / 0";
			this->lblItemProg->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(13, 25);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(30, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Item:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 8);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(51, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Progress:";
			// 
			// progressBar
			// 
			this->progressBar->Enabled = false;
			this->progressBar->Location = System::Drawing::Point(175, 8);
			this->progressBar->Name = L"progressBar";
			this->progressBar->Size = System::Drawing::Size(395, 37);
			this->progressBar->Style = System::Windows::Forms::ProgressBarStyle::Continuous;
			this->progressBar->TabIndex = 2;
			// 
			// btnUnpak
			// 
			this->btnUnpak->Enabled = false;
			this->btnUnpak->Location = System::Drawing::Point(583, 5);
			this->btnUnpak->Margin = System::Windows::Forms::Padding(10, 3, 3, 3);
			this->btnUnpak->Name = L"btnUnpak";
			this->btnUnpak->Size = System::Drawing::Size(95, 43);
			this->btnUnpak->TabIndex = 8;
			this->btnUnpak->Text = L"UnPAK";
			this->btnUnpak->UseVisualStyleBackColor = true;
			this->btnUnpak->Click += gcnew System::EventHandler(this, &frmMain::btnUnpak_Click);
			// 
			// btnPak
			// 
			this->btnPak->Enabled = false;
			this->btnPak->Location = System::Drawing::Point(684, 5);
			this->btnPak->Name = L"btnPak";
			this->btnPak->Size = System::Drawing::Size(95, 43);
			this->btnPak->TabIndex = 9;
			this->btnPak->Text = L"PAK\r\n";
			this->btnPak->UseVisualStyleBackColor = true;
			this->btnPak->Click += gcnew System::EventHandler(this, &frmMain::btnPak_Click);
			// 
			// btnCancel
			// 
			this->btnCancel->Location = System::Drawing::Point(611, 5);
			this->btnCancel->Name = L"btnCancel";
			this->btnCancel->Size = System::Drawing::Size(136, 43);
			this->btnCancel->TabIndex = 10;
			this->btnCancel->Text = L"Cancel";
			this->btnCancel->UseVisualStyleBackColor = true;
			this->btnCancel->Visible = false;
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->stsLblStatus, this->stsStatus});
			this->statusStrip1->Location = System::Drawing::Point(0, 577);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(820, 22);
			this->statusStrip1->SizingGrip = false;
			this->statusStrip1->TabIndex = 9;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// stsLblStatus
			// 
			this->stsLblStatus->Name = L"stsLblStatus";
			this->stsLblStatus->Size = System::Drawing::Size(45, 17);
			this->stsLblStatus->Text = L"Status: ";
			// 
			// stsStatus
			// 
			this->stsStatus->Name = L"stsStatus";
			this->stsStatus->Size = System::Drawing::Size(26, 17);
			this->stsStatus->Text = L"Idle";
			// 
			// openPakDialog
			// 
			this->openPakDialog->DefaultExt = L"pak";
			this->openPakDialog->Filter = L"PAK files|*.pak|All files|*.*";
			this->openPakDialog->ShowHelp = true;
			this->openPakDialog->SupportMultiDottedExtensions = true;
			this->openPakDialog->Title = L"Open PAK file";
			// 
			// savePakDialog
			// 
			this->savePakDialog->DefaultExt = L"pak";
			this->savePakDialog->Filter = L"PAK files|*.pak|All files|*.*";
			this->savePakDialog->InitialDirectory = L"%HOMEDRIVE%\\%HOMEPATH%\\";
			this->savePakDialog->SupportMultiDottedExtensions = true;
			this->savePakDialog->Title = L"Save PAK file";
			// 
			// addFolderBrowserDialog
			// 
			this->addFolderBrowserDialog->Description = L"Select a folder to add:";
			this->addFolderBrowserDialog->ShowNewFolderButton = false;
			// 
			// groupBox3
			// 
			this->groupBox3->BackColor = System::Drawing::SystemColors::Control;
			this->groupBox3->Controls->Add(this->lblOrigDir);
			this->groupBox3->Controls->Add(this->label4);
			this->groupBox3->Controls->Add(this->lblNumFiles);
			this->groupBox3->Controls->Add(this->lblPakSizeAfterPak);
			this->groupBox3->Controls->Add(this->lblPakSize);
			this->groupBox3->Controls->Add(this->btnSaveDirBrowse);
			this->groupBox3->Controls->Add(this->label7);
			this->groupBox3->Controls->Add(this->label8);
			this->groupBox3->Controls->Add(this->label5);
			this->groupBox3->Controls->Add(this->txtSaveDir);
			this->groupBox3->Controls->Add(this->label3);
			this->groupBox3->Location = System::Drawing::Point(14, 30);
			this->groupBox3->Margin = System::Windows::Forms::Padding(5);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Padding = System::Windows::Forms::Padding(10);
			this->groupBox3->Size = System::Drawing::Size(792, 111);
			this->groupBox3->TabIndex = 10;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"PAK Info";
			// 
			// lblOrigDir
			// 
			this->lblOrigDir->Location = System::Drawing::Point(140, 54);
			this->lblOrigDir->Name = L"lblOrigDir";
			this->lblOrigDir->Size = System::Drawing::Size(310, 19);
			this->lblOrigDir->TabIndex = 12;
			this->lblOrigDir->Text = L"None";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(15, 54);
			this->label4->Margin = System::Windows::Forms::Padding(3, 0, 10, 6);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(112, 13);
			this->label4->TabIndex = 11;
			this->label4->Text = L"Original PAK directory:";
			// 
			// lblNumFiles
			// 
			this->lblNumFiles->Location = System::Drawing::Point(662, 79);
			this->lblNumFiles->Name = L"lblNumFiles";
			this->lblNumFiles->Size = System::Drawing::Size(73, 13);
			this->lblNumFiles->TabIndex = 10;
			this->lblNumFiles->Text = L"0 Files";
			this->lblNumFiles->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// lblPakSizeAfterPak
			// 
			this->lblPakSizeAfterPak->Location = System::Drawing::Point(662, 54);
			this->lblPakSizeAfterPak->Name = L"lblPakSizeAfterPak";
			this->lblPakSizeAfterPak->Size = System::Drawing::Size(66, 13);
			this->lblPakSizeAfterPak->TabIndex = 9;
			this->lblPakSizeAfterPak->Text = L"0 KB";
			this->lblPakSizeAfterPak->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// lblPakSize
			// 
			this->lblPakSize->Location = System::Drawing::Point(662, 29);
			this->lblPakSize->Name = L"lblPakSize";
			this->lblPakSize->Size = System::Drawing::Size(66, 13);
			this->lblPakSize->TabIndex = 8;
			this->lblPakSize->Text = L"0 KB";
			this->lblPakSize->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// btnSaveDirBrowse
			// 
			this->btnSaveDirBrowse->Location = System::Drawing::Point(375, 73);
			this->btnSaveDirBrowse->Margin = System::Windows::Forms::Padding(3, 3, 3, 6);
			this->btnSaveDirBrowse->Name = L"btnSaveDirBrowse";
			this->btnSaveDirBrowse->Size = System::Drawing::Size(75, 23);
			this->btnSaveDirBrowse->TabIndex = 1;
			this->btnSaveDirBrowse->Text = L"Browse";
			this->btnSaveDirBrowse->UseVisualStyleBackColor = true;
			this->btnSaveDirBrowse->Click += gcnew System::EventHandler(this, &frmMain::btnSaveDirBrowse_Click);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(477, 79);
			this->label7->Margin = System::Windows::Forms::Padding(6, 6, 24, 6);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(158, 13);
			this->label7->TabIndex = 6;
			this->label7->Text = L"Number of files currently in PAK:";
			this->label7->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(492, 54);
			this->label8->Margin = System::Windows::Forms::Padding(6, 6, 24, 6);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(143, 13);
			this->label8->TabIndex = 5;
			this->label8->Text = L"Estimated Size after PAK\'ing:";
			this->label8->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(507, 29);
			this->label5->Margin = System::Windows::Forms::Padding(6, 6, 24, 6);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(128, 13);
			this->label5->TabIndex = 4;
			this->label5->Text = L"Current PAK Size on disk:";
			this->label5->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// txtSaveDir
			// 
			this->txtSaveDir->Location = System::Drawing::Point(140, 76);
			this->txtSaveDir->Margin = System::Windows::Forms::Padding(3, 3, 10, 6);
			this->txtSaveDir->Name = L"txtSaveDir";
			this->txtSaveDir->Size = System::Drawing::Size(222, 20);
			this->txtSaveDir->TabIndex = 0;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(28, 79);
			this->label3->Margin = System::Windows::Forms::Padding(3, 0, 10, 6);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(99, 13);
			this->label3->TabIndex = 0;
			this->label3->Text = L"PAK Save location:";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->panel3);
			this->groupBox1->Location = System::Drawing::Point(14, 495);
			this->groupBox1->Margin = System::Windows::Forms::Padding(5);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(792, 72);
			this->groupBox1->TabIndex = 11;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"PAK";
			// 
			// unpakFolderBrowserDialog
			// 
			this->unpakFolderBrowserDialog->Description = L"Select a folder to UnPAK the files to:";
			// 
			// frmMain
			// 
			this->AcceptButton = this->btnPak;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(820, 599);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->menuStrip1);
			this->Controls->Add(this->statusStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(836, 637);
			this->MinimumSize = System::Drawing::Size(836, 637);
			this->Name = L"frmMain";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->Text = L"pakGUI";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		// This event occurs every time an item in the PAK Contents list is checked or unchecked.
	private: System::Void lstPakContents_ItemCheck(System::Object^  sender, System::Windows::Forms::ItemCheckEventArgs^  e);

			 // This event occurs when the Browse button is hit to add an entire directory to the PAK
	private: System::Void btnBrowseDir_Click(System::Object^  sender, System::EventArgs^  e);

			 // This event occurs when the Open menu item is clicked
	private: System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);

			 // This event occurs when the New menu item is clicked
	private: System::Void newToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);

			 // This event occurs when the user drags a file into the pak contents area
	private: System::Void lstPakContents_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);
	private: inline System::Void lstPakContents_DragOver(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
			 {
				 if(e->Data->GetDataPresent(DataFormats::FileDrop))
				 {
					 e->Effect = DragDropEffects::All;
				 }
				 else
				 {
					 e->Effect = DragDropEffects::None;
				 }
			 }

			 // This event occurs when the user clicks the Select all button
	private: System::Void btnCheckAll_Click(System::Object^  sender, System::EventArgs^  e);

			 // This event occurs when the user clicks the Select none button
	private: System::Void btnCheckNone_Click(System::Object^  sender, System::EventArgs^  e);

			 // exit menu item clicked
	private: inline System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->Visible = false;
				 delete this;
			 }

			 // unpak button clicked
	private: System::Void btnUnpak_Click(System::Object^  sender, System::EventArgs^  e);

			 // TODO
			 // ADD COMMENTS TO FUNCS BELOW

	private: System::Void btnSaveDirBrowse_Click(System::Object^  sender, System::EventArgs^  e);
	private: inline System::Void logToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: inline System::Void frmLog_VisibleChanged(System::Object^  sender, System::EventArgs^  e);
	private: inline System::Void checkAllToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 btnCheckAll_Click( sender, e );
			 }
	private: inline System::Void checkNoneToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 btnCheckNone_Click( sender, e );
			 }
	private: System::Void btnPak_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btnDeleteSelected_Click(System::Object^  sender, System::EventArgs^  e);
	private: inline System::Void menuPak_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 btnPak_Click( sender, e );
			 }
	private: inline System::Void menuUnpak_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 btnUnpak_Click( sender, e );
			 }

	private: inline System::Void updateStatus();

			 // This event occurs when a column head is clicked
	private: inline System::Void lstPakContents_ColumnClick(System::Object^  sender, System::Windows::Forms::ColumnClickEventArgs^  e);

	};	

	// Implements the manual sorting of items by columns.
	ref class ListViewItemComparer: public IComparer
	{
	private:
		int col;
		int sort; // 1 = ascending, -1 = descending

	public:
		ListViewItemComparer()
		{
			col = 0;
			sort = 1; // default ascending
		}

		ListViewItemComparer( int column )
		{
			col = column;
			sort = 1;
		}

		ListViewItemComparer( int column, int sorting )
		{
			col = column;
			sort = sorting;
		}
		virtual int Compare( Object^ x, Object^ y )
		{
			return sort * String::Compare( (dynamic_cast<ListViewItem^>(x))->SubItems[ col ]->Text,
				(dynamic_cast<ListViewItem^>(y))->SubItems[ col ]->Text );
		}
	};

}

