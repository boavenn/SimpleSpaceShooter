#pragma once

class WindowProperties
{
public:
	static unsigned getWidth() { return WIDTH; }
	static unsigned getHeight() { return HEIGHT; }

private:
	static const unsigned WIDTH = 1366;
	static const unsigned HEIGHT = 768;
};