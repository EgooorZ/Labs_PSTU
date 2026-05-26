#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <QString>
#include <QVector>
#include "Product.h"

class DataStorage
{
public:
    static bool saveProducts(const QString& fileName,
                             const QVector<Product>& products,
                             QString& errorText);

    static bool loadProducts(const QString& fileName,
                             QVector<Product>& products,
                             QString& errorText);
};

#endif