#pragma once

class IReader;
class IWriter;

class CAlifePlayerData
{
	xr_vector<u8> data = {};

public:
	void save();
	void load();

	void read(IReader& reader);
	void write(IWriter& writer);
};

