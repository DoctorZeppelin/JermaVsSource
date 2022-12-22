//The following include files are necessary to allow your MyPanel.cpp to compile.
#include "cbase.h"
#include "IDialoguePanel.h"
using namespace vgui;
#include <vgui/IVGui.h>
#include <vgui_controls/Frame.h>
#include <vgui_controls/TextEntry.h>

//CMyPanel class: Tutorial example class
class CDialoguePanel : public vgui::Frame
{
    DECLARE_CLASS_SIMPLE(CDialoguePanel, vgui::Frame);
    //CMyPanel : This Class / vgui::Frame : BaseClass

	CDialoguePanel(vgui::VPANEL parent); 	// Constructor
    ~CDialoguePanel(){};				// Destructor

protected:
    //VGUI overrides:
    virtual void OnTick();
    virtual void OnCommand(const char* pcCommand);

private:
    //Other used VGUI control Elements:
	vgui::TextEntry* m_pTime; // Panel class declaration, private section
};

// Constuctor: Initializes the Panel
CDialoguePanel::CDialoguePanel(vgui::VPANEL parent)
: BaseClass(NULL, "DialoguePanel")
{
	SetParent(parent);

	SetKeyBoardInputEnabled(true);
	SetMouseInputEnabled(false);

	SetProportional(false);
	SetTitleBarVisible(false);
	SetMinimizeButtonVisible(false);
	SetMaximizeButtonVisible(false);
	SetCloseButtonVisible(false);
	SetSizeable(false);
	SetMoveable(false);
	SetVisible(true);


	SetScheme(vgui::scheme()->LoadSchemeFromFile("resource/SourceScheme.res", "SourceScheme"));

	LoadControlSettings("resource/UI/DialoguePanel.res");

	vgui::ivgui()->AddTickSignal(GetVPanel(), 100);

	DevMsg("MyPanel has been constructed\n");

	m_pTime = new vgui::TextEntry(this, "MyTextEntry");
	m_pTime->SetPos(15, 310);
	m_pTime->SetSize(50, 20);
}

//Class: CMyPanelInterface Class. Used for construction.
class CDialoguePanelInterface : public IDialoguePanel
{
private:
	CDialoguePanel* DialoguePanel;
public:
	CDialoguePanelInterface()
	{
		DialoguePanel = NULL;
	}
	void Create(vgui::VPANEL parent)
	{
		DialoguePanel = new CDialoguePanel(parent);
	}
	void Destroy()
	{
		if (DialoguePanel)
		{
			DialoguePanel->SetParent((vgui::Panel*)NULL);
			delete DialoguePanel;
		}
	}
};

static CDialoguePanel g_DialoguePanel;
IDialoguePanel* DialoguePanel = (IDialoguePanel*)&g_DialoguePanel;

void CDialoguePanel::OnTick()
{
	BaseClass::OnTick();
}

void CDialoguePanel::OnCommand(const char* pcCommand)
{
	BaseClass::OnCommand(pcCommand);
}