#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

class Product
{
public:
    Product();
    Product(int id, const QString& name, const QString& category, int quantity, int row, int cell);

    int id() const;
    QString name() const;
    QString category() const;
    int quantity() const;
    int row() const;
    int cell() const;

    void setName(const QString& name);
    void setCategory(const QString& category);
    void setQuantity(int quantity);
    void setRow(int row);
    void setCell(int cell);

private:
    int m_id;
    QString m_name;
    QString m_category;
    int m_quantity;
    int m_row;
    int m_cell;
};

#endif
