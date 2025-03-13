# main.py
from roman import Roman

def main():

    r1 = Roman(10)
    r2 = Roman("V")

    sum_result = r1 + r2
    arabic_sum_result = Roman.to_arabic(sum_result)
    print(f"{r1} + {r2} = {sum_result} = {arabic_sum_result}")  # вывод: X + V = XV = 15

    sub_result = r1 - r2
    arabic_sub_result = Roman.to_arabic(sub_result)
    print(f"{r1} - {r2} = {sub_result} = {arabic_sub_result}")  # вывод: X - V = V = 5

    mul_result = r1 * 2
    arabic_mul_result = Roman.to_arabic(mul_result)
    print(f"{r1} * 2 = {mul_result} = {arabic_mul_result}")  # вывод: X * 2 = XX = 20

    div_result = r1 // 2
    arabic_div_result = Roman.to_arabic(div_result)
    
    print(f"{r1} // 2 = {div_result} = {arabic_div_result}")  # вывод: X // 2 = V = 5

    true_div_result = r1 / 2
    arabic_true_div_result = Roman.to_arabic(true_div_result)

    print(f"{r1} / 2 = {true_div_result} = {arabic_true_div_result}")  # вывод: X / 2 = V = 5

    r3 = Roman("MMXXIII")
    print(f"{r3} = {r3.arabic}")  # вывод: MMXXIII = 2023

    arabic_number = 3999
    roman_number = Roman.to_roman(arabic_number)
    print(f"{arabic_number} = {roman_number}")  # вывод: 3999 = MMMCMXCIX

if __name__ == "__main__":
    main()
