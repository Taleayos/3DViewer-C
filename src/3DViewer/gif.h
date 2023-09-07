#ifndef GIF_H
#define GIF_H

#include <QWidget>
#include <QMovie>

namespace Ui {
class GIF;
}

class GIF: public QWidget {
    Q_OBJECT

public:
    explicit GIF( QWidget* parent = 0 );
    ~GIF();

private:
    Ui::GIF* ui;

    QMovie m_movie;
};

#endif // GIF_H
