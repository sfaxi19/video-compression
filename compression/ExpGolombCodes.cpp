#include <cmath>
#include <bitset>
#include "ExpGolombCodes.hpp"

void ExpCodeGen() {
    int M = 0;
    std::string expVal = "";
    int decVal = 0;
    int cnt = 0;
    int signVal = 0;
    int usignVal = 1;
    bool isSign = true;
    printf("uint32_t ExpCode[511];\n");
    printf("void ExpCodeInit() { \n");
    for (int i = 0; i < 511; i++) {
        if (cnt >= pow(2, M)) {
            cnt = 0;
            decVal = 0;
            M++;
        }
        expVal = "0b";
        for (int j = 0; j < M; j++) {
            expVal.append("0");
        }
        expVal.append("1");
        expVal.append(std::bitset<16>(decVal).to_string(), 16 - M, M);

        decVal++;
        cnt++;
        if (isSign) {
            printf("\tExpCode[255 + (%d)] = %s << %d;\n", signVal, expVal.c_str(), 32 - (M * 2 + 1));
            //std::cout << std::to_string(signVal) << "\t\t - " << expVal << std::endl;
            signVal--;
            isSign = false;
        } else {
            //std::cout << std::to_string(usignVal) << "\t\t - " << expVal << std::endl;
            printf("\tExpCode[255 + (%d)] = %s << %d;\n", usignVal, expVal.c_str(), 32 - (M * 2 + 1));
            usignVal++;
            isSign = true;
        }
    }
    printf("}\n");
}

uint32_t ExpCode[511];

