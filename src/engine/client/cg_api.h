/*
===========================================================================

Daemon GPL Source Code
Copyright (C) 2011  Dusan Jocic <dusanjocic@msn.com>

Daemon is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

Daemon is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

===========================================================================
*/

// Definitions used in engine/cgame communication
#ifndef CGAPI_H
#define CGAPI_H

#include "engine/qcommon/q_shared.h"
#ifdef BUILD_CGAME
// TODO: find a better way that does not depend on a gamelogic file from an engine file
#include "shared/bg_public.h"
#endif

#define CGAME_API_VERSION 3

#define CMD_BACKUP               64
#define CMD_MASK                 ( CMD_BACKUP - 1 )
// allow a lot of command backups for very fast systems
// multiple commands may be combined into a single packet, so this
// needs to be larger than PACKET_BACKUP

// snapshots are a view of the server at a given time

// Snapshots are generated at regular time intervals by the server,
// but they may not be sent if a client's rate level is exceeded, or
// they may be dropped by the network.
struct snapshot_t
{
	int           snapFlags; // SNAPFLAG_RATE_DELAYED, etc
	int           ping;

	int           serverTime; // server time the message is valid for (in msec)

	byte          areamask[ MAX_MAP_AREA_BYTES ]; // portalarea visibility bits

#ifdef BUILD_CGAME
	playerState_t ps; // complete information about the current player at this time
#else
	OpaquePlayerState ps;
#endif

	// all of the entities that need to be presented at the time of this snapshot
	std::vector<entityState_t> entities;

	// text based server commands to execute when this snapshot becomes current
	std::vector<std::string> serverCommands;
};

struct cgClientState_t
{
	connstate_t connState;
	int         connectPacketCount;
	int         clientNum;
	char        servername[ MAX_STRING_CHARS ];
	char        updateInfoString[ MAX_STRING_CHARS ];
	char        messageString[ MAX_STRING_CHARS ];
};

enum class MouseMode
{
	Deltas,       // The input is sent as movement deltas, the cursor is hidden
	CustomCursor, // The input is sent as positions, the cursor should be rendered by the game
	SystemCursor, // The input is sent as positions, the cursor should be rendered by the system
};

#endif
