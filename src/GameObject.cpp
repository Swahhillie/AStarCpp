#include "GameObject.hpp"
#include "Scene.hpp"
#include <assert.h>
#include <iostream>

GameObject::GameObject():
	name_("GameObject"),
	toBeDestroyed_(false)
{
	//ctor
	name_ = "GameObject";
}
GameObject::GameObject(std::string name)
: name_(name),
toBeDestroyed_(false)
{

}
GameObject::~GameObject()
{
	//dtor
	//std::cout << "Called delete on a " << name_ << std::endl;
}

GameObject::GameObject(const GameObject& other)
{
	//copy ctor
}

GameObject& GameObject::operator=(const GameObject& rhs)
{
	if (this == &rhs) return *this; // handle self assignment
	//assignment operator
	return *this;
}

void GameObject::setParent(GameObject * newParent)
{
	//only the root_ may have no parent. calling set parent on the root will cause a crash
	assert(parent_ != nullptr);

	if(newParent == nullptr)
	{
		parent_->children_.remove(this);
		GameObject * root = Scene::instance().getRoot();
		root->children_.push_back(this);
		parent_ = root;
	}
	else
	{
		parent_->children_.remove(this);
		newParent->children_.push_back(this);
		parent_ = newParent;
	}


}
void GameObject::destroy(GameObject * gameObject)
{
	//std::cout << "GameObject::destroy called on " << gameObject->name_ << std::endl;
	gameObject->toBeDestroyed_ = true;
	gameObject->onDestroy();

	//for(auto* go : gameObject->children_)
	for(auto it = gameObject->children_.rbegin(); it != gameObject->children_.rend(); it++)
	{
		GameObject::destroy(*it);
	}

}
void GameObject::ghostDraw(sf::RenderTarget& window, sf::RenderStates states)const
{
	states.transform *= getTransform();
	for(auto * go : children_)
	{
		go->ghostDraw(window, states);
	}
	draw(window, states);
}
