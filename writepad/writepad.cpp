#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFont>
#include <QFontDialog>

#include "writepad.h"
#include "ui_writepad.h"

WritePad::WritePad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WritePad)
{
    /**
    * @brief all the action i used to create this application \n
    */
    ui->setupUi(this);
    connect(ui->actionNew, &QAction::triggered, this, &WritePad::newDocument);
    connect(ui->actionOpen, &QAction::triggered, this, &WritePad::open);
    connect(ui->actionSave, &QAction::triggered, this, &WritePad::save);
    connect(ui->actionSaveAs, &QAction::triggered, this, &WritePad::saveAs);
    connect(ui->actionCopy, &QAction::triggered, this, &WritePad::copy);
    connect(ui->actionCut, &QAction::triggered, this, &WritePad::cut);
    connect(ui->actionPast, &QAction::triggered, this, &WritePad::paste);
    connect(ui->actionUndo, &QAction::triggered, this, &WritePad::undo);
    connect(ui->actionRedo, &QAction::triggered, this, &WritePad::redo);
    connect(ui->actionZoom, &QAction::triggered, this, &WritePad::zoomIn);
    connect(ui->actionZoom_Out, &QAction::triggered, this, &WritePad::zoomOut);
    connect(ui->actionFont, &QAction::triggered, this, &WritePad::selectFont);
    connect(ui->actionRead_Only, &QAction::triggered, this, &WritePad::readOnly);
    connect(ui->actionAbout, &QAction::triggered, this, &WritePad::about);

    /**
    * @brief  The clipboard offers a simple mechanism to copy and paste data between applications. \n
    */

#if !QT_CONFIG(clipboard)
    ui->actionCut->setEnabled(false);
    ui->actionCopy->setEnabled(false);
    ui->actionPaste->setEnabled(false);
#endif
}

WritePad::~WritePad()
{
    delete ui;
}

void WritePad::newDocument()
{
    /**
    * @brief Open new Document, when your writing something on WritePad this will creat new document in same tab, Shortcut is CTRL + N  \n
    */
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void WritePad::open()
{
    /**
    * @brief  open exiting text Document in your PC, Shortcut is CTRL + O  \n
    */
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void WritePad::save()
{
    /**
    * @brief save your current working document where its located, Shortcut is CTRL + S,\n
    *  If we don't have a filename from before, get one. \n
    * error message
    */
    QString fileName;
    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save");
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void WritePad::saveAs()
{
    /**
    * @brief save your working document wherever you want and change file format.
    * error message if error in saving file \n
    */
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void WritePad::copy()
{
    /**
    * @brief Copy text in WritePad, shortcut is CTRL + C  \n
    */
#if QT_CONFIG(clipboard)
    ui->textEdit->copy();
#endif
}

void WritePad::cut()
{
    /**
    * @brief Cut text in WritePad, shortcut is CTRL + X \n
    */
#if QT_CONFIG(clipboard)
    ui->textEdit->cut();
#endif
}

void WritePad::paste()
{
    /**
    * @brief Past text in WritePad, shortcut is CTRL + V \n
    */
#if QT_CONFIG(clipboard)
    ui->textEdit->paste();
#endif
}

void WritePad::undo()
{
    /**
    * @brief undo you writed text or pasted text in WritePad, shortcut is CTRL + U \n
    */
    ui->textEdit->undo();
}

void WritePad::redo()
{
    /**
    * @brief redo you writed text,cutted or erased  text in WritePad \n
    */
    ui->textEdit->redo();
}

void WritePad::selectFont()
{
    /**
    * @brief change your working directry font format,size,style and more \n
    */
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    if (fontSelected) {
        ui->textEdit->setFont(font);
    }
}


void WritePad::readOnly()
{
    /**
    * @brief Make this Writepad as readonly. you can't type if you trigger this function \n
    */
    if(ui->textEdit->isReadOnly()) {
        ui->textEdit->setReadOnly(false);
    } else {
        ui->textEdit->setReadOnly(true);
    }
}



void WritePad::zoomIn()
{
    /**
    * @brief Zoom in Your text in WritePad to Make it big \n
    */
    ui->textEdit->zoomIn(2);
}
void WritePad::zoomOut()
{
    /**
    * @brief Zoom Out Your text in WritePad to Make it Smaller  \n
    */
    ui->textEdit->zoomOut(2);
}

void WritePad::about()
{
    /**
    * @brief About this WritePad \n
    */
    QMessageBox::about(this, tr("About This WritePad"),
                       tr("The <b>WritePad</b> is a simple Application  "
                          "I created using QT & C++ for my QT final Project"));
}

void WritePad::on_textEdit_textChanged()
{
    /**
    * @brief Catch textChanged() action and get it length. and display length in QLCDNumber to show how manay space used so far.
    *  note that this is counting including blank space \n
    */
    int count = ui->textEdit->toPlainText().length();
    ui->lcdCount->display(count);
}

