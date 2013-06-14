#ifndef SCENE_H
#define SCENE_H

#include "Manager.hpp"
#include "GameObject.hpp"
#include "TileGraphic.hpp"
#include <vector>
#include <memory>
#include <string>
class Game;

class Scene : public Manager
{
	friend class Game;
	public:
		static Scene& instance()
		{
			static Scene INSTANCE;
			return INSTANCE;
		}
		virtual ~Scene();

		template<typename T>
		T * createGameObject(std::string name)
		{
			auto * gameObject = new T(name);
			gameObject->parent_ = root_;
			root_->children_.push_back(gameObject);
			gameObjects_.push_back(gameObject);
			return gameObject;
		}

		GameObject * getRoot() {return root_;}

		int getObjectCount()const{return gameObjects_.size();}

        /** \brief Delete gameobject that are marked for destroy
         *
         * \param
         * \param
         * \return
         *
         */

		void cleanup();
	protected:
	private:
		Scene();


		void update();
		void draw();

		sf::RenderWindow * window_;
		GameObject * root_;
		std::vector<GameObject*> gameObjects_;

/** \brief Find GameoOjects by predicate
 *
 * \param
 * \param
 * \return
 *
 */
		template<typename Func>
		std::vector<GameObject*> findGameObjects(Func func);

};

#endif // SCENE_H
