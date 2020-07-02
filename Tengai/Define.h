#pragma once

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS 60
template<typename EnumT>
constexpr int ENUM_MAX()
{
	return (int)EnumT::END;
}