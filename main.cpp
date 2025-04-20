#include <QApplication>
#include <ui/main_window.h>
#include <QFontDatabase>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    
    qDebug() << "Loaded font " << QFontDatabase::addApplicationFont(":/assets/JetBrainsMono-Regular.ttf");
    
    
    
    
    UI::MainWindow mainWindow(nullptr);
    
//    QFont serif("JetBrains Mono",16, QFont::Weight::Normal); // serif is a variable, change later
//    mainWindow.setFont(serif);
    
    mainWindow.show();
    
    return QApplication::exec();
}
