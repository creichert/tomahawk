/* === This file is part of Tomahawk Player - <http://tomahawk-player.org> ===
 *
 *   Copyright 2012, Christopher Reichert <creichert07@gmail.com>
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

#include "MetaDataEditor.h"
#include "ui_MetaDataEditor.h"

#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtCore/QFileInfo>
#include <QtCore/QFile>

#include "Result.h"
#include "Artist.h"
#include "Album.h"
#include "Typedefs.h"

#include "taglib/fileref.h"
#include "filemetadata/taghandlers/tag.h"

MetaDataEditor::MetaDataEditor( Tomahawk::result_ptr result, QWidget *parent )
    : QDialog( parent )
    , ui( new Ui::MetaDataEditor )
    , m_result( result )
{
    ui->setupUi( this );
    setWindowTitle( QString( result->track() + tr( " Properties" ) ) );
    setAttribute( Qt::WA_DeleteOnClose );

    setTitle( result->track() );
    setArtist( result->artist()->name() );
    setAlbum( result->album()->name() );
    setDiscNumber( result->albumpos() );

    connect( ui->buttonBox, SIGNAL( accepted() ), SLOT( writeMetaData() ) );
    connect( ui->buttonBox, SIGNAL( rejected() ), SLOT( close() ) );

    connect( this, SIGNAL( scanFiles( QStringList& ) ), qApp, SLOT( scanFiles( QStringList& ) ) );
}


void
MetaDataEditor::writeMetaData()
{
    QFileInfo fi( QUrl( m_result->url() ).toLocalFile() );

    QByteArray fileName = QFile::encodeName( fi.canonicalFilePath() );
    const char *encodedName = fileName.constData();

    TagLib::FileRef f( encodedName );
    Tomahawk::Tag* tag = Tomahawk::Tag::fromFile( f );

    if ( title() != m_result->track() ) {
        tag->setTitle( title() );
        m_result->setTrack( title() );
    }

    Tomahawk::artist_ptr newArtist = Tomahawk::Artist::get( artist() );
    if ( artist() != m_result->artist()->name() ) {
        tag->setArtist( artist() );
        m_result->setArtist( newArtist );
    }

    if( album() != m_result->album()->name() ) {
        tag->setAlbum( album() );
        m_result->setAlbum( Tomahawk::Album::get( newArtist, album() ) );
    }

    tag->setTrack( discnumber() );
    m_result->setDiscNumber( discnumber() );

    f.save();

    QStringList files = QStringList( fileName );
    //ScanManager::instance()->scanFiles( files );
    close();
}


void
MetaDataEditor::setTitle( const QString& title )
{
    ui->titleLineEdit->setText( title );
}


void
MetaDataEditor::setArtist( const QString& artist )
{
    ui->artistLineEdit->setText( artist );
}


void
MetaDataEditor::setAlbum( const QString& album )
{
    ui->albumLineEdit->setText( album );
}


void
MetaDataEditor::setDiscNumber( unsigned int num )
{
    ui->discNumberSpinBox->setValue( num );
}

