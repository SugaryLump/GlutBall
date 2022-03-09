#ifdef __APPLE__
#include <GLUT/glut.h>
#include <GLUT/glew.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include "sphere.hpp"
#include <time.h>
#include <iostream>
#include <string>



#define _USE_MATH_DEFINES
#define EXPLORER 0
#define FPS 1
#include <math.h>
#include <vector>
#define SLICES 10
#define STACKS 10

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
float frames;
int timebase;
float fps;
std::vector<float> vs;
std::vector<unsigned int> fs;
GLuint vertices, indices, verticeCount, indexCount;


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
	glBindBuffer(GL_ARRAY_BUFFER, vertices);
	glVertexPointer(3, GL_FLOAT, 0,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
	for (int s = 0; s < spheres.size(); s++) {
		glPushMatrix();
		glTranslatef(spheres[s]->x, spheres[s]->y, spheres[s]->z);
		glScalef(spheres[s]->scale, spheres[s]->scale, spheres[s]->scale);
		glColor3f(spheres[s]->r, spheres[s]->g, spheres[s]->b);
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);		
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

	//drawRoom();
	//drawSpheres();
	glBindBuffer(GL_ARRAY_BUFFER, vertices);
	glVertexPointer(3, GL_FLOAT, 0,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	// End of frame
	glutSwapBuffers();
}


void printSphereCount() {
	std::cout << spheres.size() << "\n";
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
		printSphereCount();
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
		printSphereCount();
	}

	if ((keysState['k'] && !previousKeysState['k'])) {
		spheres.push_back(new RocketSphere(cameraPosition.x, cameraPosition.y, cameraPosition.z,
										cameraLookAt.x, cameraLookAt.y, cameraLookAt.z));
		printSphereCount();
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
			printSphereCount();
		}
	}

	if (keysState['f'] && !previousKeysState['f']) {
		std::cout << fps << "\n";
	}

	//Finalizing

	renderScene();
	for (int i = 0; i < 256; i++) {
		previousKeysState[i] = keysState[i];
	}
	mouseDeltaX = 0;
	mouseDeltaY = 0;

	//Framerates
	frames++;
	int time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		fps = frames*1000.0/(time - timebase);
		timebase = time;
		frames = 0;
	}
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

void pushBackVertex(Vertex vertex) {
	vs.push_back(vertex.x);
	vs.push_back(vertex.y);
	vs.push_back(vertex.z);
}

void pushBackFace(Vertex vertex) {
	fs.push_back(vertex.x);
	fs.push_back(vertex.y);
	fs.push_back(vertex.z);
}

void prepareSphereVBO() {
	pushBackVertex(Vertex(0, -1, 0));
	pushBackVertex(Vertex(0, 1, 0));

	for (int st = 0; st < STACKS - 1; st++) {
		for (int sl = 0; sl < SLICES; sl++) {
			pushBackVertex(fromSpherical(sl * 2 * M_PI / SLICES, -M_PI_2 + (st + 1) * M_PI / STACKS, 1));
		}
	}

	//Bottom and top stacks;
	for (int sl = 0; sl < SLICES; sl++) {
		if (sl < SLICES - 1) {
			pushBackFace(Vertex(0, sl + 3, sl + 2));
			pushBackFace(Vertex(1, (STACKS - 2) * SLICES + 2 + sl, (STACKS - 2) * SLICES + 3 + sl));
		}
		else {
			pushBackFace(Vertex(0, 2, sl + 2));
			pushBackFace(Vertex(1, (STACKS - 2) * SLICES + 2 + sl, (STACKS - 2) * SLICES + 2));
		}
	}

	//Middle stacks;
	for (int st = 0; st < STACKS - 2; st++) {
		for (int sl = 0; sl < SLICES; sl++) {
			int v1,v2,v3,v4;
			if (sl < SLICES - 1) {
				v1 = st * SLICES + 2 + sl;
				v2 = v1 + 1;
				v3 = v1 + SLICES;
				v4 = v3 + 1;
			}
			else {
				v1 = st * SLICES + 2 + sl;
				v2 = st * SLICES + 2;
				v3 = v1 + SLICES;
				v4 = v2 + SLICES;
			}
			pushBackFace(Vertex(v1, v2, v4));
			pushBackFace(Vertex(v1, v4, v3));
		}
	}
	verticeCount = vs.size()/3;
	indexCount = fs.size();
	glGenBuffers(1, &vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vs.size(), vs.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * fs.size(), fs.data(), GL_STATIC_DRAW);

}

int main(int argc, char **argv) {
	srand(time(NULL));
	cameraMode = EXPLORER;
	alpha = 0;
	beta = 0;
	cameraPosition = Vertex(0,1,5);
	cameraLookAt = Vertex(0,1,0);
	pointerWarp = false;
	vertices = 0;
	indices = 0;

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
	glutSetCursor(GLUT_CURSOR_NONE);
	timebase = glutGet(GLUT_ELAPSED_TIME);

		
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

// Glew init
	if (glewInit() != GLEW_OK) {
		return 0;
	}
	prepareSphereVBO();

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
