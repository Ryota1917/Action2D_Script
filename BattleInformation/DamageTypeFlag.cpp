#include "DamageTypeFlag.h"


void DamageTypeFlag::SetFlag(DamageType type)
{
	mTypeFlag |= static_cast<unsigned int>(type);
}

void DamageTypeFlag::ResetFlag(DamageType type)
{
	mTypeFlag &= ~static_cast<unsigned int>(type);
}

void DamageTypeFlag::ClearFlag()
{
	mTypeFlag &= 0;
}

bool DamageTypeFlag::IsOn(DamageType type)const
{
	return mTypeFlag & (static_cast<unsigned int>(type));
}