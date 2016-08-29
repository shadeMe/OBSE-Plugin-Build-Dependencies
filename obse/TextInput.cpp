#include "TextInput.h"

TextInputMessageBox::TextInputMessageBox(char* fmtString, Script* callingScript, TESObjectREFR* callingObj)
	: m_promptText("")
{
	UInt32 fmtStringLen = strlen(fmtString);
	m_fmtString = new char[fmtStringLen + 1];
	strcpy_s(m_fmtString, fmtStringLen + 1, fmtString);

	m_scriptRefID = callingScript->refID;
	if (callingObj && (callingObj->flags & 0x00004000))	//not a temporary script
		m_scriptRefID = callingObj->refID;
}

void TextInputMessageBox::Update(std::string outputText)
{
	std::string messageText = std::string(m_promptText) + outputText;
	MessageMenu* msgBox = (MessageMenu*)GetMenuByType(kMenuType_Message);
	if (msgBox)
	{
		msgBox->messageText->SetStringValue(kTileValue_string, messageText.c_str());
		msgBox->messageText->UpdateField(kTileValue_string, 0.0, messageText.c_str());
	}
}

void TextInputMessageBox::Init()
{
	char separatorChar = '@';	// '|' doesn't work in console, substitute for testing
	char* buttons[10] = { NULL };
	UInt32 numButtons = 0;
	UInt32 fmtStringLen = strlen(m_fmtString);
	
	//separate prompt text and button text
	for (UInt32 strPos = 0; strPos < fmtStringLen && numButtons < 10; strPos++)
	{
		if (m_fmtString[strPos] == separatorChar && (strPos + 1 < fmtStringLen))
		{
			m_fmtString[strPos] = '\0';
			buttons[numButtons++] = m_fmtString + strPos + 1;
		}
	}

	m_promptText = m_fmtString;
	if (!buttons[0])		//supply default button
		buttons[0] = "Finished";


	ShowMessageBox(m_fmtString, ShowMessageBox_Callback, 0, buttons[0], buttons[1], buttons[2], buttons[3], buttons[4],
		buttons[5], buttons[6], buttons[7], buttons[8], buttons[9]);

	*ShowMessageBox_pScriptRefID = m_scriptRefID;
	*ShowMessageBox_button = -1;

	delete m_fmtString;
	m_fmtString = NULL;
}


TextInputJournal::~TextInputJournal()
{
	m_dummyBook->Destroy(false);
}

TextInputJournal::TextInputJournal(char* staticText, char* defaultText, UInt32 font, const char* fontColor)
	: m_staticText(staticText), m_defaultText(defaultText)
{
	m_staticText = std::string("<DIV align=\"left\">") + m_staticText;

	if (font && font < 6)
	{
		std::string fontStr = "<FONT face=\"";
		fontStr.append(1, font + '0');
		fontStr.append("\">");
		m_staticText = fontStr + m_staticText;
	}

	if (fontColor)
	{
		std::string fontColorStr = "<FONT color=\"";
		fontColorStr.append(fontColor);
		fontColorStr.append("\">");
		m_staticText = fontColorStr + m_staticText;
	}

	//Create a proxy book object (required by some of the BookMenu code)
	m_dummyBook = (TESObjectBOOK*)FormHeap_Allocate(sizeof(TESObjectBOOK));
	m_dummyBook->Constructor();
	m_dummyBook->bookFlags = (TESObjectBOOK::kBook_CantBeTaken);
	//TODO: Set flag according to whether it's a scroll or book
}

void TextInputJournal::Init()
{
	//TODO: Turn menu creation into a template function?

	InterfaceManager* intfc = InterfaceManager::GetSingleton();
	Tile* tile = intfc->menuRoot->ReadXML("data\\menus\\book_menu.xml");
	if (tile)
	{
		Tile* bookRoot = tile->GetRoot();
		if (bookRoot)
		{
			TileMenu* bookMenuTile = tile_cast <TileMenu>(bookRoot);
			if (bookMenuTile)
			{
				BookMenu* bookMenu = (BookMenu*)(bookMenuTile->menu);
				if (bookMenu)
				{
					bookMenu->book = m_dummyBook;
					bookMenu->bookRef = NULL;

					ToggleMenuShortcutKeys(false, bookMenu);

					bookMenu->RegisterTile(bookMenuTile);
					
					//TODO: allow creation of scroll menu too
					bookMenu->tile->UpdateFloat(BookMenu::kBookValue_IsBook, 1.0);	
					
					bookMenu->EnableMenu(false);
					bookMenu->UpdateText(m_staticText.c_str());
				}
			}
		}
	}
}

