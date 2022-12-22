#pragma once
class IDialoguePanel
{
public:
	virtual void		Create(vgui::VPANEL parent) = 0;
	virtual void		Destroy(void) = 0;
};

extern IDialoguePanel* DialoguePanel;