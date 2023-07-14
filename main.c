#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

void task1(Node **list, int k)
{
    Node *node = *list;
    Node *temp = NULL;
    Node *l = *list;
    Node *to_remove = NULL;

    int n = k;
    int len = length(l);
    int stop = 0;

    l = *list;

    while (node)
    {
        while (n > 0)
        {
            push(&temp, l->data, l->timestamp);
            l = l->next;
            n--;
        }

        Node *node2 = temp;
        Node *node3 = temp;
        double mean_value = mean(temp);
        double sigma = standard_deviation(node2);
        double diff = mean_value - sigma;
        double sum = mean_value + sigma;
        int p = 0;

        while (p < k / 2)
        {
            node3 = node3->next;
            p++;
        }

        if (node3->data < diff || node3->data > sum)
        {
            push(&to_remove, node3->data, node3->timestamp);
        }

        n = k;
        stop++;

        if (stop == len - k + 1)
        {
            break;
        }

        node = node->next;
        l = node;
        temp = NULL;
    }

    while (to_remove)
    {
        remove_element(list, to_remove->data);
        to_remove = to_remove->next;
    }
}

Node *task2_1(Node **list, int k)
{
    Node *node = *list;
    Node *temp = NULL;
    Node *l = *list;
    Node *res = NULL;

    int n = k;
    int len = length(l);
    int stop = 0;

    l = *list;

    while (node)
    {
        while (n > 0)
        {
            push(&temp, l->data, l->timestamp);
            l = l->next;
            n--;
        }

        sort(&temp);

        Node *sorted = temp;

        int p = 0;

        while (p < k / 2)
        {
            sorted = sorted->next;
            p++;
        }

        push(&res, sorted->data, sorted->timestamp);

        n = k;
        stop++;

        if (stop == len - k + 1)
        {
            break;
        }

        node = node->next;
        l = node;
        temp = NULL;
    }

    return res;
}

Node *task2_2(Node **list, int k)
{
    Node *node = *list;
    Node *temp = NULL;
    Node *l = *list;
    Node *res = NULL;

    int n = k;
    int len = length(l);
    int stop = 0;

    l = *list;

    while (node)
    {
        while (n > 0)
        {
            push(&temp, l->data, l->timestamp);
            l = l->next;
            n--;
        }

        Node *node2 = temp;
        double mean_value = mean(temp);
        int p = 0;

        while (p < k / 2)
        {
            node2 = node2->next;
            p++;
        }

        push(&res, mean_value, node2->timestamp);

        n = k;
        stop++;

        if (stop == len - k + 1)
        {
            break;
        }

        node = node->next;
        l = node;
        temp = NULL;
    }

    return res;
}

void task3(Node **list)
{
    Node *node = (*list)->next;
    node->prev = *list;
    Node *temp = NULL;
    push(&temp, node->prev->data, node->prev->timestamp);

    while (node)
    {
        int diff = node->timestamp - node->prev->timestamp;

        if (diff >= 100 && diff <= 1000)
        {
            int average_timestamp = (node->prev->timestamp + node->timestamp) / 2;
            double average_data = (node->prev->data + node->data) / 2;
            node->data = average_data;
            node->timestamp = average_timestamp;
            push(&temp, node->data, node->timestamp);
        }
        else
        {
            push(&temp, node->data, node->timestamp);
        }

        if (!node->next)
        {
            break;
        }

        node->next->prev = node;
        node = node->next;
    }

    *list = temp;
}

