////////////////////////////////////////////////////////////////////////////
//	Module 		: ef_primary.h
//	Created 	: 13.06.2003
//  Modified 	: 13.06.2003
//	Author		: Dmitriy Iassenev
//	Description : Primary function classes
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ef_base.h"

class CDistanceFunction : public CBaseFunction {
public:
	typedef CBaseFunction inherited;

	CDistanceFunction(CEF_Storage *storage) : CBaseFunction(storage)
	{
		m_fMinResultValue = 3.0;
		m_fMaxResultValue = 20.0;
		xr_strcat(m_caName,"Distance");
		OUT_MESSAGE("* Evaluation function \"%s\" is successfully initalized",m_caName);
	};

	~CDistanceFunction() override {}

	float ffGetValue() override;

	u32	dwfGetDiscreteValue(u32 dwDiscretizationValue) override
	{
		float fTemp = ffGetValue();
		if (fTemp <= m_fMinResultValue)
			return(0);
		else
			if (fTemp >= m_fMaxResultValue)
				return(dwDiscretizationValue - 1);
			else
				return(1);
	}
};

class CPersonalHealthFunction : public CBaseFunction {
public:
	typedef CBaseFunction inherited;

	CPersonalHealthFunction(CEF_Storage *storage) : CBaseFunction(storage)
	{
		m_fMinResultValue = 0.0;
		m_fMaxResultValue = 100.0;
		xr_strcat(m_caName,"PersonalHealth");
		OUT_MESSAGE("* Evaluation function \"%s\" is successfully initalized",m_caName);
	};

	float ffGetValue() override;
};

class CPersonalMoraleFunction : public CBaseFunction {
public:
	typedef CBaseFunction inherited;

	CPersonalMoraleFunction(CEF_Storage *storage) : CBaseFunction(storage)
	{
		m_fMinResultValue = 0.0;
		m_fMaxResultValue = 100.0;
		xr_strcat(m_caName,"PersonalMorale");
		OUT_MESSAGE("* Evaluation function \"%s\" is successfully initalized",m_caName);
	};

	~CPersonalMoraleFunction() override {}

	float ffGetValue() override;
};

class CPersonalCreatureTypeFunction : public CBaseFunction {
public:
	typedef CBaseFunction inherited;

	CPersonalCreatureTypeFunction(CEF_Storage *storage) : CBaseFunction(storage)
	{
		m_fMinResultValue = 1.0;
		m_fMaxResultValue = 21.0;
		xr_strcat(m_caName,"PersonalCreatureType");
		OUT_MESSAGE("* Evaluation function \"%s\" is successfully initalized",m_caName);
	};

	~CPersonalCreatureTypeFunction() override {}

	float ffGetValue() override;
};

class CPersonalWeaponTypeFunction : public CBaseFunction {
public:
	typedef CBaseFunction inherited;

	CPersonalWeaponTypeFunction(CEF_Storage *storage) : CBaseFunction(storage)
	{
		m_fMinResultValue = 1.0;
		m_fMaxResultValue = 12.0;
		xr_strcat(m_caName,"PersonalWeaponType");
		OUT_MESSAGE("* Evaluation function \"%s\" is successfully initalized",m_caName);
	};

	~CPersonalWeaponTypeFunction() override {}

			u32	  dwfGetWeaponType	();
			float ffGetTheBestWeapon();
	float ffGetValue		() override;
};

class CPersonalAccuracyFunction : public CBaseFunction {
public:
	typedef CBaseFunction inherited;

	CPersonalAccuracyFunction(CEF_Storage *storage) : CBaseFunction(storage)
	{
		m_fMinResultValue =   0.0;
		m_fMaxResultValue = 100.0;
		xr_strcat(m_caName,"PersonalAccuracy");
		OUT_MESSAGE("* Evaluation function \"%s\" is successfully initalized",m_caName);
	};

	~CPersonalAccuracyFunction() override {}

