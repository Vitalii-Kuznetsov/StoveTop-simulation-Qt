#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPainter>
#include <QPen>
#include <QDebug>
#include <QMouseEvent>
#include <QWidget>
#include <QString>
#include <QLabel>
#include <QPen>
#include <QTime>
#include <QVector>
#include <QTimer>
#include <QElapsedTimer>
#include <QtConcurrent>
#include <chrono>
#include <thread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//_____________________________________________Main Window______________//
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void errorMessage();

private slots:
    void on_actionNew_triggered();

    void on_Voltage_textEdited(const QString &arg1);

    void on_PenSize_valueChanged(int value);

    void on_startSimulation_released();

    void on_stopSimulation_released();

    void on_pauseSimulation_released();

    void on_actionExit_triggered();

    void on_threadsNumber_valueChanged(int arg1);

    void on_topSilver_released();

    void on_topCopper_released();

    void on_topIron_released();

    void on_topQuartz_released();

    void on_topBrick_released();

    void on_topGlass_released();

private:
    Ui::MainWindow *ui;
};

//______________________________________________Draw Area________________//
class DrawArea : public QWidget{
    Q_OBJECT

public:
    DrawArea(QWidget *parent = nullptr);

    void setPenWidth(int);

    void setPenColor(const QColor &newColor);

    void setNumberOfThreads(int);

    void setAlpha(double);

    void setVoltage(int);

    void updatePower();

    void setSimulation();

    void stopSimulation();

    void pauseSimulation();

    double getQ(int x, int y);

    int penWidth() { return myPenWidth; }

    int voltage() { return V; }

    double getR() { return R; }

    template <typename T>
    T heaviside(T number){ return (number >= 0 ? number : 0 ); }



public slots:
    void updateTimeStep();

    void clearImage();

    void createBurnerMap();

    void paintBurnerMap();

    void createTemperatureMapLayers();

    void paintTemperatureMap();

    void startSimulation();

    void doSimulation();

signals:
    void signalCreateBurnerMap();

    void signalCreateTemperatureLayers();

    void signalDoSimulation();

    void signalUpdateAlpha();

    void signalErrorNothingDrawn();

    void signalNoErrors();

protected:
    void paintEvent(QPaintEvent *) override;

    void resizeEvent(QResizeEvent *) override;

    void mousePressEvent(QMouseEvent *) override;

    void mouseReleaseEvent(QMouseEvent *) override;

    void mouseMoveEvent(QMouseEvent *) override;

    void addBurnerRegion(QPoint pos, int penWidth);

    void removeBurnerRegion(QPoint pos, int penWidth);

    void calcFirstHeatingStep();

    void calcOtherHeatingSteps();

    void calcOtherHeatingStepsParallel(int numberOfThreads);

    void calcOtherHeatingStepsPartial(int xMin, int xMax);


private:
    void drawLineTo(const QPoint &endPoint, bool drawStatus);

    void resizeImage(QImage *image, const QSize &newSize);

    bool drawing = false;
    bool clearing = false;
    bool simulationRunning = false;
    int myPenWidth = 50;
    QColor myPenColor = Qt::black;
    QImage image;
    QPoint lastPoint;
    QTimer *timer;
    QVector<QVector<bool>> burnerMap;

    static const int temperatureMapSizeX = 202;  // 202*202 - Fixed size of simulation window/widget (drawArea)
    static const int temperatureMapSizeY = 202;  // 2 extra points in each dimention are used as boundary, so main calc area is 200*200
    double temperatureMapL0 [temperatureMapSizeX][temperatureMapSizeY];  // Burner map, under main stove top
    double temperatureMapL1 [temperatureMapSizeX][temperatureMapSizeY];  // Initial stove temperature map
    double temperatureMapL2 [temperatureMapSizeX][temperatureMapSizeY];  // Previous state stove temp map
    double temperatureMapL3 [temperatureMapSizeX][temperatureMapSizeY];  // Current state stove temp map

    const int maxSimulationSteps = 1000000;     // For safety, execution will stop after this step is reached
    int currentSimulationStep = 0;
    int numberOfThreads = 4;

    const int outsideTemperature = 20;
    double alpha = 5.;                            // Thermal diffusivity in mm^2/s // alpha in literature
    const int timerPeriod = 100;                 // How often to show the current simulation state, each timerPeriod ms //
    const double density = 8.96e-3;             // Cu, density in g/mm^3 // rho in literature
    const double spHeatCap = 0.385;            // Cu, specific heat capacity in J/g/deg C // c in literature
    const double resistivity = 1.68e-5;       // Cu, resistivity in Ohm*mm // again rho in literature
    const double thermalResCoef = 3.86e-3;   // Cu, thermal sensitivity of resistivity, in a.u./deg C // again alpha in literature

    const double xStep = 5.;               // 1 px = 0.26 mm // not sure if it is the same on every monitor
    const double yStep = 5.;              // 200 pixels simulation area -> 1000mm -> 1m
    const double zStep = 5.;             // Burner Z size

    int V = 120;                       // Voltage, V // user will be able to change it
    double R = 0;                     // R = rho * length / cut // will be set during burner drawing
    double coef = 1;                 // V*V/xStep/yStep/zStep/density/spHeatCap // need for faster power calculation
    double power = 0;               // will be calculated based on the burner drawn
    int numberOfBurnerPixels = 0;  // number of pixels, coloured as a burner

    double timeStep = 0.002;     // xStep*yStep / 4 / alpha // in seconds // updated when the widget is created
};



#endif // MAINWINDOW_H
