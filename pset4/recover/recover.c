#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Create 8bit integer
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check user input match
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open input file
    FILE *file = fopen(argv[1], "r");
    // Return if file is none/empty
    if (file == NULL)
    {
        fclose(file);
        printf("Could not open file.\n");
    }

    // Initialise
    int position = -512, number = 0;
    _Bool test  = 0;
    BYTE end = 0;
    BYTE buffer[512] = {0};
    char name[8] = {'\0'};
    
    // Start loop till the end of file
    while (fread(&buffer, sizeof(BYTE), 512, file))
    {
        // Initialise
        test = 0;
        BYTE temp;
        
        // Easier for me check position, no actual function in here
        position += 512;
        
        // Check header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 && buffer[3] <= 0xef)
        {
            // Create jpeg and open it
            sprintf(name, "%0.3d.jpg", number);
            FILE *image = fopen(name, "w");   
                
            fwrite(&buffer, sizeof(BYTE), 512, image);
            fread(&buffer, sizeof(BYTE), 4, file);
            
            // Loop until found next header    
            while (test == 0)
            {
                if (feof(file))
                {
                    break;
                }
                if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 && buffer[3] <= 0xef)
                {
                    fseek(file, -4, SEEK_CUR);
                    test = 1;
                }
                else
                {
                    position += 4;
                    fwrite(&buffer, sizeof(BYTE), 4, image);
                    fread(&buffer, sizeof(BYTE), 4, file);
                }
            }
            
            // This "number" variable is used for jpeg name
            number++;
            fclose(image);
        }
    }
    
    // Close file
    fclose(file);
    return 0;
}