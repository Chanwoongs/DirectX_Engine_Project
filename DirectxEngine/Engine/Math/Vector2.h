#pragma once

#include <string>

#include "../Core/Type.h"

namespace DirectxEngine
{
    // 2차원 벡터 클래스.
    class Vector2
    {
    public:
        // x좌표 / y좌표.
        float x;
        float y;

        Vector2()
            : x(0.0f), y(0.0f)
        {
        }

        Vector2(float value)
            : x(value), y(value)
        {
        }

        Vector2(float x, float y)
            : x(x), y(y)
        {
        }

        // 메모리 크기.
        static uint32 Stride() { return sizeof(Vector2); }

        // 연산자 오버로딩.
        Vector2& operator+=(const Vector2& other);
        Vector2& operator-=(const Vector2& other);
        Vector2& operator*=(float scale);
        Vector2& operator/=(float scale);
        bool operator==(const Vector2& other);
        bool operator!=(const Vector2& other);
        Vector2 operator-() const;

        friend Vector2 operator+(const Vector2& left, const Vector2& right);
        friend Vector2 operator-(const Vector2& left, const Vector2& right);
        friend Vector2 operator*(const Vector2& vector, float scale);
        friend Vector2 operator*(float scale, const Vector2& vector);
        friend Vector2 operator/(const Vector2& vector, float scale);

        // (x, y) 문자열 생성 함수.
        std::wstring ToString();

        // 길이 구하기.
        float Length();
        // float LengthSquared();
        // 내적.
        friend float Dot(const Vector2& left, const Vector2& right);
        // 정규화, 내부를 건드리지 않고 정규화한 값의 복사본을 반환.
        Vector2 Normalized();
        // 같은지.
        bool Equals(const Vector2& other);

        // 선형 보간(Lerp - Linear Interpolation).
        // (1 - t) * from + t * to.
        friend Vector2 Lerp(const Vector2& from, const Vector2& to, float t);

        // 기본 값.
        static const Vector2 Zero;
        static const Vector2 One;
        static const Vector2 Right;
        static const Vector2 Up;
    };
}