/*
===========================================================================
Daemon BSD Source Code
Copyright (c) 2013-2014, Daemon Developers
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Daemon developers nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL DAEMON DEVELOPERS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
===========================================================================
*/

#include "cg_local.h"

#include "../shared/VMMain.h"
#include "../shared/CommonProxies.h"

// Symbols required by the shqred VMMqin code

int VM::VM_API_VERSION = CGAME_API_VERSION;

void VM::VMInit() {
    // Nothing to do right now
}

void VM::VMHandleSyscall(uint32_t id, IPC::Reader reader) {
    // Nothing here, TODO
}

// Definition of the VM->Engine calls

// All Miscs

int trap_GetDemoState( void )
{
	int state;
	VM::SendMsg<GetDemoStateMsg>(state);
	return state;
}

int trap_GetDemoPos( void )
{
	int pos;
	VM::SendMsg<GetDemoPosMsg>(pos);
	return pos;
}

void trap_SendClientCommand( const char *s )
{
	VM::SendMsg<SendClientCommandMsg>(s);
}

void trap_UpdateScreen( void )
{
	VM::SendMsg<UpdateScreenMsg>();
}

int trap_CM_MarkFragments( int numPoints, const vec3_t *points, const vec3_t projection, int maxPoints, vec3_t pointBuffer, int maxFragments, markFragment_t *fragmentBuffer )
{
	std::vector<std::array<float, 3>> mypoints(numPoints);
	std::array<float, 3> myproj;
	memcpy((float*)mypoints.data(), points, sizeof(float) * 3 * numPoints);
	VectorCopy(projection, myproj.data());

	std::vector<std::array<float, 3>> mypointBuffer;
	std::vector<markFragment_t> myfragmentBuffer;
	VM::SendMsg<CMMarkFragmentsMsg>(mypoints, myproj, maxPoints, maxFragments, mypointBuffer, myfragmentBuffer);

	memcpy(pointBuffer, mypointBuffer.data(), sizeof(float) * 3 * maxPoints);
	memcpy(fragmentBuffer, myfragmentBuffer.data(), sizeof(markFragment_t) * maxFragments);
	return 0;
}

int trap_RealTime( qtime_t *qtime )
{
	int res;
	VM::SendMsg<RealTimeMsg>(res, *qtime);
	return res;
}

void trap_GetGlconfig( glconfig_t *glconfig )
{
	VM::SendMsg<GetGLConfigMsg>(*glconfig);
}

void trap_GetGameState( gameState_t *gamestate )
{
	VM::SendMsg<GetGameStateMsg>(*gamestate);
}

void trap_GetClientState( cgClientState_t *cstate )
{
	VM::SendMsg<GetClientStateMsg>(*cstate);
}

void trap_GetCurrentSnapshotNumber( int *snapshotNumber, int *serverTime )
{
	VM::SendMsg<GetCurrentSnapshotNumberMsg>(*snapshotNumber, *serverTime);
}

qboolean trap_GetSnapshot( int snapshotNumber, snapshot_t *snapshot )
{
	bool res;
	VM::SendMsg<GetSnapshotMsg>(snapshotNumber, res, *snapshot);
	return res;
}

qboolean trap_GetServerCommand( int serverCommandNumber )
{
	bool res;
	VM::SendMsg<GetServerCommandMsg>(serverCommandNumber, res);
	return res;
}

int trap_GetCurrentCmdNumber( void )
{
	int res;
	VM::SendMsg<GetCurrentCmdNumberMsg>(res);
	return res;
}

qboolean trap_GetUserCmd( int cmdNumber, usercmd_t *ucmd )
{
	bool res;
	VM::SendMsg<GetUserCmdMsg>(cmdNumber, res, *ucmd);
	return res;
}

void trap_SetUserCmdValue( int stateValue, int flags, float sensitivityScale, int mpIdentClient )
{
	VM::SendMsg<SetUserCmdValueMsg>(stateValue, flags, sensitivityScale, mpIdentClient);
}

