#ifndef MINETILEMATRIX_H
#define MINETILEMATRIX_H

#include <QGraphicsScene>
#include <memory>
#include "minetile.h"

class MineTileMatrix
{
public:
    MineTileMatrix(QGraphicsScene * _scene);

    void init(unsigned _row, unsigned _col, unsigned _amount);
    void clear();

public:
    static const unsigned ms_row = 10;
    static const unsigned ms_col = 10;
    static const unsigned ms_amount = 10;
    using MineTilePtr = MineTile *;

private:
    QGraphicsScene * m_scene;
    std::vector< std::vector<MineTilePtr> > m_mineTileMatrix;

};

#endif // MINETILEMATRIX_H
