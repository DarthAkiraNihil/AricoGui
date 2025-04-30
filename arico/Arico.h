//
// Created by EgrZver on 20.04.2025.
//

#ifndef ARICOGUI_ARICO_H
#define ARICOGUI_ARICO_H

#include <QObject>
#include <QProcess>
#include <QElapsedTimer>
#include "AricoParameters.h"
#include "AricoResult.h"

namespace Arico {
    
    class Arico: public QObject {
        
        Q_OBJECT
    
        private:
            QProcess* _process;
            QElapsedTimer elapsed;
            AricoParameters lastUsedParameters;
            
        public:
            explicit Arico();
            ~Arico();
            
            void execute(const AricoParameters& parameters);
            
        private slots:
            void onAricoFinished(int code, QProcess::ExitStatus status = QProcess::NormalExit);
        
        signals:
            void aricoFinished(AricoResult result);
    
    };
    
} // Arico

#endif //ARICOGUI_ARICO_H