void trap_SetClientLerpOrigin( float x, float y, float z )
{
	VM::SendMsg<SetClientLerpOriginMsg>(x, y, z);
}

qboolean trap_GetEntityToken( char *buffer, int bufferSize )
{
	bool res;
	std::string token;
	VM::SendMsg<GetEntityTokenMsg>(bufferSize, res, token);
	Q_strncpyz(buffer, token.c_str(), bufferSize);
	return res;
}

void trap_GetDemoName( char *buffer, int size )
{
	std::string name;
	VM::SendMsg<GetDemoNameMsg>(size, name);
	Q_strncpyz(buffer, name.c_str(), size);
}

void trap_RegisterButtonCommands( const char *cmds )
{
	VM::SendMsg<RegisterButtonCommandsMsg>(cmds);
}

void trap_GetClipboardData( char *buf, int bufsize, clipboard_t clip )
{
	std::string data;
	VM::SendMsg<GetClipboardDataMsg>(bufsize, clip, data);
	Q_strncpyz(buf, data.c_str(), bufsize);
}

void trap_QuoteString( const char *str, char *buffer, int size )
{
	std::string quoted;
	VM::SendMsg<QuoteStringMsg>(size, str, quoted);
	Q_strncpyz(buffer, quoted.c_str(), size);
}

void trap_Gettext( char *buffer, const char *msgid, int bufferLength )
{
	std::string result;
	VM::SendMsg<GettextMsg>(bufferLength, msgid, result);
	Q_strncpyz(buffer, result.c_str(), bufferLength);
}

void trap_Pgettext( char *buffer, const char *ctxt, const char *msgid, int bufferLength )
{
	std::string result;
	VM::SendMsg<PGettextMsg>(bufferLength, ctxt, msgid, result);
	Q_strncpyz(buffer, result.c_str(), bufferLength);
}

void trap_GettextPlural( char *buffer, const char *msgid, const char *msgid2, int number, int bufferLength )
{
	std::string result;
	VM::SendMsg<GettextPluralMsg>(bufferLength, msgid, msgid2, number, result);
	Q_strncpyz(buffer, result.c_str(), bufferLength);
}

void trap_notify_onTeamChange( int newTeam )
{
	VM::SendMsg<NotifyTeamChangeMsg>(newTeam);
}

void trap_PrepareKeyUp( void )
{
	VM::SendMsg<PrepareKeyUpMsg>();
}

qboolean trap_GetNews( qboolean force )
{
	bool res;
	VM::SendMsg<GetNewsMsg>(force, res);
	return res;
}

// All Sounds

void trap_S_StartSound( vec3_t origin, int entityNum, int, sfxHandle_t sfx )
{
	std::array<float, 3> myorigin;
	VectorCopy(origin, myorigin.data());
	VM::SendMsg<Audio::StartSoundMsg>(myorigin, entityNum, sfx);
}

void trap_S_StartLocalSound( sfxHandle_t sfx, int )
{
	VM::SendMsg<Audio::StartLocalSoundMsg>(sfx);
}

void trap_S_ClearLoopingSounds( qboolean )
{
	VM::SendMsg<Audio::ClearLoopingSoundsMsg>();
}

void trap_S_AddLoopingSound( int entityNum, const vec3_t origin, const vec3_t velocity, sfxHandle_t sfx )
{
	if (origin) {
		trap_S_UpdateEntityPosition(entityNum, origin);
	}
	if (velocity) {
		trap_S_UpdateEntityVelocity(entityNum, velocity);
	}
	VM::SendMsg<Audio::AddLoopingSoundMsg>(entityNum, sfx);
}

void trap_S_AddRealLoopingSound( int entityNum, const vec3_t origin, const vec3_t velocity, sfxHandle_t sfx )
{
	trap_S_AddLoopingSound(entityNum, origin, velocity, sfx);
}

