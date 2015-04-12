#ifndef DATAACCESS_H
#define DATAACCESS_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QImage>
#include <QByteArray>
#include <QBuffer>

struct DISEASE {
    int id;
    QString disease;
    QImage pic;
    QString url;
    QString comment;
};

class DataAccess : public QObject {
    Q_OBJECT
public:
    explicit DataAccess(QObject *parent = 0);
    ~DataAccess();

public:
    static DataAccess* getInstance() {
        if (_instance == (DataAccess*)NULL)
            _instance = new DataAccess();
        return _instance;
    }

    static void kill() {
        if (_instance != (DataAccess*)NULL) {
            delete _instance;
            _instance =  (DataAccess*)NULL;
        }
    }

    enum CONNECTION_STATUS {OK = 1, NOK};
    CONNECTION_STATUS getStatus() {return _status;}

    int pushImage(QImage img);
    QImage fetchImage(int id);

    int pushDisease(DISEASE &d);
    DISEASE fetchDisease(int id);

    int pushUrl(QString url);


private:
    static DataAccess *_instance;
    QSqlDatabase db;
    CONNECTION_STATUS _status;

signals:

public slots:
};

#endif // DATAACCESS_H
