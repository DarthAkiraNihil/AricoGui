//
// Created by EgrZver on 20.04.2025.
//

#ifndef ARICOGUI_MAIN_WINDOW_H
#define ARICOGUI_MAIN_WINDOW_H

#include <QMainWindow>
#include "view_model/MainWindowModel.h"

namespace UI {
    QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
    QT_END_NAMESPACE
    
    class MainWindow : public QMainWindow {
        Q_OBJECT
        
        protected:
            void resizeEvent(QResizeEvent *event) override;
        
        public:
            explicit MainWindow(QWidget *parent = nullptr);
            ~MainWindow() override;
            
        private slots:
            void changeSelectedInputFile(const QString& filename);
            void changeSelectedOutputFile(const QString& filename);
            void changeNonRequiredParametersEnableState(bool state);
            void setExecutionPossibility(bool validationStatus);
            void showAboutInfo(bool checked = false);
            
            void onAricoStarted();
            void onAricoFinished();
        
        private:
            Ui::MainWindow *ui;
            ViewModel::MainWindowModel* viewModel;
            
            void connectSignals();
    };
} // UI

#endif //ARICOGUI_MAIN_WINDOW_H
