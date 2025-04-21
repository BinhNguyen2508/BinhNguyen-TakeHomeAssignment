#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "groundwaterdialogmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}

class QPushButton;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openMseDialog();
    void openOtherWallsDialog();

private:
    QWidget* m_centralWidget;
    QPushButton* m_mseButton;
    QPushButton* m_otherWallsButton;

    GroundwaterDialogModel m_mseData;
    GroundwaterDialogModel m_otherWallsData;

    void setupUi();
};
#endif // MAINWINDOW_H
