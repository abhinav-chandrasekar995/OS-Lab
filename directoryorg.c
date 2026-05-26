#include <stdio.h>
#include <string.h>

struct Directory {
    char name[20];
    int parent;
};

int main() {
    int ch, i, n;
    char file[20][20], user[10][20];
    while(1)
    {

    printf("\n1.Single Level Directory");
    printf("\n2.Two Level Directory");
    printf("\n3.Hierarchical Directory");
    printf("\nEnter choice: ");
    scanf("%d", &ch);

    switch (ch) {
        case 1:
            printf("Enter number of files: ");
            scanf("%d", &n);
            printf("Enter file names:\n");
            for (i = 0; i < n; i++)
                scanf("%s", file[i]);

            printf("\nFiles in Directory:\n");
            for (i = 0; i < n; i++)
                printf("%s\n", file[i]);
            break;

        case 2: {
            int u;
            printf("Enter number of users: ");
            scanf("%d", &u);

            for (i = 0; i < u; i++) {
                printf("Enter username and filename: ");
                scanf("%s%s", user[i], file[i]);
            }

            printf("\nTwo Level Directory:\n");
            for (i = 0; i < u; i++)
                printf("%s -> %s\n", user[i], file[i]);
            break;
        }

        case 3: {
            struct Directory dir[100];
            strcpy(dir[0].name, "root");
            dir[0].parent = -1;

            printf("Enter number of directories: ");
            scanf("%d", &n);

            for (i = 1; i <= n; i++) {
                printf("Enter directory name: ");
                scanf("%s", dir[i].name);
                dir[i].parent = 0;
            }

            printf("\nHierarchical Structure:\n");
            printf("root\n");
            for (i = 1; i <= n; i++)
                printf(" |-- %s\n", dir[i].name);
            break;
        }

        default:
            printf("Invalid Choice");
    }
    printf("\n");
}

    return 0;
}