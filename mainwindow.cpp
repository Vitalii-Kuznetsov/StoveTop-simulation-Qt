#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->centralGrid);

    ui->Voltage->setInputMask(QString("999"));
    ui->Voltage->setText(QString::number(ui->drawArea->voltage()));
    ui->PenSize->setValue(ui->drawArea->penWidth());

    connect(ui->drawArea, &DrawArea::signalError, this, &MainWindow::errorMessage);
    connect(ui->drawArea, SIGNAL(signalNoErrors()), this, SLOT(errorMessage()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::errorMessage(int errIndex)
{
    if (errIndex == 1){
        ui->statusbar->showMessage("Nothing is drawn, please draw something with left mouse.");
    }
    else {
        ui->statusbar->showMessage("");
    }
}

//______________________________________________DRAW AREA CLASS________________//
DrawArea::DrawArea(QWidget *parent)
    : QWidget(parent){
    timeStep = qMin(static_cast<double>(timerPeriod/1000.), xStep * yStep / 4. / alpha);
    coef = V*V / (xStep*yStep*zStep * density * spHeatCap);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(paintTemperatureMap()));
    connect(timer, SIGNAL(timeout()), this, SLOT(doSimulation()));
    connect(this, SIGNAL(signalDoSimulation()), this, SLOT(doSimulation()));
    connect(this, SIGNAL(signalCreateBurnerMap()), this, SLOT(createBurnerMap()));
    connect(this, SIGNAL(signalCreateTemperatureLayers()), this, SLOT(createTemperatureMapLayers()));
    connect(this, SIGNAL(signalAlphaUpdated()), this, SLOT(updateTimeStep()));
}



/*                                              PUBLIC METHODS                         */
void DrawArea::setPenWidth(int newWidth){
    // the ui does not allow less than 1 newWidth
    myPenWidth = newWidth;
}

void DrawArea::setPenColor(const QColor &newColor){
    myPenColor = newColor;
}

void DrawArea::setNumberOfThreads(int newThreads){
    numberOfThreads = newThreads;
}

void DrawArea::setAlpha(double newAlpha){
    alpha = newAlpha;
    emit signalAlphaUpdated(); // signal to update time step
}

void DrawArea::setVoltage(int newVoltage){
    V = newVoltage;
}

void DrawArea::setBurner(bool status){
    burnerOn = status;
}

void DrawArea::updatePower(){
    if (R == 0) return;     // here Power is converted into heating of 1 sq. pixel in deg C per second by using coef instead of V*V
    power = coef/R;         // multiplication by timestep will be done during calcOtherHeatingSteps,
}

void DrawArea::setSimulation(){
    numberOfBurnerPixels = 0;
    for (int x = 0; x < temperatureMapSizeX; ++x){
        for (int y = 0; y < temperatureMapSizeY; ++y){
            if (burnerMap[x][y]){
                //R += resistivity * xStep / yStep / zStep;
                ++numberOfBurnerPixels;
            }
        }
    }
    R = 1000;/*resistivity / zStep * 1e9 *
            numberOfBurnerPixels / (temperatureMapSizeX * temperatureMapSizeY);*/
    updatePower();
}

void DrawArea::stopSimulation(){
    simulationRunning = false;
    timer->stop();
}

/*void DrawArea::pauseSimulation(){
    if (simulationRunning){
        timer->stop();
        simulationRunning = false;
    }
    else{
        timer->start(timerPeriod);
        simulationRunning = true;
    }
}*/// currently not used

double DrawArea::getQ(int x, int y){
    if (burnerMap[x][y]) {
        return power;
    }
    return 0;
}



/*                                            PUBLIC SLOTS                            */

void DrawArea::updateTimeStep(){
    // time step is calc from simulation parameters,
    // but it can not be less than screen update time step
    timeStep = qMin(static_cast<double>(timerPeriod/1000.), xStep * yStep / 4. / alpha);
}

void DrawArea::clearImage(){
    image.fill(qRgb(255,255,255));
    createBurnerMap();
    createTemperatureMapLayers();
    update();
}

void DrawArea::createBurnerMap(){
    burnerMap.clear();
    burnerMap.squeeze(); /* squeeze is needed for resize option,
                           shoud it ever be implemented */
    for (int i = 0; i < this->width(); ++i){
        // fill the map with falses
        QVector<bool> row(this->height(), false);
        burnerMap.append(row);
    }
    qDebug() << "Burner map created, width: "
             << burnerMap.size() << ", height: " << burnerMap[0].size();
}

void DrawArea::createTemperatureMapLayers(){
    /* fill temperature layers for simulation
     * with outside temperature */
    for (int x = 0; x < temperatureMapSizeX; ++x){
        for (int y = 0; y < temperatureMapSizeY; ++y){
            temperatureMapL0[x][y] = outsideTemperature;
            temperatureMapL1[x][y] = outsideTemperature;
            temperatureMapL2[x][y] = outsideTemperature;
            temperatureMapL3[x][y] = outsideTemperature;
        }
    }
}

void DrawArea::paintBurnerMap(){
    /* this function draws the painted burner map point by point,
     * currently not used */
    image.fill(qRgb(0,0,0));
    update();

    QPainter painter(&image);
    int currentPenWidth = penWidth();
    setPenColor(Qt::red);
    setPenWidth(1);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    for (int i = 0; i < burnerMap.size(); ++i){
        for (int j = 0; j < burnerMap[0].size(); ++j){
            if (burnerMap[i][j]) painter.drawPoint(i,j);
        }
    }
    setPenWidth(currentPenWidth);
    update();
}

void DrawArea::paintTemperatureMap(){
    /* this function draws the current state of the simulation */
    // use current image for painting
    QPainter painter(&image);
    // save the user defined pen width
    int currentPenWidth = penWidth();
    // set our pen width to 1 pixel
    setPenWidth(1);

    for (int x = 0; x < temperatureMapSizeX; ++x){
        for (int y = 0; y < temperatureMapSizeY; ++y){
            /* for each point in the temperature map draw a pixel,
             * the color of which corresponds to the temperature 1 to 1,
             * 0-255 : red, 256-510 : full_red+green, 511-766 : full_red+full_green+blue
             * i.e. colour goes from black at T = 0 to white at T = 766,
             * heaviside function give value > 0 ? value : 0 */
            setPenColor(qRgb
                        (qMin(255., temperatureMapL3[x][y]),
                         qMin(255. , heaviside(temperatureMapL3[x][y] - 255.)),
                         qMin(255. , heaviside(temperatureMapL3[x][y] - 510.))));
            painter.setPen(QPen(myPenColor, myPenWidth));
            painter.drawPoint(x, y);
        }
    }
    // restore user defined pen width
    setPenWidth(currentPenWidth);
    update();

}

void DrawArea::startSimulation()
{
    // if nothing is drawn, emit error, do not start simulation
    if (R <= 0){
        emit signalError(1);
        return;
    }
    emit signalNoErrors();
    image.fill(qRgb(0,0,0));
    update();
    currentSimulationStep = 0;
    // start timer which is connected to doSimulation
    timer->start(timerPeriod);
    simulationRunning = true;
    // start first simulation without waiting for 1st timer timeout
    emit signalDoSimulation();
}

void DrawArea::doSimulation()
{
    // max simulation step is for safety, will be removed in release
    if (currentSimulationStep >= maxSimulationSteps) qDebug() << "Maximum simulation step reached.";
    if (!simulationRunning || currentSimulationStep > maxSimulationSteps) return;

    QElapsedTimer simulationStepTimer;
    simulationStepTimer.start();

    for (int i = 0; i < static_cast<int>(timerPeriod / timeStep / 1000); ++i){
        if (numberOfThreads <= 0) calcHeatingStep();
        else calcHeatingStepParallel(numberOfThreads);

        for (int x = 0; x < temperatureMapSizeX; ++x){
            for(int y = 0; y < temperatureMapSizeY; ++y){
                temperatureMapL2[x][y] = temperatureMapL3[x][y];
            }
        }

        ++currentSimulationStep;
    }
    qDebug() << "The whole simulation instance (" << static_cast<int>(timerPeriod / timeStep / 1000) << " steps) took "
             << simulationStepTimer.elapsed() << "milliseconds. " << "Central point: " << temperatureMapL3[100][100]
             << " Power: " << power << " Time step: " << timeStep << "Alpha: " << alpha << "\n";
}

/*                                             PROTECTED METHODS                                */
void DrawArea::mousePressEvent(QMouseEvent *event){
    // functions untill "addBurnerRegion" are from sample examples, you may skip them
    if (simulationRunning) return;

    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        drawLineTo(event->pos(), true);
        addBurnerRegion(event->pos(), penWidth());
        drawing = true;
        clearing = false;
    }
    if (event->button() == Qt::RightButton) {
        lastPoint = event->pos();
        drawLineTo(event->pos(), false);
        removeBurnerRegion(event->pos(), penWidth());
        clearing = true;
        drawing = false;
    }
}

