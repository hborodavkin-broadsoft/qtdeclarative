/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include <QDir>
#include <QGuiApplication>
#include <QQmlEngine>
#include <QQuickView>
#define DECLARATIVE_EXAMPLE_MAIN(NAME) int main(int argc, char* argv[]) \
{\
    QGuiApplication app(argc,argv);\
    QQuickView view;\
    QDir directory(QCoreApplication::applicationDirPath());\
    if (QGuiApplication::platformName() == QLatin1String("windows")) {\
        if (directory.absolutePath().endsWith("/debug", Qt::CaseInsensitive)\
            || directory.absolutePath().endsWith("/release", Qt::CaseInsensitive))\
            if (!directory.cdUp()) {\
                qWarning("Could not change to parent directory of '%s'",\
                    qPrintable(QDir::toNativeSeparators(directory.absolutePath())));\
                return -1;\
            }\
    } else if (QGuiApplication::platformName() == QLatin1String("Cocoa")) {\
        if (directory.absolutePath().endsWith(#NAME".app/Contents/MacOS"))\
            for (int i = 0; i < 3; ++i) {\
                if (!directory.cdUp()) {\
                    qWarning("Could not change to parent directory of '%s'",\
                        qPrintable(QDir::toNativeSeparators(directory.absolutePath())));\
                    return -1;\
                }\
            }\
    }\
    const QString fileName(directory.absolutePath() + "/" #NAME ".qml");\
    if (!QFile::exists(fileName)) {\
            qWarning("Could not find file '%s'", qPrintable(QDir::toNativeSeparators(fileName)));\
            return -1;\
    }\
    view.connect(view.engine(), SIGNAL(quit()), &app, SLOT(quit()));\
    view.setSource(QUrl::fromLocalFile(fileName));\
    view.show();\
    return app.exec();\
}
