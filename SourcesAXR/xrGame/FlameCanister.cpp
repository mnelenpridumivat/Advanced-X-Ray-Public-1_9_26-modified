#include "stdafx.h"
#include "FlameCanister.h"

CFlameCanister::CFlameCanister(void)
{
}

CFlameCanister::~CFlameCanister(void)
{
}

#if 0
void CFlameCanister::Load(LPCSTR section)
{
	inherited::Load(section);

	cartridge_param.kDist = pSettings->r_float(section, "k_dist");
	cartridge_param.kDisp = pSettings->r_float(section, "k_disp");
	cartridge_param.kHit = pSettings->r_float(section, "k_hit");
	//.	cartridge_param.kCritical	= pSettings->r_float(section, "k_hit_critical");
	cartridge_param.kImpulse = pSettings->r_float(section, "k_impulse");
	//m_kPierce				= pSettings->r_float(section, "k_pierce");
	cartridge_param.kAP = pSettings->r_float(section, "k_ap");
	cartridge_param.u8ColorID = READ_IF_EXISTS(pSettings, r_u8, section, "tracer_color_ID", 0);

	if (pSettings->line_exist(section, "k_air_resistance"))
		cartridge_param.kAirRes = pSettings->r_float(section, "k_air_resistance");
	else
		cartridge_param.kAirRes = pSettings->r_float(BULLET_MANAGER_SECTION, "air_resistance_k");
	m_tracer = !!pSettings->r_bool(section, "tracer");
	cartridge_param.buckShot = pSettings->r_s32(section, "buck_shot");
	cartridge_param.impair = pSettings->r_float(section, "impair");
	cartridge_param.fWallmarkSize = pSettings->r_float(section, "wm_size");
	R_ASSERT(cartridge_param.fWallmarkSize > 0);
}

BOOL CFlameCanister::net_Spawn(CSE_Abstract* DC)
{
	BOOL bResult = inherited::net_Spawn(DC);
	/*CSE_Abstract* e = (CSE_Abstract*)(DC);
	CSE_ALifeInventoryItem* l_pW = smart_cast<CSE_ALifeInventoryItem*>(e);
	m_boxCurr = l_pW->a_elapsed;

	if (m_boxCurr > m_boxSize)
		l_pW->a_elapsed = m_boxCurr = m_boxSize;*/

	return					bResult;
}

void CFlameCanister::net_Destroy()
{
	inherited::net_Destroy();
}

void CFlameCanister::OnH_B_Chield()
{
	inherited::OnH_B_Chield();
}

void CFlameCanister::OnH_B_Independent(bool just_before_destroy)
{
	if (!Useful()) {

		if (Local()) {
			DestroyObject();
		}
		m_ready_to_destroy = true;
	}
	inherited::OnH_B_Independent(just_before_destroy);
}


bool CFlameCanister::Useful() const
{
	// ≈сли IItem еще не полностью использованый, вернуть true
	return !!GetCondition();
}

bool CFlameCanister::Get(CCartridge& cartridge)
{
	if (!m_boxCurr) return false;
	cartridge.m_ammoSect = cNameSect();

	cartridge.param_s = cartridge_param;

	cartridge.m_flags.set(CCartridge::cfTracer, m_tracer);
	cartridge.bullet_material_idx = GMLib.GetMaterialIdx(WEAPON_MATERIAL_NAME);
	cartridge.m_InvShortName = NameShort();
	--m_boxCurr;
	if (m_pInventory)m_pInventory->InvalidateState();
	return true;
}

void CFlameCanister::renderable_Render()
{
	if (!m_ready_to_destroy)
		inherited::renderable_Render();
}

void CFlameCanister::UpdateCL()
{
	VERIFY2(_valid(renderable.xform), *cName());
	inherited::UpdateCL();
	VERIFY2(_valid(renderable.xform), *cName());

	if (!IsGameTypeSingle())
		make_Interpolation();

	VERIFY2(_valid(renderable.xform), *cName());

}

void CFlameCanister::net_Export(NET_Packet& P)
{
	inherited::net_Export(P);
}

void CFlameCanister::net_Import(NET_Packet& P)
{
	inherited::net_Import(P);
}

CInventoryItem* CFlameCanister::can_make_killing(const CInventory* inventory) const
{
	VERIFY(inventory);

	TIItemContainer::const_iterator	I = inventory->m_all.begin();
	TIItemContainer::const_iterator	E = inventory->m_all.end();
	for (; I != E; ++I) {
		CWeapon* weapon = smart_cast<CWeapon*>(*I);
		if (!weapon)
			continue;
		xr_vector<shared_str>::const_iterator	i = std::find(weapon->m_ammoTypes.begin(), weapon->m_ammoTypes.end(), cNameSect());
		if (i != weapon->m_ammoTypes.end())
			return			(weapon);
	}

	return					(0);
}

float CFlameCanister::Weight() const
{
	float res = inherited::Weight();
	res *= (0.05f + 0.95f * GetCondition());
	return res;
}

u32 CFlameCanister::Cost() const
{
	u32 res = inherited::Cost();

	res = iFloor(res * GetCondition() + 0.5f);

	return res;
}
#endif
