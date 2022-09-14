//  ---------------------------------------------------------------------------
//  This file is part of the 8-Bit SFX Generator
//	Copyright (C) 2022 Tobias Garpenhall <tobiasgarpenhall@gmail.com>
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//	
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program. If not, see <http://www.gnu.org/licenses/>.
//  ---------------------------------------------------------------------------

#include "MainForm.h"

using namespace IESFX;

bool MainForm::initialize()
{
	const std::size_t size = ROWS * COLUMNS;

	_evolution = new Evolution(mutation_rate(), mutation_size());

	_soundUCs = gcnew array<SoundUC^>(size);
	_player = gcnew Player(_evolution, size, volume());

	for (int i = 0; i < size; ++i)
	{
		SoundUC^ soundUC = gcnew SoundUC(_player, _evolution, i);

		pnlItems->Controls->Add(soundUC);
		soundUC->Location = Point(soundUC->Width * (i % COLUMNS), soundUC->Height * (i / COLUMNS));

		_soundUCs[i] = soundUC;
	}

	play = gcnew Player::callback_play(this, &MainForm::player_next);
	done = gcnew Player::callback_done(this, &MainForm::player_done);
	update = gcnew Player::callback_update(this, &MainForm::player_update);

	_player->_callback_play += play;
	_player->_callback_done += done;
	_player->_callback_update += update;

	_evolution_thread = gcnew Thread(gcnew ThreadStart(this, &MainForm::evolution_loop));
	_evolution_thread->Name = "evolution_thread";
	_evolution_thread->IsBackground = true;
	_evolution_thread->Start();

	_run_evolution = true;

	return true;
}

System::Void MainForm::MainForm_Shown(System::Object^ sender, System::EventArgs^ e)
{
	if (!initialize())
		throw gcnew WarningException("failed to initialize system");

#if !BUILD
	Heatmap::heatmap_3();
#endif
}

System::Void MainForm::MainForm_Activated(System::Object^ sender, System::EventArgs^ e)
{
	this->ActiveControl = nullptr;
}

System::Void MainForm::MainForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
{
	_shutdown = true;
	_evolution->shutdown();
	_evolution_thread->Join();

	delete _evolution;

	_player->_callback_play -= play;
	_player->_callback_done -= done;
	_player->_callback_update -= update;

	for (int i = 0; i < _soundUCs->Length; ++i)
		delete _soundUCs[i];

	_player->shutdown();
}

System::Void MainForm::MainForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
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

System::Void MainForm::saveButton_Click(System::Object^ sender, System::EventArgs^ e)
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
System::Void MainForm::loadButton_Click(System::Object^ sender, System::EventArgs^ e)
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

			_run_evolution = true;
		}
		break;
		case 1:
		{
			std::vector<const SoundGene*> genes = _evolution->output(_soundUCs->Length, 0);

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
			MessageBox::Show("Failed to load file.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			break;
		}

		update_evolution_status(_step + "/" + USABLE_POPULATION);
		update_status("Ready");

		this->ActiveControl = nullptr;
		this->Focus();
	}
}

System::Void MainForm::playButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (!ready())
		return;

	if (_player->active())
		_player->iterate();

	_player->set_active(true);

	this->ActiveControl = nullptr;
	this->Focus();
}
System::Void MainForm::pauseButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (!ready())
		return;

	_player->set_active(false);

	this->ActiveControl = nullptr;
	this->Focus();
}

System::Void MainForm::evolveButton_Click(System::Object^ sender, System::EventArgs^ e)
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
		_run_evolution = true;
	}

	this->ActiveControl = nullptr;
	this->Focus();
}

System::Void MainForm::resetButton_Click(System::Object^ sender, System::EventArgs^ e)
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

		_run_evolution = true;

		this->ActiveControl = nullptr;
		this->Focus();
	}
}
System::Void MainForm::retryButton_Click(System::Object^ sender, System::EventArgs^ e)
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
			std::vector<const SoundGene*> genes = _evolution->output(_soundUCs->Length, _old_step);

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

