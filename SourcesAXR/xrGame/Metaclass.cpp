#include "stdafx.h"
#include "Metaclass.h"

void CMetaclass::RegisterParents(std::unordered_set<CMetaclass*>& ParentsSet)
{
	Msg("Register parent [%s]", GetMetaclassName());
	ParentsSet.insert(this);
	for (auto& elem : Parents) {
		elem->RegisterParents(ParentsSet);
	}
}

CMetaclass::CMetaclass(std::string Name): Name(Name)
{
	Msg("Create metaclass [%s]", Name.c_str());
}

const std::string& CMetaclass::GetMetaclassName()
{
	return Name;
}

void CMetaclass::AddParent(CMetaclass* Parent)
{
	//Msg("Register parent [%s] at metaclass [%s]", Parent->GetMetaclassName(), Name.c_str());
	//Parents.insert(Parent);
	Parent->RegisterParents(Parents);
}

bool CMetaclass::IsA(CMetaclass* Class)
{
	return Class == this || Parents.find(Class) != Parents.end();
}
