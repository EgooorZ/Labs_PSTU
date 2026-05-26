#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <QVector>
#include <QString>
#include "Product.h"

class Warehouse
{
public:
    Warehouse();

    int addProduct(const QString& name, const QString& category, int quantity, int row, int cell);
    bool updateProduct(int id, const QString& name, const QString& category, int quantity, int row, int cell);
    bool removeProduct(int id);

    QVector<Product> products() const;
    void setProducts(const QVector<Product>& products);

    QVector<Product> searchProducts(const QString& query) const;

    Product* findById(int id);
    const Product* findById(int id) const;

    bool isCellBusy(int row, int cell, int ignoredProductId = -1) const;
    void clear();

private:
    QVector<Product> m_products;
    int m_nextId;
};

#endif