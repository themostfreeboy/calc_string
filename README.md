# calc_string
计算中缀表达式

可计算复杂的函数，可扩展性好，扩展时只需要修改calc.cpp文件中的rule_data注册信息以及编写对应的回调函数即可，程序支持函数的嵌套，支持浮点数运算。

目前未加入大量的异常判断逻辑，所以正常表达式可以正常计算，异常表达式，程序可能会崩溃。
