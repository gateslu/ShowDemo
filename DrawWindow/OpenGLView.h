/*
 * Copyright (c) 2010, Tae-young Jung
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the <organization>.
 * 4. Neither the name of the <organization> nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY <COPYRIGHT HOLDER> ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "glew.h"
#include "gl.h"		// Header File For The OpenGL32 Library
#include "glu.h"			// Header File For The GLu32 Library
#include "glaux.h"		// Header File For The Glaux Library
#include <Windows.h>
#include <stdint.h>
#include <process.h>

#include "GlobalHeader.h"

// COpenGLView view

class COpenGLView
{

public:
	COpenGLView();           // protected constructor used by dynamic creation
	virtual ~COpenGLView();

public:
    HDC			m_hDC;		// Private GDI Device Context
    HGLRC		m_hResouceRC;		// ×ÊÔ´ Rendering Context
    HGLRC		m_hRenderRC;		    // »æÖÆ Rendering Context
    HWND		m_hWnd;		// Holds Our Window Handle

	unsigned char* im;
	int width;
	int height;

	/* texture width & height */
	int t_width; 
	int t_height;

	BOOL loaded;
	unsigned int texture;

    float ratio_x;
    float ratio_y;

public:
    void glInital();
    int   OnCreate(void *handle);
    void OnDraw();      // overridden to draw this view
    void OnDestroy();
    void OnSize(int cx, int cy);
    void initParam(int _width, int _height);
    void SetParam(int _width, int _height);
    void SetParamEX(int _width, int _height, float _ratio_x, float _ratio_y);
    void LoadTexture(unsigned char* rgba,int _width, int _height);
    void moveToThread();
    void removeFromThread();
};


