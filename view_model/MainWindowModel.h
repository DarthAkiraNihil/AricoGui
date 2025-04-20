//
// Created by EgrZver on 20.04.2025.
//

#ifndef ARICOGUI_MAINWINDOWMODEL_H
#define ARICOGUI_MAINWINDOWMODEL_H

#include <QObject>
#include "type/AricoMode.h"
#include "arico/Arico.h"

namespace ViewModel {
    
    class MainWindowModel: public QObject {
        Q_OBJECT
        
        private:
            
            QWidget* parent;
        
            Arico::Arico* aricoInstance;
            
            QString inputFileName;
            QString outputFileName;
            int width;
            int scale;
            
            Type::AricoMode mode;
        
        public:
            explicit MainWindowModel(Arico::Arico* arico, QWidget* parent);
            
        signals:
            void selectedInputFileChanged(QString filename);
            void nonRequiredParametersEnabledChanged(bool state);
            
        public slots:
            void selectPackMode(bool checked = false);
            void selectUnpackMode(bool checked = false);
            
            void selectInputFile(bool checked = false);
            
            void executeArico(bool checked = false);
    };
    
} // ViewModel

#endif //ARICOGUI_MAINWINDOWMODEL_H
