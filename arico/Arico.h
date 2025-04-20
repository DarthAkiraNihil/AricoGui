//
// Created by EgrZver on 20.04.2025.
//

#ifndef ARICOGUI_ARICO_H
#define ARICOGUI_ARICO_H

#include <QProcess>
#include "AricoParameters.h"

namespace Arico {
    
    class Arico {
    
        private:
            QProcess* _process;
            
        public:
            explicit Arico();
            ~Arico();
            
            void run(AricoParameters parameters);
    
    };
    
} // Arico

#endif //ARICOGUI_ARICO_H
