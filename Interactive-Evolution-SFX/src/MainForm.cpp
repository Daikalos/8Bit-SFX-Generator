#include "MainForm.h"

using namespace Interactive_Evolution_SFX;

bool MainForm::initialize_sounds()
{
	sounds = gcnew array<SoundUC^>(row_count * column_count);


	for (int i = 0; i < sounds->Length; ++i)
	{
		SoundUC^ soundUC = sounds[i] = gcnew SoundUC();
		pnlItems->Controls->Add(soundUC);

		soundUC->Location = Point(soundUC->Width * (i % column_count), soundUC->Height * (i / column_count));
	}

	return true;
}
