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

#ifndef SCANNER_H
#define SCANNER_H

#include <QObject>
#include <QProcess>

// Forward declarations
class QSettings;

namespace vaultaire
{
	/**
	 * Model to represent a scanner device.
	 *
	 * @author Kyle Treubig <kyle@vimofthevine.com>
	 */
	class Scanner : public QObject
	{
		Q_OBJECT

		public:
			/**
			 * Scan result enumeration
			 */
			enum ScanResult {
				ScanCancelled,
				ScanComplete,
				ScanFailed,
				ScanNotStarted
			};

			/**
			 * Constructs a new scanner model.
			 *
			 * @param settings application settings
			 * @param parent   parent object
			 */
			Scanner(QSettings* settings, QObject* parent = 0);

			/**
			 * Performs a scan to the specified output file.
			 *
			 * @param filename output file name
			 */
			void scan(const QString& filename);

			/**
			 * Checks if the scanner is currently
			 * performing a scan.
			 *
			 * @return true if currently scanning
			 */
			bool isScanning() const;

		public slots:
			/**
			 * Cancels a running scan operation.
			 */
			void cancel();

		private slots:
			void finished(int exitCode, QProcess::ExitStatus exitStatus);
			void error(QProcess::ProcessError error);

		signals:
			/**
			 * Signals that a scan operation has begun.
			 */
			void started();

			/**
			 * Signals that a scan operation has finished.
			 *
			 * @param scan operation result
			 */
			void finished(Scanner::ScanResult result);

		private:
			QSettings* settings;
			QProcess* process;
	};
}

#endif
