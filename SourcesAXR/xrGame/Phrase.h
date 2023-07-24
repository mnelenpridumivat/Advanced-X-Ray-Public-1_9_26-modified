#pragma once

#include "PhraseScript.h"

class CPhraseDialog;
class CGameObject;

class CPhrase
{
private:
	friend CPhraseDialog;
public:
							CPhrase			();
	virtual					~CPhrase		();

	void					SetText			(LPCSTR text)			{m_text = text;}
	LPCSTR					GetText			()	const;

	LPCSTR					GetScriptText	()	const;

	void					SetID			(const shared_str& id)	{m_ID = id;}
	const shared_str&		GetID			()	const				{return m_ID;}
	bool					IsFinalizer		()	const				{return m_b_finalizer;}
	void					SetFinalizer	(bool b)				{m_b_finalizer=b;}
	int						GoodwillLevel	()	const				{return m_iGoodwillLevel;}

	bool					IsDummy			()	const;
	CDialogScriptHelper*	GetScriptHelper	()						{return &m_ScriptHelper;};

	int						GetGoodwillLevel() const				{return m_iGoodwillLevel;}
	void					SetGoodwillLevel(int v)					{m_iGoodwillLevel = v;}

	void SetSwitchingSpeaker(bool Switching) {m_switching_speaker = Switching;}
	bool GetSwitchingSpeaker() { return m_switching_speaker; }

	void SetSpeakerNameOverride(LPCSTR name) { m_speaker_name_override = name; }
	LPCSTR GetSpeakerNameOverride() { return m_speaker_name_override.c_str(); }

protected:
	//���������� ������ � ������ ���� �������
	shared_str		m_ID;
	//��������� ������������� �����
	xr_string		m_text;
	xr_string		m_script_text_id;	
	xr_string		m_script_text_val;
	//����������� ������� ���������������, ����������� ��� ����
	//���� ����� ����� ���� �������
	int				m_iGoodwillLevel;
	bool			m_b_finalizer;
	//��� ������ ���������� �������
	CDialogScriptHelper	m_ScriptHelper;

	bool			m_switching_speaker;
	xr_string		m_speaker_name_override;
};