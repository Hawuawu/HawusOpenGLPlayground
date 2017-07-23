#pragma once

#ifndef VXLECamera_H
#define VXLECamera_H

#include "VXLEngineSettings.h"
#include "VXLEControls.h"
#include <stdio.h>
#include <cstdio>
#include <iostream>

#define _USE_MATH_DEFINES 
#include <math.h>

#include "glm\vec3.hpp"
#include <glm\geometric.hpp>


class VXLECamera {
public:
	VXLECamera(VXLEngineSettings settings, VXLEFirstPersonControls *controls);
	~VXLECamera();

public:
	void recalculate();

	glm::vec3 getPosition() const { return position_; }
	glm::vec3 getDirection() const { return direction_; }

private:
	VXLEngineSettings engineSettings_;
	VXLEFirstPersonControls *controls_;	

	glm::vec3 position_;
	glm::vec3 direction_;
};

#endif // !VXLECamera_H
