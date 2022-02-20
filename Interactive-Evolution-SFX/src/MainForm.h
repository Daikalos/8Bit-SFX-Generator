#pragma once

#include <iostream>
#include <tchar.h>

#include "utilities.h"
#include "Player.h"
#include "SoundUC.h"
#include "InfoForm.h"
#include "Evolution.h"

#include <resid/sid.h>

#include <msclr/marshal_cppstd.h>

namespace IESFX
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MainForm : public Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();

			srand((unsigned)time(NULL));

			if (!initialize())
				throw gcnew WarningException("failed to initialize system");

			_color = Color::White;
			_prev = 0;
		}

	protected:
		~MainForm()
		{
			delete components;
		}

	private: System::Windows::Forms::MenuStrip^ menuStrip;
	private: System::Windows::Forms::StatusStrip^ statusStrip;
	private: System::Windows::Forms::ToolStripStatusLabel^ statusLabel;
	private: System::Windows::Forms::ToolStripMenuItem^ optionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ loadButton;
	private: System::Windows::Forms::Panel^ pnlItems;
	private: System::Windows::Forms::ToolStripMenuItem^ otherToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^ helpButton;
	private: System::Windows::Forms::ToolStrip^ botStripTool;
	private: System::Windows::Forms::ToolStripButton^ showNextButton;
	private: System::Windows::Forms::ToolStripButton^ playButton;
	private: System::Windows::Forms::ToolStripButton^ pauseButton;
	private: System::Windows::Forms::ToolStripButton^ resetButton;
	private: System::Windows::Forms::TrackBar^ mutationSizeSlider;
	private: System::Windows::Forms::TrackBar^ mutationRateSlider;
	private: System::Windows::Forms::Label^ mutationSizeTextLabel;
	private: System::Windows::Forms::Label^ mutationRateTextLabel;
	private: System::Windows::Forms::Label^ mutationRateLabel;
	private: System::Windows::Forms::Label^ mutationSizeLabel;
	private: System::Windows::Forms::TrackBar^ volumeSlider;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ToolStripMenuItem^ saveButton;
	private: System::Windows::Forms::Panel^ volumePanel;

	private: System::Windows::Forms::Panel^ modifiersPanel;
	private: System::ComponentModel::Container^ components;
	
