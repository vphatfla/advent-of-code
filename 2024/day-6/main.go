package main

import (
	"fmt"
	"io"
	"os"
	"strings"
)

var direction [][]int

func main() {
	raw_data := read_input("input.txt")
	raw_data = strings.Replace(raw_data, `\n`, "", -1)
	raw_matrix := strings.Split(raw_data, "\n")
	n := len(raw_matrix) - 1
	m := len(raw_matrix[0])

	matrix := make([][]byte, n)
	fmt.Println("n = ", n, " m = ", m)

	for i := range n {
		matrix[i] = make([]byte, m)
		for j := range m {
			matrix[i][j] = raw_matrix[i][j]
		}
	}

	for i := range n {
		for j := range m {
			fmt.Printf("%c", matrix[i][j])
		}
		fmt.Println("")
	}

	direction = [][]int{
		{-1, 0}, // up
		{0, 1},  // right
		{1, 0},  // down
		{0, -1}, // left
	}

	start_r := 0
	start_c := 0

	for i := range n {
		for j := range m {
			if matrix[i][j] == '^' {
				start_r = i
				start_c = j
				break
			}
		}
	}

	// part 1
	res := 1

	res += unique_visit(matrix, n, m, start_r, start_c, 0)

	fmt.Println("Part 1 ", res)

	// part 2

	res = 0

	for i := range n {
		for j := range m {
			if matrix[i][j] == '^' || matrix[i][j] == '#' {
				continue
			}
			matrix[i][j] = '#'
			if detect_loop(matrix, n, m, start_r, start_c, 0) {
				res += 1
			}
			matrix[i][j] = '.'
		}
	}

	fmt.Println("Part 2 ", res)
}

func unique_visit(matrix [][]byte, n, m, r, c, dir_index int) int {
	count := 0

	if matrix[r][c] == '.' {
		count = 1
		matrix[r][c] = 'X'
	}

	next_r := r + direction[dir_index][0]
	next_c := c + direction[dir_index][1]

	if !is_in_bound(n, m, next_r, next_c) {
		for i := range n {
			for j := range m {
				fmt.Printf("%c", matrix[i][j])
			}
			fmt.Println("")
		}
		return count
	}

	for matrix[next_r][next_c] == '#' {
		dir_index = (dir_index + 1) % 4
		next_r = r + direction[dir_index][0]
		next_c = c + direction[dir_index][1]
	}

	return count + unique_visit(matrix, n, m, next_r, next_c, dir_index)
}

func detect_loop(matrix [][]byte, n, m, r, c, dir_index int) bool {
	for i := 0; i < 1000000; i += 1 {
		next_r, next_c, next_dir := traverse(matrix, n, m, r, c, dir_index)
		if next_r == -99 && next_c == -99 {
			return false
		} else if next_r == -1 && next_c == -1 {
			return true
		} else {
			r = next_r
			c = next_c
			dir_index = next_dir
		}
	}
	return true
}

func traverse(matrix [][]byte, n, m, r, c, dir_index int) (int, int, int) {

	next_r := r + direction[dir_index][0]
	next_c := c + direction[dir_index][1]

	if !is_in_bound(n, m, next_r, next_c) {
		return -99, -99, 0 // ok, no loop
	}

	count := 0
	for matrix[next_r][next_c] == '#' {
		count += 1
		dir_index = (dir_index + 1) % 4
		next_r = r + direction[dir_index][0]
		next_c = c + direction[dir_index][1]
		if count == 5 {
			return -1, -1, 0
		}
	}

	return next_r, next_c, dir_index
}
func is_in_bound(n, m, r, c int) bool {
	return r >= 0 && r < n && c >= 0 && c < m
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