void ExpCodeInit() {
    ExpCode[255 + (0)] = 0b1 << 31;
    ExpCode[255 + (1)] = 0b010 << 29;
    ExpCode[255 + (-1)] = 0b011 << 29;
    ExpCode[255 + (2)] = 0b00100 << 27;
    ExpCode[255 + (-2)] = 0b00101 << 27;
    ExpCode[255 + (3)] = 0b00110 << 27;
    ExpCode[255 + (-3)] = 0b00111 << 27;
    ExpCode[255 + (4)] = 0b0001000 << 25;
    ExpCode[255 + (-4)] = 0b0001001 << 25;
    ExpCode[255 + (5)] = 0b0001010 << 25;
    ExpCode[255 + (-5)] = 0b0001011 << 25;
    ExpCode[255 + (6)] = 0b0001100 << 25;
    ExpCode[255 + (-6)] = 0b0001101 << 25;
    ExpCode[255 + (7)] = 0b0001110 << 25;
    ExpCode[255 + (-7)] = 0b0001111 << 25;
    ExpCode[255 + (8)] = 0b000010000 << 23;
    ExpCode[255 + (-8)] = 0b000010001 << 23;
    ExpCode[255 + (9)] = 0b000010010 << 23;
    ExpCode[255 + (-9)] = 0b000010011 << 23;
    ExpCode[255 + (10)] = 0b000010100 << 23;
    ExpCode[255 + (-10)] = 0b000010101 << 23;
    ExpCode[255 + (11)] = 0b000010110 << 23;
    ExpCode[255 + (-11)] = 0b000010111 << 23;
    ExpCode[255 + (12)] = 0b000011000 << 23;
    ExpCode[255 + (-12)] = 0b000011001 << 23;
    ExpCode[255 + (13)] = 0b000011010 << 23;
    ExpCode[255 + (-13)] = 0b000011011 << 23;
    ExpCode[255 + (14)] = 0b000011100 << 23;
    ExpCode[255 + (-14)] = 0b000011101 << 23;
    ExpCode[255 + (15)] = 0b000011110 << 23;
    ExpCode[255 + (-15)] = 0b000011111 << 23;
    ExpCode[255 + (16)] = 0b00000100000 << 21;
    ExpCode[255 + (-16)] = 0b00000100001 << 21;
    ExpCode[255 + (17)] = 0b00000100010 << 21;
    ExpCode[255 + (-17)] = 0b00000100011 << 21;
    ExpCode[255 + (18)] = 0b00000100100 << 21;
    ExpCode[255 + (-18)] = 0b00000100101 << 21;
    ExpCode[255 + (19)] = 0b00000100110 << 21;
    ExpCode[255 + (-19)] = 0b00000100111 << 21;
    ExpCode[255 + (20)] = 0b00000101000 << 21;
    ExpCode[255 + (-20)] = 0b00000101001 << 21;
    ExpCode[255 + (21)] = 0b00000101010 << 21;
    ExpCode[255 + (-21)] = 0b00000101011 << 21;
    ExpCode[255 + (22)] = 0b00000101100 << 21;
    ExpCode[255 + (-22)] = 0b00000101101 << 21;
    ExpCode[255 + (23)] = 0b00000101110 << 21;
    ExpCode[255 + (-23)] = 0b00000101111 << 21;
    ExpCode[255 + (24)] = 0b00000110000 << 21;
    ExpCode[255 + (-24)] = 0b00000110001 << 21;
    ExpCode[255 + (25)] = 0b00000110010 << 21;
    ExpCode[255 + (-25)] = 0b00000110011 << 21;
    ExpCode[255 + (26)] = 0b00000110100 << 21;
    ExpCode[255 + (-26)] = 0b00000110101 << 21;
    ExpCode[255 + (27)] = 0b00000110110 << 21;
    ExpCode[255 + (-27)] = 0b00000110111 << 21;
    ExpCode[255 + (28)] = 0b00000111000 << 21;
    ExpCode[255 + (-28)] = 0b00000111001 << 21;
    ExpCode[255 + (29)] = 0b00000111010 << 21;
    ExpCode[255 + (-29)] = 0b00000111011 << 21;
    ExpCode[255 + (30)] = 0b00000111100 << 21;
    ExpCode[255 + (-30)] = 0b00000111101 << 21;
    ExpCode[255 + (31)] = 0b00000111110 << 21;
    ExpCode[255 + (-31)] = 0b00000111111 << 21;
    ExpCode[255 + (32)] = 0b0000001000000 << 19;
    ExpCode[255 + (-32)] = 0b0000001000001 << 19;
    ExpCode[255 + (33)] = 0b0000001000010 << 19;
    ExpCode[255 + (-33)] = 0b0000001000011 << 19;
    ExpCode[255 + (34)] = 0b0000001000100 << 19;
    ExpCode[255 + (-34)] = 0b0000001000101 << 19;
    ExpCode[255 + (35)] = 0b0000001000110 << 19;
    ExpCode[255 + (-35)] = 0b0000001000111 << 19;
    ExpCode[255 + (36)] = 0b0000001001000 << 19;
    ExpCode[255 + (-36)] = 0b0000001001001 << 19;
    ExpCode[255 + (37)] = 0b0000001001010 << 19;
    ExpCode[255 + (-37)] = 0b0000001001011 << 19;
    ExpCode[255 + (38)] = 0b0000001001100 << 19;
    ExpCode[255 + (-38)] = 0b0000001001101 << 19;
    ExpCode[255 + (39)] = 0b0000001001110 << 19;
    ExpCode[255 + (-39)] = 0b0000001001111 << 19;
    ExpCode[255 + (40)] = 0b0000001010000 << 19;
    ExpCode[255 + (-40)] = 0b0000001010001 << 19;
    ExpCode[255 + (41)] = 0b0000001010010 << 19;
    ExpCode[255 + (-41)] = 0b0000001010011 << 19;
    ExpCode[255 + (42)] = 0b0000001010100 << 19;
    ExpCode[255 + (-42)] = 0b0000001010101 << 19;
    ExpCode[255 + (43)] = 0b0000001010110 << 19;
    ExpCode[255 + (-43)] = 0b0000001010111 << 19;
    ExpCode[255 + (44)] = 0b0000001011000 << 19;
    ExpCode[255 + (-44)] = 0b0000001011001 << 19;
    ExpCode[255 + (45)] = 0b0000001011010 << 19;
    ExpCode[255 + (-45)] = 0b0000001011011 << 19;
    ExpCode[255 + (46)] = 0b0000001011100 << 19;
    ExpCode[255 + (-46)] = 0b0000001011101 << 19;
    ExpCode[255 + (47)] = 0b0000001011110 << 19;
    ExpCode[255 + (-47)] = 0b0000001011111 << 19;
    ExpCode[255 + (48)] = 0b0000001100000 << 19;
    ExpCode[255 + (-48)] = 0b0000001100001 << 19;
    ExpCode[255 + (49)] = 0b0000001100010 << 19;
    ExpCode[255 + (-49)] = 0b0000001100011 << 19;
    ExpCode[255 + (50)] = 0b0000001100100 << 19;
    ExpCode[255 + (-50)] = 0b0000001100101 << 19;
    ExpCode[255 + (51)] = 0b0000001100110 << 19;
    ExpCode[255 + (-51)] = 0b0000001100111 << 19;
    ExpCode[255 + (52)] = 0b0000001101000 << 19;
    ExpCode[255 + (-52)] = 0b0000001101001 << 19;
    ExpCode[255 + (53)] = 0b0000001101010 << 19;
    ExpCode[255 + (-53)] = 0b0000001101011 << 19;
    ExpCode[255 + (54)] = 0b0000001101100 << 19;
    ExpCode[255 + (-54)] = 0b0000001101101 << 19;
    ExpCode[255 + (55)] = 0b0000001101110 << 19;
    ExpCode[255 + (-55)] = 0b0000001101111 << 19;
    ExpCode[255 + (56)] = 0b0000001110000 << 19;
    ExpCode[255 + (-56)] = 0b0000001110001 << 19;
    ExpCode[255 + (57)] = 0b0000001110010 << 19;
    ExpCode[255 + (-57)] = 0b0000001110011 << 19;
    ExpCode[255 + (58)] = 0b0000001110100 << 19;
    ExpCode[255 + (-58)] = 0b0000001110101 << 19;
    ExpCode[255 + (59)] = 0b0000001110110 << 19;
    ExpCode[255 + (-59)] = 0b0000001110111 << 19;
    ExpCode[255 + (60)] = 0b0000001111000 << 19;
    ExpCode[255 + (-60)] = 0b0000001111001 << 19;
    ExpCode[255 + (61)] = 0b0000001111010 << 19;
    ExpCode[255 + (-61)] = 0b0000001111011 << 19;
    ExpCode[255 + (62)] = 0b0000001111100 << 19;
    ExpCode[255 + (-62)] = 0b0000001111101 << 19;
    ExpCode[255 + (63)] = 0b0000001111110 << 19;
    ExpCode[255 + (-63)] = 0b0000001111111 << 19;
    ExpCode[255 + (64)] = 0b000000010000000 << 17;
    ExpCode[255 + (-64)] = 0b000000010000001 << 17;
    ExpCode[255 + (65)] = 0b000000010000010 << 17;
    ExpCode[255 + (-65)] = 0b000000010000011 << 17;
    ExpCode[255 + (66)] = 0b000000010000100 << 17;
    ExpCode[255 + (-66)] = 0b000000010000101 << 17;
    ExpCode[255 + (67)] = 0b000000010000110 << 17;
    ExpCode[255 + (-67)] = 0b000000010000111 << 17;
    ExpCode[255 + (68)] = 0b000000010001000 << 17;
    ExpCode[255 + (-68)] = 0b000000010001001 << 17;
    ExpCode[255 + (69)] = 0b000000010001010 << 17;
    ExpCode[255 + (-69)] = 0b000000010001011 << 17;
    ExpCode[255 + (70)] = 0b000000010001100 << 17;
    ExpCode[255 + (-70)] = 0b000000010001101 << 17;
    ExpCode[255 + (71)] = 0b000000010001110 << 17;
    ExpCode[255 + (-71)] = 0b000000010001111 << 17;
    ExpCode[255 + (72)] = 0b000000010010000 << 17;
    ExpCode[255 + (-72)] = 0b000000010010001 << 17;
    ExpCode[255 + (73)] = 0b000000010010010 << 17;
    ExpCode[255 + (-73)] = 0b000000010010011 << 17;
    ExpCode[255 + (74)] = 0b000000010010100 << 17;
    ExpCode[255 + (-74)] = 0b000000010010101 << 17;
    ExpCode[255 + (75)] = 0b000000010010110 << 17;
    ExpCode[255 + (-75)] = 0b000000010010111 << 17;
    ExpCode[255 + (76)] = 0b000000010011000 << 17;
    ExpCode[255 + (-76)] = 0b000000010011001 << 17;
    ExpCode[255 + (77)] = 0b000000010011010 << 17;
    ExpCode[255 + (-77)] = 0b000000010011011 << 17;
    ExpCode[255 + (78)] = 0b000000010011100 << 17;
    ExpCode[255 + (-78)] = 0b000000010011101 << 17;
    ExpCode[255 + (79)] = 0b000000010011110 << 17;
    ExpCode[255 + (-79)] = 0b000000010011111 << 17;
    ExpCode[255 + (80)] = 0b000000010100000 << 17;
    ExpCode[255 + (-80)] = 0b000000010100001 << 17;
    ExpCode[255 + (81)] = 0b000000010100010 << 17;
    ExpCode[255 + (-81)] = 0b000000010100011 << 17;
    ExpCode[255 + (82)] = 0b000000010100100 << 17;
    ExpCode[255 + (-82)] = 0b000000010100101 << 17;
    ExpCode[255 + (83)] = 0b000000010100110 << 17;
    ExpCode[255 + (-83)] = 0b000000010100111 << 17;
    ExpCode[255 + (84)] = 0b000000010101000 << 17;
    ExpCode[255 + (-84)] = 0b000000010101001 << 17;
    ExpCode[255 + (85)] = 0b000000010101010 << 17;
    ExpCode[255 + (-85)] = 0b000000010101011 << 17;
    ExpCode[255 + (86)] = 0b000000010101100 << 17;
    ExpCode[255 + (-86)] = 0b000000010101101 << 17;
    ExpCode[255 + (87)] = 0b000000010101110 << 17;
    ExpCode[255 + (-87)] = 0b000000010101111 << 17;
    ExpCode[255 + (88)] = 0b000000010110000 << 17;
    ExpCode[255 + (-88)] = 0b000000010110001 << 17;
    ExpCode[255 + (89)] = 0b000000010110010 << 17;
    ExpCode[255 + (-89)] = 0b000000010110011 << 17;
    ExpCode[255 + (90)] = 0b000000010110100 << 17;
    ExpCode[255 + (-90)] = 0b000000010110101 << 17;
    ExpCode[255 + (91)] = 0b000000010110110 << 17;
    ExpCode[255 + (-91)] = 0b000000010110111 << 17;
    ExpCode[255 + (92)] = 0b000000010111000 << 17;
    ExpCode[255 + (-92)] = 0b000000010111001 << 17;
    ExpCode[255 + (93)] = 0b000000010111010 << 17;
    ExpCode[255 + (-93)] = 0b000000010111011 << 17;
    ExpCode[255 + (94)] = 0b000000010111100 << 17;
    ExpCode[255 + (-94)] = 0b000000010111101 << 17;
    ExpCode[255 + (95)] = 0b000000010111110 << 17;
    ExpCode[255 + (-95)] = 0b000000010111111 << 17;
    ExpCode[255 + (96)] = 0b000000011000000 << 17;
    ExpCode[255 + (-96)] = 0b000000011000001 << 17;
    ExpCode[255 + (97)] = 0b000000011000010 << 17;
    ExpCode[255 + (-97)] = 0b000000011000011 << 17;
    ExpCode[255 + (98)] = 0b000000011000100 << 17;
    ExpCode[255 + (-98)] = 0b000000011000101 << 17;
    ExpCode[255 + (99)] = 0b000000011000110 << 17;
    ExpCode[255 + (-99)] = 0b000000011000111 << 17;
    ExpCode[255 + (100)] = 0b000000011001000 << 17;
    ExpCode[255 + (-100)] = 0b000000011001001 << 17;
    ExpCode[255 + (101)] = 0b000000011001010 << 17;
    ExpCode[255 + (-101)] = 0b000000011001011 << 17;
    ExpCode[255 + (102)] = 0b000000011001100 << 17;
    ExpCode[255 + (-102)] = 0b000000011001101 << 17;
    ExpCode[255 + (103)] = 0b000000011001110 << 17;
    ExpCode[255 + (-103)] = 0b000000011001111 << 17;
    ExpCode[255 + (104)] = 0b000000011010000 << 17;
    ExpCode[255 + (-104)] = 0b000000011010001 << 17;
    ExpCode[255 + (105)] = 0b000000011010010 << 17;
    ExpCode[255 + (-105)] = 0b000000011010011 << 17;
    ExpCode[255 + (106)] = 0b000000011010100 << 17;
    ExpCode[255 + (-106)] = 0b000000011010101 << 17;
    ExpCode[255 + (107)] = 0b000000011010110 << 17;
    ExpCode[255 + (-107)] = 0b000000011010111 << 17;
    ExpCode[255 + (108)] = 0b000000011011000 << 17;
    ExpCode[255 + (-108)] = 0b000000011011001 << 17;
    ExpCode[255 + (109)] = 0b000000011011010 << 17;
    ExpCode[255 + (-109)] = 0b000000011011011 << 17;
    ExpCode[255 + (110)] = 0b000000011011100 << 17;
    ExpCode[255 + (-110)] = 0b000000011011101 << 17;
    ExpCode[255 + (111)] = 0b000000011011110 << 17;
    ExpCode[255 + (-111)] = 0b000000011011111 << 17;
    ExpCode[255 + (112)] = 0b000000011100000 << 17;
    ExpCode[255 + (-112)] = 0b000000011100001 << 17;
    ExpCode[255 + (113)] = 0b000000011100010 << 17;
    ExpCode[255 + (-113)] = 0b000000011100011 << 17;
    ExpCode[255 + (114)] = 0b000000011100100 << 17;
    ExpCode[255 + (-114)] = 0b000000011100101 << 17;
    ExpCode[255 + (115)] = 0b000000011100110 << 17;
    ExpCode[255 + (-115)] = 0b000000011100111 << 17;
    ExpCode[255 + (116)] = 0b000000011101000 << 17;
    ExpCode[255 + (-116)] = 0b000000011101001 << 17;
    ExpCode[255 + (117)] = 0b000000011101010 << 17;
    ExpCode[255 + (-117)] = 0b000000011101011 << 17;
    ExpCode[255 + (118)] = 0b000000011101100 << 17;
    ExpCode[255 + (-118)] = 0b000000011101101 << 17;
    ExpCode[255 + (119)] = 0b000000011101110 << 17;
    ExpCode[255 + (-119)] = 0b000000011101111 << 17;
    ExpCode[255 + (120)] = 0b000000011110000 << 17;
    ExpCode[255 + (-120)] = 0b000000011110001 << 17;
    ExpCode[255 + (121)] = 0b000000011110010 << 17;
    ExpCode[255 + (-121)] = 0b000000011110011 << 17;
    ExpCode[255 + (122)] = 0b000000011110100 << 17;
    ExpCode[255 + (-122)] = 0b000000011110101 << 17;
    ExpCode[255 + (123)] = 0b000000011110110 << 17;
    ExpCode[255 + (-123)] = 0b000000011110111 << 17;
    ExpCode[255 + (124)] = 0b000000011111000 << 17;
    ExpCode[255 + (-124)] = 0b000000011111001 << 17;
    ExpCode[255 + (125)] = 0b000000011111010 << 17;
    ExpCode[255 + (-125)] = 0b000000011111011 << 17;
    ExpCode[255 + (126)] = 0b000000011111100 << 17;
    ExpCode[255 + (-126)] = 0b000000011111101 << 17;
    ExpCode[255 + (127)] = 0b000000011111110 << 17;
    ExpCode[255 + (-127)] = 0b000000011111111 << 17;
    ExpCode[255 + (128)] = 0b00000000100000000 << 15;
    ExpCode[255 + (-128)] = 0b00000000100000001 << 15;
    ExpCode[255 + (129)] = 0b00000000100000010 << 15;
    ExpCode[255 + (-129)] = 0b00000000100000011 << 15;
    ExpCode[255 + (130)] = 0b00000000100000100 << 15;
    ExpCode[255 + (-130)] = 0b00000000100000101 << 15;
    ExpCode[255 + (131)] = 0b00000000100000110 << 15;
    ExpCode[255 + (-131)] = 0b00000000100000111 << 15;
    ExpCode[255 + (132)] = 0b00000000100001000 << 15;
    ExpCode[255 + (-132)] = 0b00000000100001001 << 15;
    ExpCode[255 + (133)] = 0b00000000100001010 << 15;
    ExpCode[255 + (-133)] = 0b00000000100001011 << 15;
    ExpCode[255 + (134)] = 0b00000000100001100 << 15;
    ExpCode[255 + (-134)] = 0b00000000100001101 << 15;
    ExpCode[255 + (135)] = 0b00000000100001110 << 15;
    ExpCode[255 + (-135)] = 0b00000000100001111 << 15;
    ExpCode[255 + (136)] = 0b00000000100010000 << 15;
    ExpCode[255 + (-136)] = 0b00000000100010001 << 15;
    ExpCode[255 + (137)] = 0b00000000100010010 << 15;
    ExpCode[255 + (-137)] = 0b00000000100010011 << 15;
    ExpCode[255 + (138)] = 0b00000000100010100 << 15;
    ExpCode[255 + (-138)] = 0b00000000100010101 << 15;
    ExpCode[255 + (139)] = 0b00000000100010110 << 15;
    ExpCode[255 + (-139)] = 0b00000000100010111 << 15;
    ExpCode[255 + (140)] = 0b00000000100011000 << 15;
    ExpCode[255 + (-140)] = 0b00000000100011001 << 15;
    ExpCode[255 + (141)] = 0b00000000100011010 << 15;
    ExpCode[255 + (-141)] = 0b00000000100011011 << 15;
    ExpCode[255 + (142)] = 0b00000000100011100 << 15;
    ExpCode[255 + (-142)] = 0b00000000100011101 << 15;
    ExpCode[255 + (143)] = 0b00000000100011110 << 15;
    ExpCode[255 + (-143)] = 0b00000000100011111 << 15;
    ExpCode[255 + (144)] = 0b00000000100100000 << 15;
    ExpCode[255 + (-144)] = 0b00000000100100001 << 15;
    ExpCode[255 + (145)] = 0b00000000100100010 << 15;
    ExpCode[255 + (-145)] = 0b00000000100100011 << 15;
    ExpCode[255 + (146)] = 0b00000000100100100 << 15;
    ExpCode[255 + (-146)] = 0b00000000100100101 << 15;
    ExpCode[255 + (147)] = 0b00000000100100110 << 15;
    ExpCode[255 + (-147)] = 0b00000000100100111 << 15;
    ExpCode[255 + (148)] = 0b00000000100101000 << 15;
    ExpCode[255 + (-148)] = 0b00000000100101001 << 15;
    ExpCode[255 + (149)] = 0b00000000100101010 << 15;
    ExpCode[255 + (-149)] = 0b00000000100101011 << 15;
    ExpCode[255 + (150)] = 0b00000000100101100 << 15;
    ExpCode[255 + (-150)] = 0b00000000100101101 << 15;
    ExpCode[255 + (151)] = 0b00000000100101110 << 15;
    ExpCode[255 + (-151)] = 0b00000000100101111 << 15;
    ExpCode[255 + (152)] = 0b00000000100110000 << 15;
    ExpCode[255 + (-152)] = 0b00000000100110001 << 15;
    ExpCode[255 + (153)] = 0b00000000100110010 << 15;
    ExpCode[255 + (-153)] = 0b00000000100110011 << 15;
    ExpCode[255 + (154)] = 0b00000000100110100 << 15;
    ExpCode[255 + (-154)] = 0b00000000100110101 << 15;
    ExpCode[255 + (155)] = 0b00000000100110110 << 15;
    ExpCode[255 + (-155)] = 0b00000000100110111 << 15;
    ExpCode[255 + (156)] = 0b00000000100111000 << 15;
    ExpCode[255 + (-156)] = 0b00000000100111001 << 15;
    ExpCode[255 + (157)] = 0b00000000100111010 << 15;
    ExpCode[255 + (-157)] = 0b00000000100111011 << 15;
    ExpCode[255 + (158)] = 0b00000000100111100 << 15;
    ExpCode[255 + (-158)] = 0b00000000100111101 << 15;
    ExpCode[255 + (159)] = 0b00000000100111110 << 15;
    ExpCode[255 + (-159)] = 0b00000000100111111 << 15;
    ExpCode[255 + (160)] = 0b00000000101000000 << 15;
    ExpCode[255 + (-160)] = 0b00000000101000001 << 15;
    ExpCode[255 + (161)] = 0b00000000101000010 << 15;
    ExpCode[255 + (-161)] = 0b00000000101000011 << 15;
    ExpCode[255 + (162)] = 0b00000000101000100 << 15;
    ExpCode[255 + (-162)] = 0b00000000101000101 << 15;
    ExpCode[255 + (163)] = 0b00000000101000110 << 15;
    ExpCode[255 + (-163)] = 0b00000000101000111 << 15;
    ExpCode[255 + (164)] = 0b00000000101001000 << 15;
    ExpCode[255 + (-164)] = 0b00000000101001001 << 15;
    ExpCode[255 + (165)] = 0b00000000101001010 << 15;
    ExpCode[255 + (-165)] = 0b00000000101001011 << 15;
    ExpCode[255 + (166)] = 0b00000000101001100 << 15;
    ExpCode[255 + (-166)] = 0b00000000101001101 << 15;
    ExpCode[255 + (167)] = 0b00000000101001110 << 15;
    ExpCode[255 + (-167)] = 0b00000000101001111 << 15;
    ExpCode[255 + (168)] = 0b00000000101010000 << 15;
    ExpCode[255 + (-168)] = 0b00000000101010001 << 15;
    ExpCode[255 + (169)] = 0b00000000101010010 << 15;
    ExpCode[255 + (-169)] = 0b00000000101010011 << 15;
    ExpCode[255 + (170)] = 0b00000000101010100 << 15;
    ExpCode[255 + (-170)] = 0b00000000101010101 << 15;
    ExpCode[255 + (171)] = 0b00000000101010110 << 15;
    ExpCode[255 + (-171)] = 0b00000000101010111 << 15;
    ExpCode[255 + (172)] = 0b00000000101011000 << 15;
    ExpCode[255 + (-172)] = 0b00000000101011001 << 15;
    ExpCode[255 + (173)] = 0b00000000101011010 << 15;
    ExpCode[255 + (-173)] = 0b00000000101011011 << 15;
    ExpCode[255 + (174)] = 0b00000000101011100 << 15;
    ExpCode[255 + (-174)] = 0b00000000101011101 << 15;
    ExpCode[255 + (175)] = 0b00000000101011110 << 15;
    ExpCode[255 + (-175)] = 0b00000000101011111 << 15;
    ExpCode[255 + (176)] = 0b00000000101100000 << 15;
    ExpCode[255 + (-176)] = 0b00000000101100001 << 15;
    ExpCode[255 + (177)] = 0b00000000101100010 << 15;
    ExpCode[255 + (-177)] = 0b00000000101100011 << 15;
    ExpCode[255 + (178)] = 0b00000000101100100 << 15;
    ExpCode[255 + (-178)] = 0b00000000101100101 << 15;
    ExpCode[255 + (179)] = 0b00000000101100110 << 15;
    ExpCode[255 + (-179)] = 0b00000000101100111 << 15;
    ExpCode[255 + (180)] = 0b00000000101101000 << 15;
    ExpCode[255 + (-180)] = 0b00000000101101001 << 15;
    ExpCode[255 + (181)] = 0b00000000101101010 << 15;
    ExpCode[255 + (-181)] = 0b00000000101101011 << 15;
    ExpCode[255 + (182)] = 0b00000000101101100 << 15;
    ExpCode[255 + (-182)] = 0b00000000101101101 << 15;
    ExpCode[255 + (183)] = 0b00000000101101110 << 15;
    ExpCode[255 + (-183)] = 0b00000000101101111 << 15;
    ExpCode[255 + (184)] = 0b00000000101110000 << 15;
    ExpCode[255 + (-184)] = 0b00000000101110001 << 15;
    ExpCode[255 + (185)] = 0b00000000101110010 << 15;
    ExpCode[255 + (-185)] = 0b00000000101110011 << 15;
    ExpCode[255 + (186)] = 0b00000000101110100 << 15;
    ExpCode[255 + (-186)] = 0b00000000101110101 << 15;
    ExpCode[255 + (187)] = 0b00000000101110110 << 15;
    ExpCode[255 + (-187)] = 0b00000000101110111 << 15;
    ExpCode[255 + (188)] = 0b00000000101111000 << 15;
    ExpCode[255 + (-188)] = 0b00000000101111001 << 15;
    ExpCode[255 + (189)] = 0b00000000101111010 << 15;
    ExpCode[255 + (-189)] = 0b00000000101111011 << 15;
    ExpCode[255 + (190)] = 0b00000000101111100 << 15;
    ExpCode[255 + (-190)] = 0b00000000101111101 << 15;
    ExpCode[255 + (191)] = 0b00000000101111110 << 15;
    ExpCode[255 + (-191)] = 0b00000000101111111 << 15;
    ExpCode[255 + (192)] = 0b00000000110000000 << 15;
    ExpCode[255 + (-192)] = 0b00000000110000001 << 15;
    ExpCode[255 + (193)] = 0b00000000110000010 << 15;
    ExpCode[255 + (-193)] = 0b00000000110000011 << 15;
    ExpCode[255 + (194)] = 0b00000000110000100 << 15;
    ExpCode[255 + (-194)] = 0b00000000110000101 << 15;
    ExpCode[255 + (195)] = 0b00000000110000110 << 15;
    ExpCode[255 + (-195)] = 0b00000000110000111 << 15;
    ExpCode[255 + (196)] = 0b00000000110001000 << 15;
    ExpCode[255 + (-196)] = 0b00000000110001001 << 15;
    ExpCode[255 + (197)] = 0b00000000110001010 << 15;
    ExpCode[255 + (-197)] = 0b00000000110001011 << 15;
    ExpCode[255 + (198)] = 0b00000000110001100 << 15;
    ExpCode[255 + (-198)] = 0b00000000110001101 << 15;
    ExpCode[255 + (199)] = 0b00000000110001110 << 15;
    ExpCode[255 + (-199)] = 0b00000000110001111 << 15;
    ExpCode[255 + (200)] = 0b00000000110010000 << 15;
    ExpCode[255 + (-200)] = 0b00000000110010001 << 15;
    ExpCode[255 + (201)] = 0b00000000110010010 << 15;
    ExpCode[255 + (-201)] = 0b00000000110010011 << 15;
    ExpCode[255 + (202)] = 0b00000000110010100 << 15;
    ExpCode[255 + (-202)] = 0b00000000110010101 << 15;
    ExpCode[255 + (203)] = 0b00000000110010110 << 15;
    ExpCode[255 + (-203)] = 0b00000000110010111 << 15;
    ExpCode[255 + (204)] = 0b00000000110011000 << 15;
    ExpCode[255 + (-204)] = 0b00000000110011001 << 15;
    ExpCode[255 + (205)] = 0b00000000110011010 << 15;
    ExpCode[255 + (-205)] = 0b00000000110011011 << 15;
    ExpCode[255 + (206)] = 0b00000000110011100 << 15;
    ExpCode[255 + (-206)] = 0b00000000110011101 << 15;
    ExpCode[255 + (207)] = 0b00000000110011110 << 15;
    ExpCode[255 + (-207)] = 0b00000000110011111 << 15;
    ExpCode[255 + (208)] = 0b00000000110100000 << 15;
    ExpCode[255 + (-208)] = 0b00000000110100001 << 15;
    ExpCode[255 + (209)] = 0b00000000110100010 << 15;
    ExpCode[255 + (-209)] = 0b00000000110100011 << 15;
    ExpCode[255 + (210)] = 0b00000000110100100 << 15;
    ExpCode[255 + (-210)] = 0b00000000110100101 << 15;
    ExpCode[255 + (211)] = 0b00000000110100110 << 15;
    ExpCode[255 + (-211)] = 0b00000000110100111 << 15;
    ExpCode[255 + (212)] = 0b00000000110101000 << 15;
    ExpCode[255 + (-212)] = 0b00000000110101001 << 15;
    ExpCode[255 + (213)] = 0b00000000110101010 << 15;
    ExpCode[255 + (-213)] = 0b00000000110101011 << 15;
    ExpCode[255 + (214)] = 0b00000000110101100 << 15;
    ExpCode[255 + (-214)] = 0b00000000110101101 << 15;
    ExpCode[255 + (215)] = 0b00000000110101110 << 15;
    ExpCode[255 + (-215)] = 0b00000000110101111 << 15;
    ExpCode[255 + (216)] = 0b00000000110110000 << 15;
    ExpCode[255 + (-216)] = 0b00000000110110001 << 15;
    ExpCode[255 + (217)] = 0b00000000110110010 << 15;
    ExpCode[255 + (-217)] = 0b00000000110110011 << 15;
    ExpCode[255 + (218)] = 0b00000000110110100 << 15;
    ExpCode[255 + (-218)] = 0b00000000110110101 << 15;
    ExpCode[255 + (219)] = 0b00000000110110110 << 15;
    ExpCode[255 + (-219)] = 0b00000000110110111 << 15;
    ExpCode[255 + (220)] = 0b00000000110111000 << 15;
    ExpCode[255 + (-220)] = 0b00000000110111001 << 15;
    ExpCode[255 + (221)] = 0b00000000110111010 << 15;
    ExpCode[255 + (-221)] = 0b00000000110111011 << 15;
    ExpCode[255 + (222)] = 0b00000000110111100 << 15;
    ExpCode[255 + (-222)] = 0b00000000110111101 << 15;
    ExpCode[255 + (223)] = 0b00000000110111110 << 15;
    ExpCode[255 + (-223)] = 0b00000000110111111 << 15;
    ExpCode[255 + (224)] = 0b00000000111000000 << 15;
    ExpCode[255 + (-224)] = 0b00000000111000001 << 15;
    ExpCode[255 + (225)] = 0b00000000111000010 << 15;
    ExpCode[255 + (-225)] = 0b00000000111000011 << 15;
    ExpCode[255 + (226)] = 0b00000000111000100 << 15;
    ExpCode[255 + (-226)] = 0b00000000111000101 << 15;
    ExpCode[255 + (227)] = 0b00000000111000110 << 15;
    ExpCode[255 + (-227)] = 0b00000000111000111 << 15;
    ExpCode[255 + (228)] = 0b00000000111001000 << 15;
    ExpCode[255 + (-228)] = 0b00000000111001001 << 15;
    ExpCode[255 + (229)] = 0b00000000111001010 << 15;
    ExpCode[255 + (-229)] = 0b00000000111001011 << 15;
    ExpCode[255 + (230)] = 0b00000000111001100 << 15;
    ExpCode[255 + (-230)] = 0b00000000111001101 << 15;
    ExpCode[255 + (231)] = 0b00000000111001110 << 15;
    ExpCode[255 + (-231)] = 0b00000000111001111 << 15;
    ExpCode[255 + (232)] = 0b00000000111010000 << 15;
    ExpCode[255 + (-232)] = 0b00000000111010001 << 15;
    ExpCode[255 + (233)] = 0b00000000111010010 << 15;
    ExpCode[255 + (-233)] = 0b00000000111010011 << 15;
    ExpCode[255 + (234)] = 0b00000000111010100 << 15;
    ExpCode[255 + (-234)] = 0b00000000111010101 << 15;
    ExpCode[255 + (235)] = 0b00000000111010110 << 15;
    ExpCode[255 + (-235)] = 0b00000000111010111 << 15;
    ExpCode[255 + (236)] = 0b00000000111011000 << 15;
    ExpCode[255 + (-236)] = 0b00000000111011001 << 15;
    ExpCode[255 + (237)] = 0b00000000111011010 << 15;
    ExpCode[255 + (-237)] = 0b00000000111011011 << 15;
    ExpCode[255 + (238)] = 0b00000000111011100 << 15;
    ExpCode[255 + (-238)] = 0b00000000111011101 << 15;
    ExpCode[255 + (239)] = 0b00000000111011110 << 15;
    ExpCode[255 + (-239)] = 0b00000000111011111 << 15;
    ExpCode[255 + (240)] = 0b00000000111100000 << 15;
    ExpCode[255 + (-240)] = 0b00000000111100001 << 15;
    ExpCode[255 + (241)] = 0b00000000111100010 << 15;
    ExpCode[255 + (-241)] = 0b00000000111100011 << 15;
    ExpCode[255 + (242)] = 0b00000000111100100 << 15;
    ExpCode[255 + (-242)] = 0b00000000111100101 << 15;
    ExpCode[255 + (243)] = 0b00000000111100110 << 15;
    ExpCode[255 + (-243)] = 0b00000000111100111 << 15;
    ExpCode[255 + (244)] = 0b00000000111101000 << 15;
    ExpCode[255 + (-244)] = 0b00000000111101001 << 15;
    ExpCode[255 + (245)] = 0b00000000111101010 << 15;
    ExpCode[255 + (-245)] = 0b00000000111101011 << 15;
    ExpCode[255 + (246)] = 0b00000000111101100 << 15;
    ExpCode[255 + (-246)] = 0b00000000111101101 << 15;
    ExpCode[255 + (247)] = 0b00000000111101110 << 15;
    ExpCode[255 + (-247)] = 0b00000000111101111 << 15;
    ExpCode[255 + (248)] = 0b00000000111110000 << 15;
    ExpCode[255 + (-248)] = 0b00000000111110001 << 15;
    ExpCode[255 + (249)] = 0b00000000111110010 << 15;
    ExpCode[255 + (-249)] = 0b00000000111110011 << 15;
    ExpCode[255 + (250)] = 0b00000000111110100 << 15;
    ExpCode[255 + (-250)] = 0b00000000111110101 << 15;
    ExpCode[255 + (251)] = 0b00000000111110110 << 15;
    ExpCode[255 + (-251)] = 0b00000000111110111 << 15;
    ExpCode[255 + (252)] = 0b00000000111111000 << 15;
    ExpCode[255 + (-252)] = 0b00000000111111001 << 15;
    ExpCode[255 + (253)] = 0b00000000111111010 << 15;
    ExpCode[255 + (-253)] = 0b00000000111111011 << 15;
    ExpCode[255 + (254)] = 0b00000000111111100 << 15;
    ExpCode[255 + (-254)] = 0b00000000111111101 << 15;
    ExpCode[255 + (255)] = 0b00000000111111110 << 15;
    ExpCode[255 + (-255)] = 0b00000000111111111 << 15;
    init = true;
}

std::string getExpCodeString(int value) {
    uint32_t expCode = getExpCode(value);
    std::string str = "";
    uint32_t shift_bit = 0x80000000;
    uint32_t count = 0;
    bool isZeroBits = true;
    while (isZeroBits || (count > 0)) {
        if ((expCode & shift_bit) == 0) {
            str.append("0");
            if (isZeroBits) {
                count++;
            } else {
                count--;
            }
        } else {
            if (isZeroBits) {
                isZeroBits = false;
            } else {
                count--;
            }
            str.append("1");
        }
        shift_bit = shift_bit >> 1;
    }
    return str;
}