#pragma region Windows Form Designer generated code
	private:
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->optionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->otherToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->statusStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->statusLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->pnlItems = (gcnew System::Windows::Forms::Panel());
			this->botStripTool = (gcnew System::Windows::Forms::ToolStrip());
			this->playButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->pauseButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->showNextButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->resetButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->mutationSizeSlider = (gcnew System::Windows::Forms::TrackBar());
			this->mutationRateSlider = (gcnew System::Windows::Forms::TrackBar());
			this->mutationSizeTextLabel = (gcnew System::Windows::Forms::Label());
			this->mutationRateTextLabel = (gcnew System::Windows::Forms::Label());
			this->mutationRateLabel = (gcnew System::Windows::Forms::Label());
			this->mutationSizeLabel = (gcnew System::Windows::Forms::Label());
			this->volumeSlider = (gcnew System::Windows::Forms::TrackBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->modifiersPanel = (gcnew System::Windows::Forms::Panel());
			this->volumePanel = (gcnew System::Windows::Forms::Panel());
			this->menuStrip->SuspendLayout();
			this->statusStrip->SuspendLayout();
			this->pnlItems->SuspendLayout();
			this->botStripTool->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->mutationSizeSlider))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->mutationRateSlider))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->volumeSlider))->BeginInit();
			this->modifiersPanel->SuspendLayout();
			this->volumePanel->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip
			// 
			this->menuStrip->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->optionsToolStripMenuItem,
					this->otherToolStripMenuItem
			});
			this->menuStrip->Location = System::Drawing::Point(0, 0);
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->Size = System::Drawing::Size(675, 24);
			this->menuStrip->TabIndex = 1;
			this->menuStrip->Text = L"menuStrip";
			// 
			// optionsToolStripMenuItem
			// 
			this->optionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->saveButton,
					this->loadButton
			});
			this->optionsToolStripMenuItem->Name = L"optionsToolStripMenuItem";
			this->optionsToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->optionsToolStripMenuItem->Text = L"File";
			// 
			// saveButton
			// 
			this->saveButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"saveButton.Image")));
			this->saveButton->Name = L"saveButton";
			this->saveButton->Size = System::Drawing::Size(100, 22);
			this->saveButton->Text = L"Save";
			this->saveButton->Click += gcnew System::EventHandler(this, &MainForm::saveButton_Click);
			// 
			// loadButton
			// 
			this->loadButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"loadButton.Image")));
			this->loadButton->Name = L"loadButton";
			this->loadButton->Size = System::Drawing::Size(100, 22);
			this->loadButton->Text = L"Load";
			this->loadButton->Click += gcnew System::EventHandler(this, &MainForm::loadButton_Click);
			// 
			// otherToolStripMenuItem
			// 
			this->otherToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->helpButton });
			this->otherToolStripMenuItem->Name = L"otherToolStripMenuItem";
			this->otherToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->otherToolStripMenuItem->Text = L"Help";
			// 
			// helpButton
			// 
			this->helpButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"helpButton.Image")));
			this->helpButton->Name = L"helpButton";
			this->helpButton->Size = System::Drawing::Size(180, 22);
			this->helpButton->Text = L"Help";
			this->helpButton->Click += gcnew System::EventHandler(this, &MainForm::helpButton_Click);
			// 
			// statusStrip
			// 
			this->statusStrip->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->statusStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->statusLabel });
			this->statusStrip->Location = System::Drawing::Point(0, 715);
			this->statusStrip->Name = L"statusStrip";
			this->statusStrip->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
			this->statusStrip->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->statusStrip->Size = System::Drawing::Size(675, 26);
			this->statusStrip->SizingGrip = false;
			this->statusStrip->TabIndex = 2;
			this->statusStrip->Text = L"statusStrip";
			// 
			// statusLabel
			// 
			this->statusLabel->BackColor = System::Drawing::Color::White;
			this->statusLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->statusLabel->Name = L"statusLabel";
			this->statusLabel->Size = System::Drawing::Size(75, 21);
			this->statusLabel->Text = L"...Loading";
			// 
			// pnlItems
			// 
			this->pnlItems->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->pnlItems->BackColor = System::Drawing::Color::Black;
			this->pnlItems->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->pnlItems->Controls->Add(this->botStripTool);
			this->pnlItems->Location = System::Drawing::Point(13, 36);
			this->pnlItems->Margin = System::Windows::Forms::Padding(0);
			this->pnlItems->Name = L"pnlItems";
			this->pnlItems->Size = System::Drawing::Size(604, 590);
			this->pnlItems->TabIndex = 3;
			// 
			// botStripTool
			// 
			this->botStripTool->AutoSize = false;
			this->botStripTool->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->botStripTool->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->botStripTool->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->botStripTool->ImageScalingSize = System::Drawing::Size(36, 36);
			this->botStripTool->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->playButton, this->pauseButton,
					this->showNextButton, this->resetButton
			});
			this->botStripTool->Location = System::Drawing::Point(0, 541);
			this->botStripTool->Name = L"botStripTool";
			this->botStripTool->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->botStripTool->Size = System::Drawing::Size(600, 45);
			this->botStripTool->TabIndex = 0;
			this->botStripTool->Text = L"botStripTool";
			// 
			// playButton
			// 
			this->playButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->playButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"playButton.Image")));
			this->playButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->playButton->Margin = System::Windows::Forms::Padding(2, 2, 0, 2);
			this->playButton->Name = L"playButton";
			this->playButton->Size = System::Drawing::Size(40, 41);
			this->playButton->Text = L"Play";
			this->playButton->ToolTipText = L"Play";
			this->playButton->Click += gcnew System::EventHandler(this, &MainForm::playButton_Click);
			// 
			// pauseButton
			// 
			this->pauseButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->pauseButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pauseButton.Image")));
			this->pauseButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->pauseButton->Margin = System::Windows::Forms::Padding(0, 2, 2, 2);
			this->pauseButton->Name = L"pauseButton";
			this->pauseButton->Size = System::Drawing::Size(40, 41);
			this->pauseButton->Text = L"Pause";
			this->pauseButton->ToolTipText = L"Pause";
			this->pauseButton->Click += gcnew System::EventHandler(this, &MainForm::pauseButton_Click);
			// 
			// showNextButton
			// 
			this->showNextButton->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->showNextButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->showNextButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"showNextButton.Image")));
			this->showNextButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->showNextButton->Margin = System::Windows::Forms::Padding(6, 2, 0, 2);
			this->showNextButton->Name = L"showNextButton";
			this->showNextButton->Size = System::Drawing::Size(40, 41);
			this->showNextButton->Text = L"Next";
			this->showNextButton->ToolTipText = L"Next Subset";
			this->showNextButton->Click += gcnew System::EventHandler(this, &MainForm::showNextButton_Click);
			// 
			// resetButton
			// 
			this->resetButton->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->resetButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->resetButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"resetButton.Image")));
			this->resetButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->resetButton->Margin = System::Windows::Forms::Padding(0, 2, 2, 2);
			this->resetButton->Name = L"resetButton";
			this->resetButton->Size = System::Drawing::Size(40, 41);
			this->resetButton->Text = L"Reset";
			this->resetButton->ToolTipText = L"Reset";
			this->resetButton->Click += gcnew System::EventHandler(this, &MainForm::resetButton_Click);
			// 
			// mutationSizeSlider
			// 
			this->mutationSizeSlider->Location = System::Drawing::Point(0, 28);
			this->mutationSizeSlider->Maximum = 50;
			this->mutationSizeSlider->Minimum = 1;
			this->mutationSizeSlider->Name = L"mutationSizeSlider";
			this->mutationSizeSlider->Size = System::Drawing::Size(300, 45);
			this->mutationSizeSlider->TabIndex = 4;
			this->mutationSizeSlider->Value = 1;
			this->mutationSizeSlider->ValueChanged += gcnew System::EventHandler(this, &MainForm::mutationSizeSlider_ValueChanged);
			// 
			// mutationRateSlider
			// 
			this->mutationRateSlider->Location = System::Drawing::Point(300, 28);
			this->mutationRateSlider->Maximum = 50;
			this->mutationRateSlider->Minimum = 1;
			this->mutationRateSlider->Name = L"mutationRateSlider";
			this->mutationRateSlider->Size = System::Drawing::Size(300, 45);
			this->mutationRateSlider->TabIndex = 5;
			this->mutationRateSlider->Value = 1;
			this->mutationRateSlider->ValueChanged += gcnew System::EventHandler(this, &MainForm::mutationRateSlider_ValueChanged);
			// 
			// mutationSizeTextLabel
			// 
			this->mutationSizeTextLabel->AutoSize = true;
			this->mutationSizeTextLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->mutationSizeTextLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->mutationSizeTextLabel->Location = System::Drawing::Point(3, 0);
			this->mutationSizeTextLabel->Margin = System::Windows::Forms::Padding(0);
			this->mutationSizeTextLabel->Name = L"mutationSizeTextLabel";
			this->mutationSizeTextLabel->Size = System::Drawing::Size(135, 25);
			this->mutationSizeTextLabel->TabIndex = 6;
			this->mutationSizeTextLabel->Text = L"Mutation Size";
			// 
			// mutationRateTextLabel
			// 
			this->mutationRateTextLabel->AutoSize = true;
			this->mutationRateTextLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->mutationRateTextLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->mutationRateTextLabel->Location = System::Drawing::Point(303, 0);
			this->mutationRateTextLabel->Margin = System::Windows::Forms::Padding(0);
			this->mutationRateTextLabel->Name = L"mutationRateTextLabel";
			this->mutationRateTextLabel->Size = System::Drawing::Size(139, 25);
			this->mutationRateTextLabel->TabIndex = 7;
			this->mutationRateTextLabel->Text = L"Mutation Rate";
			// 
			// mutationRateLabel
			// 
			this->mutationRateLabel->AutoSize = true;
			this->mutationRateLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->mutationRateLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->mutationRateLabel->Location = System::Drawing::Point(439, 0);
			this->mutationRateLabel->Margin = System::Windows::Forms::Padding(0);
			this->mutationRateLabel->Name = L"mutationRateLabel";
			this->mutationRateLabel->Size = System::Drawing::Size(52, 25);
			this->mutationRateLabel->TabIndex = 8;
			this->mutationRateLabel->Text = L"- 2%";
			// 
			// mutationSizeLabel
			// 
			this->mutationSizeLabel->AutoSize = true;
			this->mutationSizeLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->mutationSizeLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->mutationSizeLabel->Location = System::Drawing::Point(135, 0);
			this->mutationSizeLabel->Margin = System::Windows::Forms::Padding(0);
			this->mutationSizeLabel->Name = L"mutationSizeLabel";
			this->mutationSizeLabel->Size = System::Drawing::Size(52, 25);
			this->mutationSizeLabel->TabIndex = 9;
			this->mutationSizeLabel->Text = L"- 2%";
			// 
			// volumeSlider
			// 
			this->volumeSlider->Location = System::Drawing::Point(-1, 20);
			this->volumeSlider->Margin = System::Windows::Forms::Padding(0);
			this->volumeSlider->Maximum = 26;
			this->volumeSlider->Name = L"volumeSlider";
			this->volumeSlider->Orientation = System::Windows::Forms::Orientation::Vertical;
			this->volumeSlider->Size = System::Drawing::Size(45, 350);
			this->volumeSlider->TabIndex = 10;
			this->volumeSlider->TickStyle = System::Windows::Forms::TickStyle::Both;
			this->volumeSlider->Value = 8;
			this->volumeSlider->ValueChanged += gcnew System::EventHandler(this, &MainForm::volumeSlider_ValueChanged);
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->label1->Location = System::Drawing::Point(-1, 365);
			this->label1->Margin = System::Windows::Forms::Padding(0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(43, 22);
			this->label1->TabIndex = 11;
			this->label1->Text = L"Off";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->label2->Location = System::Drawing::Point(0, 2);
			this->label2->Margin = System::Windows::Forms::Padding(0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(42, 22);
			this->label2->TabIndex = 12;
			this->label2->Text = L"Max";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// modifiersPanel
			// 
			this->modifiersPanel->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->modifiersPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->modifiersPanel->Controls->Add(this->mutationSizeTextLabel);
			this->modifiersPanel->Controls->Add(this->mutationSizeSlider);
			this->modifiersPanel->Controls->Add(this->mutationSizeLabel);
			this->modifiersPanel->Controls->Add(this->mutationRateLabel);
			this->modifiersPanel->Controls->Add(this->mutationRateTextLabel);
			this->modifiersPanel->Controls->Add(this->mutationRateSlider);
			this->modifiersPanel->Location = System::Drawing::Point(13, 637);
			this->modifiersPanel->Name = L"modifiersPanel";
			this->modifiersPanel->Size = System::Drawing::Size(604, 65);
			this->modifiersPanel->TabIndex = 13;
			// 
			// volumePanel
			// 
			this->volumePanel->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->volumePanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->volumePanel->Controls->Add(this->volumeSlider);
			this->volumePanel->Controls->Add(this->label2);
			this->volumePanel->Controls->Add(this->label1);
			this->volumePanel->Location = System::Drawing::Point(625, 36);
			this->volumePanel->Name = L"volumePanel";
			this->volumePanel->Size = System::Drawing::Size(43, 395);
			this->volumePanel->TabIndex = 14;
			// 
			// MainForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnableAllowFocusChange;
			this->BackColor = System::Drawing::Color::Gray;
			this->ClientSize = System::Drawing::Size(675, 741);
			this->Controls->Add(this->volumePanel);
			this->Controls->Add(this->pnlItems);
			this->Controls->Add(this->statusStrip);
			this->Controls->Add(this->menuStrip);
			this->Controls->Add(this->modifiersPanel);
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
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"8-bit SFX Generator";
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			this->statusStrip->ResumeLayout(false);
			this->statusStrip->PerformLayout();
			this->pnlItems->ResumeLayout(false);
			this->botStripTool->ResumeLayout(false);
			this->botStripTool->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->mutationSizeSlider))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->mutationRateSlider))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->volumeSlider))->EndInit();
			this->modifiersPanel->ResumeLayout(false);
			this->modifiersPanel->PerformLayout();
			this->volumePanel->ResumeLayout(false);
			this->volumePanel->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: 
		void player_next()
		{
			int next = _player->position();

			_soundUCs[_prev]->set_color(_color);
			_color = _soundUCs[next]->soundWave->BackColor;
			_soundUCs[next]->set_color(Color::Gray);

			_prev = next;
		}
		void player_done()
		{
			_soundUCs[_prev]->set_color(_color);
		}
		void player_update(Sound* sound, int i)
		{
			size_t offset = 100;

			size_t size = sound->buffer_count();
			array<short>^ samples = gcnew array<short>(size / offset);

			for (size_t i = 0, j = 0; j < size; ++i, j += offset)
				samples[i] = sound->buffer_samples()[j];

			_soundUCs[i]->add_data(samples);
		}

		System::Void saveButton_Click(System::Object^ sender, System::EventArgs^ e)
		{
			SaveFileDialog saveFileDialog;
			saveFileDialog.Filter = "TXT File|*.txt";
			saveFileDialog.Title = "Save current config";

			if (saveFileDialog.ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{

			}
		}
		System::Void loadButton_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			OpenFileDialog openFileDialog;
			openFileDialog.Filter = "TXT File|*.txt|WAV File|*.wav";
			openFileDialog.Title = "Load";

			if (openFileDialog.ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				if (!_player->load(openFileDialog.FileName))
					MessageBox::Show("Failed to load " + openFileDialog.FileName, "Error!", MessageBoxButtons::OK);
			}
		}

		System::Void playButton_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			_player->set_is_playing(true);
		}
		System::Void pauseButton_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			_player->set_is_playing(false);
		}

		System::Void resetButton_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			System::Windows::Forms::DialogResult result = MessageBox::Show(
				"Resetting will discard all progress and present new random candidates", 
				"Reset?",
				MessageBoxButtons::YesNo);

			if (result == System::Windows::Forms::DialogResult::Yes)
			{
				_player->reset();
				_evolution->reset();
			}
		}
		System::Void showNextButton_Click(System::Object^ sender, System::EventArgs^ e) 
		{

		}

		System::Void mutationSizeSlider_ValueChanged(System::Object^ sender, System::EventArgs^ e) 
		{
			mutationSizeLabel->Text = "- " + static_cast<int>(mutation_size() * 100.0).ToString() + "%";
		}
		System::Void mutationRateSlider_ValueChanged(System::Object^ sender, System::EventArgs^ e) 
		{
			mutationRateLabel->Text = "- " + static_cast<int>(mutation_rate() * 100.0).ToString() + "%";
		}

		System::Void volumeSlider_ValueChanged(System::Object^ sender, System::EventArgs^ e) 
		{
			_player->set_volume(util::scale(volumeSlider->Value, volumeSlider->Minimum, volumeSlider->Maximum));
		}

		System::Void helpButton_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (_info == nullptr || _info->IsDisposed)
				_info = gcnew InfoForm();

			if (!_info->Visible)
				_info->Show();
		}

	public:
		inline double mutation_size() { return util::scale(mutationSizeSlider->Value, 0, mutationSizeSlider->Maximum); }
		inline double mutation_rate() { return util::scale(mutationRateSlider->Value, 0, mutationRateSlider->Maximum); }

	private:
		bool initialize();

	private:
		const size_t row_count = 3;
		const size_t column_count = 4;

		size_t _prev;
		Color _color;

		array<SoundUC^>^ _soundUCs;
		InfoForm^ _info;

		Player^ _player;
		Evolution* _evolution;
};
}
