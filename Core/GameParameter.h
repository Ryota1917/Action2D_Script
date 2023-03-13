#pragma once

class GameParameter {
public:
	/// �E�B���h�E��x���W
	static const int WindowX = 512;

	/// �E�B���h�E��y���W
	static const int WindowY = 256;

	/// �E�B���h�E�̍���
	static const int WindowHeight = 768;
	
	/// �E�B���h�E�̕�
	static const int WindowWidth = 1024;

	static const char* WindowTitle() { return "Action2D"; }

	static const char* FontPath() { return "../Assets/Font/PixelMplus12-Regular.ttf"; }
};