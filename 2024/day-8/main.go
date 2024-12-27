package main

import (
	"fmt"
	"io"
	"math"
	"os"
	"sort"
	"strings"
)

type coordinate struct {
	r int
	c int
}

func main() {
	raw_data := read_input("input.txt")

	// process data

	lines := strings.Split(raw_data, "\n")
	fmt.Println("len = ", len(lines))
	n := len(lines) - 1
	m := len(lines[0])
	fmt.Println("n = ", n, " m = ", m)
	antena := make(map[rune][]coordinate)
	visited := make([][]bool, n)
	for i := 0; i < n; i += 1 {
		visited[i] = make([]bool, m)
	}

	for i, line := range lines {
		for j, char := range line {
			if char != '.' {
				if _, exits := antena[char]; !exits {
					antena[char] = []coordinate{}
				}
				c := coordinate{
					r: i,
					c: j,
				}
				antena[char] = append(antena[char], c)
			}
		}
	}

	for key, _ := range antena {
		fmt.Printf("%c ", key)
		sort.Slice(antena[key], func(i, j int) bool {
			if antena[key][i].r != antena[key][j].r {
				return antena[key][i].r < antena[key][j].r
			} else {
				return antena[key][i].c < antena[key][j].c
			}
		})
		fmt.Println(antena[key])
	}

	// part 1
	res := 0
	for _, arr := range antena {
		for i := 0; i < len(arr); i += 1 {
			for j := i + 1; j < len(arr); j += 1 {
				res += arr[i].count_antinodes(arr[j], visited, n, m)
			}
		}
	}

	fmt.Println("part 1 ", res)
	// part 2
	for i := 0; i < n; i += 1 {
		for j := 0; j < m; j += 1 {
			visited[i][j] = false
		}
	}
	res = 0

	for _, arr := range antena {
		if len(arr) > 0 {
			for _, c := range arr {
				res += 1
				visited[c.r][c.c] = true
			}
		}
	}
	for _, arr := range antena {
		for i := 0; i < len(arr); i += 1 {
			for j := i + 1; j < len(arr); j += 1 {
				res += arr[i].count_antinodes_harmonic(arr[j], visited, n, m)
			}
		}
	}
	fmt.Println("part 2 ", res)

}

func read_input(file_name string) string {
	f, err := os.Open(file_name)

	if err != nil {
		panic(err)
	}

	defer func() {
		if err := f.Close(); err != nil {
			panic(err)
		}
	}()

	b, err := io.ReadAll(f)

	if err != nil {
		panic(err)
	}

	return string(b)
}

func (c1 coordinate) count_antinodes(c2 coordinate, visited [][]bool, n, m int) int {
	if c1.r == c2.r && c1.c == c2.c {
		return 0
	}

	diff_r := int(math.Abs(float64(c1.r - c2.r)))
	diff_c := int(math.Abs(float64(c1.c - c2.c)))

	var res_r_1, res_c_1, res_r_2, res_c_2 int

	res_r_1 = c1.r - diff_r
	res_r_2 = c2.r + diff_r
	if c1.r == c2.r {
		res_c_1 = c1.c - diff_c
		res_c_2 = c2.c + diff_c
	} else if c1.c < c2.c {
		res_c_1 = c1.c - diff_c
		res_c_2 = c2.c + diff_c
	} else {
		res_c_1 = c1.c + diff_c
		res_c_2 = c2.c - diff_c
	}
	count := 0
	if res_r_1 >= 0 && res_r_1 < n && res_c_1 >= 0 && res_c_1 < m {
		if !visited[res_r_1][res_c_1] {
			count += 1
		}
		visited[res_r_1][res_c_1] = true
	}
	if res_r_2 >= 0 && res_r_2 < n && res_c_2 >= 0 && res_c_2 < m {
		if !visited[res_r_2][res_c_2] {
			count += 1
		}
		visited[res_r_2][res_c_2] = true
	}
	//	fmt.Println("given ", c1.r, "-", c1.c, " and ", c2.r, "-", c2.c)
	//	fmt.Println("get ", res_r_1, "-", res_c_1, " and ", res_r_2, "-", res_c_2)
	//	fmt.Println("n = ", n, " m = ", m, " get count  = ", count)
	return count
}

func (c1 coordinate) count_antinodes_harmonic(c2 coordinate, visited [][]bool, n, m int) int {
	if c1.r == c2.r && c1.c == c2.c {
		return 0
	}

	diff_r := int(math.Abs(float64(c1.r - c2.r)))
	diff_c := int(math.Abs(float64(c1.c - c2.c)))
	count := 0
	var res_r_1, res_c_1, res_r_2, res_c_2 int

	res_r_1 = c1.r - diff_r
	res_r_2 = c2.r + diff_r
	if c1.r == c2.r {
		res_c_1 = c1.c - diff_c
		res_c_2 = c2.c + diff_c
	} else if c1.c < c2.c {
		res_c_1 = c1.c - diff_c
		res_c_2 = c2.c + diff_c
		for res_r_1 >= 0 && res_c_1 >= 0 {
			if !visited[res_r_1][res_c_1] {
				count += 1
			}
			visited[res_r_1][res_c_1] = true
			res_r_1 -= diff_r
			res_c_1 -= diff_c
		}

		for res_r_2 < n && res_c_2 < m {
			if !visited[res_r_2][res_c_2] {
				count += 1
			}
			visited[res_r_2][res_c_2] = true
			res_r_2 += diff_r
			res_c_2 += diff_c
		}
	} else {
		res_c_1 = c1.c + diff_c
		res_c_2 = c2.c - diff_c
		for res_r_1 >= 0 && res_c_1 < m {
			if !visited[res_r_1][res_c_1] {
				count += 1
			}
			visited[res_r_1][res_c_1] = true
			res_r_1 -= diff_r
			res_c_1 += diff_c
		}

		for res_r_2 < n && res_c_2 >= 0 {
			if !visited[res_r_2][res_c_2] {
				count += 1
			}
			visited[res_r_2][res_c_2] = true
			res_r_2 += diff_r
			res_c_2 -= diff_c
		}
	}
	//	fmt.Println("given ", c1.r, "-", c1.c, " and ", c2.r, "-", c2.c)
	//	fmt.Println("get ", res_r_1, "-", res_c_1, " and ", res_r_2, "-", res_c_2)
	//	fmt.Println("n = ", n, " m = ", m, " get count  = ", count)
	return count
}
