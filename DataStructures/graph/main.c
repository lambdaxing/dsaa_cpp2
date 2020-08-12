#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode* List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* �������Ա������һ��Ԫ�ص�λ�� */
};

List ReadInput(); /* ����ʵ�֣�ϸ�ڲ���Ԫ�ش��±�1��ʼ�洢 */
Position BinarySearch(List L, ElementType X);

int main()
{
    List L;
    ElementType X;
    Position P;

    L = ReadInput();
    scanf_s("%d", &X);
    P = BinarySearch(L, X);
    printf("%d\n", P);

    return 0;
}

Position BinarySearch(List L, ElementType X)
{
    Position l = 1, r = L->Last;
    while (l <= r)
    {
        Position i = (l + r) / 2;
        if (L->Data[i] < X)
            r = i - 1;
        else if (L->Data[i] > X)
            l = i + 1;
        else
            return i;
    }
    return NotFound;
}