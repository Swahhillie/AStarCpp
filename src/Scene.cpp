#include "Scene.hpp"
#include "UnitTest++.h"
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <sstream>
#include "CameraController.hpp"
#include "Game.hpp"

Scene::Scene()
{
	//ctor
	root_ = new GameObject("Root");
}

Scene::~Scene()
{
	//dtor
	for(auto go : gameObjects_)
	{
		GameObject::destroy(go);
	}

	cleanup();

	delete root_;
}
void Scene::start()
{
	createGameObject<CameraController>("cameraController");
	bool result = font_.loadFromFile("assets/arial.ttf");
	assert(result);
	debugText_ = sf::Text("debug", font_);
}
void Scene::update()
{
	for(auto* go : gameObjects_)
	{
		go->update();
	}
	cleanup();
}

void Scene::cleanup()
{
	auto toBeDestroyed = findGameObjects([](GameObject & go){return (go.toBeDestroyed_ == true);});
	for(auto it = toBeDestroyed.rbegin(); it != toBeDestroyed.rend(); it++)
	{
		auto* go = *it;
		go->setParent(nullptr);
		auto rootIt = std::find(root_->children_.begin(), root_->children_.end(), go);
		auto gameObjectsIt = std::find(gameObjects_.begin(), gameObjects_.end(), go);

		//the scene graph must contain this object
		assert(rootIt != root_->children_.end());

		//the list of all gameobjects must contain this object
		assert(gameObjectsIt != gameObjects_.end());

		//remove from scene graph
		root_->children_.erase(rootIt);

		//remove from all gameobjects
		gameObjects_.erase(gameObjectsIt);
		delete go;

	}
}
void Scene::preRender(sf::RenderWindow & window)
{
	static bool ini =false;
	if(!ini)
	{
		ini = true;
		view_ = window.getDefaultView();
	}
	window.clear();
	window.setView(view_);
}
void Scene::draw(sf::RenderWindow & window)
{

	root_->ghostDraw(window, sf::RenderStates::Default);

	window.setView(window.getDefaultView());
	window.draw(debugText_);
	window.setView(view_);

}
sf::RenderWindow & Scene::getWindow()const
{
	return Game::instance().getWindow();
}
void Scene::lateDraw(sf::RenderWindow & window)
{

	window.display();
}
template<typename Func>
std::vector<GameObject *> Scene::findGameObjects(Func func)
{
	std::vector<GameObject *> results;
	for(auto * go : gameObjects_)
	{
		if(func(*go))
		{
			results.push_back(go);
		}
	}
	return results;
}

TEST(createdGameobjectsAreChildOfRoot)
{
	Scene & scene = Scene::instance();
	auto * root = scene.getRoot();
	auto * obj1 = scene.createGameObject<GameObject>("obj1");

	CHECK(obj1->getParent() == root);

	GameObject::destroy(obj1);
	scene.cleanup();

}
TEST(setParentOfGameObject)
{

	Scene & scene = Scene::instance();
	auto * parent = scene.createGameObject<GameObject>("Parent");
	auto * child = scene.createGameObject<GameObject>("Child");

	child->setParent(parent);

	CHECK_EQUAL(parent, child->getParent());

	GameObject::destroy(child);
	GameObject::destroy(parent);
	scene.cleanup();

}
TEST(creationIsAddedToScene)
{
	Scene & scene = Scene::instance();
	auto * obj1 = scene.createGameObject<GameObject>("obj1");
	const std::list<GameObject*> & rootChildren = scene.getRoot()->getChildren();
	CHECK(std::find(rootChildren.begin(), rootChildren.end(), obj1) != rootChildren.end());
	GameObject::destroy(obj1);
	scene.cleanup();
}
TEST(creationGetsDestroyed)
{
	Scene & scene = Scene::instance();
	//make sure the scene is currently empty
	auto initialObjectCount = scene.getObjectCount();

	auto * obj1 = scene.createGameObject<GameObject>("obj1");
	assert(scene.getObjectCount() == initialObjectCount + 1); // must have been added
	GameObject::destroy(obj1);
	assert(scene.getObjectCount() == initialObjectCount + 1); // cannot yet be destroyed
	scene.cleanup();
	CHECK_EQUAL(initialObjectCount, scene.getObjectCount()); // must be destroyed and removed
}
TEST(childrenGetDeletedWithParent)
{


	Scene & scene = Scene::instance();

	auto initialObjectCount = scene.getObjectCount();

	auto * parent = scene.createGameObject<GameObject>("grandpa");
	assert(parent->getChildren().size() == 0);

	auto * child0 = scene.createGameObject<GameObject>("firstChild");
	auto * child1 = scene.createGameObject<GameObject>("secondChild");
	child0->setParent(parent);
	child1->setParent(parent);

	//std::cout << "parent has " << parent->getChildren().size() << " children " << std::endl;
	GameObject::destroy(parent);
	scene.cleanup();
	CHECK(scene.getObjectCount() == initialObjectCount);
}

TEST(nestedChildrenDeletedWithParent)
{


	int amount = 5;
	Scene & scene = Scene::instance();

	auto initialObjectCount = scene.getObjectCount();

	GameObject * grandparent = scene.createGameObject<GameObject>("grandpa");
	GameObject * parent = grandparent;

	for(auto i = 0; i < amount; i++)
	{
		std::stringstream sstream;
		sstream << i;
		GameObject * child = scene.createGameObject<GameObject>("child" + sstream.str());
		child->setParent(parent);
		parent = child;
	}


	assert(scene.getObjectCount() == initialObjectCount + amount + 1); //whatever was already there + children + the grandparent
	//std::cout << "Grandpa has " << grandparent->getChildren().size() << " children " << std::endl;
	GameObject::destroy(grandparent);
	scene.cleanup();
	CHECK(scene.getObjectCount() == initialObjectCount);
}
