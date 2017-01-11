#ifndef OPENDATADIALOG_H
#define OPENDATADIALOG_H

#ifndef Q_DIALOG_INCLUDED_
#define Q_DIALOG_INCLUDED_
#include <QDialog>
#endif // Q_DIALOG_INCLUDED_

#ifndef Q_WIDGET_INCLUDED_
#define Q_WIDGET_INCLUDED_
#include <QWidget>
#endif // Q_WIDGET_INCLUDED_

#ifndef Q_SCROLLAREA_INCLUDED_
#define Q_SCROLLAREA_INCLUDED_
#include <QScrollArea>
#endif // Q_SCROLLAREA_INCLUDED_

#ifndef Q_VBOXLAYOUT_INCLUDED_
#define Q_VBOXLAYOUT_INCLUDED_
#include <QVBoxLayout>
#endif // Q_VBOXLAYOUT_INCLUDED_

#ifndef STD_MAP_INCLUDED_
#define STD_MAP_INCLUDED_
#include <map>
#endif // STD_MAP_INCLUDED_

class OpenDataDialog : public QDialog {
	QScrollArea* m_scrollArea;
	QVBoxLayout* m_dialogLayout;
	QVBoxLayout* m_scrollAreaLayout;
public:
	OpenDataDialog (QWidget* parent);

	void addKeyValueTable (std::map<QString, QString>& keyValues);
};

#endif // OPENDATADIALOG_H
