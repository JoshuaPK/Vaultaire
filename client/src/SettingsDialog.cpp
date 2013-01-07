/*
 * Copyright 2012 Kyle Treubig
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <QtGui>

#include "SettingsDialog.h"

namespace vaultaire
{
	/** Constructor */
	SettingsDialog::SettingsDialog(QWidget* parent) : QDialog(parent)
	{
		selection = new QListWidget(this);
		selection->setMaximumWidth(10);

		pages = new QStackedWidget(this);
		connect(selection, SIGNAL(currentRowChanged(int)),
			pages, SLOT(setCurrentIndex(int)));

		// Selection list and settings pages
		QHBoxLayout* topLayout = new QHBoxLayout;
		topLayout->addWidget(selection);
		topLayout->addWidget(pages);

		// Buttons
		QDialogButtonBox* buttons = new QDialogButtonBox(
			QDialogButtonBox::Close);
		connect(buttons, SIGNAL(rejected()), this, SLOT(close()));

		// Put it all together
		QVBoxLayout* mainLayout = new QVBoxLayout;
		mainLayout->addLayout(topLayout);
		mainLayout->addWidget(buttons);
		setLayout(mainLayout);

		setWindowTitle(tr("Settings"));
	}

	/** Add settings page */
	void SettingsDialog::add(const QString& label, QWidget* page)
	{
		selection->addItem(label);
		pages->addWidget(page);

		// Make sure selection widget is wide enough
		QLabel tmp(label);
		int width = tmp.sizeHint().width() + 25;
		if (selection->maximumWidth() < width)
		{
			selection->setMaximumWidth(width);
		}
	}
}

