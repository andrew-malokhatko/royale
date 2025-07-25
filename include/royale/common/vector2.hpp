#pragma once

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

		Vector2& scale(double scaleFactorX, double scaleFactorY)
		{
			x = x * scaleFactorX;
			y = y * scaleFactorY;
			return *this;
		}

		Vector2& scale(double scaleFactor)
		{
			return scale(scaleFactor, scaleFactor);
		}

		Vector2& scale(Vector2 scaleFactor)
		{
			return scale(scaleFactor.x, scaleFactor.y);
		}
	};
}