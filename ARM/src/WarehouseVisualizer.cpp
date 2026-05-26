#include "WarehouseVisualizer.h"

#include <QColor>
#include <QFont>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>

WarehouseVisualizer::WarehouseVisualizer(QWidget* parent)
    : QOpenGLWidget(parent),
      m_rows(8),
      m_cells(10),
      m_selectedProductId(-1)
{
    setMinimumSize(460, 380);
}

void WarehouseVisualizer::setProducts(const QVector<Product>& products)
{
    m_products = products;
    update();
}

void WarehouseVisualizer::setSelectedProductId(int productId)
{
    m_selectedProductId = productId;
    update();
}

void WarehouseVisualizer::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.96f, 0.96f, 0.96f, 1.0f);
}

void WarehouseVisualizer::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void WarehouseVisualizer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QFont titleFont = painter.font();
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    painter.setFont(titleFont);
    painter.setPen(Qt::black);
    painter.drawText(QRectF(0, 10, width(), 30), Qt::AlignCenter, "Схема склада");

    QFont cellFont = painter.font();
    cellFont.setPointSize(10);
    cellFont.setBold(false);
    painter.setFont(cellFont);

    for (int row = 1; row <= m_rows; ++row) {
        for (int cell = 1; cell <= m_cells; ++cell) {
            const QRectF rect = cellRect(row, cell);
            const Product* product = productAtCell(row, cell);

            QColor backgroundColor(246, 246, 246);
            QColor borderColor(80, 80, 80);
            int borderWidth = 1;

            if (product != nullptr) {
                backgroundColor = QColor(170, 215, 255);
            }

            if (product != nullptr && product->id() == m_selectedProductId) {
                backgroundColor = QColor(255, 218, 110);
                borderColor = QColor(170, 110, 0);
                borderWidth = 3;
            }

            painter.setBrush(backgroundColor);
            painter.setPen(QPen(borderColor, borderWidth));
            painter.drawRect(rect);

            painter.setPen(Qt::black);

            if (product != nullptr) {
                painter.drawText(rect, Qt::AlignCenter, QString::number(product->id()));
            } else {
                painter.drawText(rect, Qt::AlignCenter, QString("%1.%2").arg(row).arg(cell));
            }
        }
    }

    painter.setPen(Qt::black);
    painter.drawText(20, height() - 50, "Голубой цвет - занятая ячейка");
    painter.drawText(20, height() - 28, "Жёлтый цвет - выбранный товар");
}

void WarehouseVisualizer::mousePressEvent(QMouseEvent* event)
{
    for (int row = 1; row <= m_rows; ++row) {
        for (int cell = 1; cell <= m_cells; ++cell) {
            if (cellRect(row, cell).contains(event->position())) {
                const Product* product = productAtCell(row, cell);

                if (product != nullptr) {
                    emit productSelected(product->id());
                }

                return;
            }
        }
    }
}

QRectF WarehouseVisualizer::cellRect(int row, int cell) const
{
    const int leftMargin = 28;
    const int topMargin = 55;
    const int rightMargin = 28;
    const int bottomMargin = 75;

    const double gridWidth = width() - leftMargin - rightMargin;
    const double gridHeight = height() - topMargin - bottomMargin;
    const double cellWidth = gridWidth / m_cells;
    const double cellHeight = gridHeight / m_rows;

    return QRectF(
        leftMargin + (cell - 1) * cellWidth + 2,
        topMargin + (row - 1) * cellHeight + 2,
        cellWidth - 4,
        cellHeight - 4
    );
}

const Product* WarehouseVisualizer::productAtCell(int row, int cell) const
{
    for (const Product& product : m_products) {
        if (product.row() == row && product.cell() == cell) {
            return &product;
        }
    }

    return nullptr;
}
