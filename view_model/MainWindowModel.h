//
// Created by EgrZver on 20.04.2025.
//

#ifndef ARICOGUI_MAINWINDOWMODEL_H
#define ARICOGUI_MAINWINDOWMODEL_H

#include <QObject>
#include "type/AricoMode.h"

namespace ViewModel {
    
    class MainWindowModel: public QObject {
        Q_OBJECT
        
        private:
            QString inputFileName;
            QString outputFileName;
            int width;
            int scale;
            
            Type::AricoMode mode;
        
        public:
            explicit MainWindowModel();
            
        signals:
            void selectedInputFileChanged(QString filename);
            
        public slots:
            void selectPackMode(bool checked = false);
            void selectUnpackMode(bool checked = false);
            
            void selectInputFileButtonPressed(bool checked = false);
            
    };
    
} // ViewModel

#endif //ARICOGUI_MAINWINDOWMODEL_H
