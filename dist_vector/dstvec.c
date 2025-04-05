#include <stdio.h>
#include <stdlib.h>

struct node {
    unsigned dist[20];
    unsigned from[20];
} rt[10];

int main() {
    int cost_matrix[20][20];
    int nodes, i, j, k, count = 0;
    printf("Enter the number of nodes: ");
    scanf("%d", &nodes);

    printf("Enter the Cost Matrix:\n");
    for (i = 0; i < nodes; i++) {
        for (j = 0; j < nodes; j++) {
            scanf("%d", &cost_matrix[i][j]);
            cost_matrix[i][i]=0;
            rt[i].dist[j] = cost_matrix[i][j];
            rt[i].from[j] = j;
        }
    }

    do {
        count = 0;
        for (i = 0; i < nodes; i++) {
            for (j = 0; j < nodes; j++) {
                for (k = 0; k < nodes; k++) {
                    if (rt[i].dist[j] > cost_matrix[i][k] + rt[k].dist[j]) {
                        rt[i].dist[j] = rt[i].dist[k] + rt[k].dist[j];
                        rt[i].from[j] = rt[k].from[j];
                        count++;
                    }
                }
            }
        }
    } while (count != 0);

    for (i = 0; i < nodes; i++) {
        printf("\nFor router %d:\n", i + 1);
        for (j = 0; j < nodes; j++) {
            printf("    node %d via %d dist %d\n", j + 1, rt[i].from[j]+1, rt[i].dist[j]);
        }
    }

    return 0;
}