System::Void MainForm::showPrevButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (!ready())
		return;

	update_status("Loading...");

	int next_step = _step - _soundUCs->Length;
	std::vector<const SoundGene*> genes = _evolution->output(_soundUCs->Length,
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
System::Void MainForm::showNextButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (!ready())
		return;

	update_status("Loading...");

	int next_step = _step + _soundUCs->Length;
	std::vector<const SoundGene*> genes = _evolution->output(_soundUCs->Length,
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

System::Void MainForm::mutationSizeSlider_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
	mutationSizeLabel->Text = "- " + String::Format(
		System::Globalization::CultureInfo::InvariantCulture, "{0:0.0}",
		Decimal::Round(System::Decimal(mutation_size() * 100), 1)) + "%";

	_evolution->set_mutation_size(mutation_size());
}
System::Void MainForm::mutationRateSlider_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
	mutationRateLabel->Text = "- " + String::Format(
		System::Globalization::CultureInfo::InvariantCulture, "{0:0.0}",
		Decimal::Round(System::Decimal(mutation_rate() * 100), 1)) + "%";

	_evolution->set_mutation_rate(mutation_rate());
}

System::Void MainForm::volumeSlider_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
	_player->set_volume(volume());

	this->ActiveControl = nullptr;
	this->Focus();
}

System::Void MainForm::helpButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (_info == nullptr || _info->IsDisposed)
		_info = gcnew InfoForm();

	if (!_info->Visible)
		_info->Show();

	this->ActiveControl = nullptr;
	this->Focus();
}

System::Void MainForm::statusTimer_Tick(System::Object^ sender, System::EventArgs^ e)
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

System::Void MainForm::mutationRateSlider_Enter(System::Object^ sender, System::EventArgs^ e)
{
	this->ActiveControl = nullptr;
	this->Focus();
}
System::Void MainForm::mutationSizeSlider_Enter(System::Object^ sender, System::EventArgs^ e)
{
	this->ActiveControl = nullptr;
	this->Focus();
}
System::Void MainForm::volumeSlider_Enter(System::Object^ sender, System::EventArgs^ e)
{
	this->ActiveControl = nullptr;
	this->Focus();
}

void MainForm::player_next()
{
	int next = static_cast<int>(_player->position());

	_soundUCs[_prev]->set_color(_color);
	_color = _soundUCs[next]->soundWave->BackColor;
	_soundUCs[next]->set_color(Color::FromArgb(255, 185, 185, 185));

	_prev = next;
}
void MainForm::player_done()
{
	_soundUCs[_prev]->set_color(_color);
}
void MainForm::player_update(Sound* sounds)
{
	constexpr std::size_t offset = 35;

	for (int i = 0; i < _soundUCs->Length; ++i)
	{
		size_t size = sounds[i].buffer_count();
		const sf::Int16* buffer = sounds[i].buffer_samples();

		array<short>^ samples = gcnew array<short>(size / offset);

		for (size_t i = 0, j = 0; i < samples->Length && j < size; ++i, j += offset)
			samples[i] = buffer[j];

		_soundUCs[i]->add_data(samples);
	}
}

bool MainForm::ready()
{
	if (_evolution->active())
	{
		MessageBox::Show("System is not ready yet.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return false;
	}
	return true;
}

void MainForm::update_status(String^ status)
{
	if (this->InvokeRequired)
		Invoke(gcnew update_status_del(this, &MainForm::us), status);
	else
		us(status);
}
void MainForm::us(String^ status)
{
	statusLabel->Text = status;
	Refresh();
}

void MainForm::update_evolution_status(String^ status)
{
	if (this->InvokeRequired)
		Invoke(gcnew update_status_del(this, &MainForm::ues), status);
	else
		ues(status);
}
void MainForm::ues(String^ status)
{
	evolutionStatusLabel->Text = status;
	Refresh();
}

void MainForm::evolution_loop()
{
	while (!_shutdown)
	{
		while (!_run_evolution && !_shutdown);
		_run_evolution = false;

		if (_shutdown)
			break;

		update_status("Loading...");
		int result = _evolution->execute();

		if (_shutdown)
			break;

		if (result != EXIT_SUCCESS)
		{
			switch (result)
			{
			case EXIT_FAILURE:
				MessageBox::Show("Please select candidates for evolution first.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				break;
			}
			update_status("Ready");
			continue;
		}

		std::vector<const SoundGene*> genes = _evolution->output(_soundUCs->Length, 0);

		if (!genes.empty())
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
}

double MainForm::mutation_size()
{ 
	return util::scale(mutationSizeSlider->Value, 0, mutationSizeSlider->Maximum);
}
double MainForm::mutation_rate() 
{ 
	return util::scale(mutationRateSlider->Value, 0, mutationRateSlider->Maximum); 
}
float MainForm::volume() 
{ 
	return (float)util::scale(volumeSlider->Value, volumeSlider->Minimum, volumeSlider->Maximum); 
}
