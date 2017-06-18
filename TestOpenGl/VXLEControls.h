#pragma once

#ifndef VXLEFirstPersonControls_H
#define VXLEFirstPersonControls_H

class VXLEFirstPersonControls
{
public:
	bool forward = false;
	bool backward = false;
	bool leftStrafe = false;
	bool rightStrafe = false;

	bool movingMouse = false;
	float lastMouseX = 0.0;
	float lastMouseY = 0.0;
};

#endif // !VXLEFirstPersonControls_H