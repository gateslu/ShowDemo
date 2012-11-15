#include "drawclass.h"

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default
bool	light;				// Lighting ON/OFF ( NEW )
bool	lp;					// L Pressed? ( NEW )
bool	fp;					// F Pressed? ( NEW )

GLfloat	xrot;				// X Rotation
GLfloat	yrot;				// Y Rotation
GLfloat xspeed;				// X Rotation Speed
GLfloat yspeed;				// Y Rotation Speed
GLfloat	z=-5.0f;			// Depth Into The Screen
GLfloat factor = 4.0f/3.0f;
GLfloat LightAmbient[]=		{ 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]=	{ 0.0f, 0.0f, 2.0f, 1.0f };

GLuint	filter;				// Which Filter To Use
GLuint	texture[1];			// Storage For 3 Textures

char Filename[256] = {0};

typedef struct _RGBImageRec {
    GLint sizeX, sizeY;
    unsigned char *data;
} _RGBImageRec;

void start_address( void * pContext)
{
    DrawClass *pThis = (DrawClass *)pContext;
    wglMakeCurrent(pThis->hDC, pThis->hRC);
    while(!pThis->ThreadExitFlag)
    {
        if (pThis->DrawGLScene())
            SwapBuffers(pThis->hDC);
        ::Sleep(20);
    }
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);									// Depth Buffer Setup
    wglMakeCurrent(NULL,NULL);
    wglDeleteContext(pThis->hRC);
}

//AUX_RGBImageRec *LoadBMP(char *Filename)				// Loads A Bitmap Image
//{
//    AUX_RGBImageRec *aux_rgbImageRex = (AUX_RGBImageRec *)malloc(sizeof(AUX_RGBImageRec));
//    unsigned char *buffer = (unsigned char *)malloc(1920*1080*4);
//    FILE *File=NULL;									// File Handle

//    if (!Filename)										// Make Sure A Filename Was Given
//    {
//        return NULL;									// If Not Return NULL
//    }

//    File=fopen(Filename,"r");							// Check To See If The File Exists

//    if (File)											// Does The File Exist?
//    {
//        fseek(File, 0L, SEEK_END);
//        int fliesize = ftell(File);         //得到文件大小
//        fseek(File, 0L, SEEK_SET);
//        size_t size = fread( (void *)buffer, fliesize, 1, File );
//        BMP_FILE_HDR *fh = (BMP_FILE_HDR *)buffer;
//        BMP_INFO_HDR *bh = (BMP_INFO_HDR *)(buffer + sizeof(BMP_FILE_HDR));
//        int buffSize = fh->bfSize;    //得到文件大小
//        aux_rgbImageRex->sizeX = bh->biWidth;
//        aux_rgbImageRex->sizeY = bh->biHeight;
//        int infoSize = sizeof(BMP_FILE_HDR)+sizeof(BMP_INFO_HDR);
//        int dataSize = fliesize-infoSize;
//        aux_rgbImageRex->data = (unsigned char *)malloc(1920*1080*4);
//        memcpy(aux_rgbImageRex->data, buffer+infoSize, dataSize);
//        fclose(File);									// Close The Handle
//        free(buffer);
//        return aux_rgbImageRex;				// Load The Bitmap And Return A Pointer
//    }
//    free(buffer);
//    return NULL;										// If Load Failed Return NULL
//}

AUX_RGBImageRec *LoadBMP(char *Filename)				// Loads A Bitmap Image
{
    FILE *File=NULL;									// File Handle

    if (!Filename)										// Make Sure A Filename Was Given
    {
        return NULL;									// If Not Return NULL
    }

    File=fopen(Filename,"r");							// Check To See If The File Exists

    if (File)											// Does The File Exist?
    {
        fclose(File);									// Close The Handle
        return auxDIBImageLoadA(Filename);				// Load The Bitmap And Return A Pointer
    }

    return NULL;										// If Load Failed Return NULL
}

DrawClass::DrawClass() :
    hDC(NULL), hRC(NULL), hWnd(NULL),
    ThreadHandle(NULL), ThreadExitFlag(true),
    m_pBuf(0),
    m_Width(0),
    m_Height(NULL)
{
    m_pBuf = (unsigned char*)malloc(1920*1080*4);
    memset(m_pBuf, 0, 1920*1080*4);
}

DrawClass::~DrawClass()
{
    KillGLWindow();
    if(m_pBuf != NULL)
        free(m_pBuf);
}

