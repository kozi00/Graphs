#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Stack.h"
#include "Vector.h"

enum Group { NO_GROUP, FIRST_GROUP, SECOND_GROUP };

struct Vertex {
    int numberOfEdges;
    int id;
};


void Merge(int left, int mid, int right, Vector<Vertex>& v) {
    int sizeLeft = mid - left + 1;//podzial na 2 czesci
    int sizeRight = right - mid;
    Vertex* leftArray = new Vertex[sizeLeft];
    Vertex* rightArray = new Vertex[sizeRight];

    for (int i = 0; i < sizeLeft; ++i) {//przypisanie wartosci do dwoch czesci
        leftArray[i] = v[left + i];
    }
    for (int j = 0; j < sizeRight; ++j) {
        rightArray[j] = v[mid + 1 + j];
    }

    int leftIndex = 0, rightIndex = 0, mergedIndex = left;
    while (leftIndex < sizeLeft && rightIndex < sizeRight) {//lacznie 2 czesci
        if (leftArray[leftIndex].numberOfEdges >= rightArray[rightIndex].numberOfEdges) {//malejaco
            v[mergedIndex] = leftArray[leftIndex++];
        }
        else {
            v[mergedIndex] = rightArray[rightIndex++];
        }
        mergedIndex++;
    }

    while (leftIndex < sizeLeft) {//przypisywanie pozostalych czesci
        v[mergedIndex++] = leftArray[leftIndex++];
    }
    while (rightIndex < sizeRight) {
        v[mergedIndex++] = rightArray[rightIndex++];
    }

    delete[] leftArray;
    delete[] rightArray;
}

void SortDescending(int left, int right, Vector<Vertex>& v) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        SortDescending(left, mid, v);
        SortDescending(mid + 1, right, v);
        Merge(left, mid, right, v);
    }
}

void AssignColor(const Vector<Vector<int>>& graph, Vector<int>& color, const Vector<Vertex>& orderOfChecking) {
    for (int i = 0; i < orderOfChecking.GetSize(); i++) {
        if (graph[orderOfChecking[i].id].GetSize() == 0) {//jesli nie ma sasiadow -> przypisz najmnejsza wartosc i przejdz do kolejnego
            color[orderOfChecking[i].id] = 1;
            continue;
        }

        Vector<bool> availableColors(graph.GetSize(), true);

        for (int neighbor : graph[orderOfChecking[i].id]) {//sprawdzanie jakie kolory sa zajete
            if (color[neighbor] != 0) {
                availableColors[color[neighbor]] = false;
            }
        }
        int currentColor;
        for (currentColor = 1; currentColor < graph.GetSize(); currentColor++) {//przypisanie najnizszego mozlwiego koloru
            if (availableColors[currentColor]) {
                break;
            }
        }

        color[orderOfChecking[i].id] = currentColor;
    }

}


bool AssignGroup(const Vector<Vector<int>>& graph, int startVertex, Vector<Group>& group) {//przypisywanie dfsem grup na zmiane
    Stack s;
    s.push(startVertex);
    group[startVertex] = FIRST_GROUP;

    while (!s.isEmpty()) {
        int currentVertex = s.pop();

        for (int neighbor : graph[currentVertex]) {
            if (group[neighbor] == NO_GROUP) {
                group[neighbor] = (group[currentVertex] == FIRST_GROUP) ? SECOND_GROUP : FIRST_GROUP;
                s.push(neighbor);
            }
            else if (group[neighbor] == group[currentVertex]) {
                return false;//jesli sasiednie wierzcholki sa w tej samej grupie to jest niemozliwe
            }
        }
    }
    return true;//jesli przypisano wszystkim grupy to jest mozliwe
}
void DFS(const Vector<Vector<int>>& graph, int startVertex, Vector<bool>& visited) {
    Stack s;
    s.push(startVertex);
    while (!s.isEmpty()) {
        int currentVertex = s.pop();
        if (!visited[currentVertex]) {
            visited[currentVertex] = true;
            for (int neighbour : graph[currentVertex]) {
                if (!visited[neighbour]) {
                    s.push(neighbour);
                }
            }
        }
    }
}