void trap_S_StopLoopingSound( int entityNum )
{
	VM::SendMsg<Audio::StopLoopingSoundMsg>(entityNum);
}

void trap_S_UpdateEntityPosition( int entityNum, const vec3_t origin )
{
	std::array<float, 3> myposition;
	VectorCopy(origin, myposition.data());
	VM::SendMsg<Audio::UpdateEntityPositionMsg>(entityNum, myposition);
}

void trap_S_Respatialize( int entityNum, const vec3_t origin, vec3_t axis[ 3 ], int )
{
	if (origin) {
		trap_S_UpdateEntityPosition(entityNum, origin);
	}
	std::array<float, 9> myaxis;
	memcpy(myaxis.data(), axis, sizeof(float) * 9);
	VM::SendMsg<Audio::RespatializeMsg>(entityNum, myaxis);
}

sfxHandle_t trap_S_RegisterSound( const char *sample, qboolean)
{
	int sfx;
	VM::SendMsg<Audio::RegisterSoundMsg>(sample, sfx);
	return sfx;
}

void trap_S_StartBackgroundTrack( const char *intro, const char *loop )
{
	VM::SendMsg<Audio::StartBackgroundTrackMsg>(intro, loop);
}

void trap_S_StopBackgroundTrack( void )
{
	VM::SendMsg<Audio::StopBackgroundTrackMsg>();
}

void trap_S_UpdateEntityVelocity( int entityNum, const vec3_t velocity )
{
	std::array<float, 3> myvelocity;
	VectorCopy(velocity, myvelocity.data());
	VM::SendMsg<Audio::UpdateEntityVelocityMsg>(entityNum, myvelocity);
}

void trap_S_SetReverb( int slotNum, const char* name, float ratio )
{
	VM::SendMsg<Audio::SetReverbMsg>(slotNum, name, ratio);
}

void trap_S_BeginRegistration( void )
{
	VM::SendMsg<Audio::BeginRegistrationMsg>();
}

void trap_S_EndRegistration( void )
{
	VM::SendMsg<Audio::EndRegistrationMsg>();
}

// All renderer

void trap_R_SetAltShaderTokens( const char *str )
{
	VM::SendMsg<Render::SetAltShaderTokenMsg>(str);
}

void trap_R_GetShaderNameFromHandle( const qhandle_t shader, char *out, int len )
{
	std::string result;
	VM::SendMsg<Render::GetShaderNameFromHandleMsg>(shader, result);
	Q_strncpyz(out, result.c_str(), len);
}

void trap_R_ScissorEnable( qboolean enable )
{
	VM::SendMsg<Render::ScissorEnableMsg>(enable);
}

void trap_R_ScissorSet( int x, int y, int w, int h )
{
	VM::SendMsg<Render::ScissorSetMsg>(x, y, w, h);
}

qboolean trap_R_inPVVS( const vec3_t p1, const vec3_t p2 )
{
	bool res;
	std::array<float, 3> myp1, myp2;
	VectorCopy(p1, myp1.data());
	VectorCopy(p2, myp2.data());
	VM::SendMsg<Render::InPVVSMsg>(myp1, myp2, res);
	return res;
}

void trap_R_LoadWorldMap( const char *mapname )
{
	VM::SendMsg<Render::LoadWorldMapMsg>(mapname);
}

qhandle_t trap_R_RegisterModel( const char *name )
{
	int handle;
	VM::SendMsg<Render::RegisterModelMsg>(name, handle);
	return handle;
}

qhandle_t trap_R_RegisterSkin( const char *name )
{
	int handle;
	VM::SendMsg<Render::RegisterSkinMsg>(name, handle);
	return handle;
}

qhandle_t trap_R_RegisterShader( const char *name, RegisterShaderFlags_t flags )
{
	int handle;
	VM::SendMsg<Render::RegisterShaderMsg>(name, flags, handle);
	return handle;
}

