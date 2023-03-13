#pragma once
#include<vector>

class ItemData {
public:
	static const char* GetTexturePath(int id) { return mTexturePathes[id]; }

private:
	static std::vector<const char*> mTexturePathes;
};
std::vector<const char*> ItemData::mTexturePathes = { "","../Assets/Images/Item/sword.png","../Assets/Images/Item/bomb.png" };