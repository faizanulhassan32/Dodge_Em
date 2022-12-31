//============================================================================
// Name        : game.cpp
// Author      : Hassan Mustafa
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Dodge 'Em...
//============================================================================
 
#ifndef DODGE_CPP_
#define DODGE_CPP_
#include "util.h"
#include <iostream>
#include <fstream> 
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;
	float px=334;	          // Initial X co-ordinates for players car
	float py=30;	          // Initial Y co-ordinates for players car
	float pvar1=px;		  // Global variable for X of players car 	
	float pvar2=py;		  // Global variable for Y of players car
	int score;		  // Global variable for gamescore
	float oppx=442;		 //  Initial X co-ordiantes for opponents car
	float oppy=30;		 //  Initial Y co-ordiantes for opponents car
	float oppvar3=oppx;       // Global variable for X of opponents car 	
	float oppvar4=oppy;       // Global variable for Y of opponents car 	
	int lives=3;              // Global variable for total number of lives..
	int gamemenu=0;
	int counter[76];	  //Since there are 76 food items in the arena so declaring a Counter Array for that
	int highScore[100];      // Global array to maintain highscore..	


	// X Co-ordinates of food
	int FOODX[76] = {  38,110,180,250,320,460,530,600,670,732,732,
			   732,732,732,732,732,732,670,600,530,460,320, 
			   250,180,110,38,38,38,38,38,38,38,120,180,250,320,
			   460,530,600,650,650,650,650,650,650,600,530,460,
			   320,250,180,115,115,115, 115 ,115,190,250,320,460, 
			   530,580,580,580,580,530,460,320,250,190,190,190,285,490,490,285  } ;

	// Y Co-ordinates of food
	int FOODY[76] = {  30,30,30,30,30,30,30,30,30,30,245,
			   175,105,345,415,485,540,540,540,540,540,
			   540,540,540,540,540,485,415,345,245,175,105,90,
			   90,90,90,90,90,90,90,175,245,345,415,482,
			   482,482,482,482,482,482,482,415,345,245,175,148,148,
		           148,148,148,148,245,345,418,418,418,418,418,418,345,245,208,208,358,358  } ;

	int FOODCOUNT=0;  // Global Counter to count number of food items eaten
	int FOODSIZE = 15;  // global varaible for Size of Food
	float* FOODCOLOR = colors[WHITE]; //global variable for Food color


// seed the random numbers generator by current time (see the documentation of srand for further help)...
	
/*  Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) 
{
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

/*
 * Main Canvas drawing function.
 * */

void drawingPlayersCar()
{
float px = pvar1; 		// x co-ordinate for players car
	float py = pvar2;  		// y co-ordinate for players car
	float width = 7; 
	float height = 7;
	float* color = colors[RED];	// color of players car
	float radius = 2;		// radius of players car
	DrawRoundRect(px,py,width,height,color,radius); // bottom left tyre
	DrawRoundRect(px+width*3,py,width,height,color,radius); // bottom right tyre
	DrawRoundRect(px+width*3,py+height*4,width,height,color,radius); // top right tyre
	DrawRoundRect(px,py+height*4,width,height,color,radius); // top left tyre
	DrawRoundRect(px, py+height*2, width, height, color, radius/2); // body left rect
	DrawRoundRect(px+width, py+height, width*2, height*3, color, radius/2); // body center rect
	DrawRoundRect(px+width*3, py+height*2, width, height, color, radius/2); // body right rects

}

