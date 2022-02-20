#include "MainForm.h"

using namespace IESFX;

bool MainForm::initialize()
{
	size_t size = row_count * column_count;
	double volume = util::scale(volumeSlider->Value, volumeSlider->Minimum, volumeSlider->Maximum);

	_evolution = new Evolution();

	_soundUCs = gcnew array<SoundUC^>(size);
	_player = gcnew Player(_evolution, size, volume);

	for (size_t i = 0; i < size; ++i)
	{
		SoundUC^ soundUC = gcnew SoundUC(_player, _evolution, i);

		pnlItems->Controls->Add(soundUC);
		soundUC->Location = Point(soundUC->Width * (i % column_count), soundUC->Height * (i / column_count));

		_soundUCs[i] = soundUC;
	}

	_player->_callback_play += gcnew Player::callback_play(this, &MainForm::player_next);
	_player->_callback_done += gcnew Player::callback_done(this, &MainForm::player_done);
	_player->_callback_update += gcnew Player::callback_update(this, &MainForm::player_update);

	_player->initialize();

	return true;
}
