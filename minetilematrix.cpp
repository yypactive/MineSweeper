#include "minetilematrix.h"

MineTileMatrix::MineTileMatrix(QGraphicsScene * _scene)
    : m_scene(_scene),
      m_mineTileMatrix(0)
{

}

void MineTileMatrix::init(unsigned _row, unsigned _col, unsigned _amount)
{
    clear();
/*    m_mineTileMatrix = std::move(
                std::vector< std::vector<MineTilePtr> >(
                    _row, std::vector<> ()
                    )
                );*/

}

void MineTileMatrix::clear()
{
    m_mineTileMatrix.clear();
}
