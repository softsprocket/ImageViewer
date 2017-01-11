#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifndef Q_MAINWINDOW_INCLUDED_
#define Q_MAINWINDOW_INCLUDED_
#include <QMainWindow>
#endif// Q_MAINWINDOW_INCLUDED_

#ifndef Q_PIXMAP_INCLUDED_
#define Q_PIXMAP_INCLUDED_
#include <QPixmap>
#endif// Q_PIXMAP_INCLUDED_

#ifndef Q_GRAPHICSSCENE_INCLUDED_
#define Q_GRAPHICSSCENE_INCLUDED_
#include <QGraphicsScene>
#endif// Q_GRAPHICSSCENE_INCLUDED_

#ifndef Q_GRAPHICSVIEW_INCLUDED_
#define Q_GRAPHICSVIEW_INCLUDED_
#include <QGraphicsView>
#endif// Q_GRAPHICSVIEW_INCLUDED_

#ifndef Q_GRAPHICSPIXMAPITEM_INCLUDED_
#define Q_GRAPHICSPIXMAPITEM_INCLUDED_
#include <QGraphicsPixmapItem>
#endif// Q_GRAPHICSPIXMAPITEM_INCLUDED_

#ifndef Q_TOOLBUTTON_INCLUDED_
#define Q_TOOLBUTTON_INCLUDED_
#include <QToolButton>
#endif// Q_TOOLBUTTON_INCLUDED_

#ifndef STD_MAP_INCLUDED_
#define STD_MAP_INCLUDED_
#include <map>
#endif // STD_MAP_INCLUDED_

class MainWindow : public QMainWindow {
	Q_OBJECT
private:
	QMenu* m_fileMenu;
	QAction* m_openAction;
	QAction* m_metadataAction;

	QToolButton* m_hflipButton;
	QAction* m_hflipAction;
	QToolButton* m_vflipButton;
	QAction* m_vflipAction;

	std::map<QString, QString> m_metaDataKeyValues;

	void createMenus ();
	void createToolbars ();
	void createActions ();
	void openFileDialog ();
	void openMetadataDialog ();

	QGraphicsScene* m_scene;
	QGraphicsView* m_view;
	QPixmap* m_currentImage;
	QGraphicsPixmapItem* m_item;
	QString m_picDir;

	void flipHorizontal ();
	void flipVertical ();
public:
	MainWindow (QWidget *parent = 0);
	~MainWindow ();
};

#endif // MAINWINDOW_H
