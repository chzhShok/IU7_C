## Позитивные тесты
1. сложение матриц, матрицы размером 1х1 
2. сложение матриц, квадратные матрицы размером 3х3 
3. сложение матриц, прямоугольные матрицы размером 3х4 
4. умножение матриц, результат - квадратная матрица 3х3 
5. умножение матриц, результат - прямоугольная матрица 3х1 
6. умножение матриц, даны квадратные матрицы размером 3х3 
7. умножение матриц, результат - матрица размером 1х1
8. операция по варианту, вычисление обратной матрицы 1х1
9. операция по варианту, вычисление обратной матрицы 3х3

## Негативные тесты
1. на вход не передаются аргументы
2. на вход передаётся 1 аргумент 
3. на вход передаются неверные аргументы
4. передаваемый файл не существует
5. пустой файл
6. количество строк или столбцов - не число 
7. количество строк или столбцов - число <= 0 
8. сложение матриц, нельзя провести сложение (размеры матриц не совпадают) 
9. умножение матриц, нельзя провести умножение (кол-во строк первой матрицы != кол-во столбцов второй матрицы)
10. на вход передаётся 2 аргумента
11. на вход передаётся 3 аргумента
12. на вход передаётся 6 аргументов
13. на вход передается сложение, но число аргументов неверное
14. на вход передается сложение, но первый файл не существует
15. на вход передается сложение, но второй файл не существует
17. на вход передается сложение, но n == 0 в первом файле
18. на вход передается сложение, но n == 0 во втором файле
19. на вход передается операция по варианту, но число аргументов неверное
20. на вход передается операция по варианту, но файл не существует
21. на вход передается операция по варианту, но n == 0
22. на вход передается операция по варианту, но в первой строке 2 числа
23. на вход передается операция по варианту, но обратной матрицы не существует