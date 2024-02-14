#pragma once
#include <unordered_set>
#include <string>

#pragma warning (disable : 4584)

#define DECLARE_NONSTATIC_CLASS_GETTER() \
	virtual CMetaclass* GetClass() const override { return StaticClass();} \

#define DECLARE_OBJECT_ISA() \
	virtual bool IsA(CMetaclass* Class) const override {return StaticClass()->IsA(Class);} \

#define DECLARE_METACLASS(ClassName) \
public: \
	static CMetaclass* StaticClass(){ \
		static CMetaclass* Instance = nullptr; \
		if (!Instance) { \
			Instance = new CMetaclass(#ClassName); \
		} \
		return Instance; \
	} \
	DECLARE_NONSTATIC_CLASS_GETTER() \
	DECLARE_OBJECT_ISA() \
private:\

#define ADD_PARENT_CHECKED(ClassName, Parent) \
	static_assert(std::is_base_of_v<Parent, ClassName> == true); \
	Instance->AddParent(Parent::StaticClass()); \

#define DECLARE_METACLASS1(ClassName, Parent1) \
public: \
	static CMetaclass* StaticClass(){ \
		static CMetaclass* Instance = nullptr; \
		if (!Instance) { \
			Instance = new CMetaclass(#ClassName); \
			ADD_PARENT_CHECKED(ClassName, Parent1) \
		} \
		return Instance; \
	} \
	DECLARE_NONSTATIC_CLASS_GETTER() \
	DECLARE_OBJECT_ISA() \
private:\

#define DECLARE_METACLASS2(ClassName, Parent1, Parent2) \
public: \
	static CMetaclass* StaticClass(){ \
		static CMetaclass* Instance = nullptr; \
		if (!Instance) { \
			Instance = new CMetaclass(#ClassName); \
			ADD_PARENT_CHECKED(ClassName, Parent1) \
			ADD_PARENT_CHECKED(ClassName, Parent2) \
		} \
		return Instance; \
	} \
	DECLARE_NONSTATIC_CLASS_GETTER() \
	DECLARE_OBJECT_ISA() \
private:\

#define DECLARE_METACLASS3(ClassName, Parent1, Parent2, Parent3) \
public: \
	static CMetaclass* StaticClass(){ \
		static CMetaclass* Instance = nullptr; \
		if (!Instance) { \
			Instance = new CMetaclass(#ClassName); \
			ADD_PARENT_CHECKED(ClassName, Parent1) \
			ADD_PARENT_CHECKED(ClassName, Parent2) \
			ADD_PARENT_CHECKED(ClassName, Parent3) \
		} \
		return Instance; \
	} \
	DECLARE_NONSTATIC_CLASS_GETTER() \
	DECLARE_OBJECT_ISA() \
private:\

#define DECLARE_METACLASS4(ClassName, Parent1, Parent2, Parent3, Parent4) \
public: \
	static CMetaclass* StaticClass(){ \
		static CMetaclass* Instance = nullptr; \
		if (!Instance) { \
			Instance = new CMetaclass(#ClassName); \
			ADD_PARENT_CHECKED(ClassName, Parent1) \
			ADD_PARENT_CHECKED(ClassName, Parent2) \
			ADD_PARENT_CHECKED(ClassName, Parent3) \
			ADD_PARENT_CHECKED(ClassName, Parent4) \
		} \
		return Instance; \
	} \
	DECLARE_NONSTATIC_CLASS_GETTER() \
	DECLARE_OBJECT_ISA() \
private:\

#define DECLARE_METACLASS5(ClassName, Parent1, Parent2, Parent3, Parent4, Parent5) \
public: \
	static CMetaclass* StaticClass(){ \
		static CMetaclass* Instance = nullptr; \
		if (!Instance) { \
			Instance = new CMetaclass(#ClassName); \
			ADD_PARENT_CHECKED(ClassName, Parent1) \
			ADD_PARENT_CHECKED(ClassName, Parent2) \
			ADD_PARENT_CHECKED(ClassName, Parent3) \
			ADD_PARENT_CHECKED(ClassName, Parent4) \
			ADD_PARENT_CHECKED(ClassName, Parent5) \
		} \
		return Instance; \
	} \
	DECLARE_NONSTATIC_CLASS_GETTER() \
	DECLARE_OBJECT_ISA() \
private:\

#define DECLARE_METACLASS6(ClassName, Parent1, Parent2, Parent3, Parent4, Parent5, Parent6) \
public: \
	static CMetaclass* StaticClass(){ \
		static CMetaclass* Instance = nullptr; \
		if (!Instance) { \
			Instance = new CMetaclass(#ClassName); \
			ADD_PARENT_CHECKED(ClassName, Parent1) \
			ADD_PARENT_CHECKED(ClassName, Parent2) \
			ADD_PARENT_CHECKED(ClassName, Parent3) \
			ADD_PARENT_CHECKED(ClassName, Parent4) \
			ADD_PARENT_CHECKED(ClassName, Parent5) \
			ADD_PARENT_CHECKED(ClassName, Parent6) \
		} \
		return Instance; \
	} \
	DECLARE_NONSTATIC_CLASS_GETTER() \
	DECLARE_OBJECT_ISA() \
private:\

#define DECLARE_METACLASS7(ClassName, Parent1, Parent2, Parent3, Parent4, Parent5, Parent6, Parent7) \
public: \
	static CMetaclass* StaticClass(){ \
		static CMetaclass* Instance = nullptr; \
		if (!Instance) { \
			Instance = new CMetaclass(#ClassName); \
			ADD_PARENT_CHECKED(ClassName, Parent1) \
			ADD_PARENT_CHECKED(ClassName, Parent2) \
			ADD_PARENT_CHECKED(ClassName, Parent3) \
			ADD_PARENT_CHECKED(ClassName, Parent4) \
			ADD_PARENT_CHECKED(ClassName, Parent5) \
			ADD_PARENT_CHECKED(ClassName, Parent6) \
			ADD_PARENT_CHECKED(ClassName, Parent7) \
		} \
		return Instance; \
	} \
	DECLARE_NONSTATIC_CLASS_GETTER() \
	DECLARE_OBJECT_ISA() \
private:\

#define DECLARE_METACLASS11(ClassName, Parent1, Parent2, Parent3, Parent4, Parent5, Parent6, Parent7, Parent8, Parent9, Parent10, Parent11) \
public: \
	static CMetaclass* StaticClass(){ \
		static CMetaclass* Instance = nullptr; \
		if (!Instance) { \
			Instance = new CMetaclass(#ClassName); \
			ADD_PARENT_CHECKED(ClassName, Parent1) \
			ADD_PARENT_CHECKED(ClassName, Parent2) \
			ADD_PARENT_CHECKED(ClassName, Parent3) \
			ADD_PARENT_CHECKED(ClassName, Parent4) \
			ADD_PARENT_CHECKED(ClassName, Parent5) \
			ADD_PARENT_CHECKED(ClassName, Parent6) \
			ADD_PARENT_CHECKED(ClassName, Parent7) \
			ADD_PARENT_CHECKED(ClassName, Parent8) \
			ADD_PARENT_CHECKED(ClassName, Parent9) \
			ADD_PARENT_CHECKED(ClassName, Parent10) \
			ADD_PARENT_CHECKED(ClassName, Parent11) \
		} \
		return Instance; \
	} \
	DECLARE_NONSTATIC_CLASS_GETTER() \
	DECLARE_OBJECT_ISA() \
private:\

class CMetaclass {
	std::unordered_set<CMetaclass*> Parents = {};

	void RegisterParents(std::unordered_set<CMetaclass*>& ParentsSet) {
		ParentsSet.insert(this);
		for (auto& elem : Parents) {
			elem->RegisterParents(ParentsSet);
		}
	}

	std::string Name;

public:

	CMetaclass(std::string_view Name) : Name(Name) {}

	const std::string& GetClassName() {
		return Name;
	}

	void AddParent(CMetaclass* Parent) {
		Parents.insert(Parent);
		Parent->RegisterParents(Parents);
	}

	bool IsA(CMetaclass* Class) {
		return Parents.find(Class) != Parents.end();
	}

};

class IMetaClass {
public:
	virtual CMetaclass* GetClass() const = 0;
	virtual bool IsA(CMetaclass* Class) const = 0;
};

template<typename To>
To* meta_cast(void* ptr) {
	CMetaclass* FromClass = static_cast<IMetaClass*>(ptr)->GetClass();

	if (!FromClass->IsA(To::StaticClass())) {
		return nullptr;
	}
	return reinterpret_cast<To*>(ptr);
}

class MetacastClass {

public:

	template<typename To>
	static To* meta_cast(void* ptr) {
#ifdef DEBUG
		static_assert(std::is_base_of_v<IMetaClass, To> == true);
#endif
		CMetaclass* FromClass = static_cast<IMetaClass*>(ptr)->GetClass();

		if (!FromClass->IsA(To::StaticClass())) {
			return nullptr;
		}
		return reinterpret_cast<To*>(ptr);
	}

	template<typename To>
	static const To* meta_cast(const void* ptr) {
#ifdef DEBUG
		static_assert(std::is_base_of_v<IMetaClass, To> == true);
#endif
		CMetaclass* FromClass = static_cast<const IMetaClass*>(ptr)->GetClass();

		if (!FromClass->IsA(To::StaticClass())) {
			return nullptr;
		}
		return reinterpret_cast<const To*>(ptr);
	}

};