void DrawArea::mouseMoveEvent(QMouseEvent *event){
    if (simulationRunning) return;

    if ((event->buttons() & Qt::LeftButton) && drawing) {
        drawLineTo(event->pos(), true);
    }
    if ((event->buttons() & Qt::RightButton) && clearing) {
        drawLineTo(event->pos(), false);
    }
}

void DrawArea::mouseReleaseEvent(QMouseEvent *event){
    if (simulationRunning) return;

    if (event->button() == Qt::LeftButton && drawing ) {
        drawLineTo(event->pos(), true);
        drawing = false;
        clearing = false;
    }
    if (event->button() == Qt::RightButton && clearing ) {
        drawLineTo(event->pos(), false);
        drawing = false;
        clearing = false;
    }
}

void DrawArea::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}

void DrawArea::drawLineTo(const QPoint &endPoint, bool drawStatus){
    QPainter painter(&image);
    if (drawStatus) {
        addBurnerRegion(endPoint, penWidth());
        setPenColor(Qt::black);
    }
    else{
        setPenColor(Qt::white);
        removeBurnerRegion(endPoint, penWidth());
    }

    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap));
    if (endPoint == lastPoint){
        painter.drawPoint(lastPoint);
    }
    else{
        painter.drawLine(lastPoint, endPoint);
    }


    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));

    lastPoint = endPoint;
}

