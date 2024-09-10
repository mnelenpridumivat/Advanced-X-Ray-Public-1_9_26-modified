#include "stdafx.h"
#include "PlayerMetadata.h"
#include "alife_space.h"
#include "../xrCore/FS.h"

void CPlayerMetadata::SaveAll(IWriter* writer)
{
}

void CPlayerMetadata::LoadAll(IReader* reader)
{
}

CPlayerMetadata::CPlayerMetadata()
{
}

CPlayerMetadata::~CPlayerMetadata()
{
	IWriter* writer = FS.w_open(save_name);
	SaveAll(writer);
	FS.w_close(writer);
}

CPlayerMetadata& CPlayerMetadata::GetInstance()
{
	static CPlayerMetadata metadata;
	if (!metadata.isInited) {
		LPCSTR game_saves_path = FS.get_path("$app_data_root$")->m_Path;
		strconcat(sizeof(save_name), metadata.save_name, game_saves_path, "metadata");
		strconcat(sizeof(save_name), metadata.save_name, metadata.save_name, SAVE_EXTENSION);

		IReader* stream;
		stream = FS.r_open(metadata.save_name);
		if (!stream) {
			FS.r_close(stream);
			IWriter* writer = FS.w_open(metadata.save_name);
			metadata.SaveAll(writer);
			FS.w_close(writer);
		}
		else {
			metadata.LoadAll(stream);
			FS.r_close(stream);
		}

		metadata.isInited = true;
	}
	return metadata;
}

void CPlayerMetadata::ProcessSave()
{
	IWriter* writer = FS.w_open(save_name);
	SaveAll(writer);
	FS.w_close(writer);
}

void CPlayerMetadata::IncStartNewGame()
{
	//Device
}

void CPlayerMetadata::IncSaveGame()
{
}

void CPlayerMetadata::IncLoadGame()
{
}
