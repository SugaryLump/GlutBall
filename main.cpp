#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "sphere.hpp"
#include <time.h>

#define _USE_MATH_DEFINES
#define EXPLORER 0
#define FPS 1
#include <math.h>
#include <vector>
#define SLICES 10
#define STACKS 10
#define SLICES 10

struct Vertex {
	float x;
	float y;
	float z;
	Vertex(float x_, float y_, float z_) {
		x = x_;
		y = y_;
		z = z_;
	}
	Vertex() {
		x = 0;
		y = 0;
		z = 0;
	}
};

short cameraMode;
float alpha;
float beta;
Vertex cameraPosition;
Vertex cameraLookAt;
short previousKeysState[256];
short keysState[256];
short specialKeysState[112];
int prevMouseX;
int prevMouseY;
int mouseDeltaX;
int mouseDeltaY;
bool pointerWarp;
std::vector<Sphere*> spheres;

void normalizeAlphaBeta() {
	if (alpha > 2 * M_PI) {
		alpha -= 2 * M_PI;
	}
	else if (alpha < 0) {
		alpha += 2 * M_PI;
	}

	if (beta > M_PI_2) {
		beta = M_PI_2 - 0.01;
	}
	else if (beta < -M_PI_2) {
		beta = -M_PI_2 + 0.01;
	}
}

Vertex fromSpherical(float alpha, float beta, float radius) {
	float x = cos(beta) * sin(alpha) * radius;
	float y = sin(beta) * radius;
	float z = cos(beta) * cos(alpha) * radius;
	return Vertex(x,y,z);
}

Vertex fromPolar(float alpha, float radius, float y) {
		return Vertex(sin(alpha) * radius, y, cos(alpha) * radius);
}

void drawTriangle(Vertex v1, Vertex v2, Vertex v3) {
	glVertex3f(v1.x, v1.y, v1.z);
	glVertex3f(v2.x, v2.y, v2.z);
	glVertex3f(v3.x, v3.y, v3.z);
}

