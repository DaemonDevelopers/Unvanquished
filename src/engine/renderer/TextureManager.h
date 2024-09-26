/*
===========================================================================

Daemon BSD Source Code
Copyright (c) 2024 Daemon Developers
All rights reserved.

This file is part of the Daemon BSD Source Code (Daemon Source Code).

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
// TextureManager.h

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

class Texture {
	public:
	GLuint textureHandle = 0;
	GLuint64 bindlessTextureHandle = 0;
	bool hasBindlessHandle = false;

	GLenum target = GL_TEXTURE_2D;
	GLenum format = GL_RGBA8;

	bool hasBindlessImageHandles = false;
	uint8_t mipLevels = 0;
	GLuint64 bindlessImageHandles[16]; // Enough for all mipmaps of a 32768x32768 texture, which is the current maximum

	Texture();
	~Texture();

	bool IsResident() const;
	bool AreImagesResident() const;
	void MakeResident();
	void MakeImagesResident( const GLenum access );
	void MakeNonResident();
	void MakeImagesNonResident();

	void GenBindlessHandle();
	void GenBindlessImageHandle();

	private:
		bool bindlessTextureResident = false;
		bool bindlessImagesResident = false;
};

class TextureManager {
	public:
	TextureManager();
	~TextureManager();

	GLuint64 BindTexture( const GLint location, Texture* texture );
	void BindReservedTexture( const GLenum target, const GLuint handle );
	void FreeTextures();

	private:
		std::vector<Texture*> textures;
};

#endif // TEXTURE_MANAGER_H
