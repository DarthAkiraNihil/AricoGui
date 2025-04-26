//
// Created by EgrZver on 26.04.2025.
//

#ifndef ARICOGUI_ARICORESULT_H
#define ARICOGUI_ARICORESULT_H

#include <arico/AricoExecutionStatus.h>

namespace Arico {
    struct AricoResult {
        long long elapsedTime = 0.0;
        double compressionCoefficient = 0.0;
        AricoExecutionStatus status = AricoExecutionStatus::NotLaunched;
    };
}

#endif //ARICOGUI_ARICORESULT_H
