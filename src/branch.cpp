#include "branch.h"

Branch::Branch(const ofVec3f _position, const ofVec3f _direction){
    this->setPosition(_position);
    direction = _direction;
}

void Branch::setPosition(ofVec3f pos){
    this->node.move(pos);
}

ofVec3f Branch::getPosition(){
    this->node.getGlobalPosition();
}

void Branch::draw(){
    cout << "called" << endl;
    if(this->node.getParent() != nullptr){
        auto pos = this->node.getGlobalPosition();
        auto parentPos = this->node.getParent()->getGlobalPosition();
        ofDrawLine(pos.x, pos.y, parentPos.x, parentPos.y);
    }

}
