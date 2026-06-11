#pragma once
#include "../model/printjob.h"

class PrinterRepository {
public:
    void saveJob(const PrintJob& job);
};