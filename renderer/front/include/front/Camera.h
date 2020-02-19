#pragma once

#include <front/Precompiled.h>

namespace blitz::front
{
    class Camera
    {
      public:
        Camera(const Vector3f& pos, const Vector3f& dir, const Vector3f& worldUpVector);

        void move(const Vector3f& displacement);
        void rotate(const Vector3f& angles);
        Matrix4f calculateViewMatrix() const;
        
      private:
        Vector3f rotation; //euler angles (yaw, pitch roll)
        Vector3f position;
        Vector3f direction;
        Vector3f worldUp;
    };
} // namespace blitz::front