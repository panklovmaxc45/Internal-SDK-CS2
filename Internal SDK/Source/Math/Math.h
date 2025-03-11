#pragma once

#include <Windows.h>
#include <complex>

const float ScreenWidth = static_cast<float>(GetSystemMetrics(SM_CXSCREEN));
const float ScreenHeight = static_cast<float>(GetSystemMetrics(SM_CYSCREEN));

struct Vector2 {
    constexpr Vector2(
        const float X = 0.f,
        const float Y = 0.f
    ) noexcept : X(X), Y(Y) {
    }

    float X, Y;
};

struct Vector3 {
    constexpr Vector3(
        const float X = 0.f,
        const float Y = 0.f,
        const float Z = 0.f
    ) noexcept : X(X), Y(Y), Z(Z) {
    }

    Vector3 operator+(const Vector3& Other) const {
        return Vector3(X + Other.X, Y + Other.Y, Z + Other.Z);
    }

    Vector3 operator-(const Vector3& Other) const {
        return Vector3(X - Other.X, Y - Other.Y, Z - Other.Z);
    }

    Vector3 operator*(float Scalar) const {
        return Vector3(X * Scalar, Y * Scalar, Z * Scalar);
    }

    float Length() const {
        return std::sqrt(X * X + Y * Y + Z * Z);
    }

    bool WTS(Vector2& Out, float(*ViewMatrix)[4][4]) const {
        const float W = (*ViewMatrix)[3][0] * X + (*ViewMatrix)[3][1] * Y + (*ViewMatrix)[3][2] * Z + (*ViewMatrix)[3][3];

        if (W <= 0.01f)
            return false;

        const float InvW = 1.0f / W;

        Out.X = (ScreenWidth / 2.0f) + (((*ViewMatrix)[0][0] * X + (*ViewMatrix)[0][1] * Y + (*ViewMatrix)[0][2] * Z + (*ViewMatrix)[0][3]) * InvW * (ScreenWidth / 2.0f));
        Out.Y = (ScreenHeight / 2.0f) - (((*ViewMatrix)[1][0] * X + (*ViewMatrix)[1][1] * Y + (*ViewMatrix)[1][2] * Z + (*ViewMatrix)[1][3]) * InvW * (ScreenHeight / 2.0f));

        return true;
    }

    float X, Y, Z;
};

extern const float ScreenWidth;
extern const float ScreenHeight;