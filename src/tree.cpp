#include "tree.h"


Tree::Tree() {
    auto rootPos = ofVec3f(ofGetWidth()/2, ofGetHeight(), 0);
    auto rootDir = ofVec3f(0, -10, 0);
    shared_ptr<Branch> root(new Branch(rootPos, rootDir));
    branches.push_back(root);

    for (int i =0; i<n_leaves; i++) {
        leaves.push_back(Leaf());
    }

    bool found = false;
    while(!found){
        auto current = *branches.back();
        ofVec3f currentPosition = current.node.getPosition();
        for(auto l:leaves){
            l.draw();
            float distance = currentPosition.distance(l.getPosition());
            cout << distance << endl;
            if(distance < max_dist){
                found = true;
            }
        }

        if (!found){
            auto newPos = current.node.getGlobalPosition() + current.direction;
            shared_ptr<Branch> nextBranch(new Branch(newPos, current.direction));
            auto parent = *branches.back();
            nextBranch->node.setParent(parent.node);
            branches.push_back(nextBranch);
        }
    }
}

void Tree::draw(){
    for(auto l:leaves){
        l.draw();
    }
//    for(auto b:branches){
//        //b->draw();
//    }
}
