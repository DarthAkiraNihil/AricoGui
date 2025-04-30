//
// Created by EgrZver on 26.04.2025.
//

#ifndef ARICOGUI_ARICOEXECUTIONSTATUS_H
#define ARICOGUI_ARICOEXECUTIONSTATUS_H

namespace Arico {
    enum class AricoExecutionStatus {
        Success = 0,
        ErrorWidthTooSmall = 1,
        ErrorChunkSizeTooSmall = 2,
        ErrorInvalidSignature = 10,
        ErrorLengthCheckpointNotFound = 11,
        ErrorCountsCheckpointNotFound = 12,
        
        UnknownError = 0xFF,
        NotLaunched = 0x100,
    };
}

#endif //ARICOGUI_ARICOEXECUTIONSTATUS_H
