#ifndef BALL_H
#define BALL_H

/**-
*Megadjuk a labda helyzetét és a sebeségét egy struktórán keresztül 
*/

typdef struct Ball
{
	//Labda helye az X tengelyen
	float x;
	
	//Labda helye az Y tengelyen
    float y;
	
	//Labda mérete
    float radius;
	
	//X és Y tengelyen lévő sebesség
    float speed_x;
    float speed_y;
}Ball;

void move_ball(Ball* ball, float x, float y);

void start_ball(Ball* ball, float x, float y);

void update_ball(Ball* ball, double time);

#endif /*BALL_H*/