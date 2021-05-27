#include "renderer.h"
#include <QPainter>
#include <QPainterPath>
#include <math.h>
#include <complex>
#include <vector>
#include <math.h>


Renderer::Renderer(QWidget *parent) : QWidget(parent), maxIterations(100), zoom(1), posX(0), posY(0), bufferInitialized(false), width(0), height(0)  {
    QPalette p = palette();
    p.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(p);
}

Renderer::~Renderer() {
    clearBuffer();
}

void Renderer::draw() {
    clearBuffer();
    initBuffer();

    viewThread = new ViewThread(this);
    viewThread->setThreadsRemaining(height);
    viewThread->start();

    for(int i = 0; i < height; i++) {
        threads[i]->setY(i);
        threads[i]->start();
    }

    viewThread->wait();
    delete viewThread;
    repaint();

    threads.clear();
}

void Renderer::threadUpdate() {
    repaint();

    for(int i = 0; i < height; i++) {
        if(threads[i] != nullptr) {
            if(threads[i]->isFinished()) {
                delete threads[i];
                threads[i] = nullptr;
                viewThread->setThreadsRemaining(viewThread->getThreadsRemaining() - 1);
            }
        }
    }
}

void Renderer::paintEvent(QPaintEvent *event) {
    if(bufferInitialized) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.drawPixmap(0, 0, width, height, *pixels);
    }
}

void Renderer::insertLine(QColor *points, int arrSize, int y) {
    mutex.lock();
    QPainter *painter  = new QPainter(pixels);
    QPen pen;
    for(int i = 0; i < arrSize; i++) {
        pen.setColor(points[i]);
        QPoint point(i, y);
        painter->setPen(pen);
        painter->drawPoint(point);
    }
    delete painter;
    mutex.unlock();
}

void Renderer::fillPalette(int palleteSize) {
    colorPalette.clear();
    for(int i = 0; i < palleteSize; i++)
        colorPalette.push_back(interpolateColor(double(i) / double(palleteSize-1)));
}

QColor Renderer::interpolateColor(double position) {
    int red = 0, green = 0, blue = 0;

    for(unsigned int i = 0; i < renderPalette.size(); i++) {
        if(position >= posPalette[i] && position <= posPalette[i+1]) {
            unsigned int next = i+1;
            if(next > posPalette.size())
                next = 0;

            double length = posPalette[i+1]-posPalette[i];
            double pos = position-posPalette[i];
            double ratio = pos/length;
            red = (int)(ratio*renderPalette[i].red() + (1-ratio)*renderPalette[next].red());
            green = (int)(ratio*renderPalette[i].green() + (1-ratio)*renderPalette[next].green());
            blue = (int)(ratio*renderPalette[i].blue() + (1-ratio)*renderPalette[next].blue());
            break;
        }
    }


    return QColor((int)red, (int)green, int(blue));
}

void Renderer::renderLine(QColor *points, int y) {
    for(int x = 0; x < width; x++)
        points[x] = getColor(x, y);
}

QColor& Renderer::getColor(int X, int Y) {
    double RE_START = -2 * zoom;
    double RE_END = 1 * zoom;
    double IM_START = -1 * zoom;
    double IM_END = 1 * zoom;
    std::complex<double> point(RE_START + posX + (double(X) / width)  * (RE_END - RE_START), IM_START  + posY + (double(Y) / height) * (IM_END - IM_START));
    std::complex<double> Z(0, 0);

    int i = 0;
    while(abs(Z) < 4 && i < maxIterations)
        Z = Z * Z + point, i++;


    return colorPalette[round(double(i)/double(maxIterations) * (colorPalette.size()-1))];
}

void Renderer::clearBuffer() {
    if(bufferInitialized) {
        delete pixels;
        threads.clear();
    }
}

void Renderer::initBuffer() {
    this->width = QWidget::width();
    this->height = QWidget::height();

    pixels = new QPixmap(width, height);

    for(int i = 0; i < height; i++) {
        threads.insert({i, new RenderThread(this, width)});
    }

    bufferInitialized = true;
}

void Renderer::setColorPalette(ColorPalette palette) {
    renderPalette.clear();
    posPalette.clear();

    if(palette == Monochromatic) {
        renderPalette.push_back(QColor(255, 255, 255));
        renderPalette.push_back(QColor(0, 0, 0));
        posPalette.push_back(0);
        posPalette.push_back(1);
    } else if(palette == Custom) {
        renderPalette.push_back(QColor(0, 7, 100));
        renderPalette.push_back(QColor(32, 107, 203));
        renderPalette.push_back(QColor(237, 255, 255));
        renderPalette.push_back(QColor(255, 170, 0));
        renderPalette.push_back(QColor(0, 2, 0));
        posPalette.push_back(0);
        posPalette.push_back(0.16);
        posPalette.push_back(0.42);
        posPalette.push_back(0.6425);
        posPalette.push_back(0.85);
        posPalette.push_back(1);
    }

    fillPalette(256);
}

void Renderer::setMaxIterations(int number) {
    this->maxIterations = number;
}

int Renderer::getMaxIterations() {
    return maxIterations;
}

void Renderer::setZoom(double value) {
    this->zoom = value;
}

void Renderer::setPosX(double value) {
    this->posX = value;
}

void Renderer::setPosY(double value) {
    this->posY = value;
}

double Renderer::getZoom() {
    return zoom;
}

double Renderer::getPosX() {
    return posX;
}

double Renderer::getPosY() {
    return posY;
}