void drawingOpponentsCar()
{
//Drawing opponents car

	float oppx = oppvar3; 		// x co-ordinate for players car
	float oppy = oppvar4;  		// y co-ordinate for players car
	float width1 = 7; 
	float height1 = 7;
	float* color1 = colors[BLUE];	// color of players car
	float radius1 = 2;		// radius of players car
	DrawRoundRect(oppx,oppy,width1,height1,color1,radius1); // bottom left tyre
	DrawRoundRect(oppx+width1*3,oppy,width1,height1,color1,radius1); // bottom right tyre
	DrawRoundRect(oppx+width1*3,oppy+height1*4,width1,height1,color1,radius1); // top right tyre
	DrawRoundRect(oppx,oppy+height1*4,width1,height1,color1,radius1); // top left tyre
	DrawRoundRect(oppx, oppy+height1*2, width1, height1, color1, radius1/2); // body left rect
	DrawRoundRect(oppx+width1, oppy+height1, width1*2, height1*3, color1, radius1/2); // body center rect
	DrawRoundRect(oppx+width1*3, oppy+height1*2, width1, height1, color1, radius1/2); // body right rects

}

void drawingArena()
{
//Drawing Arena

	string scorex="Score = "+to_string(score);	// displaying score
	string livesx="Lives = "+to_string(lives);	// displaying lives	
	DrawString( 100, 660, scorex , colors[WHITE]);
	DrawString( 100, 620, livesx, colors[WHITE]);

	int gap_turn = 50;
	int sx = 20;
	int sy = 20;
	int swidth = 800/2 - gap_turn/2; // half width
	int sheight = 10;
	float *scolor = colors[WHITE];

	DrawRectangle(sx+4, sy-15, swidth-40, sheight*1.5, scolor); // bottom left
	DrawRectangle(sx+59, sy+52, swidth-95, sheight*1, scolor); // bottom left second line
	DrawRectangle(sx+137, sy+111, swidth-172, sheight*1, scolor); // bottom left third line
	DrawRectangle(sx+205, sy+168, swidth-242, sheight*1, scolor); // bottom left fourth line

	DrawRectangle(sx-5 + swidth + gap_turn, sy-14, swidth-42, sheight*1.5, scolor); // bottom right
	DrawRectangle(sx-5 + swidth + gap_turn, sy+52, swidth-98, sheight*1, scolor); // bottom right second line
	DrawRectangle(sx-8 + swidth + gap_turn, sy+112, swidth-176, sheight*1, scolor); // bottom right third line
	DrawRectangle(sx-8 + swidth + gap_turn, sy+170, swidth-244, sheight*1, scolor); // bottom right fourth line

	DrawRectangle(sx-45+swidth*2+gap_turn, sy-10+sheight, sheight*1.5, swidth-122, scolor); // right down
	DrawRectangle(sx-120+swidth*2+gap_turn, sy+54+sheight, sheight*1.5, swidth-188, scolor); // right down second line
	DrawRectangle(sx-200+swidth*2+gap_turn, sy+114+sheight, sheight*1.5, swidth-250, scolor); // right down third line
	DrawRectangle(sx-268+swidth*2+gap_turn, sy+172+sheight, sheight*1.5, swidth-310, scolor); // right down fourth line

	DrawRectangle(sx-45+swidth*2+gap_turn, sy-120+sheight+swidth+gap_turn, sheight*1.5, swidth-130, scolor); // right up
	DrawRectangle(sx-120+swidth*2+gap_turn, sy-120+sheight+swidth+gap_turn, sheight*1.5, swidth-188, scolor); // right up second line
	DrawRectangle(sx-200+swidth*2+gap_turn, sy-120+sheight+swidth+gap_turn, sheight*1.5, swidth-250, scolor); // right up third line	
	DrawRectangle(sx-268+swidth*2+gap_turn, sy-120+sheight+swidth+gap_turn, sheight*1.5, swidth-306, scolor); // right up fourth line

	DrawRectangle(sx-420+ swidth + gap_turn, sy+560, swidth-40, sheight*1.5, scolor); // top left
	DrawRectangle(sx-365+ swidth + gap_turn, sy+504, swidth-95, sheight*1, scolor); // top left second line
	DrawRectangle(sx-288+ swidth + gap_turn, sy+444, swidth-170, sheight*1, scolor); // top left third line
	DrawRectangle(sx-220+ swidth + gap_turn, sy+383, swidth-240, sheight*1, scolor); // top left fourth line

	DrawRectangle(sx+418, sy+560, swidth-38, sheight*1.5, scolor); // top right
	DrawRectangle(sx+418, sy+504, swidth-98, sheight*1, scolor); // top right second line
	DrawRectangle(sx+418, sy+442, swidth-178, sheight*1, scolor); // top right third line
	DrawRectangle(sx+416, sy+386, swidth-244, sheight*1, scolor); // top right fourth line

	DrawRectangle(sx+5-sheight*1.5, sy-119+sheight+swidth+gap_turn, sheight*1.5, swidth-130, scolor); // left up
	DrawRectangle(sx+75-sheight*1.5, sy-120+sheight+swidth+gap_turn, sheight*1.5, swidth-190, scolor); // left up second line
	DrawRectangle(sx+151-sheight*1.5, sy-120+sheight+swidth+gap_turn, sheight*1.5, swidth-250, scolor); // left up third line
	DrawRectangle(sx+220-sheight*1.5, sy-120+sheight+swidth+gap_turn, sheight*1.5, swidth-310, scolor); // left up fourth line
	
	DrawRectangle(sx+5-sheight*1.5, sy-11+sheight, sheight*1.5, swidth-125, scolor); // left down
	DrawRectangle(sx+75-sheight*1.5, sy+56+sheight, sheight*1.5, swidth-192, scolor); // left down second line
	DrawRectangle(sx+152-sheight*1.5, sy+114+sheight, sheight*1.5, swidth-250, scolor); // left down third line
	DrawRectangle(sx+220-sheight*1.5, sy+172+sheight, sheight*1.5, swidth-310, scolor); // left down fourth line
	
	DrawRectangle(sx+320, sy+316, swidth-260, sheight*1, scolor); // for middle box
	DrawRectangle(sx+320, sy+236, swidth-260, sheight*1, scolor); // for middle box
	DrawRectangle(sx+335-sheight*1.5, sy+238+sheight, sheight*1.5, swidth-355, scolor); // for middle box
	DrawRectangle(sx+435-sheight*1.5, sy+238+sheight, sheight*1.5, swidth-355, scolor); // for middle box
	DrawRectangle(sx+335-sheight*1.5, sy+285+sheight, sheight*1.5, swidth-355, scolor); // for middle box
	DrawRectangle(sx+435-sheight*1.5, sy+285+sheight, sheight*1.5, swidth-355, scolor); // for middle box

	// for loop to draw 76 food items with in arena..
	
	for ( int i=0 ; i<76 ; i++ )
	{
	if ( counter[i] == 0 )
	DrawSquare ( FOODX[i] , FOODY[i] , FOODSIZE , FOODCOLOR );
	}
	
}



