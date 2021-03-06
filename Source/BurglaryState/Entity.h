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

#ifndef GRG_ENTITY_H
#define GRG_ENTITY_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <memory>
#include <string>
#include <map>

namespace sf
{
	class RenderTarget;
};

namespace Blackguard
{
	struct TileObject;
	namespace BurglaryState
	{
		struct BoundingBox;
		class Player;
		class EntityWorldInterface;
		
		struct BoundingBox
		{
			bool intersects(const BoundingBox& other) const;
			BoundingBox translated(const sf::Vector2f& by) const;
			void updatePosition(const sf::Vector2f& entityPosition);
			sf::Vector2f size;
			sf::Vector2f position;
			sf::Vector2f center;
			sf::Vector2f offset;
		};

		struct BoundingCircle
		{
			BoundingCircle(sf::Vector2f center, float circleRadius) : position(center), radius(circleRadius) {} 
			BoundingCircle() {}
			bool contains(const sf::Vector2f& point) const;
			sf::Vector2f position;
			float radius;
		};
		
		class Entity : public std::enable_shared_from_this<Entity>
		{
		public:
			Entity();
			virtual ~Entity();
			virtual void update(float deltaTime);
			virtual void draw(sf::RenderTarget* target) const {}
			virtual void drawLight(sf::RenderTarget* target, sf::RenderStates renderStates=sf::RenderStates(sf::BlendAdd)) const {}
			virtual void drawGUI(sf::RenderTarget* target) const {}
			virtual void drawBackground(sf::RenderTarget* target) const {}
			virtual bool activate(Player& activator) { return false; }
			virtual void remove();
			virtual bool canBeRemoved() { return toBeRemoved; }
			virtual std::string getType(){ return "unknown"; };
			virtual void initializeFromTileObject(const TileObject&){};
			// Signals:
			virtual void onHitWall(){};
			virtual void onHitWallSideways(bool y){};
			virtual void onNoise(sf::Vector2f position, float strength){};
			// Setter:
			virtual void move(const sf::Vector2f& pos);
			virtual void setPosition(const sf::Vector2f& pos);
			virtual void setWorldInterface(EntityWorldInterface* interface);
			// Getter:
			virtual sf::Vector2f getPosition() const;
			virtual sf::Vector2f getMovement() const;
			virtual sf::Vector2f getCenter() const { return bounds.center; };
			virtual BoundingBox& getBounds() { return bounds; }
		protected:
			virtual void updatePosition();
			virtual void finalize(){};
			sf::Vector2f position;
			sf::Vector2f movement;
			BoundingBox bounds;
			bool toBeRemoved;
			EntityWorldInterface* world;
		};
	}
}

#endif //GRG_ENTITY_H