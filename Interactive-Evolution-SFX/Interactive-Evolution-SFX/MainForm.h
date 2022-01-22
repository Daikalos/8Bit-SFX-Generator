#pragma once

#include "SoundUC.h"

namespace Interactive_Evolution_SFX 
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			initialize_sounds();
		}

	protected:
		~MainForm()
		{
			delete components;
			delete[] sounds;
		}
	private: System::Windows::Forms::Button^ btnPlay;
	private: System::Windows::Forms::MenuStrip^ menuStrip;
	private: System::Windows::Forms::StatusStrip^ statusStrip;
	private: System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel1;
	private: System::Windows::Forms::FlowLayoutPanel^ pnlItems;
	private: System::Windows::Forms::ToolStripMenuItem^ optionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ loadToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ creditsToolStripMenuItem;


	private: System::ComponentModel::Container ^components;

	private: 
		array<SoundUC^>^ sounds;

		bool initialize_sounds();

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->btnPlay = (gcnew System::Windows::Forms::Button());
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->statusStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->pnlItems = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->optionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->creditsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip->SuspendLayout();
			this->statusStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// btnPlay
			// 
			this->btnPlay->Location = System::Drawing::Point(149, 658);
			this->btnPlay->Margin = System::Windows::Forms::Padding(2, 5, 2, 5);
			this->btnPlay->Name = L"btnPlay";
			this->btnPlay->Size = System::Drawing::Size(134, 50);
			this->btnPlay->TabIndex = 0;
			this->btnPlay->Text = L"Play";
			this->btnPlay->UseVisualStyleBackColor = true;
			// 
			// menuStrip
			// 
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->optionsToolStripMenuItem });
			this->menuStrip->Location = System::Drawing::Point(0, 0);
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->Size = System::Drawing::Size(1008, 24);
			this->menuStrip->TabIndex = 1;
			this->menuStrip->Text = L"menuStrip1";
			// 
			// statusStrip
			// 
			this->statusStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripStatusLabel1 });
			this->statusStrip->Location = System::Drawing::Point(0, 733);
			this->statusStrip->Name = L"statusStrip";
			this->statusStrip->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
			this->statusStrip->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->statusStrip->Size = System::Drawing::Size(1008, 28);
			this->statusStrip->SizingGrip = false;
			this->statusStrip->TabIndex = 2;
			this->statusStrip->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->BackColor = System::Drawing::Color::White;
			this->toolStripStatusLabel1->Font = (gcnew System::Drawing::Font(L"Arial Black", 12, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(96, 23);
			this->toolStripStatusLabel1->Text = L"...Loading";
			// 
			// pnlItems
			// 
			this->pnlItems->Location = System::Drawing::Point(149, 86);
			this->pnlItems->Name = L"pnlItems";
			this->pnlItems->Size = System::Drawing::Size(664, 512);
			this->pnlItems->TabIndex = 3;
			// 
			// optionsToolStripMenuItem
			// 
			this->optionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->loadToolStripMenuItem,
					this->creditsToolStripMenuItem, this->helpToolStripMenuItem
			});
			this->optionsToolStripMenuItem->Name = L"optionsToolStripMenuItem";
			this->optionsToolStripMenuItem->Size = System::Drawing::Size(61, 20);
			this->optionsToolStripMenuItem->Text = L"Options";
			// 
			// loadToolStripMenuItem
			// 
			this->loadToolStripMenuItem->Name = L"loadToolStripMenuItem";
			this->loadToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->loadToolStripMenuItem->Text = L"Load";
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->helpToolStripMenuItem->Text = L"Help";
			// 
			// creditsToolStripMenuItem
			// 
			this->creditsToolStripMenuItem->Name = L"creditsToolStripMenuItem";
			this->creditsToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->creditsToolStripMenuItem->Text = L"Credits";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(17, 33);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnableAllowFocusChange;
			this->BackColor = System::Drawing::Color::Gray;
			this->ClientSize = System::Drawing::Size(1008, 761);
			this->Controls->Add(this->pnlItems);
			this->Controls->Add(this->statusStrip);
			this->Controls->Add(this->btnPlay);
			this->Controls->Add(this->menuStrip);
			this->DoubleBuffered = true;
			this->Font = (gcnew System::Drawing::Font(L"Arial Black", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->ImeMode = System::Windows::Forms::ImeMode::On;
			this->MainMenuStrip = this->menuStrip;
			this->Margin = System::Windows::Forms::Padding(8, 9, 8, 9);
			this->MaximizeBox = false;
			this->Name = L"MainForm";
			this->RightToLeftLayout = true;
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Interactive Evolution SFX";
			this->TopMost = true;
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			this->statusStrip->ResumeLayout(false);
			this->statusStrip->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
};
}