int DrawClass::InitGL(GLvoid)
{
    //    if (!LoadGLTextures())								// Jump To Texture Loading Routine
    //    {
    //        return FALSE;									// If Texture Didn't Load Return FALSE
    //    }
    glGenTextures(1, &texture[0]);					// Create Three Textures,3,1,设置纹理

    glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);                     // Black Background
    glClearDepth(1.0f);                                         	// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);							// The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
    glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	// Position The Light
    glEnable(GL_LIGHT1);								// Enable Light One
    return TRUE;										// Initialization Went OK

}

//int DrawClass::LoadGLTextures()
//{
//    int Status=FALSE;									// Status Indicator

//    AUX_RGBImageRec *TextureImage[1];					// Create Storage Space For The Texture

//    memset(TextureImage,0,sizeof(void *)*1);           	// Set The Pointer To NULL

//    // Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
//    if (TextureImage[0]=LoadBMP(Filename))            //Filename,"Data/AngryBirds2.bmp"
//    {
//        Status=TRUE;									// Set The Status To TRUE

//        glGenTextures(3, &texture[0]);					// Create Three Textures,3,1,设置纹理

//        // Create Nearest Filtered Texture,更改为加载一个纹理
//        glBindTexture(GL_TEXTURE_2D, texture[0]);
//        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
//        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
//        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
//        //        glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

//        //        // Create Linear Filtered Texture
//        glBindTexture(GL_TEXTURE_2D, texture[1]);
//        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
//        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
//        //        glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

//        // Create MipMapped Texture
//        glBindTexture(GL_TEXTURE_2D, texture[2]);
//        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
//        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
//    }

//    if (TextureImage[0])								// If Texture Exists
//    {
//        if (TextureImage[0]->data)						// If Texture Image Exists
//        {
//            free(TextureImage[0]->data);				// Free The Texture Image Memory
//        }

//        free(TextureImage[0]);							// Free The Image Structure
//    }

//    return Status;
//}

GLvoid DrawClass::ReSizeGLScene(GLsizei width, GLsizei height)
{
    if (height==0)										// Prevent A Divide By Zero By
    {
        height=1;										// Making Height Equal One
    }

    glViewport(0,0,width,height);						// Reset The Current Viewport

    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
    glLoadIdentity();									// Reset The Projection Matrix

    // Calculate The Aspect Ratio Of The Window
    gluPerspective(28.2f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);      //(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

    glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
    glLoadIdentity();
}

void DrawClass::setDisplayWin(void *handle)
{
    if (!hDC)
    {
        hWnd = (HWND)handle;
        if (hWnd == NULL)
        {
            return;
        }
        RECT targetRect;
        ::GetClientRect(hWnd, &targetRect);
        width = targetRect.right-targetRect.left;
        height = targetRect.bottom-targetRect.top;
        if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
        {
            return;								// Return FALSE
        }

        static    PIXELFORMATDESCRIPTOR pfd =
        {
            sizeof(PIXELFORMATDESCRIPTOR),    //上述格式描述符的大小
            1,                                //版本号
            PFD_DRAW_TO_WINDOW |              //格式支持窗口
            PFD_SUPPORT_OPENGL |              //格式必须支持OpenGL
            PFD_DOUBLEBUFFER,                 //必须支持双缓冲
            PFD_TYPE_RGBA,                    //申请RGBA 格式
            24,                               //选定色彩深度
            0, 0, 0, 0, 0, 0, 0, 0,           //忽略RGBA
            0,                                //无累加缓存
            0, 0, 0, 0,                       //忽略聚集位
            32,                               //32位Z-缓存(深度缓存)
            0,                                //无蒙板缓存
            0,                                //无辅助缓存
            PFD_MAIN_PLANE,                   //主绘图层
            0,                                //Reserved
            0, 0, 0                           //忽略层遮罩
        };

        //选择一个最适合pfd描述的像素格式索引值
        int nPixelFormat = ChoosePixelFormat(hDC, &pfd);

        //为DC设置像素格式
        SetPixelFormat(hDC, nPixelFormat, &pfd);

        if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
        {
            KillGLWindow();								// Reset The Display
            return;								// Return FALSE
        }

        if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
        {
            KillGLWindow();								// Reset The Display
            return;								// Return FALSE
        }

        ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

        if (!InitGL())									// Initialize Our Newly Created GL Window
        {
            KillGLWindow();								// Reset The Display
            return;								// Return FALSE
        }
        //        wglMakeCurrent(NULL,NULL);
        //        ThreadExitFlag = false;
        //        ThreadHandle = _beginthread(start_address,1920*1080*4,(void *)this);
        wglMakeCurrent(hDC, hRC);

        DrawGLScene();
        SwapBuffers(hDC);
    }
    else
    {
        DrawGLScene();
        SwapBuffers(hDC);
    }
}

