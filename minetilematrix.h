#ifndef MINETILEMATRIX_H
#define MINETILEMATRIX_H

#include <QGraphicsScene>
#include <memory>
#include "minetile.h"
#include "minedatamgr.h"

class MineTileMatrix : public QObject
{
    Q_OBJECT
public:
    static const unsigned ms_row = 10;
    static const unsigned ms_col = 10;
    static const unsigned ms_amount = 10;
    static const qreal ms_space;
    using MineTilePtr = std::unique_ptr<MineTile>;

public:
    MineTileMatrix(QGraphicsScene * _scene);

    void init(unsigned _row, unsigned _col, unsigned _amount);
    void clear();
    void addToScene();
    qreal getWidth();
    qreal getHeight();

signals:
    void startStopWatch();
    void sendSucc();
    void sendFail();
    void setFlagCount(unsigned);

public slots:
    void onTileClickedHandle(QPoint _cp, bool _isShift);
    void CountFlag();

private:
    void initConnect();
    std::vector<QPoint> getNeighborVec(QPoint _p);
    unsigned getNeighborFlag(QPoint _p);
    unsigned getNeighborQuest(QPoint _p);
    unsigned countCovered();
    void success();
    void failure();
    void checkMine();

private:
    QGraphicsScene * m_scene;
    std::vector< std::vector<MineTilePtr> > m_mineTileMatrix;
    MineDataMgr m_mineMgr;
    qreal m_width;
    qreal m_height;
    bool m_firstStep;
    unsigned m_mineAmount;

};

#endif // MINETILEMATRIX_H
