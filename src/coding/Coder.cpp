//
// Created by sfaxi19 on 28.12.17.
//
#include <AVIMaker/AVIMaker.h>
#include <Blocks.hpp>
#include <coding/BitStream/BitStreamIO.hpp>
#include "Coder.hpp"
#include "bmp_lib/bmp.h"
#include "motion_compensation/motion_compensation.h"
#include "Scanning.hpp"
#include "common/global.hpp"
#include "Binarization.hpp"
#include "DCT.hpp"
#include "CabacFsm.hpp"
#include "Quantization.hpp"

inline int sign(int x) {
    return (x >= 0) ? 1 : -1;
}


void mark_range(TRIPLERGB **frame, int x, int y, int h, int w, int component) {
    for (int i = y; i < y + h; i++)
        setComponent((TRIPLEBYTES **) frame, i, x, 255, component);//frame[i][x].red = 255;
    for (int i = y; i < y + h; i++)
        setComponent((TRIPLEBYTES **) frame, i, x + w - 1, 255, component); //frame[i][x + w - 1].red = 255;
    for (int i = x; i < x + w; i++)
        setComponent((TRIPLEBYTES **) frame, y, i, 255, component); //frame[y][i].red = 255;
    for (int i = x; i < x + w; i++)
        setComponent((TRIPLEBYTES **) frame, y + h - 1, i, 255, component); //frame[y + h - 1][i].red = 255;
}


void mark_range(TRIPLERGB **frame, mc::block_info bi, int component) {
    mark_range(frame, (int) bi.x, (int) bi.y, (int) bi.height, (int) bi.width, component);
}

void print_block(double block[][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%8.2f", block[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_block2x2(const char *title, double **block) {
    printf("%s\n", title);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%8.2f", block[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

std::string block_to_string(double **block) {
    std::string binStr = "";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%8.2f", block[i][j]);
        }
    }
    printf("\n");
}

void print_block(TRIPLEYCbCr **frame, int x, int y, int h, int w) {
    for (int i = y; i < y + h; i++) {
        for (int j = x; j < x + w; j++) {
            printf("%8d", frame[i][j].Y);
        }
        printf("\n");
    }
    printf("\n");
}

void print_block(TRIPLEYCbCr **frame, mc::block_info bi) {
    print_block(frame, (int) bi.x, (int) bi.y, (int) bi.height, (int) bi.width);
}

void block_from_frame(int **block, TRIPLEYCbCr **frame, mc::block_info block_info, int component) {
    for (int i = 0; i < 4; i++) {
        block[i] = new int[4];
        for (int j = 0; j < 4; j++) {
            block[i][j] = getComponent((TRIPLEBYTES **) frame, block_info.y + i, block_info.x + j, component);
            //frame[block_info.y + i][block_info.x + j].Y;
        }
    }
}

void block4x4_from_16x16(int **block, int block16x16[16][16], size_t hIdx, size_t wIdx) {
    for (size_t i = 0; i < 4; i++) {
        block[i] = new int[4];
        for (size_t j = 0; j < 4; j++) {
            block[i][j] = block16x16[hIdx + i][wIdx + j];
        }
    }
}

/*
void
subtract_to_16x16_block(TRIPLEYCbCr **base, TRIPLEYCbCr **target, double **block, mc::block_info block_info,
                        mc::vect v) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            block[i][j] = target[block_info.y + i][block_info.x + j].Y -
                          base[block_info.y + v.y + i][block_info.x + v.x + j].Y;
        }
    }
}

void
subtract_to_4x4_block(TRIPLEYCbCr **base, TRIPLEYCbCr **target, double **block, mc::block_info block_info, mc::vect v) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            block[i][j] = target[block_info.y + i][block_info.x + j].Y -
                          base[block_info.y + v.y + i][block_info.x + v.x + j].Y;
        }
    }
}

void
addition_to_4x4_block(TRIPLEYCbCr **base, double **block, mc::block_info block_info, mc::vect v) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            block[i][j] = block[i][j] + base[block_info.y + v.y + i][block_info.x + v.x + j].Y;
        }
    }
}
*/
uint8_t getBit(char ch) {
    return static_cast<uint8_t>((ch == '1') ? 1 : 0);
}

void getFreq(int *freq, double **block) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if ((i == 0) && (j == 0)) continue;
            freq[256 + (int) block[i][j]]++;
        }
    }
}

double blockEntropy(const int freq[], int len, int N) {
    double sum = 0;
    double p = 0;
    for (int i = 0; i < len; i++) {
        p = ((double) freq[i] / N);
        if (p == 0) continue;
        sum += p * log2(p);
    }
    return sum * (-1);
}

