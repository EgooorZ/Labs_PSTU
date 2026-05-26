#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Warehouse.h"

class QLineEdit;
class QSpinBox;
class QPushButton;
class QTableWidget;
class WarehouseVisualizer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override = default;

private slots:
    void addProduct();
    void updateProduct();
    void removeProduct();
    void clearForm();

    void searchProducts();
    void resetSearch();

    void saveProducts();
    void loadProducts();

    void tableSelectionChanged();
    void visualizerSelectionChanged(int productId);

private:
    void setupUi();
    void setupConnections();

    bool readForm(QString& name,
                  QString& category,
                  int& quantity,
                  int& row,
                  int& cell);

    void refreshTable(const QVector<Product>& products);
    void fillForm(const Product& product);
    void selectTableRowByProductId(int productId);
    void updateVisualizer();

    int selectedProductId() const;

    Warehouse m_warehouse;

    QLineEdit* m_nameEdit;
    QLineEdit* m_categoryEdit;
    QSpinBox* m_quantitySpin;
    QSpinBox* m_rowSpin;
    QSpinBox* m_cellSpin;
    QLineEdit* m_searchEdit;

    QPushButton* m_addButton;
    QPushButton* m_updateButton;
    QPushButton* m_deleteButton;
    QPushButton* m_clearButton;
    QPushButton* m_searchButton;
    QPushButton* m_resetSearchButton;
    QPushButton* m_saveButton;
    QPushButton* m_loadButton;

    QTableWidget* m_table;
    WarehouseVisualizer* m_visualizer;

    int m_currentSelectedId;
};

#endif