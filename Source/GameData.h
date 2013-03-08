/*
 *   Copyright 2013 Manuel Riecke <m.riecke@mrbeast.org>
 *   Copyright 2013 Raffael Zica <raffael@trollgames.de>
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

#ifndef GRG_GAMEDATA_H
#define GRG_GAMEDATA_H

namespace Blackguard
{
	/** Persistent data across multiple game states. This is the data that would be saved in Savegames. */
	struct GameData
	{
		struct // Player
		{
			int experience;
			int level;
			int gold;
			// TODO Skills
			// TODO Equipment
			// TODO Inventory
		} Player;

		struct // World
		{
			// TODO
		} World;
	};
}

#endif // GRG_GAMEDATA_H
