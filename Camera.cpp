#include "Camera.h"

CameraClass::CameraClass(unsigned int viewportWidth, unsigned int viewportHeight, float verticalFOV, float nearClip, float farClip)
	: viewportWidth(viewportWidth), viewportHeight(viewportHeight), verticalFOV(verticalFOV), nearClip(nearClip), farClip(farClip)
{
	view = glm::lookAt(position, position + forwardDirection, glm::vec3(0.f, 1.f, 0.f));
	inverseView = glm::inverse(view);
	projection = glm::perspectiveFov(verticalFOV, (float)viewportWidth, (float)viewportHeight, nearClip, farClip);
	inverseProjection = glm::inverse(projection);
}

void CameraClass::GetRayDirections(std::vector<glm::vec3>& rayDirections)
{
	glm::vec2 coordinate;
	glm::vec4 target;

	for (unsigned int y = 0u; y < viewportHeight; ++y) {
		for (unsigned int x = 0u; x < viewportWidth; ++x) {
			float offsetX = Utils::RandomFloat() - 0.5f;
			float offsetY = Utils::RandomFloat() - 0.5f;

			coordinate = glm::vec2(((float)x + offsetX) / (float)viewportWidth, ((float)y + offsetY) / (float)viewportHeight);
			coordinate *= 2.f;
			coordinate -= 1.f;

			target = inverseProjection * glm::vec4(coordinate.x, coordinate.y, 1.f, 1.f);
			rayDirections[x + y * viewportWidth] = glm::vec3(inverseView * glm::vec4(glm::normalize(glm::vec3(target) / target.w), 0.f));
		}
	}
}

void CameraClass::Update(float timeDelta)
{
	if (IsMouseButtonUp(MOUSE_RIGHT_BUTTON)) {
		this->moved = false;
		return;
	}

	Vector2 rawMouseDelta = GetMouseDelta();
	glm::vec2 mouseDelta(rawMouseDelta.x * 0.003, -rawMouseDelta.y * 0.003);

	this->moved = true;
	
	constexpr glm::vec3 upDirection(0.f, 1.f, 0.f);
	glm::vec3 rightDirection = glm::cross(forwardDirection, upDirection);

	if (IsKeyDown(KEY_W))
		position += forwardDirection * timeDelta;
	if (IsKeyDown(KEY_S))
		position -= forwardDirection * timeDelta;
	if (IsKeyDown(KEY_A))
		position -= rightDirection * timeDelta;
	if (IsKeyDown(KEY_D))
		position += rightDirection * timeDelta;
	if (IsKeyDown(KEY_LEFT_SHIFT))
		position += upDirection * timeDelta;
	if (IsKeyDown(KEY_SPACE))
		position -= upDirection * timeDelta;

	float pitchDelta = mouseDelta.y;
	float yawDelta = mouseDelta.x;

	glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-pitchDelta, rightDirection), glm::angleAxis(-yawDelta, upDirection)));
	forwardDirection = glm::rotate(q, forwardDirection);

	view = glm::lookAt(position, position + forwardDirection, upDirection);
	inverseView = glm::inverse(view);
}
