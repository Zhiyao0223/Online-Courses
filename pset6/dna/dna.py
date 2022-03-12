# Import library
import csv
import sys


# Main function
def main():
    # Initialise variables
    word_counter = 0
    gene = []
    status = False
    
    # Check for correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py DATABASE_FILENAME SEQUENCE_FILENAME")

    # Open .txt file for reading sequences of genes
    with open(sys.argv[2], "r") as txt_file:
        line = txt_file.read()
        
    # Append first 8 elements into list
    for i in range(word_counter, word_counter+8):
        try:
            gene.append(line[i])
        except IndexError as error:
            break

    # Initialise gene
    agatc = 1
    aatg = 1
    tatc = 1
    tctag = 1
    tctg = 1
    ttttttct = 1
    gaaa = 1
    gata = 1

    # Loop until end of sequences
    while(word_counter <= len(line)):
        tmp = 1
        
        # Use try except to avoid list out of range
        try:
            # AGATC
            if gene[0] == "A":
                if gene[1] == "G":
                    if gene[2] == "A":
                        if gene[3] == "T":
                            if gene[4] == "C":
                                for i in range(word_counter+5, len(line), 5):
                                    if line[i:i+5] == "AGATC":
                                        tmp += 1
                                    else:
                                        if tmp > agatc:
                                            agatc = tmp
                                        break
                # AATG
                elif gene[1] == "A":
                    if gene[2] == "T":
                        if gene[3] == "G":
                            for i in range(word_counter+4, len(line), 4):
                                if line[i:i+4] == "AATG":
                                    tmp += 1
                                else:
                                    if tmp > aatg:
                                        aatg = tmp
                                    break
            # TATC
            elif gene[0] == "T":
                if gene[1] == "A":
                    if gene[2] == "T":
                        if gene[3] == "C":
                            for i in range(word_counter+4, len(line), 4):
                                if line[i:i+4] == "TATC":
                                    tmp += 1
                                else:
                                    if tmp > tatc:
                                        tatc = tmp
                                    break
                # TCTAG
                elif gene[1] == "C":
                    if gene[2] == "T":
                        if gene[3] == "A":
                            if gene[4] == "G":
                                for i in range(word_counter+5, len(line), 5):
                                    if line[i:i+5] == "TCTAG":
                                        tmp += 1
                                    else:
                                        if tmp > tctag:
                                            tctag = tmp
                                        break
                        # TCTG
                        elif gene[3] == "G":
                            for i in range(word_counter+4, len(line), 4):
                                if line[i:i+4] == "TCTG":
                                    tmp += 1
                                else:
                                    if tmp > tctg:
                                        tctg = tmp
                                    break

                # TTTTTTCT
                elif gene[1] == "T":
                    if gene[2] == "T":
                        if gene[3] == "T":
                            if gene[4] == "T":
                                if gene[5] == "T":
                                    if gene[6] == "C":
                                        if gene[7] == "T":
                                            for i in range(word_counter+8, len(line), 8):
                                                if line[i:i+8] == "TTTTTTCT":
                                                    tmp += 1
                                                else:
                                                    if tmp > ttttttct:
                                                        ttttttct = tmp
                                                    break
            # GAAA
            elif gene[0] == "G":
                if gene[1] == "A":
                    if gene[2] == "A":
                        if gene[3] == "A":
                            for i in range(word_counter+4, len(line), 4):
                                if line[i:i+4] == "GAAA":
                                    tmp += 1
                                else:
                                    if tmp > gaaa:
                                        gaaa = tmp
                                    break
                    # GATA
                    elif gene[2] == "T":
                        if gene[3] == "A":
                            for i in range(word_counter+4, len(line), 4):
                                if line[i:i+4] == "GATA":
                                    tmp += 1
                                else:
                                    if tmp > gata:
                                        gata = tmp
                                    break

        # Prevent list out of range
        except IndexError as error:
            pass

        # Remove first element from list and increment word_counter
        gene.pop(0)
        word_counter += 1
        
        # Prevent list out of range when append new element
        try:
            gene.append(line[word_counter+7])
        except IndexError as error:
            break
    
    # Initialise variable determine database type        
    large = False

    # Open csv file for reading
    with open(sys.argv[1], "r") as csv_file:
        # Read all data into dictionary
        reader = csv.DictReader(csv_file)
        
        # Loop over all lines in .csv
        for line in reader:
            # If large database
            if len(reader.fieldnames) == 9:
                large = True
                
            # Check for genes
            if int(line['AGATC']) == agatc and int(line['AATG']) == aatg and int(line['TATC']) == tatc:
                # Large database need check for other genes
                if large:
                    if int(line['TTTTTTCT']) == ttttttct and int(line['GAAA']) == gaaa and int(line['GATA']) == gata and int(line['TCTG']) == tctg and int(line['TATC']) == tatc:
                        print(line['name'])
                        status = True
                        break
                # Small database
                else:
                    print(line['name'])
                    status = True
                    break
    
    # If no records of found, return Not match
    if not status:
        print("No match")


# Declare main function
main()