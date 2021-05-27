#ifndef RENDERER_H
#define RENDERER_H
#include <QWidget>
#include <QMutex>
#include <QPainter>
#include "renderthread.h"
#include "viewthread.h"

class RenderThread;
class ViewThread;

class Renderer : public QWidget {
    Q_OBJECT
    protected:
        std::vector<QColor> renderPalette;
        std::vector<double> posPalette;
        std::vector<QColor> colorPalette;
        int maxIterations;
        double zoom;
        double posX;
        double posY;

        void paintEvent(QPaintEvent *event) override;
        void renderLine(QColor *points, int y);
        void insertLine(QColor *points, int arrSize, int y);
        void threadUpdate();

    public:
        enum ColorPalette { Monochromatic, Custom };


        explicit Renderer(QWidget *parent = 0);
        Renderer(const Renderer &thread) = delete;
        Renderer& operator=(const Renderer &thread) = delete;
        ~Renderer();

        void draw();

        void setMaxIterations(int number);
        int getMaxIterations();
        void setZoom(double value);
        void setPosX(double value);
        void setPosY(double value);
        void setColorPalette(ColorPalette palette);
        double getZoom();
        double getPosX();
        double getPosY();




    private:
        bool bufferInitialized;
        QPixmap *pixels;
        int width;
        int height;

        mutable QMutex mutex;
        std::map<int, RenderThread*> threads;
        ViewThread *viewThread;

        void fillPalette(int palleteSize);
        QColor interpolateColor(double position);
        QColor& getColor(int X, int Y);
        void clearBuffer();
        void initBuffer();


    friend RenderThread;
    friend ViewThread;
};

#endif // RENDERER_H
