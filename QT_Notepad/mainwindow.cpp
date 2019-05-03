#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
   //Clear the screen
    currentFile.clear();
   //Create a new text window
    ui->textEdit->setText(QString());
}

void MainWindow::on_actionOpen_triggered()
{
    //Open a new file
    QString fileName = QFileDialog::getOpenFileName(this, "Open the File");
    QFile file(fileName);
    currentFile = fileName;

    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Can not open file: ", file.errorString());
    }

    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText((text));
    file.close();


}

void MainWindow::on_actionSave_triggered()
{
    //Open a new file
    QString fileName = QFileDialog::getSaveFileName(this, "Save the File");
    QFile file(fileName);


    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Can not save file: ", file.errorString());
    }

      currentFile = fileName;
        setWindowTitle(fileName);
        QTextStream out(&file);

        //Copy the text in the text edit
        QString text = ui->textEdit->toPlainText();
        out << text;
        file.close();



}

void MainWindow::on_actionExit_triggered()
{
    //print "Are you sure you want to quit? (y/n)
    QApplication::quit();
}



void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}



void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}
