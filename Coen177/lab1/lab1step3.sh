# Name: Sami Shibli
# Date: April 2nd 2024
# Title: Lab1 
# Description: This program computes the area and perimeter of a circle given its radius.
#!/bin/sh
calculate_area() {
    echo "scale=2; 3.14 * $1 * $1" | bc
}

calculate_perimeter() {
    echo "scale=2; 2 * 3.14 * $1" | bc
}

is_positive_number() {
    awk -v num="$1" 'BEGIN {exit !(num > 0)}'
}

echo "Enter the radius of the circle: "
read radius

if is_positive_number "$radius"; then
    area=$(calculate_area "$radius")
    perimeter=$(calculate_perimeter "$radius")
    echo "The area of the circle with radius $radius is $area."
    echo "The perimeter of the circle with radius $radius is $perimeter."
else
    echo "Error: The radius must be a strictly positive number."
fi
