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
            int chunkSize;
            
            Type::AricoMode mode;
            Type::AricoMode frozenMode;
            
            bool aricoRunning;
            
            bool validate();
        
        public:
            explicit MainWindowModel(Arico::Arico* arico, QWidget* parent);
            
        private slots:
            void onAricoFinished(Arico::AricoResult result, QString message);
            
        signals:
            void selectedInputFileChanged(QString filename);
            void selectedOutputFileChanged(QString filename);
            void nonRequiredParametersEnabledChanged(bool state);
            void validationStatusChanged(bool validationStatus);
            
            void aricoStarted();
            void aricoFinished();
            
        public slots:
            void selectPackMode(bool checked = false);
            void selectUnpackMode(bool checked = false);
            
            void selectInputFile(bool checked = false);
            void selectOutputFile(bool checked = false);
            
            void changeWidth(const QString &text);
            void changeScale(const QString &text);
            void changeChunkSize(const QString &text);
            
            void executeArico(bool checked = false);
    };
    
} // ViewModel

#endif //ARICOGUI_MAINWINDOWMODEL_H
