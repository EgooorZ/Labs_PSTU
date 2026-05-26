#ifndef WAREHOUSEVISUALIZER_H
#define WAREHOUSEVISUALIZER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QVector>
#include <QRectF>
#include "Product.h"

class WarehouseVisualizer : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit WarehouseVisualizer(QWidget* parent = nullptr);

    void setProducts(const QVector<Product>& products);
    void setSelectedProductId(int productId);

signals:
    void productSelected(int productId);

protected:
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    QRectF cellRect(int row, int cell) const;
    const Product* productAtCell(int row, int cell) const;

    QVector<Product> m_products;
    int m_rows;
    int m_cells;
    int m_selectedProductId;
};

#endif
