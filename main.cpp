// By Reza Banivakil

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QStringList>
#include <QTextStream>

const int max_zeros = 1;
QStringList numbers{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

QString stringMultiplier(QString str, const int factor) {
  QString tmp(str);
  for (int i = 0; i < factor - 1; i++) {
    tmp.append(str);
  }
  return tmp;
}

bool checkInList(QString var, QStringList &list, int pos) {
  foreach (const QString item, list) {
    if (var.at(pos) == item)
      return true;
  }
  return false;
}

void change(QDir &dir, QStringList &numbers) {
  foreach (
      QFileInfo fi,
      dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::Name)) {
    int i = 0;
    if (fi.isDir()) {
      QDir child(fi.filePath());
      change(child, numbers);
    }
    while (checkInList(fi.fileName(), numbers, i)) {
      i++;
    }
    if (i == max_zeros) {
      QString newName = fi.absolutePath() + "/" +
                        stringMultiplier("0", max_zeros) + fi.fileName();
      QDir dir(fi.absoluteFilePath());
      dir.rename(fi.absoluteFilePath(), newName);
    }
  }
}

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  QString path;
  qInfo() << "Please enter your path:";
  QTextStream qtin(stdin);
  path = qtin.readLine().replace('\\', '/');
  QDir dir(path);
  change(dir, numbers);
  qInfo() << "Finished";
  return a.exec();
}
