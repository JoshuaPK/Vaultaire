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

#include "ScannerSettings.h"
#include "SettingKeys.h"

namespace vaultaire
{
	static const QString DEVICE_HELP = "Unique identifier of the scanner device";
	static const QString SCAN_COMMAND_HELP = "Command to be executed to perform a scan operation.\n"
		"\n"
		"The following values in the command are automatically replaced:\n"
		"  %device% : the unique name of the scanner device";
	static const QString SCANNED_SUFFIX_HELP = "File extension of the output scanned file";
	static const QString CONVERT_COMMAND_HELP = "Command to be executed to perform image file conversion.\n"
		"\n"
		"The following values in the command are automatically replaced:\n"
		"  %in% : original image file name\n"
		"  %out% : output (converted) image file name";
	static const QString CONVERT_SUFFIX_HELP = "File extension of the converted image file";

	/** Constructor */
	ScannerSettings::ScannerSettings(QWidget* parent)
		: QWidget(parent)
	{
		settings = new QSettings(QSettings::SystemScope,
			qApp->organizationName(), qApp->applicationName(), this);

		// Scanner device field
		QString currentDevice = settings->value(SCANNER_DEVICE_KEY,
			DEFAULT_SCANNER_DEVICE).toString();
		scannerDevice = new QLineEdit(currentDevice, this);
		scannerDevice->setToolTip(DEVICE_HELP);
		connect(scannerDevice, SIGNAL(textEdited(QString)),
			this, SLOT(deviceNameChanged(QString)));

		// Scan command field
		QString currentCommand = settings->value(SCAN_COMMAND_KEY,
			DEFAULT_SCAN_COMMAND).toString();
		scanCommand = new QTextEdit(currentCommand, this);
		scanCommand->setToolTip(SCAN_COMMAND_HELP);
		scanCommand->setTabChangesFocus(true);
		scanCommand->setMaximumHeight(100);
		connect(scanCommand, SIGNAL(textChanged()),
			this, SLOT(scanCommandChanged()));

		// Scanned file suffix field
		QString currentScanSuffix = settings->value(SCANNED_SUFFIX_KEY,
			DEFAULT_SCANNED_SUFFIX).toString();
		scannedSuffix = new QLineEdit(currentScanSuffix, this);
		scannedSuffix->setToolTip(SCANNED_SUFFIX_HELP);
		connect(scannedSuffix, SIGNAL(textEdited(QString)),
			this, SLOT(scanSuffixChanged(QString)));

		// Conversion command field
		QString currentConvertCmd = settings->value(CONVERT_CMD_KEY,
			DEFAULT_CONVERT_CMD).toString();
		convertCommand = new QTextEdit(currentConvertCmd, this);
		convertCommand->setToolTip(CONVERT_COMMAND_HELP);
		convertCommand->setTabChangesFocus(true);
		convertCommand->setMaximumHeight(100);
		connect(convertCommand, SIGNAL(textChanged()),
			this, SLOT(convertCommandChanged()));

		// Converted file suffix field
		QString currentConvertedSuffix = settings->value(CONVERTED_SUFFIX_KEY,
			DEFAULT_CONVERTED_SUFFIX).toString();
		convertedSuffix = new QLineEdit(currentConvertedSuffix, this);
		convertedSuffix->setToolTip(CONVERT_SUFFIX_HELP);
		connect(convertedSuffix, SIGNAL(textEdited(QString)),
			this, SLOT(convertSuffixChanged(QString)));

		// Do-conversion field
		bool currentDoConvert = settings->value(DO_CONVERT_KEY, false).toBool();
		doConversion = new QCheckBox(this);
		doConversion->setChecked(currentDoConvert);
		connect(doConversion, SIGNAL(clicked(bool)),
			this, SLOT(doConversionChanged(bool)));
		connect(doConversion, SIGNAL(clicked(bool)),
			convertCommand, SLOT(setEnabled(bool)));
		connect(doConversion, SIGNAL(clicked(bool)),
			convertedSuffix, SLOT(setEnabled(bool)));

		// Create form
		QFormLayout* form = new QFormLayout;
		setLayout(form);
		form->addRow(tr("Scanner Device"), scannerDevice);
		form->addRow(tr("Scan Command"), scanCommand);
		form->addRow(tr("Scanned File Extension"), scannedSuffix);
		form->addRow(tr("Convert Scanned File?"), doConversion);
		form->addRow(tr("Conversion Command"), convertCommand);
		form->addRow(tr("Converted File Extension"), convertedSuffix);

		// Disable field if not writable (i.e., no permission
		// to modify system-level settings)
		scannerDevice->setEnabled(settings->isWritable());
		scanCommand->setEnabled(settings->isWritable());
		scannedSuffix->setEnabled(settings->isWritable());
		doConversion->setEnabled(settings->isWritable());
		convertCommand->setEnabled(currentDoConvert && settings->isWritable());
		convertedSuffix->setEnabled(currentDoConvert && settings->isWritable());
	}

	/** Store change to scanner device */
	void ScannerSettings::deviceNameChanged(const QString& newDevice)
	{
		settings->setValue(SCANNER_DEVICE_KEY, newDevice);
	}

	/** Store change to scan command */
	void ScannerSettings::scanCommandChanged()
	{
		settings->setValue(SCAN_COMMAND_KEY, scanCommand->toPlainText());
	}

	/** Store change to scanned file suffix */
	void ScannerSettings::scanSuffixChanged(const QString& newSuffix)
	{
		settings->setValue(SCANNED_SUFFIX_KEY, newSuffix);
	}

	/** Store change to do-conversion */
	void ScannerSettings::doConversionChanged(bool doConvert)
	{
		settings->setValue(DO_CONVERT_KEY, doConvert);
	}

	/** Store change to conversion command */
	void ScannerSettings::convertCommandChanged()
	{
		settings->setValue(CONVERT_CMD_KEY, convertCommand->toPlainText());
	}

	/** Store change to converted file suffix */
	void ScannerSettings::convertSuffixChanged(const QString& newSuffix)
	{
		settings->setValue(CONVERTED_SUFFIX_KEY, newSuffix);
	}

}