/*
 * 1) dc_level
 * 2) dc4x4
 * 3) block4x4(i) i = 1..16
 */


void subtract_to_16x16block(TRIPLEYCbCr **base, TRIPLEYCbCr **target, int tmpBlock[16][16], mc::block_info block,
                            mc::vect v, int component) {
    for (int i = 0; i < block.height; i++) {
        for (int j = 0; j < block.width; j++) {
            tmpBlock[block.y + i][block.x + j] = clip(
                    getComponent((TRIPLEBYTES **) target, block.y + i, block.x + j, component)
                    - getComponent((TRIPLEBYTES **) base, block.y + v.y + i, block.x + v.x + j, component),
                    0,
                    255);
        }
    }
}


int QS = 28;

void macroblock_decoding(TRIPLEYCbCr **base, mc::block_info &block16x16info, MacroblockInfo *mb_res) {
    LOG(MAIN, "%s(base=%p, x=%lu, y=%lu, w=%lu h=%lu)", __FUNCTION__, base,
        block16x16info.x, block16x16info.y,
        block16x16info.width, block16x16info.height);
    size_t block_size = 4;
    size_t blocks_in_width = block16x16info.width / block_size;
    size_t blocks_in_height = block16x16info.height / block_size;

    int **pToDC_block = mb_res->dc_block;

    /****************************************************
     *              IQuantization DC block
     ****************************************************/
    iquant_block(pToDC_block, QS);
    /****************************************************
     *                  IDCT DC block
     ****************************************************/
    pToDC_block[0][0] = mb_res->dc_level;
    idct(pToDC_block);

    for (size_t i = 0; i < blocks_in_height; i++) {
        for (size_t j = 0; j < blocks_in_width; j++) {
            int **pToBlock = mb_res->block[i][j];
            //mc::block_info block4x4info(block16x16info.x + j * block_size, block16x16info.y + i * block_size, 4, 4);
            //block_from_frame(pToBlock, frame, block4x4info, COMPONENT_Y);
            /****************************************************
             *              IQuantization residual 4x4
             ****************************************************/
            iquant_block(pToBlock, QS);
            /****************************************************
             *                  IDCT residual 4x4
             ****************************************************/
            pToBlock[0][0] = pToDC_block[i][j];
            idct(pToBlock);
            //print_block(target, blockInfo1);
            //print_block("Result:", block);
        }
    }
}

BITMAPINFOHEADER bmInfo;
BITMAPFILEHEADER bmFile;

void frame_decoding(TRIPLEYCbCr **base, TRIPLEYCbCr **target, size_t defWidth, size_t defHeight, BitStream &bitStream) {
    LOG(MAIN, "%s(w=%lu, h=%lu)", __FUNCTION__, defWidth, defHeight);
    size_t block_size = 16;
    size_t blocks_in_width = defWidth / block_size;
    size_t blocks_in_height = defHeight / block_size;
    FrameInfo frameInfo(defHeight, defWidth);
    frameInfo.fromBitStream(bitStream);
    static int frameIdx = 0;
    int idx = 0;
    for (int component = COMPONENT_Y; component <= COMPONENT_CR; component++) {
        bool first_flag = true;
        int dc_prev = 0;
        for (size_t i = 0; i < blocks_in_height; i++) {
            for (size_t j = 0; j < blocks_in_width; j++) {
                MacroblockInfo *mb_res = frameInfo.macroblocks[idx];
                mc::block_info block16x16info(j * block_size, i * block_size, block_size, block_size);
                if (first_flag) {
                    first_flag = false;
                } else {
                    mb_res->dc_level = mb_res->dc_level + dc_prev;
                }
                dc_prev = mb_res->dc_level;

                mb_res->dc_level = mb_res->dc_level * 8;
                //mb_res->dc_level = mb_res->dc_level * 8;
                //if (idx == 200) frameInfo.macroblocks[idx]->print();

                macroblock_decoding(base, block16x16info, mb_res);
                /****************************************************
                *                 Addition macroblock
                ****************************************************/
                //addition_to_4x4_block(base, pToBlock, block4x4info, v);
                //decFrameInfo.macroblocks.push_back(mb_res);
                if (mb_res->mb_type == P) {
                    //addition_to_frame(target, mb_res, block16x16info);
                }
                idx++;
            }
            //if (bitStream.isEnd()) break;
        }
    }
    LOG(INFO, "\n%s", frameInfo.toString().c_str());
    frameInfo.saveFrame(bmFile, bmInfo, "decode/in" + std::to_string(frameIdx++) + ".bmp");
}