//TODO: 
//	-Extract most of this and ResolveControlCode() to a wrapper class so that storing book text in a StringVar
//		allows conversion to/from HTML and control characters
//	-Support for <IMG> and <FONT> tags
//  -Parse HTML tags
void TextInputJournal::Update(std::string outputText)
{
	//convert control characters to HTML
	for (UInt32 strPos = 0; strPos < outputText.length(); strPos++)
	{
		bool bIsControlChar = false;
		switch (outputText[strPos])
		{
		case kControl_Enter:
			outputText.insert(strPos, "<BR>");
			strPos += 4;
			bIsControlChar = true;
			break;
		case kControl_Center:
			outputText.insert(strPos, "<DIV align=\"center\">");
			strPos += 20;
			bIsControlChar = true;
			break;
		case kControl_Left:
			outputText.insert(strPos, "<DIV align=\"left\">");
			strPos += 18;
			bIsControlChar = true;
			break;			
		case kControl_Right:
			outputText.insert(strPos, "<DIV align=\"right\">");
			strPos += 19;
			bIsControlChar = true;
			break;
		case kControl_NewPage:
			outputText.insert(strPos, "<HR>");
			strPos += 4;
			bIsControlChar = true;
			break;
		}

		if (bIsControlChar)
			outputText.erase(strPos, 1);
	}

	BookMenu* bookMenu = (BookMenu*)GetMenuByType(kMenuType_Book);
	if (bookMenu)
		bookMenu->UpdateText((m_staticText + outputText).c_str());
}

bool TextInputJournal::ResolveControlCode(UInt8 controlCharacter, std::string* outStr)
{
	//return control codes based on key pressed
	//non-printing chars are used as placeholders for html tags to allow deletion of formatting
	//	and to keep input text synced with output text

	switch (controlCharacter)
	{
	case 13:		//Enter
		*outStr = std::string(1, kControl_Enter);
		return true;
	case 'C':
		*outStr = std::string(1, kControl_Center);
		return true;
	case 'L':
		*outStr = std::string(1, kControl_Left);
		return true;
	case 'R':
		*outStr = std::string(1, kControl_Right);
		return true;
	case 'H':
		*outStr = std::string(1, kControl_NewPage);
		return true;
	default:
		return false;
	}
}



TextInputHandler* TextInputHandler::s_singleton = NULL;
UInt32 TextInputHandler::s_MAX_LEN = 4096;			//TODO: prevent text from running off bottom of screen (check menu height?)

void TextInputHandler::Close()
{
	delete s_singleton;
	s_singleton = NULL;

	//Reset adjusted ini setting bBackgroundKeyboard
}

bool TextInputHandler::BlinkCursor()
{
	if (!m_cursorTimer)
	{
		m_cursorTimer = GetTickCount();
		m_cursorChar = '|';
	}

	DWORD elapsedTime = GetTickCount();
	if (elapsedTime - m_cursorTimer > m_cursorDelay)
	{
		m_cursorTimer = elapsedTime;
		m_cursorChar = (m_cursorChar == '|') ? 127 : '|';
		m_inputText.replace(m_cursorPos, 1, 1, m_cursorChar);

		return true;
	}
	else
		return false;
}

UInt32 TextInputHandler::FindWordBoundary(bool bFindBackwards)
{
	UInt32 terminalVal = m_inputText.length() - 1;
	SInt32 stepVal = 1;
	bool bPatternStart = false;

	if (bFindBackwards)
	{
		terminalVal = 0;
		stepVal = -1;
		bPatternStart = true;
	}

	UInt32 idx = m_cursorPos + stepVal;
	if (idx == terminalVal)
		return m_cursorPos;

	char prevChar = m_inputText[idx];
	char nextChar = 0;
	bool bPrevIsGraph = isgraph(prevChar) ? true : false;
	idx += stepVal;

	while (idx != terminalVal)
	{
		nextChar = m_inputText[idx];
		bool bNextIsGraph = isgraph(nextChar) ? true : false;
		if (bPrevIsGraph == bPatternStart && bNextIsGraph != bPatternStart)
			break;

		idx += stepVal;
		prevChar = nextChar;
		bPrevIsGraph = bNextIsGraph;
	}

	return bFindBackwards ? idx + 1 : idx;


/*	for (UInt32 strPos = m_cursorPos + stepVal; strPos != terminalVal; strPos += stepVal)
	{
		if (!isgraph(m_inputText[strPos]))
			return strPos;
	}

	return -1;
*/
}

