#ifndef OBIWANAPPLICATION_H
#define OBIWANAPPLICATION_H

#include <QGuiApplication>

class ObiWanApplication: public QGuiApplication
{
    Q_OBJECT
public:
    explicit ObiWanApplication(int argc, char* argv[]);
    void terminate();

};

#endif // OBIWANAPPLICATION_H
