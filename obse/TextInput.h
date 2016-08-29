//class definitions for text input, defined separately to avoid cluttering up Commands_Input.cpp
#pragma once

#include "GameForms.h"
#include "GameObjects.h"
#include "GameMenus.h"
#include <string>
#include "Hooks_Gameplay.h"

//abstract base class for various text input menus
class TextInputMenu
{
	std::string m_promptText;
	UInt32 m_maxLen;
	UInt32 m_defaultTextEndPos;		//text preceding this pos can't be erased by user

public:
	virtual	~TextInputMenu() = 0;
	virtual void Update(std::string outputText) = 0;		//refreshes the menu when text changes
	virtual void Init() = 0;								//Initializes and displays menu after construction
	virtual bool ResolveControlCode(UInt8 controlCharacter) = 0;	//translate a control-character to text
	virtual UInt32 DeleteText(UInt32 startPos, UInt32 numToDelete, bool bBackward, bool bDeleteWord = false);

	UInt32 InsertChar(UInt32 insertPos, char toInsert);			//returns position one past the end of toInsert
	UInt32 InsertText(UInt32 insertPos, const char* toInsert);	//as above
	
};

//A messagebox
class TextInputMessageBox : public TextInputMenu
{
	std::string	m_promptText;
	char		* m_fmtString;
	UInt32		m_scriptRefID;

public:
	virtual ~TextInputMessageBox()
		{	}
	virtual void Update(std::string outputText);
	virtual void Init();
	virtual bool ResolveControlCode(UInt8 controlCharacter, std::string* outStr)
		{	return false;	}
	virtual std::string GetDefaultText()
		{	return "";	}

	TextInputMessageBox(char* fmtString, Script* callingScript, TESObjectREFR* callingObj);
};

//A book or scroll
class TextInputJournal : public TextInputMenu
{
	std::string		m_staticText;		// text MUST begin with an html tag. Probably put font here
	std::string		m_defaultText;
	TESObjectBOOK	* m_dummyBook;

public:
	virtual ~TextInputJournal();
	virtual void Update(std::string outputText);
	virtual void Init();
	virtual bool ResolveControlCode(UInt8 controlCharacter, std::string* outStr);
	virtual std::string GetDefaultText()
		{	return m_defaultText;	}
	TextInputJournal(char* staticText, char* defaultText, UInt32 font = 0, const char* fontColor = NULL);
};

//Contains and controls TextInputMenu object
class TextInputHandler
{
	TextInputHandler(TextInputMenu* menu, UInt16 maxLen);

	static TextInputHandler	* s_singleton;						//not technically a singleton but close enough I suppose
	TextInputMenu			* m_menu;
//	UInt16					m_maxInputLen;
	UInt16					m_cursorPos;
	DWORD					m_cursorTimer;
	DWORD					m_cursorDelay;
	char					m_cursorChar;
//	std::string				m_inputText;
	BYTE					m_prevKeyboardState[256];
//	bool					bBackgroundKeyboardInitialState;
	UInt8					m_controlKeyPressed;				//scripts can check this for user-defined controls

	bool	BlinkCursor();		//returns true if cursor char changed
	bool	IsValidInputKey(UInt32 keyCode);
	UInt32	FindWordBoundary(bool bFindBackwards = false);
public:
	static UInt32	s_MAX_LEN;

	~TextInputHandler()
		{	delete m_menu;	}
	static TextInputHandler * GetTextBox()	
		{	return s_singleton;	}
	static bool Create(TextInputMenu* menu, UInt16 maxLen);
	void GetInputString(char* outString);	
	void Update();
	void Close();
	UInt8 GetControlKeyPressed();
};