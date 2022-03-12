# Import library
from math import floor


# Main function
def main():
    # Initialise variable
    total = 0

    # Do-while loop take correct input
    while True:
        try:
            amount = float(input("Change owed: "))
        except:
            print("Invalid amount entered. Please try again...\n")
            continue

        if amount != 0 and amount > 0:
            break
        print("Invalid value entered. Please try again...\n")

    # Round to cent
    cent = round(amount * 100, 0)

    temp = floor(cent / 25)
    total += temp
    remainding = cent % 25

    # Calculate number of 10
    if remainding != 0:
        temp = floor(remainding / 10)
        total += temp
        remainding %= 10

    # Calculate number of 5 and 1
    if remainding != 0:
        temp = floor(remainding / 5)
        total += temp + (remainding % 5)

    # Output
    print(total)


# Calling main function
main()