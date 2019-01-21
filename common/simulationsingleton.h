#ifndef SIMULATIONSINGLETON_H
#define SIMULATIONSINGLETON_H

#include <QObject>
#include <QMutex>

class SimulationSingleton : public QObject
{
    Q_OBJECT
public:
    static SimulationSingleton* getInstance();
    static void drop();
    bool isRun() const;

public slots:
    void simulationRun();
    void SimulationStop();
    void SimulationError(const QString& simError);

signals:
    void startSimulation();
    void stopSimulation();
    void error(const QString& e);


private:
    SimulationSingleton(const SimulationSingleton&) = delete;
    SimulationSingleton& operator =(const SimulationSingleton&) = delete;
    SimulationSingleton(QObject *parent = 0);
    ~SimulationSingleton(){}

     static SimulationSingleton* m_instance;
     static QMutex m_mutex;
     bool m_isRun{false};
};

#endif // SIMULATIONSINGLETON_H
