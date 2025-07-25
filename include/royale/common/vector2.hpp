#pragma once

namespace royale
{
	class Vector2
	{
	public:
		double x {};
		double y {};

		Vector2() = default;

		Vector2(double x, double y)
		{
			this->x = x;
			this->y = y;
		}

		Vector2 scale(double scaleFactor)
		{
			x = x * scaleFactor;
			y = y * scaleFactor;
			return *this;
		}

		Vector2 scale(double scaleFactorX, double scaleFactorY)
		{
			x = x * scaleFactorX;
			y = y * scaleFactorY;
			return *this;
		}

		Vector2 scale(Vector2 scaleFactor)
		{
			x = x * scaleFactor.x;
			y = y * scaleFactor.y;
			return *this;
		}
	};
}