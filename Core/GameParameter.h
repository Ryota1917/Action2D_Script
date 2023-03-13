#pragma once

class GameParameter {
public:
	/// ウィンドウのx座標
	static const int WindowX = 512;

	/// ウィンドウのy座標
	static const int WindowY = 256;

	/// ウィンドウの高さ
	static const int WindowHeight = 768;
	
	/// ウィンドウの幅
	static const int WindowWidth = 1024;

	static const char* WindowTitle() { return "Action2D"; }

	static const char* FontPath() { return "../Assets/Font/PixelMplus12-Regular.ttf"; }
};