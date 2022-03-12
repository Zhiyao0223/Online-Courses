# Import library to use floor function
import math


# Check total sum of whole credit card number
def checksum(credit_card):
    # Initialise and convert credit card no into string
    sum = 0
    i = 0
    tmp = credit_card
    
    # Create loop to add up every no in credit card
    while tmp > 0:
        remain = tmp % 10
        tmp = math.floor(tmp / 10)
        
        # Card no require *2 if not divisible by 2
        if i % 2 != 0:
            remain *= 2
            
            remain_string = str(remain)
            for no in range(len(remain_string)):
                sum += int(remain_string[no])
        else:
            sum += remain
         
        i += 1   

    # Check if total sum divisible by 10, valid if can
    if sum % 10 != 0:
        return False

    return True


# Check and return the card type
def card_type(number):
    # Initialise and convert credit card no into string type
    card_length = len(str(number))
    tmp = number

    # Get the first two digit of credit card
    while tmp > 100:
        tmp /= 10

    # Ensure no decimal
    tmp = math.floor(tmp)

    # Visa and Mastercard
    if card_length == 13 or card_length == 16:
        if tmp >= 51 and tmp <= 55:
            return "MASTERCARD"
        else:
            tmp = math.floor(tmp / 10)

            if tmp == 4:
                return "VISA"

    elif card_length == 15:
        if tmp == 34 or tmp == 37:
            return "AMEX"

    return "INVALID"


# Main function
def main():
    # Taking credit card no and check for alphabet or symbol
    while True:
        try:
            number = int(input("Please inset your credit card number (exclude hypen) :"))
            break
        except:
            print("Invalid credit card number. Please try again.")

    # Verify card
    card_status = checksum(number)
    if card_status == False:
        print("INVALID")
        return

    # Return and print card type
    output = card_type(number)
    print(output)


# Call main function
main()