GLvoid DrawClass::KillGLWindow()
{
    ThreadExitFlag = true;
    if (ThreadHandle)
    {
        DWORD exitCode = 0;
        GetExitCodeThread((HANDLE)ThreadHandle, &exitCode);
        if (exitCode == STILL_ACTIVE)
            WaitForSingleObject((HANDLE)ThreadHandle, INFINITE);
        ThreadHandle = NULL;
    }
    if (hRC)											// Do We Have A Rendering Context?
    {
        //		wglMakeCurrent(hDC,hRC);
        if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
        {
            //            MessageBox(NULL,L"Release Of DC And RC Failed.",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
        }

        if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
        {
            //            MessageBox(NULL,L"Release Rendering Context Failed.",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
        }
        hRC=NULL;										// Set RC To NULL
    }

    if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
    {
        //        MessageBox(NULL,L"Release Device Context Failed.",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
    }
    hDC=NULL;										// Set DC To NULL

    if (hWnd /*&& !DestroyWindow(hWnd)*/)					// Are We Able To Destroy The Window?
    {
        glDeleteTextures(1, &texture[0]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
        glLoadIdentity();									// Reset The View
        InvalidateRect(hWnd,NULL,TRUE);
        //        MessageBox(NULL,L"Could Not Release hWnd.",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
        hWnd=NULL;										// Set hWnd To NULL
    }
}

int DrawClass::DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
    glLoadIdentity();									// Reset The View
    glTranslatef(0.0f,0.0f,z);

    //    glRotatef(xrot,1.0f,0.0f,0.0f);
    //    glRotatef(yrot,0.0f,1.0f,0.0f);

    glBindTexture(GL_TEXTURE_2D, texture[0]);          //filter:2选择纹理

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-factor, -1.0f,  1.0f);     //glVertex3f参数1,设置x方向比例
    glTexCoord2f(1.0f, 0.0f); glVertex3f( factor, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( factor,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-factor,  1.0f,  1.0f);
    glEnd();

    return TRUE;										// Keep Going
}

void DrawClass::setfileName(char *_filename)
{
    memcpy(Filename,_filename,256);
}

int DrawClass::LoadGLTextures(unsigned char *pBuf, int Width, int Height, GLuint *texture)
{
    int Status=FALSE;									// Status Indicator
    // Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
    Status=TRUE;									// Set The Status To TRUE

    // Create Nearest Filtered Texture,更改为加载一个纹理
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, Width / Height);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, Width, Height, GL_RGB, GL_UNSIGNED_BYTE, pBuf);
//            glTexImage2D(GL_TEXTURE_2D, 0, 3, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, pBuf);
//    glPixelStorei(GL_UNPACK_ROW_LENGTH, picture->p[j].i_pitch / picture->p[j].i_pixel_pitch);
//    glTexSubImage2D(vgl->tex_target, 0,
//                    0, 0,
//                    vgl->fmt.i_width  * vgl->chroma->p[j].w.num / vgl->chroma->p[j].w.den,
//                    vgl->fmt.i_height * vgl->chroma->p[j].h.num / vgl->chroma->p[j].h.den,
//                    vgl->tex_format, vgl->tex_type, picture->p[j].p_pixels);

            // Create Linear Filtered Texture
//    glBindTexture(GL_TEXTURE_2D, texture[0]);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
//    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, Width, Height, GL_RGB, GL_UNSIGNED_BYTE, pBuf);
    //        glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

    // Create MipMapped Texture
//    glBindTexture(GL_TEXTURE_2D, texture[0]);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
//    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, Width, Height, GL_RGB, GL_UNSIGNED_BYTE, pBuf);


    return Status;
}

void DrawClass::loadData(unsigned char *pBuf, int Width, int Height)
{
    memset(m_pBuf, 0, 3*Width*Height);
    memcpy(m_pBuf, pBuf, 3*Width*Height);
    m_Width = Width;
    m_Height = Height;
    LoadGLTextures(m_pBuf, m_Width, m_Height,texture);
    if (hWnd)
    {
//        RECT targetRect;
//        ::GetClientRect(hWnd, &targetRect);
//        int _width = targetRect.right-targetRect.left;
//        int _height = targetRect.bottom-targetRect.top;
//        ReSizeGLScene(_width, _height);					// Set Up Our Perspective GL Screen
        setDisplayWin(hWnd);
    }
}