void trap_R_RegisterFont( const char *fontName, const char *fallbackName, int pointSize, fontMetrics_t *font )
{
	VM::SendMsg<Render::RegisterFontMsg>(fontName, fallbackName, pointSize, *font);
}

void trap_R_ClearScene( void )
{
	VM::SendMsg<Render::ClearSceneMsg>();
}

void trap_R_AddRefEntityToScene( const refEntity_t *re )
{
	VM::SendMsg<Render::AddRefEntityToSceneMsg>(*re);
}

void trap_R_AddPolyToScene( qhandle_t hShader, int numVerts, const polyVert_t *verts )
{
	std::vector<polyVert_t> myverts(numVerts);
	memcpy(myverts.data(), verts, numVerts * sizeof(polyVert_t));
	VM::SendMsg<Render::AddPolyToSceneMsg>(hShader, myverts);
}

void trap_R_AddPolysToScene( qhandle_t hShader, int numVerts, const polyVert_t *verts, int numPolys )
{
	std::vector<polyVert_t> myverts(numVerts);
	memcpy(myverts.data(), verts, numVerts * sizeof(polyVert_t));
	VM::SendMsg<Render::AddPolysToSceneMsg>(hShader, myverts, numPolys);
}

void trap_R_AddLightToScene( const vec3_t org, float radius, float intensity, float r, float g, float b, qhandle_t hShader, int flags )
{
	std::array<float, 3> myorg;
	VectorCopy(org, myorg.data());
	VM::SendMsg<Render::AddLightToSceneMsg>(myorg, radius, intensity, r, g, b, hShader, flags);
}

void trap_R_AddAdditiveLightToScene( const vec3_t org, float intensity, float r, float g, float b )
{
	std::array<float, 3> myorg;
	VectorCopy(org, myorg.data());
	VM::SendMsg<Render::AddAdditiveLightToSceneMsg>(myorg, intensity, r, g, b);
}

void trap_R_RenderScene( const refdef_t *fd )
{
	VM::SendMsg<Render::RenderSceneMsg>(*fd);
}

void trap_R_SetColor( const float *rgba )
{
	std::array<float, 4> myrgba;
	memcpy(myrgba.data(), rgba, 4 * sizeof(float));
	VM::SendMsg<Render::SetColorMsg>(myrgba);
}

void trap_R_SetClipRegion( const float *region )
{
	std::array<float, 4> myregion;
	memcpy(myregion.data(), region, 4 * sizeof(float));
	VM::SendMsg<Render::SetClipRegionMsg>(myregion);
}

void trap_R_DrawStretchPic( float x, float y, float w, float h, float s1, float t1, float s2, float t2, qhandle_t hShader )
{
	VM::SendMsg<Render::DrawStretchPicMsg>(x, y, w, h, s1, t1, s2, t2, hShader);
}

void trap_R_DrawRotatedPic( float x, float y, float w, float h, float s1, float t1, float s2, float t2, qhandle_t hShader, float angle )
{
	VM::SendMsg<Render::DrawRotatedPicMsg>(x, y, w, h, s1, t1, s2, t2, hShader, angle);
}

void trap_R_ModelBounds( clipHandle_t model, vec3_t mins, vec3_t maxs )
{
	std::array<float, 3> mymins, mymaxs;
	VM::SendMsg<Render::ModelBoundsMsg>(model, mymins, mymaxs);
	VectorCopy(mymins.data(), mins);
	VectorCopy(mymaxs.data(), maxs);
}

int trap_R_LerpTag( orientation_t *tag, const refEntity_t *refent, const char *tagName, int startIndex )
{
	int result;
	VM::SendMsg<Render::LerpTagMsg>(*refent, tagName, startIndex, *tag, result);
	return result;
}

void trap_R_RemapShader( const char *oldShader, const char *newShader, const char *timeOffset )
{
	VM::SendMsg<Render::RemapShaderMsg>(oldShader, newShader, timeOffset);
}

