#pragma once

namespace Interactive_Evolution_SFX 
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class SoundUC : public System::Windows::Forms::UserControl
	{
	public:
		SoundUC(void)
		{
			InitializeComponent();
		}

	protected:
		~SoundUC()
		{
			delete components;
		}
	private: System::Windows::Forms::ToolStrip^ stripTool;
	private: System::Windows::Forms::ToolStripButton^ pauseButton;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ soundWave;
	private: System::Windows::Forms::ToolStripButton^ saveButton;
	private: System::Windows::Forms::ToolStripButton^ playButton;
	private: System::Windows::Forms::ToolStripButton^ mutateButton;

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(SoundUC::typeid));
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->stripTool = (gcnew System::Windows::Forms::ToolStrip());
			this->playButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->pauseButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->saveButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->mutateButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->soundWave = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->stripTool->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->soundWave))->BeginInit();
			this->SuspendLayout();
			// 
			// stripTool
			// 
			this->stripTool->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->stripTool->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->stripTool->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->playButton, this->pauseButton,
					this->saveButton, this->mutateButton
			});
			this->stripTool->Location = System::Drawing::Point(0, 155);
			this->stripTool->Name = L"stripTool";
			this->stripTool->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->stripTool->Size = System::Drawing::Size(150, 25);
			this->stripTool->TabIndex = 0;
			this->stripTool->Text = L"stripTool";
			// 
			// playButton
			// 
			this->playButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->playButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"playButton.Image")));
			this->playButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->playButton->Name = L"playButton";
			this->playButton->Size = System::Drawing::Size(23, 22);
			this->playButton->Text = L"Play";
			this->playButton->ToolTipText = L"Play";
			// 
			// pauseButton
			// 
			this->pauseButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->pauseButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pauseButton.Image")));
			this->pauseButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->pauseButton->Name = L"pauseButton";
			this->pauseButton->Size = System::Drawing::Size(23, 22);
			this->pauseButton->Text = L"Pause";
			this->pauseButton->ToolTipText = L"Pause";
			// 
			// saveButton
			// 
			this->saveButton->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->saveButton->AutoToolTip = false;
			this->saveButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->saveButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->saveButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Bold));
			this->saveButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"saveButton.Image")));
			this->saveButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->saveButton->Name = L"saveButton";
			this->saveButton->Size = System::Drawing::Size(35, 22);
			this->saveButton->Text = L"Save";
			this->saveButton->Click += gcnew System::EventHandler(this, &SoundUC::saveButton_Click);
			// 
			// mutateButton
			// 
			this->mutateButton->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->mutateButton->AutoToolTip = false;
			this->mutateButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->mutateButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->mutateButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Bold));
			this->mutateButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"mutateButton.Image")));
			this->mutateButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->mutateButton->Name = L"mutateButton";
			this->mutateButton->Size = System::Drawing::Size(49, 22);
			this->mutateButton->Text = L"Mutate";
			this->mutateButton->Click += gcnew System::EventHandler(this, &SoundUC::mutateButton_Click);
			// 
			// soundWave
			// 
			this->soundWave->BorderSkin->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->soundWave->BorderSkin->BorderDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
			chartArea1->AxisX->InterlacedColor = System::Drawing::Color::Transparent;
			chartArea1->AxisX->IsLabelAutoFit = false;
			chartArea1->AxisX->LabelStyle->Enabled = false;
			chartArea1->AxisX->LabelStyle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 6, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			chartArea1->AxisX->LineWidth = 0;
			chartArea1->AxisX->MajorGrid->Enabled = false;
			chartArea1->AxisX->MajorGrid->LineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dot;
			chartArea1->AxisX->MajorGrid->LineWidth = 2;
			chartArea1->AxisX->MajorTickMark->Enabled = false;
			chartArea1->AxisX->MinorGrid->LineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dot;
			chartArea1->AxisY->InterlacedColor = System::Drawing::Color::Transparent;
			chartArea1->AxisY->IsLabelAutoFit = false;
			chartArea1->AxisY->LabelStyle->Enabled = false;
			chartArea1->AxisY->LabelStyle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 6, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			chartArea1->AxisY->LineWidth = 0;
			chartArea1->AxisY->MajorTickMark->Enabled = false;
			chartArea1->AxisY->MaximumAutoSize = 100;
			chartArea1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			chartArea1->BackGradientStyle = System::Windows::Forms::DataVisualization::Charting::GradientStyle::VerticalCenter;
			chartArea1->BackHatchStyle = System::Windows::Forms::DataVisualization::Charting::ChartHatchStyle::Cross;
			chartArea1->BorderColor = System::Drawing::Color::Gray;
			chartArea1->BorderDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Solid;
			chartArea1->BorderWidth = 2;
			chartArea1->Name = L"ChartArea1";
			this->soundWave->ChartAreas->Add(chartArea1);
			this->soundWave->Dock = System::Windows::Forms::DockStyle::Fill;
			this->soundWave->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			legend1->Enabled = false;
			legend1->Name = L"Legend1";
			this->soundWave->Legends->Add(legend1);
			this->soundWave->Location = System::Drawing::Point(0, 0);
			this->soundWave->Margin = System::Windows::Forms::Padding(0);
			this->soundWave->Name = L"soundWave";
			series1->BackSecondaryColor = System::Drawing::Color::Transparent;
			series1->BorderColor = System::Drawing::Color::Black;
			series1->BorderWidth = 3;
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series1->Color = System::Drawing::Color::DodgerBlue;
			series1->Legend = L"Legend1";
			series1->Name = L"Sound";
			this->soundWave->Series->Add(series1);
			this->soundWave->Size = System::Drawing::Size(150, 155);
			this->soundWave->TabIndex = 2;
			// 
			// SoundUC
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->Controls->Add(this->soundWave);
			this->Controls->Add(this->stripTool);
			this->Name = L"SoundUC";
			this->Size = System::Drawing::Size(150, 180);
			this->stripTool->ResumeLayout(false);
			this->stripTool->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->soundWave))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void mutateButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		DialogResult dialogueResult = MessageBox::Show("Are you sure you want to mutate this SFX?", "Mutate?", MessageBoxButtons::YesNo);

		if (dialogueResult == DialogResult::Yes)
		{

		}
	}
	private: System::Void saveButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		SaveFileDialog saveFileDialog;
		saveFileDialog.Filter = "WAV File|*.wav";
		saveFileDialog.Title = "Save the selected sound";
		saveFileDialog.ShowDialog();

		if (saveFileDialog.FileName != "")
		{

		}
	}
};
}