//1
Vector<Vertex> DegreeSequence(const Vector<Vector<int>>& graph) {//posortowanie grafu po liczbie wierzcholkow
    Vector<Vertex> vertices(graph.GetSize());

    for (int i = 0; i < graph.GetSize(); i++) {
        vertices[i].numberOfEdges = graph[i].GetSize();
        vertices[i].id = i;
    }

    SortDescending(0, vertices.GetSize() - 1, vertices);

    for (int i = 0; i < graph.GetSize(); i++) {
        printf("%d ", vertices[i].numberOfEdges);
    }
    printf("\n");
    return vertices;
}
//2
void NumberOfComponents(const Vector<Vector<int>>& graph) {//liczba podgrafow krote nie maja czesci wspolnej
    Vector<bool> visited(graph.GetSize(), false);
    int componentCount = 0;

    for (int i = 0; i < graph.GetSize(); i++) {
        if (!visited[i]) {
            ++componentCount;
            DFS(graph, i, visited);
        }
    }
    printf("%d\n", componentCount);
}
//3
void Bipartiteness(const Vector<Vector<int>>& graph) {//sprawdzanie czy mozna podzielic wierzcholki na 2 grupy
    Vector<Group>group(graph.GetSize(), NO_GROUP);

    for (int i = 0; i < graph.GetSize(); i++) {
        if (group[i] == NO_GROUP) {
            if (!AssignGroup(graph, i, group)) {
                printf("F\n");
                return;
            }
        }
    }
    printf("T\n");
}
//4
void EccentricityOfvertices() {
    printf("?\n");
}
//5
void Planarity() {
    printf("?\n");
}
//6a
void Greedy(const Vector<Vector<int>>& graph) {//przypisanie kazdemu wierzcholkowi najmniejszy mozliwy kolor
    Vector<int> color(graph.GetSize(), 0);

    Vector<Vertex> orderOfChecking(graph.GetSize());
    for (int i = 0; i < orderOfChecking.GetSize(); i++) {//kolejnosc jest bez zmian ( 1 otrzymany)
        orderOfChecking[i].numberOfEdges = graph[i].GetSize();
        orderOfChecking[i].id = i;
    }

    AssignColor(graph, color, orderOfChecking);

    for (int i = 0; i < color.GetSize(); i++) {
        printf("%d ", color[i]);
    }
    printf("\n");
}
//6b
void LFmethod(const Vector<Vector<int>>& graph, const Vector<Vertex>& orderOfChecking) {//przypisanie kazdemu wierzcholkowi najmniejszy mozliwy kolor
    Vector<int> color(graph.GetSize(), 0);

    AssignColor(graph, color, orderOfChecking);//kolejnosc od najwiekszego stopnia

    for (int i = 0; i < color.GetSize(); i++) {
        printf("%d ", color[i]);
    }
    printf("\n");
}
//6c
void SLFmethod() {
    printf("?\n");
}
//7
void NumberOfDifferentC4Subgraphs() {
    printf("?\n");
}
//8
void NumberOfTheGraphComplementsEdges(const Vector<Vector<int>>& graph) {
    long long vertices = graph.GetSize();
    long long numberOfEdgesInCompleteGraph = (vertices * (vertices - 1)) / 2;
    long long numberOfEdges = 0;
    for (int i = 0; i < graph.GetSize(); i++) {
        numberOfEdges += graph[i].GetSize();
    }
    numberOfEdges /= 2;//trzeba podzielic na 2 bo liczy bo kazda krawedz liczy 2 razy ( z 2 wierzcholkow)
    long long numberOfEdgesInComplementsGraph = numberOfEdgesInCompleteGraph - numberOfEdges;
    printf("%lld\n", numberOfEdgesInComplementsGraph);

}

int main() {
    Vector<Vector<int>> vector;

    int k;
    scanf("%d", &k);
    for (int a = 0; a < k; a++) {
        int n;
        scanf("%d", &n);
        Vector<Vector<int>> graph(n);

        for (int i = 0; i < n; i++) {
            int s;
            scanf("%d", &s);
            graph[i].resize(s);
            for (int j = 0; j < s; j++) {
                int neighbour;
                scanf("%d", &neighbour);
                graph[i][j] = neighbour - 1;//-1 bo id sasiada zaczyna sie od 1 a nie od 0
            }
        }

        Vector<Vertex> sortedByDegree = DegreeSequence(graph);//zwraca posortowana tablce wierzcholkow(od najwyzszego stopnia)
        NumberOfComponents(graph);
        Bipartiteness(graph);
        EccentricityOfvertices();
        Planarity();
        Greedy(graph);
        LFmethod(graph, sortedByDegree);//uzywa posortowana tablce wierzcholkow(od najwyzszego stopnia)
        SLFmethod();
        NumberOfDifferentC4Subgraphs();
        NumberOfTheGraphComplementsEdges(graph);
    }
    return 0;
}