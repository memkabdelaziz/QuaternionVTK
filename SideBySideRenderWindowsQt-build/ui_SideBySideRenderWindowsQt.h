/********************************************************************************
** Form generated from reading UI file 'SideBySideRenderWindowsQt.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIDEBYSIDERENDERWINDOWSQT_H
#define UI_SIDEBYSIDERENDERWINDOWSQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_SideBySideRenderWindowsQt
{
public:
    QAction *actionOpenFile;
    QAction *actionExit;
    QAction *actionPrint;
    QAction *actionHelp;
    QAction *actionSave;
    QWidget *centralwidget;
    QVTKWidget *qvtkWidgetLeft;
    QVTKWidget *qvtkWidgetRight;
    QLabel *label;

    void setupUi(QMainWindow *SideBySideRenderWindowsQt)
    {
        if (SideBySideRenderWindowsQt->objectName().isEmpty())
            SideBySideRenderWindowsQt->setObjectName(QStringLiteral("SideBySideRenderWindowsQt"));
        SideBySideRenderWindowsQt->resize(990, 583);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Icons/help.png"), QSize(), QIcon::Normal, QIcon::Off);
        SideBySideRenderWindowsQt->setWindowIcon(icon);
        SideBySideRenderWindowsQt->setIconSize(QSize(22, 22));
        actionOpenFile = new QAction(SideBySideRenderWindowsQt);
        actionOpenFile->setObjectName(QStringLiteral("actionOpenFile"));
        actionOpenFile->setEnabled(true);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Icons/fileopen.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenFile->setIcon(icon1);
        actionExit = new QAction(SideBySideRenderWindowsQt);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon2;
        icon2.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon2);
        actionPrint = new QAction(SideBySideRenderWindowsQt);
        actionPrint->setObjectName(QStringLiteral("actionPrint"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Icons/print.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPrint->setIcon(icon3);
        actionHelp = new QAction(SideBySideRenderWindowsQt);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        actionHelp->setIcon(icon);
        actionSave = new QAction(SideBySideRenderWindowsQt);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Icons/filesave.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon4);
        centralwidget = new QWidget(SideBySideRenderWindowsQt);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        qvtkWidgetLeft = new QVTKWidget(centralwidget);
        qvtkWidgetLeft->setObjectName(QStringLiteral("qvtkWidgetLeft"));
        qvtkWidgetLeft->setGeometry(QRect(10, 20, 511, 541));
        qvtkWidgetRight = new QVTKWidget(centralwidget);
        qvtkWidgetRight->setObjectName(QStringLiteral("qvtkWidgetRight"));
        qvtkWidgetRight->setGeometry(QRect(540, 20, 441, 541));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(690, 260, 181, 51));
        SideBySideRenderWindowsQt->setCentralWidget(centralwidget);

        retranslateUi(SideBySideRenderWindowsQt);

        QMetaObject::connectSlotsByName(SideBySideRenderWindowsQt);
    } // setupUi

    void retranslateUi(QMainWindow *SideBySideRenderWindowsQt)
    {
        SideBySideRenderWindowsQt->setWindowTitle(QApplication::translate("SideBySideRenderWindowsQt", "SimpleView", 0));
        actionOpenFile->setText(QApplication::translate("SideBySideRenderWindowsQt", "Open File...", 0));
        actionExit->setText(QApplication::translate("SideBySideRenderWindowsQt", "Exit", 0));
        actionPrint->setText(QApplication::translate("SideBySideRenderWindowsQt", "Print", 0));
        actionHelp->setText(QApplication::translate("SideBySideRenderWindowsQt", "Help", 0));
        actionSave->setText(QApplication::translate("SideBySideRenderWindowsQt", "Save", 0));
        label->setText(QApplication::translate("SideBySideRenderWindowsQt", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class SideBySideRenderWindowsQt: public Ui_SideBySideRenderWindowsQt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIDEBYSIDERENDERWINDOWSQT_H
