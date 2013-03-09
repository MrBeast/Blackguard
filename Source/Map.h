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
#include "EntityTypes.h"
#include "SFML/Window.hpp"

namespace Blackguard
{
	class Map
	{
	public:
		Map();
		std::string generateID();
		void add(std::string id, EntityPtr entity);
		void remove(std::string id);
		void update(float deltaTime);
		void draw();
		void processEvent(sf::Event& evt);
	private:
		void cleanup();
	private:
		std::map<std::string,EntityPtr> objects;
		std::stack<std::string> disposedObjects;
		int idCounter;
	};
}

#endif //GRG_MAP_H