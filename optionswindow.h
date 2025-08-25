#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include <QWidget>

namespace Ui {
class OptionsWindow;
}

class OptionsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsWindow(QWidget *parent = nullptr);
    ~OptionsWindow();

private:
    Ui::OptionsWindow *ui;
};

#endif // OPTIONSWINDOW_H
