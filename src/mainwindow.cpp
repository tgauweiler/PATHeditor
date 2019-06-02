#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDir>
#include <QShortcut>
#include <windows.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect SLOTs
    QObject::connect(this->ui->tableWidget, &QTableWidget::cellChanged, this, &MainWindow::SLOTcellChanged);
    QObject::connect(this->ui->saveButton, &QPushButton::clicked, this, &MainWindow::SLOTsavePATH);
    QObject::connect(this->ui->addButton, &QPushButton::clicked, this, &MainWindow::SLOTaddEntry);

    QShortcut* shortcut = new QShortcut(QKeySequence(Qt::Key_Delete), this, SLOT(SLOTdeleteEntry()));
    shortcut->setAutoRepeat(false);

    // Setup table
    this->ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    this->ui->tableWidget->horizontalHeader()->hide();

    readPATH();
    updateTable();
    updatePathValues();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->pathRegistry;
}

void MainWindow::SLOTcellChanged(int row, int column)
{
    QString path = this->ui->tableWidget->item(row, column)->text();
    bool exists = this->existsFolder(path);

    // Set color of table cell text
    if (exists)
    {
        this->ui->tableWidget->item(row, column)->setTextColor(QColor(Qt::GlobalColor::black));
    }
    else
    {
        this->ui->tableWidget->item(row, column)->setTextColor(QColor(Qt::GlobalColor::red));
    }
    //    qDebug() << row << column << path << exists;
}

void MainWindow::readPATH()
{
    this->pathRegistry = new QSettings("HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment", QSettings::NativeFormat);
    this->pathValues = this->pathRegistry->value("Path", "no-path").toString().split(";");
    //    qDebug() << pathValues;
}

bool MainWindow::existsFolder(const QString& path)
{
    return QDir(path).exists();
}

void MainWindow::SLOTsavePATH()
{
    QString path = this->pathValues.join(";");
    this->pathRegistry->setValue("Path", path);
    SendMessageA(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM) "Environment");
    qDebug() << "SAVING..." << path;
}

void MainWindow::SLOTaddEntry()
{
    int numRows = this->ui->tableWidget->rowCount();
    this->ui->tableWidget->insertRow(numRows);

    //    this->ui->tableWidget->editItem(this->ui->tableWidget->item(numRows,0)); // Not working at the moment for the last row
}

void MainWindow::SLOTdeleteEntry()
{
    this->ui->tableWidget->removeRow(this->ui->tableWidget->currentRow());
}

void MainWindow::updateTable()
{
    this->ui->tableWidget->clear();
    this->ui->tableWidget->setRowCount(this->pathValues.length());
    this->ui->tableWidget->setColumnCount(1);
    for (int c = 0; c < this->pathValues.length(); ++c)
    {
        this->ui->tableWidget->setItem(c, 0, new QTableWidgetItem(this->pathValues.at(c)));
    }
}

void MainWindow::updatePathValues()
{
    this->pathValues.clear();
    QAbstractItemModel* model = this->ui->tableWidget->model();
    for (int r = 0; r < model->rowCount(); ++r)
    {
        this->pathValues = this->pathValues + model->index(r, 0).data().toStringList();
    }
    qDebug() << this->pathValues;
}
