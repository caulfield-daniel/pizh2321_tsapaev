from writing import *

if __name__ == "__main__":
    pencil = Pencil()
    pen = Pen()
    gel_pen = GelPen()

    pencil.write("Проверка карандаша.")
    pen.write("Проверка ручки.")
    gel_pen.write("Проверка гелевой ручки.") 

    pencil.write("Еще одна проверка карандаша.")
    # Вернем последний текст, написанный карандашом
    print(pencil.last_written_text())

    # Отменим последнее действие карандаша
    pencil.undo()

    # Вновь проверим последний текст, написанный карандашом
    print(pencil.last_written_text())
    print(pen.last_written_text())

    # Зададим стили письма
    pen.set_writing_style("italic")
    pencil.set_writing_style("bold")
    gel_pen.set_writing_style("underline")
    
    # Напишем текст заданным стилем
    for _ in (pencil, pen, gel_pen):
        _.write("Текст с заданным стилем.")