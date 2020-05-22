#ifndef TRACKER_H
#define TRACKER_H
#include <vector>

#include "./dataType.h"

class tracker
{
public:
    DYNAMICM iou_cost();
    Eigen::VectorXf iou();
};

#endif // TRACKER_H
