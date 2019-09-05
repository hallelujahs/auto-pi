// Copyright (c) 2014-2019 winking324
//


#include "controller/log_controller.h"

#include <QDir>
#include <QDebug>
#include <QString>
#include <QIODevice>
#include <QDateTime>
#include <QApplication>

#include "commons/singleton.h"


namespace auto_pi {


static const QString kLogDir = "/var/log/auto-pi/";


struct LogConfig {
  qint64 pid = QApplication::applicationPid();
  QDateTime ts = QDateTime::currentDateTimeUtc();
  QFile log_file;
  QString log_file_name;
};


void ResetLogFileName() {
  auto *log_config = Singleton<LogConfig>::Instance();
  log_config->log_file_name = kLogDir;
  log_config->log_file_name += "auto_pi.log.";
  log_config->log_file_name += log_config->ts.toString("yyyyMMdd.");
  log_config->log_file_name += QString::number(log_config->pid);
}


void RemoveOldLogFiles() {
  // TODO(shanhui): remove old files
}


void RotateLogFile(const QDateTime &now) {
  auto *log_config = Singleton<LogConfig>::Instance();
  auto last_ts = log_config->ts.toSecsSinceEpoch();
  auto current_ts = now.toSecsSinceEpoch();

  if (current_ts - last_ts > 24 * 60 * 60) {
    log_config->ts = now;
    InitLog();
  }
}


void MessageHandler(QtMsgType type, const QMessageLogContext &context,
                    const QString &msg) {
  auto current = QDateTime::currentDateTimeUtc();
  RotateLogFile(current);

  auto *log_config = Singleton<LogConfig>::Instance();
  QTextStream stream(&log_config->log_file);

  static const QMap<QtMsgType, QString> kMsgTypeStr = {
    {QtDebugMsg, "D"},
    {QtInfoMsg, "I"},
    {QtWarningMsg, "W"},
    {QtCriticalMsg, "E"},
    {QtFatalMsg, "F"},
    {QtSystemMsg, "E"}
  };

  stream << kMsgTypeStr[type] << current.toString("MMdd hh:mm:ss.zzz ")
         << log_config->pid << " " << context.file << ":" << context.line
         << " " << context.function << ": " << msg << endl;

  if (type == QtFatalMsg) {
    log_config->log_file.close();
    abort();
  }
}


bool InitLog() {
  if (!QDir(kLogDir).exists()) {
    QDir().mkdir(kLogDir);
  }

  RemoveOldLogFiles();
  ResetLogFileName();

  auto *log_config = Singleton<LogConfig>::Instance();
  if (log_config->log_file.isOpen()) {
    log_config->log_file.close();
  }

  log_config->log_file.setFileName(log_config->log_file_name);
  if (log_config->log_file.open(QIODevice::WriteOnly|QIODevice::Append)) {
    qInstallMessageHandler(MessageHandler);
    return true;
  }
  return false;
}


}  // namespace auto_pi
