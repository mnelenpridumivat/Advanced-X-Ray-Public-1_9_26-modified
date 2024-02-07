#pragma once
#include <unordered_set>
#include <string>

#define DECLARE_NONSTATIC_CLASS_GETTER() \
	virtual CMetaclass* GetClass() override { return StaticClass();} \

#define DECLARE_OBJECT_ISA() \
	virtual bool IsA(CMetaclass* Class) override {return StaticClass()->IsA(Class);} \

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

#define DECLARE_METACLASS1(ClassName, Parent1) \
public: \
	static CMetaclass* StaticClass(){ \
		static CMetaclass* Instance = nullptr; \
		if (!Instance) { \
			Instance = new CMetaclass(#ClassName); \
			Instance->AddParent(Parent1::StaticClass()); \
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
			Instance->AddParent(Parent1::StaticClass()); \
			Instance->AddParent(Parent2::StaticClass()); \
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
			Instance->AddParent(Parent1::StaticClass()); \
			Instance->AddParent(Parent2::StaticClass()); \
			Instance->AddParent(Parent3::StaticClass()); \
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
			Instance->AddParent(Parent1::StaticClass()); \
			Instance->AddParent(Parent2::StaticClass()); \
			Instance->AddParent(Parent3::StaticClass()); \
			Instance->AddParent(Parent4::StaticClass()); \
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
			Instance->AddParent(Parent1::StaticClass()); \
			Instance->AddParent(Parent2::StaticClass()); \
			Instance->AddParent(Parent3::StaticClass()); \
			Instance->AddParent(Parent4::StaticClass()); \
			Instance->AddParent(Parent5::StaticClass()); \
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
			Instance->AddParent(Parent1::StaticClass()); \
			Instance->AddParent(Parent2::StaticClass()); \
			Instance->AddParent(Parent3::StaticClass()); \
			Instance->AddParent(Parent4::StaticClass()); \
			Instance->AddParent(Parent5::StaticClass()); \
			Instance->AddParent(Parent6::StaticClass()); \
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
			Instance->AddParent(Parent1::StaticClass()); \
			Instance->AddParent(Parent2::StaticClass()); \
			Instance->AddParent(Parent3::StaticClass()); \
			Instance->AddParent(Parent4::StaticClass()); \
			Instance->AddParent(Parent5::StaticClass()); \
			Instance->AddParent(Parent6::StaticClass()); \
			Instance->AddParent(Parent7::StaticClass()); \
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
	virtual CMetaclass* GetClass() = 0;
	virtual bool IsA(CMetaclass* Class) = 0;
};

template<typename To>
To* meta_cast(void* ptr) {
	CMetaclass* FromClass = static_cast<IMetaClass*>(ptr)->GetClass();

	if (!FromClass->IsA(To::StaticClass())) {
		return nullptr;
	}
	return reinterpret_cast<To*>(ptr);
}
