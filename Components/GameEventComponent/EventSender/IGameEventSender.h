#pragma once

/// コンポ―ネントからイベントを発行します
class IGameEventSender{
public:
	IGameEventSender() {};
	virtual ~IGameEventSender() {};

	virtual void Send(class Game* game) = 0;
};