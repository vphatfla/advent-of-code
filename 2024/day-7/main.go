package main

import (
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"
)

func main() {
	raw_data := read_input("input.txt")
	lines := strings.Split(raw_data, "\n")

	// process the data
	var data [][]int64
	for _, line := range lines {
		if len(line) == 0 {
			continue
		}
		temp_line := strings.Split(line, " ")
		m := len(temp_line)

		arr := make([]int64, m)

		for i, str := range temp_line {
			if i == 0 {
				arr[i], _ = strconv.ParseInt(str[:len(str)-1], 10, 64)
			} else {
				arr[i], _ = strconv.ParseInt(str, 10, 64)
			}
		}
		data = append(data, arr)
	}

	// fmt.Println("Processed data : \n", data)

	// part 1

	var res int64

	for _, row := range data {
		if correct_eq(row[1:], row[0], 0, 0) {
			res += row[0]
		}
	}
	fmt.Println("Part 1 ", res)

	// part 2

	res = 0

	for _, row := range data {
		if correct_eq_with_concat(row[1:], row[0], 0, 0) {
			res += row[0]
		}
	}

	fmt.Println("Part 2 = ", res)
}

func correct_eq(nums []int64, target int64, index int, sum int64) bool {
	if sum == target && index == len(nums) {
		return true
	}
	if sum > target || index >= len(nums) {
		return false
	}

	return correct_eq(nums, target, index+1, sum+nums[index]) || correct_eq(nums, target, index+1, sum*nums[index])
}

func correct_eq_with_concat(nums []int64, target int64, index int, sum int64) bool {
	if sum == target && index == len(nums) {
		return true
	}
	if sum > target || index >= len(nums) {
		return false
	}

	return correct_eq_with_concat(nums, target, index+1, sum+nums[index]) ||
		correct_eq_with_concat(nums, target, index+1, sum*nums[index]) ||
		correct_eq_with_concat(nums, target, index+1, concat_nums(sum, nums[index]))
}

func concat_nums(n1, n2 int64) int64 {
	var nums []int64
	for n2 > 0 {
		nums = append(nums, n2%10)
		n2 /= 10
	}

	for i := len(nums) - 1; i >= 0; i -= 1 {
		n1 = n1*10 + nums[i]
	}

	return n1
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
