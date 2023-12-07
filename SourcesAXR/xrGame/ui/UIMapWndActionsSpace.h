#pragma once


namespace UIMapWndActionsSpace {

	enum EWorldProperties {
		ePropTargetMapShown,
		ePropMapMinimized,
		ePropMapResized,
		ePropMapIdle,
		ePropMapCentered,
		ePropDummy					= static_cast<u16>(-1),
	};

	enum EWorldOperators {
		eOperatorMapResize,
		eOperatorMapMinimize,
		eOperatorMapIdle,
		eOperatorMapCenter,
		eWorldOperatorDummy			= static_cast<u16>(-1),
	};
};