void DrawArea::resizeEvent (QResizeEvent *event){
    if (width() > image.width() || height() > image.height()){
        int newWidth = qMax(width(), image.width());
        int newHeight = qMax(height(), image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    if (width() < image.width() || height() < image.height()){
        int newWidth = qMin(width(), image.width());
        int newHeight = qMin(height(), image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
    emit signalCreateBurnerMap();
    emit signalCreateTemperatureLayers();
}

void DrawArea::resizeImage(QImage *image, const QSize &newSize){
    if (image->size() == newSize){
        return;
    }

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255,255,255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0,0), *image);
    *image = newImage;
}



void DrawArea::addBurnerRegion(QPoint pos, int penWidth){
    // do not do anything is the simulation is running
    if (simulationRunning) return;

    /* some specific math to define a circle of diameter penWidth
     * and fill the burnerMap with true within this circle */
    int yMin = qMax(0, pos.y() - int(penWidth/2));
    int yMax = qMin(burnerMap[0].size(), pos.y() + int(penWidth/2));

    for (int y = yMin; y < yMax; ++y ){
        int offset = qSqrt((penWidth/2)*(penWidth/2) - (y - pos.y())*(y - pos.y()));
        int xMin = qMax(0, pos.x() - offset);
        int xMax = qMin(burnerMap.size(), pos.x() + offset);

        for (int x = xMin; x < xMax; ++x){
            burnerMap[x][y] = true;
        }
    }
}

void DrawArea::removeBurnerRegion(QPoint pos, int penWidth){
    // same as addBurnerRegion, but remove (false instead of true)
    if (simulationRunning) return;

    int yMin = qMax(0, pos.y() - int(penWidth/2));
    int yMax = qMin(burnerMap[0].size(), pos.y() + int(penWidth/2));

    for (int y = yMin; y < yMax; ++y ){
        int offset = qSqrt((penWidth/2)*(penWidth/2) - (y - pos.y())*(y - pos.y()));
        int xMin = qMax(0, pos.x() - offset);
        int xMax = qMin(burnerMap.size(), pos.x() + offset);

        for (int x = xMin; x < xMax; ++x){
            burnerMap[x][y] = false;
        }
    }
}

void DrawArea::calcHeatingStep()
{
    // we are not calculating at border points, constant boundary condition works there

    /* first we calculate the current temperature of the burner,
     * calculation only at the point where burner is drawn.
     * Approximation - burner cools down at the same rate as it
     * heats up. If burner is on, we heat, if off, we cool untill outside temp */
    for (int x = 0; x < temperatureMapSizeX; ++x){
        for (int y = 0; y < temperatureMapSizeY; ++y){
            if (burnerMap[x][y]){
                if (burnerOn) {
                    temperatureMapL0[x][y] += timeStep * getQ(x,y); }
                else {
                    temperatureMapL0[x][y] = qMax(static_cast<double>(outsideTemperature),
                                                  temperatureMapL0[x][y] - timeStep * getQ(x,y)); }
            }
        }
    }

    /* simple solution of a differential equation, explicit type.
     * for z it is outside temperature from the top
     * and burner (temperatureMap0) from the bottom */
    for (int x = 1; x < temperatureMapSizeX-1; ++x){
        for (int y = 1; y < temperatureMapSizeY-1; ++y){
            temperatureMapL3[x][y] = temperatureMapL2[x][y] + alpha*timeStep * (
                        (temperatureMapL2[x+1][y] - 2*temperatureMapL2[x][y] + temperatureMapL2[x-1][y])/xStep/xStep +   // x
                        (temperatureMapL2[x][y+1] - 2*temperatureMapL2[x][y] + temperatureMapL2[x][y-1])/yStep/yStep +   // y
                        (outsideTemperature - 2*temperatureMapL2[x][y] + temperatureMapL0[x][y])/zStep/zStep );          // z
        }
    }
}

void DrawArea::calcHeatingStepParallel(int numberOfThreads)
{
    // we are not calculating at border points, constant boundary condition works there

    int batch = (temperatureMapSizeX-2) / numberOfThreads;

    for (int i = 0; i < numberOfThreads; ++i){
        QFuture<void> future = QtConcurrent::run(&DrawArea::calcHeatingStepPartial, this, i*batch+1, (i+1)*batch+1);
    }

}

void DrawArea::calcHeatingStepPartial(int xMin, int xMax)
{
    // we are not calculating at border points, constant boundary condition works there
    // although for burner is would be better to calculate

    /* first we calculate the current temperature of the burner,
     * calculation only at the point where burner is drawn.
     * Approximation - burner cools down at the same rate as it
     * heats up. If burner is on, we heat, if off, we cool untill outside temp */
    for (int x = xMin; x < xMax; ++x){
        for (int y = 1; y < temperatureMapSizeY-1; ++y){
            if (burnerMap[x][y]){
                if (burnerOn) {
                    temperatureMapL0[x][y] += timeStep * getQ(x,y); }
                else {
                    temperatureMapL0[x][y] = qMax(static_cast<double>(outsideTemperature),
                                                  temperatureMapL0[x][y] - timeStep * getQ(x,y)); }
            }
        }
    }

    /* simple solution of a differential equation, explicit type.
     * for z it is outside temperature from the top
     * and burner (temperatureMap0) from the bottom */
    for (int x = xMin; x < xMax; ++x){
        for (int y = 1; y < temperatureMapSizeY-1; ++y){
            temperatureMapL3[x][y] = temperatureMapL2[x][y] + alpha*timeStep * (
                        (temperatureMapL2[x+1][y] - 2*temperatureMapL2[x][y] + temperatureMapL2[x-1][y])/xStep/xStep +   // x
                        (temperatureMapL2[x][y+1] - 2*temperatureMapL2[x][y] + temperatureMapL2[x][y-1])/yStep/yStep +   // y
                        (outsideTemperature - 2*temperatureMapL2[x][y] + temperatureMapL0[x][y])/zStep/zStep );          // z
        }
    }
}

//______________________________________________Main Window________________//

void MainWindow::on_actionNew_triggered()
{
    using namespace std::this_thread;
    using namespace std::chrono;
    using namespace std::chrono_literals;

    ui->drawArea->stopSimulation();
    sleep_for(1000ms);
    ui->drawArea->clearImage();
}


void MainWindow::on_PenSize_valueChanged(int value)
{
    ui->drawArea->setPenWidth(value);
    ui->labelSetPenSize->setText(QString("Pen size: ") + QString::number(value));
}


void MainWindow::on_Voltage_textEdited(const QString &arg1)
{
    int voltage = arg1.toInt();
    ui->drawArea->setVoltage(voltage);
    if (voltage > 300){
        ui->Voltage->setText(QString("300"));
    }
}


void MainWindow::on_startSimulation_released()
{
    ui->drawArea->setSimulation();
    ui->drawArea->startSimulation();
}


void MainWindow::on_stopSimulation_released()
{
    ui->drawArea->stopSimulation();
}


/*void MainWindow::on_pauseSimulation_released()
{
    ui->drawArea->pauseSimulation();
}*/


void MainWindow::on_actionExit_triggered()
{
    using namespace std::this_thread;
    using namespace std::chrono;
    using namespace std::chrono_literals;

    ui->drawArea->stopSimulation();
    sleep_for(1000ms);
    this->close();
}


void MainWindow::on_threadsNumber_valueChanged(int arg1)
{
    ui->drawArea->setNumberOfThreads(arg1);
}


void MainWindow::on_topSilver_released()
{
    ui->drawArea->setAlpha(165.6);
    ui->labelTopMaterial->setText(QString("Stove top material: Silver"));
}


void MainWindow::on_topCopper_released()
{
    ui->drawArea->setAlpha(111.);
    ui->labelTopMaterial->setText(QString("Stove top material: Copper"));
}


void MainWindow::on_topIron_released()
{
    ui->drawArea->setAlpha(23.);
    ui->labelTopMaterial->setText(QString("Stove top material: Iron"));
}


void MainWindow::on_topQuartz_released()
{
    ui->drawArea->setAlpha(1.4);
    ui->labelTopMaterial->setText(QString("Stove top material: Quartz"));
}


void MainWindow::on_topBrick_released()
{
    ui->drawArea->setAlpha(0.52);
    ui->labelTopMaterial->setText(QString("Stove top material: Brick"));
}


void MainWindow::on_topGlass_released()
{
    ui->drawArea->setAlpha(0.34);
    ui->labelTopMaterial->setText(QString("Stove top material: Glass"));
}


void MainWindow::on_HeaterOn_toggled(bool checked)
{
    if (checked) ui->drawArea->setBurner(true);
    else ui->drawArea->setBurner(false);

}

