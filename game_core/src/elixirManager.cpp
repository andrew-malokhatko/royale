#include "elixirManager.hpp"
#include "config.hpp"

namespace royale
{
	void ElixirManager::startGenerating()
	{
		mGenerating = true;
	}

	void ElixirManager::stopGenerating()
	{
		mGenerating = false;
	}

	void ElixirManager::setGenerationSpeed(double speed)
	{
		mSpeed = speed;
	}

	void ElixirManager::generateElixir(double dt)
	{
		if (!mGenerating)
		{
			return;
		}

		if (mElixir >= Config::MAX_ELIXIR)
		{
			mElixir = Config::MAX_ELIXIR;
			return;
		}

		mElixir += dt * mSpeed * Config::ELIXIR_GENERATION_SPEED;
	}

	double ElixirManager::getElixir() const
	{
		return mElixir;
	}
}