void task4(Node **list, int k)
{
    Node *node = *list;
    Node *temp = NULL;
    push(&temp, node->data, node->timestamp);
    Node *l = *list;
    int len = length(l);
    int q = len - k;

    while (q > 0)
    {
        if (node->next->timestamp - node->timestamp > 1000)
        {
            Node *left = NULL;
            Node *right = NULL;
            Node *node2 = *list;
            Node *node3 = *list;
            node2->prev = NULL;

            while (node2->timestamp != node->timestamp)
            {
                node2->next->prev = node2;
                node2 = node2->next;
            }

            int n = k;

            add(&left, node2->data, node2->timestamp);

            while (n > 1)
            {
                add(&left, node2->prev->data, node2->prev->timestamp);
                node2 = node2->prev;
                n--;
            }

            while (node3->timestamp != node->next->timestamp)
            {
                node3 = node3->next;
            }

            int p = k;

            push(&right, node3->data, node3->timestamp);

            while (p > 1)
            {
                push(&right, node3->next->data, node3->next->timestamp);
                node3 = node3->next;
                p--;
            }

            int timestamp = node->timestamp + 200;

            while (timestamp <= node->next->timestamp)
            {
                double data = generate_data(left, right, timestamp, k);
                if (timestamp == node->next->timestamp)
                {
                    push(&temp, node->next->data, node->next->timestamp);
                }
                else
                {
                    push(&temp, data, timestamp);
                }

                timestamp += 200;
            }
        }
        else
        {
            push(&temp, node->next->data, node->next->timestamp);
        }

        node = node->next;
        q--;
    }

    while (node)
    {
        push(&temp, node->data, node->timestamp);
        node = node->next;
    }

    *list = temp;
}

void task5(Node **list, int delta)
{
    Node *node = *list;
    Node *temp = *list;
    Node *node2 = *list;
    sort(&(*list));

    int l = 0;
    int r = 0;

    if (node->data < 0)
    {
        l = (int)node->data / delta - 1;
    }
    else
    {
        l = (int)node->data / delta;
    }

    while (node->next)
    {
        node = node->next;
    }

    if (node->data < 0)
    {
        r = (int)node->data / delta;
    }
    else
    {
        r = (int)node->data / delta + 1;
    }

    int left = l * delta;
    int right = r * delta;

    while (left <= right)
    {
        int count = count_occurrences(temp, left, left + delta);

        if (count == 0)
        {
            printf("");
        }
        else
        {
            printf("[%d, %d] %d\n", left, left + delta, count);
        }

        left = left + delta;
        temp = node2;
    }
}

int main(int argc, char *argv[])
{
    Node *list = NULL;
    int n;
    scanf("%d", &n);

    while (n > 0)
    {
        double a;
        int b;
        scanf("%d%lf", &b, &a);
        push(&list, a, b);
        n--;
    }

    int i = 1;
    while (i < argc)
    {
        if (strstr(argv[i], "--st") != 0)
        {
            int delta = 0;
            char *src = strstr(argv[i], "--st");

            if (src != NULL)
            {
                src += strlen("--st");
                sscanf(src, "%d", &delta);
            }

            task5(&list, delta);
        }
        else if (strcmp(argv[i], "--e1") == 0)
        {
            task1(&list, 5);
        }
        else if (strcmp(argv[i], "--e2") == 0)
        {
            list = task2_1(&list, 5);
        }
        else if (strcmp(argv[i], "--e3") == 0)
        {
            list = task2_2(&list, 5);
        }
        else if (strcmp(argv[i], "--u") == 0)
        {
            task3(&list);
        }
        else if (strcmp(argv[i], "--c") == 0)
        {
            task4(&list, 3);
        }

        i++;
    }

    if (strcmp(argv[i - 1], "--e1") == 0)
    {
        printf("%d\n", length(list));
        print(list);
    }
    else if (strcmp(argv[i - 1], "--e2") == 0)
    {
        printf("%d\n", length(list));
        print(list);
    }
    else if (strcmp(argv[i - 1], "--e3") == 0)
    {
        printf("%d\n", length(list));
        print(list);
    }
    else if (strcmp(argv[i - 1], "--u") == 0)
    {
        printf("%d\n", length(list));
        print(list);
    }
    else if (strcmp(argv[i - 1], "--c") == 0)
    {
        printf("%d\n", length(list));
        print(list);
    }
}