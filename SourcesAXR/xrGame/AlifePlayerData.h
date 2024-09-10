#pragma once

class IReader;
class IWriter;

class CAlifePlayerData
{
public:
	void save();
	void load();

	void read(IReader* reader);
	void write(IWriter* reader);
};

