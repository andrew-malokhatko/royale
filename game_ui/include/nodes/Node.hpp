#pragma once

#include "raylib.h"
#include <vector>
#include <functional>

namespace ui
{
	using NodeId = size_t;

	class Node
	{
	private:
		inline static NodeId idCounter = 0;
		NodeId mId;

		std::function<void()> clickCallback{};
		std::function<void()> releaseCallback{};
		std::function<void()> hoverCallback{};

	protected:
		bool mVisible = true;
		bool mEnabled = true;

		Rectangle mRec{};
		std::vector<Node*> mChildren;

		virtual void onClick() { if (clickCallback) clickCallback(); };
		virtual void onRelease() { if (releaseCallback) releaseCallback(); };
		virtual void onHover() { if (hoverCallback) hoverCallback(); };

	public:
		Node(Rectangle rec, bool visible = true, bool enabled = true);

		virtual void update() {};
		virtual void draw() const = 0;
		virtual void resize(int width, int height) = 0;

		void setOnClickCallback(std::function<void()> callback) { clickCallback = callback; };
		void setOnReleaseCallback(std::function<void()> callback) { releaseCallback = callback; };
		void setOnHoverCallback(std::function<void()> callback) { hoverCallback = callback; };

		void addChild(Node* node);
		void removeChild(NodeId childId);
		
		void setPosition(Vector2 position);
		void setSize(Vector2 size);

		Vector2 getPosition() const;
		Vector2 getSize() const;
		Vector2 getCenter() const;

		bool isEnabled() const;
		bool isVisible() const;
		bool collides(Vector2 point) const;
		bool isMouseOver() const;
	};
}