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
	size_t size = ROWS * COLUMNS;

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

	_player->_callback_play += gcnew Player::callback_play(this, &MainForm::player_next);
	_player->_callback_done += gcnew Player::callback_done(this, &MainForm::player_done);
	_player->_callback_update += gcnew Player::callback_update(this, &MainForm::player_update);

	Task::Factory->StartNew(gcnew Action(this, &MainForm::execute_evolution));

	return true;
}
