package main

import (
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"
)

func main() {
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

	order_map, update_list := process_raw_data(string(b))

	// part 1
	res := 0
	for _, list := range update_list {
		if check := check_order(order_map, list); check {
			res += list[len(list)/2]
		}
	}

	fmt.Println("part 1 ", res)

	// part 2
	res = 0
	for _, list := range update_list {
		check := check_order(order_map, list)

		if !check {
			list = correct_order(order_map, list)
			res += list[len(list)/2]

		}
	}

	fmt.Println("part 2 ", res)
}

func correct_order(order_map map[int]map[int]bool, list []int) []int {
	i := 0
	for i < len(list) {
		check := true
		j := i + 1
		for j < len(list) {
			if _, ok := order_map[list[i]][list[j]]; ok {
				// out of order, reorder
				check = false
				temp := list[i]
				list[i] = list[j]
				list[j] = temp
				break
			}
			j += 1
		}

		if check {
			i += 1
		}
	}

	return list
}
func check_order(order_map map[int]map[int]bool, list []int) bool {
	check := true
	for i := 0; i < len(list); i += 1 {
		for j := i + 1; j < len(list); j += 1 {
			if _, ok := order_map[list[i]][list[j]]; ok {
				// ok means key exist, which is not in correct order
				check = false
				break
			}
		}
		if !check {
			break
		}
	}

	return check
}
func process_raw_data(raw_data string) (map[int]map[int]bool, [][]int) {
	parts := strings.Split(raw_data, "\n\n")

	// order list
	order_map := make(map[int]map[int]bool)

	list := strings.Split(parts[0], "\n")
	for _, e := range list {
		num_list := strings.Split(e, "|")
		p1, _ := strconv.Atoi(num_list[0])
		p2, _ := strconv.Atoi(num_list[1])

		if _, exist := order_map[p2]; !exist {
			order_map[p2] = make(map[int]bool)
		}

		order_map[p2][p1] = true
	}

	// update list
	var update_list [][]int

	lists := strings.Split(parts[1], "\n")

	for _, l := range lists {
		var row []int
		num_str := strings.Split(l, ",")
		for _, str := range num_str {
			num, _ := strconv.Atoi(str)
			row = append(row, num)
		}
		update_list = append(update_list, row)
	}

	return order_map, update_list
}
