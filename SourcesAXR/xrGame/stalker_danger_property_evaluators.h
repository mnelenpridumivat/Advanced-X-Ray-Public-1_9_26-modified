////////////////////////////////////////////////////////////////////////////
//	Module 		: stalker_danger_property_evaluators.h
//	Created 	: 31.05.2005
//  Modified 	: 31.05.2005
//	Author		: Dmitriy Iassenev
//	Description : Stalker danger property evaluators classes
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "wrapper_abstract.h"
#include "property_evaluator_const.h"
#include "property_evaluator_member.h"
#include "danger_object.h"

class CAI_Stalker;

typedef CWrapperAbstract2<CAI_Stalker,CPropertyEvaluator>		CStalkerPropertyEvaluator;
typedef CWrapperAbstract2<CAI_Stalker,CPropertyEvaluatorConst>	CStalkerPropertyEvaluatorConst;
typedef CWrapperAbstract2<CAI_Stalker,CPropertyEvaluatorMember>	CStalkerPropertyEvaluatorMember;

//////////////////////////////////////////////////////////////////////////
// CStalkerPropertyEvaluatorDangers
//////////////////////////////////////////////////////////////////////////

class CStalkerPropertyEvaluatorDangers : public CStalkerPropertyEvaluator {
protected:
	typedef CStalkerPropertyEvaluator inherited;

public:
						CStalkerPropertyEvaluatorDangers	(CAI_Stalker *object = nullptr, LPCSTR evaluator_name = "");
	_value_type	evaluate							() override;
};

//////////////////////////////////////////////////////////////////////////
// CStalkerPropertyEvaluatorDangerUnknown
//////////////////////////////////////////////////////////////////////////

class CStalkerPropertyEvaluatorDangerUnknown : public CStalkerPropertyEvaluator {
protected:
	typedef CStalkerPropertyEvaluator inherited;

public:
						CStalkerPropertyEvaluatorDangerUnknown	(CAI_Stalker *object = nullptr, LPCSTR evaluator_name = "");
	_value_type	evaluate								() override;
};

//////////////////////////////////////////////////////////////////////////
// CStalkerPropertyEvaluatorDangerInDirection
//////////////////////////////////////////////////////////////////////////

class CStalkerPropertyEvaluatorDangerInDirection : public CStalkerPropertyEvaluator {
protected:
	typedef CStalkerPropertyEvaluator inherited;

public:
						CStalkerPropertyEvaluatorDangerInDirection	(CAI_Stalker *object = nullptr, LPCSTR evaluator_name = "");
	_value_type	evaluate									() override;
};

//////////////////////////////////////////////////////////////////////////
// CStalkerPropertyEvaluatorDangerWithGrenade
//////////////////////////////////////////////////////////////////////////

class CStalkerPropertyEvaluatorDangerWithGrenade : public CStalkerPropertyEvaluator {
protected:
	typedef CStalkerPropertyEvaluator inherited;

public:
						CStalkerPropertyEvaluatorDangerWithGrenade	(CAI_Stalker *object = nullptr, LPCSTR evaluator_name = "");
	_value_type	evaluate									() override;
};

//////////////////////////////////////////////////////////////////////////
// CStalkerPropertyEvaluatorDangerBySound
//////////////////////////////////////////////////////////////////////////

class CStalkerPropertyEvaluatorDangerBySound : public CStalkerPropertyEvaluator {
protected:
	typedef CStalkerPropertyEvaluator inherited;

public:
						CStalkerPropertyEvaluatorDangerBySound	(CAI_Stalker *object = nullptr, LPCSTR evaluator_name = "");
	_value_type	evaluate								() override;
};

//////////////////////////////////////////////////////////////////////////
// CStalkerPropertyEvaluatorDangerUnknownCoverActual
//////////////////////////////////////////////////////////////////////////

class CStalkerPropertyEvaluatorDangerUnknownCoverActual : public CStalkerPropertyEvaluator {
protected:
	typedef CStalkerPropertyEvaluator inherited;

private:
	Fvector				m_cover_selection_position;

public:
						CStalkerPropertyEvaluatorDangerUnknownCoverActual	(CAI_Stalker *object = nullptr, LPCSTR evaluator_name = "");
	_value_type	evaluate											() override;
};

//////////////////////////////////////////////////////////////////////////
// CStalkerPropertyEvaluatorDangerGrenadeExploded
//////////////////////////////////////////////////////////////////////////

class CStalkerPropertyEvaluatorDangerGrenadeExploded : public CStalkerPropertyEvaluator {
protected:
	typedef CStalkerPropertyEvaluator inherited;

public:
						CStalkerPropertyEvaluatorDangerGrenadeExploded	(CAI_Stalker *object = nullptr, LPCSTR evaluator_name = "");
	_value_type	evaluate										() override;
};

//////////////////////////////////////////////////////////////////////////
// CStalkerPropertyEvaluatorGrenadeToExplode
//////////////////////////////////////////////////////////////////////////

class CStalkerPropertyEvaluatorGrenadeToExplode : public CStalkerPropertyEvaluator {
protected:
	typedef CStalkerPropertyEvaluator inherited;

public:
						CStalkerPropertyEvaluatorGrenadeToExplode	(CAI_Stalker *object = nullptr, LPCSTR evaluator_name = "");
	_value_type	evaluate									() override;
};

//////////////////////////////////////////////////////////////////////////
// CStalkerPropertyEvaluatorEnemyWounded
//////////////////////////////////////////////////////////////////////////

class CStalkerPropertyEvaluatorEnemyWounded : public CStalkerPropertyEvaluator {
protected:
	typedef CStalkerPropertyEvaluator inherited;

public:
						CStalkerPropertyEvaluatorEnemyWounded	(CAI_Stalker *object = nullptr, LPCSTR evaluator_name = "");
	_value_type	evaluate								() override;
};