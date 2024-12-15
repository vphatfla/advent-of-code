package main

import (
	"fmt"
	"io"
	"os"
	"strings"
)

var xmasArr []string
var resCount int
var dirArr []int

func main() {
	xmasArr = []string{"X", "M", "A", "S"}
	resCount = 0
	dirArr = []int{-1, 0, 1}

	f, err := os.Open("input.txt")

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

	rawData := string(b)

	var matrix [][]string

	tempD := strings.Split(rawData, "\n")

	for _, str := range tempD {
		temp := strings.Split(str, "")
		if len(temp) > 0 {
			matrix = append(matrix, temp)
		}
	}

	for i := range matrix {
		for j := range matrix[i] {
			fmt.Print(matrix[i][j], " , ")
		}
		fmt.Println(" ")
	}

	n := len(matrix)
	m := len(matrix[0])
	fmt.Println(n, " ----  ", m)

	/*
		Part 1
		for r := range n {
			for c := range m {
				if matrix[r][c] == xmasArr[0] {
					matrix[r][c] = "."
					for i := range len(dirArr) {
						for j := range len(dirArr) {
							dfs(matrix, n, m, r+dirArr[i], c+dirArr[j], dirArr[i], dirArr[j], 1)
						}
					}
					matrix[r][c] = xmasArr[0]
				}
			}
		}
	*/

	// Part 2
	for r := 1; r < n-1; r += 1 {
		for c := 1; c < m-1; c += 1 {
			if check_double_mas(matrix, r, c) {
				resCount += 1
			}
		}
	}
	fmt.Println(resCount)
}

func dfs(matrix [][]string, n, m, r, c, dir_i, dir_j, idx int) {
	if r < 0 || r >= n || c < 0 || c >= m {
		return
	}

	if matrix[r][c] == "." {
		return
	}

	if matrix[r][c] == xmasArr[idx] {
		if idx == len(xmasArr)-1 {
			fmt.Println("at ", r, " : ", c, " = ", matrix[r][c], " idx = ", idx)
			resCount += 1
		} else {
			temp := matrix[r][c]
			matrix[r][c] = "."
			dfs(matrix, n, m, r+dir_i, c+dir_j, dir_i, dir_j, idx+1)
			matrix[r][c] = temp
		}
	}

}

func check_double_mas(matrix [][]string, r, c int) bool {
	fmt.Println("at ", r, " and ", c)
	return matrix[r][c] == "A" &&
		((matrix[r-1][c-1] == "M" && matrix[r+1][c+1] == "S") || (matrix[r-1][c-1] == "S" && matrix[r+1][c+1] == "M")) &&
		((matrix[r-1][c+1] == "M" && matrix[r+1][c-1] == "S") || (matrix[r-1][c+1] == "S" && matrix[r+1][c-1] == "M"))
}
