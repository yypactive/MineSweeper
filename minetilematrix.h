#ifndef MINETILEMATRIX_H
#define MINETILEMATRIX_H

#include <QGraphicsScene>
#include <memory>
#include "minetile.h"
#include "minedatamgr.h"

class MineTileMatrix
{
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

private:
    QGraphicsScene * m_scene;
    std::vector< std::vector<MineTilePtr> > m_mineTileMatrix;
    MineDataMgr m_mineMgr;

};

#endif // MINETILEMATRIX_H
