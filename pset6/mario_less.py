def main():
    # Input height
    while True:
        error = False
        try:
            height = int(input("Height: "))
        except:
            print("Please enter a valid positive integer.")
            error = True

        if error == False:
            if height > 0 and height < 9:
                break

    # Loop over left pyramid
    for x in range(height):
        for y in range(height - x - 1):
            print(" ", end="")

        for z in range(x + 1):
            print("#", end="")

        # Print a new line
        print("")


# Call main function
main()