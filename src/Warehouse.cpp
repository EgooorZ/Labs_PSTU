#include "Warehouse.h"

Warehouse::Warehouse()
    : m_nextId(1)
{
}

int Warehouse::addProduct(const QString& name, const QString& category, int quantity, int row, int cell)
{
    Product product(m_nextId, name, category, quantity, row, cell);
    m_products.push_back(product);

    ++m_nextId;

    return product.id();
}

bool Warehouse::updateProduct(int id, const QString& name, const QString& category, int quantity, int row, int cell)
{
    Product* product = findById(id);

    if (product == nullptr) {
        return false;
    }

    product->setName(name);
    product->setCategory(category);
    product->setQuantity(quantity);
    product->setRow(row);
    product->setCell(cell);

    return true;
}

bool Warehouse::removeProduct(int id)
{
    for (int i = 0; i < m_products.size(); ++i) {
        if (m_products[i].id() == id) {
            m_products.removeAt(i);
            return true;
        }
    }

    return false;
}

QVector<Product> Warehouse::products() const
{
    return m_products;
}

void Warehouse::setProducts(const QVector<Product>& products)
{
    m_products = products;
    m_nextId = 1;

    for (const Product& product : m_products) {
        if (product.id() >= m_nextId) {
            m_nextId = product.id() + 1;
        }
    }
}

QVector<Product> Warehouse::searchProducts(const QString& query) const
{
    const QString preparedQuery = query.trimmed().toLower();

    if (preparedQuery.isEmpty()) {
        return m_products;
    }

    QVector<Product> result;

    for (const Product& product : m_products) {
        const bool matchedById = QString::number(product.id()).contains(preparedQuery);
        const bool matchedByName = product.name().toLower().contains(preparedQuery);
        const bool matchedByCategory = product.category().toLower().contains(preparedQuery);

        if (matchedById || matchedByName || matchedByCategory) {
            result.push_back(product);
        }
    }

    return result;
}

Product* Warehouse::findById(int id)
{
    for (Product& product : m_products) {
        if (product.id() == id) {
            return &product;
        }
    }

    return nullptr;
}

const Product* Warehouse::findById(int id) const
{
    for (const Product& product : m_products) {
        if (product.id() == id) {
            return &product;
        }
    }

    return nullptr;
}

bool Warehouse::isCellBusy(int row, int cell, int ignoredProductId) const
{
    for (const Product& product : m_products) {
        if (product.id() == ignoredProductId) {
            continue;
        }

        if (product.row() == row && product.cell() == cell) {
            return true;
        }
    }

    return false;
}

void Warehouse::clear()
{
    m_products.clear();
    m_nextId = 1;
}