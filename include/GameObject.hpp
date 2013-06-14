#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <list>
#include <string>
#include <iostream>
class Scene;

class GameObject : public sf::Transformable, public sf::Drawable
{
	friend class Scene;
	public:
		GameObject();
		GameObject(std::string name);
		virtual ~GameObject();

		void setParent(GameObject * newParent);
		GameObject const * getParent()const{return parent_;};

		const std::list<GameObject*> & getChildren()const{return children_;}

		std::string name_;

		static void destroy(GameObject * gameObject);

	protected:
		virtual void update(){}

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states)const{}
		virtual void onDestroy(){}
	private:

		GameObject(const GameObject& other);
		GameObject& operator=(const GameObject& other);

	private:
		//scene graph
		GameObject * parent_;
		std::list<GameObject*> children_;

		bool toBeDestroyed_;
		void ghostDraw(sf::RenderTarget & target, sf::RenderStates states)const;
};

#endif // GAMEOBJECT_H
