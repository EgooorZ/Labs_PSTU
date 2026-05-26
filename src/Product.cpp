#include "Product.h"

Product::Product()
    : m_id(0),
      m_quantity(0),
      m_row(1),
      m_cell(1)
{
}

Product::Product(int id, const QString& name, const QString& category, int quantity, int row, int cell)
    : m_id(id),
      m_name(name),
      m_category(category),
      m_quantity(quantity),
      m_row(row),
      m_cell(cell)
{
}

int Product::id() const
{
    return m_id;
}

QString Product::name() const
{
    return m_name;
}

QString Product::category() const
{
    return m_category;
}

int Product::quantity() const
{
    return m_quantity;
}

int Product::row() const
{
    return m_row;
}

int Product::cell() const
{
    return m_cell;
}

void Product::setName(const QString& name)
{
    m_name = name;
}

void Product::setCategory(const QString& category)
{
    m_category = category;
}

void Product::setQuantity(int quantity)
{
    m_quantity = quantity;
}

void Product::setRow(int row)
{
    m_row = row;
}

void Product::setCell(int cell)
{
    m_cell = cell;
}
