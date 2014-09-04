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

#define syscallVM(...) 0

// TODO non-syscalls, implement them at some point

void trap_EscapedArgs( char *buffer, int bufferLength )
{
}

void trap_LiteralArgs( char *buffer, int bufferLength )
{
}

float trap_Cvar_VariableValue( const char *var_name )
{
}

qboolean trap_FS_LoadPak( const char *pak )
{
}

// All Miscs

int trap_GetDemoState( void )
{
	int state;
	VM::SendMsg<GetDemoStateMsg>(state);
	return state;
}

void trap_GS_FS_Seek( fileHandle_t f, long offset, fsOrigin_t origin )
{
	VM::SendMsg<FSSeekMsg>(f, offset, origin);
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


//39.
//re.ProjectDecal(args[1], args[2], VMA(3), VMA(4), VMA(5), args[6], args[7]);
void trap_R_ProjectDecal( qhandle_t hShader, int numPoints, vec3_t *points, vec4_t projection, vec4_t color, int lifeTime, int fadeTime )
{
    syscallVM( CG_R_PROJECTDECAL, hShader, numPoints, points, projection, color, lifeTime, fadeTime );
}

//40.
//re.ClearDecals();
void trap_R_ClearDecals( void )
{
    syscallVM( CG_R_CLEARDECALS );
}

//59.
//re.LoadWorld(VMA(1));
void trap_R_LoadWorldMap( const char *mapname )
{
    //CG_DrawInformation(qtrue);

    syscallVM( CG_R_LOADWORLDMAP, mapname );
}

//60.
//return re.RegisterModel(VMA(1));
qhandle_t trap_R_RegisterModel( const char *name )
{
    //CG_DrawInformation(qtrue);

    return syscallVM( CG_R_REGISTERMODEL, name );
}

//61.
//return re.RegisterSkin(VMA(1));
qhandle_t trap_R_RegisterSkin( const char *name )
{
    //CG_DrawInformation(qtrue);

    return syscallVM( CG_R_REGISTERSKIN, name );
}

//62.
//return re.GetSkinModel(args[1], VMA(2), VMA(3));
qboolean trap_R_GetSkinModel( qhandle_t skinid, const char *type, char *name )
{
    return syscallVM( CG_R_GETSKINMODEL, skinid, type, name );
}

//63.
//return re.GetShaderFromModel(args[1], args[2], args[3]);
qhandle_t trap_R_GetShaderFromModel( qhandle_t modelid, int surfnum, int withlightmap )
{
    return syscallVM( CG_R_GETMODELSHADER, modelid, surfnum, withlightmap );
}

//64.
//return re.RegisterShader(VMA(1), args[2]);
qhandle_t trap_R_RegisterShader( const char *name, RegisterShaderFlags_t flags )
{
    //CG_DrawInformation(qtrue);

    return syscallVM( CG_R_REGISTERSHADER, name, flags );
}

//65.
//re.RegisterFont(VMA(1), args[2], VMA(3));
void trap_R_RegisterFont( const char *fontName, const char *fallbackName, int pointSize, fontMetrics_t *font )
{
    //CG_DrawInformation(qtrue);

    /**/
    syscallVM( CG_R_REGISTERFONT, fontName, fallbackName, pointSize, font );
}

//68.
//re.ClearScene();
void trap_R_ClearScene( void )
{
    syscallVM( CG_R_CLEARSCENE );
}

//69.
//re.AddRefEntityToScene(VMA(1));
void trap_R_AddRefEntityToScene( const refEntity_t *re )
{
    syscallVM( CG_R_ADDREFENTITYTOSCENE, re );
}

//70.
//re.AddRefLightToScene(VMA(1));
void trap_R_AddRefLightToScene( const refLight_t *light )
{
    syscallVM( CG_R_ADDREFLIGHTSTOSCENE, light );
}

//71.
//re.AddPolyToScene(args[1], args[2], VMA(3));
void trap_R_AddPolyToScene( qhandle_t hShader, int numVerts, const polyVert_t *verts )
{
    syscallVM( CG_R_ADDPOLYTOSCENE, hShader, numVerts, verts );
}

//72.
//re.AddPolysToScene(args[1], args[2], VMA(3), args[4]);
void trap_R_AddPolysToScene( qhandle_t hShader, int numVerts, const polyVert_t *verts, int numPolys )
{
    syscallVM( CG_R_ADDPOLYSTOSCENE, hShader, numVerts, verts, numPolys );
}

//73.
//re.AddPolyBufferToScene(VMA(1));
void trap_R_AddPolyBufferToScene( polyBuffer_t *pPolyBuffer )
{
    syscallVM( CG_R_ADDPOLYBUFFERTOSCENE, pPolyBuffer );
}

//74.
//re.AddLightToScene(VMA(1), VMF(2), VMF(3), VMF(4), VMF(5), VMF(6), args[7], args[8]);
void trap_R_AddLightToScene( const vec3_t org, float radius, float intensity, float r, float g, float b, qhandle_t hShader, int flags )
{
    syscallVM( CG_R_ADDLIGHTTOSCENE, org, PASSFLOAT( radius ), PASSFLOAT( intensity ), PASSFLOAT( r ), PASSFLOAT( g ), PASSFLOAT( b ), hShader, flags );
}

//75.
//re.AddAdditiveLightToScene( VMA(1), VMF(2), VMF(3), VMF(4), VMF(5) );
void trap_R_AddAdditiveLightToScene( const vec3_t org, float intensity, float r, float g, float b )
{
    syscallVM( CG_R_ADDADDITIVELIGHTTOSCENE, org, PASSFLOAT( intensity ), PASSFLOAT( r ), PASSFLOAT( g ), PASSFLOAT( b ) );
}

//77.
//re.AddCoronaToScene(VMA(1), VMF(2), VMF(3), VMF(4), VMF(5), args[6], args[7]);
void trap_R_AddCoronaToScene( const vec3_t org, float r, float g, float b, float scale, int id, qboolean visible )
{
    syscallVM( CG_R_ADDCORONATOSCENE, org, PASSFLOAT( r ), PASSFLOAT( g ), PASSFLOAT( b ), PASSFLOAT( scale ), id, visible );
}

//78.
//re.SetFog(args[1], args[2], args[3], VMF(4), VMF(5), VMF(6), VMF(7));
void trap_R_SetFog( int fogvar, int var1, int var2, float r, float g, float b, float density )
{
    syscallVM( CG_R_SETFOG, fogvar, var1, var2, PASSFLOAT( r ), PASSFLOAT( g ), PASSFLOAT( b ), PASSFLOAT( density ) );
}

//79.
//re.SetGlobalFog(args[1], args[2], VMF(3), VMF(4), VMF(5), VMF(6));
void trap_R_SetGlobalFog( qboolean restore, int duration, float r, float g, float b, float depthForOpaque )
{
    syscallVM( CG_R_SETGLOBALFOG, restore, duration, PASSFLOAT( r ), PASSFLOAT( g ), PASSFLOAT( b ), PASSFLOAT( depthForOpaque ) );
}

//80.
//re.RenderScene(VMA(1));
void trap_R_RenderScene( const refdef_t *fd )
{
    syscallVM( CG_R_RENDERSCENE, fd );
}

//81.
//re.SaveViewParms();
void trap_R_SaveViewParms( void )
{
    syscallVM( CG_R_SAVEVIEWPARMS );
}

//82.
//re.RestoreViewParms();
void trap_R_RestoreViewParms( void )
{
    syscallVM( CG_R_RESTOREVIEWPARMS );
}

//83.
//re.SetColor(VMA(1));
void trap_R_SetColor( const float *rgba )
{
    syscallVM( CG_R_SETCOLOR, rgba );
}

//84.
//re.SetClipRegion( VMA(1) );
void trap_R_SetClipRegion( const float *region )
{
    syscallVM( CG_R_SETCLIPREGION, region );
}

//85.
//re.DrawStretchPic(VMF(1), VMF(2), VMF(3), VMF(4), VMF(5), VMF(6), VMF(7), VMF(8), args[9]);
void trap_R_DrawStretchPic( float x, float y, float w, float h, float s1, float t1, float s2, float t2, qhandle_t hShader )
{
    syscallVM( CG_R_DRAWSTRETCHPIC, PASSFLOAT( x ), PASSFLOAT( y ), PASSFLOAT( w ), PASSFLOAT( h ), PASSFLOAT( s1 ), PASSFLOAT( t1 ), PASSFLOAT( s2 ), PASSFLOAT( t2 ), hShader );
}

//86.
//re.DrawRotatedPic(VMF(1), VMF(2), VMF(3), VMF(4), VMF(5), VMF(6), VMF(7), VMF(8), args[9], VMF(10));
void trap_R_DrawRotatedPic( float x, float y, float w, float h, float s1, float t1, float s2, float t2, qhandle_t hShader, float angle )
{
    syscallVM( CG_R_DRAWROTATEDPIC, PASSFLOAT( x ), PASSFLOAT( y ), PASSFLOAT( w ), PASSFLOAT( h ), PASSFLOAT( s1 ), PASSFLOAT( t1 ), PASSFLOAT( s2 ), PASSFLOAT( t2 ), hShader, PASSFLOAT( angle ) );
}

//87.
//re.DrawStretchPicGradient(VMF(1), VMF(2), VMF(3), VMF(4), VMF(5), VMF(6), VMF(7), VMF(8), args[9], VMA(10), args[11]);
void trap_R_DrawStretchPicGradient( float x, float y, float w, float h, float s1, float t1, float s2, float t2, qhandle_t hShader, const float *gradientColor, int gradientType )
{
    syscallVM( CG_R_DRAWSTRETCHPIC_GRADIENT, PASSFLOAT( x ), PASSFLOAT( y ), PASSFLOAT( w ), PASSFLOAT( h ), PASSFLOAT( s1 ), PASSFLOAT( t1 ), PASSFLOAT( s2 ), PASSFLOAT( t2 ), hShader, gradientColor, gradientType );
}

//88.
//re.Add2dPolys(VMA(1), args[2], args[3]);
void trap_R_Add2dPolys( polyVert_t *verts, int numverts, qhandle_t hShader )
{
    syscallVM( CG_R_DRAW2DPOLYS, verts, numverts, hShader );
}

//89.
//re.ModelBounds(args[1], VMA(2), VMA(3));
void trap_R_ModelBounds( clipHandle_t model, vec3_t mins, vec3_t maxs )
{
    syscallVM( CG_R_MODELBOUNDS, model, mins, maxs );
}

//90.
//return re.LerpTag(VMA(1), VMA(2), VMA(3), args[4]);
int trap_R_LerpTag( orientation_t *tag, const refEntity_t *refent, const char *tagName, int startIndex )
{
    return syscallVM( CG_R_LERPTAG, tag, refent, tagName, startIndex );
}

//101.
//return Key_IsDown(args[1]);
qboolean trap_Key_IsDown( int keynum )
{
    return syscallVM( CG_KEY_ISDOWN, keynum );
}

//102.
//return Key_GetCatcher();
int trap_Key_GetCatcher( void )
{
    return syscallVM( CG_KEY_GETCATCHER );
}

//103.
//Key_SetCatcher(args[1]);
void trap_Key_SetCatcher( int catcher )
{
    syscallVM( CG_KEY_SETCATCHER, catcher );
}

//104.
//return Key_GetKey(VMA(1));
int trap_Key_GetKey( const char *binding )
{
    return syscallVM( CG_KEY_GETKEY, binding );
}

//105.
//return Key_GetOverstrikeMode();
qboolean trap_Key_GetOverstrikeMode( void )
{
    return syscallVM( CG_KEY_GETOVERSTRIKEMODE );
}

//106.
//Key_SetOverstrikeMode(args[1]);
void trap_Key_SetOverstrikeMode( qboolean state )
{
    syscallVM( CG_KEY_SETOVERSTRIKEMODE, state );
}

//107.
//return (int)memset(VMA(1), args[2], args[3]);

//108.
//return (int)memcpy(VMA(1), VMA(2), args[3]);

//109.
//return (int)strncpy(VMA(1), VMA(2), args[3]);

//110
//return FloatAsInt(sin(VMF(1)));

//111
//return FloatAsInt(cos(VMF(1)));

//112
//return FloatAsInt(atan2(VMF(1), VMF(2)));

//113
//return FloatAsInt(sqrt(VMF(1)));

//114
//return FloatAsInt(floor(VMF(1)));

//115
//return FloatAsInt(ceil(VMF(1)));

//116
//return FloatAsInt(acos(VMF(1)));

//126.
//return CIN_PlayCinematic(VMA(1), args[2], args[3], args[4], args[5], args[6]);
int trap_CIN_PlayCinematic( const char *arg0, int xpos, int ypos, int width, int height, int bits )
{
    return syscallVM( CG_CIN_PLAYCINEMATIC, arg0, xpos, ypos, width, height, bits );
}

//127.
//return CIN_StopCinematic(args[1]);
e_status trap_CIN_StopCinematic( int handle )
{
    return (e_status) syscallVM( CG_CIN_STOPCINEMATIC, handle );
}

//128.
//return CIN_RunCinematic(args[1]);
e_status trap_CIN_RunCinematic( int handle )
{
    return (e_status) syscallVM( CG_CIN_RUNCINEMATIC, handle );
}

//129.
//CIN_DrawCinematic(args[1]);
void trap_CIN_DrawCinematic( int handle )
{
    syscallVM( CG_CIN_DRAWCINEMATIC, handle );
}

//130.
//CIN_SetExtents(args[1], args[2], args[3], args[4], args[5]);
void trap_CIN_SetExtents( int handle, int x, int y, int w, int h )
{
    syscallVM( CG_CIN_SETEXTENTS, handle, x, y, w, h );
}

//131.
//re.RemapShader(VMA(1), VMA(2), VMA(3));
void trap_R_RemapShader( const char *oldShader, const char *newShader, const char *timeOffset )
{
    syscallVM( CG_R_REMAP_SHADER, oldShader, newShader, timeOffset );
}

//139.
//if(cls.state == CA_ACTIVE && !clc.demoplaying) {
//	if(uivm) {
//		VM_Call(uivm, UI_SET_ACTIVE_MENU, args[1]);
//	}
//}
void trap_UI_Popup( int arg0 )
{
    syscallVM( CG_INGAME_POPUP, arg0 );
}

//140.
void trap_UI_ClosePopup( const char *arg0 )
{
    syscallVM( CG_INGAME_CLOSEPOPUP, arg0 );
}

//141.
//Key_GetBindingBuf(args[1], VMA(2), args[3]);
void trap_Key_GetBindingBuf( int keynum, int team, char *buf, int buflen )
{
    syscallVM( CG_KEY_GETBINDINGBUF, keynum, team, buf, buflen );
}

//142.
//Key_SetBinding(args[1], VMA(2));
void trap_Key_SetBinding( int keynum, int team, const char *binding )
{
    syscallVM( CG_KEY_SETBINDING, keynum, team, binding );
}

//148.
//Key_KeynumToStringBuf(args[1], VMA(2), args[3]);
void trap_Key_KeynumToStringBuf( int keynum, char *buf, int buflen )
{
    syscallVM( CG_KEY_KEYNUMTOSTRINGBUF, keynum, buf, buflen );
}

//152.
//return re.inPVS(VMA(1), VMA(2));
qboolean trap_R_inPVS( const vec3_t p1, const vec3_t p2 )
{
    return syscallVM( CG_R_INPVS, p1, p2 );
}

//157.
//return re.LoadDynamicShader(VMA(1), VMA(2));
qboolean trap_R_LoadDynamicShader( const char *shadername, const char *shadertext )
{
    return syscallVM( CG_R_LOADDYNAMICSHADER, shadername, shadertext );
}

//158.
//re.RenderToTexture(args[1], args[2], args[3], args[4], args[5]);
void trap_R_RenderToTexture( int textureid, int x, int y, int w, int h )
{
    syscallVM( CG_R_RENDERTOTEXTURE, textureid, x, y, w, h );
}

//160.
//re.Finish();
void trap_R_Finish( void )
{
    syscallVM( CG_R_FINISH );
}

//162.
void trap_S_StartSoundVControl( vec3_t origin, int entityNum, int entchannel, sfxHandle_t sfx, int volume )
{
    syscallVM( CG_S_STARTSOUND, origin, entityNum, entchannel, sfx, volume );
}

//163.
int trap_R_LightForPoint( vec3_t point, vec3_t ambientLight, vec3_t directedLight, vec3_t lightDir )
{
    return syscallVM( CG_R_LIGHTFORPOINT, point, ambientLight, directedLight, lightDir );
}

//165.
qhandle_t trap_R_RegisterAnimation( const char *name )
{
    return syscallVM( CG_R_REGISTERANIMATION, name );
}

//166.
int trap_R_CheckSkeleton( refSkeleton_t *skel, qhandle_t hModel, qhandle_t hAnim )
{
    return syscallVM( CG_R_CHECKSKELETON, skel, hModel, hAnim );
}

//167.
int trap_R_BuildSkeleton( refSkeleton_t *skel, qhandle_t anim, int startFrame, int endFrame, float frac, qboolean clearOrigin )
{
    return syscallVM( CG_R_BUILDSKELETON, skel, anim, startFrame, endFrame, PASSFLOAT( frac ), clearOrigin );
}

//168.
int trap_R_BlendSkeleton( refSkeleton_t *skel, const refSkeleton_t *blend, float frac )
{
    return syscallVM( CG_R_BLENDSKELETON, skel, blend, PASSFLOAT( frac ) );
}

//169.
int trap_R_BoneIndex( qhandle_t hModel, const char *boneName )
{
    return syscallVM( CG_R_BONEINDEX, hModel, boneName );
}

//170.
int trap_R_AnimNumFrames( qhandle_t hAnim )
{
    return syscallVM( CG_R_ANIMNUMFRAMES, hAnim );
}

//171.
int trap_R_AnimFrameRate( qhandle_t hAnim )
{
    return syscallVM( CG_R_ANIMFRAMERATE, hAnim );
}

//172.
void trap_CompleteCallback( const char *complete )
{
    syscallVM( CG_COMPLETE_CALLBACK, complete );
}

//174.
void trap_R_Glyph( fontHandle_t font, const char *str, glyphInfo_t *glyph )
{
    syscallVM( CG_R_GLYPH, font, str, glyph );
}

//175.
void trap_R_GlyphChar( fontHandle_t font, int ch, glyphInfo_t *glyph )
{
    syscallVM( CG_R_GLYPHCHAR, font, ch, glyph );
}

//176.
void trap_R_UnregisterFont( fontHandle_t font )
{
    syscallVM( CG_R_UREGISTERFONT, font );
}

//181.
//return re.inPVVS(VMA(1), VMA(2));
qboolean trap_R_inPVVS( const vec3_t p1, const vec3_t p2 )
{
    return syscallVM( CG_R_INPVVS, p1, p2 );
}

qhandle_t trap_RegisterVisTest( void )
{
    return syscallVM( CG_REGISTERVISTEST );
}

void trap_AddVisTestToScene( qhandle_t hTest, vec3_t pos, float depthAdjust, float area )
{
    syscallVM( CG_ADDVISTESTTOSCENE, hTest, pos, PASSFLOAT( depthAdjust ),
            PASSFLOAT( area ) );
}

float trap_CheckVisibility( qhandle_t hTest )
{
    return syscallVM( CG_CHECKVISIBILITY, hTest );
}

void trap_UnregisterVisTest( qhandle_t hTest )
{
    syscallVM( CG_UNREGISTERVISTEST, hTest );
}

void trap_SetColorGrading( int slot, qhandle_t hShader )
{
    syscallVM( CG_SETCOLORGRADING, slot, hShader );
}

void trap_R_ScissorEnable( qboolean enable )
{
    syscallVM( CG_R_SCISSOR_ENABLE, enable );
}

void trap_R_ScissorSet( int x, int y, int w, int h )
{
    syscallVM( CG_R_SCISSOR_SET, x, y, w, h );
}

void trap_LAN_LoadCachedServers( void )
{
    syscallVM( CG_LAN_LOADCACHEDSERVERS );
}

void trap_LAN_SaveCachedServers( void )
{
    syscallVM( CG_LAN_SAVECACHEDSERVERS );
}

int trap_LAN_AddServer( int source, const char *name, const char *addr )
{
    return syscallVM( CG_LAN_ADDSERVER, source, name, addr );
}

void trap_LAN_RemoveServer( int source, const char *addr )
{
    syscallVM( CG_LAN_REMOVESERVER, source, addr );
}

int trap_LAN_GetPingQueueCount( void )
{
    return syscallVM( CG_LAN_GETPINGQUEUECOUNT );
}

void trap_LAN_ClearPing( int n )
{
    syscallVM( CG_LAN_CLEARPING, n );
}

void trap_LAN_GetPing( int n, char *buf, int buflen, int *pingtime )
{
    syscallVM( CG_LAN_GETPING, n, buf, buflen, pingtime );
}

void trap_LAN_GetPingInfo( int n, char *buf, int buflen )
{
    syscallVM( CG_LAN_GETPINGINFO, n, buf, buflen );
}

int trap_LAN_GetServerCount( int source )
{
    return syscallVM( CG_LAN_GETSERVERCOUNT, source );
}

void trap_LAN_GetServerAddressString( int source, int n, char *buf, int buflen )
{
    syscallVM( CG_LAN_GETSERVERADDRESSSTRING, source, n, buf, buflen );
}

void trap_LAN_GetServerInfo( int source, int n, char *buf, int buflen )
{
    syscallVM( CG_LAN_GETSERVERINFO, source, n, buf, buflen );
}

int trap_LAN_GetServerPing( int source, int n )
{
    return syscallVM( CG_LAN_GETSERVERPING, source, n );
}

void trap_LAN_MarkServerVisible( int source, int n, qboolean visible )
{
    syscallVM( CG_LAN_MARKSERVERVISIBLE, source, n, visible );
}

int trap_LAN_ServerIsVisible( int source, int n )
{
    return syscallVM( CG_LAN_SERVERISVISIBLE, source, n );
}

qboolean trap_LAN_UpdateVisiblePings( int source )
{
    return syscallVM( CG_LAN_UPDATEVISIBLEPINGS, source );
}

void trap_LAN_ResetPings( int n )
{
    syscallVM( CG_LAN_RESETPINGS, n );
}

int trap_LAN_ServerStatus( const char *serverAddress, char *serverStatus, int maxLen )
{
    return syscallVM( CG_LAN_SERVERSTATUS, serverAddress, serverStatus, maxLen );
}

qboolean trap_LAN_ServerIsInFavoriteList( int source, int n )
{
    return syscallVM( CG_LAN_SERVERISINFAVORITELIST, source, n );
}

int trap_LAN_CompareServers( int source, int sortKey, int sortDir, int s1, int s2 )
{
    return syscallVM( CG_LAN_COMPARESERVERS, source, sortKey, sortDir, s1, s2 );
}

void trap_R_GetShaderNameFromHandle( const qhandle_t shader, char *out, int len )
{
    syscallVM( CG_R_GETSHADERNAMEFROMHANDLE, shader, out, len );
}

void trap_R_SetAltShaderTokens( const char *str )
{
    syscallVM( CG_R_SETALTSHADERTOKENS, str );
}

void trap_Rocket_Init( void )
{
    syscallVM( CG_ROCKET_INIT );
}

void trap_Rocket_Shutdown( void )
{
    syscallVM( CG_ROCKET_SHUTDOWN );
}

void trap_Rocket_LoadDocument( const char *path )
{
    syscallVM( CG_ROCKET_LOADDOCUMENT, path );
}

void trap_Rocket_LoadCursor( const char *path )
{
    syscallVM( CG_ROCKET_LOADCURSOR, path );
}

void trap_Rocket_DocumentAction( const char *name, const char *action )
{
    syscallVM( CG_ROCKET_DOCUMENTACTION, name, action );
}

qboolean trap_Rocket_GetEvent( void )
{
    return syscallVM( CG_ROCKET_GETEVENT );
}

void trap_Rocket_DeleteEvent( void )
{
    syscallVM( CG_ROCKET_DELELTEEVENT );
}

void trap_Rocket_RegisterDataSource( const char *name )
{
    syscallVM( CG_ROCKET_REGISTERDATASOURCE, name );
}

void trap_Rocket_DSAddRow( const char *name, const char *table, const char *data )
{
    syscallVM( CG_ROCKET_DSADDROW, name, table, data );
}

void trap_Rocket_DSChangeRow( const char *name, const char *table, int row, const char *data )
{
    syscallVM( CG_ROCKET_DSCHANGEROW, name, table, row, data );
}

void trap_Rocket_DSRemoveRow( const char *name, const char *table, int row )
{
    syscallVM( CG_ROCKET_DSREMOVEROW, name, table, row );
}

void trap_Rocket_DSClearTable( const char *name, const char *table )
{
    syscallVM( CG_ROCKET_DSCLEARTABLE, name, table );
}

void trap_Rocket_SetInnerRML( const char *RML, int parseFlags )
{
    syscallVM( CG_ROCKET_SETINNERRML, RML, parseFlags );
}

void trap_Rocket_GetAttribute( const char *attribute, char *out, int length )
{
    syscallVM( CG_ROCKET_GETATTRIBUTE, attribute, out, length );
}

void trap_Rocket_SetAttribute( const char *attribute, const char *value )
{
    syscallVM( CG_ROCKET_SETATTRIBUTE, attribute, value );
}

void trap_Rocket_GetProperty( const char *name, void *out, int len, rocketVarType_t type )
{
    syscallVM( CG_ROCKET_GETPROPERTY, name, out, len, type );
}

void trap_Rocket_SetProperty( const char *property, const char *value )
{
    syscallVM( CG_ROCKET_SETPROPERYBYID, property, value );
}
void trap_Rocket_GetEventParameters( char *params, int length )
{
    syscallVM( CG_ROCKET_GETEVENTPARAMETERS, params, length );
}
void trap_Rocket_RegisterDataFormatter( const char *name )
{
    syscallVM( CG_ROCKET_REGISTERDATAFORMATTER, name );
}

void trap_Rocket_DataFormatterRawData( int handle, char *name, int nameLength, char *data, int dataLength )
{
    syscallVM( CG_ROCKET_DATAFORMATTERRAWDATA, handle, name, nameLength, data, dataLength );
}

void trap_Rocket_DataFormatterFormattedData( int handle, const char *data, qboolean parseQuake )
{
    syscallVM( CG_ROCKET_DATAFORMATTERFORMATTEDDATA, handle, data, parseQuake );
}

void trap_Rocket_RegisterElement( const char *tag )
{
    syscallVM( CG_ROCKET_REGISTERELEMENT, tag );
}

void trap_Rocket_SetElementDimensions( float x, float y )
{
    syscallVM( CG_ROCKET_SETELEMENTDIMENSIONS, PASSFLOAT( x ), PASSFLOAT( y ) );
}

void trap_Rocket_GetElementTag( char *tag, int length )
{
    syscallVM( CG_ROCKET_GETELEMENTTAG, tag, length );
}

void trap_Rocket_GetElementAbsoluteOffset( float *x, float *y )
{
    syscallVM( CG_ROCKET_GETELEMENTABSOLUTEOFFSET, x, y );
}

void trap_Rocket_QuakeToRML( const char *in, char *out, int length )
{
    syscallVM( CG_ROCKET_QUAKETORML, in, out, length );
}

void trap_Rocket_SetClass( const char *in, qboolean activate )
{
    syscallVM( CG_ROCKET_SETCLASS, in, activate );
}

void trap_Rocket_InitializeHuds( int size )
{
    syscallVM( CG_ROCKET_INITHUDS, size );
}

void trap_Rocket_LoadUnit( const char *path )
{
    syscallVM( CG_ROCKET_LOADUNIT, path );
}

void trap_Rocket_AddUnitToHud( int weapon, const char *id )
{
    syscallVM( CG_ROCKET_ADDUNITTOHUD, weapon, id );
}

void trap_Rocket_ShowHud( int weapon )
{
    syscallVM( CG_ROCKET_SHOWHUD, weapon );
}

void trap_Rocket_ClearHud( int weapon )
{
    syscallVM( CG_ROCKET_CLEARHUD, weapon );
}

void trap_Rocket_AddTextElement( const char *text, const char *Class, float x, float y )
{
    syscallVM( CG_ROCKET_ADDTEXT, text, Class, PASSFLOAT( x ), PASSFLOAT( y ) );
}

void trap_Rocket_ClearText( void )
{
    syscallVM( CG_ROCKET_CLEARTEXT );
}

void trap_Rocket_RegisterProperty( const char *name, const char *defaultValue, qboolean inherited, qboolean force_layout, const char *parseAs )
{
    syscallVM( CG_ROCKET_REGISTERPROPERTY, name, defaultValue, inherited, force_layout, parseAs );
}

void trap_Rocket_ShowScoreboard( const char *name, qboolean show )
{
    syscallVM( CG_ROCKET_SHOWSCOREBOARD, name, show );
}

void trap_Rocket_SetDataSelectIndex( int index )
{
    syscallVM( CG_ROCKET_SETDATASELECTINDEX, index );
}

