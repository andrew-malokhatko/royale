#include "Node.hpp"
#include "rlgl.h"

namespace ui
{
	Node::Node(Rectangle rectangle, bool visible, bool enabled)
		:
		mId {++idCounter},
		mRec{ rectangle },
		mVisible{ visible },
		mEnabled{ enabled }
	{
	}

	void Node::draw() const
	{
		rlPushMatrix();
		rlTranslatef(mRec.x, mRec.y, 0.0f);

		drawSelf();

		for (const Node* child : mChildren)
		{
			child->draw();
		}

		rlPopMatrix();
	}

	void Node::resize(int width, int height)
	{
		resizeSelf(width, height);

		//for (Node* child : mChildren)
		//{
		//	child->resize(width, height);
		//}
	}

	void Node::update()
	{
		updateSelf();

		for (Node* child : mChildren)
		{
			child->update();
		}
	}

	void Node::addChild(Node* node)
	{
		mChildren.push_back(node);
	}

	void Node::removeChild(NodeId childId)
	{
		auto it = std::find_if(mChildren.begin(), mChildren.end(),
			[childId](const Node* child) {
				return child->mId == childId;
			}
		);

		if (it != mChildren.end())
		{
			mChildren.erase(it);
		}
	}

	Vector2 Node::getPosition() const
	{
		return { mRec.x, mRec.y };
	}

	Vector2 Node::getCenter() const
	{
		return { mRec.x + mRec.width / 2, mRec.y + mRec.height / 2 };
	}

	void Node::setPosition(Vector2 position)
	{
		mRec.x = position.x;
		mRec.y = position.y;
	}

	Vector2 Node::getSize() const
	{
		return { mRec.width, mRec.height };
	}

	void Node::setSize(Vector2 size)
	{
		mRec.width = size.x;
		mRec.height = size.y;
	}

	bool Node::isEnabled() const
	{
		return mEnabled;
	}

	bool Node::isVisible() const
	{
		return mVisible;
	}

	bool Node::collides(Vector2 point) const
	{
		return CheckCollisionPointRec(point, mRec);
	}

	bool Node::isMouseOver() const
	{
		return(CheckCollisionPointRec(GetMousePosition(), mRec));
	}
}