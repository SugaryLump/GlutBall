#include "sphere.hpp"
#include <math.h>
#define GRAVITY 0.01f

int signum(float x) {
	return (x > 0) - (x < 0);
}

Sphere::Sphere(float x_, float y_, float z_, float cameraX, float cameraY, float cameraZ) {
    x = x_;
	y = y_;
	z = z_;
    radius = (float)(rand() % 10 + 2);
    radius = radius / 30.0f;
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

    if (y - radius < 0) {
        y += radius - y;
        yvel = -yvel;
    }
	if (abs(x) + radius/2.0f > 25) {
        while(abs(x) + radius/2.0f > 25) {
            x -= signum(x);
        }
		xvel = -xvel;
	}
	if (abs(z) + radius/2.0f > 25) {
        while(abs(z) + radius/2.0f > 25) {
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
    radius = (float)(rand() % 10 + 2);
    radius = radius / 10.0f;
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

    if (y - radius < 0 || abs(x) + radius/2.0f > 25 ||
         abs(z) + radius/2.0f > 25) {
        x -= xvel;
        y -= yvel;
        z -= zvel;
		colliding = true;
	}
}