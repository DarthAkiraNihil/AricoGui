//
// Created by EgrZver on 26.04.2025.
//

#ifndef ARICOGUI_ABOUT_DIALOG_H
#define ARICOGUI_ABOUT_DIALOG_H

#include <QDialog>

namespace UI {
    QT_BEGIN_NAMESPACE
    namespace Ui { class AboutDialog; }
    QT_END_NAMESPACE
    
    class AboutDialog : public QDialog {
        Q_OBJECT
        
        public:
            explicit AboutDialog(QWidget *parent = nullptr);
            
            ~AboutDialog() override;
        
        private:
            Ui::AboutDialog *ui;
    };
} // UI

#endif //ARICOGUI_ABOUT_DIALOG_H
