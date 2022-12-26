#pragma once

#include "cbase.h"
#include "DialogueEntity.h"

class CDialogueEntity : public CLogicalEntity
{
public:
	DECLARE_CLASS(CDialogueEntity, CLogicalEntity);
	void Spawn();
	void Think();
	COutputEvent	m_OnRead;
	string_t	m_DialogueName;
	void Read(inputdata_t& inputdata);
private:
	// Add any member variables or functions that you need here.
	int	m_nThreshold;	// Count at which to fire our output
	int	m_nCounter;	// Internal counter

	COutputEvent	m_OnThreshold;	// Output event when the counter reaches the threshold
};

LINK_ENTITY_TO_CLASS(dialogue_entity, CDialogueEntity);

BEGIN_DATADESC(CDialogueEntity)
// don't save, recomputed on load
//DEFINE_FIELD( m_soundscapeIndex, FIELD_INTEGER ),
DEFINE_FIELD(m_DialogueName, FIELD_STRING),

// Silence, Classcheck!
//	DEFINE_ARRAY( m_positionNames, FIELD_STRING, 4 )

DEFINE_INPUTFUNC(FIELD_VOID, "Read", Read),

DEFINE_OUTPUT(m_OnRead, "OnRead"),


END_DATADESC()