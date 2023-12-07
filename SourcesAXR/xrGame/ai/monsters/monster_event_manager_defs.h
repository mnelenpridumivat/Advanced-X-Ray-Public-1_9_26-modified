#pragma once

enum EEventType {
	eventAnimationStart = static_cast<u32>(0),
	eventAnimationEnd,
	eventSoundStart,
	eventSoundEnd,
	eventParticlesStart,
	eventParticlesEnd,
	eventStep,
	eventTAChange,
	eventVelocityBounce,
};

class IEventData {};

#define DEFINE_DELEGATE	void __stdcall
