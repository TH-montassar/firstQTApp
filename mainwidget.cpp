#include <QtWidgets>
#include "mainwidget.h"

// Constructor for main widget
MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    button_ = new QPushButton(tr("Push Me!"));
    textBrowser_ = new QTextBrowser();

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(button_, 0, 0);
    mainLayout->addWidget(textBrowser_, 1, 0);
    setLayout(mainLayout);
    setWindowTitle(tr("Connecting buttons to processes.."));
    // Connect the Buttons "released" signal to MainWidget's onButtonReleased method.
    connect(button_, SIGNAL(released()), this, SLOT(onButtonReleased()));
}

// Destructor
MainWidget::~MainWidget()
{
    delete button_;
    delete textBrowser_;
}

// Handler for button click
void MainWidget::onButtonReleased()
{
    // clear the text in the textBrowser
    textBrowser_->clear();
    textBrowser_->append(tr("Running command:"));

    // Set up our process to write to stdout and run our command
    process_.setCurrentWriteChannel(QProcess::StandardOutput); // Set the write channel
    process_.start("ls -alh $HOME/Desktop");                   // Start the program
}

// This is called whenever the QProcess::readyReadStandardOutput() signal is received
void MainWidget::onCaptureProcessOutput()
{
    // Determine whether the object that sent the signal was a pointer to a process
    QProcess *process = qobject_cast<QProcess *>(sender());
    // If so, append the output to the textbrowser
    if (process)
        textBrowser_->append(process->readAllStandardOutput());
}