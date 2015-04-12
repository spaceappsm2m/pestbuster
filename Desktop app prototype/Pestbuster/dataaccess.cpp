#include "dataaccess.h"

DataAccess* DataAccess::_instance = NULL;


DataAccess::DataAccess(QObject *parent) : QObject(parent) {
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setUserName("postgres");
    db.setPassword("root");
    db.setPort(5432);
    db.setDatabaseName("pestbuster");

    if (db.open()) {
        _status = OK;
    } else {
        _status = NOK;
        qDebug()<<db.lastError();
    }
}

DataAccess::~DataAccess() {
    db.close();
}

int DataAccess::pushImage(QImage img) {
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QBuffer::WriteOnly);
    img.save(&buffer, "PNG");

    QSqlQuery query;

    query.prepare("INSERT INTO pictures (pic) VALUES (:pic)");
    query.bindValue(":pic", bytes/*QString (bytes.toBase64())*/);
    bool ret = query.exec();
    db.commit();

    if (ret == true) {
        QSqlQuery query("SELECT MAX(id_pic) FROM pictures");
        query.next();
        bool ok;
        int m = query.value(0).toInt(&ok);

        return (ok==true? m:-1);
    }

    return -1;
}

QImage DataAccess::fetchImage(int id) {
    QString rq = QString("SELECT pic FROM pictures WHERE id_pic = %1").arg(id);
    QSqlQuery query(rq);
    if (query.next()) {
        QByteArray array = query.value(0).toByteArray();
        return QImage::fromData(array, "PNG");
    }
    return QImage();
}

int DataAccess::pushDisease(DISEASE &d) {
    int id_url = pushUrl(d.url);
    int id_pic = pushImage(d.pic);

    QSqlQuery query;

    query.prepare("INSERT INTO disease (lbl_disease, id_pic, url, comment) VALUES (:lbl_disease, :id_pic, :url, :comment)");
    query.bindValue(":lbl_disease", d.disease);
    query.bindValue(":id_pic", id_pic);
    query.bindValue(":url", id_url);
    query.bindValue(":comment", d.comment);
    bool ret = query.exec();
    db.commit();

    if (ret == true) {
        QSqlQuery query("SELECT MAX(id_disease) FROM disease");
        query.next();
        bool ok;
        int m = query.value(0).toInt(&ok);

        return (ok==true? m:-1);
    }

    return -1;
}

DISEASE DataAccess::fetchDisease(int id) {
    /*QString rq = QString("SELECT * FROM disease WHERE id_disease = %1").arg(id);
    QSqlQuery query(rq);
    if (query.next()) {
        QByteArray array = query.value(0).toByteArray();
        return QImage::fromData(array, "PNG");
    }
    return QImage();*/
}


int DataAccess::pushUrl(QString url) {
    QSqlQuery query;

    query.prepare("INSERT INTO url (url) VALUES (:url)");
    query.bindValue(":url", url);
    bool ret = query.exec();
    db.commit();

    if (ret == true) {
        QSqlQuery query("SELECT MAX(id_url) FROM url");
        query.next();
        bool ok;
        int m = query.value(0).toInt(&ok);

        return (ok==true? m:-1);
    }

    return -1;
}
