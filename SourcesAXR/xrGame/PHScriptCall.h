#pragma once
#include "PHReqComparer.h"
#include "phcommander.h"
#include "script_engine.h"
#include "script_space_forward.h"
#include "script_callback_ex.h"
//template<>
//IC bool compare_safe(const functor<>& f1,const functor<>& f2)
//{
//	f1.typ
//}

class CPHScriptCondition:
	public CPHCondition,
	public CPHReqComparerV
{
	luabind::functor<bool>			*m_lua_function;

							CPHScriptCondition				(const CPHScriptCondition &func);

public:
							CPHScriptCondition				(const luabind::functor<bool> &func)	;
	~CPHScriptCondition				() override;
	bool 			is_true							() override;
	bool 			obsolete						()								const override;
	bool			compare							(const	CPHReqComparerV* v)		const override {return v->compare(this);}
	bool			compare							(const	CPHScriptCondition*v)	const override {return v->m_lua_function==m_lua_function;}
	///virtual bool			is_equal						(CPHReqBase* v)							;
	//virtual bool			is_relative						(CPHReqBase* v)							;

};

class CPHScriptAction :
	public CPHAction,
	public CPHReqComparerV
{
	bool	b_obsolete							   ;
	luabind::functor<void>			*m_lua_function;
public:
							CPHScriptAction					(const luabind::functor<void> &func)	;
							CPHScriptAction					(const CPHScriptAction &action)			;
	~CPHScriptAction				() override;
	void 			run								() override;
	bool 			obsolete						()								const override;
	bool			compare							(const	CPHReqComparerV* v)		const override {return v->compare(this);}
	bool			compare							(const	CPHScriptAction* v)		const override {return *m_lua_function==*(v->m_lua_function);}
};


class CPHScriptObjectCondition:
	public CPHCondition,
	public CPHReqComparerV
{
	luabind::object					*m_lua_object;
	shared_str						m_method_name;
public:
							CPHScriptObjectCondition		(const luabind::object &lua_object, LPCSTR method)	;
							CPHScriptObjectCondition		(const CPHScriptObjectCondition &object)			;
	~CPHScriptObjectCondition		() override;
	bool 			is_true							() override;
	bool 			obsolete						()										const override;
	virtual bool			compare							(const	luabind::object* v)				const		{return *m_lua_object==*v;}
	bool			compare							(const	CPHReqComparerV* v)				const override {return v->compare(this);}
	bool			compare							(const	CPHScriptObjectCondition* v)	const override;
};

class CPHScriptObjectAction :
	public CPHAction,
	public CPHReqComparerV
{
	bool	b_obsolete							   ;
	luabind::object					*m_lua_object;
	shared_str						m_method_name;
public:
							CPHScriptObjectAction			(const luabind::object &lua_object, LPCSTR method)	;
							CPHScriptObjectAction			(const CPHScriptObjectAction &object)				;
	~CPHScriptObjectAction			() override;
	void 			run								() override;
	bool 			obsolete						()										const override;
	virtual bool			compare							(const	luabind::object* v)				const		{return *m_lua_object==*v;}
	bool			compare							(const	CPHReqComparerV* v)				const override {return v->compare(this);}
	bool			compare							(const	CPHScriptObjectAction* v)		const override;
};
//////////////////////////////////////////////////////////////////////////////////////////

class CPHScriptObjectConditionN:
	public CPHCondition,
	public CPHReqComparerV
{
	CScriptCallbackEx<bool>			m_callback;
public:
	CPHScriptObjectConditionN			( const luabind::object &object,const luabind::functor<bool> &functor)	;
	~CPHScriptObjectConditionN		() override;
	bool 			is_true							() override;
	bool 			obsolete						()										const override;
	virtual bool			compare							(const	luabind::object* v)				const		{return m_callback==(*v);}
	bool			compare							(const	CPHReqComparerV* v)				const override {return v->compare(this);}
	bool			compare							(const	CPHScriptObjectConditionN* v)	const override {return m_callback==v->m_callback;}
};

class CPHScriptObjectActionN :
	public CPHAction,
	public CPHReqComparerV
{
	bool	b_obsolete							   ;
	CScriptCallbackEx<void>			m_callback;
public:
	CPHScriptObjectActionN			( const luabind::object &object,const luabind::functor<void> &functor);
	~CPHScriptObjectActionN			() override;
	void 			run								() override;
	bool 			obsolete						()									const override;
	virtual bool			compare							(const	luabind::object* v)			const			{return m_callback==*v;}
	bool			compare							(const	CPHReqComparerV* v)			const override {return v->compare(this);}
	bool			compare							(const	CPHScriptObjectActionN* v)	const override {return m_callback==v->m_callback;}
};

class CPHScriptGameObjectCondition :
	public CPHScriptObjectConditionN
{
	CObject* m_obj;
	bool	 b_obsolete;
public:
	CPHScriptGameObjectCondition( const luabind::object &object,const luabind::functor<bool> &functor,CObject* gobj):
	CPHScriptObjectConditionN(object,functor)
	{
		m_obj=gobj;
		b_obsolete=false;
	}

	bool 			is_true							() override
	{b_obsolete=CPHScriptObjectConditionN::is_true();return b_obsolete;}
	virtual bool			compare							(const	CObject* v)			const			{return m_obj->ID()==v->ID();}
	bool			compare							(const	CPHReqComparerV* v)	const override {return v->compare(this);}
	bool			obsolete						()							const override {return b_obsolete;}
};

class CPHScriptGameObjectAction :
	public CPHScriptObjectActionN
{
	CObject* m_obj;
public:
	CPHScriptGameObjectAction( const luabind::object &object,const luabind::functor<void> &functor,CObject* gobj):
	CPHScriptObjectActionN(object,functor)
	{
		m_obj=gobj;
	}

	bool			compare							(const	CPHReqComparerV* v)	const override {return v->compare(this);}
	virtual bool			compare							(const	CObject* v)			const			{return m_obj->ID()==v->ID();}
};

class CPHSriptReqObjComparer :
	public CPHReqComparerV
{
	luabind::object					*m_lua_object;

public:
								CPHSriptReqObjComparer	(const luabind::object & lua_object)			{m_lua_object= xr_new<luabind::object>(lua_object);}
								CPHSriptReqObjComparer	(const CPHSriptReqObjComparer &object)			{m_lua_object= xr_new<luabind::object>(*object.m_lua_object);}
		virtual					~CPHSriptReqObjComparer	()												{xr_delete(m_lua_object);}
	bool		compare					(const	CPHScriptObjectCondition* v)	const override {return v->compare(m_lua_object);}
	bool		compare					(const	CPHScriptObjectAction* v)		const override {return v->compare(m_lua_object);}
	bool		compare					(const	CPHScriptObjectConditionN* v)	const override {return v->compare(m_lua_object);}
	bool		compare					(const	CPHScriptObjectActionN* v)		const override {return v->compare(m_lua_object);}
};


class CPHSriptReqGObjComparer :
	public CPHReqComparerV
{
	CObject				*m_object;

public:
	CPHSriptReqGObjComparer	(CObject* object)			{m_object= object;}
	bool		compare					(const	CPHScriptGameObjectAction* v)	const override {return v->compare(m_object);}
	bool		compare					(const	CPHScriptGameObjectCondition* v)const override {return v->compare(m_object);}
};