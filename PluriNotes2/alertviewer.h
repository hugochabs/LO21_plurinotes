#ifndef ALERTVIEWER_H
#define ALERTVIEWER_H

#include <QMessageBox>


class AlertViewer : public QMessageBox
{
public:
    AlertViewer(const QString& title, const QString &message);
};

#endif // ALERTVIEWER_H
