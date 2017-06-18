#include "VXLECamera.h"
VXLECamera::VXLECamera(VXLEngineSettings settings, VXLEFirstPersonControls *controls) 
	: 
	engineSettings_(settings),
	controls_(controls),
	position_(glm::vec3(0,0,0)),
	direction_(glm::vec3(0, 0, 0))
{
}

VXLECamera::~VXLECamera()
{

}

void VXLECamera::recalculate()
{

	float windowMiddleX = engineSettings_.containerWidth / 2;
	float windowMiddleY = engineSettings_.containerHeight / 2;


	//std::cout << controls_->forward << controls_->backward << controls_->leftStrafe << controls_->rightStrafe << std::endl;

	if (controls_->movingMouse)
	{
		double horizontal = (controls_->lastMouseX - windowMiddleX) * engineSettings_.yawSensitivity;
		double vertical = (controls_->lastMouseY - windowMiddleY) * engineSettings_.pitchSensitivity;

		//std::cout << "Mid window values: " << windowMiddleX << "\t" << windowMiddleY << std::endl;
		//std::cout << "Mouse values     : " << controls_->lastMouseX << "\t" << controls_->lastMouseY << std::endl;
		//std::cout << horizontal << "\t" << vertical << std::endl << std::endl;

		direction_.x += vertical;
		direction_.y += horizontal;
		/*
		if (direction_.x < -90)
		{
			direction_.x = -90;
		}

		if (direction_.x > 90)
		{
			direction_.x = 90;
		}

		if (direction_.y < -90)
		{
			direction_.y = -90;
		}

		if (direction_.y > 90)
		{
			direction_.y = 90;
		}*/

		if (direction_.y < -180.0f)
		{
			direction_.y += 360.0f;
		}

		if (direction_.y > 180.0f)
		{
			direction_.y -= 360.0f;
		}

		if (direction_.y < 0)
		{
			direction_.y += 360;
		}
		if (direction_.y > 360)
		{
			direction_.y += -360;
		}

	}

	glm::vec3 movement;

	double sinXDirection = sin(direction_.x * (M_PI / 180));
	double cosXDirection = cos(direction_.x * (M_PI / 180));

	double sinYDirection = sin(direction_.y * (M_PI / 180));
	double cosYDirection = cos(direction_.y * (M_PI / 180));

	double pitchLimitFactor = cosXDirection;

	if (controls_->forward)
	{
		movement.x += (sinYDirection * pitchLimitFactor);
		movement.y += (-1 * sinXDirection);
		movement.z += (-1 * cosYDirection * pitchLimitFactor);
	}

	if (controls_->backward)
	{
		movement.x += (-1 * sinYDirection * pitchLimitFactor);
		movement.y += (sinXDirection);
		movement.z += (cosYDirection * pitchLimitFactor);
	}

	if (controls_->leftStrafe)
	{
		movement.x += -1 * cosYDirection;
		movement.z += -1 * sinYDirection;
	}

	if (controls_->rightStrafe)
	{
		movement.x += cosYDirection;
		movement.z += sinYDirection;
	}


	// Normalise our movement vector
	//movement.normalise();

	// Calculate our value to keep the movement the same speed regardless of the framerate...
	//double framerateIndependentFactor = movementSpeedFactor * deltaTime;

	// .. and then apply it to our movement vector.
	//movement *= framerateIndependentFactor;

	// Finally, apply the movement to our position
	movement.x = (movement.x * engineSettings_.movementFactor);
	movement.y = (movement.y * engineSettings_.movementFactor);
	movement.z = (movement.z * engineSettings_.movementFactor);

	float rat = sqrt(std::pow(movement.x, 2) + std::pow(movement.y, 2) + std::pow(movement.z, 2));
	//std::cout << rat<< std::endl << std::endl;
	if (rat > 0) {
		movement.x /= rat;
		movement.y /= rat;
		movement.z /= rat;
	}
	position_ += movement;
}