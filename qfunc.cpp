#include "qfunc.h"

QMap<QString, fileTypes>& extensionMap()
{
  static QMap<QString, fileTypes> qmap;
  return qmap;
}


QString getFileTypeDescription(fileTypes type)
{

  if (type == fileTypes::Map) return QString("Map");
  if (type == fileTypes::Texture) return QString("Texture");
  if (type == fileTypes::Graphic) return QString("Graphic");
  if (type == fileTypes::Sound) return QString("Sound");
  if (type == fileTypes::Demo) return QString("Demo");
  if (type == fileTypes::Model) return QString("Model");
  if (type == fileTypes::Skin) return QString("Skin");
  if (type == fileTypes::Data) return QString("Data");
  if (type == fileTypes::Other) return QString("Other");
  if (type == fileTypes::Config) return QString("Configuration");
  throw (QString("Unknown fileType encountered"));

  return QString(); // We should never return this...
}



QString getSinglePathSelection()
{
  QFileDialog fileDialog;
  fileDialog.setFileMode(QFileDialog::Directory);
  fileDialog.setViewMode(QFileDialog::Detail);
  fileDialog.setOption(QFileDialog::ShowDirsOnly, true);
  fileDialog.setOption(QFileDialog::DontUseNativeDialog, true);

  QStringList files;
  if (fileDialog.exec()) {
      files = fileDialog.selectedFiles();
    }

  if (files.empty()) {
      QMessageBox(QMessageBox::Warning, QString("No selection"), QString("No output folder selected."),QMessageBox::Close).exec();
      return QString();
    }

  QString path = QDir::toNativeSeparators(files.at(0));
  return path;
}


QStringList getFileSelections()
{
  QFileDialog fileDialog;
  fileDialog.setFileMode(QFileDialog::ExistingFiles);
  fileDialog.setViewMode(QFileDialog::Detail);

  QStringList files;
  if (fileDialog.exec()) {
      files = fileDialog.selectedFiles();
    }

  return files;
}


fileTypes getFileType(QString extension)
{
  return extensionMap().value(extension, fileTypes::Other);
}


QString absoluteFileName(std::array< char, int(PAK_DATA_LABEL_SIZE) > fname)
{
  QString filename(QString::fromLocal8Bit(static_cast<char*>(fname.data()), PAK_DATA_LABEL_SIZE));
  QString x =  getFileName(filename);
  x.truncate(x.indexOf((QChar)0));
  return x;

}

QString getFileName(const QString &x)
{
  QFileInfo f(x);
  return f.fileName();
}



QString arrayToQString(std::array< char, int(PAK_DATA_LABEL_SIZE) > &filename)
{
  QString filename_stringified = QString::fromLocal8Bit(filename.data() , PAK_DATA_LABEL_SIZE);
  filename_stringified.truncate(filename_stringified.indexOf((QChar)0));
  return filename_stringified;
}


QString getExtension(std::array<char, PAK_DATA_LABEL_SIZE> &filename)
{

  auto it = std::find(filename.begin(), filename.end(), '.');
  it++; // Skip the .
  auto end = std::find(it, filename.end(), '\0');
  QString s;
  s.resize(static_cast<int>(std::distance(it, end)));
  std::copy(it, end, s.begin());
  s = s.toLower();
  return s;
}


bool confirmOverwrite(QString filename)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("File exists");
    msgBox.setText(filename);
    msgBox.setInformativeText("This file already exists.  Do you want to save and overwrite?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int result = msgBox.exec();
    switch (result) {
      case QMessageBox::Ok:
        return true;
        break;
      case QMessageBox::Cancel:
        return false;
        break;
      default:
        return false;
      }
    return false;
}