void drawRoom() {
	glBegin(GL_TRIANGLES);
	for (int x = 0; x < 100; x++) {
		for(int z = 0; z < 100; z++) {
			glColor3f(0.8, 0.5 + 0.5/10000*x*z, 0.8);
			Vertex v1 = Vertex(-25 + x*0.5, 0, -25 + z*0.5);
			Vertex v2 = Vertex(-25 + x*0.5, 0, -25 + (z + 1)*0.5);
			Vertex v3 = Vertex(-25 + (x+1)*0.5, 0, -25 + (1 + z)*0.5);
			Vertex v4 = Vertex(-25 + (x+1)*0.5, 0, -25 + z*0.5);
			drawTriangle(v1, v2, v3);
			drawTriangle(v1, v3, v4);
		}
	}
	glEnd();
	glPushMatrix();
	glTranslatef(0, 25, -25);
	glRotatef(90, 1, 0, 0);
	glBegin(GL_TRIANGLES);
	for (int x = 0; x < 100; x++) {
		for(int z = 0; z < 100; z++) {
			glColor3f(0.8, 0.5 + 0.5/10000*x*z, 0.8);
			Vertex v1 = Vertex(-25 + x*0.5, 0, -25 + z*0.5);
			Vertex v2 = Vertex(-25 + x*0.5, 0, -25 + (z + 1)*0.5);
			Vertex v3 = Vertex(-25 + (x+1)*0.5, 0, -25 + (1 + z)*0.5);
			Vertex v4 = Vertex(-25 + (x+1)*0.5, 0, -25 + z*0.5);
			drawTriangle(v1, v2, v3);
			drawTriangle(v1, v3, v4);
		}
	}
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 25, 25);
	glRotatef(-90, 1, 0, 0);
	glBegin(GL_TRIANGLES);
	for (int x = 0; x < 100; x++) {
		for(int z = 0; z < 100; z++) {
			glColor3f(0.8, 0.5 + 0.5/10000*x*z, 0.8);
			Vertex v1 = Vertex(-25 + x*0.5, 0, -25 + z*0.5);
			Vertex v2 = Vertex(-25 + x*0.5, 0, -25 + (z + 1)*0.5);
			Vertex v3 = Vertex(-25 + (x+1)*0.5, 0, -25 + (1 + z)*0.5);
			Vertex v4 = Vertex(-25 + (x+1)*0.5, 0, -25 + z*0.5);
			drawTriangle(v1, v2, v3);
			drawTriangle(v1, v3, v4);
		}
	}
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(25, 25, 0);
	glRotatef(90, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	for (int x = 0; x < 100; x++) {
		for(int z = 0; z < 100; z++) {
			glColor3f(0.8, 0.5 + 0.5/10000*x*z, 0.8);
			Vertex v1 = Vertex(-25 + x*0.5, 0, -25 + z*0.5);
			Vertex v2 = Vertex(-25 + x*0.5, 0, -25 + (z + 1)*0.5);
			Vertex v3 = Vertex(-25 + (x+1)*0.5, 0, -25 + (1 + z)*0.5);
			Vertex v4 = Vertex(-25 + (x+1)*0.5, 0, -25 + z*0.5);
			drawTriangle(v1, v2, v3);
			drawTriangle(v1, v3, v4);
		}
	}
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-25, 25, 0);
	glRotatef(-90, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	for (int x = 0; x < 100; x++) {
		for(int z = 0; z < 100; z++) {
			glColor3f(0.8, 0.5 + 0.5/10000*x*z, 0.8);
			Vertex v1 = Vertex(-25 + x*0.5, 0, -25 + z*0.5);
			Vertex v2 = Vertex(-25 + x*0.5, 0, -25 + (z + 1)*0.5);
			Vertex v3 = Vertex(-25 + (x+1)*0.5, 0, -25 + (1 + z)*0.5);
			Vertex v4 = Vertex(-25 + (x+1)*0.5, 0, -25 + z*0.5);
			drawTriangle(v1, v2, v3);
			drawTriangle(v1, v3, v4);
		}
	}
	glEnd();
	glPopMatrix();
}

