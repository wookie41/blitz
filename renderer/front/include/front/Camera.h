#pragma once

#include <core/RenderState.h>
#include <front/Precompiled.h>


namespace blitz::front
{
    class Camera
    {
      public:
        Camera(const Vector3f& pos, const Vector3f& dir, const Vector3f& worldUpVector, const float& fov);

        void move(const Vector3f& displacement);
        void rotate(const Vector3f& angles);
        Matrix4f calculateViewMatrix() const;

        float getFieldOfView() const;
        void setFieldOfView(const float& fov);

        Projection getProjection() const;
        void setProjection(const Projection& newProjection);

        Vector3f getDirection() const;

        Vector3f calculateRightVector() const;

      private:
        Projection projection = Projection::ORTHOGRAPHIC;
        float fieldOfView = 45.f;
        Vector3f rotation; // euler angles (yaw, pitch roll)
        Vector3f position;
        Vector3f direction;
        Vector3f worldUp;
    };
} // namespace blitz::front