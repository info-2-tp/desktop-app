#include "obiwanapplication.h"

ObiWanApplication::ObiWanApplication(int argc, char* argv[]):  QGuiApplication (argc, argv) {}

void ObiWanApplication::terminate() {

}

void ObiWanApplication::newJob() {
    Job* job = this->jobPresenter.createJob();
}
