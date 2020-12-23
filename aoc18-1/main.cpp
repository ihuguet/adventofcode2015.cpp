#include <iostream>
#include <string>
#include <vector>

constexpr int STEPS_NUM = 100;

std::vector<std::vector<bool>> parse_grid (std::istream &input);
std::vector<std::vector<bool>> empty_grid(int rows, int cols);
int count_neighbours_on(const std::vector<std::vector<bool>> &grid, int row, int col);

int main () {
    std::istream &input = std::cin;

    auto grid = parse_grid(input);
    for (int i = 0; i < STEPS_NUM; i++) {
        std::vector<std::vector<bool>> grid_new = empty_grid(grid.size(), grid[0].size());

        for (int y = 0; y < grid.size(); y++) { 
            for (int x = 0; x < grid[y].size(); x++) {
                int neighbour_on_cnt = count_neighbours_on(grid, y, x);
                if (grid[y][x])
                    grid_new[y][x] = neighbour_on_cnt == 2 || neighbour_on_cnt == 3;
                else
                    grid_new[y][x] = neighbour_on_cnt == 3;
            }
        }
        grid = std::move(grid_new);
    }

    int cnt = 0;
    for (auto &row : grid) {
        for (auto col : row) {
            if (col)
                cnt++;
        }
    }

    std::cout << "Lights ON = " << cnt << std::endl;
    return 0;
}

std::vector<std::vector<bool>> parse_grid(std::istream &input) {
    std::vector<std::vector<bool>> grid;

    std::string line;
    while (std::getline(input, line)) {
        auto &row = grid.emplace_back();
        for (char ch : line)
            row.push_back(ch == '#');
    }

    return grid;
}

std::vector<std::vector<bool>> empty_grid(int rows, int cols) {
    std::vector<std::vector<bool>> grid(rows, std::vector<bool>(cols));
    return grid;
}

int count_neighbours_on(const std::vector<std::vector<bool>> &grid, int row, int col) {
    int row_ini = std::max(row - 1, 0);
    int row_end = std::min(row + 1, static_cast<int>(grid[0].size()) - 1);
    int col_ini = std::max(col - 1, 0);
    int col_end = std::min(col + 1, static_cast<int>(grid.size()) - 1);

    int cnt = 0;
    for (int y = row_ini; y <= row_end; y++) {
        for (int x = col_ini; x <= col_end; x++) {
            if (grid[y][x] && (y != row || x != col))
                cnt++;
        }
    }
    return cnt;
}