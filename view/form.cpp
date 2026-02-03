#include "form.h"
#include "ui_form.h"
#include <QPalette>
#include <QColor>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

}

Form::~Form()
{
    delete ui;
}
void Form::paintEvent(QPaintEvent *) {

    QPainter painter(this);
    painter.drawPixmap(5, 5, m_pixmap);
    //painter.drawRoundedRect(5,5,width()+5, height()+5,3,3);
}

void Form::resizeEvent(QResizeEvent *) {
    auto newRect = m_pixmap.rect().united(rect());
    if (newRect != m_pixmap.rect()){
        QPixmap newPixmap{newRect.size()};
        QPainter painter{&newPixmap};
        painter.fillRect(newPixmap.rect(), QColor(188, 190, 251));
        painter.drawPixmap(5, 5, m_pixmap);
        m_pixmap = newPixmap;
    }

}

void Form::mousePressEvent(QMouseEvent *ev) {
    if (ev->button() == Qt::RightButton) {
        clearWindow();
    } else {
        m_lastPos = ev->pos();
        draw(ev->pos());
    }
}

void Form::mouseMoveEvent(QMouseEvent *ev) {
    if (ev->buttons() & Qt::LeftButton)
        draw(ev->pos());
}

void Form::clearWindow() {
    QPainter painter{&m_pixmap};
    painter.eraseRect(this->rect());
    update();
    //auto newRect = m_pixmap.rect().united(rect());
        //QPixmap newPixmap{rect().size()};
    painter.fillRect(m_pixmap.rect(), QColor(188, 190, 251));
    painter.drawPixmap(5, 5, m_pixmap);
        //m_pixmap = newPixmap;
}

void Form::draw(const QPoint &pos) {
    QPainter painter{&m_pixmap};
    //painter.setRenderHint(QPainter::Antialiasing);
    QPen pen;
    pen.setWidth(20.0);
    pen.setColor(Qt::black);
    pen.setCapStyle(Qt::FlatCap);
    pen.joinStyle();
    painter.setPen(pen);
    painter.drawEllipse(m_lastPos, 5, 5);

    m_lastPos = pos;
    update();
    SavePixels();
}

void Form::SavePixels() {
    QImage img;
    img = m_pixmap.toImage();
    img = img.scaled(28, 28);
    img = img.transformed(QTransform().rotate(-90));

    QPixmap pxDst(img.size());  // blurred destination
    pxDst.fill(Qt::transparent);
    {
        QPainter painter(&pxDst);
        qt_blurImage(&painter, img, 4, true, false);
    }

    Pixels_draw.push_back(-1);
    for (int i = pxDst.toImage().size().width() - 1; i >= 0; i--) {
        for (int j = 0; j < pxDst.toImage().size().height(); j++) {
            Pixels_draw.push_back(pxDst.toImage().pixelColor(j, i).black());
        }
    }

}
