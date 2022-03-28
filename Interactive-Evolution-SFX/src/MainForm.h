#pragma once

#include <iostream>
#include <tchar.h>

#include <resid/sid.h>
#include <msclr/marshal_cppstd.h>

#include "utilities.h"
#include "Player.h"
#include "SoundUC.h"
#include "InfoForm.h"
#include "Evolution.h"
#include "Heatmap.h"
#include "Config.h"

namespace IESFX
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading::Tasks;

	public ref class MainForm : public Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
		}

	protected:
		~MainForm()
		{
			delete components;
		}

	private: System::Windows::Forms::MenuStrip^ menuStrip;
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
	private: System::Windows::Forms::Label^ mutationSizeTextLabel;
	private: System::Windows::Forms::Label^ mutationSizeLabel;
	private: System::Windows::Forms::TrackBar^ volumeSlider;
	private: System::Windows::Forms::ToolStripMenuItem^ saveButton;
	private: System::Windows::Forms::Panel^ volumePanel;
	private: System::Windows::Forms::Panel^ modifiersPanel;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::ToolStripButton^ evolveButton;
	private: System::Windows::Forms::ToolStripButton^ showPrevButton;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ mutationRateLabel;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TrackBar^ mutationRateSlider;
	private: System::Windows::Forms::ToolStripButton^ retryButton;
	private: System::Windows::Forms::Timer^ statusTimer;
	private: System::Windows::Forms::ToolStrip^ toolStrip1;
	private: System::Windows::Forms::ToolStripLabel^ statusLabel;
	private: System::Windows::Forms::ToolStripLabel^ evolutionStatusLabel;
	private: System::ComponentModel::IContainer^ components;
	
