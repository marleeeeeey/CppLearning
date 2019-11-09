#include "Matrix.h"

Matrix::Matrix(sf::Vector2u size)
{
    m_cellTable.resize(size.y);
    for (auto & line : m_cellTable)
    {
        line.resize(size.x);
    }
}

void Matrix::add(const Object& object)
{
    for(unsigned row = 0; row < m_cellTable.size(); ++row)
    {
        auto& line = m_cellTable[row];
        for(unsigned col = 0; col < line.size(); ++col)
        {
            auto& matrixCell = line[col];
            if(object.isVisible({ col, row }))
                matrixCell = object.getCell({ col, row });
        }
    }
}

bool Matrix::checkCollision(const Object& object)
{
    for(unsigned row = 0; row < m_cellTable.size(); ++row)
    {
        const auto& line = m_cellTable[row];
        for(unsigned col = 0; col < line.size(); ++col)
        {
            const auto& matrixCell = line[col];
            if(matrixCell.isVisible == object.isVisible({ col, row }))
                return true;
        }
    }

    return false;
}

void Matrix::draw(sf::RenderWindow& window)
{
    for(unsigned row = 0; row < m_cellTable.size(); ++row)
    {
        const auto & line = m_cellTable[row];
        for(unsigned col = 0; col < line.size(); ++col)
        {
            const auto& cell = line[col];
            if(cell.isVisible)
            {
                unsigned size_px = 20;
                sf::RectangleShape rect({size_px, size_px});
                rect.setPosition({ col * size_px, row * size_px });
                rect.setOutlineColor(cell.color);
                rect.setOutlineThickness(2);
                window.draw(rect);
                col++;
            }
        }
    }
}
