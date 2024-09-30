#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void printPath(int parent[], int j)
{
    if (parent[j] == -1)
    {
        return;
    }
    printPath(parent, parent[j]);
    printf(" -> %d", j);
}

void bellmanFord(int **graph, int vertices, int edges, int source)
{
    int distance[vertices];
    int parent[vertices];
    int inNegativeCycle[vertices];

    for (int i = 0; i < vertices; i++)
    {
        distance[i] = INT_MAX;
        parent[i] = -1;
        inNegativeCycle[i] = 0;
    }
    distance[source] = 0;

    for (int i = 0; i < vertices - 1; i++)
    {
        for (int u = 0; u < vertices; u++)
        {
            for (int v = 0; v < vertices; v++)
            {
                if (graph[u][v] != 0 && distance[u] != INT_MAX &&
                    distance[u] + graph[u][v] < distance[v])
                {
                    distance[v] = distance[u] + graph[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    for (int u = 0; u < vertices; u++)
    {
        for (int v = 0; v < vertices; v++)
        {
            if (graph[u][v] != 0 && distance[u] != INT_MAX &&
                distance[u] + graph[u][v] < distance[v])
            {
                inNegativeCycle[v] = 1;
            }
        }
    }

    for (int i = 0; i < vertices; i++)
    {
        if (inNegativeCycle[i])
        {
            for (int j = 0; j < vertices; j++)
            {
                if (graph[i][j] != 0)
                {
                    inNegativeCycle[j] = 1;
                }
            }
        }
    }

    printf("Vertex Distance from Source\n");
    for (int i = 0; i < vertices; i++)
    {
        if (inNegativeCycle[i])
        {
            printf("%d \t\t Negative Cycle\n", i);
        }
        else if (distance[i] == INT_MAX)
        {
            printf("%d \t\t Unreachable\n", i);
        }
        else
        {
            printf("%d \t\t %d", i, distance[i]);
            printf("\t Path: %d", source);
            printPath(parent, i);
            printf("\n");
        }
    }
}

int main()
{
    int vertices, edges, source;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);
    printf("Enter number of edges: ");
    scanf("%d", &edges);

    int **graph = (int **)malloc(vertices * sizeof(int *));
    for (int i = 0; i < vertices; i++)
    {
        graph[i] = (int *)calloc(vertices, sizeof(int));
    }

    printf("Enter edges in the format (u v weight):\n");
    for (int i = 0; i < edges; i++)
    {
        int u, v, weight;
        scanf("%d %d %d", &u, &v, &weight);
        graph[u][v] = weight;
    }

    printf("Enter the source vertex: ");
    scanf("%d", &source);

    bellmanFord(graph, vertices, edges, source);

    for (int i = 0; i < vertices; i++)
    {
        free(graph[i]);
    }
    free(graph);

    return 0;
}