void startGame()
{
	drawingPlayersCar();
	drawingOpponentsCar();
	drawingArena();
		
}

void gameMenu()
{
	if (gamemenu == 0)	// initially values is set to 0
	{
		DrawString( 250 , 500 , "To Start The Game Press : 1" , colors[WHITE]);
		DrawString( 250 , 400 , "For High Score Press : 2" , colors[WHITE]);
		DrawString( 250 , 300 , "For Help Press : 3" , colors[WHITE]);
		DrawString( 250 , 200 , "To Exit Press : 4" , colors[WHITE]);
	}

	else if (gamemenu == 1)		// 1 pressed for starting the game
	{
		startGame();
	}

	else if (gamemenu == 2)		// 2 pressed for high scores
	{
		string scoreHigh="High Score = "+to_string(highScore[0]);
		DrawString( 250 , 200 , scoreHigh , colors[WHITE]);
	}

	else if (gamemenu == 3)		// 3 pressed for help
	{
		DrawString( 50, 550, "Welcome To Dodge_em", colors[WHITE]);
		DrawString( 50, 450, "Use Arrow Keys To Play The Game", colors[WHITE]);
		DrawString( 50, 350, "Collect All The Foods To Complete The Level", colors[WHITE]);
		DrawString( 50, 250, "Avoid Hitting The Opponents Car", colors[WHITE]);
		DrawString( 50, 150, "Enjoy!! And Good Luck", colors[WHITE]);
	}

	else if (gamemenu == 4)		// 4 pressed for exit
	{
		exit(1);
	}

}