// pushBits
// readBits

void decoding(AVIMaker &aviMaker, BitStream &bitStream) {
    LOG(MAIN, "%s()", __FUNCTION__);
    system("mkdir -p decode");
    bitStream.readReset();
    size_t h = aviMaker.video()->height();
    size_t w = aviMaker.video()->width();
    TRIPLEYCbCr **base = nullptr;
    TRIPLEYCbCr **target = new TRIPLEYCbCr *[h];
    for (int i = 0; i < h; i++) {
        target[i] = new TRIPLEYCbCr[w];
    }
    while (!bitStream.isEnd()) {
        //read frame info
        frame_decoding(base, target, w, h, bitStream);
        //aviMaker.addFrame(0, (TRIPLERGB **) target);
        //break;
        // LOG(INFO, "%d", bit);
    }
    LOG(INFO, "RESULT: %s", bitStream.toString(150).c_str());

    //LOG(INFO, "Encode Size: %lu", encFrameInfo.macroblocks.size());
    //LOG(INFO, "Decode Size: %lu", decFrameInfo.macroblocks.size());

    /*int not_equale = 0;
    for (int i = 0; i < encFrameInfo.macroblocks.size(); i++) {
        MacroblockInfo *mb_info1 = encFrameInfo.macroblocks[i];
        MacroblockInfo *mb_info2 = decFrameInfo.macroblocks[i];
        if (!mb_info1->equale(mb_info2)) {
            mb_info1->print();
            mb_info2->print();
            not_equale++;
            LOG(WARN, "Not Equale!");
        }
    }
    LOG(INFO, "Not equale count: %d", not_equale);
    */
}

int
macroblock_coding(TRIPLEYCbCr **base, TRIPLEYCbCr **target, mc::block_info &block16x16info, int frame_type,
                  MacroblockInfo *mb_res, int component) {
    LOG(MAIN, "%s(target=%p, x=%lu, y=%lu, w=%lu h=%lu)", __FUNCTION__, target,
        block16x16info.x, block16x16info.y,
        block16x16info.width, block16x16info.height);
    size_t block_size = 4;
    size_t blocks_in_width = block16x16info.width / block_size;
    size_t blocks_in_height = block16x16info.height / block_size;
    int tmp16x16block[16][16] = {0};
    if ((base) && (frame_type == P)) {
        mc::vect v = mc::logarithmicSearch(base, target, 20, 20, block16x16info);
        subtract_to_16x16block(base, target, tmp16x16block, block16x16info, v, component);
        mb_res->mb_type = P;
        mb_res->v = v;
    } else {
        mb_res->mb_type = I;
    }

    int **pToDC_block = mb_res->dc_block;

    for (size_t i = 0; i < blocks_in_height; i++) {
        for (size_t j = 0; j < blocks_in_width; j++) {
            int **pToBlock = mb_res->block[i][j];
            if (mb_res->mb_type == I) {
                mc::block_info block4x4pos(block16x16info.x + j * block_size, block16x16info.y + i * block_size, 4, 4);
                block_from_frame(pToBlock, target, block4x4pos, component);
            } else {
                block4x4_from_16x16(pToBlock, tmp16x16block, i * block_size, j * block_size);
            }
            //print_block("CODE_BLOC: ", pToBlock);
            /****************************************************
             *                  DCT residual 4x4
             ****************************************************/
            pToDC_block[i][j] = dct(pToBlock);
            /****************************************************
             *              Quantization residual 4x4
             ****************************************************/
            quant_block(pToBlock, QS);
        }
    }
    /****************************************************
     *                  DCT DC block
     ****************************************************/
    int dc = dct(pToDC_block);
    pToDC_block[0][0] = 0;
    /****************************************************
     *              Quantization DC block
     ****************************************************/
    quant_block(pToDC_block, QS);
    return dc;
}

