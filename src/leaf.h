//
//  leaf.hpp
//  testSpaceColonization
//
//  Created by DavidePrati on 06/09/16.
//
//
#include "ofMain.h"

class Leaf {

public:
    Leaf();
    void draw();
    ofVec3f getPosition();
    bool reached = false;

private:
    ofVec3f pos;
};
