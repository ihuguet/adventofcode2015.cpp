#include <iostream>
#include <vector>


static constexpr int MIN_PRESENTS = 34'000'000; // puzzle input


static unsigned int find_lowest_conforming_house(
    unsigned int max_visited_houses_per_elf,
    unsigned int mult_presents_per_elf);

int main () {
    std::cout << "Part1: Lowest hous Num with at least " << MIN_PRESENTS << " presents: "
              << find_lowest_conforming_house(MIN_PRESENTS, 10) << std::endl;
    std::cout << "Part2: Lowest hous Num with at least " << MIN_PRESENTS << " presents: "
              << find_lowest_conforming_house(50, 11) << std::endl;
    return 0;
}

static unsigned int find_lowest_conforming_house(
    unsigned int max_visited_houses_per_elf,
    unsigned int mult_presents_per_elf)
{
    std::vector<unsigned int> presents_sum(MIN_PRESENTS, 0);
    
    size_t lowest_conforming_house = MIN_PRESENTS - 1;

    for (size_t i = 0; i < lowest_conforming_house; i++) {
        unsigned int elf_num = i + 1;
        size_t cnt_houses = max_visited_houses_per_elf;

        for (size_t j = i; cnt_houses > 0 && j < lowest_conforming_house; j += elf_num) {
            presents_sum[j] += mult_presents_per_elf * elf_num;
            cnt_houses--;

            if (presents_sum[j] >= MIN_PRESENTS) {
                lowest_conforming_house = j;
                break;
            }
        }
    }

    return lowest_conforming_house + 1;
}
