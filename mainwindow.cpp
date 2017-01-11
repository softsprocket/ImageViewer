#include "mainwindow.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMenuBar>
#include <QString>
#include <QStandardPaths>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <QToolBar>
#include <QStatusBar>
#include <QToolButton>
#include <QImageReader>
#include <QByteArray>
#include <QFileInfo>

#include <exiv2/exiv2.hpp>
#include <map>

#include "opendatadialog.h"
#include "filepreviewdialog.h"

MainWindow::MainWindow (QWidget *parent)
	: QMainWindow(parent), m_currentImage (nullptr), m_item (nullptr), m_picDir (QString::null) {
	m_scene = new QGraphicsScene (this);
	m_view = new QGraphicsView (this);
	m_view->setScene (m_scene);

	this->setCentralWidget (m_view);

	createActions ();
	createMenus ();
	createToolbars ();

	setStatusBar (statusBar ());
	statusBar ()->showMessage ("Go");

	resize (QDesktopWidget ().availableGeometry (this).size () * 0.7);

	setWindowTitle ("Image Viewer");
}

MainWindow::~MainWindow () {
	if (m_currentImage != nullptr) {
		delete m_currentImage;
	}
}

void MainWindow::createMenus () {
	m_fileMenu = menuBar ()->addMenu (tr ("&File"));
	m_fileMenu->addAction (m_openAction);
	m_fileMenu->addAction (m_metadataAction);

}

void MainWindow::createActions () {
	m_openAction = new QAction (tr ("&Open"), this);
	m_openAction->setShortcuts (QKeySequence::Open);
	m_openAction->setStatusTip (tr ("Open image file"));
	connect (m_openAction, &QAction::triggered, this, &MainWindow::openFileDialog);

	m_metadataAction = new QAction (tr ("&Metadata"), this);
	m_metadataAction->setShortcut (QKeySequence(tr("Ctrl+M")));
	m_metadataAction->setStatusTip (tr ("Open image file"));
	connect (m_metadataAction, &QAction::triggered, this, &MainWindow::openMetadataDialog);
	m_metadataAction->setVisible (false);

	m_vflipAction = new QAction (tr ("VFlip"), this);
	connect (m_vflipAction, &QAction::triggered, this, &MainWindow::flipVertical);
	m_hflipAction = new QAction (tr ("HFlip"), this);
	connect (m_hflipAction, &QAction::triggered, this, &MainWindow::flipHorizontal);
}

void MainWindow::createToolbars () {
	QToolBar* transBar = addToolBar ("Translate");
	m_vflipButton = new QToolButton (this);
	m_vflipButton->setDefaultAction (m_vflipAction);

	m_hflipButton = new QToolButton (this);
	m_hflipButton->setDefaultAction (m_hflipAction);


	transBar->addWidget (m_vflipButton);
	transBar->addWidget (m_hflipButton);
}