	float ffGetValue() override;
};

class CPersonalIntelligenceFunction : public CBaseFunction {
public:
	typedef CBaseFunction inherited;

	CPersonalIntelligenceFunction(CEF_Storage *storage) : CBaseFunction(storage)
	{
		m_fMinResultValue =   0.0;
		m_fMaxResultValue = 100.0;
		xr_strcat(m_caName,"PersonalIntelligence");
		OUT_MESSAGE("* Evaluation function \"%s\" is successfully initalized",m_caName);
	};

	~CPersonalIntelligenceFunction() override {}

	float ffGetValue() override;
};

class CPersonalRelationFunction : public CBaseFunction {
public:
	typedef CBaseFunction inherited;

	CPersonalRelationFunction(CEF_Storage *storage) : CBaseFunction(storage)
	{
		m_fMinResultValue =   0.0;
		m_fMaxResultValue = 100.0;
		xr_strcat(m_caName,"PersonalRelation");
		OUT_MESSAGE("* Evaluation function \"%s\" is successfully initalized",m_caName);
	};

	~CPersonalRelationFunction() override {}

	float ffGetValue() override;
};

class CPersonalGreedFunction : public CBaseFunction {
public:
	typedef CBaseFunction inherited;

	CPersonalGreedFunction(CEF_Storage *storage) : CBaseFunction(storage)
	{
		m_fMinResultValue =   0.0;
		m_fMaxResultValue = 100.0;
		xr_strcat(m_caName,"PersonalGreed");
		OUT_MESSAGE("* Evaluation function \"%s\" is successfully initalized",m_caName);
	};

	~CPersonalGreedFunction() override {}

	float ffGetValue() override;
};

class CPersonalAggressivenessFunction : public CBaseFunction {
public:
	typedef CBaseFunction inherited;

	CPersonalAggressivenessFunction(CEF_Storage *storage) : CBaseFunction(storage)
	{
		m_fMinResultValue =   0.0;
		m_fMaxResultValue = 100.0;
		xr_strcat(m_caName,"PersonalAggressiveness");
		OUT_MESSAGE("* Evaluation function \"%s\" is successfully initalized",m_caName);
	};

	~CPersonalAggressivenessFunction() override {}

	float ffGetValue() override;
};

class CEnemyMoraleFunction : public CBaseFunction {
public:
	typedef CBaseFunction inherited;

	CEnemyMoraleFunction(CEF_Storage *storage) : CBaseFunction(storage)
	{
		m_fMinResultValue = 0.0;
		m_fMaxResultValue = 100.0;
		xr_strcat(m_caName,"EnemyMorale");
		OUT_MESSAGE("* Evaluation function \"%s\" is successfully initalized",m_caName);
	};

	~CEnemyMoraleFunction() override {}

	float ffGetValue() override;
};

class CEnemyEquipmentCostFunction : public CBaseFunction {
public:
	typedef CBaseFunction inherited;

	CEnemyEquipmentCostFunction(CEF_Storage *storage) : CBaseFunction(storage)
	{
		m_fMinResultValue = 0.0;
		m_fMaxResultValue = 12.0;
		xr_strcat(m_caName,"EnemyEquipmentCost");
		OUT_MESSAGE("* Evaluation function \"%s\" is successfully initalized",m_caName);
	};

	~CEnemyEquipmentCostFunction() override {}

	float ffGetValue() override;
};

class CEnemyRukzakWeightFunction : public CBaseFunction {
public:
	typedef CBaseFunction inherited;

	CEnemyRukzakWeightFunction(CEF_Storage *storage) : CBaseFunction(storage)
	{
		m_fMinResultValue = 1.0;
		m_fMaxResultValue = 12.0;
		xr_strcat(m_caName,"EnemyRukzakWeight");
		OUT_MESSAGE("* Evaluation function \"%s\" is successfully initalized",m_caName);
	};

