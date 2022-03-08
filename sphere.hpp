class Sphere {
    public:
        float x;
        float y;
        float z;
        float radius;
        float r;
        float g;
        float b;
        float xvel;
        float yvel;
        float zvel;
        Sphere() = default;
        Sphere(float x, float y, float z, float cameraX, float cameraY, float cameraZ);
        void update();
};