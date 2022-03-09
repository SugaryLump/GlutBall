#include "sphere.hpp"
#include <math.h>
#define GRAVITY 0.01f
#define RADIUS 1

int signum(float x) {
	return (x > 0) - (x < 0);
}

Sphere::Sphere(float x_, float y_, float z_, float cameraX, float cameraY, float cameraZ) {
    x = x_;
	y = y_;
	z = z_;
    scale = (float)(rand() % 11 + 5);
    scale = scale / 10.0f;
    r = (float)(rand() % 7 + 1) / 10.0f;
    g = (float)(rand() % 7 + 1) / 10.0f;
    b = (float)(rand() % 7 + 1) / 10.0f;
    xvel = (cameraX - x)/10.0f;
    yvel = (cameraY - y)/10.0f;
    zvel = (cameraZ - z)/10.0f;
    colliding = false;
}

void Sphere::update() {
    yvel -= GRAVITY;

    x += xvel;
    y += yvel;
    z += zvel;

    if (y - scale * RADIUS < 0) {
        y += scale * RADIUS - y;
        yvel = -yvel;
    }
	if (abs(x) + scale * RADIUS > 25) {
        while(abs(x) + scale*RADIUS > 25) {
            x -= signum(x);
        }
		xvel = -xvel;
	}
	if (abs(z) + scale * RADIUS > 25) {
        while(abs(z) + scale * RADIUS > 25) {
            z -= signum(z);
        }
		zvel = -zvel;
	}


	xvel = xvel / 1.001;
	zvel = zvel / 1.001;

	if (abs(xvel) < 0.01)
		xvel = 0;
	if (abs(zvel) < 0.01)
		zvel = 0;
}

RocketSphere::RocketSphere(float x_, float y_, float z_, float cameraX, float cameraY, float cameraZ) {
    x = x_;
	y = y_;
	z = z_;
    scale = (float)(rand() % 11 + 5);
    scale = scale / 5.0f;
    r = (float)(rand() % 7 + 1) / 10.0f;
    g = (float)(rand() % 7 + 1) / 10.0f;
    b = (float)(rand() % 7 + 1) / 10.0f;
    xvel = (cameraX - x)/10.0f;
    yvel = (cameraY - y)/10.0f;
    zvel = (cameraZ - z)/10.0f;
    colliding = false;
}

void RocketSphere::update() {
    x += xvel;
    y += yvel;
    z += zvel;

    if (y - scale * RADIUS < 0 || abs(x) + scale * RADIUS > 25 ||
         abs(z) + scale * RADIUS > 25) {
        x -= xvel;
        y -= yvel;
        z -= zvel;
		colliding = true;
	}
}