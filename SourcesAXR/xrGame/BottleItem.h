///////////////////////////////////////////////////////////////
// BottleItem.h
// BottleItem - бутылка с напитком, которую можно разбить
///////////////////////////////////////////////////////////////


#pragma once

#include "fooditem.h"


class CBottleItem: public CFoodItem
{
private:
    typedef	CFoodItem inherited;
public:
				CBottleItem			();
    ~CBottleItem		() override;


    void Load				(LPCSTR section) override;
	

	void	OnEvent					(NET_Packet& P, u16 type) override;


    void	Hit				(SHit* pHDS) override;
	

			void					BreakToPieces		();
protected:
	//партиклы разбивания бутылки
	shared_str m_sBreakParticles;
	ref_sound sndBreaking;
};