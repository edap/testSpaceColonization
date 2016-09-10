#include "ofMain.h"

class Branch{

public:
    Branch(ofVec3f _position, ofVec3f _direction);
    void draw();
    void setPosition(ofVec3f _pos);
    ofVec3f getPosition();

    ofVec3f direction;
    ofNode node;
};
