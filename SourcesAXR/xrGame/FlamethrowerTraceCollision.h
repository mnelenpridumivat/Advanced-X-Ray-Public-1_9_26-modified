#pragma once

#include "../xrEngine/feel_touch.h"
#include "../xrCore/_types.h"

class CFlamethrower;
class CFlamethrowerTraceManager;
class ENGINE_API CObject;
class CCustomMonster;

class CFlamethrowerTraceCollision :
	public Feel::Touch
{

	CFlamethrowerTraceManager* m_flamethrower;
	bool m_IsActive = false;
	bool m_IsCollided = false;
	float m_current_time = 0.0f;
	Fvector m_position;
	Fvector m_direction;

	float m_LifeTime = 0.0f;
	float m_RadiusMin = 0.0f;
	float m_RadiusMax = 0.0f;
	float m_RadiusMaxTime = 0.0f;
	float m_RadiusCollided = 0.0f;
	float m_Velocity = 0.0f;
	float m_GravityVelocity = 0.0f;

	struct FlamethrowerTraceData {
		CFlamethrowerTraceCollision* TracedObj = nullptr;
	};

	static BOOL	hit_callback(collide::rq_result& result, LPVOID params);
	static BOOL test_callback(const collide::ray_defs& rd, CObject* object, LPVOID params);

public:

	CFlamethrowerTraceCollision(CFlamethrowerTraceManager* flamethrower);
	~CFlamethrowerTraceCollision();

	inline CFlamethrowerTraceManager* GetParent() const { return m_flamethrower; };
	inline CFlamethrower* GetParentWeapon() const;

	inline bool IsActive() { return m_IsActive; }
	inline bool IsCollided() { return m_IsCollided; }
	inline Fvector GetCurrentPosition() { return m_position; }
	float GetCurrentRadius();
	inline Fvector GetPosition() { return m_position; }
	inline Fvector GetDirection() { return m_direction; }

	void	feel_touch_new(CObject* O) override;
	void	feel_touch_delete(CObject* O) override;
	BOOL	feel_touch_contact(CObject* O) override;

	void Activate();
	void Deactivate();
	void Update(float DeltaTime);

};

class CFlamethrowerTraceManager
{

	CFlamethrower* m_flamethrower;

	DEFINE_VECTOR(CCustomMonster*, FOverlappedObjects, FOverlappedObjectsIt);
	DEFINE_VECTOR(CFlamethrowerTraceCollision*, FCollisions, FCollisionsIt);

	FOverlappedObjects Overlapped;
	FCollisions CollisionsPool;

	float LifeTime;
	float LifeTimeGroundAddition;

public:

	void UpdateOverlaps(float DeltaTime);

	void RegisterOverlapped(CCustomMonster* enemy);
	void UnregisterOverlapped(CCustomMonster* enemy);
	const FOverlappedObjects& GetOverlapped();

	inline CFlamethrower* GetParent() const { return m_flamethrower; };



};
