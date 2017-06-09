#include "alertviewer.h"

AlertViewer::AlertViewer(const QString &title, const QString &message) : QMessageBox()
{
    setText(message);
    setWindowTitle(title);
}