qboolean trap_R_inPVS( const vec3_t p1, const vec3_t p2 )
{
	bool res;
	std::array<float, 3> myp1, myp2;
	VectorCopy(p1, myp1.data());
	VectorCopy(p2, myp2.data());
	VM::SendMsg<Render::InPVSMsg>(myp1, myp2, res);
	return res;
}

int trap_R_LightForPoint( vec3_t point, vec3_t ambientLight, vec3_t directedLight, vec3_t lightDir )
{
	int result;
	std::array<float, 3> mypoint, myambient, mydirected, mydir;
	VectorCopy(point, mypoint.data());
	VM::SendMsg<Render::LightForPointMsg>(mypoint, myambient, mydirected, mydir, result);
	VectorCopy(myambient.data(), ambientLight);
	VectorCopy(mydirected.data(), directedLight);
	VectorCopy(mydir.data(), lightDir);
	return result;
}

qhandle_t trap_R_RegisterAnimation( const char *name )
{
	int handle;
	VM::SendMsg<Render::RegisterAnimationMsg>(name, handle);
	return handle;
}

int trap_R_BuildSkeleton( refSkeleton_t *skel, qhandle_t anim, int startFrame, int endFrame, float frac, qboolean clearOrigin )
{
	int result;
	VM::SendMsg<Render::BuildSkeletonMsg>(anim, startFrame, endFrame, frac, clearOrigin, *skel, result);
	return result;
}

int trap_R_BlendSkeleton( refSkeleton_t *skel, const refSkeleton_t *blend, float frac )
{
	int result;
	VM::SendMsg<Render::BlendSkeletonMsg>(*skel, *blend, frac, *skel, result);
	return result;
}

int trap_R_BoneIndex( qhandle_t hModel, const char *boneName )
{
	int index;
	VM::SendMsg<Render::BoneIndexMsg>(hModel, boneName, index);
	return index;
}

int trap_R_AnimNumFrames( qhandle_t hAnim )
{
	int n;
	VM::SendMsg<Render::AnimNumFramesMsg>(hAnim, n);
	return n;
}

int trap_R_AnimFrameRate( qhandle_t hAnim )
{
	int n;
	VM::SendMsg<Render::AnimFrameRateMsg>(hAnim, n);
	return n;
}

qhandle_t trap_RegisterVisTest( void )
{
	int handle;
	VM::SendMsg<Render::RegisterVisTestMsg>(handle);
	return handle;
}

void trap_AddVisTestToScene( qhandle_t hTest, vec3_t pos, float depthAdjust, float area )
{
	std::array<float, 3> mypos;
	VectorCopy(pos, mypos.data());
	VM::SendMsg<Render::AddVisTestToSceneMsg>(hTest, mypos, depthAdjust, area);
}

float trap_CheckVisibility( qhandle_t hTest )
{
	float result;
	VM::SendMsg<Render::CheckVisibilityMsg>(hTest, result);
	return result;
}

void trap_UnregisterVisTest( qhandle_t hTest )
{
	VM::SendMsg<Render::UnregisterVisTestMsg>(hTest);
}

void trap_SetColorGrading( int slot, qhandle_t hShader )
{
	VM::SendMsg<Render::SetColorGradingMsg>(slot, hShader);
}

// All keys

int trap_Key_GetCatcher( void )
{
	int result;
	VM::SendMsg<Key::GetCatcherMsg>(result);
	return result;
}

void trap_Key_SetCatcher( int catcher )
{
	VM::SendMsg<Key::SetCatcherMsg>(catcher);
}

void trap_Key_GetBindingBuf( int keynum, int team, char *buf, int buflen )
{
	std::string result;
	VM::SendMsg<Key::GetBindingBufMsg>(keynum, team, buflen, result);
	Q_strncpyz(buf, result.c_str(), buflen);
}

void trap_Key_KeynumToStringBuf( int keynum, char *buf, int buflen )
{
	std::string result;
	VM::SendMsg<Key::KeyNumToStringMsg>(keynum, buflen, result);
	Q_strncpyz(buf, result.c_str(), buflen);
}

