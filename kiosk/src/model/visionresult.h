
#pragma once
#include <QString>

struct VisionResult {
    int correct = 0;
    int total = 0;
    QString acuity; // "6/6", "6/9"
};