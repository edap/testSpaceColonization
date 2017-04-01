#include "branch.h"

Branch::Branch(const ofVec3f _direction){
    direction = _direction;
    originalDirection = _direction;
}

void Branch::move(ofVec3f pos){
    this->node.move(pos);
}

void Branch::setParent(shared_ptr<Branch> branch){
    this->node.setParent(branch->node);
}

ofVec3f Branch::getPosition(){
    return this->node.getGlobalPosition();
}

void Branch::reset(){
    this->direction = this->originalDirection;
    this->count = 0;
}

void Branch::draw(){
    if(this->node.getParent() != nullptr){
        auto pos = this->node.getGlobalPosition();
        auto parentPos = this->node.getParent()->getGlobalPosition();
        ofDrawLine(pos.x, pos.y, parentPos.x, parentPos.y);
    }
}
