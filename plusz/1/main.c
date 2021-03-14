#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

int main (int argc, char* argv[]){

	int window;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(500 , 500);
	window=glutCreateWindow("Ablak");
	
	glutSetWindow(window);
	return 0;
}