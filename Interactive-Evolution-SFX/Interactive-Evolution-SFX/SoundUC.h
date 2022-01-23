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
	protected:

	protected:
	private: System::Windows::Forms::ToolStripButton^ toolStripButton1;




	private: System::Windows::Forms::DataVisualization::Charting::Chart^ soundWave;
	private: System::Windows::Forms::ToolStripButton^ toolStripButton2;



	protected:

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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->stripTool = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripButton1 = (gcnew System::Windows::Forms::ToolStripButton());
			this->soundWave = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->toolStripButton2 = (gcnew System::Windows::Forms::ToolStripButton());
			this->stripTool->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->soundWave))->BeginInit();
			this->SuspendLayout();
			// 
			// stripTool
			// 
			this->stripTool->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->stripTool->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->stripTool->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->toolStripButton1,
					this->toolStripButton2
			});
			this->stripTool->Location = System::Drawing::Point(0, 155);
			this->stripTool->Name = L"stripTool";
			this->stripTool->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
			this->stripTool->Size = System::Drawing::Size(150, 25);
			this->stripTool->TabIndex = 0;
			this->stripTool->Text = L"stripTool";
			// 
			// toolStripButton1
			// 
			this->toolStripButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton1.Image")));
			this->toolStripButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton1->Name = L"toolStripButton1";
			this->toolStripButton1->Size = System::Drawing::Size(23, 22);
			this->toolStripButton1->Text = L"toolStripButton1";
			// 
			// soundWave
			// 
			this->soundWave->BorderSkin->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->soundWave->BorderSkin->BorderDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
			chartArea2->AxisX->IsLabelAutoFit = false;
			chartArea2->AxisX->LabelStyle->Enabled = false;
			chartArea2->AxisX->LabelStyle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 6, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			chartArea2->AxisX->LineWidth = 0;
			chartArea2->AxisX->MajorGrid->Enabled = false;
			chartArea2->AxisX->MajorTickMark->Enabled = false;
			chartArea2->AxisX->MinorGrid->LineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dot;
			chartArea2->AxisY->InterlacedColor = System::Drawing::Color::Silver;
			chartArea2->AxisY->IsInterlaced = true;
			chartArea2->AxisY->IsLabelAutoFit = false;
			chartArea2->AxisY->LabelStyle->Enabled = false;
			chartArea2->AxisY->LabelStyle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 6, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			chartArea2->AxisY->LineWidth = 0;
			chartArea2->AxisY->MajorGrid->Enabled = false;
			chartArea2->AxisY->MajorTickMark->Enabled = false;
			chartArea2->AxisY->MaximumAutoSize = 100;
			chartArea2->BackColor = System::Drawing::Color::DimGray;
			chartArea2->Name = L"ChartArea1";
			this->soundWave->ChartAreas->Add(chartArea2);
			this->soundWave->Dock = System::Windows::Forms::DockStyle::Fill;
			this->soundWave->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			legend2->Enabled = false;
			legend2->Name = L"Legend1";
			this->soundWave->Legends->Add(legend2);
			this->soundWave->Location = System::Drawing::Point(0, 0);
			this->soundWave->Margin = System::Windows::Forms::Padding(0);
			this->soundWave->Name = L"soundWave";
			series2->BackSecondaryColor = System::Drawing::Color::Transparent;
			series2->BorderColor = System::Drawing::Color::Black;
			series2->BorderWidth = 3;
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series2->Color = System::Drawing::Color::CornflowerBlue;
			series2->Legend = L"Legend1";
			series2->Name = L"Sound";
			this->soundWave->Series->Add(series2);
			this->soundWave->Size = System::Drawing::Size(150, 155);
			this->soundWave->TabIndex = 2;
			this->soundWave->Click += gcnew System::EventHandler(this, &SoundUC::soundWave_Click);
			this->soundWave->MouseEnter += gcnew System::EventHandler(this, &SoundUC::soundWave_MouseEnter);
			// 
			// toolStripButton2
			// 
			this->toolStripButton2->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton2.Image")));
			this->toolStripButton2->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton2->Name = L"toolStripButton2";
			this->toolStripButton2->Size = System::Drawing::Size(23, 22);
			this->toolStripButton2->Text = L"toolStripButton2";
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

	private: System::Void soundWave_Click(System::Object^ sender, System::EventArgs^ e) 
	{

	}
	private: System::Void soundWave_MouseEnter(System::Object^ sender, System::EventArgs^ e) 
	{

	}
};
}
