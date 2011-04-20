/* === This file is part of Tomahawk Player - <http://tomahawk-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *
 *   Tomahawk is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Tomahawk is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Tomahawk. If not, see <http://www.gnu.org/licenses/>.
 */

#include "adiumplugin.h"

using namespace Tomahawk::InfoSystem;

AdiumPlugin::AdiumPlugin(QObject *parent)
    : InfoPlugin(parent)
{
    /** No supported types since the plugin pushes info, doesn't get any */
    qDebug() << Q_FUNC_INFO;
    QSet< InfoType > supportedTypes;
    InfoSystem *system = qobject_cast< InfoSystem* >(parent);
    system->registerInfoTypes(this, supportedTypes);

    /** Connect to audio state signals.
	TODO: Move this into InfoSystem? There could end up being many plugins
	connected to audio state signals. */

    connect( system, SIGNAL( audioStarted( const Tomahawk::result_ptr& track ) ),
	     SLOT( audioStarted( const Tomahawk::result_ptr& track ) ) );
    connect( system, SIGNAL( audioFinished( const Tomahawk::result_ptr& track ) ),
	     SLOT( audioFinished( const Tomahawk::result_ptr& track ) ) );
    connect( system, SIGNAL( audioStopped( const Tomahawk::result_ptr& track ) ),
	     SLOT( audioStopped() ) );
    connect( system, SIGNAL( audioPaused( const Tomahawk::result_ptr& track ) ),
	     SLOT( audioPaused() ) );
    connect( system, SIGNAL( audioResumed( const Tomahawk::result_ptr& track ) ),
	     SLOT( audioResumed() ) );
    
}

AdiumPlugin::~AdiumPlugin()
{
    qDebug() << Q_FUNC_INFO;
}

void AdiumPlugin::getInfo(const QString &caller, const InfoType type, const QVariant& data, InfoCustomData customData)
{
    switch (type)
    {
        default:
        {
            emit info(caller, Tomahawk::InfoSystem::InfoNoInfo, QVariant(), QVariant(), customData);
            return;
        }
    }
}

/** Audio state slots */

void AdiumPlugin::audioStarted( const Tomahawk::result_ptr& track )
{
    qDebug() << Q_FUNC_INFO;
    // TODO: audio started, so push update status to Adium with playing track
}

void AdiumPlugin::audioFinished( const Tomahawk::result_ptr& track )
{
    qDebug() << Q_FUNC_INFO;
}

void AdiumPlugin::audioStopped()
{
    qDebug() << Q_FUNC_INFO;
    // TODO: audio stopped, so push update status to Adium that says "stopped"
}

void AdiumPlugin::audioPaused()
{
    qDebug() << Q_FUNC_INFO;
    // TODO: audio paused, so push update status to Adium that says "paused"
}

void AdiumPlugin::audioResumed()
{
    qDebug() << Q_FUNC_INFO;
    // TODO: audio resumed, so push update status to Adium with playing track
}
