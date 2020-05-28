#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
union REGS i,o;
int leftcolor[15];

int get_key()
 {union REGS in,out;
    in.h.ah=0;
	int86(22,&in,&out);
	return(out.h.ah);
 }
void showmouse()
 {  i.x.ax=1;
     int86(0x33,&i,&o);
  }
void getmouse(int *button,int *x,int *y)
 {  i.x.ax=3;
     int86(0x33,&i,&o);
	 *button=o.x.bx;
	 *x=o.x.cx;
	 *y=o.x.dx;
}
void hidemouse()
 {i.x.ax=2;
 int86(0x33,&i,&o);
 }
void restrictmouse(int left,int top,int right,int bottom)
 {i.x.ax=7;
  i.x.cx=left;
  i.x.dx=right;
   int86(0x33,&i,&o);
  i.x.ax=8;
  i.x.cx=top;
  i.x.dx=bottom;
  int86(0x33,&i,&o);
 }
void drawcolorpanel()
  { int left,top,color,c;
   left=100;
   top=436;
	color=getcolor();
	setcolor(YELLOW);
	settextstyle(DEFAULT_FONT,0,1);
	rectangle(1,431,635,457);
	setcolor(RED);
	outtextxy(10,440,"COLORS:");
	for(c=0;c<15;c++)
	 {setfillstyle(SOLID_FILL,c+1);
	  bar(left,top,left+16,top+16);
	  leftcolor[c]=left;
	  left+=26;
	 }
	setcolor(color);
}
void drawshapepanel()
{ int left,top,c,color;
    left=529;
     top=45;
    color=getcolor();
    setcolor(GREEN);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);

   for(c=0;c<7;c++)
    {rectangle(left,top,left+100,top+25);
       top+=30;
    }
   setcolor(RED);
   outtextxy(540,50,"BAR");
   outtextxy(540,80,"LINE");
   outtextxy(540,110,"PIXEL");
   outtextxy(540,140,"ELLIPSE");
   outtextxy(540,170,"FREEHAND");
   outtextxy(540,200,"RECTANGLE");
   outtextxy(540,230,"CLEAR");
   setcolor(color);
}

void changecolor(int x,int y)
{  int c,e;
   outtextxy(getmaxx()/2,getmaxx()/2,"h");
 for( c = 0 ; c <= 13 ; c++ )
   {
      if( x > leftcolor[c] && x < leftcolor[c+1] && y > 437 && y < 453 )
	 setcolor(c+1);
      if( x > leftcolor[14] && x < 505 && y > 437 && y < 453 )
	 setcolor(WHITE);
   }

}
char changeshape(int x,int y)
 {
   if(x>=529&&x<=633)
    {if (y>=45&&y<70)
      return('b');
	  if(y>=75&&y<100)
	  return('l');
	  if(y>=105&&y<130)
	      return('p');
	  if(y>=135&&y<160)
	  return('e');
      if(y>=165&&y<190)
	  return('f');
      if(y>=195&&y<220)
	  return('r');
	  if(y>=225&&y<250)
	   return('c');
    }
}
 void main()
  {int gd=DETECT,gm;
    char ch='f';
	int temp1,temp2,maxx,maxy,color,get,button,x,y;
	clrscr();
    initgraph(&gd,&gm,"C:\\TurboC3\\BGI");

     setcolor(RED);
     maxx=getmaxx();
     maxy=getmaxy();
     rectangle(0,0,getmaxx(),getmaxy());
     drawcolorpanel();
     drawshapepanel();
     setcolor(WHITE);
     settextstyle(SANS_SERIF_FONT,HORIZ_DIR,2);
     outtextxy(maxx/2-180,maxy-28,"PAINT IN C");

    showmouse();
     restrictmouse(1,1,maxx-1,maxy-1);
    rectangle(2,2,518,427);
     setviewport(1,1,519,428,1);
    while(1)
      { if(kbhit())
	    {
	    get=get_key();
	    if(get==1)
	    return;
	   }
	 getmouse(&button,&x,&y);
     //  while(button==0)
       //	getmouse(&button,&x,&y);
       //	temp1=x;
       //	temp2=y;
	 if(button==1)
	 {
		if((x>4&&x<635)&&(y>431&&y<457))

	     { changecolor(x,y);
	       /*	while(button==1)
		getmouse(&button,&x,&y);


		line(temp1,temp2,x,y); */
	       outtextxy(maxx/2,maxy/2,"HI");
	       }
	  if((x>535&&x<633)&&(y>40&&y<255))
	    ch=changeshape(x,y);
	 getmouse(&button,&x,&y);
	{   while(button==0)
	   getmouse(&button,&x,&y);
	   temp1=x;
	   temp2=y;
		 if ( ch == 'f' )
	 {
	    hidemouse();
	    while( button == 1 )
	    {
	       line(temp1,temp2,x,y);
	       temp1 = x;
	       temp2 = y;
	       getmouse(&button,&x,&y);
	    }
	    showmouse();
	 }

	 while( button == 1)
	    getmouse(&button,&x,&y);

	 /* to avoid interference of mouse while drawing */
	// hidemouse();

	 if( ch == 'p')
	    putpixel(x,y,getcolor());

	 else if ( ch == 'b' )
	 {
	    setfillstyle(SOLID_FILL,getcolor());
	    bar(temp1,temp2,x,y);
	 }
	 else if ( ch == 'l')
	    line(temp1,temp2,x,y);
	 else if ( ch == 'e')
	    ellipse(temp1,temp2,0,360,abs(x-temp1),abs(y-temp2));
	 else if ( ch == 'r' )
	    rectangle(temp1,temp2,x,y);
	 else if ( ch == 'c' )
	 {
	    ch = 'f';          // setting to freehand drawing
	    clearviewport();
	    color = getcolor();
	    setcolor(WHITE);
	    rectangle(2,2,518,427);
	    setcolor(color);

	 }

      }
	 }
     }
   getch();
}



























