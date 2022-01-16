#ifndef WRITEPAD_H
#define WRITEPAD_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class WritePad; }
QT_END_NAMESPACE

class WritePad : public QMainWindow
{
    Q_OBJECT

public:
    WritePad(QWidget *parent = nullptr);
    ~WritePad();

//slots for all functions
private slots:

    // new document
    void newDocument();

    //open doc
    void open();

    //save working
    void save();

    //save as new
    void saveAs();

   //copy text
    void copy();

    //cut text
    void cut();

    //past text
    void paste();

    //undo text
    void undo();

    //redo text
    void redo();

    //change font
    void selectFont();


    void about();

    //zoom in text
    void zoomIn();

    //zoom out text
    void zoomOut();

    //make QtextEdit as readonly
    void readOnly();

    //count words
    void on_textEdit_textChanged();

private:
    Ui::WritePad *ui;
    QString currentFile;
};
#endif // WRITEPAD_H
