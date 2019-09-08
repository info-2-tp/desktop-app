#include "jobrepository.h"

#include <iostream>
JobRepository::JobRepository(){}

Job JobRepository::save(Job job) {
    QSqlQuery query;
    bool ok;
    query.exec("select id from job order by id desc limit 1");
    query.next();
    unsigned long last_id = query.value(ID).toULongLong(&ok);
    Job toSaveJob(NEW_ID(last_id), job.getName(), job.getHeight(), job.getQuantity(), job.getDate(), job.getMeasure(), job.getState(),
                job.getPriority());
    if (insert(toSaveJob)) {
        return toSaveJob;
    }

    return job;
}

bool JobRepository::insert(Job job) {
    QSqlQuery query;
    unsigned long long id = (unsigned long long) job.getId();
    query.prepare("insert into job values(:id, :name, :height, :measure, :quantity, :state, :remaining_quantity, :date, :priority)");
    query.bindValue(":id", QVariant(id));
    query.bindValue(":name", QVariant(QString::fromStdString(job.getName())));
    query.bindValue(":height", QVariant(job.getHeight()));
    query.bindValue(":measure", QVariant(job.getMeasure()));
    query.bindValue(":quantity", QVariant(job.getQuantity()));
    query.bindValue(":state", QVariant(job.getState()));
    query.bindValue(":remaining_quantity", QVariant(job.getRemaining_quantity()));
    query.bindValue(":date", QVariant(QDateTime::fromTime_t(job.getDate())));
    query.bindValue(":priority", QVariant(job.getPriority()));
    return query.exec();
}
