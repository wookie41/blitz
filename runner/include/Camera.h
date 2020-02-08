#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include <blitzcommon/DataType.h>
#include <corecrt_math_defines.h>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
  public:
    // Camera Attributes
    blitz::Vector3f Position;
    blitz::Vector3f Front;
    blitz::Vector3f Up;
    blitz::Vector3f Right;
    blitz::Vector3f WorldUp;
    // Euler Angles
    float Yaw;
    float Pitch;
    // Camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // Constructor with vectors
    Camera(blitz::Vector3f position = { 0.0f, 0.0f, 0.0f }, blitz::Vector3f up = { 0.0f, 1.0f, 0.0f },
           float yaw = YAW,
           float pitch = PITCH)
    : Front(blitz::Vector3f(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    // Constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : Front(blitz::Vector3f(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = blitz::Vector3f(posX, posY, posZ);
        WorldUp = blitz::Vector3f(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    blitz::Matrix4f GetViewMatrix() { return blitz::Matrix4f::LookAt(Position, Position + Front, Up); }

    // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }

    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // Update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        if (Zoom >= 1.0f && Zoom <= 45.0f)
            Zoom -= yoffset;
        if (Zoom <= 1.0f)
            Zoom = 1.0f;
        if (Zoom >= 45.0f)
            Zoom = 45.0f;
    }

  private:
    // Calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // Calculate the new Front vector
        blitz::Vector3f front;
        front.x = cos(Yaw * M_PI / 180.f) * cos(Pitch * M_PI / 180.f);
        front.y = sin(Pitch * M_PI / 180.f);
        front.z = sin(Yaw * M_PI / 180.f) * cos(Pitch * M_PI / 180.f);
        Front = front.Normalized();
        // Also re-calculate the Right and Up vector
        Right = blitz::Vector3f::CrossProduct(Front, WorldUp).Normalized(); // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = blitz::Vector3f::CrossProduct(Right, Front).Normalized();
    }
};
#endif
