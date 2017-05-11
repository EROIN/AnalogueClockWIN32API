#include <windows.h>
#include <time.h>
#include "Clock_private.h"

HWND hwnd;
int xh,yh,xm,ym,xs,ys,x,y;
     HBRUSH hbr;
     HDC hdc;
     PAINTSTRUCT ps;
     HGDIOBJ hdbr;
     HPEN hpen;
     RECT r;

void OnTimer(HWND);
void Display()
{
     hpen=CreatePen(PS_SOLID,10,RGB(180,180,100));                   //hour and minute handle
     hdbr=SelectObject(hdc,hpen);
     MoveToEx(hdc,x,y,NULL);
     LineTo(hdc,x+xh,y+yh);
     MoveToEx(hdc,x,y,NULL);
     LineTo(hdc,x+xm,y+ym);
     SelectObject(hdc,hdbr);
     DeleteObject(hpen);
     
     hpen=CreatePen(PS_DASHDOT,1,RGB(25,255,5));
     hdbr=SelectObject(hdc,hpen);
     MoveToEx(hdc,x,y,NULL);
     LineTo(hdc,x+xs,y+ys);
     SelectObject(hdc,hpen);
     DeleteObject(hpen);
}     
void Create()
{
     
     hbr=CreateSolidBrush(RGB(336,3232,4242));             //3000 all
     hdbr=SelectObject(hdc,hbr);
     Ellipse(hdc,x-y,0,x+y,2*y);
     SelectObject(hdc,hdbr);
     DeleteObject(hbr);
     
     hbr=CreateSolidBrush(RGB(300,0,0));        // 300,0,0
     hdbr=SelectObject(hdc,hbr);
     Ellipse(hdc,x-y+10,10,x+y-10,2*y-10);
     SelectObject(hdc,hdbr);
     DeleteObject(hbr);  
     
     hpen=CreatePen(PS_DASHDOT,1,RGB(255,255,255));                          //25,255,5
     hdbr=SelectObject(hdc,hpen);
      int h,i,hg;
     for(i=1;i<=60;i++)
     {
     h=i*6;
     if(!(h%5))
     hg=11*y/20;
     else
     hg=7*y/8;
     MoveToEx(hdc,x+floor(hg*cos((float)3.14*h/180)),y+floor(hg*sin((float)3.14*h/180)),NULL);
     LineTo(hdc,x+floor((y-10)*cos((float)3.14*h/180)),y+floor((y-10)*sin((float)3.14*h/180)));
     }
     SelectObject(hdc,hdbr);
     DeleteObject(hpen);
}
void Times()
{
     time_t sec=time(NULL);
      int h=sec/3600;
      int m=(sec%3600)/60;
      int s=(sec%3600)%60;
      m+=30;
      h=h%24;
      h=h+5;
      if(m>=60)
      {
               h++;
               m=m%60;
      }
      if(h>=24)
      h=h%24;
      if(h>12)
      h=h-12;
      int i=m;
      int j=s;
      
      h=180-(h*30);
      m=180-(m*6);
      s=180-(s*6);
      h=h-(i/2);
      m=m-(j/10);
      
      float hdeg=h*3.14/180;
      float mdeg=m*3.14/180;
      float sdeg=s*3.14/180;
            
      xh=ceil(65*y/100*sin(hdeg));
      yh=ceil(65*y/100*cos(hdeg));
      xm=ceil(95*y/100*sin(mdeg));
      ym=ceil(95*y/100*cos(mdeg));
      xs=ceil(95*y/100*sin(sdeg));
      ys=ceil(95*y/100*cos(sdeg));
}     
void OnPaint(HWND);

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

char szClassName[ ] = "WindowsApp";

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)

{               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WndProc;      /* This function is called by windows */
    wincl.style = CS_HREDRAW|CS_VREDRAW;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (hThisInstance,MAKEINTRESOURCE(100));
    wincl.hIconSm = LoadIcon (hThisInstance,MAKEINTRESOURCE(100));
    wincl.hCursor = LoadCursor (NULL, IDC_HAND );
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    wincl.hbrBackground = CreateSolidBrush(RGB(200,200,200));

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "EROIN'S CLOCK",       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           CW_USEDEFAULT,                 /* The programs width */
           CW_USEDEFAULT,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nFunsterStil);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam)
{
        switch(message)
        {
                       case WM_DESTROY:
                       KillTimer(hwnd,1);
                       EndPaint(hwnd,&ps);
                       PostQuitMessage(0);
                       break;
                       
                       case WM_PAINT:
                       OnPaint(hwnd);
                       break;
                       
                       case WM_TIMER:
                       OnTimer(hwnd);
                       break;
                       
                       case WM_SIZE:
                       x=LOWORD(lparam)/2;
                       y=HIWORD(lparam)/2;
                       break;
                       
                       default:
                       return DefWindowProc(hwnd,message,wparam,lparam);
        }
}
void OnPaint(HWND hwnd)
{       
     hdc=BeginPaint(hwnd,&ps);
     Create();
     Times();
     Display();
     SetTimer(hwnd,1,1000,NULL);
}
void OnTimer(HWND hwnd)
{
     SelectObject(hdc,hdbr);
     DeleteObject(hpen);
     Times();
     Create();
     Display();
}
