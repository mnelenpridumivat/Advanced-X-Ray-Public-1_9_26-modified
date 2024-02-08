#pragma once

class CVisualZone :
	public CCustomZone,
	public IMetaClass
{
	DECLARE_METACLASS1(CVisualZone, CCustomZone)
	typedef				CCustomZone		inherited	;
	MotionID			m_idle_animation			;
	MotionID			m_attack_animation			;
	u32					m_dwAttackAnimaionStart		;
	u32					m_dwAttackAnimaionEnd		;
public:
	CVisualZone				()						;
	~CVisualZone					() override;
	BOOL	net_Spawn						(CSE_Abstract* DC) override;
	void	SwitchZoneState					(EZoneState new_state) override;
	void	Load							(LPCSTR section) override;
	virtual void	UpdateBlowout					()						;
protected:
private:
};