void drawSpheres() {
	for (int s = 0; s < spheres.size(); s++) {
		Sphere* sph = spheres[s];
		float r = sph->radius;
		glPushMatrix();
		glTranslatef(sph->x, sph->y, sph->z);
		glBegin(GL_TRIANGLES);
		glColor3f(sph->r, sph->g, sph->b);

		Vertex bottom = Vertex(0, - sph->radius, 0);
		float alpha = 0;
		for (int sl = 0; sl < SLICES; sl++) {
			if (sl < SLICES - 1) {
				Vertex v1 = fromSpherical(alpha, -M_PI_2 + M_PI / STACKS, r);
				Vertex v2 = fromSpherical(alpha + 2 * M_PI / SLICES, -M_PI_2 + M_PI / STACKS, r);
				drawTriangle(bottom, v2, v1);
			}
			else {
				Vertex v1 = fromSpherical(alpha, -M_PI_2 + M_PI / STACKS, r);
				Vertex v2 = fromSpherical(0, -M_PI_2 + M_PI / STACKS, r);
				drawTriangle(bottom, v2, v1);
			}
			alpha += 2 * M_PI / SLICES;
		}

		Vertex top = Vertex(0, sph->radius, 0);
		alpha = 0;
		for (int sl = 0; sl < SLICES; sl++) {
			if (sl < SLICES - 1) {
				Vertex v1 = fromSpherical(alpha, M_PI_2 - M_PI / STACKS, r);
				Vertex v2 = fromSpherical(alpha + 2 * M_PI / SLICES, M_PI_2 - M_PI / STACKS, r);
				drawTriangle(top, v1, v2);
			}
			else {
				Vertex v1 = fromSpherical(alpha, M_PI_2 - M_PI / STACKS, r);
				Vertex v2 = fromSpherical(0, M_PI_2 - M_PI / STACKS, r);
				drawTriangle(top, v1, v2);
			}
			alpha += 2 * M_PI / SLICES;
		}

		float beta = -M_PI_2 + M_PI/SLICES;
		for (int st = 0; st < STACKS - 2; st++) {
			alpha = 0;
			for (int sl = 0; sl < STACKS; sl++) {
				if (sl < SLICES - 1) {
					Vertex v1 = fromSpherical(alpha, beta, r);
					Vertex v2 = fromSpherical(alpha, beta + M_PI/SLICES, r);
					Vertex v3 = fromSpherical(alpha + 2 * M_PI/SLICES, beta, r);
					Vertex v4 = fromSpherical(alpha + 2 * M_PI/SLICES, beta + M_PI/SLICES, r);
					drawTriangle(v2, v3, v4);
					drawTriangle(v3, v2, v1);
				}
				else {
					Vertex v1 = fromSpherical(alpha, beta, r);
					Vertex v2 = fromSpherical(alpha, beta + M_PI/SLICES, r);
					Vertex v3 = fromSpherical(0, beta, r);
					Vertex v4 = fromSpherical(0, beta + M_PI/SLICES, r);
					drawTriangle(v2, v3, v4);
					drawTriangle(v3, v2, v1);
				}
				alpha += 2 * M_PI / SLICES;
			}
			beta += M_PI/SLICES;
		}
		glEnd();
		glPopMatrix();
	}
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(cameraPosition.x,cameraPosition.y,cameraPosition.z, 
		      cameraLookAt.x,cameraLookAt.y,cameraLookAt.z,
			  0.0f,1.0f,0.0f);

	drawRoom();
	drawSpheres();

	// End of frame
	glutSwapBuffers();
}


