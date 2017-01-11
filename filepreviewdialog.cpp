#include "filepreviewdialog.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>

#include <iostream>

#include <exiv2/exiv2.hpp>

FilePreviewDialog::FilePreviewDialog (QWidget* parent, Exiv2::Image* image) : QDialog (parent), m_image (image) {
	setModal (true);
	resize (600, 800);
	setWindowTitle ("File Preview");
	m_thumbnailScene = new QGraphicsScene;
	m_thumbnailView = new QGraphicsView (this);
	m_thumbnailView->setScene (m_thumbnailScene);
	getThumbnail ();
}

void FilePreviewDialog::getThumbnail () {
	Exiv2::PreviewManager loader (*m_image);
	Exiv2::PreviewPropertiesList list = loader.getPreviewProperties();

	// Some application logic to select one of the previews from the list
	Exiv2::PreviewPropertiesList::const_iterator pos = list.cbegin ();

	if (pos != list.cend()) {
		// Get the selected preview image
		Exiv2::PreviewImage preview = loader.getPreviewImage (*pos);

		std::string name = "preview" + preview.extension ();

		std::cout << "Writing preview" << " "
			  << preview.width () << "x" << preview.height () << " "
			  << "to file" << " " << name << std::endl;

		preview.writeFile ("preview");
		QPixmap* thumbnail = new QPixmap (name.c_str ());

		m_thumbnailItem = new QGraphicsPixmapItem (*thumbnail);
		m_thumbnailScene->addItem (m_thumbnailItem);
	}

}


