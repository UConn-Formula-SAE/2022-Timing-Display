#define MATR_BIT(pos) ( 1<<(pos) )

#define MATR_G MATR_BIT(0)
#define MATR_F MATR_BIT(1)
#define MATR_E MATR_BIT(2)
#define MATR_D MATR_BIT(3)
#define MATR_C MATR_BIT(4)
#define MATR_B MATR_BIT(5)
#define MATR_A MATR_BIT(6)
#define MATR_DP MATR_BIT(7)

#define RAW_0 (MATR_A | MATR_B | MATR_C | MATR_D | MATR_E | MATR_F)
#define RAW_1 (MATR_B | MATR_C)
#define RAW_2 (MATR_A | MATR_B | MATR_D | MATR_E | MATR_G)
#define RAW_3 (MATR_A | MATR_B | MATR_C | MATR_D | MATR_G)
#define RAW_4 (MATR_B | MATR_C | MATR_F | MATR_G)
#define RAW_5 (MATR_A | MATR_C | MATR_D | MATR_F | MATR_G)
#define RAW_6 (MATR_A | MATR_C | MATR_D | MATR_E | MATR_F | MATR_G)
#define RAW_7 (MATR_A | MATR_B | MATR_C)
#define RAW_8 (MATR_A | MATR_B | MATR_C | MATR_D | MATR_E | MATR_F | MATR_G)
#define RAW_9 (MATR_A | MATR_B | MATR_C | MATR_F | MATR_G)

#define RAW_A (MATR_A | MATR_B | MATR_C | MATR_E | MATR_F | MATR_G)
#define RAW_B (MATR_C | MATR_D | MATR_E | MATR_F | MATR_G)
#define RAW_C (MATR_A | MATR_D | MATR_E | MATR_F)
#define RAW_D (MATR_B | MATR_C | MATR_D | MATR_E | MATR_G)
#define RAW_E (MATR_A | MATR_D | MATR_E | MATR_F | MATR_G)
#define RAW_F (MATR_A | MATR_E | MATR_F | MATR_G)

#define RAW_U (MATR_F | MATR_E | MATR_D | MATR_C | MATR_B)
#define RAW_O RAW_0
#define RAW_n (MATR_C | MATR_E | MATR_G)
#define RAW_S RAW_5
