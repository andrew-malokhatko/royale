#pragma once

#include <cmath>

namespace royale
{
	class Vector2
	{
	public:
		double x{};
		double y{};

		Vector2() = default;

		Vector2(double x, double y) :
			x{ x },
			y{ y }
		{
		}

		void scale(double scaleFactorX, double scaleFactorY)
		{
			x = x * scaleFactorX;
			y = y * scaleFactorY;
		}

		void scale(double scaleFactor)
		{
			scale(scaleFactor, scaleFactor);
		}

		void scale(Vector2 scaleFactor)
		{
			scale(scaleFactor.x, scaleFactor.y);
		}

		double length()	
		{
			return std::sqrt(x * x + y * y);
		}

		void normalize()
		{
			double len = length();
			if (len == 0)
			{
				return;
			}

			x = x / len;
			y = y / len;
		}

		Vector2 operator+(const Vector2& other) const
		{
			return Vector2{ x + other.x, y + other.y };
		} 
	};
}