void GameDisplay()
{

	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0.1/*Red Component*/, 0.1 ,	//148.0/255/*Green Component*/,
			0.1 /*Blue Component*/, 0.1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

	// calling some functions from util.cpp file to help students

	//Square at 400,20 position
	//DrawSquare( 400 , 20 ,40,colors[RED]); 
	//Square at 250,250 position
	
	//Display Score
	//DrawString( 50, 800, "Score=0", colors[MISTY_ROSE]);
	//Triangle at 300, 450 position
	//DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
	// Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
	//Circle at 50, 670 position;
	
	//Line from 550,50 to 550,480 with width 10
	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	
	gameMenu();
	glutSwapBuffers(); // do not modify this line.. or draw anything below this line


/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */
}
void NonPrintableKeys(int key, int x, int y) 
{	
	//GLUT_KEY_UP/DOWN/RIGHT/LEFT is constant and contains ASCII for arrow keys/
	
	// For Left Gap
	 
	if ( (key == GLUT_KEY_RIGHT) && ( ( pvar1==38 ) && ( pvar2>=280 && pvar2<=340 ))  )	
	{
	pvar1=pvar1+77;
	} 
	else if ( (key == GLUT_KEY_RIGHT) && ( ( pvar1==115 ) && ( pvar2>=280 && pvar2<=340 ))  )	

	{pvar1=pvar1+75;}
	   
	else if ( (key == GLUT_KEY_RIGHT) && ( ( pvar1==190 ) && ( pvar2>=280 && pvar2<=340 ))  )
	      	
	{pvar1=pvar1+87;}

		if ( (key == GLUT_KEY_LEFT) && ( ( pvar1==115 ) && ( pvar2>=280 && pvar2<=340 ))  )	
		{
		pvar1=pvar1-77;
		} 
		else if ( (key == GLUT_KEY_LEFT) && ( ( pvar1==190 ) && ( pvar2>=280 && pvar2<=340 ))  )	

		{pvar1=pvar1-75;}
		   
		else if ( (key == GLUT_KEY_LEFT) && ( ( pvar1==277 ) && ( pvar2>=280 && pvar2<=340 ))  )
		      	
		{pvar1=pvar1-87;}


	// For Upper Gap
	          
	else if( (key == GLUT_KEY_DOWN) && (( pvar2==540 ) && ( pvar1>300 && pvar1<500 ))  )		 
	{
	pvar2=pvar2-58;
	}
	else if( (key == GLUT_KEY_DOWN) && (( pvar2==482 ) && ( pvar1>300 && pvar1<500 ))  )		 
	{
	pvar2=pvar2-64;	
	}
	else if( (key == GLUT_KEY_DOWN) && (( pvar2==418 ) && ( pvar1>300 && pvar1<500 ))  )		 
	{
	pvar2=pvar2-60;	
	}		
		else if( (key == GLUT_KEY_UP) && (( pvar2==482 ) && ( pvar1>300 && pvar1<500 ))  )		 
		{
		pvar2=pvar2+58;
		}
		
		else if( (key == GLUT_KEY_UP) && (( pvar2==418 ) && ( pvar1>300 && pvar1<500 ))  )		 
		{
		pvar2=pvar2+64;
		}		
		else if( (key == GLUT_KEY_UP) && (( pvar2==358 ) && ( pvar1>300 && pvar1<500 ))  )		 
		{
		pvar2=pvar2+60;
		}
		
	// For Right Gap

	if( (key == GLUT_KEY_LEFT) && (( pvar1==732 ) && ( pvar2>=250 && pvar2<=350 ))  )		 
	{
	pvar1=pvar1-82;
	}
	else if( (key == GLUT_KEY_LEFT) && (( pvar1==650 ) && ( pvar2>250 && pvar2<350 ))  )		 
	{
	pvar1=pvar1-70;
	}
	else if( (key == GLUT_KEY_LEFT) && (( pvar1==580 ) && ( pvar2>250 && pvar2<350 ))  )		 
	{
	pvar1=pvar1-90;
	}

		if( (key == GLUT_KEY_RIGHT) && (( pvar1==650 ) && ( pvar2>=250 && pvar2<=350 ))  )		 	
		{
		pvar1=pvar1+82;
		}
		else if( (key == GLUT_KEY_RIGHT) && (( pvar1==580 ) && ( pvar2>250 && pvar2<350 ))  )		 
		{	
		pvar1=pvar1+70;
		}
		else if( (key == GLUT_KEY_RIGHT) && (( pvar1==490 ) && ( pvar2>250 && pvar2<350 ))  )		 
		{
		pvar1=pvar1+90;
		}
		
	// For Lower Gap	
	
	else if( (key == GLUT_KEY_UP) && (( pvar2==30 ) && ( pvar1>=334 && pvar1<=440 ))  )		
	{
	pvar2=pvar2+60;
	}	
	else if( (key == GLUT_KEY_UP) && (( pvar2==90 ) && ( pvar1>=334 && pvar1<=440 ))  )		 
	{
	pvar2=pvar2+58;
	}
	else if( (key == GLUT_KEY_UP) && (( pvar2==148 ) && ( pvar1>=334 && pvar1<=500 ))  )		 
	{
	pvar2=pvar2+60;
	}

		else if( (key == GLUT_KEY_DOWN) && (( pvar2==90 ) && ( pvar1>=334 && pvar1<=440 ))  )		 
		{
		pvar2=pvar2-60;
		}		
		else if( (key == GLUT_KEY_DOWN) && (( pvar2==148 ) && ( pvar1>=334 && pvar1<=440 ))  )		 
		{
		pvar2=pvar2-58;
		}		
		else if( (key == GLUT_KEY_DOWN) && (( pvar2==208 ) && ( pvar1>=334 && pvar1<=500 ))  )		 
		{	
		pvar2=pvar2-60;
		}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y)
{
	if (key == 27  /* escape key ASCII*/) 
	{
	gamemenu=0;
	}

	if ( key == '1' )
	gamemenu = 1;

	if ( key == '2' )
	gamemenu = 2;

	if ( key == '3' )
	gamemenu = 3;

	if ( key == '4' )
	exit(1);
		
	glutPostRedisplay();
}



