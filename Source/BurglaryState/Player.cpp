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

#include "Player.h"
#include "BurglaryState.h"
#include "SFML/Graphics.hpp"
#include "../GameData.h"
#include "../Game.h"

using namespace Blackguard;
using namespace Blackguard::BurglaryState;
using namespace Blackguard::Utility;

Player::Player() : Entity()
{
	this->graphics.setTexture(Game::instance->assets.textures["Player"]);
	this->bounds.size = sf::Vector2f(graphics.getTexture()->getSize());
	this->isMoving = false;
	this->isRunning = false;
	this->movingDir = South;
}

Player::~Player()
{
}

void Player::update(float deltaTime)
{
	float speed = 64.f;
	if(this->isRunning)
		speed = 128.f;

	if(this->isMoving)
		this->move(DirToVector(movingDir) * speed * deltaTime);
}

void Player::draw(sf::RenderTarget* target) const
{
	target->draw(graphics);
}

void Player::move(const sf::Vector2f& pos)
{
	Entity::move(pos);
	graphics.setPosition(position);
}

void Player::setPosition(const sf::Vector2f& pos)
{
	Entity::setPosition(pos);
	graphics.setPosition(position);
}

void Player::addEXP(int value)
{
	Game::instance->data.Player.experience += value;
}

void Player::addGold(int value)
{
	Game::instance->data.Player.gold += value;
}

int Player::getEXP() const
{
	return Game::instance->data.Player.experience;
}

int Player::getGold() const
{
	return Game::instance->data.Player.gold;
}

int Player::getLevel() const
{
	// TODO: Better Level formula. Replace placeholder.
	return Game::instance->data.Player.experience / 100;
}

bool Player::activate()
{
	auto entityManager = Game::instance->State.burglary->getEntityManager();
	BoundingBox activationRectangle = bounds.translated(DirToVector(movingDir) * 48.f);
	std::vector<EntityPtr> objects = entityManager->findEntitiesInside(activationRectangle);
	for(EntityPtr& obj : objects)
	{
		if(obj->activate(*this))
		{
			return true;
		}
	}
	return false;
}

void Player::setMoving(bool moving)
{
	this->isMoving = moving;
}

void Player::setMovingDirection(Direction dir)
{
	if(dir != Stop)
		this->movingDir = dir;
}

void Player::setRunning(bool running)
{
	this->isRunning = running;
}