bool TextInputHandler::Create(TextInputMenu* menu, UInt16 maxLen)
{
	if (s_singleton)		//already initialized
		return false;
	else
	{
		s_singleton = new TextInputHandler(menu, maxLen);
		return true;
	}

	//TODO: SetIniSetting bBackgroundKeyboard 1 (fix for issue with GetAsyncKeyState() on Win2000)
}

TextInputHandler::TextInputHandler(TextInputMenu* menu, UInt16 maxLen)
	: m_menu(menu), m_maxInputLen(maxLen), m_cursorPos(0), m_cursorTimer(0), m_cursorDelay(500), m_controlKeyPressed(-1)
{
	//initialize keyboard state array
	for (UInt32 i = 0; i < 256; i++)
		m_prevKeyboardState[i] = (GetAsyncKeyState(i) & 0x8000) ? 0x80 : 0x00;

	m_inputText = m_menu->GetDefaultText();
	m_cursorPos = m_inputText.length();

	m_menu->Init();
}

void TextInputHandler::GetInputString(char* outString)	
{ 
	std::string str = m_inputText;
	str.erase(m_cursorPos, 1);

	//TODO: convert control characters before returning string
	strcpy_s(outString, str.length() + 1, str.c_str());
}

UInt8 TextInputHandler::GetControlKeyPressed()
{
	//like GetButtonPressed, value is reset to -1 once it is returned
	UInt8 ctrlKey = m_controlKeyPressed;
	m_controlKeyPressed = -1;
	return ctrlKey;
}

