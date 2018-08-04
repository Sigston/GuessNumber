#pragma once
#include <string>

class Drawer
{
private:
	const unsigned int mScreenSpace;
	const unsigned int mPadding;
	const char mScreenCharacter;
	const unsigned int mDrawSpace;
	const std::string mUserPrompt;

	void AddPadding(std::string &Result);
	void DrawLine(std::string &Line);
	std::string MakeLine(std::string &Line);

public:
	Drawer(unsigned int ScreenSpace, unsigned int Padding, char ScreenCharacter, std::string UserPrompt);
	void DrawSeperator();
	void DrawBlankLine();
	void DrawCentralLine(std::string Text);
	void DrawText(std::string Text);
	void DrawMultiLineText(std::string Text);
	void DrawUserPrompt();
};
