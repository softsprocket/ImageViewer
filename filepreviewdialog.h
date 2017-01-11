#ifndef FILEPREVIEWDIALOG_H
#define FILEPREVIEWDIALOG_H

#ifndef EXIV2_EXIV2_INCLUDED_
#define  EXIV2_EXIV2_INCLUDED_
#include <exiv2/exiv2.hpp>
#endif // EXIV2_EXIV2_INCLUDED_

#ifndef Q_GRAPHICSSCENE_INCLUDED_
#define Q_GRAPHICSSCENE_INCLUDED_
#include <QGraphicsScene>
#endif // Q_GRAPHICSSCENE_INCLUDED_

#ifndef Q_GRAPHICSVIEW_INCLUDED_
#define Q_GRAPHICSVIEW_INCLUDED_
#include <QGraphicsView>
#endif // Q_GRAPHICSVIEW_INCLUDED_

#ifndef Q_DIALOG_INCLUDED_
#define Q_DIALOG_INCLUDED_
#include <QDialog>
#endif // Q_DIALOG_INCLUDED_

class FilePreviewDialog : public QDialog {
	Exiv2::Image* m_image;
	QGraphicsScene* m_thumbnailScene;
	QGraphicsView* m_thumbnailView;
	QGraphicsPixmapItem* m_thumbnailItem;
public:
	FilePreviewDialog(QWidget* parent, Exiv2::Image* image);
	void getThumbnail ();
};

#endif // FILEPREVIEWDIALOG_H
