#include "FileReader.h"
#include <string>
#include <fstream>

std::string GetFileText(std::string FileName)
{
	std::string Text;
	std::ifstream File(FileName);
	if (File.is_open())
	{
		char buffer[4096];
		while (File.read(buffer, sizeof(buffer)))
			Text.append(buffer, sizeof(buffer));
		Text.append(buffer, File.gcount());
	}
	else
	{
		Text.append("ERROR: COULD NOT OPEN FILE.");
	}
	File.clear();
	File.close();
	return Text;
}

void UpdateFile(std::string FileName, std::string FileString)
{
	// Replace contents of File with the in FileString
	std::ofstream File(FileName);
	File << FileString;
	File.close();
}