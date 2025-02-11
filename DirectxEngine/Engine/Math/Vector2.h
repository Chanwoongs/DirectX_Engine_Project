#pragma once

#include <string>

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
       
        // 기본 값.
        static const Vector2 Zero;
        static const Vector2 One;
        static const Vector2 Right;
        static const Vector2 Up;

        // (x, y) 문자열 생성 함수.
        std::wstring ToString();

        // 길이 구하기.
        float Length();
        // float LengthSquared();
        // 내적.
        float Dot(const Vector2& other);
        // 정규화, 내부를 건드리지 않고 정규화한 값의 복사본을 반환.
        Vector2 Normalized();
        // 같은지.
        bool Equals(const Vector2& other);
    };
}