void MainWindow::openFileDialog () {
	if (m_picDir.isNull ()) {
		m_picDir = QStandardPaths::writableLocation (QStandardPaths::PicturesLocation);
	}

	QList<QByteArray> supportedFormats = QImageReader::supportedImageFormats();

	QString imgFormats = "Image Files (";
	for (QByteArray format : supportedFormats) {
		imgFormats.append(" *.");
		imgFormats.append (format);
	}
	imgFormats.append(")");


	QString fileName = QFileDialog::getOpenFileName (this, tr("Open Image"), m_picDir, imgFormats);

	if (fileName.isNull ()) {
		return;
	}
	QString title ("Image Viewer - ");
	title.append(fileName);
	setWindowTitle (title);

	Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open (fileName.toStdString ());
	if (image.get () != 0) {
		image->readMetadata();
		QString mimeType (image->mimeType ().c_str ());
		statusBar ()->showMessage (mimeType);

		 Exiv2::ExifData & exifData = image->exifData();
		 if (!exifData.empty ()) {
			mimeType.append (" - EXIF");


			Exiv2::ExifData::const_iterator end = exifData.end();
			for (Exiv2::ExifData::const_iterator i = exifData.begin(); i != end; ++i) {

				m_metaDataKeyValues[QString (i->key ().c_str ())] = QString (i->value ().toString ().c_str ());
			}

			m_metadataAction->setVisible (true);
		 }

		 Exiv2::IptcData & iptcData = image->iptcData();
		 if (!iptcData.empty ()) {
			mimeType.append (" - IPTC");

			Exiv2::IptcData::const_iterator end = iptcData.end();
			for (Exiv2::IptcData::const_iterator i = iptcData.begin(); i != end; ++i) {
				m_metaDataKeyValues[QString (i->key ().c_str ())] = QString (i->value ().toString ().c_str ());
			}

			m_metadataAction->setVisible (true);
		}

		 Exiv2::XmpData & xmpData = image->xmpData();
		 if (!xmpData.empty ()) {
			mimeType.append (" - XMP");

			Exiv2::XmpData::const_iterator end = xmpData.end();
			for (Exiv2::XmpData::const_iterator i = xmpData.begin(); i != end; ++i) {
				m_metaDataKeyValues[QString (i->key ().c_str ())] = QString (i->value ().toString ().c_str ());
			}

			m_metadataAction->setVisible (true);
		}

		 statusBar ()->showMessage (mimeType);
	}

	FilePreviewDialog fpd (this, image.get ());
	fpd.exec ();

	QFileInfo fi (fileName);
	m_picDir = fi.absolutePath ();

	if (m_currentImage != nullptr) {
		delete m_currentImage;
	}

	m_currentImage = new QPixmap (fileName);

	if (m_item != nullptr) {
		delete m_item;
	}

	m_item = new QGraphicsPixmapItem (*m_currentImage);
	m_scene->addItem (m_item);


}

void MainWindow::openMetadataDialog () {
	OpenDataDialog odd (this);
	odd.addKeyValueTable (m_metaDataKeyValues);
	odd.exec ();
}

void MainWindow::flipHorizontal () {

	// Get the current transform
	QTransform transform(m_item->transform());

	qreal m11 = transform.m11();    // Horizontal scaling
	qreal m12 = transform.m12();    // Vertical shearing
	qreal m13 = transform.m13();    // Horizontal Projection
	qreal m21 = transform.m21();    // Horizontal shearing
	qreal m22 = transform.m22();    // vertical scaling
	qreal m23 = transform.m23();    // Vertical Projection
	qreal m31 = transform.m31();    // Horizontal Position (DX)
	qreal m32 = transform.m32();    // Vertical Position (DY)
	qreal m33 = transform.m33();    // Addtional Projection Factor

	// We need this in a minute
	qreal scale = m11;

	// Horizontal flip
	m11 = -m11;

	// Re-position back to origin
	if(m31 > 0)
		m31 = 0;
	else
		m31 = (m_item->boundingRect().width() * scale);

	// Write back to the matrix
	transform.setMatrix(m11, m12, m13, m21, m22, m23, m31, m32, m33);

	// Set the items transformation
	m_item->setTransform(transform);
}

void MainWindow::flipVertical () {
	// Get the current transform
	QTransform transform(m_item->transform());

	qreal m11 = transform.m11();    // Horizontal scaling
	qreal m12 = transform.m12();    // Vertical shearing
	qreal m13 = transform.m13();    // Horizontal Projection
	qreal m21 = transform.m21();    // Horizontal shearing
	qreal m22 = transform.m22();    // vertical scaling
	qreal m23 = transform.m23();    // Vertical Projection
	qreal m31 = transform.m31();    // Horizontal Position (DX)
	qreal m32 = transform.m32();    // Vertical Position (DY)
	qreal m33 = transform.m33();    // Addtional Projection Factor

	// We need this in a minute
	qreal scale = m22;

	// Vertical flip
	m22 = -m22;

	// Re-position back to origin
	if(m32 > 0)
		m32 = 0;
	else
		m32 = (m_item->boundingRect().height() * scale);

	// Write back to the matrix
	transform.setMatrix(m11, m12, m13, m21, m22, m23, m31, m32, m33);

	// Set the items transformation
	m_item->setTransform(transform);

}
