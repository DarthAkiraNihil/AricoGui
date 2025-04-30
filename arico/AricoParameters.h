//
// Created by EgrZver on 20.04.2025.
//

#ifndef ARICOGUI_ARICOPARAMETERS_H
#define ARICOGUI_ARICOPARAMETERS_H

#include <QString>
#include "type/AricoMode.h"

namespace Arico {
    
    struct AricoParameters {
        QString inputFile;
        QString outputFile;
        int width;
        int scale;
        int chunkSize;
        Type::AricoMode mode;
    };
    
}


#endif //ARICOGUI_ARICOPARAMETERS_H
