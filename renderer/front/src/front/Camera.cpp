#include <front/Camera.h>

namespace blitz::front
{
    Camera::Camera(const Vector3f& pos, const Vector3f& dir, const Vector3f& worldUpVector)
    : position(pos), direction(dir), worldUp(worldUpVector)
    {
        rotation = { 0, 0, 0 };
    }

    void Camera::move(const Vector3f& displacement) { position += displacement; }
    
    void Camera::rotate(const Vector3f& angles) 
    {
        rotation.x = std::max(rotation.x + angles.x, 90.f);
        rotation.y = std::max(rotation.y + angles.y, 90.f);
        rotation.z = std::max(rotation.z + angles.z, 90.f);

        direction.x = cos(toRadians(rotation.x)) * cos(toRadians(rotation.y));
        direction.y = sin(toRadians(rotation.x));
        direction.z = sin(toRadians(rotation.x)) * cos(toRadians(rotation.y));
    }

    Matrix4f Camera::calculateViewMatrix() const
    {
        const Vector3f cameraRight = Vector3f::CrossProduct(worldUp, direction);
        const Vector3f cameraUp = Vector3f::CrossProduct(direction, cameraRight);
        return Matrix4f::LookAt(position, direction, cameraUp);
    }
} // namespace blitz::front