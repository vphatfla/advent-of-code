package utils

import (
	"io"
	"os"
)

func ReadInput(file_name string) string {
	f, err := os.Open(file_name)
	// fmt.Println("path = ", file_name)
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
