#pragma once

#include <QPushButton>

class Button : public QPushButton
{
    Q_OBJECT

public:
    Button(const QString& text, QWidget* parent = nullptr);

signals:
    void digitClicked(int);

private slots:
    void isClicked();
};