void frame_coding(TRIPLEYCbCr **base, TRIPLEYCbCr **target, size_t frameWidth, size_t frameHeight,
                  BitStream &bitStream) {
    LOG(MAIN, "%s(base=%p, target=%p, w=%lu, h=%lu)", __FUNCTION__, base, target, frameWidth, frameHeight);
    size_t block_size = 16;
    size_t blocks_in_width = frameWidth / block_size;
    size_t blocks_in_height = frameHeight / block_size;

    FrameInfo frameInfo(frameHeight, frameWidth);
    frameInfo.frame_type = (base == nullptr) ? I : P;
    for (int component = COMPONENT_Y; component <= COMPONENT_CR; component++) {
        bool first_flag = true;
        int dc_prev = 0;
        for (size_t i = 0; i < blocks_in_height; i++) {
            for (size_t j = 0; j < blocks_in_width; j++) {
                MacroblockInfo *mb_res = new MacroblockInfo;
                mc::block_info block16x16pos(j * block_size, i * block_size, block_size, block_size);

                int dc = macroblock_coding(base, target, block16x16pos, frameInfo.frame_type, mb_res, component);
                mb_res->dc_level = dc / 8;

                if (first_flag) {
                    first_flag = false;
                } else {
                    mb_res->dc_level = mb_res->dc_level - dc_prev;
                }
                dc_prev = dc / 8;
                //LOG(INFO, "dc=%d -> dc'=%d", dc, mb_res->dc_level);
                frameInfo.macroblocks.push_back(mb_res);
            }
        }
    }
    frameInfo.toBitStream(bitStream);
    LOG(INFO, "\n%s", frameInfo.toString().c_str());
}

void transform_test(VideoStream *video) {
    TRIPLEYCbCr **target = RGB2YCbCr(video->getFrame(0), video->height(), video->width());
    mc::block_info blockInfo1(100, 100, 4, 4);
    mc::block_info blockInfo2(120, 124, 4, 4);
    mc::block_info blockInfo3(124, 120, 4, 4);
    mc::block_info blockInfo4(124, 124, 4, 4);
    int **block = new int *[4];
    for (int i = 0; i < 4; i++) {
        block[i] = new int[4];
    }

    int **dc = new int *[2];
    for (int i = 0; i < 2; i++) {
        dc[i] = new int[2];
    }


    /****************************************************
     *                  Read block
     ****************************************************/
    block_from_frame(block, target, blockInfo1, COMPONENT_Y);
    //mc::vect v = mc::logarithmicSearch(base, target, 20, 20, blockInfo1);
    //subtract_to_4x4_block(base, target, block, blockInfo1, v);
    print_block("BLOCK1:", block);
    /****************************************************
     *                     DCT
     ****************************************************/
    dc[0][0] = dct(block);
    print_block("DCT:", block);
    /****************************************************
     *                   Quantization
     ****************************************************/
    //int QS = 22;
    quant_block(block, QS);
    print_block("QUANT:", block);
    /****************************************************
     *                  Check Entropy
     ****************************************************/
    //int freq[512] = {0};
    //getFreq(freq, block);
    //LOG(INFO, "H = %f", blockEntropy(freq, 512, 15) * 15);
    /****************************************************
     *                  IQuantization
     ****************************************************/
    iquant_block(block, QS);
    print_block("IQUANT:", block);
    /****************************************************
     *                      IDCT
     ****************************************************/
    block[0][0] = dc[0][0];
    idct(block);
    print_block("IDCT:", block);

}

