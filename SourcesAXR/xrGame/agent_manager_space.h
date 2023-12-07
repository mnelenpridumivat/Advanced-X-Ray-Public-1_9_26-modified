////////////////////////////////////////////////////////////////////////////
//	Module 		: agent_manager_space.h
//	Created 	: 25.05.2004
//  Modified 	: 25.05.2004
//	Author		: Dmitriy Iassenev
//	Description : Agent manager space
////////////////////////////////////////////////////////////////////////////

#pragma once

namespace AgentManager {
	enum EProperties {
		ePropertyOrders			= static_cast<u32>(0),
		ePropertyItem,
		ePropertyEnemy,
		ePropertyDanger,

		ePropertyScript,
		ePropertyDummy			= static_cast<u32>(-1),
	};

	enum EOperators {
		eOperatorNoOrders		= static_cast<u32>(0),
		eOperatorGatherItem,
		eOperatorKillEnemy,
		eOperatorReactOnDanger,

		eOperatorScript,
		eOperatorDummy			= static_cast<u32>(-1),
	};
};