	~CEnemyRukzakWeightFunction() override {}

	float ffGetValue() override;
};

class CEnemyAnomalityFunction : public CBaseFunction {
public:
	typedef CBaseFunction inherited;

	CEnemyAnomalityFunction(CEF_Storage *storage) : CBaseFunction(storage)
	{
		m_fMinResultValue = 1.0;
		m_fMaxResultValue = 12.0;
		xr_strcat(m_caName,"EnemyAnomality");
		OUT_MESSAGE("* Evaluation function \"%s\" is successfully initalized",m_caName);
	};

	~CEnemyAnomalityFunction() override {}

	float ffGetValue() override;
};

class CGraphPointType0 : public CBaseFunction {
public:
	typedef CBaseFunction inherited;

	CGraphPointType0(CEF_Storage *storage) : CBaseFunction(storage)
	{
		m_fMinResultValue = 0.0;
		m_fMaxResultValue = 100.0;
		xr_strcat(m_caName,"GraphPointType0");
		OUT_MESSAGE("* Evaluation function \"%s\" is successfully initalized",m_caName);
	};

	~CGraphPointType0() override {}

	float ffGetValue() override;
};

class CPersonalEyeRange : public CBaseFunction {
public:
	typedef CBaseFunction inherited;

	CPersonalEyeRange(CEF_Storage *storage) : CBaseFunction(storage)
	{
		m_fMinResultValue = 0.0;
		m_fMaxResultValue = 100.0;
		xr_strcat(m_caName,"PersonalEyeRange");
		OUT_MESSAGE("* Evaluation function \"%s\" is successfully initalized",m_caName);
	};

	~CPersonalEyeRange() override {}

	float ffGetValue() override;
};

class CPersonalMaxHealth : public CBaseFunction {
public:
	typedef CBaseFunction inherited;

	CPersonalMaxHealth(CEF_Storage *storage) : CBaseFunction(storage)
	{
		m_fMinResultValue = 0.0;
		m_fMaxResultValue = 1000.0;
		xr_strcat(m_caName,"PersonalMaxHealth");
		OUT_MESSAGE("* Evaluation function \"%s\" is successfully initalized",m_caName);
	};

	~CPersonalMaxHealth() override {}

	float	ffGetValue() override;
	u32		dwfGetDiscreteValue(u32 dwDiscretizationValue = 1) override;
};

class CEquipmentType : public CBaseFunction {
public:
	typedef CBaseFunction inherited;

	CEquipmentType(CEF_Storage *storage) : CBaseFunction(storage)
	{
		m_fMinResultValue = 1.0;
		m_fMaxResultValue = 5.0;
		xr_strcat(m_caName,"EquipmentType");
		OUT_MESSAGE("* Evaluation function \"%s\" is successfully initalized",m_caName);
	};

	~CEquipmentType() override {}

	float	ffGetValue() override;
};

class CItemDeterioration : public CBaseFunction {
public:
	typedef CBaseFunction inherited;

	CItemDeterioration(CEF_Storage *storage) : CBaseFunction(storage)
	{
		m_fMinResultValue = 0.0;
		m_fMaxResultValue = 100.0;
		xr_strcat(m_caName,"ItemDeterioration");
		OUT_MESSAGE("* Evaluation function \"%s\" is successfully initalized",m_caName);
	};

	~CItemDeterioration() override {}

	float	ffGetValue() override;
};

class CEquipmentPreference : public CBaseFunction {
public:
	typedef CBaseFunction inherited;

	CEquipmentPreference(CEF_Storage *storage) : CBaseFunction(storage)
	{
		m_fMinResultValue = 1.0;
		m_fMaxResultValue = 3.0;
		xr_strcat(m_caName,"EquipmentPreference");
		OUT_MESSAGE("* Evaluation function \"%s\" is successfully initalized",m_caName);
	};

	~CEquipmentPreference() override {}

