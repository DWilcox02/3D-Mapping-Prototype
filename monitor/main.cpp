/*
-lmingw32 -lSDLmain -lSDL -lopengl32 -lglu32
*/

//Headers
#include "SDL.h"
#include "SDL_opengl.h"
#include <stdio.h>
#include <windows.h>
#include <math.h>
#define PI 3.14159265358979323846
#include <iostream>
#include <vector>  //for std::vector
#include <string>  //for std::string

using namespace std;


//Start of the program
int main(int argc, char* args[])
{
    SDL_Init (SDL_INIT_EVERYTHING);

    //Memory allocation
    printf("Hello World");
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 32);
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1);

    SDL_WM_SetCaption( "Monitor", NULL);

    SDL_SetVideoMode(640,480,32, SDL_OPENGL);

    glClearColor(1,1,1,1); //The color of the screen when it is cleared (during framechange - R,G,B,Alpha)
    glViewport(0,0,640,480); //Which portions of the frame are visable

    glShadeModel(GL_SMOOTH); //Use gradients on color transitions

    glMatrixMode(GL_PROJECTION); //2D Drawing
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);



    std::cout << "OpenGL is running\n";
    std::cout << "Program has started\n";


        //Serial Port Initialization

        //Open USB port COM4 - the only one working on my PC
        HANDLE hSerial;

        hSerial = CreateFile("COM4",
                             GENERIC_READ,
                             0,
                             0,
                             OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL,
                             0);
        if(hSerial==INVALID_HANDLE_VALUE){
            if(GetLastError()==ERROR_FILE_NOT_FOUND){
                //Serial Port does not exist, inform user.
            }
            //Some other error occurred, inform user.
        }

        //Setting Parameters
        DCB dcbSerialParams = {0};

        dcbSerialParams.DCBlength=sizeof(dcbSerialParams);

        if (!GetCommState(hSerial, &dcbSerialParams)) {
            //error getting state
        }

        dcbSerialParams.BaudRate=CBR_9600;
        dcbSerialParams.ByteSize=8;
        dcbSerialParams.StopBits=ONESTOPBIT;
        dcbSerialParams.Parity=NOPARITY;

        if(!SetCommState(hSerial, &dcbSerialParams)){
            //Error Setting Serial Port device
        }

        //Timeouts
        COMMTIMEOUTS timeouts={0};

        timeouts.ReadIntervalTimeout=50;
        timeouts.ReadTotalTimeoutConstant=50;
        timeouts.ReadTotalTimeoutMultiplier=10;
        timeouts.WriteTotalTimeoutConstant=50;
        timeouts.WriteTotalTimeoutMultiplier=10;

        if(!SetCommTimeouts(hSerial, &timeouts)){
            //Error occurred, inform user.
        }

        //Buffer
        unsigned char szBuff [8] = {0};

        //DWORD dwBytesRead = 0;

    bool isRunning = true;

    SDL_Event event;


//Declarations
float rpm0 = 0000;
float rpm1 = 0000;
float rpm2 = 0000;


int tachx;
int tachy;
int tachcenx0 = 320;
int tachceny0 = 125;
int tachcenx1 = 320;
int tachceny1 = 175;
int tachcenx2 = 490;
int tachceny2 = 125;

float ptdeg;
float ptdist;


vector<int> xVals; //Array for all the xValues to be drawn
vector<int> yVals; //Array for all the yValues to be drawn

//Main loop
    while ( isRunning)
    {
        //Exit Events
        while ( SDL_PollEvent(&event))
        {
            if ( event.type == SDL_QUIT)
            {
            isRunning = false;
            }

            if ( event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
            {
            isRunning = false;
            }

        }

        //Reading Serial Port


        DWORD dwBytesRead = 0;

        if (!ReadFile(hSerial, szBuff, 8, &dwBytesRead, NULL))
        {
            //Error occured Report to user
        }


        //Take Serial data from COM port and use in program
        //Very faulty as I can't figure out how to distinguish the 2 in the serial port

        //byte one
        rpm0 = szBuff [0];
        //byte two
        rpm1 = szBuff [1];


        //Rendering to the screen

        //Clear
        glClear(GL_COLOR_BUFFER_BIT);



        glPushMatrix(); //Start phase

        glOrtho(0,640,480,0,-1,1); //Set the matrix



        /*                        Draw                      */
//GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLYGON


        //Dial
        ptdeg = (PI * 2) * (rpm0 / 255); //Turns rotation into radians
        ptdist = ((float) (rpm1 + 50) / 255) * 100;

        tachx = tachcenx0 + ( ptdist * (cos (ptdeg)) ); //x on unit circle * 75 (all relative to centre of circle)
        tachy = tachceny0 + ( ptdist * (sin (ptdeg)) ); //y on unit circle * 75 (all relative to centre of circle)

        //Tach line
        glBegin(GL_LINES);
        glColor4ub(255,11,15,0);
        glVertex2f(tachcenx0,tachceny0);
        glVertex2f(tachx,tachy);
        glEnd();

        xVals.push_back(tachx); //Writes current xValue to the end of the arrayList
        yVals.push_back(tachy); //Writes current yValue to same spot

        //Points
        glColor4ub(0,0,0,255);
        glBegin(GL_POINTS);

        //Positions on circle
        glVertex2f(tachcenx0 + 80,tachceny0);
        glVertex2f(tachcenx0 - 80,tachceny0);
        glVertex2f(tachcenx0,tachceny0 + 80);
        glVertex2f(tachcenx0,tachceny0 - 80);

        //2 for each quadrant
        glVertex2f( tachcenx0 + ( 80 * (cos (PI / 6)) ),tachceny0 + ( 80 * (sin (PI / 6)) ));
        glVertex2f( tachcenx0 + ( 80 * (cos (PI / 3)) ),tachceny0 + ( 80 * (sin (PI / 3)) ));

        glVertex2f( tachcenx0 + ( 80 * (cos (PI * .666667)) ),tachceny0 + ( 80 * (sin (PI * .666667)) ));
        glVertex2f( tachcenx0 + ( 80 * (cos (PI * .833333)) ),tachceny0 + ( 80 * (sin (PI * .833333)) ));

        glVertex2f( tachcenx0 + ( 80 * (cos (PI * 1.16667)) ),tachceny0 + ( 80 * (sin (PI * 1.16667)) ));
        glVertex2f( tachcenx0 + ( 80 * (cos (PI * 1.33333)) ),tachceny0 + ( 80 * (sin (PI * 1.33333)) ));

        glVertex2f( tachcenx0 + ( 80 * (cos (PI * 1.66667)) ),tachceny0 + ( 80 * (sin (PI * 1.66667)) ));
        glVertex2f( tachcenx0 + ( 80 * (cos (PI * 1.83333)) ),tachceny0 + ( 80 * (sin (PI * 1.83333)) ));

        //Loop through every value in xValues and yValues and draw them to the plane
        for(int i = 0; i < xVals.size(); i++)
        {
            glVertex2f(xVals.at(i), yVals.at(i));
        }

        glEnd();

        glPopMatrix(); //End rendering phase

        SDL_GL_SwapBuffers();

        SDL_Delay(10); //Hold rendered frame on screen for indicated amount of time
    }

    CloseHandle(hSerial);
    SDL_Quit();

    return 0;
}
