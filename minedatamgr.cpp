#include "minedatamgr.h"
#include <algorithm>
#include <random>
#include <chrono>

MineDataMgr::MineDataMgr()
    : m_row(0), m_col(0), m_amount(0),
      m_valVec(0), m_matrix(0)
{

}

void MineDataMgr::init(unsigned _row, unsigned _col, unsigned _amount)
{
    m_row = _row;
    m_col = _col;
    m_amount = _amount;
    m_matrix = std::move(
                std::vector <std::vector <MineDataPtr> >(
                    _row, std::vector<MineDataPtr>(_col)
                    ));
    for (unsigned i = 0; i < _row; ++i)
    {
        for (unsigned j = 0; j < _col; ++j)
        {
            m_matrix[i][j] = std::make_shared<MineData>();
            m_matrix[i][j]->setY(i);
            m_matrix[i][j]->setX(j);
        }
    }
    initMine();
}

void MineDataMgr::initMine()
{
    m_valVec.clear();
    if (m_amount > 0)
    {
        unsigned sum = m_row * m_col - 1;
        m_valVec = std::move(std::vector <bool> (sum, false));
        for (unsigned i = 0; i < sum; ++i)
        {
            m_valVec[i] = i < m_amount ? true : false;
        }
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(m_valVec.begin (), m_valVec.end (), std::default_random_engine (seed));
    }
}

void MineDataMgr::assignMine(unsigned _sy, unsigned _sx)
{
    for (unsigned i = 0; i < m_valVec.size(); ++i)
    {
        unsigned ny = i < _sy * m_col + _sx ? i / m_col: (i + 1) / m_col;
        unsigned nx = i < _sy * m_col + _sx ? i % m_col: (i + 1) % m_col;
        m_matrix[ny][nx]->setMine(m_valVec[i]);
    }    
}

void MineDataMgr::calVal()
{
    for (unsigned i = 0; i < m_row; ++i)
    {
        for (unsigned j = 0; j < m_col; ++j)
        {
            PointVec neighborVec = std::move(getNeighborVec(i, j));
            unsigned val = 0;
            std::for_each(neighborVec.begin(), neighborVec.end(),
                          [&](std::pair<unsigned, unsigned> _point)
            {
                if (m_matrix[_point.first][_point.second]->getMine())
                    val ++;
            }
            );
            m_matrix[i][j]->setVal(val + '0');
        }
    }
}

void MineDataMgr::clear()
{
    m_valVec.clear();
    m_matrix.clear();
}

std::shared_ptr<MineData> MineDataMgr::getMineData(unsigned _row, unsigned _col)
{
    return m_matrix[_row][_col];
}

MineDataMgr::PointVec MineDataMgr::getNeighborVec(unsigned _y, unsigned _x)
{
    PointVec pvec;
    for (int i = -1; i < 2; ++i)
    {
        for (int j = -1; j < 2; ++j)
        {
            if (_y + i >= 0 && _y + i < m_row && _x +j >= 0 && _x + j < m_col)
                pvec.push_back(std::move(std::make_pair(_y+i, _x+j)));
        }
    }
    return pvec;
}