	float	ffGetValue() override;
};

class CMainWeaponType : public CBaseFunction {
public:
	typedef CBaseFunction inherited;

	CMainWeaponType(CEF_Storage *storage) : CBaseFunction(storage)
	{
		m_fMinResultValue = 1.0;
		m_fMaxResultValue = 4.0;
		xr_strcat(m_caName,"MainWeaponType");
		OUT_MESSAGE("* Evaluation function \"%s\" is successfully initalized",m_caName);
	};

	~CMainWeaponType() override {}

	float	ffGetValue() override;
};

class CMainWeaponPreference : public CBaseFunction {
public:
	typedef CBaseFunction inherited;

	CMainWeaponPreference(CEF_Storage *storage) : CBaseFunction(storage)
	{
		m_fMinResultValue = 1.0;
		m_fMaxResultValue = 3.0;
		xr_strcat(m_caName,"MainWeaponPreference");
		OUT_MESSAGE("* Evaluation function \"%s\" is successfully initalized",m_caName);
	};

	~CMainWeaponPreference() override {}

	float	ffGetValue() override;
};

class CItemValue : public CBaseFunction {
public:
	typedef CBaseFunction inherited;

	CItemValue(CEF_Storage *storage) : CBaseFunction(storage)
	{
		m_fMinResultValue = 100.0;
		m_fMaxResultValue = 2000.0;
		xr_strcat(m_caName,"ItemValue");
		OUT_MESSAGE("* Evaluation function \"%s\" is successfully initalized",m_caName);
	};

	~CItemValue() override {}

	float	ffGetValue() override;
};

class CWeaponAmmoCount : public CBaseFunction {
public:
	typedef CBaseFunction inherited;

	CWeaponAmmoCount(CEF_Storage *storage) : CBaseFunction(storage)
	{
		m_fMinResultValue = 0.0;
		m_fMaxResultValue = 10.0;
		xr_strcat(m_caName,"WeaponAmmoCount");
		OUT_MESSAGE("* Evaluation function \"%s\" is successfully initalized",m_caName);
	};

	~CWeaponAmmoCount() override {}

	float	ffGetValue() override;
	u32		dwfGetDiscreteValue(u32 dwDiscretizationValue = 1) override;
};

class CEnemyAnomalyType : public CBaseFunction {
public:
	typedef CBaseFunction inherited;

	CEnemyAnomalyType(CEF_Storage *storage) : CBaseFunction(storage)
	{
		m_fMinResultValue = 0.0;
		m_fMaxResultValue = 7.0;
		xr_strcat(m_caName,"EnemyAnomalyType");
		OUT_MESSAGE("* Evaluation function \"%s\" is successfully initalized",m_caName);
	};

	~CEnemyAnomalyType() override {}

	float	ffGetValue() override;
};

class CDetectorType : public CBaseFunction {
public:
	typedef CBaseFunction inherited;

	CDetectorType(CEF_Storage *storage) : CBaseFunction(storage)
	{
		m_fMinResultValue = 0.0;
		m_fMaxResultValue = 2.0;
		xr_strcat(m_caName,"DetectorType");
		OUT_MESSAGE("* Evaluation function \"%s\" is successfully initalized",m_caName);
	};

	~CDetectorType() override {}

	float	ffGetValue() override;
};

class CEnemyDistanceToGraphPoint : public CBaseFunction {
public:
	typedef CBaseFunction inherited;

	CEnemyDistanceToGraphPoint(CEF_Storage *storage) : CBaseFunction(storage)
	{
		m_fMinResultValue = 0.0;
		m_fMaxResultValue = 4.0;
		xr_strcat(m_caName,"EnemyDistanceToGraphPoint");
		OUT_MESSAGE("* Evaluation function \"%s\" is successfully initalized",m_caName);
	};

	~CEnemyDistanceToGraphPoint() override {}

	float	ffGetValue() override;
};
