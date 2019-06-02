#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    void readPATH();
    void updateTable();
    void updatePathValues();
    bool existsFolder(const QString& path);
    ~MainWindow();

public slots:
    void SLOTcellChanged(int row, int column);
    void SLOTsavePATH();
    void SLOTaddEntry();
    void SLOTdeleteEntry();

private:
    Ui::MainWindow* ui;
    QSettings* pathRegistry;
    QStringList pathValues;
};

#endif // MAINWINDOW_H
