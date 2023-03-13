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

	/// UIScreenとHUDのどちらにイベントを送るか．
	UIEventAdress adress;
	/// UIのイベントの操作
	UIEventFlag flag;
	/// どのidのイベントに送るか．-1の時は全てにイベントを送信します．
	int id;
	/// イベントのメッセージです．
	const char* message;
	/// イベントに送る数値です
	int processNum;
};