// write function to process keyboard events
void update() {
	short hMoveInput = keysState['d'] - keysState['a'];
	short vMoveInput = keysState['w'] - keysState['s'];
	short extraMoveInput = keysState[' '] - keysState['c'];

	if (keysState['m'] == 1 && previousKeysState['m'] == 0) {
		if (cameraMode == EXPLORER)
			cameraMode = FPS;
		else
			cameraMode = EXPLORER;
	}
	
	if (cameraMode == EXPLORER) {
		alpha += 0.05 * hMoveInput;
		beta += 0.05 * vMoveInput;
		normalizeAlphaBeta();

		Vertex tmp = fromSpherical(alpha, beta, 5);
		cameraPosition.x = tmp.x + cameraLookAt.x;
		cameraPosition.y = tmp.y + cameraLookAt.y;
		cameraPosition.z = tmp.z + cameraLookAt.z;
	}
	else if (cameraMode == FPS) {
		//Mouse Handler
		alpha -= mouseDeltaX * 0.005;
		beta += mouseDeltaY * 0.005;
		normalizeAlphaBeta();
		Vertex tmp = fromSpherical(alpha + M_PI, -beta, 5);
		cameraLookAt.x = tmp.x + cameraPosition.x;
		cameraLookAt.y = tmp.y + cameraPosition.y;
		cameraLookAt.z = tmp.z + cameraPosition.z;

		//Keyboard Handler
		Vertex fVector = fromSpherical(alpha + M_PI, -beta, 0.075);
		Vertex sVector = fromSpherical(alpha + M_PI_2, 0, 0.075);
		float vertical = 0.05 * extraMoveInput;
		cameraPosition.x += fVector.x * vMoveInput + sVector.x * hMoveInput;
		cameraPosition.y += fVector.y * vMoveInput + sVector.y * hMoveInput + vertical;
		cameraPosition.z += fVector.z * vMoveInput + sVector.z * hMoveInput;
		cameraLookAt.x += fVector.x * vMoveInput + sVector.x * hMoveInput;
		cameraLookAt.y += fVector.y * vMoveInput + sVector.y * hMoveInput;
		cameraLookAt.z += fVector.z * vMoveInput + sVector.z * hMoveInput;
	}

	if ((keysState['b'] && !previousKeysState['b']) || keysState['r']) {
		spheres.push_back(new Sphere(cameraPosition.x, cameraPosition.y, cameraPosition.z,
										cameraLookAt.x, cameraLookAt.y, cameraLookAt.z));
	}
	if ((keysState['q'] && !previousKeysState['q']) || keysState['e']) {
		for (int s = 0; s < 5; s++) {
			float randomAlpha = alpha + (float)(rand() % 5 + 1) / 10 - 0.3;
			float randomBeta = beta + (float)(rand() % 5 + 1) / 10 - 0.3;
			float randomRadius = 5 + (float)(rand() % 5 + 1) / 10 - 0.3;
			Vertex random = fromSpherical(randomAlpha + M_PI, -randomBeta, randomRadius);
			random.x += cameraPosition.x;
			random.y += cameraPosition.y;
			random.z += cameraPosition.z;
			spheres.push_back(new Sphere(cameraPosition.x, cameraPosition.y, cameraPosition.z,
										random.x, random.y, random.z));
		}
	}

	if ((keysState['k'] && !previousKeysState['k'])) {
		spheres.push_back(new RocketSphere(cameraPosition.x, cameraPosition.y, cameraPosition.z,
										cameraLookAt.x, cameraLookAt.y, cameraLookAt.z));
	}

	for (int s = 0; s < spheres.size(); s++) {
		spheres[s]->update();
		if (spheres[s]->colliding) {
			spheres.erase(spheres.begin() + s);
			for (int rs = 0; rs < 20; rs++) {
				float randomAlpha = (float)(rand() % 314 - 157) / 100.0f;
				float randomBeta = (float)(rand() % 212 - 106) / 100.0f;
				Vertex random = fromSpherical(randomAlpha, randomBeta, 5);
				random.x += spheres[s]->x;
				random.y += spheres[s]->y;
				random.z += spheres[s]->z;
				spheres.push_back(new Sphere(spheres[s]->x, spheres[s]->y, spheres[s]->z,
											random.x, random.y, random.z));
			}
		}
	}

	renderScene();
	for (int i = 0; i < 256; i++) {
		previousKeysState[i] = keysState[i];
	}
	mouseDeltaX = 0;
	mouseDeltaY = 0;
}

void keyboardPressHandler(unsigned char key, int x, int y) {
	keysState[key] = 1;
}

void keyboardReleaseHandler(unsigned char key, int x, int y) {
	keysState[key] = 0;
}

void specialKeyboardPressHandler(int key, int x, int y) {
	if (key < 112) {
		specialKeysState[key] = 1;
	}
}

void specialKeyboardReleaseHandler(int key, int x, int y) {
	if (key < 112) {
		specialKeysState[key] = 0;
	}
}

void passiveMouseHandler(int x, int y) {
	if (!pointerWarp) {
		mouseDeltaX = x - 540;
		mouseDeltaY = y - 500;
		pointerWarp = true;
		glutWarpPointer(540, 500);
	}
	else {
		pointerWarp = false;
	}
}


int main(int argc, char **argv) {
	srand(time(NULL));
	cameraMode = EXPLORER;
	alpha = 0;
	beta = 0;
	cameraPosition = Vertex(0,1,5);
	cameraLookAt = Vertex(0,1,0);
	pointerWarp = false;

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
	glutSetCursor(GLUT_CURSOR_NONE);
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(update);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(keyboardPressHandler);
	glutSpecialFunc(specialKeyboardPressHandler);
	glutKeyboardUpFunc(keyboardReleaseHandler);
	glutSpecialUpFunc(specialKeyboardReleaseHandler);
	glutPassiveMotionFunc(passiveMouseHandler);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