// All LAN

int trap_LAN_GetServerCount( int source )
{
	int count;
	VM::SendMsg<LAN::GetServerCountMsg>(source, count);
	return count;
}

void trap_LAN_GetServerInfo( int source, int n, char *buf, int buflen )
{
	std::string info;
	VM::SendMsg<LAN::GetServerInfoMsg>(source, n, buflen, info);
	Q_strncpyz(buf, info.c_str(), buflen);
}

int trap_LAN_GetServerPing( int source, int n )
{
	int ping;
	VM::SendMsg<LAN::GetServerPingMsg>(source, n, ping);
	return ping;
}

void trap_LAN_MarkServerVisible( int source, int n, qboolean visible )
{
	VM::SendMsg<LAN::MarkServerVisibleMsg>(source, n, visible);
}

int trap_LAN_ServerIsVisible( int source, int n )
{
	bool visible;
	VM::SendMsg<LAN::ServerIsVisibleMsg>(source, n, visible);
	return visible;
}

qboolean trap_LAN_UpdateVisiblePings( int source )
{
	bool res;
	VM::SendMsg<LAN::UpdateVisiblePingsMsg>(source, res);
	return res;
}

void trap_LAN_ResetPings( int n )
{
	VM::SendMsg<LAN::ResetPingsMsg>(n);
}

int trap_LAN_ServerStatus( const char *serverAddress, char *serverStatus, int maxLen )
{
	std::string status;
	int res;
	VM::SendMsg<LAN::ServerStatusMsg>(serverAddress, maxLen, status, res);
	Q_strncpyz(serverStatus, status.c_str(), maxLen);
	return res;
}

// All rocket

void trap_Rocket_Init( void )
{
	VM::SendMsg<Rocket::InitMsg>();
}

void trap_Rocket_Shutdown( void )
{
	VM::SendMsg<Rocket::ShutdownMsg>();
}

void trap_Rocket_LoadDocument( const char *path )
{
	VM::SendMsg<Rocket::LoadDocumentMsg>(path);
}

void trap_Rocket_LoadCursor( const char *path )
{
	VM::SendMsg<Rocket::LoadCursorMsg>(path);
}

void trap_Rocket_DocumentAction( const char *name, const char *action )
{
	VM::SendMsg<Rocket::DocumentActionMsg>(name, action);
}

qboolean trap_Rocket_GetEvent( void )
{
	bool result;
	VM::SendMsg<Rocket::GetEventMsg>(result);
	return result;
}

void trap_Rocket_DeleteEvent( void )
{
	VM::SendMsg<Rocket::DeleteEventMsg>();
}

void trap_Rocket_RegisterDataSource( const char *name )
{
	VM::SendMsg<Rocket::RegisterDataSourceMsg>(name);
}

void trap_Rocket_DSAddRow( const char *name, const char *table, const char *data )
{
	VM::SendMsg<Rocket::DSAddRowMsg>(name, table, data);
}

void trap_Rocket_DSClearTable( const char *name, const char *table )
{
	VM::SendMsg<Rocket::DSClearTableMsg>(name, table);
}

void trap_Rocket_SetInnerRML( const char *RML, int parseFlags )
{
	VM::SendMsg<Rocket::SetInnerRMLMsg>(RML, parseFlags);
}

void trap_Rocket_GetAttribute( const char *attribute, char *out, int length )
{
	std::string result;
	VM::SendMsg<Rocket::GetAttributeMsg>(attribute, length, result);
	Q_strncpyz((char*)out, result.c_str(), length);
}

void trap_Rocket_SetAttribute( const char *attribute, const char *value )
{
	VM::SendMsg<Rocket::SetAttributeMsg>(attribute, value);
}

void trap_Rocket_GetProperty( const char *name, void *out, int len, rocketVarType_t type )
{
	std::string result;
	VM::SendMsg<Rocket::GetPropertyMsg>(name, type, len, result);
	Q_strncpyz((char*)out, result.c_str(), len);
}

