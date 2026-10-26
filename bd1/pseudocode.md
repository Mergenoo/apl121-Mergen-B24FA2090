# Псевдокод — Сэдэв 27: Зогсоолын төлбөр

Энэ псевдокод нь `quest.fprg` блок схем болон `main.c`-тэй алхам алхмаар тохирно.

## Үндсэн алгоритм (Main)

```
ЭХЛЭЛ
 1.  Хувьсагч зарлах:
       бүхэл: n, i, plate, resident, inH, inM, outH, outM,
              inTotal, outTotal, minutes, fee, maxMinutes, maxPlate
       бодит: discount, pay, totalIncome, maxHours
 2.  totalIncome ← 0;  maxMinutes ← -1;  maxPlate ← 0
 3.  ХЭВЛЭХ гарчиг, тарифын мөр, хөнгөлөлтийн мөр
 4.  ДАВТ                                     // оролтын шалгалт (do-while)
       ХЭВЛЭХ "Өнөөдрийн машины тоо (5-10): "
       УНШИХ n
       ХЭРЭВ n < 5 ЭСВЭЛ n > 10 БОЛ
           ХЭВЛЭХ "Буруу утга! ..."
     ДАВТАХ ҮЕД n < 5 ЭСВЭЛ n > 10
 5.  ДУУДАХ PrintHeader()                     // дэд алгоритм (Call)
 6.  i-г 1-ээс n хүртэл 1-ээр нэмэгдүүлэн ДАВТ:
       6.1  ХЭВЛЭХ "--- i-р машин ---"
       6.2  ДАВТ                               // дугаарын шалгалт
              ХЭВЛЭХ prompt;  УНШИХ plate
              ХЭРЭВ plate < 0 ЭСВЭЛ plate > 9999 БОЛ ХЭВЛЭХ алдаа
            ДАВТАХ ҮЕД plate < 0 ЭСВЭЛ plate > 9999
       6.3  ДАВТ                               // орсон цагийн шалгалт
              УНШИХ inH, inM
              ХЭРЭВ inH < 0 ЭСВЭЛ inH > 23 ЭСВЭЛ inM < 0 ЭСВЭЛ inM > 59 БОЛ ХЭВЛЭХ алдаа
            ДАВТАХ ҮЕД (мөн адил нөхцөл)
       6.4  inTotal ← inH * 60 + inM
       6.5  ДАВТ                               // гарсан цагийн шалгалт
              УНШИХ outH, outM
              outTotal ← outH * 60 + outM
              ХЭРЭВ (цаг/минут хүрээнээс гадуур) ЭСВЭЛ outTotal <= inTotal БОЛ ХЭВЛЭХ алдаа
            ДАВТАХ ҮЕД (мөн адил нөхцөл)
       6.6  ДАВТ                               // оршин суугчийн шалгалт
              УНШИХ resident
              ХЭРЭВ resident <> 0 БА resident <> 1 БОЛ ХЭВЛЭХ алдаа
            ДАВТАХ ҮЕД resident <> 0 БА resident <> 1
       6.7  minutes ← outTotal - inTotal
       6.8  fee ← CalcFee(minutes)             // дэд алгоритмын дуудалт
       6.9  ХЭРЭВ resident = 1 БА fee > 0 БОЛ
                discount ← fee * 20 / 100
            ҮГҮЙ БОЛ
                discount ← 0
       6.10 pay ← fee - discount
       6.11 totalIncome ← totalIncome + pay
       6.12 ХЭРЭВ minutes > maxMinutes БОЛ     // хамгийн удааныг хайх
                maxMinutes ← minutes
                maxPlate ← plate
       6.13 ДУУДАХ PrintRow(i, plate, inH, inM, outH, outM, minutes, fee, discount, pay)
 7.  ХЭВЛЭХ "Нийт машин: n"
 8.  ХЭВЛЭХ "Өдрийн нийт орлого: totalIncome MNT"
 9.  maxHours ← (maxMinutes - maxMinutes MOD 60) / 60
 10. ХЭВЛЭХ "Хамгийн удаан зогссон: maxPlate дугаартай машин
              (maxMinutes мин = maxHours цаг maxMinutes MOD 60 мин)"
ТӨГСГӨЛ
```

## Дэд алгоритмууд

```
ФУНКЦ CalcFee(minutes) → fee                   // шатлалтай тариф (else-if шат)
    ХЭРЭВ minutes <= 30 БОЛ
        fee ← 0
    ҮГҮЙ БОЛ ХЭРЭВ minutes > 30 БА minutes <= 60 БОЛ
        fee ← 1000
    ҮГҮЙ БОЛ ХЭРЭВ minutes <= 180 БОЛ
        fee ← 2500
    ҮГҮЙ БОЛ ХЭРЭВ minutes <= 480 БОЛ
        fee ← 5000
    ҮГҮЙ БОЛ
        fee ← 8000
    БУЦААХ fee

ПРОЦЕДУР PrintHeader()
    ХЭВЛЭХ "No | Plate | Entry | Exit | Min | Fee | Disc | Pay"

ПРОЦЕДУР PrintRow(no, plateNo, hIn, mIn, hOut, mOut, mins, feeAmt, disc, payAmt)
    ХЭВЛЭХ no | plateNo | hIn:mIn | hOut:mOut | mins | feeAmt | disc | payAmt
```

## Схем ↔ main.c ↔ 7 элемент

| Псевдокодын алхам | `main.c` | Заавал байх элемент |
|---|---|---|
| 4, 6.2, 6.3, 6.5, 6.6 | `do { ... } while (...)` | 7. Оролтын шалгалт |
| 6.2 – 6.6 | `scanf(...)` (4+ өгөгдөл) ба `printf(...)` | 1. Оролт/гаралт |
| 6.4, 6.7, 6.10, 6.11 · 4, 6.5, 6.9 | `+ - *` · `&&`, `\|\|` | 2. Үйлдэл ба илэрхийлэл |
| 6.8 / `CalcFee` | `if / else if / else` шат | 3. Нөхцөл |
| 5, 6, 6.13 | `for` + `printf("%-4d %-8d ...")` (5–10 мөр) | 4. Давталт ба хүснэгт |
| 5, 6.8, 6.13 | Flowgorithm: `Call`/`CalcFee` · C: `main` дотор | 5. Дэд алгоритм |
| 6.12 | `if (minutes > maxMinutes)` | 6. Хайлт (хамгийн их) |
