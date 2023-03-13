#pragma once
#include"DamageEnum.h"

class DamageTypeFlag {
public:
	DamageTypeFlag() :mTypeFlag(0) {}

	void SetFlag(DamageType type);
	void ResetFlag(DamageType type);
	void ClearFlag();

	bool IsOn(DamageType type)const;

private:
	unsigned int mTypeFlag;
};