void trap_Rocket_SetProperty( const char *property, const char *value )
{
	VM::SendMsg<Rocket::SetPropertyMsg>(property, value);
}

void trap_Rocket_GetEventParameters( char *params, int length )
{
	std::string result;
	VM::SendMsg<Rocket::GetEventParametersMsg>(length, result);
	Q_strncpyz(params, result.c_str(), length);
}

void trap_Rocket_RegisterDataFormatter( const char *name )
{
	VM::SendMsg<Rocket::RegisterDataFormatterMsg>(name);
}

void trap_Rocket_DataFormatterRawData( int handle, char *name, int nameLength, char *data, int dataLength )
{
	std::string nameResult;
	std::string dataResult;
	VM::SendMsg<Rocket::DataFormatterDataMsg>(handle, nameLength, dataLength, nameResult, dataResult);
	Q_strncpyz(name, nameResult.c_str(), nameLength);
	Q_strncpyz(data, dataResult.c_str(), dataLength);
}

void trap_Rocket_DataFormatterFormattedData( int handle, const char *data, qboolean parseQuake )
{
	VM::SendMsg<Rocket::DataFormatterFormattedDataMsg>(handle, data, parseQuake);
}

void trap_Rocket_RegisterElement( const char *tag )
{
	VM::SendMsg<Rocket::RegisterElementMsg>(tag);
}

void trap_Rocket_GetElementTag( char *tag, int length )
{
	std::string result;
	VM::SendMsg<Rocket::GetElementTagMsg>(length, result);
	Q_strncpyz(tag, result.c_str(), length);
}

void trap_Rocket_GetElementAbsoluteOffset( float *x, float *y )
{
	VM::SendMsg<Rocket::GetElementAbsoluteOffsetMsg>(*x, *y);
}

void trap_Rocket_QuakeToRML( const char *in, char *out, int length )
{
	std::string result;
	VM::SendMsg<Rocket::QuakeToRMLMsg>(in, length, result);
	Q_strncpyz(out, result.c_str(), length);
}

void trap_Rocket_SetClass( const char *in, qboolean activate )
{
	VM::SendMsg<Rocket::SetClassMsg>(in, activate);
}

void trap_Rocket_InitializeHuds( int size )
{
	VM::SendMsg<Rocket::InitHUDsMsg>(size);
}

void trap_Rocket_LoadUnit( const char *path )
{
	VM::SendMsg<Rocket::LoadUnitMsg>(path);
}

void trap_Rocket_AddUnitToHud( int weapon, const char *id )
{
	VM::SendMsg<Rocket::AddUnitToHUDMsg>(weapon, id);
}

void trap_Rocket_ShowHud( int weapon )
{
	VM::SendMsg<Rocket::ShowHUDMsg>(weapon);
}

void trap_Rocket_ClearHud( int weapon )
{
	VM::SendMsg<Rocket::ClearHUDMsg>(weapon);
}

void trap_Rocket_AddTextElement( const char *text, const char *Class, float x, float y )
{
	VM::SendMsg<Rocket::AddTextMsg>(text, Class, x, y);
}

void trap_Rocket_ClearText( void )
{
	VM::SendMsg<Rocket::ClearTextMsg>();
}

void trap_Rocket_RegisterProperty( const char *name, const char *defaultValue, qboolean inherited, qboolean force_layout, const char *parseAs )
{
	VM::SendMsg<Rocket::RegisterPropertyMsg>(name, defaultValue, inherited, force_layout, parseAs);
}

void trap_Rocket_ShowScoreboard( const char *name, qboolean show )
{
	VM::SendMsg<Rocket::ShowScoreboardMsg>(name, show);
}

void trap_Rocket_SetDataSelectIndex( int index )
{
	VM::SendMsg<Rocket::SetDataSelectIndexMsg>(index);
}

