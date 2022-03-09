class Sphere {
    public:
        float x;
        float y;
        float z;
        float scale;
        float r;
        float g;
        float b;
        float xvel;
        float yvel;
        float zvel;
        bool colliding;
        Sphere() = default;
        Sphere(float x, float y, float z, float cameraX, float cameraY, float cameraZ);
        virtual void update();
};

class RocketSphere : public Sphere {
    public:
        RocketSphere(float x, float y, float z, float cameraX, float cameraY, float cameraZ);
        void update() override;
};