#pragma region Windows Form Designer generated code
	private:
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->optionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->otherToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pnlItems = (gcnew System::Windows::Forms::Panel());
			this->botStripTool = (gcnew System::Windows::Forms::ToolStrip());
			this->playButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->pauseButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->showNextButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->showPrevButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->retryButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->resetButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->evolveButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->mutationSizeSlider = (gcnew System::Windows::Forms::TrackBar());
			this->mutationSizeTextLabel = (gcnew System::Windows::Forms::Label());
			this->mutationSizeLabel = (gcnew System::Windows::Forms::Label());
			this->volumeSlider = (gcnew System::Windows::Forms::TrackBar());
			this->modifiersPanel = (gcnew System::Windows::Forms::Panel());
			this->volumePanel = (gcnew System::Windows::Forms::Panel());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->mutationRateLabel = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->mutationRateSlider = (gcnew System::Windows::Forms::TrackBar());
			this->statusTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->statusLabel = (gcnew System::Windows::Forms::ToolStripLabel());
			this->evolutionStatusLabel = (gcnew System::Windows::Forms::ToolStripLabel());
			this->menuStrip->SuspendLayout();
			this->pnlItems->SuspendLayout();
			this->botStripTool->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->mutationSizeSlider))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->volumeSlider))->BeginInit();
			this->modifiersPanel->SuspendLayout();
			this->volumePanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->mutationRateSlider))->BeginInit();
			this->toolStrip1->SuspendLayout();
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
			this->helpButton->Size = System::Drawing::Size(99, 22);
			this->helpButton->Text = L"Help";
			this->helpButton->Click += gcnew System::EventHandler(this, &MainForm::helpButton_Click);
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
			this->botStripTool->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {
				this->playButton, this->pauseButton,
					this->showNextButton, this->showPrevButton, this->retryButton, this->resetButton, this->evolveButton
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
			this->showNextButton->Margin = System::Windows::Forms::Padding(0, 2, 0, 2);
			this->showNextButton->Name = L"showNextButton";
			this->showNextButton->Size = System::Drawing::Size(40, 41);
			this->showNextButton->Text = L"Next";
			this->showNextButton->ToolTipText = L"Show Next Subset";
			this->showNextButton->Click += gcnew System::EventHandler(this, &MainForm::showNextButton_Click);
			// 
			// showPrevButton
			// 
			this->showPrevButton->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->showPrevButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->showPrevButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"showPrevButton.Image")));
			this->showPrevButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->showPrevButton->Margin = System::Windows::Forms::Padding(4, 2, 0, 2);
			this->showPrevButton->Name = L"showPrevButton";
			this->showPrevButton->Size = System::Drawing::Size(40, 41);
			this->showPrevButton->Text = L"Prev";
			this->showPrevButton->ToolTipText = L"Show Previous Subset";
			this->showPrevButton->Click += gcnew System::EventHandler(this, &MainForm::showPrevButton_Click);
			// 
			// retryButton
			// 
			this->retryButton->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->retryButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->retryButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"retryButton.Image")));
			this->retryButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->retryButton->Margin = System::Windows::Forms::Padding(0, 2, 2, 2);
			this->retryButton->Name = L"retryButton";
			this->retryButton->Size = System::Drawing::Size(40, 41);
			this->retryButton->Text = L"Retry";
			this->retryButton->ToolTipText = L"Retry";
			this->retryButton->Click += gcnew System::EventHandler(this, &MainForm::retryButton_Click);
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
			// evolveButton
			// 
			this->evolveButton->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->evolveButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->evolveButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"evolveButton.Image")));
			this->evolveButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->evolveButton->Margin = System::Windows::Forms::Padding(0, 2, 110, 2);
			this->evolveButton->Name = L"evolveButton";
			this->evolveButton->Size = System::Drawing::Size(40, 41);
			this->evolveButton->Text = L"Evolve";
			this->evolveButton->ToolTipText = L"Evolve";
			this->evolveButton->Click += gcnew System::EventHandler(this, &MainForm::evolveButton_Click);
			// 
			// mutationSizeSlider
			// 
			this->mutationSizeSlider->Location = System::Drawing::Point(-2, 30);
			this->mutationSizeSlider->Maximum = 200;
			this->mutationSizeSlider->Minimum = 1;
			this->mutationSizeSlider->Name = L"mutationSizeSlider";
			this->mutationSizeSlider->Size = System::Drawing::Size(327, 45);
			this->mutationSizeSlider->TabIndex = 4;
			this->mutationSizeSlider->TickFrequency = 2;
			this->mutationSizeSlider->Value = 14;
			this->mutationSizeSlider->ValueChanged += gcnew System::EventHandler(this, &MainForm::mutationSizeSlider_ValueChanged);
			this->mutationSizeSlider->Enter += gcnew System::EventHandler(this, &MainForm::mutationSizeSlider_Enter);
			// 
			// mutationSizeTextLabel
			// 
			this->mutationSizeTextLabel->AutoSize = true;
			this->mutationSizeTextLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->mutationSizeTextLabel->ForeColor = System::Drawing::Color::Aqua;
			this->mutationSizeTextLabel->Location = System::Drawing::Point(1, 1);
			this->mutationSizeTextLabel->Margin = System::Windows::Forms::Padding(0);
			this->mutationSizeTextLabel->Name = L"mutationSizeTextLabel";
			this->mutationSizeTextLabel->Size = System::Drawing::Size(128, 25);
			this->mutationSizeTextLabel->TabIndex = 6;
			this->mutationSizeTextLabel->Text = L"Mutation Size";
			// 
			// mutationSizeLabel
			// 
			this->mutationSizeLabel->AutoSize = true;
			this->mutationSizeLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 14.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->mutationSizeLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->mutationSizeLabel->Location = System::Drawing::Point(129, 1);
			this->mutationSizeLabel->Margin = System::Windows::Forms::Padding(0);
			this->mutationSizeLabel->Name = L"mutationSizeLabel";
			this->mutationSizeLabel->Size = System::Drawing::Size(67, 25);
			this->mutationSizeLabel->TabIndex = 9;
			this->mutationSizeLabel->Text = L"- 7.0%";
			// 
			// volumeSlider
			// 
			this->volumeSlider->Location = System::Drawing::Point(-1, 39);
			this->volumeSlider->Margin = System::Windows::Forms::Padding(0);
			this->volumeSlider->Maximum = 50;
			this->volumeSlider->Name = L"volumeSlider";
			this->volumeSlider->Orientation = System::Windows::Forms::Orientation::Vertical;
			this->volumeSlider->Size = System::Drawing::Size(45, 508);
			this->volumeSlider->TabIndex = 10;
			this->volumeSlider->TickStyle = System::Windows::Forms::TickStyle::Both;
			this->volumeSlider->Value = 8;
			this->volumeSlider->ValueChanged += gcnew System::EventHandler(this, &MainForm::volumeSlider_ValueChanged);
			this->volumeSlider->Enter += gcnew System::EventHandler(this, &MainForm::volumeSlider_Enter);
			// 
			// modifiersPanel
			// 
			this->modifiersPanel->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->modifiersPanel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->modifiersPanel->Controls->Add(this->mutationSizeTextLabel);
			this->modifiersPanel->Controls->Add(this->mutationSizeSlider);
			this->modifiersPanel->Controls->Add(this->mutationSizeLabel);
			this->modifiersPanel->Location = System::Drawing::Point(13, 638);
			this->modifiersPanel->Name = L"modifiersPanel";
			this->modifiersPanel->Size = System::Drawing::Size(325, 66);
			this->modifiersPanel->TabIndex = 13;
			// 
			// volumePanel
			// 
			this->volumePanel->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->volumePanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->volumePanel->Controls->Add(this->pictureBox2);
			this->volumePanel->Controls->Add(this->pictureBox1);
			this->volumePanel->Controls->Add(this->volumeSlider);
			this->volumePanel->Location = System::Drawing::Point(625, 36);
			this->volumePanel->Name = L"volumePanel";
			this->volumePanel->Size = System::Drawing::Size(43, 590);
			this->volumePanel->TabIndex = 14;
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(3, 547);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(35, 35);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 12;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(3, 4);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(35, 35);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 11;
			this->pictureBox1->TabStop = false;
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel1->Controls->Add(this->mutationRateLabel);
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->mutationRateSlider);
			this->panel1->Location = System::Drawing::Point(345, 638);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(325, 66);
			this->panel1->TabIndex = 14;
			// 
			// mutationRateLabel
			// 
			this->mutationRateLabel->AutoSize = true;
			this->mutationRateLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 14.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->mutationRateLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->mutationRateLabel->Location = System::Drawing::Point(132, 1);
			this->mutationRateLabel->Margin = System::Windows::Forms::Padding(0);
			this->mutationRateLabel->Name = L"mutationRateLabel";
			this->mutationRateLabel->Size = System::Drawing::Size(67, 25);
			this->mutationRateLabel->TabIndex = 8;
			this->mutationRateLabel->Text = L"- 9.0%";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::Aqua;
			this->label4->Location = System::Drawing::Point(1, 1);
			this->label4->Margin = System::Windows::Forms::Padding(0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(131, 25);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Mutation Rate";
			// 
			// mutationRateSlider
			// 
			this->mutationRateSlider->Location = System::Drawing::Point(-1, 30);
			this->mutationRateSlider->Maximum = 200;
			this->mutationRateSlider->Minimum = 1;
			this->mutationRateSlider->Name = L"mutationRateSlider";
			this->mutationRateSlider->Size = System::Drawing::Size(325, 45);
			this->mutationRateSlider->TabIndex = 5;
			this->mutationRateSlider->TickFrequency = 2;
			this->mutationRateSlider->Value = 18;
			this->mutationRateSlider->ValueChanged += gcnew System::EventHandler(this, &MainForm::mutationRateSlider_ValueChanged);
			this->mutationRateSlider->Enter += gcnew System::EventHandler(this, &MainForm::mutationRateSlider_Enter);
			// 
			// statusTimer
			// 
			this->statusTimer->Enabled = true;
			this->statusTimer->Tick += gcnew System::EventHandler(this, &MainForm::statusTimer_Tick);
			// 
			// toolStrip1
			// 
			this->toolStrip1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->toolStrip1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->toolStrip1->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->toolStrip1->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->statusLabel, this->evolutionStatusLabel });
			this->toolStrip1->Location = System::Drawing::Point(0, 716);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->toolStrip1->ShowItemToolTips = false;
			this->toolStrip1->Size = System::Drawing::Size(675, 25);
			this->toolStrip1->TabIndex = 15;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// statusLabel
			// 
			this->statusLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->statusLabel->Name = L"statusLabel";
			this->statusLabel->Size = System::Drawing::Size(80, 22);
			this->statusLabel->Text = L"Loading...";
			// 
			// evolutionStatusLabel
			// 
			this->evolutionStatusLabel->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->evolutionStatusLabel->Name = L"evolutionStatusLabel";
			this->evolutionStatusLabel->Size = System::Drawing::Size(154, 22);
			this->evolutionStatusLabel->Text = L"Gen: 10 | Quality: 50";
			// 
			// MainForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnableAllowFocusChange;
			this->BackColor = System::Drawing::Color::Gray;
			this->ClientSize = System::Drawing::Size(675, 741);
			this->Controls->Add(this->toolStrip1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->volumePanel);
			this->Controls->Add(this->pnlItems);
			this->Controls->Add(this->menuStrip);
			this->Controls->Add(this->modifiersPanel);
			this->DoubleBuffered = true;
			this->Font = (gcnew System::Drawing::Font(L"Arial Black", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->ImeMode = System::Windows::Forms::ImeMode::On;
			this->KeyPreview = true;
			this->MainMenuStrip = this->menuStrip;
			this->Margin = System::Windows::Forms::Padding(8, 9, 8, 9);
			this->MaximizeBox = false;
			this->Name = L"MainForm";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"8-Bit SFX Generator";
			this->Activated += gcnew System::EventHandler(this, &MainForm::MainForm_Activated);
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
			this->Shown += gcnew System::EventHandler(this, &MainForm::MainForm_Shown);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::MainForm_KeyDown);
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			this->pnlItems->ResumeLayout(false);
			this->botStripTool->ResumeLayout(false);
			this->botStripTool->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->mutationSizeSlider))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->volumeSlider))->EndInit();
			this->modifiersPanel->ResumeLayout(false);
			this->modifiersPanel->PerformLayout();
			this->volumePanel->ResumeLayout(false);
			this->volumePanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->mutationRateSlider))->EndInit();
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: 
		System::Void MainForm_Shown(System::Object^ sender, System::EventArgs^ e)
		{
			if (!initialize())
				throw gcnew WarningException("failed to initialize system");

#if !BUILD
			Heatmap::heatmap_1();
#endif
		}
		System::Void saveButton_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (!ready())
				return;

			SaveFileDialog saveFileDialog;
			saveFileDialog.Filter = "TXT File|*.txt";
			saveFileDialog.Title = "Save current population";

			if (saveFileDialog.ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				update_status("Loading...");

				if (!_evolution->save(msclr::interop::marshal_as<std::string>(saveFileDialog.FileName)))
					MessageBox::Show("Failed to save file.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);

				update_status("Ready");

				this->ActiveControl = nullptr;
				this->Focus();
			}
		}
		System::Void loadButton_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if (!ready())
				return;

			OpenFileDialog openFileDialog;
			openFileDialog.Filter = "TXT File|*.txt";
			openFileDialog.Title = "Load a population";

			if (openFileDialog.ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				update_status("Loading...");

				switch (_evolution->load(msclr::interop::marshal_as<std::string>(openFileDialog.FileName)))
				{
				case 0:
				{
					for (int i = 0; i < _soundUCs->Length; ++i)
						_soundUCs[i]->reset();

					_player->reset();

					Task::Factory->StartNew(gcnew Action(this, &MainForm::execute_evolution));
				}
				break;
				case 1:
				{
					std::vector<SoundGene> genes = _evolution->output(_soundUCs->Length, 0);

					if (genes.size() != 0)
					{
						for (int i = 0; i < _soundUCs->Length; ++i)
							_soundUCs[i]->reset();

						_player->reset();
						_player->update(genes);

						_prev = _old_step = _step = 0;
						_color = Color::White;
					}
					else
						MessageBox::Show("Population could be created.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
				break;
				default:
				{
					MessageBox::Show("Failed to load file.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
				break;
				}

				update_evolution_status(_step + "/" + USABLE_POPULATION);
				update_status("Ready");

				this->ActiveControl = nullptr;
				this->Focus();
			}
		}

		System::Void playButton_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if (!ready())
				return;

			if (_player->is_playing())
				_player->iterate();

			_player->set_is_playing(true);

			this->ActiveControl = nullptr;
			this->Focus();
		}
		System::Void pauseButton_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if (!ready())
				return;

			_player->set_is_playing(false);

			this->ActiveControl = nullptr;
			this->Focus();
		}

		System::Void evolveButton_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (!ready())
				return;

			System::Windows::Forms::DialogResult result = MessageBox::Show(
				"Do you wish to evolve using the selected candidates?",
				"Evolve?",
				MessageBoxButtons::YesNo, MessageBoxIcon::Question);

			if (result == System::Windows::Forms::DialogResult::Yes)
			{
				_player->reset();
				Task::Factory->StartNew(gcnew Action(this, &MainForm::execute_evolution));
			}

			this->ActiveControl = nullptr;
			this->Focus();
		}

		System::Void resetButton_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if (!ready())
				return;

			System::Windows::Forms::DialogResult result = MessageBox::Show(
				"Resetting will discard all progress and present new random candidates.", 
				"Reset?",
				MessageBoxButtons::YesNo, MessageBoxIcon::Question);

			if (result == System::Windows::Forms::DialogResult::Yes)
			{
				for (int i = 0; i < _soundUCs->Length; ++i)
					_soundUCs[i]->reset();

				_player->reset();
				_evolution->reset();

				Task::Factory->StartNew(gcnew Action(this, &MainForm::execute_evolution));

				this->ActiveControl = nullptr;
				this->Focus();
			}
		}
		System::Void retryButton_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (!ready())
				return;

			System::Windows::Forms::DialogResult result = MessageBox::Show(
				"Retry will bring you back to your previous population.",
				"Retry?",
				MessageBoxButtons::YesNo, MessageBoxIcon::Question);

			if (result == System::Windows::Forms::DialogResult::Yes)
			{
				update_status("Loading...");

				if (_evolution->retry())
				{
					std::vector<SoundGene> genes = _evolution->output(_soundUCs->Length, _old_step);

					if (genes.size() != 0)
					{
						for (int i = 0; i < _soundUCs->Length; ++i)
							_soundUCs[i]->reset();

						_player->reset();
						_player->update(genes);

						_prev = 0;
						_step = _old_step;
						_color = Color::White;
					}
					else
						MessageBox::Show("No new candidates could be presented.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
				else
					MessageBox::Show("No previous population to go back to.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);

				update_evolution_status(_step + "/" + USABLE_POPULATION);
				update_status("Ready");

				this->ActiveControl = nullptr;
				this->Focus();
			}
		}

		System::Void showPrevButton_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (!ready())
				return;

			update_status("Loading...");

			int next_step = _step - _soundUCs->Length;
			std::vector<SoundGene> genes = _evolution->output(_soundUCs->Length, 
				(next_step = (next_step < 0) ? USABLE_POPULATION - _soundUCs->Length : next_step));

			if (genes.size() != 0)
			{
				for (int i = 0; i < _soundUCs->Length; ++i)
					_soundUCs[i]->reset();

				_player->reset();
				_player->update(genes);

				_step = next_step;
			}
			else
				MessageBox::Show("No (previous) candidates could be presented.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);

			update_evolution_status(_step + "/" + USABLE_POPULATION);
			update_status("Ready");

			this->ActiveControl = nullptr;
			this->Focus();
		}
		System::Void showNextButton_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if (!ready())
				return;

			update_status("Loading...");

			int next_step = _step + _soundUCs->Length;
			std::vector<SoundGene> genes = _evolution->output(_soundUCs->Length, 
				(next_step = (next_step >= USABLE_POPULATION) ? 0 : next_step));
			
			if (genes.size() != 0)
			{
				for (int i = 0; i < _soundUCs->Length; ++i)
					_soundUCs[i]->reset();

				_player->reset();
				_player->update(genes);

				_step = next_step;
			}
			else
				MessageBox::Show("No (further) candidates could be presented.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);

			update_evolution_status(_step + "/" + USABLE_POPULATION);
			update_status("Ready");

			this->ActiveControl = nullptr;
			this->Focus();
		}

		System::Void mutationSizeSlider_ValueChanged(System::Object^ sender, System::EventArgs^ e) 
		{
			mutationSizeLabel->Text = "- " + String::Format(
				System::Globalization::CultureInfo::InvariantCulture, "{0:0.0}", 
				Decimal::Round(System::Decimal(mutation_size() * 100), 1)) + "%";

			_evolution->set_mutation_size(mutation_size());
		}
		System::Void mutationRateSlider_ValueChanged(System::Object^ sender, System::EventArgs^ e)
		{
			mutationRateLabel->Text = "- " + String::Format(
				System::Globalization::CultureInfo::InvariantCulture, "{0:0.0}",
				Decimal::Round(System::Decimal(mutation_rate() * 100), 1)) + "%";

			_evolution->set_mutation_rate(mutation_rate());
		}

		System::Void volumeSlider_ValueChanged(System::Object^ sender, System::EventArgs^ e) 
		{
			_player->set_volume(volume());

			this->ActiveControl = nullptr;
			this->Focus();
		}

		System::Void helpButton_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (_info == nullptr || _info->IsDisposed)
				_info = gcnew InfoForm();

			if (!_info->Visible)
				_info->Show();

			this->ActiveControl = nullptr;
			this->Focus();
		}

		System::Void statusTimer_Tick(System::Object^ sender, System::EventArgs^ e)
		{
			if (_evolution->active())
			{
				update_evolution_status(
					"Generation: " + String::Format(System::Globalization::CultureInfo::InvariantCulture, 
						"{0:0.0}", Decimal::Round(System::Decimal(_evolution->generation() * 100), 1)) + 
					"% | Quality: " + String::Format(System::Globalization::CultureInfo::InvariantCulture,
						"{0:0.0}", Decimal::Round(System::Decimal(_evolution->quality() * 100), 1)) + "%");
			}
		}

		System::Void MainForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
		{
			_player->shutdown();
		}

		System::Void MainForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
		{
			switch (e->KeyCode)
			{
			case Keys::Left:
			{
				showPrevButton_Click(sender, e);
				e->Handled = true;
			}
			break;
			case Keys::Right:
			{
				showNextButton_Click(sender, e);
				e->Handled = true;
			}
			break;
			case Keys::Up:
			{
				playButton_Click(sender, e);
				e->Handled = true;
			}
			break;
			case Keys::Down:
			{
				pauseButton_Click(sender, e);
				e->Handled = true;
			}
			break;
			case Keys::Enter:
			{
				evolveButton_Click(sender, e);
				e->Handled = true;
			}
			break;
			case Keys::Back:
			{
				retryButton_Click(sender, e);
				e->Handled = true;
			}
			break;
			case Keys::Delete:
			{
				resetButton_Click(sender, e);
				e->Handled = true;
			}
			break;
			}
		}

		System::Void MainForm_Activated(System::Object^ sender, System::EventArgs^ e)
		{
			this->ActiveControl = nullptr;
		}

		System::Void mutationRateSlider_Enter(System::Object^ sender, System::EventArgs^ e)
		{
			this->ActiveControl = nullptr;
			this->Focus();
		}
		System::Void mutationSizeSlider_Enter(System::Object^ sender, System::EventArgs^ e)
		{
			this->ActiveControl = nullptr;
			this->Focus();
		}
		System::Void volumeSlider_Enter(System::Object^ sender, System::EventArgs^ e)
		{
			this->ActiveControl = nullptr;
			this->Focus();
		}

	private:
		void player_next()
		{
			int next = static_cast<int>(_player->position());

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
			size_t offset = 35;

			size_t size = sound->buffer_count();
			array<short>^ samples = gcnew array<short>(size / offset);

			for (size_t i = 0, j = 0; i < samples->Length && j < size; ++i, j += offset)
				samples[i] = sound->buffer_samples()[j];

			_soundUCs[i]->add_data(samples);
		}

		bool ready()
		{
			if (_evolution->active())
			{
				MessageBox::Show("System is not ready yet.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return false;
			}
			return true;
		}

		void update_status(String^ status)
		{
			if (this->InvokeRequired)
				Invoke(gcnew update_status_del(this, &MainForm::us), status);
			else
				us(status);
		}
		void us(String^ status)
		{
			statusLabel->Text = status;
			Refresh();
		}

		void update_evolution_status(String^ status)
		{
			if (this->InvokeRequired)
				Invoke(gcnew update_status_del(this, &MainForm::ues), status);
			else
				ues(status);
		}
		void ues(String^ status)
		{
			evolutionStatusLabel->Text = status;
			Refresh();
		}

		void execute_evolution()
		{
			update_status("Loading...");

			int result = _evolution->execute();

			if (result != 0)
			{
				switch (result)
				{
				case -1:
					MessageBox::Show("Please select candidates for evolution first.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
					break;
				}
				update_status("Ready");
				return;
			}

			std::vector<SoundGene> genes = _evolution->output(_soundUCs->Length, 0);

			if (genes.size() != 0)
			{
				for (int i = 0; i < _soundUCs->Length; ++i)
					_soundUCs[i]->reset();

				_player->reset();
				_player->update(genes);

				_old_step = _step;

				_prev = _step = 0;
				_color = Color::White;
			}
			else
				MessageBox::Show("Population could be created.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);

			update_evolution_status(_step + "/" + USABLE_POPULATION);

			update_status("Ready");
		}

	public:
		inline double mutation_size() { return util::scale(mutationSizeSlider->Value, 0, mutationSizeSlider->Maximum); }
		inline double mutation_rate() { return util::scale(mutationRateSlider->Value, 0, mutationRateSlider->Maximum); }
		inline float volume() { return (float)util::scale(volumeSlider->Value, volumeSlider->Minimum, volumeSlider->Maximum); }

	private:
		delegate void update_status_del(String^ status);
		delegate void update_evolution_status_del(String^ status);

	private:
		bool initialize();

	private:
		static const size_t row_count = 3;
		static const size_t column_count = 4;

		int _prev, _step, _old_step;
		Color _color;

		array<SoundUC^>^ _soundUCs;
		InfoForm^ _info;

		Player^ _player;
		Evolution* _evolution;
};
}
