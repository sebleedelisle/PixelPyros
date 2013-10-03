
struct Triangle
{
    ofVec3f v0, v1, v2;
    ofVec3f normal;

    Triangle(ofVec3f v0, ofVec3f v1, ofVec3f v2)
    {
        this->v0 = v0;
        this->v1 = v1;
        this->v2 = v2;
    }

    void setnormal(ofVec3f normal)
    {
		this->normal = normal;
    }

    void setnormal(float x, float y, float z)
    {
		setnormal(ofVec3f(x, y, z));
    }

    Triangle(void) {}

};