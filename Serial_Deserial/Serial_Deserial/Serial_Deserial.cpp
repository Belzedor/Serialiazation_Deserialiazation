#include <iostream>
#include "List.h"


void int_to_bin(int num)
{
    int sign = num;
    if (sign < 0) num = -num;
    char* reversed_bin = new char[log2(num) + 2];
    int i = 0;

    while (num > 0)
    {
        reversed_bin[i] = char('0' + num % 2);
        i++;
        num /= 2;
    }

    if (sign < 0)
    {
        reversed_bin[i] = '-';
        i++;
    }

    for (int j = i - 1; j >= 0; j--) std::cout << reversed_bin[j];

    delete[] reversed_bin;
};

void RemoveDups(char* str)
{
    int len = strlen(str);
    char* temp = new char[len] {str[0]};
    int j = 1;

    for (int i = 1; i < len; i++)
    {
        if (str[i] != str[i - 1])
        {
            temp[j] = str[i];
            j++;
        }
    }

    for (int i = 0; i < len; i++) str[i] = temp[i];

    delete[] temp;
};

int main()
{
    int_to_bin(-7);
    std::cout << "\n\n";
    char data[] = "AA A BBB 00AAA";
    RemoveDups(data);
    std::cout << data << "\n\n";;

    List list;
    list.push_back("1");
    list.push_back("2");
    list.push_back("3");
    list.push_back("4");
    list.set_rand(1, 3);
    list.set_rand(2, 4);
    list.set_rand(3, 2);
    list.set_rand(4, 1);

    std::cout << "Before serialiazation:" << '\n';
    list.show();

    char path[] = "List_data.bin";
    FILE* file;

    fopen_s(&file, path, "wb");
    if (file)
    {
        list.Serialize(file);
        fclose(file);
    }

    fopen_s(&file, path, "rb");
    if (file)
    {
        list.Deserialize(file);
        fclose(file);
    }

    std::cout << "After deserialiazation:" << '\n';
    list.show();

    return 0;
}