#ifndef MYCHARTS_H
#define MYCHARTS_H
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QProgressBar>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QTimer>
#include<QRandomGenerator>
#include <QtCharts>
#include <QDateTimeAxis>
#include <QValueAxis>
class mycharts : public QWidget {
    Q_OBJECT

public:
    explicit mycharts(QWidget *parent = nullptr) : QWidget(parent) {
        setupUI();
        setupStyles();
        setupMockData();
    }

protected:
    void setupUI();
    void setupStyles();
    void setupMockData();
    void animateUI();
    QGroupBox* createGroupBox(const QString &title, int minWidth = 0, int minHeight = 0);
    QWidget* createStatCard(const QString &title, const QString &value, const QString &unit);

};
#endif // MYCHARTS_H
