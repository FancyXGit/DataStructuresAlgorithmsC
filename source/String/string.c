#include <stdio.h>
#include <malloc.h>

typedef struct string
{
    char *str;
    int size;
} string;

// build string
// initString(&str, "Hello World!")
void initString(string *str, char *content)
{
    char *curr = content;
    int size = 0;
    while (*curr != '\0')
    {
        size++;
        curr++;
    }
    char *new_str = (char *)malloc(sizeof(char) * (size + 1));
    for (int i = 0; i < size + 1; i++)
    {
        new_str[i] = content[i];
    }
    str->size = size;
    str->str = new_str;
}

// return string length('\0' not included)
int stringLen(const string *str)
{
    return str->size;
}

// --WARNING-- if str1 wasn't initialized please use initString(string *str, char *content)
// copy str2 to str1
void stringCopy(string *str1, const string *str2)
{
    int size = str2->size;
    char *new_str = (char *)malloc(sizeof(char) * (size + 1));
    if (str1->str != NULL)
    {
        free(str1->str);
    }
    for (int i = 0; i < size + 1; i++)
    {
        new_str[i] = str2->str[i];
    }
    str1->size = size;
    str1->str = new_str;
}

// get char in string
char getStrChar(const string *str, int index)
{
    if (index >= str->size)
    {
        printf("StringIndexOutOfBoundException at function 'getStrChar'\n");
        return '\0';
    }
    return str->str[index];
}

// print string (with newline)
void printString(const string *str)
{
    printf("%s\n", str->str);
}

// return 1 if the two strings are the same
int isStrSame(const string *str1, const string *str2)
{
    if (str1->size != str2->size)
    {
        return 0;
    }
    else
    {
        for (int i = 0; i < str1->size; i++)
        {
            if (str1->str[i] != str2->str[i])
            {
                return 0;
            }
        }
        return 1;
    }
}

// --WARNING-- string res should not have been initialized or memory leak would happen
// concatenate two strings str1 and str2
// return result string *res
void stringCat(string *res, const string *str1, const string *str2)
{
    int size = str1->size + str2->size;
    char *new_str = (char *)malloc(sizeof(char) * (size + 1));
    for (int i = 0; i < str1->size; i++)
    {
        new_str[i] = str1->str[i];
    }
    for (int i = str1->size; i < size + 1; i++)
    {
        new_str[i] = str2->str[i - str1->size];
    }
    res->size = size;
    res->str = new_str;
}

// --WARNING-- string res should not have been initialized or memory leak would happen
// get substring str[start] to str[end]
// str[end] not included
void subString(string *res, string *str, int start, int end)
{
    if (start < 0 || end < 0 || end > str->size || start > end)
    {
        printf("IndexException at function 'subString'\n");
        return;
    }
    if (str->str == NULL)
    {
        printf("NullStringException at function 'subString'\n");
        return;
    }
    char *new_str = (char *)malloc(sizeof(char) * (end - start + 1)); // last char for '\0'
    for (int i = start; i < end; i++)
    {
        new_str[i - start] = str->str[i];
    }
    new_str[end - start] = '\0';
    res->size = end - start;
    res->str = new_str;
}

// free the memory of str
void freeString(string *str)
{
    if (str->str == NULL)
    {
        return;
    }
    free(str->str);
    str->size = -1;
    str->str = NULL;
}

int main(void)
{
    string str1;
    initString(&str1, "YES INDEED");
    printString(&str1);                         // YES INDEED
    printf("str1长度: %d\n", stringLen(&str1)); // 10

    // 测试拷贝
    string str2;
    initString(&str2, "");
    stringCopy(&str2, &str1);
    printString(&str2);                         // YES INDEED
    printf("str2长度: %d\n", stringLen(&str2)); // 10

    // 测试拼接
    string str3;
    stringCat(&str3, &str1, &str2);
    printString(&str3);                         // YES INDEEDYES INDEED
    printf("str3长度: %d\n", stringLen(&str3)); // 20

    // 测试比较
    printf("str1和str2是否相同: %d\n", isStrSame(&str1, &str2)); // 1
    printf("str1和str3是否相同: %d\n", isStrSame(&str1, &str3)); // 0

    // 测试取字符
    printf("str1第4个字符: %c\n", getStrChar(&str1, 3));   // I
    printf("str1第20个字符: %c\n", getStrChar(&str1, 19)); // 越界，返回'\0'

    // 测试子串
    string sub1;
    subString(&sub1, &str3, 0, 3);              // 截取前3个字符
    printString(&sub1);                         // YES
    printf("sub1长度: %d\n", stringLen(&sub1)); // 3

    string sub2;
    subString(&sub2, &str3, 5, 15); // 截取中间10个字符
    printString(&sub2);
    printf("sub2长度: %d\n", stringLen(&sub2)); // 10

    // 测试越界
    string sub3;
    subString(&sub3, &str3, -1, 5);  // start越界
    subString(&sub3, &str3, 0, 100); // end越界
    subString(&sub3, &str3, 8, 3);   // start > end

    // 测试空串
    string sub4;
    subString(&sub4, &str2, 0, 0);              // 空串
    printString(&sub4);                         // 输出空行
    printf("sub4长度: %d\n", stringLen(&sub4)); // 0

    // 释放所有字符串
    freeString(&str1);
    freeString(&str2);
    freeString(&str3);
    freeString(&sub1);
    freeString(&sub2);
    freeString(&sub3);
    freeString(&sub4);

    return 0;
}