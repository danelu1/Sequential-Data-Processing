#include <math.h>

typedef struct Node
{
    double data;
    int timestamp;
    struct Node *next, *prev;
} Node;

double mean(Node *list)
{
    double sum = 0;
    int len = 0;
    Node *node = list;

    while (node != NULL)
    {
        sum += node->data;
        node = node->next;
        len++;
    }

    return sum / len;
}

double standard_deviation(Node *list)
{
    Node *node = list;
    Node *temp = list;
    double mean_value = mean(node);
    int len = 0;
    double sum = 0;

    while (temp != NULL)
    {
        sum += (temp->data - mean_value) * (temp->data - mean_value);
        temp = temp->next;
        len++;
    }

    return sqrt(sum / len);
}

int length(Node *node)
{
    int len = 0;

    while (node != NULL)
    {
        len++;
        node = node->next;
    }

    return len;
}

void print(Node *node)
{
    while (node != NULL)
    {
        printf("%d %.02lf", node->timestamp, node->data);
        printf("\n");
        node = node->next;
    }
}

void add(Node **node, double data, int timestamp)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = data;
    temp->timestamp = timestamp;
    temp->next = *node;
    *node = temp;
}

void push(Node **node, double data, int timestamp)
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = data;
    n->timestamp = timestamp;
    n->next = NULL;

    if (!(*node))
    {
        *node = n;
        return;
    }

    Node *temp = *node;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = n;
}

void freeList(Node *node)
{
    free(node);
    while (node != NULL)
    {
        free(node);
        node = node->next;
    }

    node = NULL;
}

void remove_element(Node **head, double data)
{
    Node *temp = *head;
    Node *prev = NULL;

    if (temp && temp->data == data)
    {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp && temp->data != data)
    {
        prev = temp;
        temp = temp->next;
    }

    if (!temp)
    {
        return;
    }

    prev->next = temp->next;
    free(temp);
}

void sort(Node **head)
{
    int a;
    double b;

    Node *temp1;
    Node *temp2;

    for (temp1 = *head; temp1 != NULL; temp1 = temp1->next)
    {
        for (temp2 = temp1->next; temp2 != NULL; temp2 = temp2->next)
        {
            if (temp2->data < temp1->data)
            {
                a = temp1->timestamp;
                temp1->timestamp = temp2->timestamp;
                temp1->timestamp = a;

                b = temp1->data;
                temp1->data = temp2->data;
                temp2->data = b;
            }
        }
    }
}

int count_occurrences(Node *head, int left, int right)
{
    Node *temp = head;
    int cnt = 0;

    while (temp)
    {
        if (temp->data >= left && temp->data <= right)
        {
            cnt++;
        }

        temp = temp->next;
    }

    return cnt;
}

double scaling_factor(Node *left, Node *right, int timestamp)
{
    Node *node1 = left;
    Node *node2 = right;

    while (node1->next)
    {
        node1 = node1->next;
    }

    double C = ((double)timestamp - (double)node1->timestamp) / (node2->timestamp - node1->timestamp);
    // printf("%.02lf\n", C);

    return C;
}

void coefficients(int k, double *w)
{
    int cnt = 0;

    double sum = 0;

    for (int i = 0; i < k; i++)
    {
        double r1 = ((double)i / (k - 1)) * ((double)i / (k - 1));
        double r2 = r1 * 0.9 + 0.1;
        sum += r2;
    }

    for (int i = 0; i < k; i++)
    {
        double r = ((double)i / (k - 1)) * ((double)i / (k - 1));
        double r1 = r * 0.9 + 0.1;

        w[i] = r1 / sum;
    }
}

double generate_data(Node *left, Node *right, int timestamp, int k)
{
    Node *node1 = left;
    Node *node2 = right;

    double C = scaling_factor(left, right, timestamp);
    double *w = (double *)malloc(k * sizeof(double));
    coefficients(k, w);

    double sum_left = 0;
    double sum_right = 0;

    for (int i = 0; i < k; i++)
    {
        sum_left += node1->data * w[i];
        sum_right += node2->data * w[i];
        node1 = node1->next;
        node2 = node2->next;
    }

    double res = (1 - C) * sum_left + C * sum_right;

    return res;
}