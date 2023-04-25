#ifndef FRAMES_H
#define FRAMES_H

#include <vector>
#include <string>

using dino_matrix_t =   std::vector<std::string>;
using cactus_matrix_t = std::vector<std::string>;
namespace Frames
{
    namespace Dino
    {
        inline const dino_matrix_t dino1
        {
            "    ___    ",
            "   | *  00|",
            "    | >    ",
            "\\____      ",
            "    | \\    "
        };


        inline const dino_matrix_t dino2
        {
            "    ___    ",
            "   | *  00|",
            "    | >    ",
            "\\____      ",
            "    | |    "
        };


        inline const dino_matrix_t dino3
        {
            "    ___    ",
            "   | *  00|",
            "    | >    ",
            "\\____      ",
            "    / |    "
        };

        inline const dino_matrix_t dinoCrouch
        {
            "    ___    ",
            "   | *  00|",
            "\\____ >     ",
            "    / |    "
        };
    }

    namespace Cactus
    {
        inline const cactus_matrix_t cactus
        {
            "    __     ",
            "   /  \\    ",
            "|  |  |    ",
            " \\=\\   ==0 ",
            "   \\  |    ",
            "    |  |   ",
            "  ________ ",
        };

        inline const cactus_matrix_t cactus2
        {
            "      __   ",
            "     \\ |   ",
            "     |  |  ",
            "    8   () ",
            "  () \\|    ",
            "    |  |   ",
            "  ________ ",
        };

        inline const cactus_matrix_t cactus3
        {
            "     WW    ",
            "   \\  //   ",
            "    |  |   ",
            "  ________ ",
        };

        inline const cactus_matrix_t cactus4
        {
            "           ",
            "    __     ",
            "   |  |    ",
            "  C    D   ",
            "   \\  |    ",
            "    |  |   ",
            "  ________ ",
        };

    }

}

#endif
