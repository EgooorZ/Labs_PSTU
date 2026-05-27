#ifndef TSP_H
#define TSP_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QVector>
#include <QPair>
#include <QMouseEvent>
#include <climits>
#include <queue>
#include <algorithm>

QT_BEGIN_NAMESPACE
namespace Ui { class TSP; }
QT_END_NAMESPACE

class TSP : public QMainWindow
{
    Q_OBJECT

public:
    explicit TSP(QWidget *parent = nullptr);
    ~TSP();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void on_addVertexButton_clicked();
    void on_addEdgeButton_clicked();
    void on_solveButton_clicked();
    void on_clearButton_clicked();
    void on_removeVertexButton_clicked();
    void on_removeEdgeButton_clicked();
    void on_deep_clicked();
    void on_width_clicked();
    void on_Dijkstra_clicked();
    void on_Floyd_clicked();

private:
    Ui::TSP *ui;
    QGraphicsScene *scene;
    QVector<QGraphicsEllipseItem*> vertices;
    QVector<QVector<int>> adjacencyMatrix;
    QVector<QPair<int, int>> selectedEdges;
    QVector<QGraphicsLineItem*> selectedEdgeItems;
    QVector<QGraphicsTextItem*> selectedEdgeLabels;
    int totalCost;

    struct Node {
        QVector<QVector<int>> reducedMatrix;
        int cost;
        int vertex;
        int level;
        QVector<int> path;
        int zeroEvaluation;
    };

    struct comp {
        bool operator()(const Node* lhs, const Node* rhs) const {
            return lhs->cost > rhs->cost;
        }
    };

    QVector<QVector<int>> reduceMatrix(QVector<QVector<int>> matrix, int &reductionCost);
    int calculateZeroCost(QVector<QVector<int>> matrix, int row, int col);
    void solveTSP();
    void highlightPath(const QVector<int>& path);
    void addVertexAtPosition(const QPointF &pos);
    bool isOverlapping(int x, int y, int minDistance);
    void dfs(int vertex, QVector<bool>& visited, QVector<int>& traversalOrder);
    void bfs(int startVertex);
    void dijkstra(int startVertex);
    QVector<int> getShortestPath(const QVector<int>& parent, int endVertex) const;
    QString pathToText(const QVector<int>& path) const;
    void floydWarshall();
    QString getAllPairsShortestPaths(const QVector<QVector<int>>& dist,
                                     const QVector<QVector<int>>& next) const;
    QString reconstructPath(int i, int j,
                            const QVector<QVector<int>>& next) const;
};

#endif // TSP_H
