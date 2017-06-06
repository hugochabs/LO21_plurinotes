/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QPushButton *addNote;
    QPushButton *archiver;
    QPushButton *delete_2;
    QSpacerItem *verticalSpacer;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_2;
    QTreeWidget *ListNotes;
    QLabel *label_3;
    QTableWidget *listTask;
    QLabel *label_6;
    QTreeWidget *listArchived;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QPushButton *addRelation_2;
    QSpacerItem *verticalSpacer_2;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QHBoxLayout *horizontalLayout;
    QLabel *idl;
    QLineEdit *id;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_8;
    QLineEdit *titre;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_10;
    QLineEdit *dc;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_9;
    QLineEdit *dm;
    QHBoxLayout *horizontalLayout_5;
    QLabel *prop1L;
    QTextEdit *text;
    QLineEdit *prop1;
    QHBoxLayout *horizontalLayout_6;
    QLabel *prop2L;
    QPushButton *directoryFile;
    QLineEdit *prop2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *prop3L;
    QLineEdit *prop3;
    QDateTimeEdit *dateTimeEdit;
    QHBoxLayout *horizontalLayout_8;
    QLabel *prop4L;
    QComboBox *typeON;
    QLineEdit *prop4;
    QPushButton *saveMW;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1012, 657);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(330, 0, 112, 521));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        addNote = new QPushButton(layoutWidget);
        addNote->setObjectName(QStringLiteral("addNote"));
        QFont font;
        font.setFamily(QStringLiteral("Corbel"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        addNote->setFont(font);

        verticalLayout_3->addWidget(addNote);

        archiver = new QPushButton(layoutWidget);
        archiver->setObjectName(QStringLiteral("archiver"));

        verticalLayout_3->addWidget(archiver);

        delete_2 = new QPushButton(layoutWidget);
        delete_2->setObjectName(QStringLiteral("delete_2"));

        verticalLayout_3->addWidget(delete_2);

        verticalSpacer = new QSpacerItem(20, 318, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 0, 301, 651));
        verticalLayout_4 = new QVBoxLayout(layoutWidget1);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(layoutWidget1);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setFamily(QStringLiteral("Corbel"));
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);
        label->setFrameShape(QFrame::Box);
        label->setTextFormat(Qt::PlainText);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font2;
        font2.setFamily(QStringLiteral("Corbel"));
        font2.setPointSize(10);
        font2.setItalic(true);
        label_2->setFont(font2);

        verticalLayout_6->addWidget(label_2);

        ListNotes = new QTreeWidget(layoutWidget1);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(1, QStringLiteral("2"));
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        ListNotes->setHeaderItem(__qtreewidgetitem);
        ListNotes->setObjectName(QStringLiteral("ListNotes"));
        ListNotes->setColumnCount(2);

        verticalLayout_6->addWidget(ListNotes);


        verticalLayout->addLayout(verticalLayout_6);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font2);

        verticalLayout->addWidget(label_3);

        listTask = new QTableWidget(layoutWidget1);
        listTask->setObjectName(QStringLiteral("listTask"));

        verticalLayout->addWidget(listTask);

        label_6 = new QLabel(layoutWidget1);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font2);

        verticalLayout->addWidget(label_6);

        listArchived = new QTreeWidget(layoutWidget1);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QStringLiteral("1"));
        listArchived->setHeaderItem(__qtreewidgetitem1);
        listArchived->setObjectName(QStringLiteral("listArchived"));

        verticalLayout->addWidget(listArchived);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);
        label_4->setFrameShape(QFrame::Box);
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_4);

        addRelation_2 = new QPushButton(layoutWidget1);
        addRelation_2->setObjectName(QStringLiteral("addRelation_2"));
        QFont font3;
        font3.setFamily(QStringLiteral("Corbel"));
        font3.setPointSize(10);
        font3.setBold(true);
        font3.setWeight(75);
        addRelation_2->setFont(font3);

        verticalLayout_2->addWidget(addRelation_2);


        verticalLayout->addLayout(verticalLayout_2);


        verticalLayout_4->addLayout(verticalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        layoutWidget2 = new QWidget(centralWidget);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(520, 40, 321, 445));
        verticalLayout_5 = new QVBoxLayout(layoutWidget2);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        pushButton = new QPushButton(layoutWidget2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_9->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_9->addWidget(pushButton_2);


        verticalLayout_5->addLayout(horizontalLayout_9);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        idl = new QLabel(layoutWidget2);
        idl->setObjectName(QStringLiteral("idl"));
        QFont font4;
        font4.setFamily(QStringLiteral("Corbel"));
        font4.setPointSize(10);
        idl->setFont(font4);

        horizontalLayout->addWidget(idl);

        id = new QLineEdit(layoutWidget2);
        id->setObjectName(QStringLiteral("id"));

        horizontalLayout->addWidget(id);


        verticalLayout_5->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_8 = new QLabel(layoutWidget2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFont(font4);

        horizontalLayout_2->addWidget(label_8);

        titre = new QLineEdit(layoutWidget2);
        titre->setObjectName(QStringLiteral("titre"));

        horizontalLayout_2->addWidget(titre);


        verticalLayout_5->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_10 = new QLabel(layoutWidget2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setFont(font4);

        horizontalLayout_4->addWidget(label_10);

        dc = new QLineEdit(layoutWidget2);
        dc->setObjectName(QStringLiteral("dc"));

        horizontalLayout_4->addWidget(dc);


        verticalLayout_5->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_9 = new QLabel(layoutWidget2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setFont(font4);

        horizontalLayout_3->addWidget(label_9);

        dm = new QLineEdit(layoutWidget2);
        dm->setObjectName(QStringLiteral("dm"));

        horizontalLayout_3->addWidget(dm);


        verticalLayout_5->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        prop1L = new QLabel(layoutWidget2);
        prop1L->setObjectName(QStringLiteral("prop1L"));

        horizontalLayout_5->addWidget(prop1L);

        text = new QTextEdit(layoutWidget2);
        text->setObjectName(QStringLiteral("text"));

        horizontalLayout_5->addWidget(text);

        prop1 = new QLineEdit(layoutWidget2);
        prop1->setObjectName(QStringLiteral("prop1"));

        horizontalLayout_5->addWidget(prop1);


        verticalLayout_5->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        prop2L = new QLabel(layoutWidget2);
        prop2L->setObjectName(QStringLiteral("prop2L"));

        horizontalLayout_6->addWidget(prop2L);

        directoryFile = new QPushButton(layoutWidget2);
        directoryFile->setObjectName(QStringLiteral("directoryFile"));

        horizontalLayout_6->addWidget(directoryFile);

        prop2 = new QLineEdit(layoutWidget2);
        prop2->setObjectName(QStringLiteral("prop2"));

        horizontalLayout_6->addWidget(prop2);


        verticalLayout_5->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        prop3L = new QLabel(layoutWidget2);
        prop3L->setObjectName(QStringLiteral("prop3L"));

        horizontalLayout_7->addWidget(prop3L);

        prop3 = new QLineEdit(layoutWidget2);
        prop3->setObjectName(QStringLiteral("prop3"));

        horizontalLayout_7->addWidget(prop3);

        dateTimeEdit = new QDateTimeEdit(layoutWidget2);
        dateTimeEdit->setObjectName(QStringLiteral("dateTimeEdit"));

        horizontalLayout_7->addWidget(dateTimeEdit);


        verticalLayout_5->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        prop4L = new QLabel(layoutWidget2);
        prop4L->setObjectName(QStringLiteral("prop4L"));

        horizontalLayout_8->addWidget(prop4L);

        typeON = new QComboBox(layoutWidget2);
        typeON->setObjectName(QStringLiteral("typeON"));

        horizontalLayout_8->addWidget(typeON);

        prop4 = new QLineEdit(layoutWidget2);
        prop4->setObjectName(QStringLiteral("prop4"));

        horizontalLayout_8->addWidget(prop4);


        verticalLayout_5->addLayout(horizontalLayout_8);

        saveMW = new QPushButton(layoutWidget2);
        saveMW->setObjectName(QStringLiteral("saveMW"));
        saveMW->setFont(font3);

        verticalLayout_5->addWidget(saveMW);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        addNote->setText(QApplication::translate("MainWindow", "Ajouter\n"
" une note", Q_NULLPTR));
        archiver->setText(QApplication::translate("MainWindow", "Archiver", Q_NULLPTR));
        delete_2->setText(QApplication::translate("MainWindow", "Supprimer", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Note", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Notes actives", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "T\303\242ches", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "Notes archiv\303\251es", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Relation", Q_NULLPTR));
        addRelation_2->setText(QApplication::translate("MainWindow", "Acc\303\251der aux relations", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Annuler", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "R\303\251tablir", Q_NULLPTR));
        idl->setText(QApplication::translate("MainWindow", "Identificateur", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Titre", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "Date de cr\303\251ation", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "Date de modification", Q_NULLPTR));
        prop1L->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        prop2L->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        directoryFile->setText(QApplication::translate("MainWindow", "Choisir un fichier", Q_NULLPTR));
        prop3L->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        prop4L->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        saveMW->setText(QApplication::translate("MainWindow", "Enregistrer", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
