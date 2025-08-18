#pragma once

#include <chrono>

namespace royale
{
	class ElixirManager
	{
		double mElixir {};
		bool mGenerating {};
		double mSpeed = 1.0;

	public:
		ElixirManager() = default;

		void startGenerating();
		void stopGenerating();

		void setGenerationSpeed(double speed);
		void generateElixir(double dt);

		double getElixir() const;
		void spendElixir(double amount);
	};
}