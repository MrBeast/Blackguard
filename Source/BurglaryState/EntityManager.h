/*
 *   Copyright 2013 Manuel Riecke <m.riecke@mrbeast.org>
 *   Copyright 2013 Raffael Zica <sirjson133@gmail.com>
 *
 *   This software is provided 'as-is', without any express or implied
 *   warranty.  In no event will the authors be held liable for any damages
 *   arising from the use of this software.
 *
 *   Permission is granted to anyone to use this software for any purpose,
 *   including commercial applications, and to alter it and redistribute it
 *   freely, subject to the following restrictions:
 *
 *   1. The origin of this software must not be misrepresented; you must not
 *      claim that you wrote the original software. If you use this software
 *      in a product, an acknowledgment in the product documentation would be
 *      appreciated but is not required.
 *   2. Altered source versions must be plainly marked as such, and must not be
 *      misrepresented as being the original software.
 *   3. This notice may not be removed or altered from any source distribution.
 */

#ifndef GRG_MAP_H
#define GRG_MAP_H

#include <map>
#include <string>
#include <stack>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Entity.h"

namespace Blackguard
{
	namespace BurglaryState
	{
	class EntityManager
	{
		public:
			EntityManager();
			void add(Blackguard::BurglaryState::Entity* ptr);
			void addNamed(std::string id, Blackguard::BurglaryState::Entity* entity);
			void update(float deltaTime);
			void draw(sf::RenderTarget* target);
			std::vector<EntityPtr> getByType(const std::string& type);
			std::vector<EntityPtr> getInRect(const Blackguard::BurglaryState::BoundingBox& area);
			EntityPtr getNamed(const std::string& name);
		private:
			void cleanup();
		private:
			typedef std::vector<EntityPtr> EntityList;
			EntityList objects;
			std::map<std::string, EntityPtr>  namedObjects;
			std::map<std::string, EntityList> objectsByType;
			int idCounter;
		};
	}
}

#endif //GRG_MAP_H