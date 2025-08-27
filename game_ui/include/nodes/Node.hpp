#pragma once

#include "raylib.h"
#include <vector>
#include <functional>

#include "MouseClickEvent.hpp"
#include "MouseReleaseEvent.hpp"
#include "MouseHoverEvent.hpp"
#include "MouseMoveEvent.hpp"

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
		std::function<void()> moveCallback{};

	protected:
		bool mVisible = true;
		bool mEnabled = true;

		Rectangle mRec{};
		std::vector<Node*> mChildren;

		virtual void drawSelf() const = 0;
		virtual void resizeSelf(int width, int height) = 0;
		virtual void updateSelf() {};

		virtual void handleClick(MouseClickEvent) { if (clickCallback) clickCallback(); };
		virtual void handleRelease(MouseReleaseEvent) { if (releaseCallback) releaseCallback(); };
		virtual void handleHover(MouseHoverEvent) { if (hoverCallback) hoverCallback(); };
		virtual void handleMove(MouseMoveEvent) { if (moveCallback) moveCallback(); };

		void onClick(MouseClickEvent mouseEvent);
		void onRelease(MouseReleaseEvent mouseEvent);
		void onHover(MouseHoverEvent mouseEvent);
		void onMove(MouseMoveEvent mouseEvent);

	public:
		Node(Rectangle rec, bool visible = true, bool enabled = true);
		virtual ~Node() = default;

		void draw() const;
		void resize(int width, int height);
		void update();

		void setOnClickCallback(std::function<void()> callback) { clickCallback = callback; };
		void setOnReleaseCallback(std::function<void()> callback) { releaseCallback = callback; };
		void setOnHoverCallback(std::function<void()> callback) { hoverCallback = callback; };

		void addChild(Node* node);
		void removeChild(NodeId childId);
		
		void setPosition(Vector2 position);
		void setSize(Vector2 size);
		void setCenter(Vector2 center);
		void setVisible(bool visible);

		NodeId getId() const;
		Vector2 getPosition() const;
		Vector2 getSize() const;
		Vector2 getCenter() const;

		bool isEnabled() const;
		bool isVisible() const;
		bool collides(Vector2 point) const;
		bool isMouseOver() const;
	};
}