void coding(AVIMaker &aviMaker, BitStream &bitStream) {
    VideoStream *video = aviMaker.videoStreams[0]; //video();
    bmInfo = video->bmInfo();
    bmFile = video->bmFile();
    const size_t defHeight = video->height();
    const size_t defWidth = video->width();
    TRIPLEYCbCr **base = nullptr;
    TRIPLEYCbCr **target = nullptr;
    for (int i = 0; i < video->getLength(); i++) {
        if (i != 0) base = RGB2YCbCr(video->getFrame(i - 1), video->height(), video->width());
        target = RGB2YCbCr(video->getFrame(i), video->height(), video->width());
        frame_coding(nullptr, target, defWidth, defHeight, bitStream);
    }


    LOG(INFO, "RESULT: %s", bitStream.toString(150).c_str());

    return;

    transform_test(video);

    /*size_t block_size = 16;
    size_t blocks_in_width = defWidth / block_size;
    size_t blocks_in_height = defHeight / block_size;
    for (size_t i = 0; i < blocks_in_height; i++) {
        for (size_t j = 0; j < blocks_in_width; j++) {
            mc::block_info blockInfo(j * block_size, i * block_size, block_size, block_size);
            mark_range(video->getFrame(8), blockInfo, COMPONENT_A);
        }
    }*/
    //TRIPLEYCbCr **out = new TRIPLEYCbCr *[video->height()];
    //for (int i = 0; i < video->height(); i++) {
    //    out[i] = new TRIPLEYCbCr[video->width()];
    //}

    //print_block(frame1, posX, posY, 4, 4);
    //print_block(frame2, posX + v.x, posY + v.y, 4, 4);
    //subtract_block(frame1, frame2, m_enc, block_info, v);
    //subtract_to_4x4_block(frame1, frame1, block, block_info, v);
    //size_t block_size = 16;
    //size_t blocks_in_width = defWidth / block_size;
    //size_t blocks_in_height = defHeight / block_size;
    /*for (size_t i = 0; i < blocks_in_height; i++) {
        for (size_t j = 0; j < blocks_in_width; j++) {
            //        mark_range(video->getFrame(8), blockInfo, COMPONENT_A);

            mc::block_info blockInfo(j * block_size, i * block_size, block_size, block_size);
            mc::vect v = mc::logarithmicSearch(base, target, 20, 20, blockInfo);
            //mc::subtract_block(base, target, target, blockInfo, v);
        }
    }
     */
    //save_component_to_files((TRIPLEBYTES **) target, video->bmFile(), video->bmInfo(), COMPONENT_A, "out.bmp");

    /****************************************************
     *                  Addition block
     ****************************************************/
    //addition_to_4x4_block(base, block, blockInfo1, v);
    //print_block(target, blockInfo1);
    //print_block("Result:", block);
    /*
    block_from_frame(block, frame1, blockInfo2);
    print_block("BLOCK2:", block);
    dc[0][1] = dct(block);
    block_from_frame(block, frame1, blockInfo3);
    print_block("BLOCK3:", block);
    dc[1][0] = dct(block);
    block_from_frame(block, frame1, blockInfo4);
    print_block("BLOCK4:", block);
    dc[1][1] = dct(block);
*/
    //print_block2x2("DC:", dc);
    /*
    LOG(INFO, "dc1=%f", dc);
    dc = dc1 - dc2;
    LOG(INFO, "dc2=%f", dc);
    dc = dc2 - dc3;
    LOG(INFO, "dc3=%f", dc);
    dc = dc3 - dc4;
    LOG(INFO, "dc4=%f", dc);*/
    //print_block("BLOCK", block);
    //print_block("DCT:", block);
    //Block4x4Layout block4x4Layout(frame1, 120, 120);

    //LOG(INFO, "\n%s", block4x4.toString("BLOCK:").c_str());

    /*
    uint32_t id2 = timer_start();
    for(int i=0; i<1000000; i++) {
        Block4x4_float block4x4(block4x4Layout);
        dct(block4x4);
    }
    timer_stop_us(id2);
    */
    //LOG(INFO, "\n%s", block4x4Layout.toString().c_str());



    //LOG(INFO, "\n%s", block4x4.toString("DCT:").c_str());


    /*
    int QS = 9;

    quant_block(block, QS);
    print_block("QUANT:", block);

    std::string data = "";

    Scanning scan(Scanning::ZIG_ZAG);
    while (!scan.stop()) {
        mc::pos pos = scan.nextStep();
        data.append(getExpCodeString((uint32_t) block[pos.y][pos.x]));
        LOG(INFO, "%3d - %s", (int) block[pos.y][pos.x], getExpCodeString((uint32_t) block[pos.y][pos.x]).c_str());
    }

    int freq[512] = {0};
    getFreq(freq, block);
    LOG(INFO, "H = %f", blockEntropy(freq, 512, 15) * 15);
    for (uint8_t m = 0; m < 2; m++) {
        for (uint16_t i = 0; i < 63; i++) {
            uint8_t MPS = m;
            uint16_t stateIdx = i;
            CabacFsm cabac(MPS, stateIdx);
            for (int i = 0; i < data.size(); i++) {
                cabac.encodingEngine(getBit(data[i]));
            }
            cabac.terminateEncode(1);
            LOG(INFO, "MPS: %d,\tstateIdx: %d\tSize: %lu", MPS, stateIdx, cabac.getEncode().size());
        }
    }
    //

    //CabacFsm cabacDecode(MPS, stateIdx, cabac.getEncode());
    //for (int i = 0; i < data.size(); i++) {
    //    cabacDecode.decodingEngine();
    //}
    //
    //cabacDecode.terminateDecode();


    LOG(INFO, "Input data:  %s\t(%lu bits)", data.c_str(), data.size());
    */
    //LOG(INFO, "Encode data: %s\t(%lu bits)", cabac.getEncode().c_str(), cabac.getEncode().size());
    /*if (data == cabacDecode.getDecode()) {
        LOG(INFO, ANSI_COLOR_GREEN
                "Decode data: %s", cabacDecode.getDecode().c_str());
    } else {
        LOG(INFO, ANSI_COLOR_RED
                "Decode data: %s", cabacDecode.getDecode().c_str());
    }*/

    /*
    iquant_block(block, QS);
    print_block("IQUANT:", block);


    idct(block);
    print_block("IDCT:", block);
*/
}
