#include <front/Camera.h>

namespace blitz::front
{
    Camera::Camera(const Vector3f& pos, const Vector3f& dir, const Vector3f& worldUpVector, const float& fov)
    : fieldOfView(fov), position(pos), direction(dir), worldUp(worldUpVector)
    {
        rotation = { 0, 0, 0 };
    }

    Vector3f Camera::getDirection() const { return direction; }

    void Camera::move(const Vector3f& displacement) { position += displacement; }

    void Camera::rotate(const Vector3f& angles)
    {
        rotation.x = rotation.x + angles.x;
        rotation.y = rotation.y + angles.y;
        rotation.z = rotation.z + angles.z;

        direction.x = cos(toRadians(rotation.x)) * cos(toRadians(rotation.y));
        direction.y = sin(toRadians(rotation.y));
        direction.z = sin(toRadians(rotation.x)) * cos(toRadians(rotation.y));
        direction.Normalize();
    }
    
    Vector3f Camera::calculateRightVector() const 
    {
        auto vec = Vector3f::CrossProduct(direction.Normalized(), worldUp);
        vec.Normalize();
        return vec; 
    }

    Matrix4f Camera::calculateViewMatrix() const
    {
        auto cameraFront = direction.Normalized();
        Vector3f cameraRight = calculateRightVector();
        Vector3f cameraUp = Vector3f::CrossProduct(cameraRight, cameraFront);
        cameraUp.Normalize();
        return Matrix4f::LookAt(position, position + cameraFront, cameraUp);
    }

    float Camera::getFieldOfView() const { return fieldOfView; }

    void Camera::setFieldOfView(const float& fov) { fieldOfView = fov; }

    Projection Camera::getProjection() const { return projection; }

    void Camera::setProjection(const Projection& newProjection) { projection = newProjection; }

} // namespace blitz::front