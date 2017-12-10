#ifndef MINEDATAMGR_H
#define MINEDATAMGR_H

#include <memory>
#include <vector>
#include "minedata.h"

class MineDataMgr
{
public:
    using MineDataPtr = std::shared_ptr<MineData>;

public:
    MineDataMgr();

    void init(unsigned _row, unsigned _col, unsigned _amount);
    void initMine();
    void assignMine(unsigned _sy, unsigned _sx);
    void clear();
    std::shared_ptr<MineData> getMineData(unsigned _row, unsigned _col);

private:


private:
    unsigned m_row;
    unsigned m_col;
    unsigned m_amount;

    std::vector <bool> m_valVec;
    std::vector <std::vector <MineDataPtr> > m_matrix;
};

#endif // MINEDATAMGR_H
