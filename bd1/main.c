

#include <stdio.h>

int main(void)
{
    int n, i;                       
    int plate, resident;            
    int inH, inM, outH, outM;       
    int inTotal, outTotal, minutes; 
    int fee, discount, pay;         
    int totalIncome = 0;            
    int maxMinutes = -1;            
    int maxPlate = 0;               

    printf("=== ЗОГСООЛЫН ТӨЛБӨРИЙН СИСТЕМ ===\n");
    printf("Тариф: 0-30 мин үнэгүй | 31-60: 1000 | 61-180: 2500 | 181-480: 5000 | 481+: 8000 (MNT)\n");
    printf("Оршин суугч 20%% хөнгөлөлттэй. Зөвхөн нэг өдрийн дотор (00:00-23:59).\n\n");

    
    printf("Өнөөдрийн машины тоо: ");
    scanf("%d", &n);

  
    printf("\n%-4s %-8s %-7s %-7s %6s %8s %8s %8s\n",
           "No", "Plate", "Entry", "Exit", "Min", "Fee", "Disc", "Pay");
    printf("------------------------------------------------------------\n");

    for (i = 1; i <= n; i++) {
        printf("\n--- %d-р машин ---\n", i);

        
        do {
            printf("Дугаарын тоон хэсэг (0-9999): ");
            scanf("%d", &plate);
            if (plate < 0 || plate > 9999) {
                printf("Буруу утга! 0-9999 хооронд оруулна уу.\n");
            }
        } while (plate < 0 || plate > 9999);

        
        do {
            printf("Орсон цаг минут (жишээ: 9 30): ");
            scanf("%d %d", &inH, &inM);
            if (inH < 0 || inH > 23 || inM < 0 || inM > 59) {
                printf("Буруу цаг! Цаг 0-23, минут 0-59 байна.\n");
            }
        } while (inH < 0 || inH > 23 || inM < 0 || inM > 59);
        inTotal = inH * 60 + inM;

        
        do {
            printf("Гарсан цаг минут (жишээ: 11 5): ");
            scanf("%d %d", &outH, &outM);
            outTotal = outH * 60 + outM;
            if (outH < 0 || outH > 23 || outM < 0 || outM > 59 || outTotal <= inTotal) {
                printf("Буруу цаг! Гарсан цаг орсноос хойш, 00:00-23:59 дотор байна.\n");
            }
        } while (outH < 0 || outH > 23 || outM < 0 || outM > 59 || outTotal <= inTotal);

        
        do {
            printf("Оршин суугч уу? (1 = тийм, 0 = үгүй): ");
            scanf("%d", &resident);
            if (resident != 0 && resident != 1) {
                printf("Буруу утга! 1 эсвэл 0 оруулна уу.\n");
            }
        } while (resident != 0 && resident != 1);

        
        minutes = outTotal - inTotal;
        if (minutes <= 30) {
            fee = 0;
        } else if (minutes > 30 && minutes <= 60) {
            fee = 1000;
        } else if (minutes > 60 && minutes <= 180) {
            fee = 2500;
        } else if (minutes > 180 && minutes <= 480) {
            fee = 5000;
        } else {
            fee = 8000;
        }

        
        if (resident == 1 && fee > 0) {
            discount = fee * 20 / 100;
        } else {
            discount = 0;
        }
        pay = fee - discount;
        totalIncome = totalIncome + pay;

       
        if (minutes > maxMinutes) {
            maxMinutes = minutes;
            maxPlate = plate;
        }

        
        printf("%-4d %-8d %02d:%02d   %02d:%02d   %6d %8d %8d %8d\n",
               i, plate, inH, inM, outH, outM, minutes, fee, discount, pay);
    }

    printf("------------------------------------------------------------\n");
    printf("Нийт машин: %d\n", n);
    printf("Өдрийн нийт орлого: %d MNT\n", totalIncome);
    printf("Хамгийн удаан зогссон: %d дугаартай машин (%d мин = %d цаг %d мин)\n",
           maxPlate, maxMinutes, maxMinutes / 60, maxMinutes % 60);

    return 0;
}
