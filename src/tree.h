//
//
//  Created by DavidePrati on 06/09/16.
//
//

#pragma once

#include "ofMain.h"
#include "leaf.h"
#include "branch.h"

class Tree {

public:
    Tree();
    void grow();
    void draw();
    
private:
    vector<Leaf> leaves;
    std::vector<shared_ptr<Branch> > branches;
    int n_leaves = 100;
    int max_dist = 150;
    int min_dist = 13;
    int branch_length = 5;
};
