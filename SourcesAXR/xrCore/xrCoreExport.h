#pragma once

// Our headers
#ifdef XRCORE_EXPORTS
#	define XRCORE_API __declspec(dllexport)
#else
#	define XRCORE_API __declspec(dllimport)
#endif