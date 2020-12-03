/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DockWidgetQuick.h"

#include <QObject>
#include <QQmlParserStatus>
#include <QString>

namespace KDDockWidgets {

class DockWidgetQuick;

/**
 * @brief Indirection helper to instantiate dock widgets from QML
 *
 * "DockWidget {}" in QML won't create a KDDockWidget::DockWidget directly, but instead an
 * DockWidgetInstantiator. DockWidgetInstantiator will then create the DockWidget instance only
 * when the QML parsing ends (and all propreties are set)
 *
 * This allows to pass the correct uniqueName to DockWidget's ctor.
 */
class DockWidgetInstantiator
        : public QObject
        , public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QString uniqueName READ uniqueName WRITE setUniqueName NOTIFY uniqueNameChanged)
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(KDDockWidgets::DockWidgetQuick *dockWidget READ dockWidget NOTIFY dockWidgetChanged)
public:
    QString uniqueName() const;
    void setUniqueName(const QString &);

    QString source() const;
    void setSource(const QString &);

    DockWidgetQuick *dockWidget() const;

protected:
    void classBegin() override;
    void componentComplete() override;

Q_SIGNALS:
    void uniqueNameChanged();
    void sourceChanged();
    void dockWidgetChanged();
private:
    QString m_uniqueName;
    QString m_sourceFilename;
    DockWidgetQuick *m_dockWidget = nullptr;

};

}
