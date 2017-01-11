#include "opendatadialog.h"

#include <QDialog>
#include <QSize>
#include <QDialogButtonBox>
#include <QScrollArea>
#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QLabel>
#include <QHeaderView>

#include <map>

OpenDataDialog::OpenDataDialog (QWidget* parent) :
	QDialog (parent) {
//	setModal (true);
	resize (600, 800);
	setWindowTitle ("File Metadata");

	m_dialogLayout = new QVBoxLayout;
	setLayout (m_dialogLayout);

	m_scrollArea = new QScrollArea;
	m_scrollAreaLayout = new QVBoxLayout;
	m_scrollArea->setLayout (m_scrollAreaLayout);

	m_scrollArea->resize (600, 750);


	m_dialogLayout->addWidget (m_scrollArea);

	QDialogButtonBox* buttonBox = new QDialogButtonBox (QDialogButtonBox::Close, this);
	connect (buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

	m_dialogLayout->addWidget (buttonBox);
}

void OpenDataDialog::addKeyValueTable (std::map<QString, QString>& keyValues) {
	QTableWidget* table = new QTableWidget;
	int len = keyValues.size ();

	table->setRowCount (len);
	table->setColumnCount (2);

	QHeaderView* header = table->horizontalHeader ();
	header->setSectionResizeMode (QHeaderView::ResizeToContents);
	int row = 0;

	for (auto p : keyValues) {
		QTableWidgetItem* key = new QTableWidgetItem (p.first);
		table->setItem (row, 0, key);
		table->setItem (row, 1, new QTableWidgetItem (p.second));
		++row;
	}

	m_scrollAreaLayout->addWidget (table);
}
