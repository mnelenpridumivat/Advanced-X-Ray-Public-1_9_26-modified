#pragma once
#include "../xrCore/_types.h"

class IWriter;
class IReader;

class CPlayerMetadata
{
	bool isInited = false;
	string_path save_name;

	void SaveAll(IWriter* writer);
	void LoadAll(IReader* reader);

	CPlayerMetadata();
public:
	~CPlayerMetadata();

	CPlayerMetadata(const CPlayerMetadata& other) = delete;
	CPlayerMetadata(CPlayerMetadata&& other) = delete;
	CPlayerMetadata& operator=(const CPlayerMetadata& other) = delete;
	CPlayerMetadata& operator=(CPlayerMetadata&& other) = delete;

	static CPlayerMetadata& GetInstance();

	void ProcessSave();

	void IncStartNewGame();
	void IncSaveGame();
	void IncLoadGame();

};

