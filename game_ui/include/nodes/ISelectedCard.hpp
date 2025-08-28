#pragma once

#include "Card.hpp"

namespace ui
{
	class ISelectedCard
	{
	public:
		//
		//	Return currently selected card
		//
		virtual const Card* getSelectedCard() = 0;

		// 
		//	Sets selected card's visible to false
		//
		virtual void hideSelectedCard() = 0;

		// 
		//	Sets selected card's visible to true
		//
		virtual void showSelectedCard() = 0;
	};
}