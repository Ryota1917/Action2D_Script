#pragma once

enum class UIEventAdress : unsigned short {
	NONE = 0x00,
	UISCREEN = 0x01,
	HUD = 0x02,
	MANAGER = 0x04,
	ALL = UISCREEN | HUD | MANAGER
};

enum class UIEventFlag : unsigned short {
	CREATE_HUD,
	CREATE_UISCREEN,
	ACTIVE,
	PAUSE,
	CLOSE,
	TEXT,
	IMAGE,
};

struct UIEventCommand {
	UIEventCommand(UIEventAdress _adress, UIEventFlag _flag, int _id, const char* _message = nullptr, int _num = 0):
		adress(_adress), flag(_flag), id(_id), message(_message), processNum(_num)
	{}

	/// UIScreen��HUD�̂ǂ���ɃC�x���g�𑗂邩�D
	UIEventAdress adress;
	/// UI�̃C�x���g�̑���
	UIEventFlag flag;
	/// �ǂ�id�̃C�x���g�ɑ��邩�D-1�̎��͑S�ĂɃC�x���g�𑗐M���܂��D
	int id;
	/// �C�x���g�̃��b�Z�[�W�ł��D
	const char* message;
	/// �C�x���g�ɑ��鐔�l�ł�
	int processNum;
};