/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of QtSystemTest.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/


#include "qtuitestmaster_p.h"

#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QIODevice>

QtUiTestMaster::QtUiTestMaster()
    : QstProtocol()
{
   setAutoUnpack(false);
}

QtUiTestMaster::~QtUiTestMaster()
{
}

void QtUiTestMaster::processMessage( QstMessage *msg )
{
    msg->unpack();
    if (msg->event() == QLatin1String("APP_NAME")) {
        m_appName = (*msg)["appName"].toString();
        m_appVersion = (*msg)["appVersion"].toString();
        m_qtVersion = (*msg)["qtVersion"].toString();
    } else if (msg->event() == QLatin1String("SIGNAL_RECEIVED")) {
        emit signalReceived( (*msg)["sender"].toMap(), (*msg)["signal"].toString(), (*msg)["args"].toList() );
    }
}

bool QtUiTestMaster::forwardMessage( const QstMessage &msg )
{
    QstMessage reply;
    // FIXME: This timeout should really be configurable
    return sendMessage(msg, reply, 20000);
}

QString QtUiTestMaster::appName() const
{
    return m_appName;
}

QString QtUiTestMaster::appVersion() const
{
    return m_appVersion;
}

QString QtUiTestMaster::qtVersion() const
{
    return m_qtVersion;
}

void QtUiTestMaster::onReplyReceived( QstMessage *reply )
{
    // TODO - should emit signal
//     emit newMessage(reply);
}