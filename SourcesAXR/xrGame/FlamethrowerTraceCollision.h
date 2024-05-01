#pragma once

#include "../xrEngine/feel_touch.h"
#include "../xrCore/_types.h"

class CParticlesObject;
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
	bool m_launched = false;
	float m_current_time = 0.0f;
	float m_time_on_collide = 0.0f;
	//Fmatrix XFORM;
	//Fmatrix invXFORM;
	Fvector m_LastUpdatedPos;
	Fvector m_position;
	Fvector m_direction;
	float RadiusCurrent;
	float RadiusOnCollide;

	shared_str m_sFlameParticles;
	shared_str m_sEarthFlameParticles;

	float m_last_update_time;

	float m_LifeTime = 0.0f;
	float m_LifeTimeCollidedMax = 0.0f;
	float m_FlameFadeTime = 0.0f;
	float m_RadiusMin = 0.0f;
	float m_RadiusMax = 0.0f;
	float m_RadiusMaxTime = 0.0f;
	float m_RadiusCollided = 0.0f;
	float m_RadiusCollidedInterpTime = 0.0f;
	float m_RadiusCollisionCoeff = 0.0f;
	float m_Velocity = 0.0f;
	float m_GravityVelocity = 0.0f;
	float m_GravityAcceleration = 0.0f;

	CParticlesObject* m_particles = nullptr;

	struct FlamethrowerTraceData {
		CFlamethrowerTraceCollision* TracedObj = nullptr;
		float HitDist;
	};

	static BOOL	hit_callback(collide::rq_result& result, LPVOID params);
	static BOOL test_callback(const collide::ray_defs& rd, CObject* object, LPVOID params);

	void UpdateParticles();

public:

#ifdef DEBUG
	CFlamethrowerTraceCollision* Next = nullptr;
	CFlamethrowerTraceCollision* Prev = nullptr;
#endif

	CFlamethrowerTraceCollision(CFlamethrowerTraceManager* flamethrower);
	~CFlamethrowerTraceCollision();

	void Load(LPCSTR section);

	inline CFlamethrowerTraceManager* GetParent() const { return m_flamethrower; };
	inline CFlamethrower* GetParentWeapon() const;

	inline bool IsActive() { return m_IsActive; }
	inline bool IsCollided() { return m_IsCollided; }
	bool IsReadyToUpdateCollisions();
	inline Fvector GetCurrentPosition() { return m_position; }
	float GetCurrentRadius();
	inline Fvector GetPosition() { return m_position; }
	inline Fvector GetDirection() { return m_direction; }

	void SetTransform(const Fvector& StartPos, const Fvector& StartDir);

	void	feel_touch_new(CObject* O) override;
	void	feel_touch_delete(CObject* O) override;
	BOOL	feel_touch_contact(CObject* O) override;

	void Activate();
	void Deactivate();
	void Update(float DeltaTime);

};

class CFlamethrowerTraceManager :
	public Feel::Touch
{

	CFlamethrower* m_flamethrower;
	shared_str CollisionSection;

	DEFINE_VECTOR(CCustomMonster*, FOverlappedObjects, FOverlappedObjectsIt);
	DEFINE_VECTOR(CFlamethrowerTraceCollision*, FCollisions, FCollisionsIt);

	DEFINE_DEQUE(CFlamethrowerTraceCollision*, FCollisionsDeque, FCollisionsDequeIt);

	FOverlappedObjects Overlapped;
	FCollisionsDeque CollisionsPool;
	//FCollisionsDeque CollisionsDeque;

	float LifeTime;
	float LifeTimeGroundAddition;

public:

#ifdef DEBUG
	CFlamethrowerTraceCollision* LastLaunched = nullptr;
#endif

	CFlamethrowerTraceManager(CFlamethrower* flamethrower);
	~CFlamethrowerTraceManager();

	void	feel_touch_new(CObject* O) override;
	void	feel_touch_delete(CObject* O) override;
	BOOL	feel_touch_contact(CObject* O) override;

	void Load(LPCSTR section);

	void UpdateOverlaps(float DeltaTime);

	void RegisterOverlapped(CCustomMonster* enemy);
	void UnregisterOverlapped(CCustomMonster* enemy);
	const FOverlappedObjects& GetOverlapped();

	inline CFlamethrower* GetParent() const { return m_flamethrower; };

	void LaunchTrace(const Fvector& StartPos, const Fvector& StartDir);



};
