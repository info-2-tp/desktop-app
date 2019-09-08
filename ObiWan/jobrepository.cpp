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

QList<Job> JobRepository::findPriorizedWithState(State state) {
   QSqlQuery query;
   query.exec("select * from job where state = 1 order by priority desc, date asc");
   QList<Job> jobs;
   while (query.next()) {
       Job job = parseQueryResult(query);
       jobs.append(job);
   }
   return jobs;
}

Job JobRepository::parseQueryResult(QSqlQuery query) {
    unsigned long id;
    string name;
    unsigned int height, quantity, remaining_quantity;
    time_t date;
    Measure measure;
    State state;
    Priority priority;

    id = static_cast<unsigned long>(query.value("id").toLongLong());
    name = query.value("name").toString().toStdString();
    height = static_cast<unsigned int>(query.value("height").toInt());
    quantity = static_cast<unsigned int>(query.value("quantity").toInt());
    date = query.value("date").toDateTime().toTime_t();
    measure = Measure(query.value("measure").toInt());
    state = State(query.value("state").toInt());
    priority = Priority(query.value("priority").toInt());
    remaining_quantity = static_cast<unsigned int>(query.value("remaining_quantity").toInt());

    Job job = Job(id, name, height, quantity, date, remaining_quantity, measure, state, priority);
    return job;
}


