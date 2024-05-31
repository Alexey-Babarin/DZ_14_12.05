#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Функция для удаления комментариев из строки
string removeComments(string line) 
{
    bool inComment = false;
    string newLine = "";

    for (int i = 0; i < line.length(); i++) 
    {
        // Проверяем начало однострочного комментария
        if (line[i] == '/' && line[i + 1] == '/' && !inComment) 
        {
            break; // Прерываем цикл, если встретили однострочный комментарий
        }
        // Проверяем начало многострочного комментария
        else if (line[i] == '/' && line[i + 1] == '*' && !inComment) 
        {
            inComment = true; // Устанавливаем флаг, что начался многострочный комментарий
            i++;
        }
        // Проверяем окончание многострочного комментария
        else if (line[i] == '*' && line[i + 1] == '/' && inComment) 
        {
            inComment = false; // Сбрасываем флаг, что закончился многострочный комментарий
            i++;
        }
        else if (!inComment) 
        {
            newLine += line[i]; // Добавляем символ к новой строке, если не в комментарии
        }
    }

    return newLine;
}

int main() 
{
    setlocale(LC_ALL, "Russian");

    string fileContent = "";

    ifstream inFile("input.cpp");

    if (inFile) {
        string line;
        while (getline(inFile, line)) 
        {
            fileContent += removeComments(line) + "\n"; // Удаляем комментарии из строки и добавляем в общий текст
        }

        inFile.close();

        ofstream outFile("output.cpp"); // Создаем новый файл для записи результата
        outFile << fileContent; // Записываем результат без комментариев в файл
        outFile.close();

        cout << "Комментарии успешно удалены и записаны в файл output.cpp" << endl;
    }
    else 
    {
        cout << "Не удалось открыть файл" << endl;
    }

    return 0;
}