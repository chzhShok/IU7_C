# Входные данные:  
Координаты точек, задающих прямую, и координаты точки  

# Выходные данные:  
Положение точки относительно прямой: 0 - выше, 1 - на прямой, 2 - ниже    

# Позитивные тесты:  
- 01 - точка лежит на прямой  
- 02 - точка лежит ниже прямой  
- 03 - точка лежит выше прямой  
- 04 - прямая параллельна оси ординат, точка на прямой  
- 05 - прямая параллельна оси ординат, точка справа от прямой  
- 06 - прямая параллельна оси ординат, точка слева от прямой  
- 07 - прямая параллельна оси абцисс, точка на прямой  
- 08 - прямая параллельна оси абцисс, точка выше прямой  

# Негативные тесты  
- 01 - все координаты одинаковые  
- 02 - координаты точек, задающих прямую, одинаковые  
- 03 - передано 2 аргумента, а не 6
- 04 - передано 4 аргумента, а не 6