void TextInputHandler::Update()
{
	//TODO: prevent this running while console is open? Doesn't prevent use of console but console text echoed in input text

	static bool bGotKeyboardLayout = false;
	static HKL keyboardLayout = 0;

	if (!bGotKeyboardLayout)
	{
		keyboardLayout = GetKeyboardLayout(0);
		bGotKeyboardLayout = true;
	}

	bool bUpdateText = false;

	//Synthesize lpKeyboardState param to pass to ToAsciiEx, and simultaneously check for keypresses
	//TODO: Allow holding down arrow/delete keys rather than requiring individual keypresses? CTRL alleviates this somewhat
	UInt32 keyPressed = 0;
	BYTE keyboardState[256] = { 0 };
	for (UInt32 keyCode = 0; keyCode < 256; keyCode++)
	{
		UInt32 keyState = GetAsyncKeyState(keyCode);
		keyboardState[keyCode] = (keyState & 0x8000) ? 0x80 : 0x00;
		if (!keyPressed && (keyState & 0x8000))		//key is pressed
			if (!(m_prevKeyboardState[keyCode] & 0x80))	//and not previously pressed
				if (IsValidInputKey(keyCode))
					keyPressed = keyCode;
	}

	memcpy(m_prevKeyboardState, keyboardState, 256);

	bool bCtrlPressed = (keyboardState[VK_CONTROL] & 0x80) ? true : false;
	bool bAltPressed = (keyboardState[VK_MENU] & 0x80) ? true : false;

	if (bCtrlPressed && keyPressed >= 'A' && keyPressed <= 'Z')
	{
		std::string ctrlString("");
		if (m_menu->ResolveControlCode(keyPressed, &ctrlString))
		{
			m_inputText.insert(m_cursorPos, ctrlString);
			m_cursorPos += ctrlString.length();
		}
		else
			m_controlKeyPressed = keyPressed;		// allow script to handle it if unhandled by TextInputMenu
	}
	else
	{
		switch (keyPressed)
		{
		case 0:
			break;
		case VK_RETURN:
			if (m_inputText.length() < m_maxInputLen)
			{
				std::string enterStr("\n");
				m_menu->ResolveControlCode(13, &enterStr);
				m_inputText.insert(m_cursorPos, enterStr);	
				m_cursorPos += enterStr.length();
				bUpdateText = true;
			}

			break;
		case VK_BACK:
			if (m_cursorPos > 0)
			{
				if (bCtrlPressed)
				{
					UInt32 wordPos = FindWordBoundary(true);
					
					if (wordPos != -1 && wordPos < m_cursorPos)
					{						
						//m_inputText.erase(wordPos + 1, (m_cursorPos - wordPos - 1));
						//m_cursorPos = wordPos + 1;
						m_inputText.erase(wordPos, (m_cursorPos - wordPos));
						m_cursorPos = wordPos;
						bUpdateText = true;
						
						break;
					}
				}

				m_inputText.erase(--m_cursorPos, 1);

				bUpdateText = true;
			}

			break;
		case VK_DELETE:
			if (m_cursorPos < m_inputText.length())
			{
				if (bCtrlPressed)
				{
					UInt32 wordPos = FindWordBoundary();
					if (wordPos != -1 && wordPos > m_cursorPos)
					{
						//m_inputText.erase(m_cursorPos + 1, (wordPos - m_cursorPos - 1));
						m_inputText.erase(m_cursorPos + 1, (wordPos - m_cursorPos - 1));
						bUpdateText = true;

						break;
					}
				}
				
				m_inputText.erase(m_cursorPos + 1, 1);
				bUpdateText = true;
			}

			break;
		case VK_TAB:
			if (m_cursorPos + 5 < m_maxInputLen)
			{
				m_inputText.insert(m_cursorPos, 5, ' ');
				m_cursorPos += 5;
				bUpdateText = true;
			}

			break;
		case VK_LEFT:
			if (m_cursorPos > 0)
			{
				if (bCtrlPressed)
				{
					UInt32 wordPos = FindWordBoundary(true);
					if (wordPos != -1 && wordPos < m_cursorPos)
					{
						m_inputText.erase(m_cursorPos, 1);
						m_cursorPos = wordPos;
						m_inputText.insert(m_cursorPos, 1, m_cursorChar);
						bUpdateText = true;
						
						break;
					}
				}
				m_inputText.replace(m_cursorPos, 1, 1, m_inputText[m_cursorPos - 1]);
				m_inputText.replace(--m_cursorPos, 1, 1, m_cursorChar);
				bUpdateText = true;
			}

			break;
		case VK_RIGHT:
			if (m_cursorPos < m_inputText.length() - 1)
			{
				if (bCtrlPressed)
				{
					UInt32 wordPos = FindWordBoundary();
					if (wordPos != -1 && wordPos > m_cursorPos)
					{
						m_inputText.erase(m_cursorPos, 1);
						m_cursorPos = wordPos - 1;
						m_inputText.insert(m_cursorPos, 1, m_cursorChar);
						bUpdateText = true;

						break;
					}
				}
				m_inputText.replace(m_cursorPos, 1, 1, m_inputText[m_cursorPos + 1]);
				m_inputText.replace(++m_cursorPos, 1, 1, m_cursorChar);
				bUpdateText = true;
			}

			break;
		default:		//map to ASCII if possible and insert char into input text
			{	
				if (m_inputText.length() == m_maxInputLen)
					break;

				unsigned short asciiResult[2] = { 0 };
				UInt32 toAscii = ToAsciiEx(keyPressed, MapVirtualKeyEx(keyPressed, 0, keyboardLayout), 
					keyboardState, asciiResult, 0, keyboardLayout);

				if (toAscii == 1 && isprint(asciiResult[0]))		//got a valid char
				{
					m_inputText.insert(m_cursorPos++, 1, asciiResult[0]);
					bUpdateText = true;
				}

			}
		}
	}

	if (BlinkCursor())
		bUpdateText = true;

	if (bUpdateText)	//Update displayed text
		m_menu->Update(m_inputText);
}

//NOTE: This probably won't correctly handle all keys on non-U.S. keyboards
bool TextInputHandler::IsValidInputKey(UInt32 keyCode)
{
	switch (keyCode)
	{
	case VK_SPACE:
		return true;
	case VK_RETURN:
		return true;
	case VK_BACK:
		return true;
	case VK_LEFT:
		return true;
	case VK_RIGHT:
		return true;
	case VK_TAB:
		return true;
	case VK_DELETE:
		return true;
	default:
		if (keyCode >= 0x41 && keyCode <= 0x5A)		//A..Z
			return true;
		else if (keyCode >= 0x30 && keyCode <= 0x39)	//0..9
			return true;
		else if (keyCode >= VK_OEM_1 && keyCode <= VK_OEM_3)	//various punctuation
			return true;
		else if (keyCode >= VK_OEM_4 && keyCode <= VK_OEM_7)	//various punctuation
			return true;
	}

	return false;
}