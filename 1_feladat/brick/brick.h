#ifndef BRICK_H
#define BRICK_H

/**
 * Data of a brick
 */
 
typedef struct Brick
{
	double a;
	double b;
	double c;
	
} Brick;

void set_size_data(Brick* brick, double a, double b, double c);

double calc_volume (const Brick* brick);

double calc_surface(const Brick* brick);

double calc_rectangle_side(const Brick* brick);

#endif //BRICK_H