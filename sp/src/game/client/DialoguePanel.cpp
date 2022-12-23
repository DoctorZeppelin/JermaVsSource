//The following include files are necessary to allow your DialoguePanel.cpp to compile.
#include "cbase.h"
#include "IDialoguePanel.h"
using namespace vgui;
#include <vgui/IVGui.h>
#include <vgui/IScheme.h>
#include <vgui_controls/Frame.h>
#include <vgui_controls/Button.h>
#include <vgui_controls/RichText.h>
#include <vgui_controls/ScalableImagePanel.h>
#include <vgui_controls/Label.h>

//CDialoguePanel class: Tutorial example class
class CDialoguePanel : public vgui::Frame
{
	DECLARE_CLASS_SIMPLE(CDialoguePanel, vgui::Frame);
	//CDialoguePanel : This Class / vgui::Frame : BaseClass

	CDialoguePanel(vgui::VPANEL parent); 	// Constructor
	~CDialoguePanel() {};				// Destructor

protected:
	//VGUI overrides:
	virtual void OnTick();
	virtual void OnCommand(const char* pcCommand);
	virtual void ApplySchemeSettings(vgui::IScheme* pScheme);

private:
	//Other used VGUI control Elements:
	Button* m_pCloseButton;
	Label* m_pDialogue;
	ScalableImagePanel* m_pIcon;
};

// Constuctor: Initializes the Panel
CDialoguePanel::CDialoguePanel(vgui::VPANEL parent)
	: BaseClass(NULL, "DialoguePanel")
{
	SetParent(parent);

	SetKeyBoardInputEnabled(true);
	SetMouseInputEnabled(true);

	SetProportional(false);
	SetTitleBarVisible(false);
	SetMinimizeButtonVisible(false);
	SetMaximizeButtonVisible(false);
	SetCloseButtonVisible(false);
	SetSizeable(false);
	SetMoveable(false);
	SetVisible(true);


	SetScheme(vgui::scheme()->LoadSchemeFromFile("resource/DialogueScheme.res", "DialogueScheme"));

	vgui::ivgui()->AddTickSignal(GetVPanel(), 100);

	DevMsg("DialoguePanel has been constructed\n");

	//Button done
	m_pCloseButton = new Button(this, "Button", "Close", this, "turnoff");
	m_pCloseButton->SetDepressedSound("common/bugreporter_succeeded.wav");
	m_pCloseButton->SetReleasedSound("ui/buttonclick.wav");

	//Text -- Dialogue
	Label* m_pDialogue = new Label(this, "dialogue", "JERMAVEEEENUS!!!!");
	m_pDialogue->SetVisible(true);

	//ImagePanel -- Speaker Icon
	ScalableImagePanel* m_pIcon = new ScalableImagePanel(this, "talkericon");
	m_pIcon->SetScheme("ClientScheme.res");
	m_pIcon->SetImage("IconTest");
	m_pIcon->SetVisible(true);

}

void CDialoguePanel::ApplySchemeSettings(IScheme* pScheme)
{
	// load control settings...
	LoadControlSettings("resource/ui/dialoguepanel.res");

	BaseClass::ApplySchemeSettings(pScheme);
}

//Class: CDialoguePanelInterface Class. Used for construction.
class CDialoguePanelInterface : public DialoguePanel
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
	void Activate(void)
	{
		if (DialoguePanel)
		{
			DialoguePanel->Activate();
		}
	}
};
static CDialoguePanelInterface g_DialoguePanel;
DialoguePanel* dialoguepanel = (DialoguePanel*)&g_DialoguePanel;

ConVar cl_showdialoguepanel("cl_showdialoguepanel", "0", FCVAR_CLIENTDLL, "Sets the state of Dialogue Panel <state>");

void CDialoguePanel::OnTick()
{
	BaseClass::OnTick();
	SetVisible(cl_showdialoguepanel.GetBool());
}

CON_COMMAND(DialogueTestMenu, "Toggles Dialogue Test Menu on or off")
{
	cl_showdialoguepanel.SetValue(!cl_showdialoguepanel.GetBool());
	dialoguepanel->Activate();
};

void CDialoguePanel::OnCommand(const char* pcCommand)
{
	BaseClass::OnCommand(pcCommand);

	if (!Q_stricmp(pcCommand, "turnoff"))
		cl_showdialoguepanel.SetValue(0);
}