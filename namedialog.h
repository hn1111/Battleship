#ifndef NAMEDIALOG_H
#define NAMEDIALOG_H

#include <QDialog>

namespace Ui {
class NameDialog;
}

class NameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NameDialog(QWidget *parent = nullptr);
    ~NameDialog();
    QString name() {
        return m_name;
    }

public slots:
    void setName();

private:
    Ui::NameDialog *ui;
    QString m_name;

    void update();
};

#endif // NAMEDIALOG_H
