#pragma once

#include "Core/Type.h"
#include "Vector3.h"

namespace DirectxEngine
{
    class Matrix4
    {
    public:
        Matrix4();
        Matrix4(const Matrix4& other);
        ~Matrix4() = default;

        // 메모리 너비(단위: 바이트).
        static uint32 Stride() { return sizeof(Matrix4); }

        static Matrix4 Rotation(const Vector3& rotation);
        static Matrix4 Rotation(float x, float y, float z);
        static Matrix4 RotationX(float angle);
        static Matrix4 RotationY(float angle);
        static Matrix4 RotationZ(float angle);

        // operator overloading.
        Matrix4& operator=(const Matrix4& other);
        Matrix4 operator*(const Matrix4& other);
        Matrix4 operator*=(const Matrix4& other);

        friend Vector3 operator*(const Matrix4& matrix, const Vector3& vector);
        friend Vector3 operator*(const Vector3& vector, const Matrix4& matrix);

        // Degree <-> Radian
        // constexpr: 상수를 static으로 만들 때 constexpr 키워드를 붙이면 header에서 초기화할 수 있다.
        // 계산을 컴파일 시점에 1번만 하고 저장한다.
        static constexpr const float DegreeToRadian = 3.141592f / 180.0f;
        static constexpr const float RadianToDegree = 180.0f / 3.141592f;

        static Matrix4 Identity;

    private:
        // 공용체.
        // 공용체는 메모리를 공유.
        // 공용체안에서 덩치가 가장 큰 메모리 공간을 공유한다.
        union
        {
            struct
            {
                float m00, m01, m02, m03;
                float m10, m11, m12, m13;
                float m20, m21, m22, m23;
                float m30, m31, m32, m33;
            };

            float elements[4 * 4];
        };
    };
}