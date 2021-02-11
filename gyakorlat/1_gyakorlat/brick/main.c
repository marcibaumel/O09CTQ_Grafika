#include "brick.h"

#include <stdio.h>

int main(int argc, char* argv[]){
	Brick brick;
	double a, b, c, g;
	double surface, volume, rectangle_slide;
	int con=0;


	do{
		printf ("The 'a' side size: \n" );
			scanf ("%lf" , &a);
		
		printf ("The 'b' side size: \n" );
			scanf ("%lf" , &b);
		
		printf ("The 'b' side size: \n" );
			scanf ("%lf" , &c);
			
		if(a>0 && b>0 && c>0){
			con=1;
			set_size_data(&brick, a, b, c);
		}
		else{
			printf("\n HIBA \n");
		}
	}while(con!=1);
	
	printf("\n\n--Results:-- \n\n");
	
	//set_size_data(&brick, 75, 5, 6);
	printf("\nSet Data: %f %f %f \n\n" ,brick.a ,brick.b, brick.c);
	
	volume=calc_volume(&brick);
	printf("Volume of the brick: %f \n\n", volume);
	
	surface=calc_surface(&brick);
	printf("Surface of the brick: %f \n\n" ,surface);
	
	rectangle_slide=calc_rectangle_side(&brick);
	if(rectangle_slide==0){
		printf("No rectangle in this brick! \n\n");
	}
	else{
		printf("There is a reactangle in this brick! \n");
	}
	
	printf ("Are you done ? (Press a button)" );
	scanf ("%f" , &g);
	return 0;
}