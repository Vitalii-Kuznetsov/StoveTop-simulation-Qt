#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Qt main libs
#include <QWidget>
#include <QDebug>

// Qt objects
#include <QLabel>

// Qt libs for painting
#include <QPainter>
#include <QPen>
#include <QMouseEvent>

// Qt data structures
#include <QString>
#include <QVector>
#include <QHash>
#include <QQueue>

// Qt timer
#include <QTime>
#include <QTimer>
#include <QElapsedTimer>

// Qt multithreading
#include <QtConcurrent>

// C++ chrono libs
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
    void errorMessage(int errIndex);

private slots:
    void on_actionNew_triggered();

    //void on_Voltage_textEdited(const QString &arg1);

    void on_PenSize_valueChanged(int value);

    void on_startSimulation_released();

    void on_stopSimulation_released();

    // void on_pauseSimulation_released();

    void on_actionExit_triggered();

    void on_threadsNumber_valueChanged(int arg1);

    void on_topSilver_released();

    void on_topCopper_released();

    void on_topIron_released();

    void on_topQuartz_released();

    void on_topBrick_released();

    void on_topGlass_released();

    void on_HeaterOn_toggled(bool checked);

    void on_powerDial_valueChanged(int value);

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

    void setWatts(int);

    void setBurner(bool);

    void updatePower();

    void setSimulation();

    void stopSimulation();

    void pauseSimulation();

    double getDeltaT(int x, int y);

    int penWidth() { return myPenWidth; }

    int getWatts() { return W; }

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

    void signalAlphaUpdated();

    void signalError(int errIndex);

    void signalNoErrors(int errIndex);

protected:
    void paintEvent(QPaintEvent *) override;

    void resizeEvent(QResizeEvent *) override;

    void mousePressEvent(QMouseEvent *) override;

    void mouseReleaseEvent(QMouseEvent *) override;

    void mouseMoveEvent(QMouseEvent *) override;

    void addBurnerRegion(QPoint pos, int penWidth);

    void removeBurnerRegion(QPoint pos, int penWidth);

    void calcHeatingStep();

    void calcHeatingStepParallel(int numberOfThreads);

    void calcHeatingStepPartial(QPromise<void> &promise, int xMin, int xMax);


private:
    void drawLineTo(const QPoint &endPoint, bool drawStatus);

    void resizeImage(QImage *image, const QSize &newSize);

    // status bools
    bool drawing = false;
    bool clearing = false;
    bool simulationRunning = false;
    bool multithreadRunning = false;
    bool burnerOn = false;

    int myPenWidth = 50; // starting defalut pen width
    QColor myPenColor = Qt::black;       // and colour
    QImage image;
    QPoint lastPoint;
    QTimer *timer;

    // bool map of where the burner was drawn
    QVector<QVector<bool>> burnerMap;

    // setting temperature maps of the burner and stove top
    static const int temperatureMapSizeX = 202;  // 202*202 - Fixed size of simulation window/widget (drawArea)
    static const int temperatureMapSizeY = 202;  // 2 extra points in each dimention are used as boundary, so main calc area is 200*200
    double temperatureMapL0 [temperatureMapSizeX][temperatureMapSizeY];  // Burner map, under main stove top
    double temperatureMapL1 [temperatureMapSizeX][temperatureMapSizeY];  // Initial stove temperature map
    double temperatureMapL2 [temperatureMapSizeX][temperatureMapSizeY];  // Previous state stove temp map
    double temperatureMapL3 [temperatureMapSizeX][temperatureMapSizeY];  // Current state stove temp map

    // simulation parameters
    const int maxSimulationSteps = 1000000;     // For safety, execution will stop after this step is reached
    int currentSimulationStep = 0;
    int numberOfThreads = 1;

    // physical constants
    const double outsideTemperature = 20.;

    const double density = 8.96e-3;             // Cu, density in g/mm^3 // rho in literature
    const double volHeatCapCu = 3.45e-3;       // Cu, specific heat capacity in J/mm^3/deg C // c in literature
    const double resistivity = 1.68e-5;       // Cu, resistivity in Ohm*mm // again rho in literature
    const double thermalResCoef = 3.86e-3;   // Cu, thermal sensitivity of resistivity, in a.u./deg C // again alpha in literature
    const int maxHeaterTemp = 800;          // max temperature set for Cu heater, it will be not able to heat further

    // simulation constants
    const double xStep = 0.26;           // 1 px = 0.26 mm // value for my monitor
    const double yStep = 0.26;          // one pixel - one small block of burner
    const double zStep = 2.;           // thickness of the stove top (glass or other)
                                      // consider there is burner at 0-zStep and air at 0+zStep
    const double burnerSizeZ = 1.;   // burner Z size
                                    // these values are used for calculation of the size of the burner,
                                   // stove top, as well as x, y and z simulation steps
    const int timerPeriod = 100;  // How often to show the current simulation state, each timerPeriod the update will run, in ms

    // simulation variables
    double alpha = 5.;               // Thermal diffusivity in mm^2/s, denepds on stove top material, which can be changed
    double timeStep = 0.002;        // xStep*yStep / 4 / alpha, in seconds; updated when the widget is created and when alpha is changed
    int W = 5000;                  // Total power supplied, Wh; user will be able to change it
    double power = 0;             // power = f(W), shows the temperature increase of the burner based on W
    int numberOfBurnerPixels = 0;// number of pixels coloured as a burner



    // currently unused parts
    /* Dict of volumetric heat capacities for materials, J / mm^3 / K
    const QHash<QString, int> volHeatCap{
        {"Copper", 3.45e-3},
        {"Silver", 2.44e-3},
        {"Iron", 3.547e-3},
        {"Quartz", 0.741e-3*2.65},
        {"Brick", 0.840e-3*2},
        {"Glass", 2.1e-3}
    };*/
};



#endif // MAINWINDOW_H