/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */

void PCarMovement()
{
	// For first layer of players car

	if ( pvar1 != 38 && pvar2 == 30 )	
	pvar1--;

	else if ( pvar2 != 540 && pvar1 == 38)
	pvar2++;
	
	else if ( pvar1 != 732 && pvar2 == 540 )
	pvar1++;

	else if ( pvar2 != 595 && pvar1 == 732 )
	pvar2--;

		// For second layer of players car

		else if (pvar2!=482 && pvar1==115)
		pvar2++;

		else if (pvar1!=650 && pvar2==482)
		pvar1++;

		else if ( pvar2!=90 && pvar1==650 )
		pvar2--;

		else if ( pvar1!=115 && pvar2==90 )
		pvar1--;


			// For third layer of players car

			else if (pvar2!=418 && pvar1==190)
			pvar2++;

			else if (pvar1!=580 && pvar2==418)
			pvar1++;

			else if ( pvar2!=148 && pvar1==580 )
			pvar2--;

			else if ( pvar1!=150 && pvar2==148 )
			pvar1--;

				// For fourth layer of players car

				else if ( pvar2!=358 && pvar1==277)
				pvar2++;

				else if ( pvar1!=490 && pvar2==358)
				pvar1++;
				
				else if ( pvar2!=208 && pvar1==490)			
				pvar2--;

				else if (pvar1!=277 && pvar2==208)
				pvar1--;

	
}

