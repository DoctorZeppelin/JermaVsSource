//The following include files are necessary to allow your MyPanel.cpp to compile.
#include "cbase.h"
#include "IMyPanel.h"
using namespace vgui;
#include <vgui/IVGui.h>
#include <vgui/IScheme.h>
#include <vgui_controls/Frame.h>
#include <vgui_controls/Button.h>
#include <vgui_controls/RichText.h>
#include <vgui_controls/ScalableImagePanel.h>
#include <vgui_controls/Label.h>

//CMyPanel class: Tutorial example class
class CMyPanel : public vgui::Frame
{
	DECLARE_CLASS_SIMPLE(CMyPanel, vgui::Frame);
	//CMyPanel : This Class / vgui::Frame : BaseClass

	CMyPanel(vgui::VPANEL parent); 	// Constructor
	~CMyPanel() {};				// Destructor

protected:
	//VGUI overrides:
	virtual void OnTick();
	virtual void OnCommand(const char* pcCommand);
	virtual void ApplySchemeSettings(vgui::IScheme* pScheme);

private:
	//Other used VGUI control Elements:
	vgui::IImage* m_pActiveImage;
	Button* m_pCloseButton;
	RichText* m_pDialogue;
	ScalableImagePanel* m_pIcon;
};

// Constuctor: Initializes the Panel
CMyPanel::CMyPanel(vgui::VPANEL parent)
	: BaseClass(NULL, "MyPanel")
{
	SetParent(parent);

	SetKeyBoardInputEnabled(true);
	SetMouseInputEnabled(true);

	SetProportional(true);
	SetTitleBarVisible(false);
	SetMinimizeButtonVisible(false);
	SetMaximizeButtonVisible(false);
	SetCloseButtonVisible(false);
	SetSizeable(false);
	SetMoveable(false);
	SetVisible(true);


	SetScheme(vgui::scheme()->LoadSchemeFromFile("resource/DialogueScheme.res", "DialogueScheme"));

	LoadControlSettings("resource/UI/mypanel.res");

	vgui::ivgui()->AddTickSignal(GetVPanel(), 100);

	DevMsg("MyPanel has been constructed\n");
}

void CMyPanel::ApplySchemeSettings(IScheme* pScheme)
{
	// load control settings...
	LoadControlSettings("resource/dialoguescheme.res");

	BaseClass::ApplySchemeSettings(pScheme);

	//Button done
	m_pCloseButton = new Button(this, "Button", "Close", this, "turnoff");
	m_pCloseButton->SetPos(433, 472);
	m_pCloseButton->SetDepressedSound("common/bugreporter_succeeded.wav");
	m_pCloseButton->SetReleasedSound("ui/buttonclick.wav");

	//Text -- Dialogue
	RichText* m_pDialogue = new RichText(this, "dialogue");
	m_pDialogue->SetText("JERMAVEEEENUUSS!!!!!");
	m_pDialogue->SetFont(pScheme->GetFont("DefaultVerySmall"));
	m_pDialogue->SetPos(342, 0);
	m_pDialogue->SetSize(1579, 512);
	m_pDialogue->SetVisible(true);

	//ImagePanel -- Speaker Icon
	ScalableImagePanel* m_pIcon = new ScalableImagePanel(this, "talkericon");
	m_pIcon->SetScheme("ClientScheme.res");
	m_pIcon->SetImage("IconTest");
	m_pIcon->SetPos(200, 200);
	m_pIcon->SetSize(200, 200);
	m_pIcon->SetVisible(true);

}

//Class: CMyPanelInterface Class. Used for construction.
class CMyPanelInterface : public MyPanel
{
private:
	CMyPanel* MyPanel;
public:
	CMyPanelInterface()
	{
		MyPanel = NULL;
	}
	void Create(vgui::VPANEL parent)
	{
		MyPanel = new CMyPanel(parent);
	}
	void Destroy()
	{
		if (MyPanel)
		{
			MyPanel->SetParent((vgui::Panel*)NULL);
			delete MyPanel;
		}
	}
	void Activate(void)
	{
		if (MyPanel)
		{
			MyPanel->Activate();
		}
	}
};
static CMyPanelInterface g_MyPanel;
MyPanel* mypanel = (MyPanel*)&g_MyPanel;

ConVar cl_showmypanel("cl_showmypanel", "0", FCVAR_CLIENTDLL, "Sets the state of myPanel <state>");

void CMyPanel::OnTick()
{
	BaseClass::OnTick();
	SetVisible(cl_showmypanel.GetBool());
}

CON_COMMAND(DialogueTestMenu, "Toggles testpanelfenix on or off")
{
	cl_showmypanel.SetValue(!cl_showmypanel.GetBool());
	mypanel->Activate();
};

void CMyPanel::OnCommand(const char* pcCommand)
{
	BaseClass::OnCommand(pcCommand);

	if (!Q_stricmp(pcCommand, "turnoff"))
		cl_showmypanel.SetValue(0);
}