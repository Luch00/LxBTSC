/********************************************************************************
** Form generated from reading UI file 'QtGuiClass.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUICLASS_H
#define UI_QTGUICLASS_H

#include <QtCore/QVariant>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <TsTextEdit.h>
#include <TsChatTabWidget.h>
#include <TsTabWidget.h>

QT_BEGIN_NAMESPACE

class Ui_QtGuiClass
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QWebEngineView *webEngineView;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QWebEngineView *webEngineView_2;
    //QPlainTextEdit *plainTextEdit;
	TsTextEdit *plainTextEdit;

    void setupUi(QWidget *QtGuiClass)
    {
        if (QtGuiClass->objectName().isEmpty())
            QtGuiClass->setObjectName(QStringLiteral("QtGuiClass"));
        QtGuiClass->resize(636, 534);
        verticalLayout = new QVBoxLayout(QtGuiClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(QtGuiClass);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::South);
        /*tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        webEngineView = new QWebEngineView(tab);
        webEngineView->setObjectName(QStringLiteral("webEngineView"));
        webEngineView->setUrl(QUrl(QStringLiteral("file:///C:/Users/TURSAS/AppData/Roaming/TS3Client/plugins/LxBTSC/template/chat.html")));

        verticalLayout_2->addWidget(webEngineView);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        webEngineView_2 = new QWebEngineView(tab_2);
        webEngineView_2->setObjectName(QStringLiteral("webEngineView_2"));
        webEngineView_2->setUrl(QUrl(QStringLiteral("about:blank")));

        verticalLayout_3->addWidget(webEngineView_2);

        tabWidget->addTab(tab_2, QString());*/

        verticalLayout->addWidget(tabWidget);

        plainTextEdit = new TsTextEdit(QtGuiClass);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(120);
        sizePolicy.setHeightForWidth(plainTextEdit->sizePolicy().hasHeightForWidth());
        plainTextEdit->setSizePolicy(sizePolicy);
        plainTextEdit->setMinimumSize(QSize(0, 24));
        plainTextEdit->setMaximumSize(QSize(16777215, 120));
        plainTextEdit->setSizeIncrement(QSize(0, 24));
        plainTextEdit->setBaseSize(QSize(0, 0));
        plainTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        plainTextEdit->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
		
        verticalLayout->addWidget(plainTextEdit);

        retranslateUi(QtGuiClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QtGuiClass);
    } // setupUi

    void retranslateUi(QWidget *QtGuiClass)
    {
        QtGuiClass->setWindowTitle(QApplication::translate("QtGuiClass", "QtGuiClass", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("QtGuiClass", "Server", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("QtGuiClass", "Channel", 0));
        plainTextEdit->setPlainText(QString());
    } // retranslateUi

};

namespace Ui {
    class QtGuiClass: public Ui_QtGuiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUICLASS_H