void OPPCarMovement()
{
//For first layer of opponents car
	
	if ( oppvar3 != 732 && oppvar4 == 30 )	
	oppvar3++;
	
	else if ( oppvar4 != 540 && oppvar3 == 732)
	oppvar4++;
	
	else if ( oppvar3 != 38 && oppvar4 == 540 )
	{oppvar3--;
		if ( oppvar3>= 300 && oppvar3<= 410 && oppvar4 == 540 )
		{
		oppvar4 = oppvar4 - 58;
		}
	}
	else if ( oppvar4 != 30 && oppvar3 == 38 )
	oppvar4--;

		// For second layer of opponents car
		else if ( oppvar3 != 110 && oppvar4 == 482 )
		oppvar3--;
		
		else if ( oppvar4 != 90 && oppvar3 == 110 )
		oppvar4--;

		else if ( oppvar3 != 650 && oppvar4 == 90 )
		{oppvar3++;
			if ( oppvar3>= 380 && oppvar3<= 442 && oppvar4 == 90 )
			{
			oppvar4 = oppvar4 - 60;
			}
		}
		else if ( oppvar4 != 482 && oppvar3 == 650 )		
		oppvar4++;
		

}

void dismissFood()
{
//for loop to dismiss food items
	for ( int i=0; i<76; i++ )
	{
		if (pvar1 == FOODX[i] && pvar2 == FOODY[i] && counter[i] == 0 )
		{
		score++;
		counter[i]=1;
		}

	glutPostRedisplay();
	}
}

void carsCollision()
{
	// if condition for players and opponents cars collision
	if (pvar1==oppvar3 && pvar2==oppvar4)
	{  
		// Writing to file
		cout<<"This is score"<<score;
		//writing score to a file
		ofstream fout;
		fout.open ("high score.txt");
		fout <<score<< endl;	
		fout.close();
		

		// Redrawing the eaten food items again after players and opponents cars collision
		for ( int i=0 ; i<76 ; i++ )
	       	{
			if ( counter[i] == 0 )
			  {
				DrawSquare ( FOODX[i] , FOODY[i] , FOODSIZE , FOODCOLOR );
				glutPostRedisplay();
			  }
			else
				counter[i]=0;	
		}

		// resetting the X and Y co-ordiantes of players and opponents car after collision
		pvar1=334; 
		pvar2=30;
		oppvar3=442;
		oppvar4=30;
		

		// decrementing the lives after collision
		lives--;

	
		//if condition when all three lives are wasted
		if ( lives==0 )
		{

			//reading from a file
			string fileScore;
			fstream fin ("high score.txt"); //name of the file it is supposed to read
			if (fin.is_open())
			{
				while ( getline (fin, fileScore) ) //this loop will run depending on the number of lines in the file
				{
				   for (int i=0; i<100; i++) {
				    highScore[i] = stoi(fileScore); } // stoi is used to convert string into int..
							
				}
				fin.close();
			}

			
			else 
			      cout << "Unable to open file"; 
			
	// Loop for sorting the highScore array in descending order so that the first index value is always the highest number..
		       for( int i = 0 ; i<100 ; i++)
		       {
				for(int j=i+1 ; j<=100 ; j++)
				{
					if(highScore[i] < highScore[j])
					{
					int hs = highScore[i];
					highScore[i] = highScore[j];
	       				highScore[j] = hs;
					}
				}
			}

			// Exiting the game arena when three lives are lost..
			exit(1); 	
		}

		//reseting the game score after collision
		score=0;
	
	}
}

void Timer(int m)
{
	// implement your functionality here
	// once again we tell the library to call our Timer function after next 1000/FPS
	dismissFood();
	PCarMovement();
	OPPCarMovement();
	carsCollision();

	glutPostRedisplay();
	glutTimerFunc(1, Timer, 0);
}
/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout <<"X "<< x << " " <<"Y "<< y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {

	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x1, int y1) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{

	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */

int main(int argc, char*argv[]) {

	//b = new Board(60, 60); // create a new board object to use in the Display Function ...

	int width = 800, height = 700; // i have set my window size to be 800 x 600
	//b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Made By Faizan"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */

