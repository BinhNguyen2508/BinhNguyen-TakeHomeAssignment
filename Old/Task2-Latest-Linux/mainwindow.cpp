#include <QtWidgets>
#include "mainwindow.h"
#include "groundwaterdialog.h"

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
{
    setupUi();
}

MainWindow::~MainWindow()
{
}

void MainWindow::openMseDialog()
{
    GroundwaterDialog dialog(true, m_mseData, this);

    if (dialog.exec() == QDialog::Accepted) {
        m_mseData = dialog.getDialogData();
    }
}

void MainWindow::openOtherWallsDialog()
{
    GroundwaterDialog dialog(false, m_otherWallsData, this);

    if (dialog.exec() == QDialog::Accepted) {
        m_otherWallsData = dialog.getDialogData();
    }
}

void MainWindow::setupUi()
{
    setWindowTitle("Task 2");

    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);

    m_mseButton = new QPushButton(tr("MSE"));
    m_otherWallsButton = new QPushButton(tr("Other Walls"));

    connect(m_mseButton, &QPushButton::clicked, this, &MainWindow::openMseDialog);
    connect(m_otherWallsButton, &QPushButton::clicked, this, &MainWindow::openOtherWallsDialog);

    QHBoxLayout *mainLayout = new QHBoxLayout(m_centralWidget);
    mainLayout->addWidget(m_mseButton);
    mainLayout->addWidget(m_otherWallsButton);

    mainLayout->setContentsMargins(10, 10, 10, 10);

    setTabOrder(m_mseButton, m_otherWallsButton);

    resize(400, 100);
}
