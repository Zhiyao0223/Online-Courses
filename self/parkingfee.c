#include <math.h>
#include <stdio.h>

#define NUL '\0'

typedef struct
{
    char* name;
    char vehicletype;
    int rate;
}
parking;

char getVehicleType(void);
void displayVehicleRate(int type, parking vehicle[]);
int calHoursParked (int inHr, int inMin, int outHr, int outMin);
int parkingCharged(char type, int hours, parking vehicle[]);

int main (void)
{
    // Initialise
    parking vehicle[3];

    vehicle[0].name = "CAR", vehicle[0].vehicletype = 'c', vehicle[0].rate = 2;
    vehicle[1].name = "BUS", vehicle[1].vehicletype = 'b', vehicle[1].rate = 3;
    vehicle[2].name = "TRUCK", vehicle[2].vehicletype = 't', vehicle[2].rate = 4;

    int hour = 0, hour1 = 0;
    int min = 0, min1 = 0;

    // Prompt user input
    char temp = getVehicleType();
    
    printf("Time entered car park (hh mm) : ");
    scanf("%d", &hour);
    scanf("%d", &min);

    printf("Time exited car park (hh mm) : ");
    scanf("%d", &hour1);
    scanf("%d", &min1);
    
    int hours = calHoursParked(hour, min, hour1, min1);
    
    
    // Parking ticket start with print ==
    printf("\n\n\n");
    for (int i = 0; i < 40; i++)
    {
        printf("=");
    }
    printf("\nPARKING TICKET\n");
    
    displayVehicleRate(temp, vehicle);
    
    printf("Hours parked: %d\n", hours);

    if (hours == -1)
    {
        printf("Error, please see the management\n");
        return -1;
    }
    
    int charge = parkingCharged(temp, hours, vehicle);

    printf("Please pay this ammount =====> RM %d.00\n", charge);
    printf("Thank You and Have a Nice Day~ \n");
    
    // Print ==
    for (int i = 0; i < 40; i++)
    {
        printf("=");
    }
    printf("\n");
    return 0;
}





// Prompt for vehicle type
char getVehicleType(void)
{
    char cartype = NUL;

    while (cartype != 'c' && cartype != 'b' && cartype != 't')
    {
        printf("Vehicle type: c(ar), b(us), t(ruck)?  ");
        scanf(" %c", &cartype);
    }

    return cartype;
}





// Show info
void displayVehicleRate(int type, parking vehicle[])
{
    for (int i = 0; i < 3; i++)
    {
        if (type == vehicle[i].vehicletype)
        {
            printf("Vehicle type: %s => RM %d.00 per hour (or part thereof)\n", vehicle[i].name, vehicle[i].rate);
            break;
        }
    }

    return;
}





// Calculate parking hour
int calHoursParked (int inHr, int inMin, int outHr, int outMin)
{
    int total[2] = {0};
    int number = 0;
    double difference = 0;
    
    if (inHr < 7 || outHr < 7)
    {
        return -1;
    }

    total[0] = (inHr * 60) + inMin;
    total[1] = (outHr * 60) + outMin;

    difference = ((total[1] - total[0]) / 60.0);
    number = ceil(difference);

    return number;
}





// Calculate parking fee. Here take three argument
int parkingCharged(char type, int hours, parking vehicle[])
{
    int charge = 0;
    for (int i = 0; i < 3; i++)
    {
        if (type == vehicle[i].vehicletype)
        {
            charge = hours * vehicle[i].rate;
        }
    }

    return charge;
}