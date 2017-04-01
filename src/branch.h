#include "ofMain.h"

class Branch{

public:
    Branch(ofVec3f _direction);
    void draw();
    void move(ofVec3f _pos);
    void setParent(shared_ptr<Branch> branch);
    ofVec3f getPosition();
    void reset();

    ofVec3f direction;
    ofVec3f originalDirection;
    int count = 0;
private:
    ofNode node;
};
