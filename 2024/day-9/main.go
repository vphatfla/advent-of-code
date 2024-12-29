package main

import (
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"
	"vphatfla/advent-of-code/2024/utils"
)

type frag struct {
	id     int
	start  int
	end    int
	length int
}

func main() {
	p, _ := os.Getwd()
	raw := utils.ReadInput(p + "/input.txt")
	raw = strings.ReplaceAll(raw, "\n", "")

	// process data
	list := []int{}
	is_free := false
	counter := 0
	for _, r := range raw {
		temp := -1
		if !is_free {
			temp = counter
			counter += 1
		}

		n, _ := strconv.Atoi(string(r))
		for _ = range n {
			list = append(list, temp)
		}
		is_free = !is_free
	}

	// :w

	n := len(list)
	og_list := make([]int, n)
	copy(og_list, list)
	// part 1
	left := 0
	right := len(list) - 1

	for left < right {
		for list[left] != -1 && left < n {
			left += 1
		}

		for list[right] == -1 && right >= 0 {
			right -= 1
		}

		if left >= right {
			continue
		}

		temp := list[left]
		list[left] = list[right]
		list[right] = temp
	}

	// fmt.Println("after re-arraged = ", list)

	// calculate checksum

	res := 0
	for i, v := range list {
		if v == -1 {
			break
		}
		res += i * v
	}

	fmt.Println("PART 1 = ", res)

	// part 2
	copy(list, og_list)
	free_map := make(map[int]int)
	data_arr := []frag{}
	left = 0
	for left < n {
		if list[left] == -1 {
			right = left
			for right < n && list[right] == -1 {
				right += 1
			}
			free_map[left] = right - 1
			left = right
		} else {
			left += 1
		}
	}

	left = 0
	for left < n {
		if list[left] == -1 {
			left += 1
			continue
		}
		right = left
		for right < n && list[right] != -1 && list[left] == list[right] {
			right += 1
		}
		f := frag{
			id:     list[left],
			start:  left,
			end:    right - 1,
			length: right - left,
		}
		data_arr = append(data_arr, f)
		left = right
	}

	free_index_list := []int{}
	for k := range free_map {
		free_index_list = append(free_index_list, k)
	}

	sort.Ints(free_index_list)

	// fmt.Println("List before moved ", list)
	for i := len(data_arr) - 1; i >= 0; i -= 1 {
		//		fmt.Println("At ", data_arr[i])
		//		fmt.Println("free index list ", free_index_list)
		for _, k := range free_index_list {
			if _, exists := free_map[k]; !exists {
				continue
			}
			free_length := free_map[k] - k + 1
			if free_length >= data_arr[i].length && k < data_arr[i].start {
				m := min(free_length, data_arr[i].length)
				//				fmt.Println("m length = ", m, " at k = ", k, " and end ", free_map[k])
				for j := k; j <= k+m-1; j += 1 {
					list[j] = data_arr[i].id
				}

				for j := data_arr[i].start; j <= data_arr[i].end; j += 1 {
					list[j] = -1
				}

				if free_length > m {
					// fmt.Println("detect new free space ")
					new_index := k + m
					free_map[new_index] = free_map[k]
					// fmt.Println("new index = ", new_index, " and end ", free_map[new_index])
					free_index_list = append([]int{new_index}, free_index_list...)
					sort.Ints(free_index_list)
					// fmt.Println("idnex free list ", free_index_list)
				}

				delete(free_map, k)
				break
			}
		}
	}

	res = 0
	for i, v := range list {
		if v != -1 {
			res += i * v
		}
	}

	// fmt.Println("list after moved  ", list)
	fmt.Println("PART 2 = ", res)
}
